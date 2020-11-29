#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <QString>

class Fraction {
public:
    Fraction(int numerator = 0, unsigned int denominator = 1);

    // Funkcije koje omogucavaju da citamo privatne podatke.
    // Kljucna rec `const` sa desne strane oznacava da funkcije
    // ne menjaju stanje objekta.
    int numerator() const;
    unsigned int denominator() const;

    // Funkcije koje omogucavaju da se promene vrednosti za
    // brojilac i imenilac.
    void set_numerator(int numerator);
    void set_denominator(unsigned int denominator);

    // Binarni operatori za sabiranje i oduzimanje razlomaka `a` i `b` gde je:
    // - `a` -> *this
    // - `b` -> other
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;

    // Postfiksno inkremetiranje.
    Fraction operator++(int);

    // Prefiksno inkrementiranje.
    Fraction& operator++();

    // Unarni operator -
    Fraction operator-() const;

    // Operator za konverziju u double.
    operator double() const;
    // Operator za konverziju u QString
    operator QString() const;

    // Operatori za jednakost i nejednakost.
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;

    // ------------------------------------------------------------------------
    // DOMACI:
    // ------------------------------------------------------------------------
    // - Mnozenje razlomaka
    // - Deljenje razlomaka
    // - Operatori >, <
    // - Prefiksni i postfiksni operatori --
    // - Operatori >=, <=
    // - Mnozenje i deljenje skalarom
    // ------------------------------------------------------------------------

private:
    int m_numerator;
    unsigned m_denominator;

    // Oznacavamo ove dve funkcije (odnosno operator << i >>) kao prijateljske funkcije
    // za nasu klasu. Time dozvoljavamo funkcijama da pristupe privatnim clanovima za
    // objekte koji su instanca ove klase. To omogucava da direktno pristupamo
    // brojiocu i imeniocu (m_numerator, m_denominator) umesto da zovemo funkcije
    // numerator() i denominator().
    friend std::ostream& operator<<(std::ostream& out, const Fraction& value);
    friend std::istream& operator>>(std::istream& in, Fraction& value);

    // Vrsi skracivanje razlomaka.
    void reduce_fraction();
};

std::ostream& operator<<(std::ostream& out, const Fraction& value);
std::istream& operator>>(std::istream& in, const Fraction& value);

#endif
