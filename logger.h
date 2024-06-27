#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

void log_info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf("INFO: ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

void log_warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "WARN: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void log_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "ERROR: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void log_to_file(FILE* file, const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(file, format, args);
    va_end(args);
}

#endif 
