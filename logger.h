#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

void log_info(const char* format, ...);
void log_warn(const char* format, ...);
void log_error(const char* format, ...);
void log_to_file(FILE* file, const char* format, ...);

#endif 
