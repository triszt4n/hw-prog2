/**
 * \file usefulio.hpp
 * @brief Useful persistence helper functions
 */

#ifndef USEFULIO_H
#define USEFULIO_H

#include <iostream>
#include <string>
#include <cstdlib>

/**
 * @brief Useful function for reading in a string from stream
 * @return string from stream
 */
inline std::string readString(std::istream& is) {
    size_t len;
    char* p;

    (is >> len).ignore(1);
    p = new char[len + 1];
    is.read(p, len);
    p[len] = '\0';
    std::string result = p;
    delete[] p;

    return result;
}

/**
 * @brief Useful function for writing out a string to stream
 */
inline void writeString(std::ostream& os, std::string str) {
    os << str.size() << ' ';
    os.write(str.c_str(), str.size());
    os << ' ';
}

#endif // USEFULIO_H
