//rotaryencoder.c
#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "smart_encoder.h"

rotaryEncoder encoder;

void updateEncoder(){
    int MSB = digitalRead(encoder.pin_a);
    int LSB = digitalRead(encoder.pin_b);

    int encoded = (MSB << 1) | LSB;
    int sum = (enc->lastEncoded << 2) | encoded;

    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) 
        encoder.value++;
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) 
        encoder.value--;

    encoder.lastEncoded = encoded;
}

void execEncoder(){
    static long lastValue = 0;
    printf("\nEnter!\n");
}

void setupencoder(int pin_a,int pin_b,int pin_exec){
    enc.pin_a = pin_a;
    enc.pin_b = pin_b;
    enc.value = 0;
    enc.lastEncoded = 0;

    pinMode(pin_a, INPUT);
    pinMode(pin_b, INPUT);
    pullUpDnControl(pin_a, PUD_UP);
    pullUpDnControl(pin_b, PUD_UP);
    wiringPiISR(pin_a,INT_EDGE_BOTH, updateEncoder);
    wiringPiISR(pin_b,INT_EDGE_BOTH, updateEncoder);

    /* TODO:
    Finish the read of the "Enter" button
    */
    pinMode(pin_exec, INPUT);
    wiringPiISR(pin_exec,INT_EDGE_FALLING, execEncoder);
    /*
    pullUpDnControl(pin_a, PUD_UP);
    */
}

int main(int ac, char **av){

    wiringPiSetup();
    setupencoder(3,2,0);

    while(1){
        printf("Value = %ld           \r",encoder.value);
    }
}
