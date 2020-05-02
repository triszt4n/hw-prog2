/**
 * @file profile_handler.h
 */

#ifndef PROFILE_HANDLER_H
#define PROFILE_HANDLER_H

#include <iostream>
#include "profile.h"

class ProfileHandler {
    struct KVPair {
        std::string key;
        Profile* value;
    };
    static KVPair prototypes[3];
public:
    Profile* loadOne(std::istream& is);

    ~ProfileHandler();
};

#endif // PROFILE_HANDLER_H
