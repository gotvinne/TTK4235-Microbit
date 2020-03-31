#include "led_matrix.h"
#include "gpio.h"
#include <stdint.h>

/* Pins 13, 14, 15 on the micro:bit */
#define SUPPLY_PINS 0xe000
/* Pins 4, 5, 6, 7, 8, 9, 10, 11, 12 on the micro:bit */
#define GROUND_PINS 0x1ff0

void led_matrix_init(){
    GPIO->DIRSET = SUPPLY_PINS | GROUND_PINS; //| går forran = 
    GPIO->OUTCLR = SUPPLY_PINS | GROUND_PINS; //Resultatet er lang maske med 15 1'ere. 
} //11111111111100000

void led_matrix_turn_on(){
    GPIO->OUTSET = SUPPLY_PINS; //LED er output, så dei kan vi sette på ved å endre OUT-registeret. 
}

void led_matrix_turn_off(){
    GPIO->OUTCLR = SUPPLY_PINS;
}
