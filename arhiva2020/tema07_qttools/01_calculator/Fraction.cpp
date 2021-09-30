#include "Fraction.hpp"

Fraction::Fraction(int numerator, unsigned int denominator)
    : m_numerator(numerator), m_denominator(denominator)
{
    reduce_fraction();
}

void Fraction::reduce_fraction()
{
    // TODO: Domaci: Implementirati skracivanje razlomaka
}

int Fraction::numerator() const
{
    return m_numerator;
}

unsigned int Fraction::denominator() const
{
    return m_denominator;
}

void Fraction::set_numerator(int numerator)
{
    m_numerator = numerator;
}

void Fraction::set_denominator(unsigned int denominator)
{
    m_denominator = denominator;
}

Fraction Fraction::operator+(const Fraction& other) const
{
    return Fraction(
        m_denominator * other.m_numerator + other.m_denominator * m_numerator,
        m_denominator * other.m_denominator
    );
}

Fraction Fraction::operator-(const Fraction& other) const
{
    return Fraction(
        other.m_denominator * m_numerator - m_denominator * other.m_numerator,
        m_denominator * other.m_denominator
    );
}

// Postfiksno inkrementiranje.
Fraction Fraction::operator++(int)
{
    Fraction tmp(m_numerator, m_denominator);

    // Inkremenitiramo trenutni objekat koristeci
    // prefiksni operator inkrementacije.
    ++(*this);

    // Vracamo originalnu verziju.
    return tmp;
}

// Prefiksno inkrementiranje.
Fraction& Fraction::operator++()
{
    m_numerator += m_denominator;
    return (*this);
}

// Unarni operator -
Fraction Fraction::operator-() const
{
    // TODO Domaci
    return Fraction();
}

// Operator za konverziju u double.
Fraction::operator double() const
{
    return m_numerator / static_cast<double>(m_denominator);
}

Fraction::operator QString() const
{
    return
        QString::number(m_numerator)
        + "/"
        + QString::number(m_denominator);
}

// Operatori za jednakost i nejednakost.
bool Fraction::operator==(const Fraction& other) const
{
    return m_numerator * other.m_denominator == other.m_numerator * m_denominator;
}

bool Fraction::operator!=(const Fraction& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Fraction& value)
{
    return out << value.m_numerator << "/" << value.m_denominator;
}

std::istream& operator>>(std::istream& in, Fraction& value)
{
    // Koristimo `c` da progutamo separator izmedju brojeva koje je prosledio korisnik.
    char c;
    return in >> value.m_numerator >> c >> value.m_denominator;
}
