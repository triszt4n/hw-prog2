/**
 * @file order.cpp
 */

#include "order.h"
#include <cstdlib>
#include <iostream>
#include <string>

void Order::save(std::ostream& os) const {

}

void Order::load(std::istream& is) const {

}


///getters
int Order::getId() const {
    return 0;
}

std::string Order::getOrdedBy() const {
    return 0;
}

std::string Order::getAcceptedBy() const {
    return 0;
}

std::string Order::getDeliveredBy() const {
    return 0;
}

OrderState Order::getState() const {
    return UNSENT;
}


void Order::displayOrder(std::ostream& os) const {

}


///setters:
void Order::appendPizza(int serialNum) {

}

void Order::addTopping(int index, int serialNumOfTopping) {

}

void Order::setShippingAddress(std::string sA) {

}

void Order::setPayBy(int choice) {

}

void Order::setComment(std::string comment) {

}


///Commands to change state of order
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


bool Order::operator==(Order& rhs) const {
    return 0;
}
