
//PA0 - PA3 = D4- D7
//PA4 = RS
//PA5 =RW
//PA6 = EN


#include "aryana_lcd_class.h"
#include "aryana_gpio_class.h"
#include "aryana_delay_class.h"


aryana_lcd::aryana_lcd(char myPort, int myRs , int myRw, int myEn)
{
		port=myPort;  //'A'
	    rs_pin=myRs; // 4
	    rw_pin=myRw; // 5
	    en_pin=myEn;

	    LCD_Initialaze();

}
int aryana_lcd::String_length(char string[]) {
    int i;
    int count = 0;
    for (i = 0; string[i] != '\0'; i++) {
        count++;
    }
    return count;
}

void aryana_lcd::LCD_GPIO_Init(void)
{
    
	aryana_GPIO gpio;
    aryana_delay delay;
    delay.ms(1000);
    gpio.Enable(port);
    for(int i=0;i<=6;i++)
    {
        gpio.PINiSetMode_OUT(port,i);
    }
    //set EN and RW to low;
    gpio.PINi_Low(port,en_pin);
    gpio.PINi_Low(port,rw_pin);


}



void aryana_lcd::LCD_4UpperBitsWrite(char data ,int RS)// set RS  1(data) or 0(command)
{
    aryana_GPIO gpio;
    aryana_delay delay;
    //Command or Data Mode:
    if(RS==0)
        gpio.PINi_Low(port,rs_pin);
    else
        gpio.PINi_High(port,rs_pin);
    // set data to lcd pins
    char Data4Bit = data & 0xF0;// high bits
    Data4Bit= ( (Data4Bit >> 4) & 0x0F ); // shift 4 bits to right and keep lower bits;
    
    for(int i=0;i<=3;i++)
    {
        int bit=1;
        int bitPositionValue=1;
        for(int j=0;j<i;j++){
            bitPositionValue=bitPositionValue*2;
        }
        if((Data4Bit & bitPositionValue)==0)
        {bit=0;}
        gpio.PINi_Write(port,i,bit);
    }
    gpio.PINi_High(port,en_pin);
    delay.ms(1);
    gpio.PINi_Low(port,en_pin);
    delay.ms(1);

}

void aryana_lcd::sendCommand(unsigned char command)
{
    aryana_delay delay;
	 LCD_4UpperBitsWrite(command,0);
	 delay.ms(1);
	 LCD_4UpperBitsWrite((command<<4),0);
	 delay.ms(1);
}
void aryana_lcd::sendChar(unsigned char command)
{
	aryana_delay delay;

	LCD_4UpperBitsWrite(command,1);
	delay.ms(1);
	LCD_4UpperBitsWrite(command<< 4,1);
	delay.ms(1);
}
void aryana_lcd::sendString(char string[])
{
	int index=0;
	for(index=0 ; index <aryana_lcd::String_length(string);index++ )
		aryana_lcd::sendChar(string[index]);

}

void aryana_lcd::LCD_Initialaze(){

	aryana_delay delay;
// initialize GPIO
	aryana_lcd::LCD_GPIO_Init();
	delay.ms(1000);

// 4 bit mode
	aryana_lcd::LCD_4UpperBitsWrite(0x20,0);
	delay.ms(1);
	aryana_lcd::sendCommand(0x28);

// Clear display
	aryana_lcd::sendCommand(0x01);
// return home
	aryana_lcd::sendCommand(0x02);
// display on - no cursor
	aryana_lcd::sendCommand(0x0F);


}
