#ifndef ARYANA_GPIO_H
#define ARYANA_GPIO_H

class aryana_GPIO{
    public:
    void Enable(char PortName); // example : GPIOx_Enable('A');  -> enables PortA's clock
    void PINiSetMode_INPUT(char PortName,unsigned int pin);
    void PINi_High(char PortName,unsigned int pin); // example : GPIOx_PINi_High('A',2) -> sets PA2 to High
    void PINi_Low(char PortName,unsigned int pin); // example : GPIOx_PINi_LOW('A',2) -> sets PA2 to low ,that is, it resets PA2
    void PINiSetMode_OUT(char PortName,unsigned int pin);  // example : GPIOx_PINiSetMode_OUT('A',0);  -> sets PA0 to output
    void PINi_Write(char PortName,unsigned int pin,int bit); // example : GPIOx_PINi_LOW('A',2) -> sets PA2 to low ,that is, it resets PA2
    void Read(char PortName,int* PortInputValue_Array);

};

#endif
