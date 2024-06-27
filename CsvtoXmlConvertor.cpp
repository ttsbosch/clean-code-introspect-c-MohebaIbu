#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "TradeRecord.h"
#include "DataTypeConvertor.h"
#include "StringHelpers.h"
#include "logger.h"


void write_trade_records_to_xml(const TradeRecords* objects, int objectCount, const char* filename) {
    FILE* outFile = fopen(filename, "w");
    if (outFile == NULL) {
        log_error("Failed to open output file");
        return;
    }

    log_to_file(outFile, "<TradeRecords>\n");
    for (int i = 0; i < objectCount; i++) {
        log_to_file(outFile, "\t<TradeRecord>\n");
        log_to_file(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", objects[i].SrcCurrency);
        log_to_file(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", objects[i].DestCurrency);
        log_to_file(outFile, "\t\t<Lots>%.2f</Lots>\n", objects[i].Lots);
        log_to_file(outFile, "\t\t<Price>%.2f</Price>\n", objects[i].Price);
        log_to_file(outFile, "\t</TradeRecord>\n");
    }
    log_to_file(outFile, "</TradeRecords>");
    fclose(outFile);
    log_info("%d trades processed and written to %s", objectCount, filename);
}

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

        if (csvFieldCount != 3) {
            fprintf(stderr, "WARN: Line %d malformed. Only %d field(s) found.\n", lineCount + 1, csvFieldCount);
            continue;
        }

        if (strlen(csvFileFields[0]) != 6) {
            fprintf(stderr, "WARN: Trade currencies on line %d malformed: '%s'\n", lineCount + 1, csvFileFields[0]);
            continue;
        }

        int tradeAmount;
        if (!tryToConvertStringToInt(csvFileFields[1], &tradeAmount)) {
            fprintf(stderr, "WARN: Trade amount on line %d not a valid integer: '%s'\n", lineCount + 1, csvFileFields[1]);
        }

        double tradePrice;
        if (!tryToConvertStringToDecimal(csvFileFields[2], &tradePrice)) {
            fprintf(stderr, "WARN: Trade price on line %d not a valid decimal: '%s'\n", lineCount + 1, csvFileFields[2]);
        }
        
        strncpy(records[recordCount].SrcCurrency, csvFileFields[0], 3);
        strncpy(records[recordCount].DestCurrency, csvFileFields[0] + 3, 3);
        records[recordCount].Lots = tradeAmount / LotSize;
        records[recordCount].Price = tradePrice;
        recordCount++;
        lineCount++;
    }

    write_trade_records_to_xml(records, recordCount, "output.xml");
}

