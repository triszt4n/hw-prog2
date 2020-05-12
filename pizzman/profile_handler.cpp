/**
 * @file profile_handler.cpp
 */

#include "profile_handler.h"
#include "admin.h"
#include "customer.h"
#include "deliverer.h"
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * @fn setPrototypes()
 * @brief Loading up static items of prototypes
 */
void ProfileHandler::setPrototypes() {
    prototypes[0].key = "admin";
    prototypes[0].value = new Admin();
    prototypes[1].key = "customer";
    prototypes[1].value = new Customer();
    prototypes[2].key = "deliverer";
    prototypes[2].value = new Deliverer();
}

/**
 * @fn loadOne(std::istream& is): Profile*
 * @brief Finds the prototype by the key read from the stream
 * @return a pointer to the found prototype's value
 */
Profile* ProfileHandler::loadOne(std::istream& is) {
    std::string key;
    if (!(is >> key))
        return NULL;

    size_t i = 0;
    while ((i < PROF_NUMBER) && (prototypes[i].key != key))
        ++i;

    if (i == PROF_NUMBER)
        return NULL;

    Profile* proto = prototypes[i].value;
    Profile* clone = proto->clone();
    clone->load(is);
    return clone;
}

/**
 * @fn erasePrototypes()
 * @brief Deletes allocated memory for static members
 */
void ProfileHandler::erasePrototypes() {
    for (size_t i = 0; i < PROF_NUMBER; i++) {
        delete prototypes[i].value;
    }
}

