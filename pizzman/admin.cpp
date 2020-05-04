/**
 * @file admin.cpp
 */

#include "admin.h"
#include "profile.h"
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
Rights Admin::verifyLogin(std::string usern, std::string pw) const {
    if (username == usern && password == pw)
        return ADMIN;
    else
        return NOT_MATCHING;
}

void Admin::save(std::ostream& os) const {

}

void Admin::load(std::istream& is) const {

}
