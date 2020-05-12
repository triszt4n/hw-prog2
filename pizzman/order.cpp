/**
 * @file order.cpp
 */

#include "order.h"
#include "list.hpp"
#include "usefulio.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>

/**
 * @typedef PizzaIter
 * @brief Used for pizza list's iterator
 */
typedef List<std::string>::iterator PizzaIter;

void Order::save(std::ostream& os) const {
    os << id << ' ';
    writeString(os, orderedBy);
    writeString(os, acceptedBy);
    writeString(os, deliveredBy);
    writeString(os, shippingAddress);

    os << static_cast<int>(payBy) << ' ';
    os << sentDate << ' ';
    os << deliveredDate << ' ';
    os << static_cast<int>(state) << std::endl;
    writeString(os, comment);

    os << items.size();
    os << std::endl;

    for (PizzaIter iter = items.begin(); iter != items.end(); ++iter) {
        writeString(os, *iter);
        os << std::endl;
    }
}

bool Order::load(std::istream& is) {
    int helpingInteger;

    (is >> id).ignore(1);

    orderedBy = readString(is);
    acceptedBy = readString(is);
    deliveredBy = readString(is);
    shippingAddress = readString(is);

    (is >> helpingInteger).ignore(1);
    payBy = static_cast<PaymentMethod>(helpingInteger);

    (is >> sentDate).ignore(1);

    (is >> deliveredDate).ignore(1);

    (is >> helpingInteger).ignore(1);
    state = static_cast<OrderState>(helpingInteger);

    comment = readString(is);

    size_t pizzaNum;
    (is >> pizzaNum).ignore(1);
    for (size_t i = 0; i < pizzaNum; ++i) {

    }

    return true;
}

/**
 * @brief Copy constructor
 */
Order::Order(const Order& order) {
    id = order.getId();
    orderedBy = order.getOrderedBy();
    acceptedBy = order.getAcceptedBy();
    deliveredBy = order.getDeliveredBy();
    shippingAddress = order.getShippingAddress();
    payBy = order.getPayBy();
    sentDate = order.getSentDate();
    deliveredDate = order.getDeliveredDate();
    state = order.getState();
    comment = order.getComment();
    copyItems(order, *this);
}

///getters:

int Order::getId() const {
    return id;
}

std::string Order::getOrderedBy() const {
    return orderedBy;
}

std::string Order::getAcceptedBy() const {
    return acceptedBy;
}

std::string Order::getDeliveredBy() const {
    return deliveredBy;
}

std::string Order::getShippingAddress() const {
    return shippingAddress;
}

PaymentMethod Order::getPayBy() const {
    return payBy;
}

time_t Order::getSentDate() const {
    return sentDate;
}

time_t Order::getDeliveredDate() const {
    return deliveredDate;
}

OrderState Order::getState() const {
    return state;
}

std::string Order::getComment() const {
    return comment;
}

/**
 * @brief Copying object's items into other one
 * @param orderSource - source, that's items will get copied
 * @param orderDest - destination, into the items will get copied
 */
void copyItems(const Order& orderSource, Order& orderDest) {
    orderDest.items.clear();
    for (PizzaIter iter = orderSource.items.begin(); iter != orderSource.items.end(); ++iter) {
        orderDest.items.insert(*iter);
    }
}

/**
 * @fn displayOrder(std::ostream& os)
 * @brief Displays every important information of the ordering onto a stream
 * @param os - the stream to write to
 */
void Order::displayOrder(std::ostream& os) const {
    os << "order #" << id << "      sent: " << ctime(&sentDate) << std::endl;
    os << "          delivered: " << ctime(&deliveredDate) << std::endl;
    os << "ship.address: " << shippingAddress << std::endl;

    switch (payBy) {
    case BANK_CARD:
        os << "     paid by: BANK CARD";
        break;
    case VOUCHER:
        os << "     paid by: VOUCHER";
        break;
    default:
        os << "     paid by: CASH";
    }

    switch (state) {
    case SENT:
        os << "order status: SENT" << std::endl;
        break;
    case ACCEPTED:
        os << "order status: ACCEPTED" << std::endl;
        break;
    case EN_ROUTE:
        os << "order status: EN ROUTE" << std::endl;
        break;
    case DELIVERED:
        os << "order status: DELIVERED" << std::endl;
        break;
    case FAILED:
        os << "order status: FAILED" << std::endl;
        break;
    default:
        os << "order status: UNSENT" << std::endl;
    }

    if (orderedBy != "")
        os << "  ordered by: " << orderedBy << std::endl;
    if (acceptedBy != "")
        os << " accepted by: " << acceptedBy << std::endl;
    if (deliveredBy != "")
        os << "delivered by: " << orderedBy << std::endl;

    os << "comment: " << comment << std::endl;

    os << "pizzas: " << std::endl;
    for (PizzaIter iter = items.begin(); iter != items.end(); ++iter) {
        os << *iter << std::endl;
    }
    os << std::endl;
}


///setters:

/**
 * @brief Appends a pizza from the global pizzas to the order list
 * @param allItems - points to the List of all the global pizzas
 * @param serialNum - identifies the pizza, which should be appended to order list from global pizzas
 */
void Order::appendPizza(const int& serialNum, List<Pizza*>& pizzas) {
    //Pizza pizza(serialNum, )
    /// SZÜKSÉGEM LESZ A KÜLSŐ ÖSSZES PIZZÁRA IS, HOGY MOST AKKOR MELYIK SERIALNUMOS PIZZÁT ADJUK HOZZÁ

    //items.insert(Pizza());
}

/**
 * @brief Simple getter for getting the state of ordering
 * @return state
 */
void Order::addTopping(const int& index, const int& serialNumOfTopping, List<Topping*>& toppings) {

}

void Order::setShippingAddress(const std::string& sA) {
    shippingAddress = sA;
}

void Order::setPayBy(const int& choice) {
    if ((choice > 2) || (choice < 0))
        throw std::out_of_range("PaymentMethod has 3 enumerated values");
    else
        payBy = static_cast<PaymentMethod>(choice);
}

void Order::setComment(const std::string& comment) {
    this->comment = comment;
}


///commands to change state of order:


void Order::sendOrder(const std::string& username) {
    state = SENT;
    sentDate = std::time(0);
    orderedBy = username;
}

void Order::acceptOrder(const std::string& username) {
    state = ACCEPTED;
    acceptedBy = username;
}

void Order::deliverOrder(const std::string& username) {
    state = EN_ROUTE;
    deliveredBy = username;
}

void Order::closeOrder(bool success, const std::string& comment) {
    if (success)
        state = DELIVERED;
    else
        state = FAILED;
    this->comment += "\n" + comment;
}

/**
 * @brief Comparator for orders
 * @return true if their ids are identical (it's their unique key)
 * @see List<T>.find(const T& data)
 */
bool Order::operator==(const Order& rhs) const {
    return id == rhs.getId();
}

Order* Order::clone() const {
    return new Order(*this);
}
