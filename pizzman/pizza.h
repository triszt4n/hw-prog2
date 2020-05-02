/**
 * @file pizza.h
 */

#ifndef PIZZA_H
#define PIZZA_H

#include <iostream>
#include <string>
#include "list.hpp"
#include "topping.h"

class Pizza {
    int serialNum;
    std::string name;
    List<Topping> toppings;
    double price;
public:
    void save(std::ostream& os) const;
    void load(std::istream& is) const;

    Pizza():
        serialNum(0), name(""), price(0) { }
    Pizza(int serialNum, std::string name, double price):
        serialNum(serialNum), name(name), price(price) { }

    //Pizza(Pizza& pizza); -- MIGHT NOT NEED IT

    int getSerialNum() const;

    std::string toString() const; ///< Used by Order, to display the order itself...

    void addTopping(Topping& topping);
    void setPrice(double p);

    bool operator==(Pizza& rhs) const;
};

#endif // PIZZA_H
