#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct mi {
    char *label;
    int (*activate)(void);
} menuitem;

typedef struct m {
    char *banner;
    int nitems;
    int cursor;
    menuitem *items;
} menu;

void gtfo(char *msg){
    printf("%s\n",msg);
    exit(1);
}

menuitem *newItem(char *label, int(*action)(void)){
    menuitem *mitem = (menuitem *)malloc(sizeof(menuitem));
    if( mitem == NULL )
        return NULL;
    mitem->label = strdup(label);
    if( mitem->label == NULL )
        return NULL;
    mitem->activate = action;
    return mitem;
}

void destroyItem(menuitem *item){
    free(item->label);
    free(item);
}

menu *newMenu(char *banner, int nitems){
    menu *rm = (menu *)malloc(sizeof(menu));
    if( rm == NULL )
        return NULL;
    rm->banner = strdup(banner);
    if( rm->banner == NULL )
        return NULL;
    rm->items = (menuitem *)malloc(sizeof(menuitem *)*nitems);
    if( rm->items == NULL )
        return NULL;
    rm->nitems = nitems;
    rm->cursor = 0;
    return rm;
}

void destroyMenu(menu *dm){
    free(dm->banner);
    free(dm->items);
    free(dm);
}

void menu_down(menu *m){
    (m->cursor)--;
    if( m->cursor < 0 )
        m->cursor = (m->nitems - 1);
}

void menu_up(menu *m){
    (m->cursor)++;
    if( m->cursor >= m->nitems )
        m->cursor = 0;
}

void menu_execute(menu *m){
    (m->items[m->cursor]).activate();
}

int item1(){
    printf("This is item1\n");
    return 1;
}

int item2(){
    printf("This is item2\n");
    return 2;
}

int item3(){
    printf("This is item3\n");
    return 3;
}

int main(int ac, char *av[]){
    static struct termios origt,newt;
    volatile char c;

    printf("Welcome to the menu system\n");

    if( tcgetattr(STDIN_FILENO,&origt) < 0 )
        gtfo("tcgetattr failed!\n");

    newt = origt;

    if( tcsetattr(STDIN_FILENO, TCSANOW, &newt) < 0 ){
        tcsetattr(STDIN_FILENO, TCSANOW, &origt);
        gtfo("tcsetattr failed!\n");
    }

    menu *m1 = newMenu("Ultimate control",3);
    m1->items[0] = *newItem("Item 1", &item1);
    m1->items[1] = *newItem("Item 2", &item2);
    m1->items[2] = *newItem("Item 3", &item3);

// Do some useful shit
    while(1){
        c = getchar();
        if( c == 'q' )
            break;
        switch(c){
            case 'j':
                menu_down(m1);
                break;
            case 'k':
                menu_up(m1);
                break;
            case 'e':  // execute
                menu_execute(m1);
                break;
        }
    }
// Done with useful shit
    
    tcsetattr(STDIN_FILENO, TCSANOW, &origt);
    printf("We're done, bye!\n");
}
