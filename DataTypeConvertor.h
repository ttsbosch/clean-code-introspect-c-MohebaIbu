#ifndef DATATYPECONVERTOR_H
#define DATATYPECONVERTOR_H


int tryToConvertStringToInt(const char* inputString, int* integerValue) {
    char* endptr;
    *integerValue = strtol(inputString, &endptr, 10);
    if (endptr == inputString) {
        return 0;
    }
    return 1;
}

int tryToConvertStringToDecimal(const char* inputString, double* decimalValue) {
    char* endptr;
    *decimalValue = strtod(inputString, &endptr);
    if (endptr == inputString) {
        return 0;
    }
    return 1;
}
#endif // DATATYPECONVERTOR_H
