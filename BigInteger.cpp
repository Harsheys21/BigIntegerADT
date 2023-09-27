/********************************************************************************* 
* Harsh Jha, hjha 
* 2023 Winter CSE101 PA6 
* BigInteger.cpp 
* BigInteger C++ for BigInteger ADT 
*********************************************************************************/
#include<iostream>
#include<sstream>
#include<iomanip>
#include<string>
#include <cstring>
#include"List.h"
#include "BigInteger.h"
void negateList(List& L);
void sumList(List& S, List A, List B, int sgn);
int normalizeList(List& L);
void shiftList(List& L, int p);
void scalarMultList(List& L, ListElement m);

const int base = 1000000000;
const int p = 9;

// public constructors
// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){

    // determine sign
    if(s[0] == '-'){
        signum = -1;
    }
    else{
        signum = 1;
    }

    // remove sign from number
    std::string a = "";
    if(s[0] == '-' || s[0] == '+'){
        s.erase(0,1);
    }

    while(s[0] == '0'){
        s.erase(0,1);
    }

    if(s.length() == 0){
        signum = 0;
        return;
    }

    // add any leading 0's
    int remainder = (s.length()) % p;
    std::string f = "";
    if(remainder > 0){
        for(int i = 0; i < p - remainder; i++){
            f += "0";
        }
    }
    f += s;
    // seperate into list
    std::string c = "";
    digits.moveFront();
    for(size_t i = 0; i < f.length(); i++){
        if(i%p == 0 && i != 0){
            long value = std::stol(c);
            digits.insertBefore(value);
            c = "";
        }
        c += f[i];
    }
    long value = std::stol(c);
    digits.insertBefore(value);
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    digits = N.digits;
    signum = N.signum;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is negative, 
// positive or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    if(signum > N.signum){
        return 1;
    }
    else if(N.signum > signum){
        return -1;
    }

    if(digits.length() > N.digits.length()){
        return 1;
    }
    else if(N.digits.length() > digits.length()){
        return -1;
    } else {
        List a = N.digits;
        List b = digits;
        a.moveFront();
        b.moveFront();
        while(a.position() < b.length()){
            if(a.peekNext() > b.peekNext()){
                return -1;
            }
            else if(a.peekNext() < b.peekNext()){
                return 1;
            }
            a.moveNext();
            b.moveNext();
        }
        return 0;
    }
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    signum *= -1;
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger big;
    List A = this->digits;
    List B = N.digits;
    if(signum != N.signum){
        if(N.signum == -1){
            sumList(big.digits, A, B, -1);
        } else{
            sumList(big.digits, B, A, -1);
        }
    }
    else{
        sumList(big.digits, A, B, 1);
    }

    big.signum = normalizeList(big.digits);

    if(signum == -1 && N.signum == -1){
        big.signum = -1;
    }
    return big;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger big;
    List A = this->digits;
    List B = N.digits;
    if(signum == 1 && N.signum == 1){
        sumList(big.digits, A, B, -1);
    }
    else if(signum == 1 && N.signum == -1){
        sumList(big.digits, A, B, 1);
    } else if(signum == -1 && N.signum == 1){
        sumList(big.digits, A, B, 1);
    } else {
        sumList(big.digits, B, A, -1);
    }

    big.signum = normalizeList(big.digits);
    if(signum == -1 && N.signum == 1){
        big.signum = -1;
    }
    return big;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger big;
    List A;
    List B;

    if(this->digits.length() > N.digits.length()){
        A = this->digits;
        B = N.digits;
    }
    else{
        A = N.digits;
        B = this->digits;
    }

    big.signum = signum * N.signum;

    B.moveBack();
    List C;
    ListElement cursor = 0;

    int p = 0;
    while(B.position() > 0){
        C = A;
        cursor = B.peekPrev();
        scalarMultList(C, cursor);
        shiftList(C, p);
        sumList(big.digits, C, big.digits, 1);
        normalizeList(big.digits);
        B.movePrev();
        p++;
    }

    return big;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::string s = "";

    if(signum == 0){
        s+= "0";
        return s;
    } else if(signum == -1){
        s += "-";
    } 
    
    digits.moveFront();
    s+= std::to_string(digits.peekNext());
    digits.moveNext();
    while(digits.position() < digits.length()){
        std::string as = std::to_string(digits.peekNext());
        size_t t = as.length();
        for(int i = t; i < p; i++){
            s+="0";
        }
        s+= as;
        digits.moveNext();
    }

    return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 0){
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) < 0){
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) <= 0){
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) > 0){
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) >= 0){
        return true;
    }
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.add(B);
    return C;
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.sub(B);
    return C;
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.mult(B);
    return C;
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}

// ------------------------------------------------------------------------helper functions

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
    L.moveFront();
    while(L.position() < L.length()){
        L.setAfter(L.peekNext() * -1);
        L.moveNext();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    S.clear();
    S.moveFront();
    A.moveBack();
    B.moveBack();
    while(A.position() > 0 && B.position() > 0){
        long a = A.peekPrev();
        long b = B.peekPrev();
        S.insertAfter(a + (sgn * b));
        A.movePrev();
        B.movePrev();
    }

    while(A.position() > 0){
        S.insertAfter(A.peekPrev());
        A.movePrev();
    }
    
    while(B.position() > 0){
        S.insertAfter(B.peekPrev());
        B.movePrev();
    }

}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
    L.moveFront();
    while(L.length() != 0 && L.peekNext() == 0){
        L.eraseAfter();
    }

    if(L.length() == 0){
        return 0;
    }
    else{
        L.moveFront();
        if(L.peekNext() > 0){
            L.moveBack();
            while(L.position() > 0){
                ListElement cursor = L.peekPrev();

                if(cursor >= base){
                    ListElement carry = cursor/base;
                    L.setBefore(cursor-(carry * base));
                    L.movePrev();
                    if(L.position() == 0){
                        L.insertAfter(carry);
                    }
                    else{
                        L.setBefore(L.peekPrev() + carry);
                    }
                } else if(cursor < 0){
                    int carry;
                    if(cursor % base == cursor){
                        carry = base/base;
                    } else if(cursor % base == 0){
                        carry = cursor/base;
                    } else{
                        carry = (cursor/base) + 1;
                    }
                    L.setBefore(cursor+(carry*base));
                    L.movePrev();
                    L.setBefore(L.peekPrev() - carry);
                } else {
                    L.movePrev();
                }
            }
        } else{
            negateList(L);
            normalizeList(L);
            return -1;
        }
    }

    L.moveFront();
    while(L.length() != 0 && L.peekNext() == 0){
        L.eraseAfter();
    }

    L.moveFront();
    if(L.length() != 0 && L.peekNext() < 0){
        negateList(L);
        normalizeList(L);
        return -1;
    }

    return 1;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
    L.moveBack();
    for(int i = 0; i < p; i++){
        L.insertBefore(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    L.moveFront();
    while(L.position() < L.length()){
        L.setAfter(L.peekNext() * m);
        L.moveNext();
    }
}