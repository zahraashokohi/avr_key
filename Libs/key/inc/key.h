#ifndef _KEY_H_
#define _KEY_H_

#include "io_define.h"

#define KEY_MAX_NUM     2

typedef enum {
    ACTIVE_LOW = 0,
    ACTIVE_HIGH = 1,
    
}ActiveState;
typedef enum{
    KeyState_Hold,
    KeyState_Release,
    KeyState_Pressed,
    KeyState_None,
    KeyState_Num,
}KeyState; 


typedef struct {
    GPIO* io;
    GPIO_Pin pin;    
}Key_Config;



typedef void (*KeyCallback) (void);
typedef uint8_t (*Key_ReadFunction) (Key_Config*);
typedef void (*Key_initFunction) (Key_Config*, ActiveState activeState);

typedef union{
   KeyCallback    callBacks[KeyState_Num];   
   struct{  
       KeyCallback  onHold;
       KeyCallback  onReleased;
       KeyCallback  onPressed;
       KeyCallback  onNone; 
   };
}KeyCallbacks;

typedef struct{
    Key_ReadFunction read;
    Key_initFunction init;
}Driver;

typedef struct{
    Key_Config* config;
    KeyCallbacks* callback;
    KeyState state; 
    ActiveState  activeState;   
}Key;


void Key_add(Key* key, Key_Config* config, KeyCallbacks* callback, ActiveState activeState);
void Key_ISR(void);
void Key_init(Driver* driver);

#endif 
