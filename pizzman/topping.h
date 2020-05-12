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
    int price;
public:
    void save(std::ostream& os);
    bool load(std::istream& is);
    Topping(const int& serialNum = -1, const std::string& name = "", const int& price = 0):
        serialNum(serialNum), name(name), price(price) { }
    Topping(const Topping& topping) {
        serialNum = topping.getSerialNum();
        name = topping.getName();
        price = topping.getPrice();
    }

    std::string getName() const;
    int getSerialNum() const;
    int getPrice() const;
    bool operator==(const Topping& rhs) const;
    Topping* clone() const;
    //std::string getNameIfSameSerial(const int& serial) const;
};

#endif // TOPPING_H
