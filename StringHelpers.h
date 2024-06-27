#ifndef STRINGHELPERS_H
#define STRINGHELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char** performStringSeperation(const char* inputString, char inputDelimiter) {
    int characterCounter = 0;
    const char* inputStringPtr = inputString;
    while (*inputStringPtr != '\0') {
        if (*inputStringPtr == inputDelimiter) {
            characterCounter++;
        }
        inputStringPtr++;
    }

    char** seperatedString = (char**)malloc(sizeof(char*) * (characterCounter + 2));
    int i = 0;
    inputStringPtr = inputString;
    char* token = (char*)malloc(strlen(inputString) + 1);
    int j = 0;
    while (*inputStringPtr != '\0') {
        if (*inputStringPtr == inputDelimiter) {
            token[j] = '\0';
            seperatedString[i++] = strdup(token);
            j = 0;
        } else {
            token[j++] = *inputStringPtr;
        }
        inputStringPtr++;
    }
    token[j] = '\0';
    seperatedString[i++] = strdup(token);
    seperatedString[i] = NULL;
    free(token);
    return seperatedString;
}
#endif // STRINGHELPERS_H
