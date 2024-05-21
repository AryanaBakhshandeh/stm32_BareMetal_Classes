#ifndef ARYANA_LCD_h
#define ARYANA_LCD_h

class aryana_lcd
{

public:
    aryana_lcd(char = 'A', int = 4, int = 5, int = 6);// constructior -> configs LCD (PA0~PA3= D4~D7 |PA4 = RS | PA5 =RW | PA6 = EN)

    void sendCommand(unsigned char command);
    void sendChar(unsigned char command);
    void sendString(char string[]);

private:
    char port;  //'A'
    int rs_pin; // 4
    int rw_pin; // 5
    int en_pin; // 6

    void LCD_GPIO_Init(void);
    void LCD_Initialaze();                          // initializing 
    void LCD_4UpperBitsWrite(char data ,int RS);   // set RS  1(data) or 0(command)
    int String_length(char string[]) ;
};

#endif

/*		-=========	Commands !============================================================
1	            Function Set: 8-bit, 1 Line, 5x7 Dots                       	0x30	48
2	            Function Set: 8-bit, 2 Line, 5x7 Dots                       	0x38	56
3	            Function Set: 4-bit, 1 Line, 5x7 Dots                       	0x20	32
4	            Function Set: 4-bit, 2 Line, 5x7 Dots                       	0x28	40
5	            Entry Mode	                                                    0x06	6
6	            Display off Cursor off
                (clearing display without clearing DDRAM content)	            0x08	8

7	            Display on Cursor on	                                        0x0E	14
8	            Display on Cursor off	                                        0x0C	12
9	            Display on Cursor blinking	                                    0x0F	15
10	            Shift entire display left	                                    0x18	24
11	            Shift entire display right	                                    0x1C	30
12	            Move cursor left by one character	                            0x10	16
13	            Move cursor right by one character	                            0x14	20
14	            Clear Display (also clear DDRAM content)	                    0x01	1
15	            Set DDRAM address or coursor position on display        0x80 + address*	      128 + address*
16	            Set CGRAM address or set pointer to CGRAM location	    0x40 + address**	  64 + address**


Sr.No.	Hex Code	Command to LCD instruction Register
1	    01	        Clear display screen
2	    02	        Return home
3	    04	        Decrement cursor (shift cursor to left)
4	    06	        Increment cursor (shift cursor to right)
5	    05	        Shift display right
6	    07	        Shift display left
7	    08	        Display off, cursor off
8	    0A	        Display off, cursor on
9	    0C	        Display on, cursor off
10	    0E	        Display on, cursor blinking
11	    0F	        Display on, cursor blinking
12	    10	        Shift cursor position to left
13	    14	        Shift the cursor position to the right
14	    18	        Shift the entire display to the left
15	    1C	        Shift the entire display to the right
16	    80	        Force cursor to the beginning ( 1st line)
17	    C0	        Force cursor to the beginning ( 2nd line)


*/
