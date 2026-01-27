#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int number_letters(char *buffer, size_t strlength);
int number_words(char *buffer, size_t strlength);
int number_sentences(char *buffer, size_t strlength);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Argument required");
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "File not found");
        return 1;
    }
    fseek(in, 0, SEEK_END);
    long size = ftell(in);
    rewind(in);

    char *buffer = malloc(size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "ALlocation failed");
        fclose(in);
        return 1;
    }
    size_t n = fread(buffer, 1, size, in);

    while (n > 0 && buffer[n - 1] == '\n') {
        n--;
    }
    buffer[n] = '\0';
    size_t strlength = strlen(buffer);
    fclose(in);

    int nletters = number_letters(buffer, strlength);
    int nwords = number_words(buffer, strlength);
    int nsentences = number_sentences(buffer, strlength);

    // int index = round(0.0588 * nletters * 100 / nwords - 0.296 * nsentences * 100 / nwords - 15.8);

    free(buffer);
    return 0;
}

int number_letters(char *buffer, size_t strlength) {
    int letters = 0;
    for (size_t i = 0; i < strlength; i++) {
        if (isalpha(buffer[i])) {
            letters++;
        }
    }
    return letters;
}

int number_words(char *buffer, size_t strlength) {
    int words = 1;
    for (size_t i = 0; i < strlength; i++) {
        if (isblank(buffer[i])) {
            words++;
        }
    }
    return words;
}

int number_sentences(char *buffer, size_t strlength) {
    int sentences = 0;
    for (size_t i = 0; i < strlength; i++) {
        if (buffer[i] == '!' || buffer[i] == '?' || buffer[i] == '.') {
            sentences++;
        }
    }
    return sentences;
}
