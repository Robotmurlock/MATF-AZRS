#ifndef TSVPARSER_H
#define TSVPARSER_H

#include "txtparser.h"

class TSVParser : public TXTParser
{
public:
    TSVParser();

    // TXTParser interface
private:
    QString parseCell(const QString &cell) const override;
    QString formatCell(const QString &content) const override;
};

#endif // TSVPARSER_H
