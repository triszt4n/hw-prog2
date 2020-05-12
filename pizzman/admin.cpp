/**
 * @file admin.cpp
 */

#include "admin.h"
#include "profile.h"
#include "usefulio.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * @fn verifyLogin(std::string usern, std::string pw) in Admin
 * @brief Grants the ADMIN rights if the proper username and password is given
 * @param usern - the username input
 * @param pw - the password input
 * @return ADMIN if the credentials are identical, NOT_MATCHING otherwise
 */
Rights Admin::verifyLogin(const std::string& usern, const std::string& pw) const {
    if ((username == usern) && (password == pw))
        return ADMIN;
    else
        return NOT_MATCHING;
}

void Admin::greetings(std::ostream& os) const {
    os << "-------------------------" << std::endl;
    os << "Hi, " << name << " (" << username << ")!" << std::endl;
    os << "reg: " << ctime(&regDate);
    os << "-------------------------" << std::endl << std::endl;
}

void Admin::save(std::ostream& os) const {
    os << "admin ";
    writeString(os, username);
    writeString(os, password);
    writeString(os, name);
    os << regDate << std::endl;
}

void Admin::load(std::istream& is) {
    username = readString(is);
    password = readString(is);
    name = readString(is);
    is >> regDate;
}
