#include "stdio.h"

#define FLUSH while (getchar() != '\n') // replaces fflush on linux


int main (int argc, char const *argv[]) {

    int optionChoosen = 0, read = 0;

    printf("Изберете начин на работа \n");
    printf("1 - Четене от файл, изход във файл \n");
    printf("2 - Четене от файл, изход на екрана \n");
    printf("3 - Четене от клавиатура, изход на екрана \n");
    printf("4 - Четене от клавиатура, във файл \n");

    while (1) {
        read = scanf("%d", &optionChoosen);

        if (read > 0) {
            if ((optionChoosen > 0) && (optionChoosen < 5)) {
                printf("Вие избрахте опция %d\n", optionChoosen);
                break;
            } else {
                printf("Няма такава опция\n");
            }
        } else {
            printf("Неправилен вход\n");
        }

        FLUSH;
    }

    return 0;
}
