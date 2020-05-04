/**
 * @file deliverer.cpp
 */

#include "deliverer.h"
#include "profile.h"
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
Rights Deliverer::verifyLogin(std::string usern, std::string pw) const {
    if (username == usern && password == pw)
        return DELIVERER;
    else
        return NOT_MATCHING;
}

void Deliverer::save(std::ostream& os) const {

}

void Deliverer::load(std::istream& is) const {

}
