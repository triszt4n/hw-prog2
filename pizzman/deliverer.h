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
    Deliverer(): Profile("DUMMY", "", "") { }
    Deliverer(std::string username, std::string pw = "", std::string name = ""):
        Profile(username, pw, name) { }

    Rights verifyLogin(const std::string& username, const std::string& pw) const;
    void greetings(std::ostream& os) const;
    void save(std::ostream& os) const;
    void load(std::istream& is);

    Deliverer* clone() const {
        return new Deliverer(username, password, name);
    }
};

#endif // DELIVERER_H
