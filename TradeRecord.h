#ifndef TRADERECORD_H
#define TRADERECORD_H

typedef struct {
    char SrcCurrency[256]; 
    char DestCurrency[256]; 
    float Lots;
    double Price;
} TradeRecords;
