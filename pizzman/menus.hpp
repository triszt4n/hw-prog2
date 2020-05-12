#ifndef MENUS_H
#define MENUS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <exception>

using std::endl;
using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::ifstream;
using std::exception;

#include "memtrace.h"
#include "admin.h"
#include "profile.h"
#include "customer.h"
#include "deliverer.h"
#include "list.hpp"
#include "pizza.h"
#include "order.h"
#include "topping.h"
#include "profile_handler.h"
#include "usefulio.hpp"
#include "motor_functions.hpp"

void listOrders(List<Order*>& orders, bool showAll, const OrderState& state = UNSENT) {
    cout << "\n------\nList of the queried orders:" << endl;
    for (List<Order*>::iterator iter = orders.begin(); iter != orders.end(); ++iter) {
        if (showAll || ((*iter)->getState() == state))
            (*iter)->displayOrder(cout);
    }
    cout << "------" << endl << endl;
}

void setOrderDeliveredOrFailed(List<Order*>& orders, bool isSuccess) {
    int serial; string comment;

    cout << "> order's id: ";
    cin >> serial; cin.ignore(1);
    cout << "> any comment: ";
    getline(cin, comment);
    try {
        Order* found = orders[serial];
        found->closeOrder(isSuccess, comment);
        cout << "\n------\nUpdated order status\n------\n\n";
    }
    catch (exception e) {
        cout << "Error at orderId, " << e.what() << endl;
    }
}

void startOrder(List<Topping*>& toppings, List<Pizza*>& pizzas, List<Order*>& orders) {
    /// TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //HARD START_ORDER LOGIKA, SOK ELÁGAZÁS, SOK SWITCH, TALÁN EGY NAGY WHILE ÉS A VÉGÉN SEND
}

bool menuCustomer(Customer* user, List<Topping*>& toppings, List<Pizza*>& pizzas, List<Order*>& orders) {
    string choice;
    bool quit = false;

    user->greetings(cout);
    cout << "Choose an action as Customer" << endl;
    cout << "[ 1] List my orders and their status" << endl;
    cout << "[ 2] Set my address" << endl;
    cout << "[ 3] Set my mobile" << endl;
    cout << "[ 4] Start an order" << endl;
    cout << "[11] Quit application" << endl;
    cout << "> ";
    cin >> choice; cin.ignore(1);

    string tempString;
    switch (atoi(choice.c_str())) {
    case 1:
        /// TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        break;
    case 2:
        cout << "> new address: ";
        getline(cin, tempString);
        user->setAddress(tempString);
        cout << "\n------\nUpdated address\n------\n\n";
        break;
    case 3:
        cout << "WARNING: Make sure, the entered number is existent, as we will reach to you through this number" << endl;
        cout << "> new mobile: ";
        getline(cin,tempString);
        user->setMobile(tempString);
        cout << "\n------\nUpdated mobile phone number\n------\n\n";
        break;
    case 4:
        startOrder(toppings, pizzas, orders);
        break;
    case 11:
        quit = true;
        break;
    default:
        cout << "\n------\nERROR: Unexpected input\n------\n\n";
    }
    return quit;
}

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
    cout << "[11] Quit application" << endl;
    cout << "> ";
    cin >> choice; cin.ignore(1);

    string name, username, comment;
    int price, topNum, serial;
    List<int> toppingListHelper;

    switch (atoi(choice.c_str())) {
    case 1:
        cout << "\n------\nList of the pizza offers:" << endl;
        for (List<Pizza*>::iterator iter = pizzas.begin(); iter != pizzas.end(); ++iter) {
            cout << "#" << (*iter)->getSerialNum() << " " << (*iter)->getName() << " - " << (*iter)->getPrice() << " Ft" << endl;
            (*iter)->displayToppingList(cout, toppings);
            cout << endl;
        }
        cout << "------" << endl << endl;
        break;
    case 2:
        cout << "\n------\nList of the toppings:" << endl;
        for (List<Topping*>::iterator iter = toppings.begin(); iter != toppings.end(); ++iter) {
            cout << "#" << (*iter)->getSerialNum() << " " << (*iter)->getName() << " - " << (*iter)->getPrice() << " Ft" << endl;
        }
        cout << "------" << endl << endl;
        break;
    case 3:
        listOrders(orders, true);
        break;
    case 4:
        startOrder(toppings, pizzas, orders);
        break;
    case 5:
        cout << "> order's id: ";
        cin >> serial; cin.ignore(1);
        try {
            Order* found = orders[serial];
            found->acceptOrder(user->getUsername());
            cout << "\n------\nUpdated order status\n------\n\n";
        }
        catch (exception e) {
            cout << "Error at orderId, " << e.what() << endl;
        }
        break;
    case 6:
        cout << "> order's id: ";
        cin >> serial; cin.ignore(1);
        cout << "> delivered by: ";
        getline(cin, username);
        try {
            Order* found = orders[serial];
            found->deliverOrder(name);
            cout << "\n------\nUpdated order status\n------\n\n";
        }
        catch (exception e) {
            cout << "Error at orderId, " << e.what() << endl;
        }
        break;
    case 7:
        setOrderDeliveredOrFailed(orders, true);
        break;
    case 8:
        setOrderDeliveredOrFailed(orders, false);
        break;
    case 9:
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
        break;
    case 10:
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
            for (int i = 0; i < topNum; ++i) {
                cout << "> topping #" << i+1 << ": ";
                cin >> serial; cin.ignore(1);
                if ((serial >= 0) && (serial < static_cast<int>(toppings.size()))) {
                    toppingListHelper.insert(serial);
                }
                else {
                    cout << "\n------\nInvalid input, try again\n------\n\n";
                    --i;
                }
            }

            serial = pizzas.size();
            Pizza pizza = Pizza(serial, name, price);
            copyToppingList(toppingListHelper, pizza);
            pizzas.insert(pizza.clone());
            cout << "\n------\nCreated new pizza\nUpdated pizza offers\n------\n\n";
        }
        break;
    case 11:
        quit = true;
        break;
    default:
        cout << "\n------\nERROR: Unexpected input\n------\n\n";
    }

    return quit;
}

bool menuDeliverer(Deliverer* user, List<Topping*>& toppings, List<Pizza*>& pizzas, List<Order*>& orders) {
    string choice;
    bool quit = false;

    user->greetings(cout);
    cout << "Choose an action as Deliverer" << endl;
    cout << "[ 1] List all accepted orders" << endl;
    cout << "[ 2] List all en route orders" << endl;
    cout << "[ 3] Take an order for delivery" << endl;
    cout << "[ 4] Set an order-delivery as \"delivered\"" << endl;
    cout << "[ 5] Set an order-delivery as \"failed\"" << endl;
    cout << "[11] Quit application" << endl;
    cout << "> ";
    cin >> choice; cin.ignore(1);

    int serial;

    switch (atoi(choice.c_str())) {
    case 1:
        listOrders(orders, false, ACCEPTED);
        break;
    case 2:
        listOrders(orders, false, EN_ROUTE);
        break;
    case 3:
        cout << "> order's id: ";
        cin >> serial; cin.ignore(1);
        try {
            Order* found = orders[serial];
            found->deliverOrder(user->getUsername());
            cout << "\n------\nUpdated order status\n------\n\n";
        }
        catch (exception e) {
            cout << "Error at orderId, " << e.what() << endl;
        }
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
