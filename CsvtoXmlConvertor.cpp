#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "TradeRecord.h"
#include "ErrorHandling.h"
#include "StringHelpers.h"
#include "logger.h"
#include "IO_Operation.h"



void convertCsvToXmlFile(FILE* csvfilestream) {
    char csvfileline[1024];
    TradeRecords records[1024];
    int lineCount = 0;
    int recordCount = 0;
    int LotSize = 100;
    while (fgets(csvfileline, sizeof(csvfileline), csvfilestream)) {
        char* csvFileFields[3];
        int csvFieldCount = 0;
        char* token = strtok(csvfileline, ",");
        while (token != NULL) {
            csvFileFields[csvFieldCount++] = token;
            token = strtok(NULL, ",");
        }

        performErrorChecks(csvFieldCount,lineCount ,ccsvFileFields)
        
        strncpy(records[recordCount].SrcCurrency, csvFileFields[0], 3);
        strncpy(records[recordCount].DestCurrency, csvFileFields[0] + 3, 3);
        records[recordCount].Lots = tradeAmount / LotSize;
        records[recordCount].Price = tradePrice;
        recordCount++;
        lineCount++;
    }

    write_trade_records_to_xml(records, recordCount, "output.xml");
}

