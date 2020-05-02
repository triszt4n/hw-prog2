/**
 * @file deliverer.cpp
 */

#include "deliverer.h"
#include "profile.h"
#include <cstdlib>
#include <iostream>
#include <string>

Rights Deliverer::verifyLogin(std::string username, std::string pw) const {
    return NOT_MATCHING;
}

void Deliverer::save(std::ostream& os) const {

}

void Deliverer::load(std::istream& is) const {

}
