#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

void convertCsvToXmlFile(FILE* csvfilestream) {
    char csvfileline[1024];
    TradeRecords records[1024];
    int lineCount = 0;
    int recordCount = 0;

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

    FILE* outputXmlFile = fopen("output.xml", "w");
    fprintf(outputXmlFile, "<TradeRecords>\n");
    for (int recordIndex = 0; recordIndex < recordCount; recordIndex++) {
        fprintf(outputXmlFile, "\t<TradeRecord>\n");
        fprintf(outputXmlFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", records[recordIndex].SrcCurrency);
        fprintf(outputXmlFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", records[recordIndex].DestCurrency);
        fprintf(outputXmlFile, "\t\t<Lots>%d</Lots>\n", records[recordIndex].Lots);
        fprintf(outputXmlFile, "\t\t<Price>%f</Price>\n", records[recordIndex].Price);
        fprintf(outputXmlFile, "\t</TradeRecord>\n");
    }
    fprintf(outputXmlFile, "</TradeRecords>");
    fclose(outputXmlFile);
    printf("INFO: %d trades processed\n", recordCount);
}

