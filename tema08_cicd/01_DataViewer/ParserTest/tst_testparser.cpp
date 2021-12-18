#include <QtTest>
#include <QDir>

#include "../Parser/tsvparser.h"
#include "../Parser/csvparser.h"
#include <QFile>
#include <QTextStream>
#include <vector>
#include <cassert>
#include <QDebug>

QString joinpath(std::vector<QString> args)
{
    assert(args.size() >= 1);
    QString path = args[0];
    for(size_t i=1; i<args.size(); i++)
        path += "/" + args[i];
    return path;
}

void stringToFile(const QString &content, const QString &path)
{
    QFile file(path);
    assert(file.open(QIODevice::WriteOnly | QIODevice::Text));
    QTextStream out(&file);
    out << content;
    file.close();

}

bool sameContent(const QString &path1, const QString &path2)
{
    QFile file1(path1);
    assert(file1.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in1(&file1);

    QFile file2(path2);
    assert(file2.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in2(&file2);

    while(!file1.atEnd() && !file2.atEnd())
    {
        auto line1 = file1.readLine();
        auto line2 = file2.readLine();
        if(line1 != line2)
            return false;
    }

    return file1.atEnd() && file2.atEnd();
}

void deleteFile(const QString &path)
{
    QFile file(path);
    file.remove();
}

class TestParser : public QObject
{
    Q_OBJECT

public:
    TestParser();
    ~TestParser();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_TSVParser_load();
    void test_TSVParser_store();
    void test_CSVParser_load();
    void test_CSVParser_store();

private:
    QString *tmp_path;

    QString *tsv_data_path;
    QString *tsv_data_str;
    std::vector<std::vector<QString> > *tsv_data;

    QString *csv_data_path;
    QString *csv_data_str;
    std::vector<std::vector<QString> > *csv_data;
};

TestParser::TestParser() {}

TestParser::~TestParser() {}

void TestParser::initTestCase()
{
    tmp_path = new QString(QDir(".").absolutePath());

    tsv_data_path = new QString(joinpath({*tmp_path, "test.tsv"}));
    tsv_data_str = new QString("a\tb\tc\n1\t2\t3\n4\t5\t6\n");
    tsv_data = new std::vector<std::vector<QString> >{
        {"a", "b", "c"},
        {"1", "2", "3"},
        {"4", "5", "6"}
    };

    csv_data_path = new QString(joinpath({*tmp_path, "test.csv"}));
    csv_data_str = new QString("\"a\",\"b\",\"c\"\n\"1\",\"2\",\"3\"\n\"4\",\"5\",\"6\"\n");
    csv_data = new std::vector<std::vector<QString> >{
        {"a", "b", "c"},
        {"1", "2", "3"},
        {"4", "5", "6"}
    };

    stringToFile(*tsv_data_str, *tsv_data_path);
    stringToFile(*csv_data_str, *csv_data_path);
}

void TestParser::cleanupTestCase()
{
    deleteFile(*csv_data_path);
    deleteFile(*tsv_data_path);

    delete tmp_path;
    delete tsv_data_path;
    delete tsv_data_str;
    delete tsv_data;
    delete csv_data_path;
    delete csv_data_str;
    delete csv_data;
}

void TestParser::test_TSVParser_load()
{
    // Arrange
    auto parser = TSVParser();

    // Act
    auto result = parser.load(*tsv_data_path);

    // Assert
    QVERIFY(result == *tsv_data);
}

void TestParser::test_TSVParser_store()
{
    // Arrange
    auto parser = TSVParser();
    auto result_path = joinpath({*tmp_path, "result.tsv"});

    // Act
    parser.store(*tsv_data, result_path);

    // Assert
    QVERIFY(sameContent(*tsv_data_path, result_path));

    // Cleanup
    deleteFile("result.tsv");
}

void TestParser::test_CSVParser_load()
{
    // Arrange
    auto parser = CSVParser();

    // Act
    auto result = parser.load(*csv_data_path);

    // Assert
    QVERIFY(result == *csv_data);
}

void TestParser::test_CSVParser_store()
{
    // Arrange
    auto parser = CSVParser();
    auto result_path = joinpath({*tmp_path, "result.csv"});

    // Act
    parser.store(*csv_data, result_path);

    // Assert
    QVERIFY(sameContent(*csv_data_path, result_path));

    // Cleanup
    deleteFile("result.csv");
}

QTEST_APPLESS_MAIN(TestParser)

#include "tst_testparser.moc"
