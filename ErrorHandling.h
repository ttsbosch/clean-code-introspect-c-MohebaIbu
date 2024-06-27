#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H
#include "DataTypeConvertor.h"
#include "logger.h"
#define true 1
#define false 0
typedef int bool;


void performErrorChecks(int csvFieldCount,int lineCount ,char *csvFileFields[3] )
{
  checkFieldCountAsSpecified(csvFieldCount,lineCount,3);
  checkLengthOfieldsAsSpecified(csvFileFields,lineCount,6);
  checkGivenVaribleIsInt(csvFileFields,lineCount);
  checkGivenVaraibleIsDouble(csvFileFields,lineCount);
}

void  checkFieldCountAsSpecified (int csvFieldCount,int lineCount,int refCountValue)
{
  if (csvFieldCount != refCountValue) {
            log_warn(stderr, "WARN: Line %d malformed. Only %d field(s) found.\n", lineCount + 1, csvFieldCount);
            continue;
        }
}

void  checkLengthOfieldsAsSpecified (char *csvFileFields[3],int lineCount,refFieldLength)
{
   if (strlen(csvFileFields[0]) != refFieldLength) {
            log_warn(stderr, "WARN: Trade currencies on line %d malformed: '%s'\n", lineCount + 1, csvFileFields[0]);
            continue;
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




#endif 
