#include "dataviewer.h"
#include "ui_dataviewer.h"

#include <QFileDialog>
#include <QTableWidgetItem>
#include <QMessageBox>

DataViewer::DataViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataViewer)
{
    ui->setupUi(this);
}

DataViewer::~DataViewer()
{
    delete ui;
}

void DataViewer::on_pbtnImport_clicked()
{
    auto filePath = openFile();
    auto parser = getParser();

    try {
        auto data = parser->load(filePath);
        showData(data);
    }
    catch (QString msg) {
        QMessageBox box;
        box.setText(msg);
        box.exec();
    }

    delete parser;
}

void DataViewer::on_pbtnExport_clicked()
{
    auto filePath = saveFile();
    auto parser = getParser();

    // Store data
    auto data = getData();
    parser->store(data, filePath);
    delete parser;
}

QString DataViewer::openFile()
{
    auto filePath = QFileDialog::getOpenFileName(this, "Select file to view.", ".");
    ui->lFilePath->setText(filePath);
    return filePath;
}

QString DataViewer::saveFile()
{
    auto filePath = QFileDialog::getSaveFileName(this, "Save file.", ".");
    ui->lFilePath->setText(filePath);
    return filePath;
}

TXTParser *DataViewer::getParser() const
{
    auto fileType = ui->cbFileType->currentText();
    return TXTParser::parser(fileType);
}

void DataViewer::showData(const std::vector<std::vector<QString> > &data)
{
    auto n_rows = data.size();
    auto n_cols = data.at(0).size();
    ui->twData->setRowCount(n_rows);
    ui->twData->setColumnCount(n_cols);
    for(size_t i=0; i<n_rows; i++)
    {
        for(size_t j=0; j<n_cols; j++)
        {
            auto item = new QTableWidgetItem(data[i][j]);
            ui->twData->setItem(i, j, item);
        }
    }
}

std::vector<std::vector<QString> > DataViewer::getData() const
{
    std::vector<std::vector<QString> > data;
    for(int i=0; i<ui->twData->rowCount(); i++)
    {
        std::vector<QString> row;
        for(int j=0; j<ui->twData->columnCount(); j++)
        {
            row.push_back(ui->twData->item(i, j)->text());
        }
        data.push_back(row);
    }

    return data;
}

