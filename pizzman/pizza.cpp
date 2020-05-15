/**
 * @file pizza.cpp
 * @brief Pizza class definitions
 * Contains: +copyItems() friend function, +loadPizzas() function
 */

#include "pizza.h"
#include "list.hpp"
#include "topping.h"
#include "usefulio.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>

/**
 * @typedef ItemIter
 * @brief Used for Pizza's own items List iterator
 */
typedef List<Topping>::iterator ItemIter;

/**
 * @typedef TopIter
 * @brief Used for toppings (heterostore) list's iterator
 */
typedef List<Topping*>::iterator TopIter;





/**
 * @brief Copying object's items into other one (overload for Pizza)
 * @param pizzaSource - source, that's items will get copied
 * @param pizzaDest - destination, into the items will get copied
 * @see Used by assign operator ...
 */
void copyItems(const Pizza& pizzaSource, Pizza& pizzaDest) {
    pizzaDest.items.clear();
    for (ItemIter iter = pizzaSource.items.begin(); iter != pizzaSource.items.end(); ++iter) {
        pizzaDest.items.insert(*iter);
    }
}

/**
 * @brief Assign operator for Pizza
 * @see Used by order.h
 */
Pizza& Pizza::operator=(const Pizza& rhs) {
    if (&rhs == this)
        return *this;
    else {
        serialNum = rhs.getSerialNum();
        name = rhs.getName();
        price = rhs.getPrice();
        copyItems(rhs, *this);
        return *this;
    }
}

/**
 * @brief Copy constructor
 * Depends highly on assign operator
 */
Pizza::Pizza(const Pizza& pizza) {
    *this = pizza;
}




/// --------------------- Persistence ----------------------

/**
 * @brief Simple I/O function for object storing
 */
void Pizza::save(std::ostream& os) const {
    os << serialNum << ' ';
    writeString(os, name);
    os << price << ' ' << items.size() << ' ';
    for (ItemIter iter = items.begin(); iter != items.end(); ++iter) {
        os << iter->getSerialNum() << ' ';
    }
    os << std::endl;
}

/**
 * @brief Simple I/O function for object storing
 */
bool Pizza::load(std::istream& is, List<Topping*>& toppings) {
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
        TopIter found = toppings[serial];
        if (found != toppings.end())
            items.insert(*(*found));
    }
    return true;
}

/// ------------------ End of Persistence ------------------




/// ----------------------- Getters ------------------------

/**
 * @brief Getting serialNum of object
 */
int Pizza::getSerialNum() const {
    return serialNum;
}

/**
 * @brief Getting name of object
 */
std::string Pizza::getName() const {
    return name;
}

/**
 * @brief Getting price of object
 */
int Pizza::getPrice() const {
    return price;
}

/**
 * @brief Displays pizza's toppings onto a stream
 */
void Pizza::displayItems(std::ostream& os) const {
    for (ItemIter iter = items.begin(); iter != items.end(); ++iter) {
        os << "- ";
        iter->displayTopping(os, false);
    }
}

/**
 * @brief Displays pizza's all details onto a stream
 */
void Pizza::displayPizza(std::ostream& os) const {
    os << "#" << serialNum << " " << name << " - " << price << " Ft" << std::endl;
    displayItems(os);
    os << std::endl;
}

/**
 * @brief Writes items onto a file stream
 */
void Pizza::writeItems(std::ostream& os) const {
    os << items.size() << ' ';
    for (ItemIter iter = items.begin(); iter != items.end(); ++iter) {
        os << iter->getSerialNum() << ' ';
    }
}

/// -------------------- End of Getters --------------------






/// ----------------------- Setters ------------------------

/**
 * @brief Inserts the serial of topping to the list of toppings in the pizza
 * Also, the price is incremented by the price of the new topping.
 * @param serial - the serialNum of topping to be inserted
 * @return true, if insertion was successful
 */
bool Pizza::addTopping(List<Topping*>& toppings, const int& serial) {
    TopIter top = toppings[serial];
    if (top == toppings.end()) {
        return false;
    }
    else {
        items.insert(*(*top));
        price += (*top)->getPrice();
        return true;
    }
}

/**
 * @brief Admin can reset the price to an amount they want
 * @param p - price to be set to
 */
void Pizza::setPrice(const int& p) {
    price = p;
}

/// -------------------- End of Setters --------------------





/**
 * @brief Comparator for pizzas
 * @return true if their serialNums are identical (it's their unique key)
 * @see List<T>.find(const T& data)
 */
bool Pizza::operator==(const Pizza& rhs) const {
    return serialNum == rhs.getSerialNum();
}

/**
 * @brief Cloning method
 * @return a pointer with clone object
 */
Pizza* Pizza::clone() const {
    return new Pizza(*this);
}

/**
 * @brief loading up pizzas with data from give file
 * @return true if loading was successful
 */
bool loadPizzas(List<Pizza*>& pizzas, List<Topping*>& toppings, std::istream& is) {
    size_t inputNum;
    (is >> inputNum).ignore(1);

    for (size_t i = 0; i < inputNum; ++i) {
        Pizza inputPizza;
        bool canPut = inputPizza.load(is, toppings);
        if (canPut)
            pizzas.insert(inputPizza.clone());
    }
    return true;
}
