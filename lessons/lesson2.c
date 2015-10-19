#include "stdio.h"
#include "math.h"

int main (int argc, char const *argv[]) {
    int a, b, c;

    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    if ( (a != 0) && (b != 0) ){
        if (a != 0) {
            if (c != 0) {
                int x1, x2;
                int d = pow(b, 2) - 4*a*c;

                if (d > 0) {
                    x1 = (-b - sqrt(d)) / 2*a;
                    x2 = (-b + sqrt(d)) / 2*a;
                    printf("x1 = %d, x2 = %d\n", x1, x2);
                } else if (d == 0) {
                    printf("Два еднакви корени %d\n", (-b/2*a));
                } else {
                    printf("Няма реални корени\n");
                }
            } else {
                printf(" х1 = %d, x2 = 0\n", (-b/a) );
            }
        } else {
            printf( "Един корен %d\n", (-c/b) );
        }
    } else {
        printf("Изродено\n");
    }

    return 0;
};
