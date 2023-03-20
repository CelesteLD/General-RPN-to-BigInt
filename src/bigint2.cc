/**
 * @file bigint2.cc
 * @author Celeste Luis Díaz (alu0101321660@ull.edu.es)
 * @brief Implementation of the BigInt class for base 2
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

#include "../include/bigint.h"

BigInt<2>::BigInt(long value) {}

BigInt<2>::BigInt(std::string& value) {

    if (value[0] == '0') {
        sign_ = 0;
        value = value.substr(1);
    } else {
        sign_ = 1;
        value = value.substr(1);
    }

    for (int i = value.size() - 1; i >= 0; i--) {
        if (value[i] == '0') {
            digits_.push_back(false);
        } else {
            digits_.push_back(true);
        }
    }

}

BigInt<2>::BigInt(const char* value) { 

    if (value[0] == '0') {
        sign_ = 0;
        // Eliminar esa posicion
        value = value + 1;
    } else {
        sign_ = 1;
        // Eliminar esa posicion
        value = value + 1;
    }

    for (int i = strlen(value) - 1; i >= 0; i--) {
        if (value[i] == '0') {
            digits_.push_back(false);
        } else {
            digits_.push_back(true);
        }
    }
}

BigInt<2>::BigInt(const BigInt<2>& value) {
    digits_ = value.digits_;
    sign_ = value.sign_;
}

// Asignment Operators
BigInt<2>& BigInt<2>::operator=(const BigInt<2>& num) {
    digits_ = num.digits_;
    sign_ = num.sign_;

    return *this;
}

// Accesor Methods
int BigInt<2>::sign() const {
    return sign_;
}

char BigInt<2>::operator[](int index) const {
    return digits_[index];
}

std::vector<bool> BigInt<2>::digits() const {
    return digits_;
}

void BigInt<2>::setSign(int sign) {
    sign_ = sign;
}

void BigInt<2>::setDigits(std::vector<bool> digits) {
    digits_ = digits;
}

void BigInt<2>::setPosition(int position, bool value) {
    digits_[position] = value;
}

// Comparison Operators
bool operator==(const BigInt<2>& num1, const BigInt<2>& num2) {

    if (num1.sign_ != num2.sign_) {
        return false;
    }

    if (num1.digits_.size() != num2.digits_.size()) {
        for (int i = 0; i < num1.digits_.size(); i++) {
            for (int j = 0; j < num2.digits_.size(); j++) {
                if (num1.digits_[i] == false && num2.digits_[j] == false) {
                    return true;
                }
            }
        }
        return false;
    }

    for (int i = 0; i < num1.digits_.size(); i++) {
        if (num1.digits_[i] != num2.digits_[i]) {
            return false;
        }
    }

    return true;
}

bool BigInt<2>::operator!=(const BigInt<2>& num) const {
    return !(*this == num);
}

bool operator>(const BigInt<2>& num1, const BigInt<2>& num2) {

    // Comprobar que los dos números tengan el mismo número de dígitos
    int size1 = num1.digits_.size();
    int size2 = num2.digits_.size();

    BigInt<2> aux1 = num1;
    BigInt<2> aux2 = num2;

    if (size1 > size2) {
        for (int i = 0; i < size1 - size2; i++) {
            aux2.digits_.push_back(false);
        }
    } else if (size1 < size2) {
        for (int i = 0; i < size2 - size1; i++) {
            aux1.digits_.push_back(false);
        }
    }

    // Comprobar el signo
    if (num1.sign_ == 1 && num2.sign_ == 0) {
        return true;
    } else if (num1.sign_ == 0 && num2.sign_ == 1) {
        return false;
    }

    // Comprobar los dígitos
    for (int i = aux1.digits_.size() - 1; i >= 0; i--) {
        if (aux1.digits_[i] == true && aux2.digits_[i] == false) {
            return true;
        } else if (aux1.digits_[i] == false && aux2.digits_[i] == true) {
            return false;
        }
    }

    return false;
}

bool operator<(const BigInt<2>& num1, const BigInt<2>& num2) {
    return !(num1 > num2 || num1 == num2);
}

bool operator>=(const BigInt<2>& num1, const BigInt<2>& num2) {
    return (num1 > num2 || num1 == num2);
}

bool operator<=(const BigInt<2>& num1, const BigInt<2>& num2) {
    return (num1 < num2 || num1 == num2);
}

// Increment and Decrement Operators
BigInt<2>& BigInt<2>::operator++() {
    *this = *this + BigInt<2>("01");
    return *this;
}

BigInt<2> BigInt<2>::operator++(int) {
    BigInt<2> aux = *this;
    ++(*this);
    return aux;
}

BigInt<2>& BigInt<2>::operator--() {
    *this = *this - BigInt<2>("01");
    return *this;
}

BigInt<2> BigInt<2>::operator--(int) {
    BigInt<2> aux = *this;
    --(*this);
    return aux;
}

// Arithmetic Operators

BigInt<2> operator+(const BigInt<2>& num1, const BigInt<2>& num2) {


    int size1 = num1.digits_.size();
    int size2 = num2.digits_.size();

    BigInt<2> aux1 = num1;
    BigInt<2> aux2 = num2;

    
    BigInt<2> result;
    result.digits_.resize(std::max(size1, size2), false);

    bool carry = false;

    if (aux1.sign_ == 0 && aux2.sign_ == 0) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(false);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(false);
            }
        }

        for(int i = 0; i < result.digits_.size(); i++) {
            if (aux1.digits_[i] == false && aux2.digits_[i] == false) {
                if (carry == true) {
                    result.digits_[i] = true;
                    carry = false;
                } else {
                    result.digits_[i] = false;
                }
            } else if (aux1.digits_[i] == true && aux2.digits_[i] == true) {
                if (carry == true) {
                    result.digits_[i] = true;
                } else {
                    result.digits_[i] = false;
                    carry = true;
                }
            } else {
                if (carry == true) {
                    result.digits_[i] = false;
                } else {
                    result.digits_[i] = true;
                }
            }
        }
        if (carry == true) {
            result.digits_.push_back(true);
        }
    } else if (aux1.sign_ == 1 && aux2.sign_ == 1) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(true);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(true);
            }
        }

        result = aux1.abs() + aux2.abs();

        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;

    } else if (aux1.sign_ == 0 && aux2.sign_ == 1) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(true);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(false);
            }
        }

        if (aux1 > aux2.abs()) {

            result = aux1 - aux2.abs();

        } else {
            result = aux2.abs() - aux1;
            result = result.complementTwo();
            result.digits_[result.digits_.size()] = true;
            result.sign_ = 1;

        }
    } else if (aux1.sign_ == 1 && aux2.sign_ == 0) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(false);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(true);
            }
        }

        if (aux1.abs() > aux2) {

            result = aux1.abs() - aux2;
            result = result.complementTwo();
            result.digits_[result.digits_.size()] = true;
            result.sign_ = 1;

        } else if (aux1.abs() < aux2) {
            result = aux2 - aux1.abs();
        }
    }

    return result;
}

BigInt<2> BigInt<2>::operator-(const BigInt<2> &num) const {

    int size1 = digits_.size();
    int size2 = num.digits_.size();

    BigInt<2> aux1 = *this;
    BigInt<2> aux2 = num;

    
    BigInt<2> result;

    result.digits_.resize(std::max(size1, size2), false);

    if (aux1.sign_ == 1 && aux2.sign_ == 1) {
        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(true);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(true);
            }
        }

        result = aux1.abs() + aux2.abs();

        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;

    } else if (aux1.sign_ == 0 && aux2.sign_ == 0) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(false);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(false);
            }
        }

        if (aux1 > aux2) {

            bool carry = false;
            for(int i = 0; i < result.digits_.size(); i++) { 
                if (aux1.digits_[i] == false && aux2.digits_[i] == false) { // 0 - 0 -> Carry = 0
                    if (carry == true) {
                        result.digits_[i] = true;
                        carry = true;
                    } else {
                        result.digits_[i] = false;
                    }
                } else if (aux1.digits_[i] == true && aux2.digits_[i] == true) { // 1 - 1 -> Carry = 0
                    if (carry == true) {
                        result.digits_[i] = true;
                        carry = true;
                    } else {
                        result.digits_[i] = false;
                    }
                } else if (aux1.digits_[i] == false && aux2.digits_[i] == true) { // 0 - 1 -> Carry = 1
                    if (carry == true) {
                        result.digits_[i] = false;
                        carry = true;
                    } else {
                        result.digits_[i] = true;
                        carry = true;
                    }
                } else { // 1 - 0 -> Carry = 0
                    if (carry == true) {
                        result.digits_[i] = false;
                        carry = false;
                    } else {
                        result.digits_[i] = true;
                    }
                }
            }

            if (carry == true) {
                result.digits_.push_back(true);
            }

        } else {


            aux2 = aux2.complementTwo();
            aux2.digits_[aux2.digits_.size()] = true;
            aux2.setSign(1);

            result = aux1 + aux2;
        }

    } else if (aux1.sign_ == 0 && aux2.sign_ == 1) {
        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(true);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(false);
            }
        }

        result = aux1 + aux2.abs();

    } else if (aux1.sign_ == 1 && aux2.sign_ == 0) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(false);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(true);
            }
        }

        result = aux1.abs() + aux2;
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
    }

    return result;
}

BigInt<2> BigInt<2>::complementTwo() const {

    if (this->sign_ == 1) {
        return *this;
    }

    BigInt<2> result;

    result.digits_.resize(this->digits_.size(), false);

    BigInt<2> aux = *this;
    aux.setPosition(aux.digits_.size(), true);

    int i = 0; 
    for (i = 0; i < this->digits_.size() + 1; i++) {
        if (aux.digits_[i]) {
            result.digits_[i] = true;
            break;
        } else {
            result.digits_[i] = false;
        }
    }

    // Invertir los dígitos
    for (i = i + 1; i < this->digits_.size() + 1; i++) {
        if (aux.digits_[i]) {
            result.digits_[i] = false;
        } else {
            result.digits_[i] = true;
        }
    }

    return result;
}

BigInt<2> BigInt<2>::abs() const {

    if (this->sign_ == 0) {
        return *this;
    }

    BigInt<2> result;

    result.digits_.resize(this->digits_.size(), false);

    int i = 0;
    for (i = 0; i < this->digits_.size(); i++) {
        if (this->digits_[i]) {
            result.digits_[i] = true;
            break;
        } else {
            result.digits_[i] = false;
        }
    }

    // Invertir los demas

    for (i = i + 1; i < this->digits_.size(); i++) {
        if (this->digits_[i]) {
            result.digits_[i] = false;
        } else {
            result.digits_[i] = true;
        }
    }

    return result;

}



BigInt<2> BigInt<2>::operator-() const {
    if(this->sign_ == 0) {
        BigInt<2> result = *this;
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
        return result;
    } else {
        BigInt<2> result = *this;
        result = result.abs();
        result.sign_ = 0;
        return result;
    }
}

BigInt<2> BigInt<2>::operator*(const BigInt<2>& num) const {
    BigInt<2> result;
    BigInt<2> aux1 = *this;
    BigInt<2> aux2 = num;

    if (aux1.sign_ == 1) {
        aux1 = aux1.abs(); // Convertir a positivo
    }

    if (aux2.sign_ == 1) {
        aux2 = aux2.abs(); // Convertir a positivo
    }

    int size1 = aux1.digits_.size();
    int size2 = aux2.digits_.size();

    if (size1 > size2) {
        for (int i = 0; i < size1 - size2; i++) {
            aux2.digits_.push_back(false);
        }
    } else if (size1 < size2) {
        for (int i = 0; i < size2 - size1; i++) {
            aux1.digits_.push_back(false);
        }
    }

    result.digits_.resize(size1 + size2, false);

    // 0 x 0 = 0
    // 0 x 1 = 0
    // 1 x 0 = 0
    // 1 x 1 = 1 

    for (int i = 0; i < aux1.digits_.size(); i++) {
        bool carry = false;
        for (int j = 0; j < aux2.digits_.size(); j++) {
            bool product = aux1.digits_[i] && aux2.digits_[j];
            bool sum = result.digits_[i+j] ^ product ^ carry;
            carry = (result.digits_[i+j] && product) || (result.digits_[i+j] && carry) || (product && carry);
            result.digits_[i+j] = sum;
        }
        if (carry) {
            result.digits_[i+aux2.digits_.size()] = true;
        }
    }


    if (this->sign_ == 1 && num.sign_ == 0) {
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
        
    } else if (this->sign_ == 0 && num.sign_ == 1) {
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
    }


    return result;
}


BigInt<2> operator/(const BigInt<2>& dividend, const BigInt<2>& divisor) {

    BigInt<2> result;

    BigInt<2> aux1 = dividend;

    if(dividend.sign_ == 1) {
        aux1 = aux1.abs();
    }

    BigInt<2> aux2 = divisor;

    if(divisor.sign_ == 1) {
        aux2 = aux2.abs();
    }

    int size1 = aux1.digits_.size();
    int size2 = aux2.digits_.size();

    if (size1 > size2) {
        for (int i = 0; i < size1 - size2; i++) {
            aux2.digits_.push_back(false);
        }
    } else if (size1 < size2) {
        for (int i = 0; i < size2 - size1; i++) {
            aux1.digits_.push_back(false);
        }
    }

    result.digits_.resize(size1 + size2, false);

    // 0 / 0 = 0
    // 0 / 1 = 0
    // 1 / 0 = 0
    // 1 / 1 = 1

    while (aux1 > aux2) {
        aux1 = aux1 - aux2;
        result = result + BigInt<2>("01");
    }

    if (aux1 == aux2) {
        result = result + BigInt<2>("01");
    }

    // Si los signos son diferentes el resultado es negativo

    if (dividend.sign_ == 1 && divisor.sign_ == 0) {
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
    } else if (dividend.sign_ == 0 && divisor.sign_ == 1) {
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
    }

    return result;

}

BigInt<2> BigInt<2>::operator%(const BigInt<2>& num) const {
    BigInt<2> result;
    BigInt<2> aux;
    // Dividir hasta que el resto sea menor que el divisor
    if (num.sign() == 1) {
        aux = num.abs();
    } else {
        aux = num;
    }

    if (this->sign() == 1) {
        result = this->abs();
    } else {
        result = *this;
    }

    if (result < aux) {
        return result;
    }

    while (result > aux) {
        result = result - aux;
    }

    return result;
}


// Flow Operators
std::ostream &operator<<(std::ostream &os, const BigInt<2> &num) {

    // Imprimir el signo
    if (num.sign_ == 1) {
        os << "1";
    } else {
        os << "0";
    }

    for (int i = num.digits_.size(); i >= 0; i--) {
        if (num.digits_[i]) {
            os << "1";
        } else {
            os << "0";
        }
    }

    return os;
}

std::istream &operator>>(std::istream &is, BigInt<2> &num) {
    std::string str;
    is >> str;
    num = BigInt<2>(str);
    return is;
}

// Cambio de tipo

template <size_t Base>
BigInt<2>::operator BigInt<Base>() const {

    BigInt<Base> result;
    BigInt<2> aux = *this;

    switch (Base) {
        case 2:
            return *this;
            break;

        case 8:
            {
                if (aux.sign_ == 1) {
                    aux = aux.abs();
                } 


                // Comprobar que aux tiene un numero de digitos multiplo de 3
                if (aux.digits_.size() % 3 != 0) {
                    for (int i = 0; i < 3 - (aux.digits_.size() % 3); i++) {
                        aux.digits_.push_back(false);
                    }
                }

                std::string digitsOctal;

                // Recorrer los digitos de aux de 3 en 3
                for (int i = 0; i < aux.digits_.size(); i += 3) {
                    int sum = 0;
                    for (int j = 0; j < 3; j++) {
                        sum += aux.digits_[i+j] * std::pow(2, j);
                    }
                    digitsOctal += std::to_string(sum);
                }

                // Invertir el string
                std::reverse(digitsOctal.begin(), digitsOctal.end());

                // Eliminar los ceros a la izquierda
                while (digitsOctal[0] == '0') {
                    digitsOctal.erase(0, 1);
                }

                result = BigInt<Base>(digitsOctal);

                if (sign_ == 1) {
                    result.setSign(-1);
                }

                return result;

                break;
                
            }
            
        case 10:
            {
                if (aux.sign_ == 1) {
                    aux = aux.abs();
                } 

                for (int i = 0; i < aux.digits_.size(); ++i) {
                    if (aux.digits_[i]) {
                        result = result + BigInt<Base>(std::pow(2, i));
                    }
                }

                if (sign_ == 1) {
                    result.setSign(-1);
                }

                return result;

                break;
            }

        case 16:
            {
                if (aux.sign_ == 1) {
                    aux = aux.abs();
                } 

                // Comprobar que aux tiene un numero de digitos multiplo de 4
                if (aux.digits_.size() % 4 != 0) {
                    for (int i = 0; i < 4 - (aux.digits_.size() % 4); i++) {
                        aux.digits_.push_back(false);
                    }
                }

                std::string digitsHex;

                // Recorrer los digitos de aux de 4 en 4
                for (int i = 0; i < aux.digits_.size(); i += 4) {
                    int sum = 0;
                    for (int j = 0; j < 4; j++) {
                        sum += aux.digits_[i+j] * std::pow(2, j);
                    }
                    switch (sum) {
                        case 10:
                            digitsHex += "A";
                            break;
                        case 11:
                            digitsHex += "B";
                            break;
                        case 12:
                            digitsHex += "C";
                            break;
                        case 13:
                            digitsHex += "D";
                            break;
                        case 14:
                            digitsHex += "E";
                            break;
                        case 15:
                            digitsHex += "F";
                            break;
                        default:
                            digitsHex += std::to_string(sum);
                            break;
                    }
                }

                // Invertir el string
                std::reverse(digitsHex.begin(), digitsHex.end());

                // Eliminar los ceros a la izquierda
                while (digitsHex[0] == '0') {
                    digitsHex.erase(0, 1);
                }

                result = BigInt<Base>(digitsHex);

                if (sign_ == 1) {
                    result.setSign(-1);
                }

                return result;

                break;
            }
        default:
            return *this;
            break;
    }

}

// Methods Overrided from Number

std::ostream& BigInt<2>::write(std::ostream& os) const {
    os << *this;
    return os;
}

std::istream& BigInt<2>::read(std::istream& is) {
    is >> *this;
    return is;
}

Number* BigInt<2>::add(const Number* num) const {
    return new BigInt<2>(*this + *dynamic_cast<const BigInt<2>*>(num));
}

Number* BigInt<2>::subtract(const Number* num) const {
    return new BigInt<2>(*this - *dynamic_cast<const BigInt<2>*>(num));
}

Number* BigInt<2>::multiply(const Number* num) const {
    return new BigInt<2>(*this * *dynamic_cast<const BigInt<2>*>(num));
}

Number* BigInt<2>::divide(const Number* num) const {
    return new BigInt<2>(*this / *dynamic_cast<const BigInt<2>*>(num));
}

Number* BigInt<2>::module(const Number* num) const {
    return new BigInt<2>(*this % *dynamic_cast<const BigInt<2>*>(num));
}

BigInt<2>::operator BigInt<8>() const {

    BigInt<8> result;

    BigInt<2> aux = *this;

    if (aux.sign_ == 1) {
        aux = aux.abs();
    }

    std::string digitsOctal;

    // Recorrer los digitos de aux de 3 en 3
    for (int i = 0; i < aux.digits_.size(); i += 3) {
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += aux.digits_[i+j] * std::pow(2, j);
        }
        digitsOctal += std::to_string(sum);
    }

    // Invertir el string
    std::reverse(digitsOctal.begin(), digitsOctal.end());

    // Eliminar los ceros a la izquierda
    while (digitsOctal[0] == '0') {
        digitsOctal.erase(0, 1);
    }

    result = BigInt<8>(digitsOctal);

    if (sign_ == 1) {
        result.setSign(-1);
    }

    return result;


}

BigInt<2>::operator BigInt<10>() const {

    BigInt<2> aux = *this;

    if (sign_ == 1) {
        aux = aux.abs();
    }

    long result = 0;
    // Recorrer el número de bits de aux
    for (int i = 0; i < aux.digits_.size(); ++i) {
        if (aux.digits_[i]) {
            result += std::pow(2, i);
        }
    }

    return BigInt<10>(result);
}

BigInt<2>::operator BigInt<16>() const {

    BigInt<16> result;

    BigInt<2> aux = *this;

    if (aux.sign_ == 1) {
        aux = aux.abs();
    } 

    // Comprobar que aux tiene un numero de digitos multiplo de 4
    if (aux.digits_.size() % 4 != 0) {
        for (int i = 0; i < 4 - (aux.digits_.size() % 4); i++) {
            aux.digits_.push_back(false);
        }
    }

    std::string digitsHex;

    // Recorrer los digitos de aux de 4 en 4
    for (int i = 0; i < aux.digits_.size(); i += 4) {
        int sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += aux.digits_[i + j] * std::pow(2, j);
        }
        switch (sum) {
        case 10:
            digitsHex += "A";
            break;
        case 11:
            digitsHex += "B";
            break;
        case 12:
            digitsHex += "C";
            break;
        case 13:
            digitsHex += "D";
            break;
        case 14:
            digitsHex += "E";
            break;
        case 15:
            digitsHex += "F";
            break;
        default:
            digitsHex += std::to_string(sum);
            break;
        }
    }

    // Invertir el string
    std::reverse(digitsHex.begin(), digitsHex.end());

    // Eliminar los ceros a la izquierda
    while (digitsHex[0] == '0') {
        digitsHex.erase(0, 1);
    }

    result = BigInt<16>(digitsHex);

    if (sign_ == 1) {
        result.setSign(-1);
    }

    return result;

}

int BigInt<2>::getBase() const {
    return 2;
}