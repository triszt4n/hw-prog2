/**
 * @file customer.h
 * @brief Customer class declaration
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include "profile.h"

/**
 * @class Customer
 * @brief Child class of a Profile, defines a customer's attributes
 */
class Customer: public Profile {
    std::string address;
    std::string mobile;
public:
    Customer(): Profile("DUMMY", "", ""), address(""), mobile("") { }
    Customer(std::string username, std::string pw = "", std::string name = "", std::string addr = "", std::string mob = ""):
        Profile(username, pw, name), address(addr), mobile(mob) { }

    std::string getAddress();
    void setMobile(const std::string& mob);
    void setAddress(const std::string& addr);

    Rights verifyLogin(const std::string& username, const std::string& pw) const;

    void greetings(std::ostream& os) const;

    void save(std::ostream& os) const;
    void load(std::istream& is);

    Customer* clone() const {
        return new Customer(username, password, name, address, mobile);
    }
};

#endif // CUSTOMER_H
