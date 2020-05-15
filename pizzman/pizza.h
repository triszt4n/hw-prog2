/**
 * @file pizza.h
 * @brief Pizza class declaration
 */

#ifndef PIZZA_H
#define PIZZA_H

#include <iostream>
#include <string>
#include "list.hpp"
#include "topping.h"

/**
 * @class Pizza
 * @brief Model for pizza
 * @see private data items is a List of Toppings
 */
class Pizza {
    int serialNum;
    std::string name;
    int price;
    List<Topping> items;
public:
    void save(std::ostream& os) const;
    bool load(std::istream& is, List<Topping*>& toppings);

    Pizza(const int& serialNum = -1, const std::string& name = "", const int& price = 0):
        serialNum(serialNum), name(name), price(price) { }
    Pizza(const Pizza& pizza);
    Pizza& operator=(const Pizza& rhs);

    int getSerialNum() const;
    std::string getName() const;
    int getPrice() const;

    void displayItems(std::ostream& os) const;
    void displayPizza(std::ostream& os) const;
    void writeItems(std::ostream& os) const;

    friend void copyItems(const Pizza& pizzaSource, Pizza& pizzaDest);

    bool addTopping(List<Topping*>& toppings, const int& serial);
    void setPrice(const int& p);

    bool operator==(const Pizza& rhs) const;
    Pizza* clone() const;
};

/**
 * @brief loading up pizzas with data from give file
 * @return true if loading was successful
 */
bool loadPizzas(List<Pizza*>& pizzas, List<Topping*>& toppings, std::istream& is);

#endif // PIZZA_H
