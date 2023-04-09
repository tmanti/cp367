#include <curses.h> // display libary (make sure to -lcurses)
#include <time.h> // gettimeofday and seeding rand
#include <sys/time.h>
#include <stdlib.h> // for rand

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

    while(test_count < 10){
        int tar_num = rand()%36;
        delay = rand() % 3 + 1;

        clear();

        printw("TEST " + test_count+1); //maybe center
        refresh();
        napms(delay*1000);

        if(tar_num < 10){
            target = tar_num + '0';
        } else {
            target = 'a' + tar_num - 10;
        }

        struct timeval start, end;

        //printw(); // - put the char at a random point on the screen 
        refresh();

        gettimeofday( &start, NULL );
        //get wait for correct char
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

    //all elapsed, min, max, average
    double sum = 0;
    for(int i = 0; i < 10; i++){
        printf("%d. %.4f", i, resp_spd[i]);
        sum = resp_spd[i];
    }

    printf("max %.4f min %.4f avg %.4f", max_spd, min_spd, sum/10);

    // Clean up the curses library
    endwin();

    return 0;
}