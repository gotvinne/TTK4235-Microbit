#include "button.h"
#include "gpio.h"

/* Fyll inn disse to */
#define BUTTON_A_PIN 17
#define BUTTON_B_PIN 26

//GPIO er en variabel i gpio.h som inneholder abstraksjonen av minnemappinga. 
void button_init(){
    GPIO->PIN_CNF[BUTTON_A_PIN] = 0; //Button A, this is config. Input-enheter er 0. 
    GPIO->PIN_CNF[BUTTON_B_PIN] = 0;
}

uint8_t button_a_pressed(){
    uint8_t is_pressed = 0; 
    if (!(GPIO->IN & (1 << 17))){ //Vi sjekker på aktivt lav. 
        is_pressed = 1; 
    }
    return is_pressed; 
}

uint8_t button_b_pressed(){
    uint8_t is_pressed = 0; 
    if (!(GPIO->IN & (1 << 26))){ //Vi sjekker på aktivt lav. 
        is_pressed = 1; 
    }
    return is_pressed; 
}
