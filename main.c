#include "main.h"

#ifndef NULL
    #define NULL (void*)0
#endif

/*KeyCallback callback[KeyState_Num] = {
    NULL, keyOnRelease, keyOnPressed, NULL     
};*/

KeyCallbacks  callBackFun1;
KeyCallbacks  callBackFun2;

Driver driver = {
    keyRead, keyInit 
};

void main(void)
{
    Key key1;  
    Key key2;
    Key_Config config1 = {
        GPIOA, GPIO_Pin0,
    };  
    Key_Config config2 = {
        GPIOA, GPIO_Pin1,
    };
    Key_add(&key1, &config1, &callBackFun1, ACTIVE_LOW);
    Key_add(&key2, &config2, &callBackFun2, ACTIVE_HIGH);
    callBackFun1.onPressed = keyOnPressed1;
    callBackFun1.onReleased = keyOnRelease1;
    callBackFun2.onPressed = keyOnPressed2;
    callBackFun2.onReleased = keyOnRelease2;
    Key_init(&driver);
    while (1)
    {
        Key_ISR();
        //PORTB = key1.state; 
        //delay_ms(500);
         
    }
}


void keyOnPressed1 (void){
    PORTB++;  
}
void keyOnRelease1 (void){
    PORTC++;
} 
void keyOnPressed2 (void){
    PORTC++;  
}
void keyOnRelease2 (void){
    PORTB++;
} 

uint8_t keyRead(Key_Config* config){
    return (config->io->pin.value & (1 << config->pin)) != 0;
}
void keyInit(Key_Config* config,ActiveState activeState){
    config->io->ddr.value &= ~(1 << config->pin);
    config->io->port.value |= activeState << config->pin;
}

