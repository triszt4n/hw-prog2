/**
 * @file customer.cpp
 */

#include "customer.h"
#include "profile.h"
#include "usefulio.hpp"
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
Rights Customer::verifyLogin(const std::string& usern, const std::string& pw) const {
    if ((username == usern) && (password == pw))
        return DEFAULT;
    else
        return NOT_MATCHING;
}

/**
 * @brief Casual method for writing out a greeting to the stream
 * @param os - stream to write to
 */
void Customer::greetings(std::ostream& os) const {
    os << "-------------------------" << std::endl;
    os << "Hi, " << name << " (" << username << ")!" << std::endl;
    os << (address == "" ? "*no address*" : address) << ", " << mobile << std::endl;
    os << "registered on: " << ctime(&regDate);
    os << "-------------------------" << std::endl << std::endl;
}

/**
 * @brief Simple setter for address
 * @param addr - the new address
 */
void Customer::setAddress(const std::string& addr) {
    address = addr;
}

/**
 * @brief Simple setter for mobile phone number
 * @param mob - the new mobile phone number
 */
void Customer::setMobile(const std::string& mob) {
    mobile = mob;
}

void Customer::save(std::ostream& os) const {
    os << "customer ";
    writeString(os, username);
    writeString(os, password);
    writeString(os, name);
    writeString(os, address);
    writeString(os, mobile);
    os << regDate << std::endl;
}

void Customer::load(std::istream& is) {
    username = readString(is);
    password = readString(is);
    name = readString(is);
    address = readString(is);
    mobile = readString(is);
    is >> regDate;
}
