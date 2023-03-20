/**
 * @file number.h
 * @author Celeste Luis Díaz (alu0101321660@ull.edu.es)
 * @brief Abstract class that represents a number
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <iostream>

#include <string>

template<size_t base> class BigInt;

class Number {

    private:
        virtual std::ostream& write(std::ostream&) const = 0;
        virtual std::istream& read(std::istream&) = 0;

    public:
        static Number* create(size_t base, const std::string& str);

        // Flow control
        friend std::ostream& operator<<(std::ostream&, const Number&);
        friend std::istream& operator>>(std::istream&, Number&);

        virtual Number* add(const Number*) const = 0;
        virtual Number* subtract(const Number*) const = 0;
        virtual Number* multiply(const Number*) const = 0;
        virtual Number* divide(const Number*) const = 0;
        virtual Number* module(const Number*) const = 0;
        // virtual Number* pow(const Number*) const = 0;
        
        virtual operator BigInt<2>() const = 0;
        virtual operator BigInt<8>() const = 0;
        virtual operator BigInt<10>() const = 0;
        virtual operator BigInt<16>() const = 0;

        virtual int getBase() const = 0;

};

#include "bigint.h"