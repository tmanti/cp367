#include <fcntl.h> // open
#include <unistd.h> // read
#include <sys/types.h> // read
#include <sys/uio.h> // read
#include <stdio.h> // fopen, fread
#include <stdlib.h>
#include <sys/time.h> // gettimeofday
#include <string.h>

ssize_t read(int fd, void *buf, size_t count);
int close(int fd); 

struct timeval start, end; // maintain starting and finishing wall time.

void startTimer( ) { // memorize the starting time
    gettimeofday( &start, NULL );
}

void stopTimer( char *str ) { // checking the finishing time and computes the elapsed time
    gettimeofday( &end, NULL );
    printf("%s's elapsed time\t= %ld\n",str, ( end.tv_sec - start.tv_sec ) * 1000000 + (end.tv_usec - start.tv_usec));
}

int main( int argc, char *argv[] ) {
    int typeofcalls;
    // validate arguments
    // implementation
    if(argc != 4){
        fprintf(stderr, "usage: %s filename bytes typeofcalls\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Parsing the arguments passed to your C program
    // Including the number of bytes to read per read( ) or fread( ), and
    // the type of i/o calls used
    // implementation
    char *file_name = argv[1];

    int bytes = atoi(argv[2]);
    if(bytes == 0 && strcmp(argv[2], "0")!=0){
        fprintf(stderr, "usage: %s filename bytes typeofcalls\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    typeofcalls = atoi(argv[3]);
    if(typeofcalls == 0 && strcmp(argv[3], "0")!=0){
        fprintf(stderr, "usage: %s filename bytes typeofcalls\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (typeofcalls == 1) {
        // Use unix I/O system calls to
        // implementation

        int fd = open(file_name, O_RDONLY);
        if(fd == -1){
            fprintf(stderr, "filename of: %s, not found", file_name);
            exit(EXIT_FAILURE);
        }
        
        char *buf = malloc(bytes);

        startTimer();

        int file_read = 0;

        while(1){
            if(!read(fd, buf, bytes)){
                break;
            }
        }

        printf("Using Unix I/O system calls to read a file by %i bytes per read\n", bytes);
        stopTimer("Unix reads");

        close(fd);
    } else if (typeofcalls == 0) {
        // Use standard I/O
        // implementation
        // if bytes == 1 then use fgetc else fread

        FILE *fd = fopen(file_name, "r");
        if(fd == NULL){
            fprintf(stderr, "filename of: %s, not found", file_name);
            exit(EXIT_FAILURE);
        }

        char c;
        char *buf = malloc(bytes);

        startTimer();

        if(bytes == 1){
            do{
                c = fgetc(fd);
                if(feof(fd)){
                    break;
                }
            }while(1);
        } else {                            
            while(1){
                if(!fread(buf, bytes, 1, fd)){
                    break;
                }
            }
        }
        
        printf("Using C functions to read a file by %i bytes per fread\n", bytes);
        stopTimer("C fread");
        
        fclose(fd);

    } else {
        fprintf(stderr, "usage: %s filename bytes typeofcalls\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}