/**
 * @file topping.cpp
 */

#include "topping.h"
#include "usefulio.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * @brief Helper function for toString() in Pizza
 * @return the name of topping, if the serial is the same
 */
/*std::string Topping::getNameIfSameSerial(const int& serial) const {
    if (serialNum == serial)
        return name;
    else
        return std::string("");
}*/

/**
 * @brief Saver method, saves attributes into stream
 */
void Topping::save(std::ostream& os) {
    os << serialNum << " ";
    writeString(os, name);
    os << price << std::endl;
}

/**
 * @brief Loader method, loads attributes from stream
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

/**
 * @brief Comparator for toppings
 * @return true if their serialNum are identical (it's their unique key)
 * @see List<T>.find(const T& data)
 */
bool Topping::operator==(const Topping& rhs) const {
    return serialNum == rhs.getSerialNum();
}

Topping* Topping::clone() const {
    return new Topping(*this);
}
