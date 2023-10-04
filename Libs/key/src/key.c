#include "key.h"
#include "io_define.h"

Key* _keys[KEY_MAX_NUM];
uint8_t _keyNum = 0;
Driver* _driver;

void Key_add(Key* key, Key_Config* config, KeyCallbacks* callback, ActiveState activeState){
    // init key    
    key->config = config;
    key->callback = callback;
    key->state = KeyState_None;  
    key->activeState = activeState; 
    // Store address
    _keys[_keyNum] = key;
    _keyNum++;       
}

void Key_ISR(void){
    uint8_t len = _keyNum;
    Key** keys = _keys;
    
    while(len--){
        Key* key = *keys;             
         
        uint8_t pinState = _driver->read(key->config);                 
        key->state = ((key->state << 1) | (pinState^ key->activeState)) & 0x03; 
        if(key->callback->callBacks[key->state]){
            key->callback->callBacks[key->state]();
        }                  
        keys++;    
    }            
}


void Key_init(Driver* driver){
    //keys->config
    //(*keys).config
    uint8_t len = _keyNum;
    Key** keys = _keys;       
    _driver = driver;          
    while(len--)
    {      
        Key* key = *keys; 
        _driver->init(key->config, key->activeState);
        keys++;
    }    
}
