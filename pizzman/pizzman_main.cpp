/**
 * \file pizzman_main.cpp
 * @brief Realizing the use of program and/or testing
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

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

#include "motor_functions.hpp"
#include "menus.hpp"


/// Comment these to run live mode
#define TESTING
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/// The memtrace error comes from catch.hpp when testing :(


#ifndef TESTING
int main()
{
    bool canStart = true;

    /// Preloading all data from files
    List<Profile*> profiles;
    List<Topping*> toppings;
    List<Pizza*> pizzas;
    List<Order*> orders;
    canStart = preloadProfiles(profiles, "profiles.txt");
    canStart = preloadToppings(toppings, "toppings.txt");
    canStart = preloadPizzas(pizzas, toppings, "pizzas.txt");
    canStart = preloadOrders(orders, toppings, "orders.txt");
    Profile* userLoggedIn = NULL;

    /// Main logic
    if (!canStart) {
        cout << "\n------\nERROR: Can't load database - Fatal error\n------\n\n";
    }
    else {
        bool quitApp = false;
        string choice;
        Rights userRights = NOT_MATCHING;

        do {
            cout << "Welcome to the PIZZMAN management application\nLog in or register" << endl;
            cout << "[ 1] Log in" << endl;
            cout << "[ 2] Register" << endl;
            cout << "[ 3] Quit application" << endl;
            cout << "> ";
            cin >> choice; cin.ignore(1);

            switch (atoi(choice.c_str())) {
            case 1:
                userLoggedIn = login(userRights, profiles);
                if (userRights == NOT_MATCHING) {
                    cout << "\n------\nERROR: No match in database\n------\n\n";
                }
                else {
                    cout << "\n------\nSuccessfully logged in\n------\n\n";
                }
                break;
            case 2:
                if (regCustomer(profiles)) {
                    cout << "\n------\nSuccessful registration\nLog in now\n------\n\n";
                }
                break;
            case 3:
                quitApp = true;
                break;
            default:
                cout << "\n------\nERROR: Unexpected input\n------\n\n";
            }

            bool doLogOut = false;
            /// After successful login
            if (userRights != NOT_MATCHING) {
                do {
                    switch (userRights) {
                    case ADMIN:
                        doLogOut = menuAdmin(dynamic_cast<Admin*>(userLoggedIn), toppings, pizzas, orders);
                        break;
                    case DEFAULT:
                        doLogOut = menuCustomer(dynamic_cast<Customer*>(userLoggedIn), toppings, pizzas, orders);
                        break;
                    case DELIVERER:
                        doLogOut = menuDeliverer(dynamic_cast<Deliverer*>(userLoggedIn), orders);
                        break;
                    default:
                        doLogOut = true;
                    }
                } while (!doLogOut);
                cout << "\n------\nLogging out user...\n------\n\n";
                userRights = NOT_MATCHING;
            }
        } while (!quitApp);
    }

    cout << "\n------\nQuitting application...\n------\n\n";

    /// Saving data into files
    saveList(profiles, "profiles.txt");
    saveList(toppings, "toppings.txt");
    saveList(pizzas, "pizzas.txt");
    saveList(orders, "orders.txt");

    /// Freeing up space
    freeList(profiles);
    freeList(toppings);
    freeList(pizzas);
    freeList(orders);

    return 0;
}
#endif // TESTING



#ifdef TESTING

SCENARIO("Lists have size and can be iterated and indexed") {
    GIVEN("List<string> with 5 items") {
        List<std::string> lsStr;

        REQUIRE( lsStr.size() == 0 );

        lsStr.insert("Jennifer");
        lsStr.insert("Clara");
        lsStr.insert("Benjamin");
        lsStr.insert("Shaun");
        lsStr.insert("Murphy");

        REQUIRE( lsStr.size() == 5 );

        WHEN("We iterate through it") {
            std::vector<std::string> results;

            for (List<std::string>::iterator iter = lsStr.begin(); iter != lsStr.end(); ++iter) {
                results.push_back(*iter);
            }

            THEN("We can get the items by indirection") {
                REQUIRE( lsStr.size() == 5 );
                REQUIRE( results.size() == 5 );
                REQUIRE( results[0] == "Jennifer" );
                REQUIRE( results[1] == "Clara" );
                REQUIRE( results[2] == "Benjamin" );
                REQUIRE( results[3] == "Shaun" );
                REQUIRE( results[4] == "Murphy" );
            }
        }

        WHEN("We index it") {
            std::vector<List<std::string>::iterator> results;

            results.push_back(lsStr[0]);
            results.push_back(lsStr[1]);
            results.push_back(lsStr[2]);
            results.push_back(lsStr[3]);
            results.push_back(lsStr[4]);

            REQUIRE_THROWS_AS( lsStr[5], std::out_of_range );
            REQUIRE_THROWS_AS( lsStr[-1], std::out_of_range );
            REQUIRE_THROWS_AS( lsStr[23], std::out_of_range );

            THEN("We can get the items by indirection of iterator") {
                REQUIRE( lsStr.size() == 5 );
                REQUIRE( results.size() == 5 );
                REQUIRE( *(results[0]) == "Jennifer" );
                REQUIRE( *(results[1]) == "Clara" );
                REQUIRE( *(results[2]) == "Benjamin" );
                REQUIRE( *(results[3]) == "Shaun" );
                REQUIRE( *(results[4]) == "Murphy" );

                REQUIRE( results[4] != lsStr.end() );
            }
        }

        WHEN("We add more items") {
            lsStr.insert("Leonard");
            lsStr.insert("Sheldon");

            std::vector<std::string> results;

            for (List<std::string>::iterator iter = lsStr.begin(); iter != lsStr.end(); ++iter) {
                results.push_back(*iter);
            }

            THEN("Size increases, reiterating gets all the new items as well") {
                REQUIRE( lsStr.size() == 7 );
                REQUIRE( results.size() == 7 );
                REQUIRE( results[0] == "Jennifer" );
                REQUIRE( results[1] == "Clara" );
                REQUIRE( results[2] == "Benjamin" );
                REQUIRE( results[3] == "Shaun" );
                REQUIRE( results[4] == "Murphy" );
                REQUIRE( results[5] == "Leonard" );
                REQUIRE( results[6] == "Sheldon" );
            }
        }

        WHEN("We clear the list") {
            lsStr.clear();

            THEN("Size is null again") {
                REQUIRE( lsStr.size() == 0 );
                REQUIRE( lsStr.begin() == lsStr.end() );
                REQUIRE_THROWS_AS( *(lsStr.begin()), std::out_of_range );
                REQUIRE_THROWS_AS( lsStr[0], std::out_of_range );
                REQUIRE_THROWS_AS( lsStr[1], std::out_of_range );
            }
        }
    }

    GIVEN("A List<std::string*> with pointers") {
        List<std::string*> lsStr;

        REQUIRE( lsStr.size() == 0 );
        REQUIRE_THROWS_AS( *(lsStr.begin()) == NULL, std::out_of_range );
        REQUIRE_THROWS_AS( *(lsStr.end()) == NULL, std::out_of_range );

        std::string a1 = "Jennifer";
        std::string a2 = "Barbara";
        std::string a3 = "Abraham";
        lsStr.insert(&a1);
        lsStr.insert(&a2);
        lsStr.insert(&a3);

        REQUIRE( lsStr.size() == 3 );

        std::string a4 = "new Jason";
        std::string a5 = "new Alexandra";
        std::string* p4 = &a4;
        std::string* p5 = &a5;

        lsStr.insert(p4);
        lsStr.insert(p5);

        REQUIRE( lsStr.size() == 5 );

        WHEN("We iterate through it") {
            std::vector<std::string*> results;

            for (List<std::string*>::iterator iter = lsStr.begin(); iter != lsStr.end(); ++iter) {
                results.push_back(*iter);
            }

            THEN("We can get the items by indirection") {
                REQUIRE( lsStr.size() == 5 );
                REQUIRE( results.size() == 5 );
                REQUIRE( results[0] == &a1 );
                REQUIRE( results[1] == &a2 );
                REQUIRE( results[2] == &a3 );
                REQUIRE( *(results[3]) == "new Jason" );
                REQUIRE( *(results[4]) == "new Alexandra" );
            }
        }

        WHEN("We try find_p() on them") {
            std::string p1 = std::string("Gabriel");
            List<std::string*>::iterator p1f = lsStr.find_p(&p1);

            std::string p2 = std::string("Abraham");
            List<std::string*>::iterator p2f = lsStr.find_p(&p2);

            THEN("It finds the one with the same value (not pointer)") {
                REQUIRE( p1f == lsStr.end() );
                REQUIRE_THROWS_AS( *p1f == NULL, std::out_of_range );

                REQUIRE( p2f != lsStr.end() );
                REQUIRE( *p2f == &a3 );
                REQUIRE( *p2f != &p2 );
                REQUIRE( *(*p2f) == "Abraham" );
                REQUIRE( *(*p2f) == a3 );
            }
        }

        WHEN("We change an exterior pointer's value") {
            a1 = "Not Jennifer anymore";

            std::string p3 = std::string("Jennifer");
            List<std::string*>::iterator p3f = lsStr.find_p(&p3);

            THEN("The interior one's value should be changed too") {
                REQUIRE( lsStr.size() == 5 );
                REQUIRE( *(lsStr[0]) == &a1 );
                REQUIRE( *(*(lsStr[0])) == "Not Jennifer anymore" );

                REQUIRE( p3f == lsStr.end() );
                REQUIRE_THROWS_AS( *p3f == NULL, std::out_of_range );
            }
        }

        WHEN("We try indexing them") {
            THEN("We can get the items by indirection of iterator") {
                REQUIRE( lsStr.size() == 5 );

                REQUIRE( *(*(lsStr[0])) == "Jennifer" );
                REQUIRE( *(*(lsStr[1])) == "Barbara" );
                REQUIRE( *(*(lsStr[2])) == "Abraham" );

                REQUIRE( *(lsStr[0]) == &a1 );
                REQUIRE( *(lsStr[1]) == &a2 );
                REQUIRE( *(lsStr[2]) == &a3 );

                REQUIRE_NOTHROW( lsStr[3] );
                REQUIRE_NOTHROW( lsStr[4] );

                REQUIRE_THROWS_AS( lsStr[-1], std::out_of_range );
                REQUIRE_THROWS_AS( lsStr[5], std::out_of_range );
                REQUIRE_THROWS_AS( lsStr[72], std::out_of_range );
            }
        }
    }
}

#endif // CATCH_CONFIG_MAIN
