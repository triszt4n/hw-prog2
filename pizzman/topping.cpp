/**
 * @file topping.cpp
 */

#include "topping.h"
#include <cstdlib>
#include <iostream>
#include <string>

void Topping::save(std::ostream& os) const {

}

void Topping::load(std::istream& is) const {

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
double Topping::getPrice() const {
    return price;
}

/**
 * @brief Comparator for toppings
 * @return true if their serialNum are identical (it's their unique key)
 * @see List<T>.find(const T& data)
 */
bool Topping::operator==(Topping& rhs) const {
    return serialNum == rhs.getSerialNum();
}
