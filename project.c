#include "stdio.h"
#include "string.h"

#define FLUSH while (getchar() != '\n') // replaces fflush on linux

int searchThroughString (char *string, char *pattern);
int readFromFile (const char *finput, const char *foutput);
int readFromStdin (const char *foutput);
void writeResults (const char *fileout, int ifCount, int elseCount, int linesCount);

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
                int fileLength = strlen(argv[1]);
                if ( (argv[1][fileLength - 2] == '.') && ( (argv[1][fileLength - 1] == 'c') || (argv[1][fileLength - 1] == 'C') ) ) {
                    readFromFile(argv[1], argv[2]);
                } else {
                    printf("Въведете файл с разишернието на езика C\n");
                    return 0;
                }
            } else {
                printf("Не сте въвели файлове за четене и писане\n");
                return 0;
            }
            break;
        case 2:
            if (argc >= 2) {
                int fileLength = strlen(argv[1]);
                if ( (argv[1][fileLength - 2] == '.') && ( (argv[1][fileLength - 1] == 'c') || (argv[1][fileLength - 1] == 'C') ) ) {
                    readFromFile(argv[1], NULL);
                } else {
                    printf("Въведете файл с разишернието на езика C\n");
                    return 0;
                }
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
    int linesCount = 0;

    while ((charactersRead = getline(&line, &len, stdin)) != -1) {
        linesCount += 1;

        token = strtok(line, pattern);
        if (token != NULL) {
            while( token != NULL ) {
                if (strcmp(token, line) && searchThroughString(line, "/*")) {
                    inComment = 1;
                    break;
                } else if (strcmp(token, line) && searchThroughString(line, "*/")) {
                    inComment = 0;
                    break;
                }

                if (!inComment) {
                    ifCount += searchThroughString(token, "if");
                    elseCount += searchThroughString(token, "else");
                }
                token = strtok(NULL, pattern);
                if (token != NULL) inComment = !inComment ;
            }
        }
    }

    writeResults(foutput, ifCount, elseCount, linesCount - 1);

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
    int linesCount = 0;

    input = fopen(finput, "r");

    while ((charactersRead = getline(&line, &len, input)) != -1) {
        linesCount += 1;

        token = strtok(line, pattern);
        if (token != NULL) {
                printf("inComment: %d Token: %s\n", inComment, token);
                printf("Equal: %d\n", strcmp(token, line));
            while( token != NULL ) {
                if (strcmp(token, line) && searchThroughString(line, "/*")) {
                    inComment = 1;
                    break;
                } else if (strcmp(token, line) && searchThroughString(line, "*/")) {
                    inComment = 0;
                    break;
                }

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

    writeResults(foutput, ifCount, elseCount, linesCount);

    return 0;
}

void writeResults (const char *fileout, int ifCount, int elseCount, int linesCount) {
    if (fileout) {
        FILE *fp;
        fp = fopen(fileout, "w");

        fprintf(fp, "Брой редове %d\n", linesCount);
        fprintf(fp, "Брой if-ове %d\n", ifCount - elseCount);
        fprintf(fp, "Брой if/else-ове %d\n", elseCount);

        fclose(fp);
    } else {
        printf("Брой редове %d\n", linesCount);
        printf("Брой if-ове %d\n", ifCount - elseCount);
        printf("Брой if/else-ове %d\n", elseCount);
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
