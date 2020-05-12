#ifndef MOTOR_FUNCTIONS_H
#define MOTOR_FUNCTIONS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>

using std::endl;
using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::ifstream;
using std::ofstream;

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

/**
 * @fn regCustomer
 * @brief registers customer
 * @return true if registration was a success
 */
inline bool regCustomer(List<Profile*>& profiles) {
    string username, pw, name, address, mobile;
    cout << "> username [required]: ";
    getline(cin, username);
    cout << "> password [required]: ";
    getline(cin, pw);
    cout << "> name [required]: ";
    getline(cin, name);
    cout << "> address: ";
    getline(cin, address);
    cout << "> mobile [required]: ";
    getline(cin, mobile);

    if (username == "" || pw == "" || name == "" || mobile == "") {
        cout << "\n------\nERROR: Registration failed\nInvalid input\n------\n\n";
        return false;
    }
    else {
        for (List<Profile*>::iterator iter = profiles.begin(); iter != profiles.end(); ++iter) {
            if ((*iter)->getUsername() == username) {
                cout << "\n------\nERROR: Registration failed\nUsername taken\n------\n\n";
                return false;
            }
        }
        profiles.insert(new Customer(username, pw, name, address, mobile));
        return true;
    }
}

/**
 * @fn login
 * @brief logs in user --> passes data into parameters given
 * @param userLoggedIn - will get the user profile that logged in
 * @param userRights - will get the Rights of user logged in
 */
inline Profile* login(Rights& userRights, List<Profile*>& profiles) {
    string username, pw;
    cout << "> username: ";
    getline(cin, username);
    cout << "> password: ";
    getline(cin, pw);

    if (username == "" || pw == "") {
        cout << "\n------\nERROR: Invalid input\n------\n\n";
        userRights = NOT_MATCHING;
        return NULL;
    }

    Profile* foundPointer;
    for (List<Profile*>::iterator iter = profiles.begin(); iter != profiles.end(); ++iter) {
        Rights tempRights = (*iter)->verifyLogin(username, pw);
        if (tempRights != NOT_MATCHING) {
            userRights = tempRights;
            foundPointer = (*iter);
        }
    }
    return foundPointer; ///< has to be discussed
}

/**
 * @brief loading profiles into Profile* type heterogeneous store (list)
 * @return true if loading was successful
 */
inline bool preloadProfiles(List<Profile*>& profiles, const string& fileName) {
    ProfileHandler profileHandler;
    profileHandler.setPrototypes();

    ifstream is;
    is.open(fileName);
    if (!is) {
        cerr << "\n------\nERROR: No file found: \"" << fileName << "\"\n------\n\n";
        is.close();
        return false;
    }

    size_t inputNum;
    (is >> inputNum).ignore(1);

    for (size_t i = 0; i < inputNum; ++i) {
        Profile* inputProfile = profileHandler.loadOne(is);
        profiles.insert(inputProfile);
    }
    is.close();

    profileHandler.erasePrototypes();
    return true;
}

/**
 * @brief loading up toppings with data from give file
 * @return true if loading was successful
 */
inline bool preloadToppings(List<Topping*>& toppings, const string& fileName) {
    ifstream is;
    is.open(fileName);
    if (!is) {
        cerr << "\n------\nERROR: No file found: \"" << fileName << "\"\n------\n\n";
        is.close();
        return false;
    }

    size_t inputNum;
    (is >> inputNum).ignore(1);

    for (size_t i = 0; i < inputNum; ++i) {
        Topping inputTopping;
        bool canPut = inputTopping.load(is);
        if (canPut)
            toppings.insert(inputTopping.clone());
    }

    is.close();
    return true;
}

/**
 * @brief preloading pizzas with data from given file
 * @return true if loading was successful
 */
bool preloadPizzas(List<Pizza*>& pizzas, const string& fileName) {
    ifstream is;
    is.open(fileName);
    if (!is) {
        cerr << "\n------\nERROR: No file found: \"" << fileName << "\"\n------\n\n";
        is.close();
        return false;
    }

    loadPizzas(pizzas, is); /// source: pizza.h

    is.close();
    return true;
}

/**
 * @brief loading up orders with data from give file
 * @return true if loading was successful
 */
bool preloadOrders(List<Order*>& orders, const string& fileName) {
    ifstream is;
    is.open(fileName);
    if (!is) {
        cerr << "\n------\nERROR: No file found: \"" << fileName << "\"\n------\n\n";
        is.close();
        return false;
    }

    size_t inputNum;
    (is >> inputNum).ignore(1);

    for (size_t i = 0; i < inputNum; ++i) {
        Order inputOrder;
        bool canPut = inputOrder.load(is);
        if (canPut)
            orders.insert(inputOrder.clone());
    }

    is.close();
    return true;
}

/**
 * @brief saves all items of T list
 */
template<typename T>
void saveList(List<T>& items, const string& fileName) {
    ofstream os(fileName);

    os << items.size() << endl;
    for (typename List<T>::iterator iter = items.begin(); iter != items.end(); ++iter) {
        std::cout << "saving: " << (*iter)->getName() << std::endl; /// DEBUG
        (*iter)->save(os);
    }
}

/**
 * @brief frees up space of T list
 */
template<typename T>
void freeList(List<T>& items) {
    for (typename List<T>::iterator iter = items.begin(); iter != items.end(); ++iter) {
        std::cout << "deleting: " << (*iter)->getName() << std::endl; /// DEBUG
        delete *iter;
    }
}

#endif // MOTOR_FUNCTIONS_H
