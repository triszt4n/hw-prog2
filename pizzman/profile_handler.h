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

    static const size_t PROF_NUMBER = 3;
    KVPair prototypes[PROF_NUMBER];
public:
    Profile* loadOne(std::istream& is);
    void setPrototypes();
    void erasePrototypes();
};

#endif // PROFILE_HANDLER_H
