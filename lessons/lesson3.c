#include "stdio.h"

int main (int argc, char const *argv[]) {

    int begin = 0, end = 0, read = 0;

    while (42) {
        read = scanf("%d", &begin);

        if (read) break;
    };

    while (42) {
        read = scanf("%d", &end);

        if (read && (end > begin)) break;
    };

    int numIter = 0;

    while (42) {
        read = scanf("%d", &numIter);

        if (read && (numIter > begin) && (numIter < end)) break;
    };

    int num = 0, sum = 0;

    for (int i = 0; i < numIter; ++i) {
        read = scanf("%d", &num);
        if (read) {
            sum += num;
            continue;
        }

        printf("Грешен вход\n");
        return 0;
    }

    printf("%d\n", sum);

    return 0;
}
