/**
 * @file order.h
 * @brief Order class declaration
 */

#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <ctime>
#include "pizza.h"
#include "list.hpp"


/**
 * @enum OrderState
 * @brief Enumerator for defining the state of the order
 */
enum OrderState {
    UNSENT,
	SENT,
	ACCEPTED,
	EN_ROUTE,
	DELIVERED,
	FAILED
};

/**
 * @enum Rights
 * @brief Enumerator for defining the payment method of the order
 */
enum PaymentMethod {
    CASH,
	BANK_CARD,
	VOUCHER
};


/**
 * @class Order
 * @brief Model for order
 * @see private data items is a List of Pizza
 */
class Order {
    int id;
    std::string orderedBy;      ///<
    std::string acceptedBy;     ///< usernames of people
    std::string deliveredBy;    ///<
    List<Pizza> items;
    std::string shippingAddress;
    PaymentMethod payBy;
    time_t sentDate;
    time_t deliveredDate;
    OrderState state;
    std::string comment;
public:
    Order(int id = -1, std::string orderedBy = "", std::string acceptedBy = "",
          std::string deliveredBy = "", std::string shippingAddress = "", PaymentMethod payBy = CASH,
          time_t sentDate = 0, time_t deliveredDate = 0, OrderState state = UNSENT, std::string comment = ""):
        id(id), orderedBy(orderedBy), acceptedBy(acceptedBy), deliveredBy(deliveredBy),
        shippingAddress(shippingAddress), payBy(payBy), sentDate(sentDate),
        deliveredDate(deliveredDate), state(state), comment(comment) { }
    Order(const Order& order);
    Order& operator=(const Order& order);
    friend void copyItems(const Order& orderSource, Order& orderDest);

    ///persistence
    void save(std::ostream& os) const;
    bool load(std::istream& is, List<Topping*>& toppings);

    ///getters
    int getId() const;
    std::string getOrderedBy() const;
    std::string getAcceptedBy() const;
    std::string getDeliveredBy() const;
    std::string getShippingAddress() const;
    PaymentMethod getPayBy() const;
    time_t getSentDate() const;
    time_t getDeliveredDate() const;
    OrderState getState() const;
    std::string getComment() const;
    void displayOrder(std::ostream& os) const;

    ///setters
    void addPizza(const int& serialNum, List<Pizza*>& pizzas);
    void addTopping(const size_t& index, const int& serialNumOfTopping, List<Topping*>& toppings);
    void setShippingAddress(const std::string& sA);
    void setPayBy(const int& choice);
    void setComment(const std::string& comment);

    ///state modifiers
    void sendOrder(const std::string& username);
    void acceptOrder(const std::string& username);
    void deliverOrder(const std::string& username);
    void closeOrder(bool success, const std::string& comment = "");

    bool operator==(const Order& rhs) const;
    Order* clone() const;
};

#endif // ORDER_H
