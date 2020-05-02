/**
 * @file customer.cpp
 */

#include "customer.h"
#include "profile.h"
#include <cstdlib>
#include <iostream>
#include <string>

std::string Customer::getAddress() {
    return 0;
}

Rights Customer::verifyLogin(std::string username, std::string pw) const {
    return NOT_MATCHING;
}

void Customer::save(std::ostream& os) const {

}

void Customer::load(std::istream& is) const {

}
