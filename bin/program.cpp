/*
This file is part of Tap.

Tap is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Tap is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Tap. If not, see <http://www.gnu.org/licenses/>.
*/ 

#ifndef TAP_H
#define TAP_H



#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <sstream>


namespace mjr{
typedef unsigned long int ulint;
typedef unsigned const char* cpByte; // help iteration
typedef unsigned char* pByte; // help iteration
static const int myBASE = (1<<8);

class Tap{
public:
    typedef unsigned char Byte;
    typedef std::vector<Byte>::reverse_iterator re_iter;
    typedef std::vector<Byte>::const_reverse_iterator re_citer;
    typedef std::vector<Byte>::iterator iter;
    typedef std::vector<Byte>::const_iterator citer;

    // [Constructors] 
    Tap() :data(1) {} // x = 0
    //Tap(const std::string&); // x = "123456"
    Tap(const char*); // x = "123456"
    explicit Tap(ulint); // x = 123456
    explicit Tap(citer from, citer to): data(from, to){} // x(t2.beg, t2.end)
    explicit Tap(size_t sz, bool) : data(sz){} // bool is artificial
    Tap(const Tap&); // copy Ctor
    Tap& operator=(const Tap&);

    // [Managers] 
    int normalize();
    void resize(size_t nsz, Byte elem=' ') { data.resize(nsz,elem); }
    void push_back(Byte by) { data.push_back(by); }
    void reinit(Byte by=' ') { data.assign(len(), by); } // reinit all digits
    // to ' ' by default

    // [Checkers] 
    size_t len() const { return data.size(); }
    size_t size() const { return data.size(); }
    std::string to_s(size_t base=10) const ;
    std::string print_raw() const ;
    ulint to_ul() const ;

    // [Element access] 
    Byte& operator[](size_t i) { return data[i]; }
    Byte operator[](size_t i) const { return data[i]; }
    const Byte* to_arr() const { return &data[0]; }
    const Byte* to_rarr() const { return &data[len()-1]; }
    unsigned char* to_arr() { return &data[0]; } /// @note non const
    Byte* to_rarr() { return &data[len()-1]; } /// @note non const

    // [Iterators] 
    iter begin() { return data.begin(); }
    iter end() { return data.end(); }
    re_iter rbegin() { return data.rbegin(); }
    re_iter rend() { return data.rend(); }
    re_citer rbegin() const { return data.rbegin(); }
    re_citer rend() const { return data.rend(); }
    citer begin() const { return data.begin(); }
    citer end() const { return data.end(); }

    // [Short operations] 
    /// @attention these functions change (*this)
    int quot(int); /// @test
    int modulo(int); /// @test
    int mult(int); /// @test
    int add(int); /// @test
    int diff(int); /// @test

    Tap& operator++();
    Tap operator++(int);
    Tap& operator--();
    Tap operator--(int);
    Tap& operator*=(const Tap& t2);
    Tap& inc1(); // TEST: Do some testing
    void inc1v2(); // @test
    void inc1v3(); // @test
    Tap pow(Tap); // FIXME: slow opperation
    //..
private:

    std::vector<Byte> data;
    //..
};


class TapConvertionException{
public:
    TapConvertionException(const std::string& s) : message(s) {}
    std::string message;
};


class Util{
public:
    template<typename T>
    static std::string stringfy(T x)
    {
        std::ostringstream o;
        if (!(o << x))
            throw TapConvertionException("The number couldn't be converted into a string");
        return o.str();
    }

    template<typename Base>
    static int product(int n, unsigned char* z, unsigned char* x, int y, Base base){
        unsigned carry = 0;
        for (int i = 0; i < n; i++) {
            carry += x[i]*y;
            z[i] = carrybase;
            carry /= base;
        }
        return carry;
    }

private:
    Util();
    //..
};

