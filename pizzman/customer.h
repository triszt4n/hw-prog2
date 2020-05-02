/**
 * @file customer.h
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include "profile.h"

class Customer: public Profile {
    std::string address;
    std::string mobile;
public:
    Customer(std::string username, std::string pw, std::string name, std::string addr, std::string mob):
        Profile(username, pw, name), address(addr), mobile(mob) { }

    std::string getAddress();
    Rights verifyLogin(std::string username, std::string pw) const;
    void save(std::ostream& os) const;
    void load(std::istream& is) const;

    Customer* clone() const {
        return new Customer(this->username, this->password, this->name, this->address, this->mobile);
    }
};

#endif // CUSTOMER_H
