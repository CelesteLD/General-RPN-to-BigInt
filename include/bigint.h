/**
 * @file bigint.h
 * @author Celeste Luis Díaz (alu0101321660@ull.edu.es)
 * @brief This class represents a BigInt number
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <iostream>
#include <vector>
#include <regex>
#include <math.h>

#include "number.h"
#include "exceptions.h"

template <size_t Base> class BigInt;

// Flow Operators
template <size_t Base> std::ostream &operator<<(std::ostream &, const BigInt<Base> &);
template <size_t Base> std::istream &operator>>(std::istream &, BigInt<Base> &);

// Comparison Operators
template <size_t Base> bool operator==(const BigInt<Base>&, const BigInt<Base>&);
template <size_t Base> bool operator>(const BigInt<Base>&, const BigInt<Base>&);
template <size_t Base> bool operator<(const BigInt<Base>&, const BigInt<Base>&);

// Arithmetic Operators
template <size_t Base> BigInt<Base> operator+(const BigInt<Base>&, const BigInt<Base>&);
template <size_t Base> BigInt<Base> operator/(const BigInt<Base>&, const BigInt<Base>&);

// Pow
template <size_t Base> BigInt<Base> pow(const BigInt<Base>&, const BigInt<Base>&);


template <>
class BigInt<2> : public Number {

    private:
        std::vector<bool> digits_;
        int sign_ = 0;

    public:
        BigInt(long value = 0);
        BigInt(std::string& value);
        BigInt(const char* value);
        BigInt(const BigInt<2>& value);
        BigInt(std::vector<bool> digits);
        ~BigInt() = default;

        // Asignment Operators
        BigInt<2>& operator=(const BigInt<2>& num);

        // Flow Operators
        friend std::ostream &operator<<(std::ostream &, const BigInt<2> &);
        friend std::istream &operator>>(std::istream &, BigInt<2> &);

        // Accesor Methods
        int sign() const; 
        char operator[](int) const; 
        std::vector<bool> digits() const;
        void setSign(int sign);
        void setDigits(std::vector<bool> digits);
        void setPosition(int position, bool value);

        // Comparison Operators
        friend bool operator==(const BigInt<2>& num1, const BigInt<2>& num2);
        bool operator!=(const BigInt<2>& num) const;
        friend bool operator>(const BigInt<2>& num1, const BigInt<2>& num2);
        bool operator>=(const BigInt<2>& num) const;
        friend bool operator< (const BigInt<2>& num1, const BigInt<2>& num2);
        bool operator<=(const BigInt<2>& num) const;

        // Increment and Decrement Operators
        BigInt<2>& operator++(); 
        BigInt<2> operator++(int value); 
        BigInt<2>& operator--(); 
        BigInt<2> operator--(int value); 

        // Arithmetic Operators
        friend BigInt<2> operator+(const BigInt<2>&, const BigInt<2>&);
        BigInt<2> operator-(const BigInt<2> &) const;
        BigInt<2> operator-() const;
        BigInt<2> operator*(const BigInt<2>&) const;
        friend BigInt<2> operator/(const BigInt<2>&, const BigInt<2>&);
        BigInt<2> operator%(const BigInt<2>&) const;

        // Pow
        friend BigInt<2> pow(const BigInt<2>&, const BigInt<2>&);

        BigInt<2> complementTwo() const;
        BigInt<2> abs() const;

        template<size_t Base> operator BigInt<Base>() const;


        // Methods Overrided from Number

        // Flow control
        std::ostream& write(std::ostream&) const override;
        std::istream& read(std::istream&) override;

        virtual Number* add(const Number*) const override;
        virtual Number* subtract(const Number*) const override;
        virtual Number* multiply(const Number*) const override;
        virtual Number* divide(const Number*) const override;
        virtual Number* module(const Number*) const override;

        virtual operator BigInt<2>() const override { return reinterpret_cast<const BigInt<2>&>(*this); }
        virtual operator BigInt<8>() const override;
        virtual operator BigInt<10>() const override;
        virtual operator BigInt<16>() const override;

        virtual int getBase() const override;
};

template <size_t Base = 10>
class BigInt : public Number {

    private:
        bool checkBase();
        bool checkDigits(char digit);

        std::vector<char> digits_;
        int sign_;

    public:
        BigInt(long value = 0);
        BigInt(std::string& value);
        BigInt(const char* value);
        BigInt(const BigInt<Base>& value);
        ~BigInt();

        // Asignment Operators
        BigInt<Base>& operator=(const BigInt<Base>& num);

        // Flow Operators
        friend std::ostream &operator<<<Base>(std::ostream &, const BigInt<Base> &);
        friend std::istream &operator>><Base>(std::istream &, BigInt<Base> &);

        // Accesor Methods
        int sign() const; 
        char operator[](int) const; 

        //Setters
        void setSign(int sign);

        // Comparison Operators
        friend bool operator==<Base>(const BigInt<Base>& num1, const BigInt<Base>& num2);
        bool operator!=(const BigInt<Base>& num) const;
        friend bool operator><Base>(const BigInt<Base>& num1, const BigInt<Base>& num2);
        bool operator>=(const BigInt<Base>& num) const;
        friend bool operator< <Base>(const BigInt<Base>& num1, const BigInt<Base>& num2);
        bool operator<=(const BigInt<Base>& num) const;

        // Increment and Decrement Operators
        BigInt<Base>& operator++(); 
        BigInt<Base> operator++(int value); 
        BigInt<Base>& operator--(); 
        BigInt<Base> operator--(int value); 

        // Arithmetic Operators
        friend BigInt<Base> operator+<Base>(const BigInt<Base>&, const BigInt<Base>&);
        BigInt<Base> operator-(const BigInt<Base> &) const;
        BigInt<Base> operator-() const;
        BigInt<Base> operator*(const BigInt<Base>&) const;
        friend BigInt<Base> operator/<Base>(const BigInt<Base>&, const BigInt<Base>&);
        BigInt<Base> operator%(const BigInt<Base>&) const;

        // Pow
        friend BigInt<Base> pow<Base>(const BigInt<Base>&, const BigInt<Base>&);

        std::string toString();


        // Methods Overrided from Number

        std::ostream& write(std::ostream&) const override;
        std::istream& read(std::istream&)  override;

        virtual Number* add(const Number* other) const override;
        virtual Number* subtract(const Number* other) const override;
        virtual Number* multiply(const Number* other) const override;
        virtual Number* divide(const Number* other) const override;
        virtual Number* module(const Number* other) const override;
        // virtual Number* pow(const Number* other) const override;

        virtual operator BigInt<2>() const override;
        virtual operator BigInt<8>() const override;
        virtual operator BigInt<10>() const override;
        virtual operator BigInt<16>() const override;

        virtual int getBase() const override;

};

// Check Methods

template <size_t Base>
bool BigInt<Base>::checkBase() {
    if (Base == 2 || Base == 8 || Base == 10 || Base == 16)
        return true;

    return false;
}

template <size_t Base>
bool BigInt<Base>::checkDigits(char digit) {
    switch(Base) {
        case 2:     
            if (digit == '0' || digit == '1')
                return true;
            break;
        case 8:
            if (digit >= '0' && digit <= '7')
                return true;
            break;
        case 10:
            if (digit >= '0' && digit <= '9')
                return true;
            break;
        case 16:
            if ((digit >= '0' && digit <= '9') || (digit >= 'A' && digit <= 'F'))
                return true;
            break;
        default:
            break;
    }
    return false;
}

// Constructors

template <size_t Base>
BigInt<Base>::BigInt(long value) {

    try {
      if(checkBase()) {
          if (value < 0) {
              sign_ = -1;
              value = -value;
          } else {
              sign_ = 1;
          }
      } else {
          throw BigIntBaseNotSupported();
      }
    } catch (BigIntBaseNotSupported& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    try {
      while(value > 0) {
          if(checkDigits(value % 10 + '0')) 
              digits_.push_back(value % 10 + '0');
          else {
              throw BigIntBadDigit();
          }
          value /= 10;
      }
    } catch (BigIntBadDigit& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

template <size_t Base>
BigInt<Base>::BigInt(std::string& value) {

    try {

      if (checkBase()) {
          if (value[0] == '-') {
              sign_ = -1;
              value = value.substr(1);
          } else if (value[0] == '+') {
              sign_ = 1;
              value = value.substr(1);
          } else if (regex_match(std::string(1, value[0]), std::regex("[0-9A-F]"))) {
              sign_ = 1;
          } else {
              throw BigIntBadDigit();
          }
      } else {
          throw BigIntBaseNotSupported();
      }
    } catch (BigIntBaseNotSupported& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    } catch (BigIntBadDigit& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }


    try {
      for (int i = value.size() - 1; i >= 0; i--) {
          if (checkDigits(value[i]))
              digits_.push_back(value[i]);
          else {
            throw BigIntBadDigit();
          }
      }
    } catch (BigIntBadDigit& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

template <size_t Base>
BigInt<Base>::BigInt(const char* value) {
    // Convert char* to string
    std::string str(value);
    BigInt<Base> temp(str);
    digits_ = temp.digits_;
    sign_ = temp.sign_;
}

template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& value) {
    digits_ = value.digits_;
    sign_ = value.sign_;
}

template <size_t Base>
BigInt<Base>::~BigInt() {
    digits_.clear();
    sign_ = 0;
}

// Asignment Operators

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& num) {
    digits_ = num.digits_;
    sign_ = num.sign_;
    return *this;
}

// Flow operators
template <size_t Base>
std::ostream &operator<<(std::ostream &os, const BigInt<Base> &n) {
  if (n.sign_ == -1)
    os << "-";
  for (int i = n.digits_.size() - 1; i >= 0; i--)
    os << n.digits_[i];
  return os;
}

template <size_t Base>
std::istream &operator>>(std::istream &is, BigInt<Base> &n) {
  std::string str;
  is >> str;
  n = BigInt<Base>(str);
  return is;
}

// Accesor Methods

template <size_t Base>
int BigInt<Base>::sign() const {
    return sign_;
}

template <size_t Base>
char BigInt<Base>::operator[](int index) const {

  try {
    int size = digits_.size();
    if (index < 0 || index >= size) {
        throw BigIntIndexOutOfRange();
    }
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

    return digits_[index];
}

// Setters

template <size_t Base>
void BigInt<Base>::setSign(int sign) {
    sign_ = sign;
}


// Comparison Operators

template <size_t Base>
bool operator==(const BigInt<Base>& num1, const BigInt<Base>& num2) {

    bool num1_zero = true;
    bool num2_zero = true;

    for (int i = 0; i < num1.digits_.size(); i++) {
        if (num1.digits_[i] != '0') {
            num1_zero = false;
            break;
        }
    }

    for (int i = 0; i < num2.digits_.size(); i++) {
        if (num2.digits_[i] != '0') {
            num2_zero = false;
            break;
        }
    }

    if (num1_zero && num2_zero)
        return true;
    
    if (num1.sign_ != num2.sign_)
        return false;

    if (num1.digits_.size() != num2.digits_.size())        
        return false;

    for (int i = 0; i < num1.digits_.size(); i++) {
        if (num1.digits_[i] != num2.digits_[i])
            return false;
    }
    return true;
}

template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& num) const {
    return !(*this == num);
}

template <size_t Base>
bool operator>(const BigInt<Base>& num1, const BigInt<Base>& num2) {
    if (num1.sign_ == -1 && num2.sign_ == 1)
        return false;
    if (num1.sign_ == 1 && num2.sign_ == -1)
        return true;
    if (num1.sign_ == 1 && num2.sign_ == 1) {
        if (num1.digits_.size() > num2.digits_.size())
            return true;
        else if (num1.digits_.size() < num2.digits_.size())
            return false;
        else {
            for (int i = num1.digits_.size() - 1; i >= 0; i--) {
                if (num1[i] > num2[i])
                    return true;
                else if (num1[i] < num2[i])
                    return false;
            }
        }
    }
  return false;
}

template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base>& num) const {
    return (*this > num || *this == num);
}

template <size_t Base>
bool operator<(const BigInt<Base> &num1, const BigInt<Base> &num2) {
  return !(num1 >= num2);
}

template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base>& num) const {
    return (*this < num || *this == num);
}

// Increment and Decrement Operators

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator++() {
    BigInt<Base> one(1);
    *this = *this + one;
    return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {
    BigInt<Base> temp(*this);
    ++(*this);
    return temp;
}

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator--() {
    BigInt<Base> one(1);
    *this = *this - one;
    return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {
    BigInt<Base> temp(*this);
    --(*this);
    return temp;
}

// Arithmetic Operators

template <size_t Base>
BigInt<Base> operator+(const BigInt<Base> &n1, const BigInt<Base> &n2) {
  BigInt<Base> result;

  size_t carry = 0;
  size_t i = 0;
  size_t j = 0;

  if (n1.sign() == -1 && n2.sign() == -1)
  {
    result.sign_ = -1;
    while (i < n1.digits_.size() || j < n2.digits_.size())
    {
      int num1, num2;
      if (i < n1.digits_.size())
      {
        if (n1[i] >= '0' && n1[i] <= '9')
          num1 = n1[i] - '0';
        else if (n1[i] >= 'A' && n1[i] <= 'F')
          num1 = n1[i] - 'A' + 10;
        i++;
      }
      else
        num1 = 0;

      if (j < n2.digits_.size())
      {
        if (n2[j] >= '0' && n2[j] <= '9')
          num2 = n2[j] - '0';
        else if (n2[j] >= 'A' && n2[j] <= 'F')
          num2 = n2[j] - 'A' + 10;
        j++;
      }
      else
        num2 = 0;

      int sum = num1 + num2 + carry;
      carry = sum / Base;
      sum = sum % Base;

      if (sum >= 0 && sum <= 9)
        result.digits_.push_back(sum + '0');
      else if (sum >= 10 && sum <= 15)
        result.digits_.push_back(sum - 10 + 'A');
    }
    if (carry > 0)
      result.digits_.push_back(carry + '0');
  }
  else if (n1.sign() == 1 && n2.sign() == 1)
  {
    result.sign_ = 1;
    while (i < n1.digits_.size() || j < n2.digits_.size())
    {
      int num1, num2;
      if (i < n1.digits_.size())
      {
        if (n1[i] >= '0' && n1[i] <= '9')
          num1 = n1[i] - '0';
        else if (n1[i] >= 'A' && n1[i] <= 'F')
          num1 = n1[i] - 'A' + 10;
        i++;
      }
      else
        num1 = 0;

      if (j < n2.digits_.size())
      {
        if (n2[j] >= '0' && n2[j] <= '9')
          num2 = n2[j] - '0';
        else if (n2[j] >= 'A' && n2[j] <= 'F')
          num2 = n2[j] - 'A' + 10;
        j++;
      }
      else
        num2 = 0;

      int sum = num1 + num2 + carry;
      carry = sum / Base;
      sum = sum % Base;

      if (sum >= 0 && sum <= 9)
        result.digits_.push_back(sum + '0');
      else if (sum >= 10 && sum <= 15)
        result.digits_.push_back(sum - 10 + 'A');
    }
    if (carry > 0)
      result.digits_.push_back(carry + '0');
  }
  else if (n1.sign() == -1 && n2.sign() == 1)
  {
    BigInt<Base> n1_copy(n1);
    n1_copy.sign_ = 1;
    result = n2 - n1_copy;
  }
  else if (n1.sign() == 1 && n2.sign() == -1)
  {
    BigInt<Base> n2_copy(n2);
    n2_copy.sign_ = 1;
    result = n1 - n2_copy;
  }

  return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base> &other) const {
  BigInt<Base> result;

  size_t carry = 0;
  size_t i = 0;
  size_t j = 0;

  if (sign() == -1 && other.sign() == -1)
  {
    BigInt<Base> n1_copy(*this);
    n1_copy.sign_ = 1;
    BigInt<Base> n2_copy(other);
    n2_copy.sign_ = 1;
    result = n2_copy - n1_copy;
  }
  else if (sign() == 1 && other.sign() == 1)
  {
    BigInt<Base> n1_copy(*this);
    BigInt<Base> n2_copy(other);
    if (n1_copy < n2_copy)
    {
      result = n2_copy - n1_copy;
      result.sign_ = -1;
    }
    else
    {
      result.sign_ = 1;
      while (i < n1_copy.digits_.size() || j < n2_copy.digits_.size())
      {
        int num1, num2;
        if (i < n1_copy.digits_.size())
        {
          if (n1_copy[i] >= '0' && n1_copy[i] <= '9')
            num1 = n1_copy[i] - '0';
          else if (n1_copy[i] >= 'A' && n1_copy[i] <= 'F')
            num1 = n1_copy[i] - 'A' + 10;
          i++;
        }
        else
          num1 = 0;

        if (j < n2_copy.digits_.size())
        {
          if (n2_copy[j] >= '0' && n2_copy[j] <= '9')
            num2 = n2_copy[j] - '0';
          else if (n2_copy[j] >= 'A' && n2_copy[j] <= 'F')
            num2 = n2_copy[j] - 'A' + 10;
          j++;
        }
        else
          num2 = 0;

        int sum = num1 - num2 - carry;
        if (sum < 0)
        {
          sum += Base;
          carry = 1;
        }
        else
          carry = 0;

        if (sum >= 0 && sum <= 9)
          result.digits_.push_back(sum + '0');
        else if (sum >= 10 && sum <= 15)
          result.digits_.push_back(sum - 10 + 'A');
      }
    }
  }
  else if (sign() == -1 && other.sign() == 1)
  {
    BigInt<Base> n1_copy(*this);
    n1_copy.sign_ = 1;
    result = n1_copy + other;
    result.sign_ = -1;
  }
  else if (sign() == 1 && other.sign() == -1)
  {
    BigInt<Base> n2_copy(other);
    n2_copy.sign_ = 1;
    result = *this + n2_copy;
  }

  if (result.digits_[result.digits_.size() - 1] == '0')
    result.digits_.pop_back();

  return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-() const
{
  BigInt<Base> result(*this);
  result.sign_ = -result.sign_;
  return result;
}


template <size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base> &rhs) const
{
  BigInt<Base> result;
  result.sign_ = sign_ * rhs.sign_;

  BigInt<Base> n1 = *this;
  BigInt<Base> n2 = rhs;

  if (n1.sign() == -1)
    n1 = -n1;
  if (n2.sign() == -1)
    n2 = -n2;

  BigInt<Base> sum;

  for (size_t i = 0; i < n2.digits_.size(); i++)
  {
    BigInt<Base> temp;
    int carry = 0;
    for (size_t j = 0; j < n1.digits_.size(); j++)
    {
      int num1 = n1[j] >= '0' && n1[j] <= '9' ? n1[j] - '0' : n1[j] - 'A' + 10;
      int num2 = n2[i] >= '0' && n2[i] <= '9' ? n2[i] - '0' : n2[i] - 'A' + 10;
      int prod = num1 * num2 + carry;
      carry = prod / Base;
      prod = prod % Base;
      temp.digits_.push_back(prod >= 10 ? prod - 10 + 'A' : prod + '0');
    }
    if (carry > 0)
      temp.digits_.push_back(carry >= 10 ? carry - 10 + 'A' : carry + '0');
    for (size_t j = 0; j < i; j++)
      temp.digits_.insert(temp.digits_.begin(), '0');
    sum = sum + temp;
  }

  if (result.sign() == -1)
    result = -sum;
  else
    result = sum;

  return result;
}

template <size_t Base>
BigInt<Base> operator/(const BigInt<Base> &dividend, const BigInt<Base> &divider) {

    BigInt<Base> result;
    BigInt<Base> n1 = dividend;
    BigInt<Base> n2 = divider;

    BigInt<Base> zero = BigInt<Base>("000");

    try {
      if (n2 == zero)
        throw BigIntDivisionByZero();
    } catch (BigIntDivisionByZero &e) {
      std::cout << e.what() << std::endl;
      return BigInt<Base>("0");
    }
    
    if (n1.sign() == -1)
        n1 = -n1;
    if (n2.sign() == -1)
        n2 = -n2;

    if (n1 < n2) {

        return BigInt<Base>("0");
    }
        
    
    BigInt<Base> temp;
    for (int i = (int)n1.digits_.size() - 1; i >= 0; i--) {
        temp.digits_.insert(temp.digits_.begin(), n1[i]);
        int count = 0;
        while (temp >= n2)
        {
        temp = temp - n2;
        count++;
        }
        result.digits_.insert(result.digits_.begin(), (count >= 10) ? count - 10 + 'A' : count + '0');
    }
    
    if (dividend.sign() == -1 && divider.sign() == -1)
        result.sign_ = 1;
    else if (dividend.sign() == -1 || divider.sign() == -1)
        result.sign_ = -1;

    // Si hay algun cero al final, se elimina
    if (result.digits_[result.digits_.size() - 1] == '0')
        result.digits_.pop_back();
    
    return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base> &rhs) const
{
  BigInt<Base> result;
  BigInt<Base> n1 = *this;
  BigInt<Base> n2 = rhs;

  if (n1.sign() == -1)
    n1 = -n1;
  if (n2.sign() == -1)
    n2 = -n2;

  if (n1 < n2)
    return n1;

  BigInt<Base> temp;
  for (int i = (int)n1.digits_.size() - 1; i >= 0; i--)
  {
    temp.digits_.insert(temp.digits_.begin(), n1[i]);
    int count = 0;
    while (temp >= n2)
    {
      temp = temp - n2;
      count++;
    }
  }

  if (sign() == -1)
    result = -temp;
  else
    result = temp;

  return result;
}

template <size_t Base>
BigInt<Base> pow(const BigInt<Base> &a, const BigInt<Base> &b)
{
  try {
    if (b < BigInt<Base>(0L)) {
      throw BigIntNegativeExponent();
    }
  } catch (BigIntNegativeExponent &e) {
    std::cout << e.what() << std::endl;
    return BigInt<Base>("0000");
  }
  BigInt<Base> res(1L);
  for (BigInt<Base> i(0L); i < b; i = i + BigInt<Base>(1L))
    res = res * a;

  return res;
}

template <size_t Base>
std::string BigInt<Base>::toString(){
  std::string result;
  if (sign_ == -1)
    result += '-';
  for (int i = (int)digits_.size() - 1; i >= 0; i--)
    result += digits_[i];
  return result;
}

// Methods Overrided from Number

template <size_t Base>
std::ostream& BigInt<Base>::write(std::ostream &os) const {
    os << *this;
    return os;
}

template <size_t Base>
std::istream& BigInt<Base>::read(std::istream &is) {
    is >> *this;
    return is;
}

template <size_t Base>
Number* BigInt<Base>::add(const Number *rhs) const {
    // Comprobar la base de los dos numeros
    if (Base != rhs->getBase()) {
        // Cambiar la base de rhs a la base de this
         BigInt<Base> n3 = static_cast<BigInt<Base>>(*rhs);

         return new BigInt<Base>(*this + *(dynamic_cast<const BigInt<Base>*>(&n3)));
    }
    return new BigInt<Base>(*this + *(dynamic_cast<const BigInt<Base>*>(rhs)));
}

template <size_t Base>
Number* BigInt<Base>::subtract(const Number *rhs) const {
    // Comprobar la base de los dos numeros
    if (Base != rhs->getBase()) {
        // Cambiar la base de rhs a la base de this
         BigInt<Base> n3 = static_cast<BigInt<Base>>(*rhs);

         return new BigInt<Base>(*this - *(dynamic_cast<const BigInt<Base>*>(&n3)));
    }
    return new BigInt<Base>(*this - *(dynamic_cast<const BigInt<Base>*>(rhs)));
}

template <size_t Base>
Number* BigInt<Base>::multiply(const Number *rhs) const {
    // Comprobar la base de los dos numeros
    if (Base != rhs->getBase()) {
        // Cambiar la base de rhs a la base de this
         BigInt<Base> n3 = static_cast<BigInt<Base>>(*rhs);

         return new BigInt<Base>(*this * *(dynamic_cast<const BigInt<Base>*>(&n3)));
    }
    return new BigInt<Base>(*this * *(dynamic_cast<const BigInt<Base>*>(rhs)));
}

template <size_t Base>
Number* BigInt<Base>::divide(const Number *rhs) const {
    // Comprobar la base de los dos numeros
    if (Base != rhs->getBase()) {
        // Cambiar la base de rhs a la base de this
         BigInt<Base> n3 = static_cast<BigInt<Base>>(*rhs);

         return new BigInt<Base>(*this / *(dynamic_cast<const BigInt<Base>*>(&n3)));
    }
    return new BigInt<Base>(*this / *(dynamic_cast<const BigInt<Base>*>(rhs)));
}

template <size_t Base>
Number* BigInt<Base>::module(const Number *rhs) const {
    // Comprobar la base de los dos numeros
    if (Base != rhs->getBase()) {
        // Cambiar la base de rhs a la base de this
         BigInt<Base> n3 = static_cast<BigInt<Base>>(*rhs);

         return new BigInt<Base>(*this % *(dynamic_cast<const BigInt<Base>*>(&n3)));
    }
    return new BigInt<Base>(*this % *(dynamic_cast<const BigInt<Base>*>(rhs)));
}

// Operator cambio de tipo 2

template <size_t Base>
BigInt<Base>::operator BigInt<2>() const {

    BigInt<2> result;

    switch (Base) {
      case 2:
        result = *this;
        break;
      case 8:
            {
        std::string binaryDigits;

        if (sign_ == -1) {
          binaryDigits += "1";
        }
        else {
          binaryDigits += "0";
        }

        // Recorrer todos los digitos de this empezando por el final
        for (int i = digits_.size() - 1; i >= 0; --i) {
          // Convertir el digito octal a binario
          switch (digits_[i]) {
          case '0':
            binaryDigits += "000";
            break;
          case '1':
            binaryDigits += "001";
            break;
          case '2':
            binaryDigits += "010";
            break;
          case '3':
            binaryDigits += "011";
            break;
          case '4':
            binaryDigits += "100";
            break;
          case '5':
            binaryDigits += "101";
            break;
          case '6':
            binaryDigits += "110";
            break;
          case '7':
            binaryDigits += "111";
            break;
          }
        }

        result = BigInt<2>(binaryDigits);

        return result;

        break;
    }
    case 10:
    {
    BigInt<Base> num(*this);

    if (sign_ == -1)
    {
      num = -num;
    }

    BigInt<Base> two(2L);
    BigInt<Base> zero(0L);

    std::vector<bool> digits;

    while (num > two)
    {
      if (num % two == zero)
      {
        digits.push_back(false);
      }
      else
      {
        digits.push_back(true);
      }
      num = num / two;
    }

    if (num < two)
    {
      digits.push_back(true);
    }

    if (num == two)
    {
      digits.push_back(false);
      digits.push_back(true);
    }

    digits.push_back(false); // Signo

    // Recorrer digits desde el final e introducirlo en un string
    std::string binaryDigits;

    for (int i = digits.size() - 1; i >= 0; --i)
    {
      if (digits[i])
      {
        binaryDigits += "1";
      }
      else
      {
        binaryDigits += "0";
      }
    }

    if (sign_ == -1)
    {
      result = BigInt<2>(binaryDigits);
      result = result.complementTwo();
      result.setSign(1);

      return result;
    }
    else
    {
      result = BigInt<2>(binaryDigits);
      return result;
    }

    return result = BigInt<2>("00");
    }

    case 16:
    {
    std::string binaryDigits;

    if (sign_ == -1)
    {
      binaryDigits += "1";
    }
    else
    {
      binaryDigits += "0";
    }

    // Recorrer todos los digitos de this empezando por el final
    for (int i = digits_.size() - 1; i >= 0; --i)
    {
      // Convertir el digito hexadecimal a binario
      switch (digits_[i])
      {
      case '0':
        binaryDigits += "0000";
        break;
      case '1':
        binaryDigits += "0001";
        break;
      case '2':
        binaryDigits += "0010";
        break;
      case '3':
        binaryDigits += "0011";
        break;
      case '4':
        binaryDigits += "0100";
        break;
      case '5':
        binaryDigits += "0101";
        break;
      case '6':
        binaryDigits += "0110";
        break;
      case '7':
        binaryDigits += "0111";
        break;
      case '8':
        binaryDigits += "1000";
        break;
      case '9':
        binaryDigits += "1001";
        break;
      case 'A':
        binaryDigits += "1010";
        break;
      case 'B':
        binaryDigits += "1011";
        break;
      case 'C':
        binaryDigits += "1100";
        break;
      case 'D':
        binaryDigits += "1101";
        break;
      case 'E':
        binaryDigits += "1110";
        break;
      case 'F':
        binaryDigits += "1111";
        break;
      }
    }

    result = BigInt<2>(binaryDigits);

    return result;

    break;
    }

    default:
      return BigInt<2>("00");
      break;
    }

    return result = BigInt<2>("00");
}

// Operator cambio de tipo 8

template <size_t Base>
BigInt<Base>::operator BigInt<8>() const {
    
    BigInt<8> result;

    switch (Base) {
        case 10:
          {
            // Dividir entre 8
            BigInt<Base> num(*this);

            if (sign_ == -1) {
              num = -num;
            }

            BigInt<Base> eight(8L);

            std::vector<BigInt<Base>> digits;

            while (num > eight) {
              digits.push_back(num % eight);
              num = num / eight;
            }

            if (num < eight) {
              digits.push_back(num);
            }

            // Recorrer digits desde el final e introducirlo en un string

            std::string octalDigits;

            for (int i = digits.size() - 1; i >= 0; --i) {
              octalDigits += digits[i].toString();
            }

            // std::cout << octalDigits << std::endl;

            result = BigInt<8>(octalDigits);

            
          }
          break;

        case 16:
          {
            // Convertir a binario
            BigInt<2> binario(*this);

            std::vector<bool> BinDigits = binario.digits();

            // Invertir el vector
            std::reverse(BinDigits.begin(), BinDigits.end());

            // Convertir a octal
            std::string binarioStr;

            for (int i = 0; i < BinDigits.size(); ++i) {
              if (BinDigits[i]) {
                binarioStr += "1";
              } else {
                binarioStr += "0";
              }
            }

            std::string octalDigits;

            // Si el tamaño no es multiplo de 3, añadir 0s al principio
            if (binarioStr.size() % 3 != 0) {
              int numZeros = 3 - (binarioStr.size() % 3);

              for (int i = 0; i < numZeros; ++i) {
                binarioStr = "0" + binarioStr;
              }
            }

            for (int i = 0; i < binarioStr.size(); i += 3) {
              std::string octalDigit = binarioStr.substr(i, 3);

              if (octalDigit == "000") {
                octalDigits += "0";
              } else if (octalDigit == "001") {
                octalDigits += "1";
              } else if (octalDigit == "010") {
                octalDigits += "2";
              } else if (octalDigit == "011") {
                octalDigits += "3";
              } else if (octalDigit == "100") {
                octalDigits += "4";
              } else if (octalDigit == "101") {
                octalDigits += "5";
              } else if (octalDigit == "110") {
                octalDigits += "6";
              } else if (octalDigit == "111") {
                octalDigits += "7";
              }
            }

            result = BigInt<8>(octalDigits);
      
            return result;
    }
    break;

    default:
      return BigInt<8>("00");
      break;
    }

    return result = BigInt<8>("00");
}

template <size_t Base>
BigInt<Base>::operator BigInt<10>() const {
    BigInt<10> result;

    switch(Base) {

      case 8:
        {
          BigInt<2> binario(*this);

          result = binario;
        }

        break;  

      case 16:
        {
          BigInt<2> binario(*this);

          result = binario;
        }

        break;
    }

    return result;   
}

template <size_t Base>
BigInt<Base>::operator BigInt<16>() const {
    BigInt<16> result;

    switch(Base) {

      case 8:
        {
          BigInt<2> binario(*this);
          result = binario;
        }

        break;  

      case 10:
        {
          BigInt<2> binario(*this);
          result = binario;
        }

        break;
    }

    return result;   
}

template <size_t Base>
int BigInt<Base>::getBase() const {
    return Base;
}