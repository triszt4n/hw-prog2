/**
 * @file customer.cpp
 */

#include "customer.h"
#include "profile.h"
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * @brief Simple getter for getting the address of object
 * @return address
 */
std::string Customer::getAddress() {
    return address;
}

/**
 * @fn verifyLogin(std::string usern, std::string pw) in Customer
 * @brief Grants the DEFAULT rights if the proper username and password is given
 * @param usern - the username input
 * @param pw - the password input
 * @return DEFAULT if the credentials are identical, NOT_MATCHING otherwise
 */
Rights Customer::verifyLogin(std::string usern, std::string pw) const {
    if (username == usern && password == pw)
        return DEFAULT;
    else
        return NOT_MATCHING;
}

void Customer::save(std::ostream& os) const {

}

void Customer::load(std::istream& is) const {

}
