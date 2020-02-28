/**
 * \file komplex.cpp
 *
 * Komplex osztályt megvalósító függvények definíciója.
 *
 * Folytassa a megvalósítást sorrendben a komplex.h fájlban levő feladatoknak megfelelően!
 *
 */


#include <iostream>         // Valószínű, hogy a kiíráshoz majd kell
#include <iomanip>          // ... és ez is.
#include <cmath>            // az sqrt miatt kell.

#include "komplex.h"        // Ebben van a Komplex osztály, és néhány globális függvény deklarációja

///using namespace std;  // ha nagyon kell, akkor csak itt nyissuk ki a névteret, a headerben soha!

/// Előre elkészített tagfüggvények

/// 0, 1 és 2 paraméteres konstruktor
/// Figyelje meg, hogy a default argumentumokat CSAK a deklarációnál
/// adtuk meg!
Komplex::Komplex(double r, double im) {
    re = r; // ha nincs névütközés, nem kell kiírni a this-t
    this->im = im;
}

///---- Egy példa a konstans tagfüggvényre, ehhez hasonlóan kell
///     elkészíteni a gettereket az 1. feladatban (ELKESZULT=1)
/// Abszolút érték lekérdezése
/// @return - abszolút érték
double Komplex::abs() const { return sqrt(re*re + im*im); }

#if ELKESZULT >= 3
// 3. feladathoz (ELKESZULT 3)
// összehasonlítás
/// Egyenlőtlenség vizsgálat
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return hamis - ha a képzetes és a valós rész is azonos, egyébként false
bool Komplex::operator!=(const Komplex& rhs_k) const {  // visszavezetjük az egyenlőség vizsgálatra
    return !(*this == rhs_k);
}
#endif

#if ELKESZULT >= 6
// 6. feladathoz (ELKESZULT 6)
// a += művelet viszont módosítja önmagát!
/// Komplex + double
/// @param rhs_d - jobb oldali operandus (double)
/// @return eredeti (bal oldali) objektum ref., amihez hozzáadtuk rhd_d-t
Komplex& Komplex::operator+=(double rhs_d) {
    re += rhs_d;
    return *this;
}
#endif

// ------------------------ Eddig elkészítettük -------------------------
// TODO: A hiányzó tag- és globális függvények itt következnek

/// Valós rész lekérdezése
/// @return - valós rész
double Komplex::getRe() const {
    return this->re;
}

/// Képzetes rész lekérdezése
/// @return - képzetes rész
double Komplex::getIm() const {
    return this->im;
}

/// Valós részt beállító függvény
/// @param r - valós rész
void Komplex::setRe(double re) {
    this->re = re;
}

/// Képzetes részt beállító függvény
/// @param im - képzetes rész
void Komplex::setIm(double im) {
    this->im = im;
}

/// Egyenlőség vizsgálat
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return true - ha a képzetes és a valós rész is azonos, egyébként false
bool Komplex::operator==(const Komplex& rhs_k) const {
    return (rhs_k.getIm() == this->im && rhs_k.getRe() == this->re);
}

/// Komplex + Komplex
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return egy új komplex adat - a két komplex adat összege
Komplex Komplex::operator+(const Komplex& rhs_k) const {
    return Komplex(this->re + rhs_k.getRe(), this->im + rhs_k.getIm());
}

/// Komplex + double
/// @param rhs_d - jobb oldali operandus (double)
/// @return egy új komplex adat - a két adat összege
Komplex Komplex::operator+(double rhs_d) const {
    return Komplex(this->re + rhs_d, this->im);
}

/// double + Komplex csak globális függvénnyel valósítható meg,
/// mivel a bal oldal nem osztály.
/// Ld. az osztály deklarációja után!
Komplex operator+(const double lhs_d, const Komplex& rhs_k) {
    return Komplex(rhs_k.getRe() + lhs_d, rhs_k.getIm());
}

/// Komplex + Komplex
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return eredeti (bal oldali) objektum ref., amihez hozzáadtuk rhd_k-t
Komplex& Komplex::operator+=(const Komplex& rhs_k) {
    this->re += rhs_k.getRe();
    this->im += rhs_k.getIm();
    return *this;
}

/// Kiírás egy ostream-re.
/// Ez is csak globális függvénnyel valósítható meg.
/// A bal oldal osztály ugyan, de nincs a kezünkben, nem módosítható.
/// Ld. az osztály deklarációja után!

std::ostream& operator<<(std::ostream& os, const Komplex& k) {
    double re = k.getRe();
    double im = k.getIm();
    char elojel = (im < 0)? '-': '+';
    os << re << elojel << fabs(im) << 'j';
    return os;
}

std::istream& operator>>(std::istream& is, Komplex& k) {
    double re, im;
    char elojel, c;
    is >> re >> elojel >> im >> c;
    if (elojel == '-') im *= -1;
    k = Komplex(re, im);
    return is;
}

/// komplex konjugált
/// ~Komplex
/// @return egy új adat, amiben a konjugált érték van
Komplex Komplex::operator~() const {
    double re = this->getRe(), im = this->getIm() * -1;
    return Komplex(re, im);
}

/// Komplex * Komplex
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return egy új komplex adat - a két komplex adat szorzata
Komplex Komplex::operator*(const Komplex& rhs_k) const {
    double re = this->getRe() * rhs_k.getRe() - this->getIm() * rhs_k.getIm();
    double im = this->getRe() *rhs_k.getIm() + this->getIm() * rhs_k.getRe();
    return Komplex(re, im);
}

/// Komplex * double
/// @param rhs_d - jobb oldali operandus (double)
/// @return egy új komplex adat - a két adat szorzata
Komplex Komplex::operator*(double rhs_d) const {
    return Komplex(rhs_d * this->getRe(), rhs_d * this->getIm());
}

// a *= művelet viszont módosítja önmagát!
/// Komplex * Komplex
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return eredeti (bal oldali) objektum ref., amit megszorosztunk
Komplex& Komplex::operator*=(const Komplex& rhs_k) {
    double re = this->getRe() * rhs_k.getRe() - this->getIm() * rhs_k.getIm();
    double im = this->getRe() *rhs_k.getIm() + this->getIm() * rhs_k.getRe();
    setRe(re);
    setIm(im);
    return *this;
}

/// Komplex + double
/// @param rhs_d - jobb oldali operandus (double)
/// @return eredeti (bal oldali) objektum ref., amit megszoroztunk
Komplex& Komplex::operator*=(double rhs_d) {
    setRe(rhs_d * this->getRe());
    setIm(rhs_d * this->getIm());
    return *this;
}

/// double * Komplex
/// @param lhs_d - bal oldali operandus (double)
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return egy új komplex adat - a két adat szorzata
Komplex operator*(double lhs_d, const Komplex& rhs_k) {
    return Komplex(lhs_d * rhs_k.getRe(), lhs_d * rhs_k.getIm());
}



