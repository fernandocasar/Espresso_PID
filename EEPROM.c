#include "EEPROM.h"




void EEPROM_Write(unsigned char address, unsigned char databyte)
{ // writes the "databyte" value to EEPROM at the address given
  // location in "address".
    EECON1bits.EEPGD = 0;   // Set to access EEPROM memory
    EECON1bits.CFGS = 0;    // Do not access Config registers

    EEDATA = databyte;      // Load EEDATA with byte to be written
    EEADR = address;        // Load EEADR with address of location to write.

    EECON1bits.WREN = 1;    // Enable writing

    // NOTE: as a protective measure to prevent accidental writes, the following
    // sequence must be completed without interruption to write a byte to EEPROM.
    // Therefore, if interrupts are used they should be disabled during the sequence
    // as it would not work if an interrupt was received during the sequence.

    INTCONbits.GIE = 0;   // Disable interrupts
    EECON2 = 0x55;          // Begin Write sequence
    EECON2 = 0xAA;
    EECON1bits.WR = 1;      // Set WR bit to begin EEPROM write
    INTCONbits.GIE = 1;   // re-enable interrupts

    while (EECON1bits.WR == 1)
    {   // wait for write to complete.  WR bit will be cleared when write finishes
        // EEPROM write completion will also set the EEIF flag bit in PIR2, which
        // may be used to generate an interrupt when the EEPROM write completes.
    };

    EECON1bits.WREN = 0;    // Disable writing as a precaution.
}

unsigned char EEPROM_Read(unsigned char address)
{ // reads and returns the EEPROM byte value at the address given
  // given in "address".

    EECON1bits.EEPGD = 0;   // Set to access EEPROM memory
    EECON1bits.CFGS = 0;    // Do not access Config registers

    EEADR = address;        // Load EEADR with address of location to read.

    // execute the read
    EECON1bits.RD = 1;      // Set the RD bit to execute the EEPROM read

    // The value read is ready the next instruction cycle in EEDATA.  No wait is
    // needed.

    return EEDATA;
}
