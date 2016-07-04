#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct mi {
    char *label;
    int (*activate)(void);
} menuitem;

typedef struct m {
    char *header;
    int nitems;
    menuitem *items;
} menu;

int item1(){
    printf("This is item 1\n");
    return 1;
}

int item2(){
    printf("This is item 2\n");
    return 2;
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

menu *newMenu(char *header, int nitems){
    menu *rm = (menu *)malloc(sizeof(menu));
    if( rm == NULL )
        return NULL;
    rm->header = strdup(header);
    if( rm->header == NULL )
        return NULL;
    rm->items = (menuitem *)malloc(sizeof(menuitem *)*nitems);
    if( rm->items == NULL )
        return NULL;
    rm->nitems = nitems;
    return rm;
}

void destroyMenu(menu *dm){
    free(dm->header);
    free(dm->items);
    free(dm);
}

void wtf(char *msg){
    printf("*** %s ***\n",msg);
}

void gtfo(char *msg){
    printf("*** %s ***\n",msg);
    exit(1);
}

void menuBrowse(menu *m){
    volatile int i;
    menuitem *cursor = m->items;

    printf("Browsing menu %s\n",m->header);

    for(i=0; i < m->nitems; i++){
        printf("Item - %s\n",m->items[i].label);
        m->items[i].activate();
    } 
}

int main(int ac, char *av[]){
    printf("Welcome to inputs\n\n");

    menu *m1 = newMenu("First menu",2);
    if( m1 == NULL )
        gtfo("Menu malloc failed");

    m1->items[0] = *newItem("Item 1", &item1);
    m1->items[1] = *newItem("Item 2", &item2);

//    if( (m1->items[0] == NULL) || (m1->items[1] == NULL) )
//        gtfo("Malloc failed!");

    menuBrowse(m1);
    destroyMenu(m1);
}
