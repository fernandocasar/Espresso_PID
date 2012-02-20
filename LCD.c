#include "LCD.h"


/*special characters defined*/
unsigned char font_a_char_0[8] = {

0b00000000,
0b00000000,
0b00000001,
0b00000010,
0b00000111,
0b00000000,
0b00011111,
0b00011111

};

unsigned char font_a_char_1[8] = {

0b00001100,
0b00011000,
0b00010000,
0b00001000,
0b00000100,
0b00000000,
0b00011111,
0b00011111

};

unsigned char font_a_char_2[8] = {

0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00010000,
0b00011100

};

unsigned char font_a_char_3[8] = {

0b00011111,
0b00011111,
0b00011111,
0b00011111,
0b00001111,
0b00000111,
0b00000011,
0b00000001

};

unsigned char font_a_char_4[8] = {

0b00011111,
0b00011111,
0b00011111,
0b00011111,
0b00011111,
0b00011111,
0b00011110,
0b00011100

};

unsigned char font_a_char_5[8] = {

0b00010010,
0b00010110,
0b00011100,
0b00010000,
0b00000000,
0b00000000,
0b00000000,
0b00000000

};


void Load_Char(void)
{
    unsigned char cgram_loc;
    unsigned char i;

    //Load Custom Character 0
    for(i=0;i<8;i++){


        cgram_loc = 0b01000000 + i;
        Delay100TCYx(2);
        WriteCmdXLCD(cgram_loc);
        Delay100TCYx(2);
        WriteDataXLCD(font_a_char_0[i]);
        Delay100TCYx(2);

        cgram_loc = 0b01001000 + i;
        Delay100TCYx(2);
        WriteCmdXLCD(cgram_loc);
        Delay100TCYx(2);
        WriteDataXLCD(font_a_char_1[i]);
        Delay100TCYx(2);

        cgram_loc = 0b01010000 + i;
        Delay100TCYx(2);
        WriteCmdXLCD(cgram_loc);
        Delay100TCYx(2);
        WriteDataXLCD(font_a_char_2[i]);
        Delay100TCYx(2);

        cgram_loc = 0b01011000 + i;
        Delay100TCYx(2);
        WriteCmdXLCD(cgram_loc);
        Delay100TCYx(2);
        WriteDataXLCD(font_a_char_3[i]);
        Delay100TCYx(2);

        cgram_loc = 0b01100000 + i;
        Delay100TCYx(2);
        WriteCmdXLCD(cgram_loc);
        Delay100TCYx(2);
        WriteDataXLCD(font_a_char_4[i]);
        Delay100TCYx(2);

        cgram_loc = 0b01101000 + i;
        Delay100TCYx(2);
        WriteCmdXLCD(cgram_loc);
        Delay100TCYx(2);
        WriteDataXLCD(font_a_char_5[i]);
        Delay100TCYx(2);
    }


    WriteCmdXLCD( SET_CUR );
    Delay100TCYx(2);
}


void refresh_LCD( void )
{
    unsigned char cur;
    unsigned char rest;
    while( BusyXLCD());
    WriteCmdXLCD( SET_CUR + 3 );
    counter=0;

    
    sprintf( data, "Temp: %3i.%u  out: % 5i   ",ADC_result/10, ADC_result%10, pid_out);
    
    for( cur=0; cur < 26; cur++)
    {
        while( BusyXLCD());
        WriteDataXLCD(data[cur]);     //write to LCD

        
        counter++;

        if( counter == 13)
        {

            while(BusyXLCD());
            WriteCmdXLCD( ( SET_CUR | 0x40 ) + 3 );
        }
        if( counter == 26)
        {

            while(BusyXLCD());
            WriteCmdXLCD( SET_CUR + 3 );
            counter = 0;
        }
    }
    
}

void Draw_cup(void)
{
    while(BusyXLCD());
    WriteCmdXLCD( SET_CUR);
    Delay100TCYx(4);
    WriteDataXLCD(0x00);
    Delay100TCYx(4);
    WriteDataXLCD(0x01);
    Delay100TCYx(4);
    WriteDataXLCD(0x02);
    Delay100TCYx(4);
    WriteCmdXLCD( SET_CUR | 0x40 );
    Delay100TCYx(4);
    WriteDataXLCD(0x03);
    Delay100TCYx(4);
    WriteDataXLCD(0x04);
    Delay100TCYx(4);
    WriteDataXLCD(0x05);
    Delay100TCYx(4);
    WriteCmdXLCD( SET_CUR + 3 );
    Delay100TCYx(4);
}

void DelayFor18TCY( void )
{
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
}
void DelayPORXLCD (void)
{
  Delay1KTCYx(60); // Delay of 15ms
                   // Cycles = (TimeDelay * Fosc) / 4
                   // Cycles = (15ms * 16MHz) / 4
                   // Cycles = 60,000
  return;
}
void DelayXLCD (void)
{
  Delay1KTCYx(20); // Delay of 5ms
                   // Cycles = (TimeDelay * Fosc) / 4
                   // Cycles = (5ms * 16MHz) / 4
                   // Cycles = 20,000
  return;
}