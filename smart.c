#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <wiringPi.h>
#include <lcd.h>

void wtf(char *msg){
    printf("%s\n",msg)
}

void gtfo(char *msg){
    printf("%s\n",msg);
    exit(1);
}

int main(int ac, char *av[]){
    int lcdHandle = 0;

    wiringPiSetup();

    lcdHandle=lcdInit(
        LCD_ROWS,LCD_COLS,LCD_BITS,LCD_ENBL,LCD_CLK,
        LCD_BIT0,LCD_BIT1,LCD_BIT2,LCD_BIT3,0,0,0,0);

    if( lcdHandle < 0 )
        gtfo("Problem with lcdInit()");

    lcdPosition(lcdHandle,0,1);
    lcdPuts(lcdHandle,"Hello from Smart!");
    return 0;
}
