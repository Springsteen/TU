#include "stdio.h"
#include "string.h"

#define FLUSH while (getchar() != '\n') // replaces fflush on linux

int searchThroughString (char *string, char *pattern);
int readFromFile (const char *finput, const char *foutput);
int readFromStdin (const char *foutput);
void writeResults (const char *fileout, int ifCount, int elseCount, int charsCount);

int main (int argc, char const *argv[]) {

    int optionChoosen = 0, read = 0;

    while (1) {
        printf("Изберете начин на работа \n");
        printf("1 - Четене от файл, изход във файл \n");
        printf("2 - Четене от файл, изход на екрана \n");
        printf("3 - Четене от клавиатура, изход на екрана \n");
        printf("4 - Четене от клавиатура, във файл \n");

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

    switch (optionChoosen) {
        case 1:
            if (argc >= 3) {
                readFromFile(argv[1], argv[2]);
            } else {
                printf("Не сте въвели файлове за четене и писане\n");
                return 0;
            }
            break;
        case 2:
            if (argc >= 2) {
                readFromFile(argv[1], NULL);
            } else {
                printf("Не сте въвели файл за четене\n");
                return 0;
            }
            break;
        case 3:
            readFromStdin(NULL);
            break;
        case 4:
            if (argc >= 2) {
                readFromStdin(argv[1]);
            } else {
                printf("Не сте въвели файл за писане\n");
                return 0;
            }
            break;
    };

    return 0;
}

int readFromStdin (const char *foutput) {
    // input read vars
    char *line = NULL;
    size_t len = 0;
    ssize_t charactersRead;

    // comment vars
    const char pattern[3] = "/*";
    char *token;
    int inComment = 0;

    // result vars
    int ifCount = 0;
    int elseCount = 0;
    int charsCount = 0;

    while ((charactersRead = getline(&line, &len, stdin)) != -1) {
        charsCount += charactersRead;

        token = strtok(line, pattern);
        if (token != NULL) {
            while( token != NULL ) {
                if (!inComment) {
                    ifCount += searchThroughString(token, "if");
                    elseCount += searchThroughString(token, "else");
                }
                token = strtok(NULL, pattern);
                if (token != NULL) inComment = !inComment ;
            }
        }
    }

    writeResults(foutput, ifCount, elseCount, charsCount);

    return 0;
}

int readFromFile (const char *finput, const char *foutput) {
    if (!finput) {
        printf("Не сте въвели файл за четене\n");
        return 0;
    }

    FILE *input;

    // file read vars
    char *line = NULL;
    size_t len = 0;
    ssize_t charactersRead;

    // comment vars
    const char pattern[3] = "/*";
    char *token;
    int inComment = 0;

    // result vars
    int ifCount = 0;
    int elseCount = 0;
    int charsCount = 0;

    input = fopen(finput, "r");

    while ((charactersRead = getline(&line, &len, input)) != -1) {
        charsCount += charactersRead;

        token = strtok(line, pattern);
        if (token != NULL) {
            while( token != NULL ) {
                if (!inComment) {
                    ifCount += searchThroughString(token, "if");
                    elseCount += searchThroughString(token, "else");
                }
                token = strtok(NULL, pattern);
                if (token != NULL) inComment = !inComment ;
            }
        }
    }

    fclose(input);

    writeResults(foutput, ifCount, elseCount, charsCount);

    return 0;
}

void writeResults (const char *fileout, int ifCount, int elseCount, int charsCount) {
    if (fileout) {
        FILE *fp;
        fp = fopen(fileout, "w");

        fprintf(fp, "Брой символи %d\n", charsCount);
        fprintf(fp, "Брой if-ове %d\n", ifCount);
        fprintf(fp, "Брой else-ове %d\n", elseCount);

        fclose(fp);
    } else {
        printf("Брой символи %d\n", charsCount);
        printf("Брой if-ове %d\n", ifCount);
        printf("Брой else-ове %d\n", elseCount);
    }
}


int searchThroughString (char *string, char *pattern) {
    int count = 0;
    int length = strlen(pattern);

    if (!length) return 0;

    for (string = strstr(string, pattern); string; string = strstr(string + length, pattern))
        ++count;

    return count;
}
