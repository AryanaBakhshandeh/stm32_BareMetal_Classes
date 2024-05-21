#include "aryana_gpio_class.h"
#include "stm32f4xx.h"

void aryana_GPIO::Enable(char PortName) // example : GPIOx_Enable('A');  -> enables PortA's clock
{
    switch(PortName)
    {
        case 'A':
            RCC->AHB1ENR |= (1U<<0) ;
            break;

        case 'B':
            RCC->AHB1ENR |= (1U<<1) ;
            break;

        case 'C':
            RCC->AHB1ENR |= (1U<<2) ;
            break;

        case 'D':
            RCC->AHB1ENR |= (1U<<3) ;
            break;

        default:
        ;
    }
}
void aryana_GPIO::PINiSetMode_INPUT(char PortName,unsigned int pin)
{
    unsigned int pin_Bite_L=1U;
    unsigned int pin_Bite_H;
    
    for(unsigned int i = 1; i<=(2*pin) ;i++){
        pin_Bite_L=(pin_Bite_L<<1);
    }

    pin_Bite_H=pin_Bite_L<<1;

    switch(PortName)
    {
        case 'A':
            GPIOA->MODER &=~ pin_Bite_L ;
            GPIOA->MODER &=~ pin_Bite_H;
            break;

        case 'B':
            GPIOB->MODER &=~ pin_Bite_L ;
            GPIOB->MODER &=~ pin_Bite_H;
            break;

        case 'C':
            GPIOC->MODER &=~ pin_Bite_L ;
            GPIOC->MODER &=~ pin_Bite_H;
            break;

        case 'D':
            GPIOD->MODER &=~ pin_Bite_L ;
            GPIOD->MODER &=~ pin_Bite_H;
            break;

        default: 
        ;
    }
}
void aryana_GPIO::PINi_High(char PortName,unsigned int pin) // example : GPIOx_PINi_High('A',2) -> sets PA2 to High
{
	unsigned int pinCode=(1U<<0);

	for(unsigned int i = 1; i<= pin ;i++){
		pinCode=(pinCode<<1);
	    }
    switch(PortName)
    {
        case 'A':
        	GPIOA->ODR |=pinCode;
        	//GPIOA->BSRR = pinCode;
            break;

        case 'B':
        	GPIOB->ODR |=pinCode;
            //GPIOB->BSRR = pinCode;
            break;

        case 'C':
        	GPIOC->ODR |=pinCode;
            //GPIOC->BSRR = pinCode;
            break;

        case 'D':
        	GPIOD->ODR |=pinCode;
            //GPIOD->BSRR = pinCode;
            break;

        default: 
        ;
    }
}
void aryana_GPIO::PINi_Low(char PortName,unsigned int pin) // example : GPIOx_PINi_LOW('A',2) -> sets PA2 to low ,that is, it resets PA2
{
	unsigned int pinCode=(1U<<0);
   // unsigned int pinCode_set=(1U<<0);
   // unsigned int pinCode_Reset=(1U<<0);

    for(unsigned int i = 1; i<= pin ;i++){
    	//pinCode_set=(pinCode_set<<1);
    	pinCode=(pinCode<<1);
        }

    //pinCode_Reset=(pinCode_set<<16);

    switch(PortName)
    {
    	case 'A':
    		GPIOA->ODR &=~ pinCode;
            //GPIOA->BSRR = pinCode_Reset;
              break;

         case 'B':
        	 GPIOB->ODR &=~ pinCode;
            // GPIOB->BSRR = pinCode_Reset;
             break;

         case 'C':
        	 GPIOC->ODR &=~ pinCode;
            // GPIOC->BSRR = pinCode_Reset;
             break;

         case 'D':
        	 GPIOD->ODR &=~ pinCode;
             //GPIOD->BSRR = pinCode_Reset;
             break;
         default: ;
    }
}
void aryana_GPIO::PINiSetMode_OUT(char PortName,unsigned int pin)  // example : GPIOx_PINiSetMode_OUT('A',0);  -> sets PA0 to output
{
    unsigned int pin_Bite_L=1U;
    unsigned int pin_Bite_H;
    for(unsigned int i = 1; i<=(2*pin) ;i++){
        pin_Bite_L=(pin_Bite_L<<1);
    }
    pin_Bite_H=pin_Bite_L<<1;

     switch(PortName)
    {
        case 'A':
            GPIOA->MODER |= pin_Bite_L ;
            GPIOA->MODER &=~ pin_Bite_H;
            break;

        case 'B':
            GPIOB->MODER |= pin_Bite_L ;
            GPIOB->MODER &=~ pin_Bite_H;
            break;

        case 'C':
            GPIOC->MODER |= pin_Bite_L ;
            GPIOC->MODER &=~ pin_Bite_H;
            break;

        case 'D':
            GPIOD->MODER |= pin_Bite_L ;
            GPIOD->MODER &=~ pin_Bite_H;
            break;

        default: 
        ;
    }
}
void aryana_GPIO::PINi_Write(char PortName,unsigned int pin,int bit) // example : GPIOx_PINi_LOW('A',2) -> sets PA2 to low ,that is, it resets PA2
{
     if (bit==0){
    	 aryana_GPIO::PINi_Low(PortName,pin);
     }
     else if(bit==1){
    	 aryana_GPIO::PINi_High(PortName,pin);
     }
	
}

void aryana_GPIO::Read(char PortName,int* PortInputValue_Array)
{
    int InputRegValue; //32bit
    switch(PortName)
    {
        case 'A':
            InputRegValue = GPIOA->IDR;          
            break;

        case 'B':
            InputRegValue = GPIOB->IDR;  
            break;

        case 'C':
            InputRegValue = GPIOC->IDR;  
            break;

        case 'D':
            InputRegValue = GPIOD->IDR;  
            break;
        default:;
    }

    int BitSelector=(1U<<0); 
    for(int i=0; i < 16; ++i)
    {
        int hold =-1; //weather the i's index is 0 or 1;
        
        if(i!=0)
            BitSelector=(BitSelector<<1);

        hold=(InputRegValue & BitSelector);
        if (hold==0)
            hold = 0; // pin i is 0
        else if (hold!=-1)
            hold = 1; // pin i is 1
        PortInputValue_Array[i]=hold;
    }

}
