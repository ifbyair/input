#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <lcd.h>

#ifndef TRUE
#  define   TRUE    (1==1)
#  define   FALSE   (1==2)
#endif

static int lcdHandle;

int main(int ac, char *av[]){
    wiringPiSetup();

    lcdHandle = lcdInit(4,20,4,11,10,4,5,6,7,0,0,0,0);

    if( lcdHandle < 0 ){
        printf("Problem with lcdInit\n");
        exit(0);
    }

    lcdPosition(lcdHandle,1,1);
    lcdPuts (lcdHandle,"Howdy, man!");
    return 1;
}
