#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

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

char** files;
int filesCount = 0;

void parseArguments (int argc, char const *argv[]);
int countBytes (char* filename);
int countChars (char* filename);
int countLines (char* filename);
int countMaxLineLength (char* filename);
int countWords (char * filename);

/* helper functions */
int fileExists(const char* filename);
void printOutput(int lines, int words, int bytes, int maxLine, char* file);
void printBinaryOutput(int lines, int words, int bytes, int maxLine, char* file);

// char* buildStandardRepresentation(char* filename);

int main (int argc, char const *argv[]) {

    parseArguments(argc, argv);

    int totalLines = 0;
    int totalWords = 0;
    int totalBytes = 0;
    // int totalChars = 0;
    int maxLine = 0;

    for (int i=0; i<filesCount;++i) {
        int lines = countLines(files[i]);
        int words = countWords(files[i]);
        int bytes = countBytes(files[i]);
        int currMaxLine = countMaxLineLength(files[i]);

        totalLines += lines;
        totalWords += words;
        totalBytes += bytes;
        if (currMaxLine > maxLine) maxLine = currMaxLine;

        printOutput(lines, words, bytes, currMaxLine, files[i]);
        printBinaryOutput(totalLines, totalWords, totalBytes, maxLine, "total");
    }
    printOutput(totalLines, totalWords, totalBytes, maxLine, "total");
    printBinaryOutput(totalLines, totalWords, totalBytes, maxLine, "total");

    return 0;
}

void printOutput(int lines, int words, int bytes, int maxLine, char* file) {
    if (!showBytes &&!showChars && !showLines && !showMaxLineLength && !showWords) {
        printf("%d %d %d %s\n", lines, words, bytes, file);
    } else {
        if (showBytes) printf("%d ", bytes);
        if (showChars) printf("%d ", bytes);
        if (showLines) printf("%d ", lines);
        if (showMaxLineLength) printf("%d ", maxLine);
        if (showWords) printf("%d ", words);
        printf("%s\n", file);
    }
}

void printBinaryOutput(int lines, int words, int bytes, int maxLine, char* file) {
    if (!showBytes &&!showChars && !showLines && !showMaxLineLength && !showWords) {
        printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(lines));
        printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(words));
        printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(bytes));

    } else {
        if (showBytes) printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(bytes));
        if (showChars) printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(bytes));
        if (showLines) printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(lines));
        if (showMaxLineLength) printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(maxLine));
        if (showWords) printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(words));
    }
    for (int i = 0; i < strlen(file); ++i) {
        printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(file[i]));
    }
    printf("\n");
}

void parseArguments (int argc, char const *argv[]) {
    // start from second argument, first is program name
    for (int i=1; i<argc; ++i) {
        if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--bytes")) {
            showBytes = 1;
        } else if (!strcmp(argv[i], "-m") || !strcmp(argv[i], "--chars")) {
            showChars = 1;
        } else if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--lines")) {
            showLines = 1;
        } else if (!strcmp(argv[i], "-L") || !strcmp(argv[i], "--max-line-length")) {
            showMaxLineLength = 1;
        } else if (!strcmp(argv[i], "-w") || !strcmp(argv[i], "--words")) {
            showWords = 1;
        } else if (fileExists(argv[i])) {
            files = realloc(files, ++filesCount * sizeof(char*));
            files[filesCount-1] = (char*) malloc(strlen(argv[i]) * sizeof(char));
            strcpy(files[filesCount-1], argv[i]);
        } else {
            printf("wc: unrecognized option '%s'\n", argv[i]);
            exit(1);
        }
    }
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
    FILE * fp = fopen(filename, "rb");
    int count = 1;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == ' ') count++;
    }
    return count;
}


int fileExists (const char* filename) {
    return (access(filename, F_OK) != -1);
}
