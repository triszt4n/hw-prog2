/**
 * \file menus.hpp
 * @brief Menu functions migrated from main
 */

#ifndef MENUS_H
#define MENUS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <stdexcept>

using std::endl;
using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::ifstream;
using std::exception;

#include "admin.h"
#include "profile.h"
#include "customer.h"
#include "deliverer.h"
#include "list.hpp"
#include "pizza.h"
#include "order.h"
#include "topping.h"

/// Frequently used iterators redefined to be shorter
/**
 * @typedef OrdIter
 * @brief Used for orders (pointer store) list's iterator
 */
typedef List<Order*>::iterator OrdIter;

/**
 * @typedef TopIter
 * @brief Used for toppings (pointer store) list's iterator
 */
typedef List<Topping*>::iterator TopIter;

/**
 * @typedef PizzaIter
 * @brief Used for pizzas (pointer store) list's iterator
 */
typedef List<Pizza*>::iterator PizzaIter;


/**
 * @brief A procedure pulled out
 * Lists orders onto std::cout
 * @param state - filters for given state orders, if left UNSENT, list all
 */
void listOrdersWhereState(List<Order*>& orders, const OrderState& state = UNSENT) {
    cout << "\n------\nList of the queried orders:" << endl;
    for (OrdIter iter = orders.begin(); iter != orders.end(); ++iter) {
        if ((state == UNSENT) || ((*iter)->getState() == state))
            (*iter)->displayOrder(cout);
    }
    cout << "------" << endl << endl;
}

/**
 * @brief A procedure pulled out
 * Lists orders onto std::cout
 * @param deliverer - filters for deliverer
 */
void listOrdersWhereDeliverer(List<Order*>& orders, const std::string& deliverer) {
    cout << "\n------\nList of the queried orders:" << endl;
    for (OrdIter iter = orders.begin(); iter != orders.end(); ++iter) {
        if ((*iter)->getDeliveredBy() == deliverer)
            (*iter)->displayOrder(cout);
    }
    cout << "------" << endl << endl;
}

/**
 * @brief A procedure pulled out
 * Lists orders onto std::cout
 * @param orderer - filters for orderer
 */
void listOrdersWhereOrderer(List<Order*>& orders, const std::string& orderer) {
    cout << "\n------\nList of the queried orders:" << endl;
    for (OrdIter iter = orders.begin(); iter != orders.end(); ++iter) {
        if ((*iter)->getOrderedBy() == orderer)
            (*iter)->displayOrder(cout);
    }
    cout << "------" << endl << endl;
}

/**
 * @brief A procedure pulled out
 * Lists all the offered pizzas onto std::cout
 */
void listPizzaOffers(List<Pizza*>& pizzas) {
    cout << "\n------\nList of the pizza offers:" << endl;
    for (PizzaIter iter = pizzas.begin(); iter != pizzas.end(); ++iter) {
        (*iter)->displayPizza(cout);
    }
    cout << "------" << endl << endl;
}

/**
 * @brief A procedure pulled out
 * Lists all the toppings onto std::cout
 */
void listToppings(List<Topping*>& toppings) {
    cout << "\n------\nList of the toppings:" << endl;
    for (TopIter iter = toppings.begin(); iter != toppings.end(); ++iter) {
        (*iter)->displayTopping(cout, true);
    }
    cout << "------" << endl << endl;
}






/**
 * @brief A procedure pulled out
 * Admin's and Deliverer's option to modify state of order
 */
void setOrderDeliveredOrFailed(List<Order*>& orders, bool isSuccess) {
    int serial; string comment;

    cout << "> order's id: ";
    cin >> serial; cin.ignore(1);
    cout << "> any comment: ";
    getline(cin, comment);

    try {
        OrdIter found = orders[serial];

        if (found != orders.end()) {
            (*found)->closeOrder(isSuccess, comment);
            cout << "\n------\nUpdated order status\n------\n\n";
        }
        else {
            cout << "\n------\nERROR: Couldn't find order with id\n------\n\n";
        }
    }
    catch (exception& e) {
        cout << "\n------\nERROR: " << e.what() << "\n------\n\n";
    }
}

/**
 * @brief A procedure pulled out
 * Admin's and Deliverer's option to modify state of order
 */
void setOrderEnRoute(List<Order*>& orders, const std::string& deliverer = "") {
    int serial;
    string deliveredBy = deliverer;

    cout << "> order's id: ";
    cin >> serial; cin.ignore(1);

    if (deliverer == "") {
        cout << "> delivered by: ";
        getline(cin, deliveredBy);
    }

    try {
        OrdIter found = orders[serial];

        if (found != orders.end()) {
            (*found)->deliverOrder(deliveredBy);
            cout << "\n------\nUpdated order status\n------\n\n";
        }
        else {
            cout << "\n------\nERROR: Couldn't find order with id\n------\n\n";
        }
    }
    catch (exception& e) {
        cout << "\n------\nERROR: " << e.what() << "\n------\n\n";
    }
}

/**
 * @brief A procedure pulled out
 * Admin's option to modify state of order
 */
void setOrderAccepted(List<Order*>& orders, const std::string& accepter) {
    int serial;

    cout << "> order's id: ";
    cin >> serial; cin.ignore(1);

    try {
        OrdIter found = orders[serial];

        if (found != orders.end()) {
            (*found)->acceptOrder(accepter);
            cout << "\n------\nUpdated order status\n------\n\n";
        }
        else {
            cout << "\n------\nERROR: Couldn't find order with id\n------\n\n";
        }
    }
    catch (exception& e) {
        cout << "\n------\nERROR: " << e.what() << "\n------\n\n";
    }
}






/**
 * @brief A procedure pulled out
 * Admin's option to create a new topping
 */
void createTopping(List<Topping*>& toppings) {
    string name;
    int price, serial;

    cout << "> name of new: ";
    getline(cin, name);
    cout << "> price: ";
    cin >> price; cin.ignore(1);
    if ((name == "") || (price < 0)) {
        cout << "\n------\nERROR: Invalid input\nCouldn't create topping\n------\n\n";
    }
    else {
        serial = toppings.size();
        toppings.insert(new Topping(serial, name, price));
        cout << "\n------\nCreated new topping\nUpdated toppings\n------\n\n";
    }
}

/**
 * @brief A procedure pulled out
 * Admin's option to create a new pizza
 */
void createPizza(List<Topping*>& toppings, List<Pizza*>& pizzas) {
    string name;
    int price, topNum, serial;

    cout << "> name of new: ";
    getline(cin, name);
    cout << "> price: ";
    cin >> price; cin.ignore(1);
    cout << "> number of toppings: ";
    cin >> topNum; cin.ignore(1);

    if ((name == "") || (price < 0) || (topNum <= 0)) {
        cout << "\n------\nERROR: Invalid input\nCouldn't create topping\n------\n\n";
    }
    else {
        Pizza pizza = Pizza(pizzas.size(), name, price);

        for (int i = 0; i < topNum; ++i) {
            cout << "> topping #" << i+1 << "'s id: ";
            cin >> serial; cin.ignore(1);

            bool success = pizza.addTopping(toppings, serial);

            if (!success) {
                cout << "\n------\nInvalid input, try again\n------\n\n";
                --i;
            }
        }

        pizzas.insert(pizza.clone());
        cout << "\n------\nCreated new pizza\nUpdated pizza offers\n------\n\n";
    }
}






/**
 * @brief A procedure pulled out
 * Realizes an ordering procedure
 */
void startOrder(List<Topping*>& toppings, List<Pizza*>& pizzas, List<Order*>& orders, const string& username, const string& shippingAddress = "") {
    bool quit = false;
    Order order = Order(orders.size(), username);
    order.setShippingAddress(shippingAddress);

    do {
        string choice;
        cout << endl << "Assembling an order" << endl;
        order.displayOrder(cout);
        cout << "Choose an option" << endl;
        cout << "[ 1] List all the pizza offers" << endl;
        cout << "[ 2] List all the toppings" << endl;
        cout << "[ 3] Add pizza from offers" << endl;
        cout << "[ 4] Add topping to pizza in cart" << endl;
        cout << "[ 5] Change shipping address" << endl;
        cout << "[ 6] Change payment method" << endl;
        cout << "[ 7] Add comment" << endl;
        cout << "[ 8] Send order" << endl;
        cout << "[ 9] Cancel order" << endl;
        cout << "> ";
        cin >> choice; cin.ignore(1);

        string tempString;
        int serial, index;
        switch (atoi(choice.c_str())) {
        case 1:
            listPizzaOffers(pizzas);
            break;
        case 2:
            listToppings(toppings);
            break;
        case 3:
            cout << "> pizza's id: ";
            cin >> serial; cin.ignore(1);
            try {
                order.addPizza(serial, pizzas);
                cout << "\n------\nOrder updated: added pizza\n------\n\n";
            }
            catch (exception& e) {
                cout << "\n------\nERROR: " << e.what() << "\n------\n\n";
            }
            break;
        case 4:
            cout << "> pizza's index: ";
            cin >> index; cin.ignore(1);
            cout << "> topping's id: ";
            cin >> serial; cin.ignore(1);
            try {
                order.addTopping(index, serial, toppings);
                cout << "\n------\nOrder updated: added plus topping\n------\n\n";
            }
            catch (exception& e) {
                cout << "\n------\nERROR: " << e.what() << "\n------\n\n";
            }
            break;
        case 5:
            cout << "> new address: ";
            getline(cin, tempString);
            if (tempString == "")
                cout << "\n------\nERROR: Please enter a real address\n------\n\n";
            else {
                order.setShippingAddress(tempString);
                cout << "\n------\nOrder updated: set address\n------\n\n";
            }
            break;
        case 6:
            cout << "[ 0] CASH" << endl;
            cout << "[ 1] BANK CARD" << endl;
            cout << "[ 2] VOUCHER" << endl;
            cout << "> ";
            cin >> index; cin.ignore(1);
            try {
                order.setPayBy(index);
                cout << "\n------\nOrder updated: set payment method\n------\n\n";
            }
            catch (exception& e) {
                cout << "\n------\nERROR: " << e.what() << "\n------\n\n";
            }
            break;
        case 7:
            cout << "> add comment: ";
            getline(cin, tempString);
            order.setComment(tempString);
            cout << "\n------\nOrder updated: added plus topping\n------\n\n";
            break;
        case 8:
            order.sendOrder(username);
            orders.insert(order.clone());
            cout << "\n------\nOrder updated: order sent!\n------\n\n";
            quit = true;
        case 9:
            quit = true;
            break;
        default:
            cout << "\n------\nERROR: Unexpected input\n------\n\n";
        }
    } while (!quit);
}






/**
 * @brief Shows and controls menu for a Customer
 * @return true if option logging out is chosen
 */
bool menuCustomer(Customer* user, List<Topping*>& toppings, List<Pizza*>& pizzas, List<Order*>& orders) {
    string choice;
    bool quit = false;

    user->greetings(cout);
    cout << "Choose an action as Customer" << endl;
    cout << "[ 1] List my orders and their status" << endl;
    cout << "[ 2] Set my address" << endl;
    cout << "[ 3] Set my mobile" << endl;
    cout << "[ 4] Start an order" << endl;
    cout << "[11] Log out" << endl;
    cout << "> ";
    cin >> choice; cin.ignore(1);

    string tempString;
    switch (atoi(choice.c_str())) {
    case 1:
        listOrdersWhereOrderer(orders, user->getUsername());
        break;
    case 2:
        cout << "> new address: ";
        getline(cin, tempString);
        user->setAddress(tempString);
        cout << "\n------\nUpdated address\n------\n\n";
        break;
    case 3:
        cout << "> new mobile: ";
        getline(cin,tempString);
        if (tempString == "")
            cout << "\n------\nERROR: Enter a phone number that is existent\nWe'll reach out to you through this number\n------\n\n";
        else {
            user->setMobile(tempString);
            cout << "\n------\nUpdated mobile phone number\n------\n\n";
        }
        break;
    case 4:
        startOrder(toppings, pizzas, orders, user->getUsername(), user->getAddress());
        break;
    case 11:
        quit = true;
        break;
    default:
        cout << "\n------\nERROR: Unexpected input\n------\n\n";
    }
    return quit;
}

/**
 * @brief Shows and controls menu for an Administrator
 * @return true if option logging out is chosen
 */
bool menuAdmin(Admin* user, List<Topping*>& toppings, List<Pizza*>& pizzas, List<Order*>& orders) {
    string choice;
    bool quit = false;

    user->greetings(cout);
    cout << "Choose an action as Administrator" << endl;
    cout << "[ 1] List all the pizza offers" << endl;
    cout << "[ 2] List all the toppings" << endl;
    cout << "[ 3] List all the orders" << endl;
    cout << "[ 4] Start an order" << endl;
    cout << "[ 5] Set an order as \"accepted\"" << endl;
    cout << "[ 6] Set an order as \"en route\"" << endl;
    cout << "[ 7] Set an order as \"delivered\"" << endl;
    cout << "[ 8] Set an order as \"failed\"" << endl;
    cout << "[ 9] Create a new topping" << endl;
    cout << "[10] Create a new pizza" << endl;
    cout << "[11] Log out" << endl;
    cout << "> ";
    cin >> choice; cin.ignore(1);

    int index;
    switch (atoi(choice.c_str())) {
    case 1:
        listPizzaOffers(pizzas);
        break;
    case 2:
        listToppings(toppings);
        break;
    case 3:
        cout << "[ 0] none" << endl;
        cout << "[ 1] SENT" << endl;
        cout << "[ 2] ACCEPTED" << endl;
        cout << "[ 3] EN_ROUTE" << endl;
        cout << "[ 4] DELIVERED" << endl;
        cout << "[ 5] FAILED" << endl;
        cout << "filter? > ";
        cin >> index; cin.ignore(1);
        listOrdersWhereState(orders, static_cast<OrderState>(index));
        break;
    case 4:
        startOrder(toppings, pizzas, orders, user->getUsername());
        break;
    case 5:
        setOrderAccepted(orders, user->getUsername());
        break;
    case 6:
        setOrderEnRoute(orders);
        break;
    case 7:
        setOrderDeliveredOrFailed(orders, true);
        break;
    case 8:
        setOrderDeliveredOrFailed(orders, false);
        break;
    case 9:
        createTopping(toppings);
        break;
    case 10:
        createPizza(toppings, pizzas);
        break;
    case 11:
        quit = true;
        break;
    default:
        cout << "\n------\nERROR: Unexpected input\n------\n\n";
    }

    return quit;
}

/**
 * @brief Shows and controls menu for a Deliverer
 * @return true if option logging out is chosen
 */
bool menuDeliverer(Deliverer* user, List<Order*>& orders) {
    string choice;
    bool quit = false;

    user->greetings(cout);
    cout << "Choose an action as Deliverer" << endl;
    cout << "[ 1] List all accepted orders" << endl;
    cout << "[ 2] List all orders attached to me" << endl;
    cout << "[ 3] Take an order for delivery" << endl;
    cout << "[ 4] Set an order-delivery as \"delivered\"" << endl;
    cout << "[ 5] Set an order-delivery as \"failed\"" << endl;
    cout << "[11] Log out" << endl;
    cout << "> ";
    cin >> choice; cin.ignore(1);

    switch (atoi(choice.c_str())) {
    case 1:
        listOrdersWhereState(orders, ACCEPTED);
        break;
    case 2:
        listOrdersWhereDeliverer(orders, user->getUsername());
        break;
    case 3:
        setOrderEnRoute(orders, user->getUsername());
        break;
    case 4:
        setOrderDeliveredOrFailed(orders, true);
        break;
    case 5:
        setOrderDeliveredOrFailed(orders, false);
        break;
    case 11:
        quit = true;
        break;
    default:
        cout << "\n------\nERROR: Unexpected input\n------\n\n";
    }
    return quit;
}

#endif // MENUS_H
