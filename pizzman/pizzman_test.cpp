/**
 * @file pizzman_test.cpp
 * @brief Testing the main functions of the most important modules
 */

#include <iostream>
#include "admin.h"
#include "customer.h"
#include "deliverer.h"
#include "list.hpp"
#include "order.h"
#include "pizza.h"
#include "profile_handler.h"
#include "topping.h"

using namespace std;

///Testing main methods of class Order
void testOrder() {
    ///What the Customer could do with one Order

    ///What the Admin could do with one Order

    ///What the Deliverer could do with one Order

}

///Testing class List with Pizza and Topping
void testList() {
    /*List<Topping> myList;
	List<Topping>::iterator i1;
    for (i1 = myList.begin(); i1 != myList.end(); ++i1) {
        cout << " " << (*i1).getName();
    }
    cout << endl;

    List<Pizza> ls;
	ls.insert(Pizza(1, "Hungarian", 1200));
	ls.insert(Pizza(2, "Hawaii", 1400));
	ls.insert(Pizza(3, "Margharita", 1000));
    ///Printing out...*/
}

///Testing the process of one order
void testProcess() {

}

///Testing of reading Profiles from file and verifyLogin on them
//This is mainly the test of the heterogeneous collection of Profiles
void testProfile() {

}

///All the other functions of the program should be manually tested in the live version

int main()
{
    cout << "Hello world!" << endl;

    testOrder();
    testList();
    testProcess();
    testProfile();

    return 0;
}
