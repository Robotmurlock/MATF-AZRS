#include "txtparser.h"
#include "csvparser.h"
#include "tsvparser.h"

#include <QFile>
#include <QTextStream>

std::vector<std::vector<QString> > TXTParser::load(const QString &path) const
{
    std::vector<std::vector<QString> > data;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw QString("Opening file failed!");
    QTextStream reader(&file);

    int n_cells = -1;
    while(!reader.atEnd())
    {
        auto line = reader.readLine();
        auto cells = line.split(m_delimiter);

        // check if every row has same number of columns
        if(n_cells == -1)
            n_cells = cells.size();
        else if(n_cells != cells.size())
            throw QString("Failed to parse csv file: Wrong number of cells!");

        std::vector<QString> row;
        for(auto &cell: cells)
            row.push_back(parseCell(cell));
        data.push_back(row);
    }

    file.close();
    return data;
}

void TXTParser::store(const std::vector<std::vector<QString> > data, const QString &path) const
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw QString("Opening file failed!");
    QTextStream writer(&file);

    for(auto &row: data)
    {
        if(row.size() > 0)
        {
            for(size_t i=0; i<row.size()-1; i++)
            {
                auto &cell = row[i];
                writer << formatCell(cell) << m_delimiter;
            }
            writer << formatCell(row[row.size()-1]);
        }
        writer << "\n";
    }
}

TXTParser *TXTParser::parser(const QString &fileType)
{
    if(fileType == "csv")
        return new CSVParser();
    else if(fileType == "tsv")
        return new TSVParser();
    else
        return nullptr;
}
