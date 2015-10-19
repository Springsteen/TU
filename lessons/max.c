#include "stdio.h"

int main (int argc, char const *argv[]) {

    int a, b, c;
    int max;
    char variable;

    printf("Изберете число за a\n");
    scanf("%d", &a);
    printf("Изберете число за b\n");
    scanf("%d", &b);
    printf("Изберете число за c\n");
    scanf("%d", &c);

    max = a;
    variable = 'a';
    if (b > max) {
        max = b;
        variable = 'b';
        if (c > max) {
            max = c;
            variable = 'c';
        }
    }

    printf("Най-голямото число е %c = %d\n", variable, max);

    return 0;
}
