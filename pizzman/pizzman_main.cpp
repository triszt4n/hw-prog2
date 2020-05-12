/**
 * @file pizzman_main.cpp - Realizing the use of program
 */

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
#include "menus.hpp"

void generateTestingInput() {
    ofstream os("orders01.txt");

    os << 10 << endl;
    time_t now = std::time(0);
    Order order1 = Order(0, "trisztan", "trisztan", "nagy.elod", "Veszprem, Damjanich 4", CASH, now - 100000, now - 90000, DELIVERED, "Alles okay");
    Order order2 = Order(1, "admin", "admin", "nagy.elod", "Veszprem, Laszlo Lajos utca 10", BANK_CARD, now - 1000000, now - 990000, DELIVERED,
                         "Ki volt hulve a pizza, rendelo sokat problemazott");
    Order order3 = Order(2, "chickenapple", "admin", "kisscsillag985", "Veszprem, Haszkovo u. 11/B", VOUCHER, now - 100000, now - 90000, DELIVERED, "");
    Order order4 = Order(3, "trisztan", "", "", "Hold utca 1", BANK_CARD, now - 100000, now - 90000, FAILED,
                         "Rendelo hibas cimet adott, majd vissza is mondta a rendelest");
    Order order5 = Order(4, "momplicated99", "", "", "Buda, Karacs Terez utca 3/A", BANK_CARD, now - 540124, 0, SENT, "");
    Order order6 = Order(5, "asdfgh1024", "trisztan", "", "Godollo, Kisvercse ut SZTK rendelo porta", VOUCHER, now - 234600, 0, ACCEPTED, "");
    Order order7 = Order(6, "trisztan", "trisztan", "kisscsillag985", "Veszprem, Damjanich 4", CASH, now - 100000, now - 90000, EN_ROUTE, "");
    Order order8 = Order(7, "kf19763", "admin", "", "", CASH, now - 100000, now - 90000, FAILED, "Hibas rendeles, admin torolte");
    Order order9 = Order(8, "rattlesn4ke89", "admin", "nagy.elod", "Veszprem, Damjanich 4", CASH, now - 100000, now - 90000, DELIVERED, "");
    Order order10 = Order(9, "rattlesn4ke89", "trisztan", "starsky101", "Veszprem, Damjanich 4", CASH, now - 100000, now - 90000, DELIVERED, "");

    order1.save(os); order2.save(os); order3.save(os); order4.save(os); order5.save(os);
    order6.save(os); order7.save(os); order8.save(os); order9.save(os); order10.save(os);
}

int main()
{
    bool canStart = true;

    generateTestingInput();

    /// Preloading all data from files
    List<Profile*> profiles;
    List<Topping*> toppings;
    List<Pizza*> pizzas;
    List<Order*> orders;
    canStart = preloadProfiles(profiles, "profiles.txt");
    canStart = preloadToppings(toppings, "toppings.txt");
    canStart = preloadPizzas(pizzas, "pizzas.txt");
    Profile* userLoggedIn = NULL;

    /// Main logic
    if (canStart) {
        bool quitCycle, quitApp = false;
        string choice;
        Rights userRights = NOT_MATCHING;

        do {
            quitCycle = false;
            cout << "Welcome to the PIZZMAN management application\nLog in or register" << endl;
            cout << "[1] Log in" << endl;
            cout << "[2] Register" << endl;
            cout << "[3] Quit application" << endl;
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
                    quitCycle = true;
                }
                break;
            case 2:
                if (regCustomer(profiles)) {
                    cout << "\n------\nSuccessful registration\nLog in now\n------\n\n";
                }
                break;
            case 3:
                quitApp = true;
                quitCycle = true;
                break;
            default:
                cout << "\n------\nERROR: Unexpected input\n------\n\n";
            }
        } while (!quitCycle);

        /// After successful login
        while (!quitApp) {
            switch (userRights) {
            case ADMIN:
                quitApp = menuAdmin(dynamic_cast<Admin*>(userLoggedIn), toppings, pizzas, orders);
                break;
            case DEFAULT:
                quitApp = menuCustomer(dynamic_cast<Customer*>(userLoggedIn), toppings, pizzas, orders);
                break;
            case DELIVERER:
                quitApp = menuDeliverer(dynamic_cast<Deliverer*>(userLoggedIn), toppings, pizzas, orders);
                break;
            default:
                quitApp = true;
            }
        }
    }
    else {
        cout << "\n------\nERROR: Could not start up\nError during loading files\n------\n\n";
    }

    /// Saving data into files
    saveList(profiles, "profiles01.txt");
    saveList(toppings, "toppings01.txt");
    saveList(pizzas, "pizzas01.txt");

    /// Freeing up space
    freeList(profiles);
    freeList(toppings);
    freeList(pizzas);
    //delete userLoggedIn;

    return 0;
}
