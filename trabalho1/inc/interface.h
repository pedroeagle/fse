#ifndef INTERFACE_H_
#define INTERFACE_H_

#define ITERMAX 10000

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
void INTERFACE();
typedef struct menu{
    int start_x;
    char string_text[1000];
    char trigger;
} Menu;

typedef struct menu_bar{
    WINDOW *win;
    Menu *menus;
    int num_menus;
} Menu_bar;

#endif   