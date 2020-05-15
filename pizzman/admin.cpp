/**
 * \file admin.cpp
 * @brief Admin class definitions
 */

#include "admin.h"
#include "profile.h"
#include "usefulio.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

/**
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

/**
 * @brief Greets logged in user
 */
void Admin::greetings(std::ostream& os) const {
    os << "---------------------------------------------" << std::endl;
    os << " Hi, " << name << " (" << username << ")!" << std::endl;
    os << " registered on: " << ctime(&regDate);
    os << "---------------------------------------------" << std::endl << std::endl;
}





/// -------------------- Persistence -------------------

/**
 * @brief Simple I/O function for object storing
 */
void Admin::save(std::ostream& os) const {
    os << "admin ";
    writeString(os, username);
    writeString(os, password);
    writeString(os, name);
    os << regDate << std::endl;
}

/**
 * @brief Simple I/O function for object storing
 */
void Admin::load(std::istream& is) {
    username = readString(is);
    password = readString(is);
    name = readString(is);
    is >> regDate;
}

/// ----------------- End of Persistence ----------------
