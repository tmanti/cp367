#include <curses.h> // display libary (make sure to -lcurses)
#include <time.h> // gettimeofday and seeding rand
#include <sys/time.h>
#include <stdlib.h> // for rand
#include <string.h>

int main(){

    //init curses libary
    initscr();
    cbreak();
    noecho();

    //seed random number generator
    srand(time(NULL));
    //int random_number = rand() % range + min;
    
    int test_count = 0;

    double min_spd=1e6, max_spd=-1e6;
    double resp_spd[10];

    char ch, target;

    int delay;

    //Get screen dimensions
    int y,x;
    getmaxyx(stdscr, y, x);

    while(test_count < 10){
        int tar_num = rand()%36;
        delay = rand() % 3 + 1;

        clear();
        mvprintw(y/2, (x-6)/2, "TEST %i", test_count+1); //IT HAS BEEN CENTERED, "6" is just the length of "TEST #"
        refresh();
        napms(delay*1000);

        if(tar_num < 10){
            target = tar_num + '0';
        } else {
            target = 'a' + tar_num - 10;
        }

        struct timeval start, end;

        clear(); //Clear screen before char is placed
        mvprintw((rand() % y), (rand() % x), "%c", target); // places the char at a random place on screen
        refresh();
        gettimeofday( &start, NULL );
        //get wait for correct char
        while(1){
            ch = getch();

            if(ch == target){
                break;
            }
        }
        gettimeofday( &end, NULL );

        long seconds = end.tv_sec - start.tv_sec;
        long microseconds = end.tv_usec - start.tv_usec;
        double elapsed = seconds + microseconds*1e-6;

        resp_spd[test_count] = elapsed;

        if(elapsed > max_spd){
            max_spd = elapsed;
        }

        if(elapsed < min_spd){
            min_spd = elapsed;
        }

        //increase count 
        test_count++;
    }

    // Clean up the curses library
    endwin();

    //all elapsed, min, max, average
    double sum = 0;
    for(int i = 0; i < 10; i++){
        printf("%2d.\t %.4f \n", i+1, resp_spd[i]);
        sum += resp_spd[i];
    }

    printf("max: %.4f min: %.4f avg: %.4f \n", max_spd, min_spd, sum/10);

    return 0;
}