/**
 * @file topping.h
 */

#ifndef TOPPING_H
#define TOPPING_H

#include <iostream>
#include <string>

class Topping {
    int serialNum;
    std::string name;
    double price;
public:
    void save(std::ostream& os) const;
    void load(std::istream& is) const;
    Topping():
        serialNum(0), name(""), price(0) { }
    Topping(int serialNum, std::string name, double price):
        serialNum(serialNum), name(name), price(price) { }

    std::string getName() const;
    int getSerialNum() const;
    bool operator==(Topping& rhs) const;
};

#endif // TOPPING_H
