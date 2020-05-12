/**
 * @file pizza.cpp
 */

#include "pizza.h"
#include "list.hpp"
#include "topping.h"
#include "usefulio.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * @typedef TopIter
 * @brief Used for topping list's iterator
 */
typedef List<int>::iterator TopIter;

void Pizza::save(std::ostream& os) {

}

bool Pizza::load(std::istream& is) {
    (is >> serialNum).ignore(1);
    name = readString(is);

    size_t toppingNum;
    is >> price;
    is >> toppingNum;

    if (is.fail())
        return false;

    for (size_t i = 0; i < toppingNum; ++i) {
        int serial;
        is >> serial;
        toppingList.insert(serial);
    }
    return true;
}

/**
 * @brief Simple getter for getting the serialNum of object
 * @return serialNum
 */
int Pizza::getSerialNum() const {
    return serialNum;
}

/**
 * @brief Simple getter for getting the name of object
 * @return name
 */
std::string Pizza::getName() const {
    return name;
}

/**
 * @brief Simple getter for getting the price of object
 * @return price
 */
int Pizza::getPrice() const {
    return price;
}

/**
 * @brief Displays toppings onto a stream
 */
void Pizza::displayToppingList(std::ostream& os, List<Topping*>& toppings) const {
    for (TopIter iter = toppingList.begin(); iter != toppingList.end(); ++iter) {
        int serial = *iter;
        Topping* top = toppings[serial];
        os << "+ #" << serial << " " << top->getName() << std::endl;
    }
}

/**
 * @brief Copying object's toppingList into other one
 * @param pizzaSource - source, that's toppingList will get copied
 * @param pizzaDest - destination, into the toppingList will get copied
 */
void copyToppingList(const Pizza& pizzaSource, Pizza& pizzaDest) {
    pizzaDest.toppingList.clear();
    for (TopIter iter = pizzaSource.toppingList.begin(); iter != pizzaSource.toppingList.end(); ++iter) {
        pizzaDest.toppingList.insert(*iter);
    }
}
/// Overloading
void copyToppingList(List<int>& toppingListSource, Pizza& pizzaDest) {
    pizzaDest.toppingList.clear();
    for (TopIter iter = toppingListSource.begin(); iter != toppingListSource.end(); ++iter) {
        pizzaDest.toppingList.insert(*iter);
    }
}

/**
 * @brief Copy constructor
 */
Pizza::Pizza(const Pizza& pizza) {
    serialNum = pizza.getSerialNum();
    name = pizza.getName();
    price = pizza.getPrice();
    copyToppingList(pizza, *this);
}

/**
 * @fn addTopping(const int& toppingSerial, const int& toppingPrice)
 * @brief Inserts the serial of topping to the list of toppings in the pizza
 * Also, the price is incremented by the price of the new topping.
 * @param toppingSerial - the serialNum of topping to be inserted
 * @param toppingPrice - the price the, pizza's cost shall be incremented with
 */
void Pizza::addTopping(const int& toppingSerial, const int& toppingPrice) {
    toppingList.insert(toppingSerial);
    price += toppingPrice;
}

/**
 * @fn setPrice(int p)
 * @brief Admin can reset the price to an amount they want
 * @param p - price to be set to
 */
void Pizza::setPrice(const int& p) {
    price = p;
}

/**
 * @brief Comparator for pizzas
 * @return true if their serialNums are identical (it's their unique key)
 * @see List<T>.find(const T& data)
 */
bool Pizza::operator==(const Pizza& rhs) const {
    return serialNum == rhs.getSerialNum();
}

/**
 * @fn clone(): Pizza*
 * @brief clone the current Pizza object
 * @return a pointer of new copy of this object (should be deleted by caller)
 */
Pizza* Pizza::clone() const {
    return new Pizza(*this);
}
