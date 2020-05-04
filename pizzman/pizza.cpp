/**
 * @file pizza.cpp
 */

#include "pizza.h"
#include "list.hpp"
#include "topping.h"
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * @typedef TopIter
 * @brief Used for topping list's iterator
 */
typedef List<Topping>::iterator TopIter;

void Pizza::save(std::ostream& os) const {

}

void Pizza::load(std::istream& is) const {

}

/**
 * @brief Simple getter for getting the serialNum of object
 * @return serialNum
 */
int Pizza::getSerialNum() const {
    return serialNum;
}

/**
 * @brief Create a string, that has the information of one Pizza
 * @return string of data
 */
std::string Pizza::toString() const {
    std::string temp = name + " $";
    temp += std::to_string(price);
    temp += "\n(";
    for (TopIter iter = toppings.begin(); iter != toppings.end(); ++iter) {
        temp += " " + (*iter).getName();
    }
    temp += ")";
    return temp;
}

/**
 * @fn addTopping(Topping& topping)
 * @brief Inserts the topping to the list of toppings in the pizza
 * Also, the price is incremented by the price of the new topping.
 * @param topping - the topping to be inserted
 */
void Pizza::addTopping(Topping& topping) {
    toppings.insert(topping);
    price += topping.getPrice();
}

/**
 * @fn setPrice(double p)
 * @brief Admin can reset the price to an amount they want
 * @param p - price to be set to
 */
void Pizza::setPrice(double p) {
    price = p;
}

/**
 * @brief Comparator for pizzas
 * @return true if their serialNums are identical (it's their unique key)
 * @see List<T>.find(const T& data)
 */
bool Pizza::operator==(Pizza& rhs) const {
    return serialNum == rhs.getSerialNum();
}
