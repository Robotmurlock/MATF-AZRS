#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void inc();

private:
    Ui::MainWindow *ui;
    int m_score;
};

#endif // MAINWINDOW_H
