#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "txtparser.h"

class CSVParser : public TXTParser
{
public:
    CSVParser();
    CSVParser(char delimiter);

    // TXTParser interface
private:
    QString parseCell(const QString &cell) const final;
    QString formatCell(const QString &content) const final;
};

#endif // CSVPARSER_H
