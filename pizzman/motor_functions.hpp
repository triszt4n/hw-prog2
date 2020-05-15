/**
 * \file motor_functions.hpp
 * @brief Database motor functions migrated from main
 * Contains: login and register functions as well
 */

#ifndef MOTOR_FUNCTIONS_H
#define MOTOR_FUNCTIONS_H

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
using std::ofstream;

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
 * @typedef ProfIter
 * @brief Used for profiles (heterogeneous store) list's iterator
 */
typedef List<Profile*>::iterator ProfIter;




/**
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

    Customer dummy = Customer(username);    ///< It's not relevant what type of Profile we create, as
                                            ///< operator== work with all kind of Profiles' usernames.
                                            ///< @see profile.h operator==() and list.hpp find_p()
    ProfIter found = profiles.find_p(&dummy);
    if (found == profiles.end()) {
        return NULL;
    }
    else {
        userRights = (*found)->verifyLogin(username, pw);
        return *found;
    }
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
 * @brief Loading up toppings with data from give file
 * @return true if no fatal error at loading
 */
inline bool preloadToppings(List<Topping*>& toppings, const string& fileName) {
    ifstream is;
    is.open(fileName);
    if (!is) {
        cerr << "\n------\nNOTE: No file found: \"" << fileName << "\"\n------\n\n";
        is.close();
        return true;
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
 * @brief Loading up pizzas with data from given file
 * @return true if no fatal error at loading
 * @see pizza.h for loadPizzas()
 */
bool preloadPizzas(List<Pizza*>& pizzas, List<Topping*>& toppings, const string& fileName) {
    ifstream is;
    is.open(fileName);
    if (!is) {
        cerr << "\n------\nNOTE: No file found: \"" << fileName << "\"\n------\n\n";
        is.close();
        return true;
    }

    loadPizzas(pizzas, toppings, is);     ///< @see source: pizza.h

    is.close();
    return true;
}

/**
 * @brief Loading up orders with data from give file
 * @return true if no fatal error at loading
 */
bool preloadOrders(List<Order*>& orders, List<Topping*>& toppings, const string& fileName) {
    ifstream is;
    is.open(fileName);
    if (!is) {
        cerr << "\n------\nNOTE: No file found: \"" << fileName << "\"\n------\n\n";
        is.close();
        return true;
    }

    size_t inputNum;
    (is >> inputNum).ignore(1);

    for (size_t i = 0; i < inputNum; ++i) {
        Order inputOrder;
        bool canPut = inputOrder.load(is, toppings);
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
    for (typename List<T>::iterator iter = items.begin(); iter != items.end(); ++iter)
        (*iter)->save(os);
}

/**
 * @brief frees up space of T list
 */
template<typename T>
void freeList(List<T>& items) {
    for (typename List<T>::iterator iter = items.begin(); iter != items.end(); ++iter)
        delete *iter;
}

#endif // MOTOR_FUNCTIONS_H
