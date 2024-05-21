# stm32_BareMetal_Classes

<h1>Table of contents</h1>

<ol dir="auto">
  <li>
    <a href="#about">About</a>
  </li>
  <li> 
    <a href="#how-to-use-libraries">How to use Libraries </a>
    <br>
    2.1 <a href="#gpio"><b >gpio class</b> </a>
    <br>
    2.2 <a href="#delay"><b>delay class</b></a>
    <br>
    2.3 <a href="#lcd"><b>lcd class</b></a>
    <br>
    2.4 <a href="#keypad"><b>keyPad class</b> </a>
  </li>
</ol>

## About

There you can find Object Oriented Libraries for your STM32 projects that is written in bare-metal method. <br>
I'm still working on this ... <br>

currently you can find these libraries in my repository:
<ul>
  <li >aryana_gpio_class.h</li>
  <li>aryana_delay_class.h</li>
  <li>aryana_lcd_class.h</li>
  <li>aryana_keyPad_class.h</li>
</ul>

In the following ,you can find the instructions about each libraries. so feel free to look at them ...

## How to use Libraries
at first , you must include your propper stm32fyxx.h library to your project. <br>( for example if you use stm32f401re you should include stm32f4xx.h)
<br><br>
+ ***read the KeyPad example to laern how to use all the libraries at once***


### GPIO
- **this class has the following functions:** 


1. enable Port x
```c++
void Enable(char PortName); 
```
  2. Set Port x Pin i as Input
```c++
 void PINiSetMode_INPUT(char PortName,unsigned int pin);
```  
  3. Set Port x Pin i as Output
```c++
  void PINiSetMode_OUT(char PortName,unsigned int pin);   
```  
  4. Set Port x Pin i Low (0)
```c++
void PINi_Low(char PortName,unsigned int pin);
```
  5.  Set Port x Pin i High (1)
```c++
void PINi_High(char PortName,unsigned int pin);
```
  6. set value of Port x pin i 0 or 1
```c++
void PINi_Write(char PortName,unsigned int pin,int bit);
```
  7.   read entire Portx's value and write it to {int* PortInputValue_Array} 
```c++
void Read(char PortName,int* PortInputValue_Array);
```

- **HOW TO USE**

1. enable GPIOx
2. set GPIOx Pin i as input or out put
3. use any funtcion as you need... :)

- **GPIO example**
***Blinking LED***
```c++
#include <stm32f4xx.h>
#include "aryana_GPIO_class.h"
#define LED_PORT 'A'
#define LED_PIN 2


int main(void)
{
    aryana_GPIO gpio;  // creating an object
    gpio.Enable(LED_PORT);
    gpio.PINiSetMode_OUT(LED_PORT,LED_PIN);
  
  while(1)
  {
      gpio.PINi_High(LED_PORT,LED_PIN);
      for(int i=0;i<6000 <i++);
      gpio.PINi_Low(LED_PORT,LED_PIN);
      for(int i=0;i<6000 <i++);
  }
}

```

### ADC


### delay
- **this class has the following functions:** 
1.
```c++
ms(int delay_ms)
```
### lcd

- **this class has the following functions:** 
1. class's Constructor
  ```c++
    aryana_lcd(char = 'A', int = 4, int = 5, int = 6);// constructior -> configs LCD (PA0~PA3= D4~D7 |PA4 = RS | PA5 =RW | PA6 = EN)
  ```
2. send command to LCD
  ```c++
 void sendCommand(unsigned char command);
  ```
3. send single character to LCD
  ```c++
 void sendChar(unsigned char command);
  ```
4.send string to LCD 
  ```c++
  void sendString(char string[]);
  ```

- **HOW TO USE**
1. when creating the object , set proper values fro constructor. -> the constructor will config all the requierd pins and ports . so dont worry to do anything fancy.

```c++
 aryana_lcd lcd('B', 4, 5, 6);
```
2. send any string or command to LCD as you wish :) .

### KeyPad 
**this library has the following functions:**
1. class's Constructor
```c
aryana_keyPad(char myport = 'C', int row0 = 0, int row1 = 1, int row2 = 2, int row3 = 3, int col0 = 4, int col1 = 5, int col2 = 6, int col3 = 7);
```
2. get the Pressed key
```c
char getPressedKey(void);
```

<br>


- **HOW TO USE**
  just use getPressedKey function after creating the Obj , to listen to the keypad and get the key.

**example**
```c++
//Project : smart Door lock

#include "stm32f4xx.h"
#include "aryana_lcd_class.h"
#include "aryana_keyPad.h"
#include "aryana_GPIO_class.h"
#include "aryana_delay.h"

char ramz[5] = "2583";
char rootPass[5] = "2500";

void Vorud(aryana_delay delay, aryana_GPIO gpio, aryana_lcd lcd,
		aryana_keyPad keyPad);
void changePassword(aryana_delay delay, aryana_GPIO gpio, aryana_lcd lcd,
		aryana_keyPad keyPad);
void home(aryana_lcd lcd);

char checkPassword(char *pas,char enteredPass[4]);
char getPass(char *PassHold,aryana_lcd lcd,aryana_delay delay ,aryana_keyPad keyPad);

int main(void)
{
    aryana_keyPad keyPad;
    aryana_lcd lcd('A', 4, 5, 6);
    aryana_GPIO gpio;
    aryana_delay delay;

    // setting up the Alarm
    gpio.Enable('B');
    gpio.PINiSetMode_OUT('B', 7);
    gpio.PINi_Low('B', 7);

    lcd.sendString("Dorud sarvaram");
    lcd.sendCommand(0xC0); // 2nd line
    lcd.sendString("Farman >> ");

    char key;
    while (1)
    {
        key = keyPad.getPressedKey();
        delay.ms(60000);
        if (key == 'A') // Vorud
        {
            Vorud(delay, gpio, lcd, keyPad);
        }
        if (key == 'B') // change pass
        {
        	changePassword(delay, gpio, lcd, keyPad);
        }
    }
}

void Vorud(aryana_delay delay, aryana_GPIO gpio, aryana_lcd lcd,
           aryana_keyPad keyPad)
{
    lcd.sendCommand(0x01); // clear screen
    lcd.sendCommand(0x80); // 1nd line
    lcd.sendString("Ramz >> ");
    char holder[4];
    for (char i = 0; i < 4; i++)
    {
        holder[i] = keyPad.getPressedKey();
        delay.ms(60000);
        lcd.sendChar(holder[i]);
        ;
    }

    char TruePass = 1;
    for (char i = 0; i < 4; i++)
    {
        if (holder[i] != ramz[i])
        {
            TruePass = 0;
            break;
        }
    }
    lcd.sendCommand(0x01); // clear screen
    lcd.sendCommand(0x80); // 1nd line
    if (TruePass == 0)
    {
        lcd.sendString("ramz NaDorost :|");
        gpio.PINi_High('B', 7); // alarm !
    }
    else
    {
        lcd.sendString("KhoshAmadid ^_^");
        gpio.PINi_Low('B', 7);
    }
}

void changePassword(aryana_delay delay, aryana_GPIO gpio, aryana_lcd lcd, aryana_keyPad keyPad)
{
    char are=2; //1=are 2-na (loop)

    //enter Root Password
    char holdRootEnteredPass[5];
    char flagRootPass=0;
    char flagContinue=1;;
    while(flagRootPass==0&&flagContinue==1)
    {
		lcd.sendCommand(0x01); // clear screen
		lcd.sendCommand(0x80); // 1nd line
		lcd.sendString("RootPass>> ");
		flagContinue=getPass(holdRootEnteredPass,lcd,delay,keyPad);
		if (flagContinue==0)
			break;
		flagRootPass=checkPassword(rootPass,holdRootEnteredPass);

     }

    while(are==2&&flagContinue==1)
    {
		lcd.sendCommand(0x01); // clear screen
		lcd.sendCommand(0x80); // 1nd line
		lcd.sendString("Ramze nou>>");

		char newPass[5];
		flagContinue=getPass(newPass,lcd,delay,keyPad);
		if (flagContinue==0)
					break;

		lcd.sendCommand(0x01); // clear screen
		lcd.sendCommand(0x80); // 1nd line
		lcd.sendString("dorost? ");
		lcd.sendString(newPass);
		lcd.sendCommand(0xC0); // 2nd line
		lcd.sendString("1-are 2-na");
		char Verification = 0;
		Verification = keyPad.getPressedKey();
		while (1)
		{
			if (Verification == '1')
			{
				for (char i = 0; i < 4; i++)
					ramz[i] = newPass[i];
				are=1;

				break;
			}
			else if (Verification == '2')
			{
				are=2;
				break;
			}
		}

    }
    home(lcd);
}

void home(aryana_lcd lcd){
		lcd.sendCommand(0x01); // clear screen
	    lcd.sendCommand(0x80); // 1nd line
		lcd.sendString("Dorud sarvaram");
		lcd.sendCommand(0xC0); //2nd line
		lcd.sendString("Farman >> ");

}


char checkPassword(char *pas,char enteredPass[4]){ //return 1 == true  return 0 = false
	char TruePass=1;;
	for (char i = 0; i < 4; i++)
	    {
	        if (enteredPass[i] != pas[i])
	        {
	            TruePass = 0;
	            break;
	        }
	    }
	    return TruePass;

}

char getPass(char *PassHold,aryana_lcd lcd,aryana_delay delay ,aryana_keyPad keyPad){ // 0==cancle  1== true
	 char TruePass = 1;
		for (char i = 0; i < 4; i++)
		{
			PassHold[i] = keyPad.getPressedKey();
			if(PassHold[i]=='C')
				return 0;

			delay.ms(60000);
			lcd.sendChar(PassHold[i]);
		}
	return 1;

}



```
