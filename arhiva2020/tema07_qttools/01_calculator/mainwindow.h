#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <utility>
#include <QMainWindow>
#include <QLineEdit>
#include "Fraction.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Skrecemo paznju na imenovanje ovih slot metoda.
    // Ukoliko (void) slot metod nazovemo "on_X_Y",
    // onda ce Qt5 biblioteka automatski povezati
    // signal sa imenom Y u objektu ciji je naziv X u prozoru.
    // Vise o ovome na: https://doc.qt.io/qt-5/designer-using-a-ui-file.html#widgets-and-dialogs-with-auto-connect
    void on_pbOp1Inc_clicked();
    void on_pbOp2Inc_clicked();
    void on_pbPlus_clicked();
    void on_pbMinus_clicked();

private:
    Ui::MainWindow *ui;

    // Vrsi parsiranje razlomka iz QLineEdit polja koji se prosledjuje
    std::pair<bool, Fraction> parse(QLineEdit* le);
};

#endif // MAINWINDOW_H
