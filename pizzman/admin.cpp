/**
 * @file admin.cpp
 */

#include "admin.h"
#include "profile.h"
#include <cstdlib>
#include <iostream>
#include <string>

Rights Admin::verifyLogin(std::string username, std::string pw) const {
    return NOT_MATCHING;
}

void Admin::save(std::ostream& os) const {

}

void Admin::load(std::istream& is) const {

}
