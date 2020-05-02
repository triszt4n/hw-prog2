/**
 * @file order.h
 */

#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <ctime>
#include "pizza.h"
#include "list.hpp"

enum OrderState {
    UNSENT,
	SENT,
	ACCEPTED,
	EN_ROUTE,
	DELIVERED,
	FAILED
};

enum PaymentMethod {
    CASH,
	BANK_CARD,
	VOUCHER
};

class Order {
    int id;
    std::string orderedBy;      ///<
    std::string acceptedBy;     ///< usernames of people
    std::string deliveredBy;    ///<
    List<Pizza> items;
    std::string shippingAddress;
    PaymentMethod payBy;
    time_t* sentDate;
    time_t* deliveredDate;
    OrderState state;
    std::string comment;
public:
    Order(int id, std::string orderedBy): id(id), orderedBy(orderedBy), acceptedBy(""), deliveredBy(""),
        shippingAddress(""), payBy(CASH), sentDate(NULL), deliveredDate(NULL), state(UNSENT), comment("") { }

    void save(std::ostream& os) const;
    void load(std::istream& is) const;

    ///getters
    int getId() const;
    std::string getOrdedBy() const;
    std::string getAcceptedBy() const;
    std::string getDeliveredBy() const;
    OrderState getState() const;

    void displayOrder(std::ostream& os) const;

    ///setters:
    void appendPizza(int serialNum);
    void addTopping(int index, int serialNumOfTopping);
    void setShippingAddress(std::string sA);
    void setPayBy(int choice);
    void setComment(std::string comment);

    ///Commands to change state of order
    bool sendOrder(std::string username);
    bool acceptOrder(std::string username);
    bool deliverOrder(std::string username);
    bool closeOrder(std::string username, bool success);

    bool operator==(Order& rhs) const;
};

#endif // ORDER_H
