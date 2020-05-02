/**
 * @file admin.h
 */

#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <iostream>
#include "profile.h"

class Admin: public Profile {
public:
    Admin(std::string username, std::string pw, std::string name):
        Profile(username, pw, name) { }

    Rights verifyLogin(std::string username, std::string pw) const;
    void save(std::ostream& os) const;
    void load(std::istream& is) const;

    Admin* clone() const {
        return new Admin(this->username, this->password, this->name);
    }
};

#endif // ADMIN_H
