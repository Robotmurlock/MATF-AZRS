#ifndef TXTPARSER_H
#define TXTPARSER_H

#include <QString>
#include <vector>

class TXTParser
{
public:
    TXTParser(char delimiter)
        : m_delimiter(delimiter) {}
    virtual ~TXTParser() {};

public:
    std::vector<std::vector<QString> > load(const QString &path) const;
    void store(const std::vector<std::vector<QString> > data, const QString &path) const;
    static TXTParser *parser(const QString &fileType);;

protected:
    const char m_delimiter;
    virtual QString parseCell(const QString &cell) const = 0;
    virtual QString formatCell(const QString &content) const = 0;
};

#endif // TXTPARSER_H
