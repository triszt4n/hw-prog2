/**
 * @file order.cpp
 */

#include "order.h"
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * @typedef PizzaIter
 * @brief Used for pizza list's iterator
 */
typedef List<Pizza>::iterator PizzaIter;


void Order::save(std::ostream& os) const {

}

void Order::load(std::istream& is) const {

}


///getters:

/**
 * @brief Simple getter for getting the id of order entity
 * @return id
 */
int Order::getId() const {
    return id;
}

/**
 * @brief Simple getter for getting the username of orderer
 * @return orderedBy
 */
std::string Order::getOrdedBy() const {
    return orderedBy;
}

/**
 * @brief Simple getter for getting the username of admin, that accepted
 * @return acceptedBy
 */
std::string Order::getAcceptedBy() const {
    return acceptedBy;
}

/**
 * @brief Simple getter for getting the username of deliverer
 * @return deliveredBy
 */
std::string Order::getDeliveredBy() const {
    return deliveredBy;
}

/**
 * @brief Simple getter for getting the state of ordering
 * @return state
 */
OrderState Order::getState() const {
    return state;
}

/**
 * @fn displayOrder(std::ostream& os)
 * @brief Displays every important information of the ordering onto a stream
 * @param os - the stream to write to
 */
void Order::displayOrder(std::ostream& os) const {
    ///TODO!!!!!!!!!!!!!!4
}


///setters:

/**
 * @brief Appends a pizza from the global pizzas to the order list
 * @param allItems - points to the List of all the global pizzas
 * @param serialNum - identifies the pizza, which should be appended to order list from global pizzas
 */
void Order::appendPizza(List<Pizza>* allItems, int serialNum) {
    //Pizza pizza(serialNum, )
    /// SZÜKSÉGEM LESZ A KÜLSŐ ÖSSZES PIZZÁRA IS, HOGY MOST AKKOR MELYIK SERIALNUMOS PIZZÁT ADJUK HOZZÁ

    items.insert();
}

/**
 * @brief Simple getter for getting the state of ordering
 * @return state
 */
void Order::addTopping(int index, int serialNumOfTopping) {

}

void Order::setShippingAddress(std::string sA) {

}

void Order::setPayBy(int choice) {

}

void Order::setComment(std::string comment) {

}


///commands to change state of order:


bool Order::sendOrder(std::string username) {
    return 0;
}

bool Order::acceptOrder(std::string username) {
    return 0;
}

bool Order::deliverOrder(std::string username) {
    return 0;
}

bool Order::closeOrder(std::string username, bool success) {
    return 0;
}

/**
 * @brief Comparator for orders
 * @return true if their ids are identical (it's their unique key)
 * @see List<T>.find(const T& data)
 */
bool Order::operator==(Order& rhs) const {
    return id == rhs.getId();
}
