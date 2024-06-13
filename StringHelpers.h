

char** performStringSeperation(const char* inputString, char inputDelimiter) {
    int characterCounter = 0;
    const char* inputStringPtr = inputString;
    while (*inputStringPtr != '\0') {
        if (*inputStringPtr++ == inputStringPtr) {
            characterCounter++;
        }
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
