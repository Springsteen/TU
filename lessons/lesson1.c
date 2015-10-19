#include "stdio.h"


int main (int argc, char const *argv[]) {

    int x = 0, y=0, z=0, d=1;
    d = x++ || --y && !z++ && x+y-z;

    printf("Haha %d %d %d %d \n",x , y, z, d);

    return 0;
}
