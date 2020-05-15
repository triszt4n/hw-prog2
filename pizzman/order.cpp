/**
 * @file order.cpp
 * @brief Order class definitions
 * Contains: +copyItems() friend function
 */

#include "order.h"
#include "list.hpp"
#include "usefulio.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

/**
 * @typedef ItemIter
 * @brief Used for items' List's iterator
 */
typedef List<Pizza>::iterator ItemIter;

/**
 * @typedef TopIter
 * @brief Used for toppings (heterostore) list's iterator
 */
typedef List<Topping*>::iterator TopIter;

/**
 * @typedef PizzaIter
 * @brief Used for pizzas (heterostore) list's iterator
 */
typedef List<Pizza*>::iterator PizzaIter;





/**
 * @brief Copying object's items into other one
 * @param orderSource - source, that's items will get copied
 * @param orderDest - destination, into the items will get copied
 * @see Assign operator for use
 */
void copyItems(const Order& orderSource, Order& orderDest) {
    orderDest.items.clear();
    for (ItemIter iter = orderSource.items.begin(); iter != orderSource.items.end(); ++iter) {
        orderDest.items.insert(*iter);
    }
}

/**
 * @brief Assign operator for Order
 * @see Used mainly by copy constructor
 * @return this object by reference
 */
Order& Order::operator=(const Order& rhs) {
    if (&rhs == this) {
        return *this;
    }
    else {
        id = rhs.getId();
        orderedBy = rhs.getOrderedBy();
        acceptedBy = rhs.getAcceptedBy();
        deliveredBy = rhs.getDeliveredBy();
        shippingAddress = rhs.getShippingAddress();
        payBy = rhs.getPayBy();
        sentDate = rhs.getSentDate();
        deliveredDate = rhs.getDeliveredDate();
        state = rhs.getState();
        comment = rhs.getComment();
        copyItems(rhs, *this);
        return *this;
    }
}

/**
 * @brief Copy constructor
 * Highly dependent on assign operator
 */
Order::Order(const Order& order) {
    *this = order;
}





/// --------------------- Persistence ----------------------

/**
 * @brief Simple I/O function for object storing
 */
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

    for (ItemIter iter = items.begin(); iter != items.end(); ++iter) {
        os << iter->getSerialNum() << ' ';
        writeString(os, iter->getName());
        os << iter->getPrice() << ' ';
        iter->writeItems(os);
        os << std::endl;
    }
}

/**
 * @brief Simple I/O function for object storing
 */
bool Order::load(std::istream& is, List<Topping*>& toppings) {
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
        int pizzaSerial;
        (is >> pizzaSerial).ignore(1);

        std::string pizzaName = readString(is);

        int pizzaPrice;
        (is >> pizzaPrice).ignore(1);

        size_t toppingNum;
        (is >> toppingNum).ignore(1);

        Pizza newPizza = Pizza(pizzaSerial, pizzaName, pizzaPrice);

        for (size_t j = 0; j < toppingNum; ++j) {
            int toppingSerial;
            (is >> toppingSerial).ignore(1);

            newPizza.addTopping(toppings, toppingSerial);
        }

        items.insert(newPizza);
    }

    return true;
}

/// ------------------ End of Persistence ------------------





/// ----------------------- Getters ------------------------

/**
 * @brief Simple getter for getting id of object
 */
int Order::getId() const {
    return id;
}

/**
 * @brief Simple getter for getting username of orderer
 */
std::string Order::getOrderedBy() const {
    return orderedBy;
}

/**
 * @brief Simple getter for getting username of admin that accepted order
 */
std::string Order::getAcceptedBy() const {
    return acceptedBy;
}

/**
 * @brief Simple getter for getting username of deliverer
 */
std::string Order::getDeliveredBy() const {
    return deliveredBy;
}

/**
 * @brief Simple getter for getting shipping address of object
 */
std::string Order::getShippingAddress() const {
    return shippingAddress;
}

/**
 * @brief Simple getter for getting payment method of object
 * @return a PaymentMethod (will have to static_cast)
 */
PaymentMethod Order::getPayBy() const {
    return payBy;
}

/**
 * @brief Simple getter for getting date of sending in
 */
time_t Order::getSentDate() const {
    return sentDate;
}

/**
 * @brief Simple getter for getting date of delivery
 */
time_t Order::getDeliveredDate() const {
    return deliveredDate;
}

/**
 * @brief Simple getter for getting state of object
 * @return a OrderState (will have to static_cast)
 */
OrderState Order::getState() const {
    return state;
}

/**
 * @brief Simple getter for getting comment of object
 */
std::string Order::getComment() const {
    return comment;
}

/**
 * @brief Displays every important information of the ordering onto a stream
 * @param os - the stream to write onto
 */
void Order::displayOrder(std::ostream& os) const {
    os << "-------------------------" << std::endl;
    os << " order #" << id;
    if (sentDate != 0)
        os << "       sent: " << ctime(&sentDate);
    else
        os << std::endl;

    if (deliveredDate != 0)
        os << "           delivered: " << ctime(&deliveredDate);

    os << " ship.address: " << shippingAddress << std::endl;

    switch (payBy) {
    case BANK_CARD:
        os << "      paid by: BANK CARD" << std::endl;
        break;
    case VOUCHER:
        os << "      paid by: VOUCHER" << std::endl;
        break;
    default:
        os << "      paid by: CASH" << std::endl;
    }

    switch (state) {
    case SENT:
        os << " order status: SENT" << std::endl;
        break;
    case ACCEPTED:
        os << " order status: ACCEPTED" << std::endl;
        break;
    case EN_ROUTE:
        os << " order status: EN ROUTE" << std::endl;
        break;
    case DELIVERED:
        os << " order status: DELIVERED" << std::endl;
        break;
    case FAILED:
        os << " order status: FAILED" << std::endl;
        break;
    default:
        os << " order status: UNSENT" << std::endl;
    }

    if (orderedBy != "")
        os << "   ordered by: " << orderedBy << std::endl;
    if (acceptedBy != "")
        os << "  accepted by: " << acceptedBy << std::endl;
    if (deliveredBy != "")
        os << " delivered by: " << deliveredBy << std::endl;

    os << " comment: " << comment << std::endl;

    os << " pizzas in cart: (" << items.size() << ")" << std::endl;
    size_t i = 0;
    for (ItemIter iter = items.begin(); iter != items.end(); ++iter, ++i) {
        os << "  [index: " << i << "] ";
        iter->displayPizza(os);
    }
    os << "-------------------------" << std::endl;
}

/// -------------------- End of Getters --------------------





/// ----------------------- Setters ------------------------

/**
 * @brief Appends a pizza from the global pizzas to the order list
 * @param allItems - points to the List of all the global pizzas
 * @param serialNum - identifies the pizza, which should be appended to order list from global pizzas
 * @exception if there is indexing problem
 */
void Order::addPizza(const int& serial, List<Pizza*>& pizzas) {
    if (serial >= static_cast<int>(pizzas.size()))
        throw std::out_of_range("No pizza found");
    else {
        List<Pizza*>::iterator found = pizzas[serial];
        items.insert(*(*found));
    }
}

/**
 * @brief Adding a topping into a pizza item
 * And increments price of the pizza
 * @exception if there is indexing problem
 */
void Order::addTopping(const size_t& index, const int& serialNumOfTopping, List<Topping*>& toppings) {
    TopIter top = toppings[serialNumOfTopping];
    if (index >= items.size())
        throw std::out_of_range("Overindexing items");
    else if (top == toppings.end())
        throw std::out_of_range("No topping found");
    else {
        ItemIter iter = items[index];
        iter->addTopping(toppings, serialNumOfTopping);
    }
}

/**
 * @brief Simple setter for shipping address
 */
void Order::setShippingAddress(const std::string& sA) {
    shippingAddress = sA;
}

/**
 * @brief Simple setter for payment method
 * accepts a simple int, will cast it
 */
void Order::setPayBy(const int& choice) {
    if ((choice > 2) || (choice < 0))
        throw std::out_of_range("PaymentMethod has 3 enumerated values");
    else
        payBy = static_cast<PaymentMethod>(choice);
}

/**
 * @brief Simple setter for comment
 */
void Order::setComment(const std::string& comment) {
    this->comment = comment;
}

/// -------------------- End of Setters --------------------





/// -------------------- State modifiers -------------------

/**
 * @brief Sets state to SENT, date of sending and sender username
 * @param username - sender's username
 */
void Order::sendOrder(const std::string& username) {
    state = SENT;
    sentDate = std::time(0);
    orderedBy = username;
}

/**
 * @brief Sets state to ACCEPTED, ready for delivery, accepter's username
 * @param username - admin's username that accepted order
 */
void Order::acceptOrder(const std::string& username) {
    state = ACCEPTED;
    acceptedBy = username;
}

/**
 * @brief Sets state to EN_ROUTE, deliverer's username
 * @param username - deliverer's username
 */
void Order::deliverOrder(const std::string& username) {
    state = EN_ROUTE;
    deliveredBy = username;
}

/**
 * @brief Sets state to DELIVERED or FAILED, delivery arrival's date
 * @param success - true if successful delivery, false if failed
 * @param comment - sets comment
 */
void Order::closeOrder(bool success, const std::string& comment) {
    if (success) {
        state = DELIVERED;
        deliveredDate = std::time(0);
    }
    else
        state = FAILED;
    this->comment += "\n" + comment;
}

/// -------------------------------------------------------



/**
 * @brief Comparator for orders
 * @return true if their ids are identical (it's their unique key)
 * @see List<T>.find(const T& data)
 */
bool Order::operator==(const Order& rhs) const {
    return id == rhs.getId();
}

/**
 * @brief Cloning method
 * @return a pointer with clone object
 */
Order* Order::clone() const {
    return new Order(*this);
}
