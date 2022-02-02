#include <stdio.h>
#include "foo.h"

int main(int argc, char *argv[])
{
    printf("[begin]\nthis is main, first line is location\n");
    int i=0;
    for (i=0; i < argc; i++){
        printf("Argument %d:\t", i);
        foo(argv[i]);
    }

    printf("[end]\n");
    return 0;
}