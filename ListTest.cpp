/********************************************************************************* 
* Harsh Jha, hjha
* 2023 Winter CSE101 PA6
* ListTest.cpp
* ListTest c++ file for List ADT 
*********************************************************************************/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
    List L;
    
    for(long i = 0; i< 10; i++){
        cout << "i: " << i << endl;
        L.insertBefore(i);
        cout << "length : " << L.length() << endl; 
        cout << "front: " << L.front() << endl;
        cout << "Pos: " << L.position() << endl;
        cout << "back: " << L.back() << endl;
        cout << "L = " << L << endl;
    }

    cout << "peek Prev: " << L.peekPrev() << endl;
    L.moveFront();
    cout << "peek next: " << L.peekNext() << endl;
    cout << "Pos: " << L.position() << endl;
    L.moveBack();
    cout << "peek Prev: " << L.peekPrev() << endl;
    cout << "Pos: " << L.position() << endl;
    L.moveFront();
    long k;
    cout << "move next---" << endl;
    for(long i = 0; i < 10; i++){
        k = L.moveNext();
        cout << "K: " << k << endl;
        cout << "Pos: " << L.position() << endl;
    }

    cout << "move prev---" << endl;
    for(long i = 0; i < 10; i++){
        k = L.movePrev();
        cout << "K: " << k << endl;
        cout << "Pos: " << L.position() << endl;
    }

    k = L.moveNext();

    L.setBefore(29);
    L.setAfter(30);

    cout << "L = " << L << endl;
    L.moveFront();

    for(long i = 0; i < 10; i++){
        L.eraseAfter();
        cout << "L = " << L << endl;
    }

    cout << "L (after erase)= " << L << endl;
    cout << "Pos: " << L.position() << endl;

    for(long i = 0; i< 10; i++){
        L.insertBefore(i);
    }

    L.moveBack();
    for(long i = 0; i < 10; i++){
        L.eraseBefore();
        cout << "L = " << L << endl;
    }


    for(long i = 0; i< 10; i++){
        L.insertBefore(i);
    }

    L.moveFront();

    k = L.findNext(8);
    cout << "Position of 8: " << k << endl;

    k = L.findPrev(0);
    cout << "Position of 0: " << k << endl;


    List T;
    T.insertBefore(1);
    T.insertBefore(2);
    T.insertBefore(2);
    T.insertBefore(2);
    T.insertBefore(5);
    T.insertBefore(1);
    T.insertBefore(7);
    T.insertBefore(71);
    T.insertBefore(10);
    T.insertBefore(5);
    T.insertBefore(10);
    T.insertBefore(71);
    T.insertBefore(21);
    T.insertBefore(21);
    T.insertBefore(21);

    cout << "T: " << T << endl;

    T.cleanup();

    cout << "T cleanup: " << T << endl;
    cout << "T length : " << T.length() << endl;

    List R;
    cout << "R position beg - " << R.position() << endl;
    List pR = R;
    cout << "R copy length : " << pR.length() << endl;
    cout << "R position copy- " << R.position() << endl;
    R.insertAfter(1);
    cout << "R : " << R << endl;
    R.insertAfter(2);
    cout << "R : " << R << endl;
    R.insertAfter(3);
    cout << "R : " << R << endl;
    R.insertAfter(5);
    cout << "R : " << R << endl;
    R.insertAfter(12);
    cout << "R : " << R << endl;
    cout << "R position afterinsert - " << R.position() << endl;

    R.clear();
    cout << "R position now clear - " << R.position() << endl;

    R.insertBefore(1);
    R.insertBefore(2);
    R.insertBefore(2);
    R.insertBefore(1);
    R.insertBefore(2);
    R.insertBefore(3);
    R.insertBefore(1);
    R.findPrev(3);
    cout << "R position now : " << R.position() << endl;
    cout << "R now: " << R << endl;
    cout << "R position : " << R.position() << endl;


    List A;
    for(long i = 0; i < 40; i+=2){
        A.insertBefore(i);
    }

    cout << "List A: " << A << endl;

    for(long i = 0; i < 7; i++){
        // A.movePrev();
    }

    A.clear();
    List B;
    List C;
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    B.insertAfter(4);
    B.insertAfter(5);
    B.insertAfter(6);

    C = A.concat(B);
    if (C.length() != 6){
        printf("concat works\n");
    }

    List D = C;
    return 0;
}