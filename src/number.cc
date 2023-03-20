/**
 * @file number.cc
 * @author Celeste Luis Díaz (alu0101321660@ull.edu.es)
 * @brief Implementation of the Number class
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>

#include "../include/number.h"

Number* Number::create(size_t base, const std::string& str) {
    std::string str2 = str;
    switch (base) {
        case 2:
            return new BigInt<2>(str2);
        case 8:
            return new BigInt<8>(str2);
        case 10:
            return new BigInt<10>(str2);
        case 16:
            return new BigInt<16>(str2);
        default:
            return nullptr;
    }
}

std::ostream& operator<<(std::ostream& os, const Number& n) {
    return n.write(os);
}

std::istream& operator>>(std::istream& is, Number& n) {
    return n.read(is);
}
