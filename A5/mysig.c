#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void f(int);

int main (){
  
  int i;

  signal(SIGINT,f);
  for (i=0;i<5;i++){
    printf("hello\n");
    sleep(1);
  }
  
}

void handle_password(){
    char* password = "Laurier";
    
    while(1){
        char* written_pass = getpass("Please enter the password: ");
        if(strcmp(password, written_pass) == 0){
            break;
        } else {
            printf("You have entered an invalid password!\n");
        }
    }

    printf("exit\n");
    exit(0);
}

void f(int signum){
  char c;
  while(1){
    printf(" Interrupted! OK to quit (y/n)? ");
    c = getchar();
    if(c == 'y' || c == 'Y'){
        handle_password();
    } else {
        break;  
    }
  }
}