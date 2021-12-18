#include "tsvparser.h"

#include <QFile>
#include <QTextStream>

TSVParser::TSVParser()
    : TXTParser('\t')
{

}

QString TSVParser::parseCell(const QString &cell) const
{
    return cell;
}

QString TSVParser::formatCell(const QString &content) const
{
    return content;
}


