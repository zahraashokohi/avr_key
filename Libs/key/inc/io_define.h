#ifndef _IO_DEFINE_H_
#define _IO_DEFINE_H_

#include <stdint.h>
#include <io.h>

typedef union {
    uint8_t value;
    struct{
        uint8_t b0 : 1;
        uint8_t b1 : 1;
        uint8_t b2 : 1;
        uint8_t b3 : 1;
        uint8_t b4 : 1;
        uint8_t b5 : 1;
        uint8_t b6 : 1;
        uint8_t b7 : 1;        
    };
}Register;

typedef struct{
    Register pin;
    Register ddr;
    Register port;
}GPIO;

#define GPIOA       ((GPIO*)&PINA)
#define GPIOB       ((GPIO*)&PINB)
#define GPIOC       ((GPIO*)&PINC)
#define GPIOD       ((GPIO*)&PIND)
 
typedef enum {
    GPIO_Pin0 = 0,
    GPIO_Pin1 = 1,
    GPIO_Pin2 = 2,
    GPIO_Pin3 = 3,
    GPIO_Pin4 = 4,
    GPIO_Pin5 = 5,
    GPIO_Pin6 = 6,
    GPIO_Pin7 = 7,
}GPIO_Pin;

#endif //_IO_DEFINE_H_
