/**
 * @file profile.cpp
 */

#include "profile.h"
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * @brief Simple getter for getting the username of object
 * @return username
 */
std::string Profile::getUsername() const {
    return username;
}

/**
 * @brief Comparator for profiles
 * @return true if their usernames are identical (it's their unique key)
 * @see List<T>.find(const T& data)
 */
bool Profile::operator==(Profile& rhs) const {
    return username == rhs.getUsername();
}
