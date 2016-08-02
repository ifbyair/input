//rotaryencoder.c
#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "smart_encoder.h"

struct encoder main_encoder;

void updateEncoder(){
    int MSB = digitalRead(main_encoder.pin_a);
    int LSB = digitalRead(main_encoder.pin_b);

    int encoded = (MSB << 1) | LSB;
    int sum = (main_encoder.lastEncoded << 2) | encoded;

    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) 
        main_encoder.value++;
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) 
        main_encoder.value--;

    main_encoder.lastEncoded = encoded;
}

void setupencoder(int pin_a, int pin_b){
    main_encoder.pin_a = pin_a;
    main_encoder.pin_b = pin_b;
    main_encoder.value = 0;
    main_encoder.lastEncoded = 0;

    pinMode(pin_a, INPUT);
    pinMode(pin_b, INPUT);
    pullUpDnControl(pin_a, PUD_UP);
    pullUpDnControl(pin_b, PUD_UP);
    wiringPiISR(pin_a,INT_EDGE_BOTH, updateEncoder);
    wiringPiISR(pin_b,INT_EDGE_BOTH, updateEncoder);

    /* TODO:
    Finish the read of the "Enter" button
    pinMode(pin_b, INPUT);
    pullUpDnControl(pin_a, PUD_UP);
    */
}

int main(int ac, char **av){

    wiringPiSetup();
    setupencoder(3,2);

    while(1){
        printf("Value = %ld           \r",main_encoder.value);
    }
}
