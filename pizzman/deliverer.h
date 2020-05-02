/**
 * @file delieverer.h
 */

#ifndef DELIVERER_H
#define DELIVERER_H

#include <string>
#include <iostream>
#include "profile.h"

class Deliverer: public Profile {
public:
    Deliverer(std::string username, std::string pw, std::string name):
        Profile(username, pw, name) { }

    Rights verifyLogin(std::string username, std::string pw) const;
    void save(std::ostream& os) const;
    void load(std::istream& is) const;

    Deliverer* clone() const {
        return new Deliverer(this->username, this->password, this->name);
    }
};

#endif // DELIVERER_H
