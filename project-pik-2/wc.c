#include <stdio.h>
#include <string.h>

int showBytes = 0;
/*
    -c, --bytes
    print the byte counts
*/

int showChars = 0;
/*
    -m, --chars
    print the character counts
*/

int showLines = 0;
/*
    -l, --lines
    print the newline counts
*/

int showMaxLineLength = 0;
/*
    -L, --max-line-length
    print the length of the longest line
*/

int showWords = 0;
/*
    -w, --words
    print the word counts
*/

int fromFiles = 0;
/*
    --files0-from=F
    read input from the files specified by NUL-terminated  names  in
    file F; If F is - then read names from standard input
*/

void parseArguments (int argc, char const *argv[]);
int countBytes (char* filename);
int countChars (char* filename);
int countLines (char* filename);
int countMaxLineLength (char* filename);
int countWords (char * filename);


int main (int argc, char const *argv[]) {

    parseArguments(argc, argv);

    printf("Bytes: %d\n", countBytes("wc.c"));
    printf("Lines: %d\n", countLines("wc.c"));
    printf("MaxLineLength: %d\n", countMaxLineLength("wc.c"));

    return 0;
}


void parseArguments (int argc, char const *argv[]) {
    // start from second argument, first is program name
    for (int i=1; i<argc; ++i) {
        // printf("%s\n", argv[i]);

        if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--bytes")) showBytes = 1;
        if (!strcmp(argv[i], "-m") || !strcmp(argv[i], "--chars")) showChars = 1;
        if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--lines")) showLines = 1;
        if (!strcmp(argv[i], "-L") || !strcmp(argv[i], "--max-line-length")) showMaxLineLength = 1;
        if (!strcmp(argv[i], "-w") || !strcmp(argv[i], "--words")) showWords = 1;
    }

    // printf("showBytes: %d\n", showBytes);
    // printf("showChars: %d\n", showChars);
    // printf("showLines: %d\n", showLines);
    // printf("showMaxLineLength: %d\n", showMaxLineLength);
    // printf("showWords: %d\n", showWords);
}


int countBytes (char* filename) {
    FILE* fp = fopen(filename, "rb");
    int bytes = 0;

    while (fgetc(fp) != EOF) bytes++;

    return bytes;
}


int countChars (char* filename) {
    return countBytes(filename); // the same ???
}


int countLines (char* filename) {
    FILE* fp = fopen(filename, "rb");
    int lines = 0;
    char read;

    while ((read = fgetc(fp)) != EOF) {
        if (read == '\n') lines++;
    }

    return lines;
}


int countMaxLineLength (char* filename) {
    FILE* fp = fopen(filename, "rb");
    int max = 0;
    int charsRead = 0;
    char read;

    while ((read = fgetc(fp)) != EOF) {
        if (read == '\n') {
            if (charsRead > max) max = charsRead;
            charsRead = 0;
            continue;
        }
        charsRead++;
    }

    return max;
}


int countWords (char * filename) {
    return 0;
}
