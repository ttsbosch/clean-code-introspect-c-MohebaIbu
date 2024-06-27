#ifndef IO_OPERATION_H
#define IO_OPERATION_H

#include "TradeRecord.h"

// Function prototypes
void write_trade_records_to_xml(const TR* objects, int objectCount, const char* filename);

#endif 
