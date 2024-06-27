#include "IO_Operation.h"
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
