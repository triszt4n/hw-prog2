/**
 * @file admin.h
 * @brief Admin class declaration
 */

#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <iostream>
#include "profile.h"

/**
 * @class Admin
 * @brief Child class of a Profile, defines an administrator's attributes
 */
class Admin: public Profile {
public:
    Admin(): Profile("DUMMY", "", "") { }
    Admin(const std::string& username, const std::string& pw = "", const std::string& name = ""):
        Profile(username, pw, name) { }

    Rights verifyLogin(const std::string& username, const std::string& pw) const;

    void greetings(std::ostream& os) const;
    void save(std::ostream& os) const;
    void load(std::istream& is);

    Admin* clone() const {
        return new Admin(username, password, name);
    }
};

#endif // ADMIN_H
