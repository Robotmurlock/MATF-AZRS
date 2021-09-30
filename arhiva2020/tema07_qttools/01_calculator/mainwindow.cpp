#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Inkrementacija prvog operanda
void MainWindow::on_pbOp1Inc_clicked()
{
    auto [success, frac] = parse(ui->leOp1);
    if (!success) {
        ui->leResult->setText("Neuspelo parsiranje prvog razlomka.");
        return;
    } else {
        // Azuriramo vrednost razlomka.
        ++frac;

        // Azuriramo prikaz korisniku
        ui->leOp1->setText(frac);
    }
}

// Inkrementacija drugog operanda
void MainWindow::on_pbOp2Inc_clicked()
{
    // ------------------------------------------------------------------------
    // VAZNO
    // ------------------------------------------------------------------------
    // Uocite da se logika za drugi razlomak ponavlja i da izuzetno lici na logiku
    // za prvi razomak. Ima smisla i preporuceno je apstrahovati obe funkcije
    // novom funkcijom, a potom nju pozvati i izbeci ponavljanje koda.
    // Uradite to za domaci.
    // ------------------------------------------------------------------------

    auto [success, frac] = parse(ui->leOp2);
    if (!success) {
        ui->leResult->setText("Neuspelo parsiranje drugog razlomka.");
        return;
    } else {
        // Azuriramo vrednost razlomka.
        ++frac;

        // Azuriramo prikaz korisniku
        ui->leOp2->setText(frac);
    }
}

// Sabiranje
void MainWindow::on_pbPlus_clicked()
{
    // Pokusavamo da parsiramo prvi razlomak
    auto [success1, frac1] = parse(ui->leOp1);
    auto [success2, frac2] = parse(ui->leOp2);

    if (!success1) {
        ui->leResult->setText("Neuspelo parsiranje prvog razlomka.");
        return;
    }
    if (!success2) {
        ui->leResult->setText("Neuspelo parsiranje drugog razlomka.");
        return;
    }

    // Ako je uspelo parsiranje, vrsimo izracunavanje.
    if (success1 && success2) {
        // Izracunavamo zbir (rezultat je Fraction),
        // i potom se poziva implicitno kastovanje u tip QString (implementirali smo taj operator).
        ui->leResult->setText(frac1 + frac2);
    }
}

// Oduzimanje
void MainWindow::on_pbMinus_clicked()
{
    // ------------------------------------------------------------------------
    // VAZNO
    // ------------------------------------------------------------------------
    // Uocite da se logika za oduzimanje ponavlja i da izuzetno lici na logiku
    // za sabiranje. Ima smisla i preporuceno je apstrahovati obe funkcije
    // novom funkcijom, a potom nju pozvati i izbeci ponavljanje koda.
    // Uradite to za domaci.
    // ------------------------------------------------------------------------

    auto [success1, frac1] = parse(ui->leOp1);
    auto [success2, frac2] = parse(ui->leOp2);

    if (!success1) {
        ui->leResult->setText("Neuspelo parsiranje prvog razlomka.");
        return;
    }
    if (!success2) {
        ui->leResult->setText("Neuspelo parsiranje drugog razlomka.");
        return;
    }

    // Ako je uspelo parsiranje, vrsimo izracunavanje.
    if (success1 && success2) {
        // Izracunavamo zbir (rezultat je Fraction),
        // i potom se poziva implicitno kastovanje u tip QString (implementirali smo taj operator).
        ui->leResult->setText(frac1 - frac2);
    }
}

std::pair<bool, Fraction> MainWindow::parse(QLineEdit *le)
{
    // Vrsimo razdvajanje stringa po separatoru '/'.
    // Rezultat je lista stringova (QStringList) razdvojenih po karakteru.
    // Na primer:
    // "1/3".split('/') -> ["1", "3"]
    const auto results = le->text().split('/');

    // Ako nemamo dva elementa, vracamo neuspeh.
    // Ova funkcija naravno nije otporna na prosledjivanje
    // elemenata koji nisu brojevi.
    if (results.size() == 2) {
        auto a = results[0].toInt();
        auto b = results[1].toUInt();
        return std::make_pair(true, Fraction(a, b));
    } else {
        return std::make_pair(false, Fraction());
    }
}
