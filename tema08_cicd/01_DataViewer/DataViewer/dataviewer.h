#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include <QWidget>
#include <vector>
#include "../Parser/txtparser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DataViewer; }
QT_END_NAMESPACE

class DataViewer : public QWidget
{
    Q_OBJECT

public:
    DataViewer(QWidget *parent = nullptr);
    ~DataViewer();

public slots:
    void on_pbtnImport_clicked();
    void on_pbtnExport_clicked();

private:
    QString openFile();
    QString saveFile();
    TXTParser *getParser() const;

    void showData(const std::vector<std::vector<QString> > &data);
    std::vector<std::vector<QString> > getData() const;

    Ui::DataViewer *ui;
};
#endif // DATAVIEWER_H
