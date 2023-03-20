/**
 * @file exceptions.h
 * @author Celeste Luis Díaz (alu0101321660@ull.edu.es)
 * @brief This class contains the exceptions that can be thrown by the BigInt class
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <iostream>
#include <exception>

class BigIntException : public std::exception {
    public:
        virtual const char* what() const throw() = 0;
};

class BigIntBadDigit : public BigIntException {

    public:
        const char* what() const throw() {
            return "EXCEPTION. This digit is not allowed in this base";
        }
};

class BigIntDivisionByZero : public BigIntException {

    public:
        const char* what() const throw() {
            return "EXCEPTION. Division by zero. Not allowed";
        }
};

class BigIntBaseNotSupported : public BigIntException {

    public:
        const char* what() const throw() {
            return "EXCEPTION. This base is not supported";
        }
};

class BigIntIndexOutOfRange : public BigIntException {

    public:
        const char* what() const throw() {
            return "EXCEPTION. Index out of range";
        }
};

class BigIntNegativeExponent : public BigIntException {

    public:
        const char* what() const throw() {
            return "EXCEPTION. Negative exponent";
        }
};