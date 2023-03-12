#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    struct passwd *pw;
    char* username;
    
    pw = getpwuid(getuid()); 
    username = pw->pw_name;

    printf("%s\n", username);

   return 0;
}
