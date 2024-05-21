// v0.1  @aryana_Bakhshandeh (pure shahpur)

#include "aryana_gpio_class.h"
#include "aryana_delay_class.h"
#include "aryana_keyPad_class.h"


int aryana_keyPad::getIsPressedFlag(void)
{
    return IsPressedFlag;
}

aryana_keyPad::aryana_keyPad(char myport , int row0 , int row1 , int row2 , int row3 , int col0 , int col1, int col2, int col3)
{
    IsPressedFlag = 0;
    PressedRow = 0;
    PressedCol = 0;
    PortX_Value[16] = {0};
    RowsValue[4] = {0}; // value of KeyPad_row1Pin ~ KeyPad_row4Pin
    char Characters[16] = {'1', '2', '3', 'A',	'4', '5', '6', 'B'	,'7', '8', '9', 'C'  ,'*', '0', '#', 'D'};
    for(char i =0 ; i <16 ;i++){
    	 ArrayCharacters[i]=Characters[i];
    }
    ArrayCharacters[16];
    port =myport;
    row0Pin = row0;
    row1Pin = row1;
    row2Pin = row2;
    row3Pin = row3;
    col0Pin = col0;
    col1Pin = col1;
    col2Pin = col2;
    col3Pin = col3;
    Initialize();
}
void aryana_keyPad::ResetPins(void)
{
    aryana_GPIO gpio;

    gpio.PINi_High(port, col0Pin);
    gpio.PINi_High(port, col1Pin);
    gpio.PINi_High(port, col2Pin);
    gpio.PINi_High(port, col3Pin);
}
void aryana_keyPad::Initialize(void)
{
    aryana_GPIO gpio;
    // AHB1ENR
    gpio.Enable(port);
    // moder
    gpio.PINiSetMode_INPUT(port, row0Pin);
    gpio.PINiSetMode_INPUT(port, row1Pin);
    gpio.PINiSetMode_INPUT(port, row2Pin);
    gpio.PINiSetMode_INPUT(port, row3Pin);
    gpio.PINiSetMode_OUT(port, col0Pin);
    gpio.PINiSetMode_OUT(port, col1Pin);
    gpio.PINiSetMode_OUT(port, col2Pin);
    gpio.PINiSetMode_OUT(port, col3Pin);
    // ODR
    ResetPins();
}

int aryana_keyPad::Listen_toKeyPad(void)
{
    aryana_GPIO gpio;

    IsPressedFlag = 0;
    gpio.Read(port, PortX_Value);
    RowsValue[0] = PortX_Value[row0Pin];
    RowsValue[1] = PortX_Value[row1Pin];
    RowsValue[2] = PortX_Value[row2Pin];
    RowsValue[3] = PortX_Value[row3Pin];

    for (int i = 0; i < 4; i++) // pin i=0 to 3 means   row 1 to row 4
    {
        if (RowsValue[i] == 1)
        {
            IsPressedFlag = 1;
            return i;
        }
    }
}

void aryana_keyPad::rowColFinder(void)
{
	IsPressedFlag=0;
    while (IsPressedFlag != 1)
    {
        Listen_toKeyPad();
    } // listin to keypad until a key is pressed.

    if (IsPressedFlag == 1)
    {
        aryana_GPIO gpio;
        // check col0;
        gpio.PINi_High(port, col0Pin);
        gpio.PINi_Low(port, col1Pin);
        gpio.PINi_Low(port, col2Pin);
        gpio.PINi_Low(port, col3Pin);
        IsPressedFlag = 0;
        int RowHolder = Listen_toKeyPad();
        if (IsPressedFlag == 1)
        {
            PressedRow = RowHolder; // char[0][RowHolder] (rowHolder[0~3])
            PressedCol = 0;
        }
        else
        {
            // check col1;

            gpio.PINi_Low(port, col0Pin);
            gpio.PINi_High(port, col1Pin);
            gpio.PINi_Low(port, col2Pin);
            gpio.PINi_Low(port, col3Pin);
            IsPressedFlag = 0;
            RowHolder = Listen_toKeyPad();
            if (IsPressedFlag == 1)
            {
                PressedRow = RowHolder; // char[1][row]]
                PressedCol = 1;
            }
            else
            {
                // check col2;
                gpio.PINi_Low(port, col0Pin);
                gpio.PINi_Low(port, col1Pin);
                gpio.PINi_High(port, col2Pin);
                gpio.PINi_Low(port, col3Pin);
                IsPressedFlag = 0;
                RowHolder = Listen_toKeyPad();
                if (IsPressedFlag == 1)
                {
                    PressedRow = RowHolder; // char[2][row]]
                    PressedCol = 2;
                }
                else
                {
                    // check col2;
                    gpio.PINi_Low(port, col0Pin);
                    gpio.PINi_Low(port, col1Pin);
                    gpio.PINi_Low(port, col2Pin);
                    gpio.PINi_High(port, col3Pin);
                    IsPressedFlag = 0;
                    RowHolder = Listen_toKeyPad();
                    if (IsPressedFlag == 1)
                    {
                        PressedRow = RowHolder; // char[1][row]]
                        PressedCol = 3;
                    }
                }
            }
        }

        aryana_delay delay;
        delay.ms(1000);
        // finished proccess , now reset output pins to start listining again
        ResetPins();
    }
}

char aryana_keyPad::getPressedKey(void)
{
    aryana_delay delay;
	rowColFinder();
	delay.ms(150000);
    return ArrayCharacters[(4*PressedRow) + (PressedCol)];



}

//==============================================================================================
//==============================================================================================
//==============================================================================================
//==============================================================================================
// how to use this Lib ?//================================================
//======================================================
//======================================================
//======================================================
//=========================================
//=========================================
//=========================================
/*
     #include <stm32f4xx.h>
     #include "aryana_GPIO.h"
     #include "aryana_SysTickDelay.h"
     #include "aryana_Keypad4x4.h"
     #include "aryana_LCD16x2_4bit.h"
     int main()
     {
          LCD_Initialaze();
          KeyPad_Init();
          while (1)
          {
               KeyPad_Listen_InsideLoop();
               rowColFinder();
               //now col and row is been found ... do your things....
               if(IsPressedFlag==1){
                    LCD_data_Character(KeyPad_ArrayCharacters[(4*PressedRow) + (PressedCol)]);
                    IsPressedFlag=0;
                    sysTickDelay_ms(2000);
               }
               ////-----------------------------------------------
               KeyPad_ResetPins();
          }
     }

*/
