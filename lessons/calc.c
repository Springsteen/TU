#include "stdio.h"

int main (int argc, char const *argv[]) {

    int a, b;
    char action;

    printf("Изберете число за a\n");
    scanf("%d", &a);
    printf("Изберете число за b\n");
    scanf("%d", &b);
    printf("Изберете действие\n");
    scanf(" %c", &action);

    printf("%d %c %d\n", a, action, b);

    switch (action) {
        case '+':
            printf("Резултатът е %d\n", a + b);
            break;
        case '-':
            printf("Резултатът е %d\n", a - b);
            break;
        case '/':
            printf("Резултатът е %d\n", a / b);
            break;
        case '*':
            printf("Резултатът е %d\n", a * b);
            break;
    };

    return 0;
}
