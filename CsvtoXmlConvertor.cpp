#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include "DataTypeConvertor.h"
#include "logger.h"
#include "TradeRecord.h"
#include "StringHelpers.h"
#include "IO_Operation.h"

void  checkFieldCountAsSpecified (int csvFieldCount,int lineCount,int refCountValue)
{
  if (csvFieldCount != refCountValue) {
            log_warn(stderr, "WARN: Line %d malformed. Only %d field(s) found.\n", lineCount + 1, csvFieldCount);
            
        }
}

void  checkLengthOfieldsAsSpecified (char *csvFileFields[3],int lineCount,int refFieldLength)
{
   if (strlen(csvFileFields[0]) != refFieldLength) {
            log_warn(stderr, "WARN: Trade currencies on line %d malformed: '%s'\n", lineCount + 1, csvFileFields[0]);
            
        }
}

void  checkGivenVaribleIsInt (char *csvFileFields[3],int lineCount)
{
  int tradeAmount;
  if (!tryToConvertStringToInt(csvFileFields[1], &tradeAmount)) {
      log_warn(stderr, "WARN: Trade amount on line %d not a valid integer: '%s'\n", lineCount + 1, csvFileFields[1]);
    }
}

void  checkGivenVaraibleIsDouble (char *csvFileFields[3],int lineCount)
{
  double tradePrice;
  if (!tryToConvertStringToDecimal(csvFileFields[2], &tradePrice)) 
  {
    log_warn(stderr, "WARN: Trade price on line %d not a valid decimal: '%s'\n", lineCount + 1, csvFileFields[2]);
  }
}

void performErrorChecks(int csvFieldCount,int lineCount ,char *csvFileFields[3] )
{
  checkFieldCountAsSpecified(csvFieldCount,lineCount,3);
  checkLengthOfieldsAsSpecified(csvFileFields,lineCount,6);
  checkGivenVaribleIsInt(csvFileFields,lineCount);
  checkGivenVaraibleIsDouble(csvFileFields,lineCount);
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

