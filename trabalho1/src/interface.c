#include "interface.h"
#define FIRST 5
#define SECOND 13
#define THIRD 21

int yMax, xMax;

Menu set_menu(const char * text, char trigger){
    Menu menu;
    strcpy(menu.string_text, text);
    menu.trigger = trigger;
}
Menu_bar set_menu_bar(WINDOW *win, Menu *menus, int num_menus){
    Menu_bar menu_bar;
    menu_bar.win = win;
    menu_bar.menus = menus;
    menu_bar.num_menus = num_menus;
}
void draw(){
    
}
void INTERFACE(){
    initscr();
    noecho();
    curs_set(0);
    
    WINDOW *win = newwin(yMax/2, xMax/2, yMax/4, xMax/4);
    getmaxyx(win, yMax, xMax);
    Menu menus[3] = {
        set_menu("Monitor", 'm'),
        set_menu("Control", 'c'),
        set_menu("About", 'a')
    };
    Menu_bar menubar = set_menu_bar(win, menus, 3);
    box(win, 0, 0);
    mvwprintw(win, 0, FIRST, "Monitor");
    mvwprintw(win, 0, SECOND, "Control");
    mvwprintw(win, 0, THIRD, "About");

    char ch;
    while(ch = wgetch(win)){
        switch(ch){
            case 'm':
                wattron(win, A_STANDOUT);
                mvwprintw(win, 0, FIRST, "Monitor");
                wattroff(win, A_STANDOUT);
                mvwprintw(win, 0, SECOND, "Control");
                mvwprintw(win, 0, THIRD, "About");
                break;
            case 'c':
                wattron(win, A_STANDOUT);
                mvwprintw(win, 0, SECOND, "Control");
                wattroff(win, A_STANDOUT);
                mvwprintw(win, 0, FIRST, "Monitor");
                mvwprintw(win, 0, THIRD, "About");
                break;
            case 'a':
                wattron(win, A_STANDOUT);
                mvwprintw(win, 0, THIRD, "About");
                wattroff(win, A_STANDOUT);
                mvwprintw(win, 0, FIRST, "Monitor");
                mvwprintw(win, 0, SECOND, "Control");
                break;
            default:
                mvwprintw(win, 0, FIRST, "Monitor");
                mvwprintw(win, 0, SECOND, "Control");
                mvwprintw(win, 0, THIRD, "About");

                
        }
    }
    endwin();
}
