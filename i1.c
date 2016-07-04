// #include <wiringPi.h>
#define LEFT 0
#define CENTER 1
#define RIGHT 2

#define COLUMNS 20
#define ROWS    4

#include <stdio.h>
#include <string.h>

typedef struct mtext {
    int numlines;
    int alignment;
    char **text;
} menutext;

void OKbutton(menutext txt){
    volatile int i,j;
    volatile int pad;

    for(i=0; i<txt.numlines; i++){
        pad = (COLUMNS - strlen(txt.text[i]))/2;
        for(j=0; j<pad; j++) printf(" ");
        printf("%s",txt.text[i]);
        for(j=0; j<pad; j++) printf(" ");
        printf("\n");
    }
}

int main(int ac, char *av[]){
//    wiringPiSetup();
    const char *lines[] = { "Line 1","Line 422" };
    menutext OK1;

    OK1.numlines = 2;
    OK1.alignment = CENTER,
    OK1.text = lines;

    OKbutton(OK1);
}
