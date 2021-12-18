#include "csvparser.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

CSVParser::CSVParser()
    : TXTParser(',')
{

}

QString CSVParser::parseCell(const QString &cell) const
{
    if((cell.size() < 2) || (cell[0] != '\"') || (cell[cell.size()-1] != '\"'))
        throw QString("Failed to parse csv file: Missing cell quotes!");
    return cell.mid(1, cell.size()-2);
}

QString CSVParser::formatCell(const QString &content) const
{
    return "\"" + content + "\"";
}
