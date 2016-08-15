#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <wiringPi.h>
#include <lcd.h>

#include <smart_lcd.h>
#include <smart_encoder.h>

void wtf(char *msg){
    printf("%s\n",msg);
}

void gtfo(char *msg){
    printf("%s\n",msg);
    exit(1);
}

char *pad(char *msg){
    int padsize = (LCD_COLS - strlen(msg))/2;
    char *result = (char *)malloc(LCD_COLS+1);

    if( result == NULL )
        gtfo("malloc failed in buttonOK()");

    memset(result, ' ', LCD_COLS);
    result[LCD_COLS] = '\0';
    memcpy(result+padsize,msg,strlen(msg));
    return result;
}

int buttonOK(char *msg){
    volatile int len = strlen(msg);
    char *okmsg = NULL;

    if( len <= 0 && len > LCD_COLS ){
        char error[256];
        sprintf(error,"buttonOK(): bad message, len = %d",len);
        gtfo(error);
    }

    okmsg = pad(msg);
    printf("-%s-",okmsg);
    free(okmsg);
    return 1;
}

int main(int ac, char *av[]){
    int lcdHandle = 0;

    return buttonOK("Zhopaa");

    wiringPiSetup();

    lcdHandle=lcdInit(
        LCD_ROWS,LCD_COLS,LCD_BITS,LCD_CLK,LCD_ENBL,
        LCD_BIT0,LCD_BIT1,LCD_BIT2,LCD_BIT3,0,0,0,0);

    if( lcdHandle < 0 )
        gtfo("Problem with lcdInit()");

    lcdPosition(lcdHandle,0,1);
    lcdPuts(lcdHandle,"Hello from Smart!");
    return 0;
}
