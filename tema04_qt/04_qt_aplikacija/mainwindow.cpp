#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_score(0)
{
    ui->setupUi(this);

    // Objekat koji emituje signal: pbtnIncrement
    // Signal koji se emituje: QPushButton::clicked
    // Objekat koji prima signal: this (MainWindow)
    // Slot (fja): MainWindow::inc

    // Napomena: slot i signal su f-je koje imati isti potpis tj. iste argument
    // Specijalan slucaj: signal ima vise argumenata od slota, onda se visak ignorise

    // Rezultat:
    //      Klikom na dugme 'Increment' se poziva f-ja inc() i samim tim se uvecava
    //      trenutni rezultat igre za 1
    connect(
        ui->pbtnIncrement,
        &QPushButton::clicked,
        this,
        &MainWindow::inc
    );
}

void MainWindow::inc()
{
    m_score++;
    // QString::number je staticka metoda koja prevodi broj u nisku
    // tj. vraca QString
    QString updatedScoreText = "score: " + QString::number(m_score);
    ui->lScore->setText(updatedScoreText);
}

MainWindow::~MainWindow()
{
    delete ui;
}
