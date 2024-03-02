#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <sys/select.h>
#include <string.h> 
#include <semaphore.h>
#include <sys/mman.h>
#include <signal.h>
#include "library/win.h"

#define DEBUG 1


int main (int argc, char* argv[])
{
    // WINDOW *external_window;
    // WINDOW *printing_window;
    WINDOW *arrw[NUMWINDOWS]; // change numwindows in library
    char ch;
    int i, index = 0;
    int fdMaster;
    // change with the new windows.c and the new functiones
    
    int nrows, ncols;
    int h,w;
  
    initscr(); // start curses mode
    raw();
    noecho();
    start_color();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, h, w);
    refresh();

    sscanf(argv[1], "%d", &fdMaster);
    
    // Windows initialization
    //init_windows(Srow, Scol, &external_window, &printing_window,&PRy,&PRx,&Startx,&Starty,&Wcol,&Wrow);

    refresh();    
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    squareCreation(arrw,h,w, &nrows,&ncols);
    printw("Description of the game: \n");
    // printw("\nThis game is a simple game of a drone control, where the user can press \nthis buttons to drive the robot to avoid the obstacles and reach the targets.\n");
    // wrefresh(external_window);
    refresh();
    // wrefresh(printing_window);

    for (int i = 0; i < NUMWINDOWS; i++){
        switch (i)
        {
            case BTTW:
                print_btt_windows(arrw[i], 'w');
                break;
            case BTTE:
                print_btt_windows(arrw[i], 'e');
                break;
            case BTTR:  
                print_btt_windows(arrw[i], 'r');
                break;
            case BTTS:
                print_btt_windows(arrw[i], 's');
                break;
            case BTTD:
                print_btt_windows(arrw[i], 'd');
                break;
            case BTTF:
                print_btt_windows(arrw[i], 'f');
                break;
            case BTTX:
                print_btt_windows(arrw[i], 'x');
                break;
            case BTTC:
                print_btt_windows(arrw[i], 'c');
                break;
            case BTTV:
                print_btt_windows(arrw[i], 'v');
                break;
            case BTTQ:
                // print_btt_windows(arrw[i], 'Q');
                break;
            case BTTB:
                // print_btt_windows(arrw[i], 'B');
                break;
            default:
                printf("Error in the switch case\n");
                break;
        }
    }

    printw("Press i to play the game in online giving the input\n");
    printw("Press t to play the game in online generating targets e obstacles\n");
    printw("Press q to exit\n");
    printw("Press any other key to start the game n local mode\n");
    sleep (2);
    refresh();
    ch = getch();
    if ((write(fdMaster, &ch, sizeof(char))) < 0){
        perror("Error writing to pipe");
        exit(EXIT_FAILURE);
    }
    printw("Enjoy");
    refresh();
    for (i = 0; i < NUMWINDOWS; i++)
    {
        destroy_win(arrw[i]);
    }
    endwin();
    close(fdMaster);

    return 0;
}
    
