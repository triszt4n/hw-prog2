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
    int price;
    List<int> toppingList; ///< Contains serialNums of toppings
    //std::string getToppingName(List<Topping*>& toppings, const int& serial) const;
public:
    void save(std::ostream& os);
    bool load(std::istream& is);

    Pizza(const int& serialNum = -1, const std::string& name = "", const int& price = 0):
        serialNum(serialNum), name(name), price(price) { }
    Pizza(const Pizza& pizza);

    int getSerialNum() const;
    std::string getName() const;
    int getPrice() const;
    void displayToppingList(std::ostream& os, List<Topping*>& toppings) const;
    friend void copyToppingList(const Pizza& pizzaSource, Pizza& pizzaDest);
    friend void copyToppingList(List<int>& toppingListSource, Pizza& pizzaDest);

    void addTopping(const int& toppingSerial, const int& toppingPrice);
    void setPrice(const int& p);

    bool operator==(const Pizza& rhs) const;
    Pizza* clone() const;
};

/**
 * @brief loading up pizzas with data from give file
 * @return true if loading was successful
 */
inline bool loadPizzas(List<Pizza*>& pizzas, std::istream& is) {
    size_t inputNum;
    (is >> inputNum).ignore(1);

    for (size_t i = 0; i < inputNum; ++i) {
        Pizza inputPizza;
        bool canPut = inputPizza.load(is);
        if (canPut)
            pizzas.insert(inputPizza.clone());
    }
    return true;
}

#endif // PIZZA_H
