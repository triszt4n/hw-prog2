/**
 * @file deliverer.cpp
 */

#include "deliverer.h"
#include "profile.h"
#include "usefulio.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * @fn verifyLogin(std::string usern, std::string pw) in Deliverer
 * @brief Grants the DELIVERER rights if the proper username and password is given
 * @param usern - the username input
 * @param pw - the password input
 * @return DELIVERER if the credentials are identical, NOT_MATCHING otherwise
 */
Rights Deliverer::verifyLogin(const std::string& usern, const std::string& pw) const {
    if ((username == usern) && (password == pw))
        return DELIVERER;
    else
        return NOT_MATCHING;
}

void Deliverer::greetings(std::ostream& os) const {
    os << "-------------------------" << std::endl;
    os << "Hi, " << name << " (" << username << ")!" << std::endl;
    os << "reg: " << ctime(&regDate);
    os << "-------------------------" << std::endl << std::endl;
}

void Deliverer::save(std::ostream& os) const {
    os << "deliverer ";
    writeString(os, username);
    writeString(os, password);
    writeString(os, name);
    os << regDate << std::endl;
}

void Deliverer::load(std::istream& is) {
    username = readString(is);
    password = readString(is);
    name = readString(is);
    is >> regDate;
}
