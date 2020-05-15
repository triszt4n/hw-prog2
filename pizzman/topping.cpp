/**
 * @file topping.cpp
 * @brief Topping class definitions
 */

#include "topping.h"
#include "usefulio.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>


/// --------------------- Persistence ----------------------

/**
 * @brief Simple I/O function for object storing
 */
void Topping::save(std::ostream& os) {
    os << serialNum << " ";
    writeString(os, name);
    os << price << std::endl;
}

/**
 * @brief Simple I/O function for object storing
 * @return true if stream reading was a success
 */
bool Topping::load(std::istream& is) {
    (is >> serialNum).ignore(1);
    name = readString(is);
    is >> price;
    if (is.fail())
        return false;
    return true;
}

/// ------------------ End of Persistence ------------------




/**
 * @brief Assign operator for Topping
 * @return this object by reference
 * @see Used by copy constructor
 */
Topping& Topping::operator=(const Topping& rhs) {
    if (&rhs == this) {
        return *this;
    }
    else {
        serialNum = rhs.getSerialNum();
        name = rhs.getName();
        price = rhs.getPrice();
        return *this;
    }
}

/**
 * @brief Copy constructor for Topping
 * Highly dependent of assign operator
 */
Topping::Topping(const Topping& topping) {
    *this = topping;
}





/// ----------------------- Getters ------------------------

/**
 * @brief Displays topping's details onto a stream
 * @param showPrice - if true, write the price to the stream as well
 */
void Topping::displayTopping(std::ostream& os, bool showPrice) const {
    os << "#" << serialNum << " " << name;
    if (showPrice)
        os << " - "<< price << " Ft";
    os << std::endl;
}

/**
 * @brief Simple getter for name of topping
 * @return name
 */
std::string Topping::getName() const {
    return name;
}

/**
 * @brief Simple getter for serialNum
 * @return serialNum
 */
int Topping::getSerialNum() const {
    return serialNum;
}

/**
 * @brief Simple getter for price of topping
 * @return price
 */
int Topping::getPrice() const {
    return price;
}

/// -------------------- End of Getters --------------------





/**
 * @brief Comparator for toppings
 * @return true if their serialNum are identical (it's their unique key)
 * @see List<T>.find(const T& data)
 */
bool Topping::operator==(const Topping& rhs) const {
    return serialNum == rhs.getSerialNum();
}

/**
 * @brief Cloning method
 * @return a pointer with clone object
 */
Topping* Topping::clone() const {
    return new Topping(*this);
}
