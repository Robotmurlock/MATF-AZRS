#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// namespace - prostor imena - uopstenje pakate iz Jave
// namespace Ui grupise MainWindow i generisan Ui_MainWindow

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // explicit konstruktor onemogucava implicitno pozivanje konstruktora
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void inc();

private:
    Ui::MainWindow *ui;
    int m_score;
};

#endif // MAINWINDOW_H
