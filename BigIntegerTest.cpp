/********************************************************************************* 
* Harsh Jha, hjha 
* 2023 Winter CSE101 PA6 
* BigIntegerTest.cpp 
* BigInteger Test C++ for BigInteger ADT 
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include "BigInteger.h"

using namespace std;

int main(){
    printf("test program\n");

    string a = "+123444569";
    string b = "-123444569";
    string c = "123444599";
    string d = "+123444569999999";

    BigInteger A = BigInteger(a);
    BigInteger B = BigInteger(b);
    BigInteger C = BigInteger(c);
    BigInteger D = BigInteger(d);
    BigInteger E;

    cout << "Sign Tests: " << endl;
    cout << "sign for a: " << A.sign() << endl;
    cout << "sign for b: " << B.sign() << endl;
    cout << "sign for c: " << C.sign() << endl;
    cout << "sign for e: " << E.sign() << endl;
    
    cout << "" << endl;

    cout << "Compare tests: " << endl;
    cout << "Compare A and A: " << A.compare(A) << endl;
    cout << "Compare A and B(-): " << A.compare(B) << endl;
    cout << "Compare A and C: " << A.compare(C) << endl;
    cout << "Compare A and d: " << A.compare(D) << endl;

    printf("\n\n");
    cout << "Sign test" << endl;
    B.negate();
    cout << "sign of B: " << B.sign() << endl;

    printf("\n\n");

    cout << "Clear test" << endl;
    C.makeZero();
    cout << "Compare C and E: " << C.compare(E) << endl;

    printf("\n\n");
    // cout << "helper function tests: " << endl;
    // List L;
    // L.insertBefore(1);
    // L.insertBefore(23);
    // L.insertBefore(44);
    // L.insertBefore(45);
    // L.insertBefore(69);
    // cout << "List L: " << L << endl;

    // negateList(L);

    // cout << "Negate List L: " << L << endl;

    // negateList(L);

    // printf("\n\n");

    // cout << "vector sum tests" << endl;
    // List Al;
    // Al.insertBefore(99);
    // Al.insertBefore(11);
    // Al.insertBefore(11);
    // Al.insertBefore(11);
    // Al.insertBefore(11);
    // List Bl;
    // Bl.insertBefore(1);
    // Bl.insertBefore(1);
    // Bl.insertBefore(1);
    // Bl.insertBefore(1);
    // List Cl;

    // cout << "List L: " << L << endl;
    // cout << "List A: " << Al << endl;
    // cout << "List B: " << Bl << endl;
    // cout << "List C: " << Cl << endl;
    // printf("\n");

    // sumList(Cl, L, Bl, 1);

    // cout << "List L: " << L << endl;
    // cout << "List B: " << Bl << endl;
    // cout << "List C (L + B): " << Cl << endl;
    // printf("\n");

    // sumList(Cl, L, Bl, -1);

    // cout << "List L: " << L << endl;
    // cout << "List B: " << Bl << endl;
    // cout << "List C (L - B): " << Cl << endl;
    // printf("\n");

    // Cl.clear();

    // sumList(Cl, L, Cl, 0);

    // cout << "List L: " << L << endl;
    // cout << "List C: " << Cl << endl;
    // cout << "List C (L - C): " << Cl << endl;
    // printf("\n");

    // sumList(Cl, L, Al, 1);

    // cout << "List L: " << L << endl;
    // cout << "List A: " << Al << endl;
    // cout << "List C (L - A): " << Cl << endl;
    // printf("\n");

    // sumList(Cl, L, Al, -1);

    // cout << "List L: " << L << endl;
    // cout << "List A: " << Al << endl;
    // cout << "List C (L - A): " << Cl << endl;

    // printf("\n\n");
    // cout << "Normalize Tests: " << endl;
    // List Dl;
    // Dl.insertBefore(-5);
    // Dl.insertBefore(-5);
    // Dl.insertBefore(-5);

    // cout << "List Dl: " << Dl << endl;
    // normalizeList(Dl);
    // cout << "Normalized Dl: " << Dl << endl;

    // Dl.clear();
    // Dl.insertBefore(100);
    // Dl.insertBefore(67);
    // Dl.insertBefore(1000);
    // Dl.insertBefore(-90);

    // cout << "List Dl: " << Dl << endl;
    // normalizeList(Dl);
    // cout << "Normalized Dl: " << Dl << endl; 

    // printf("\n\n");
    // cout << "Shift Tests: " << endl;
    // cout << "List Dl: " << Dl << endl;
    // shiftList(Dl, 2);
    // cout << "shifted Dl: " << Dl << endl; 


    // printf("\n\n");
    // cout << "Scalar Tests: " << endl;   
    // cout << "List Dl: " << Dl << endl;
    // scalarMultList(Dl, 0);
    // cout << "scalar Dl: " << Dl << endl; 

    // printf("\n\n");

    // Dl.clear();
    BigInteger Q = BigInteger("+111122223333");
    BigInteger T = BigInteger("+222211110000");
    cout << "Add Tests: " << endl;

    cout << "Big Integer A: " << Q << endl;
    cout << "Big Integer B: " << T << endl;
    C = Q.add(T);
    cout << "Sum of A and B: " << C << endl;

    A = BigInteger("+111122223333");
    B = BigInteger("+222211110000");

    // pos + pos = pos
    D = BigInteger("+333333333333");
    C = A + B;

    if (!(C == D))
        return 1;

    // add a positive and a negative integer
    //-> pos + neg = 0
    B = BigInteger("-111122223333");
    C = A + B;
    if (C.sign() != 0)
        return 2;

    //-> pos + neg > 0
    B = BigInteger("-110122223333");
    D = BigInteger("1000000000");
    C = A + B;
    if (C.sign() != 1)
        return 31;
    if (!(C == D))
        return 32;

    //-> pos + neg < 0
    B = BigInteger("-112122223333");
    D = BigInteger("-1000000000");
    C = A + B;
    if (C.sign() != -1)
        return 41;
    if (!(C == D))
        return 42;

    //-> neg + neg = neg
    A = BigInteger("-221211110000");
    D = BigInteger("-333333333333");
    cout << "print A: " << A << endl;
    cout << "print B: " << B << endl;
    C = A + B;

    cout << "print C: " << C << endl;
    cout << "print D: " << D << endl;
    
    A = BigInteger("+111122223333");
    B = BigInteger("+222211110000");

    // pos + pos = pos
    D = BigInteger("+333333333333");
    A += B;
    cout << "print A: " << A << endl;
    cout << "print D: " << D << endl;

    A = BigInteger("+111122223333");
    B = BigInteger("+111122223333");

    C = A - B;
    if (C.sign() != 0)
        return 1;

    // pos - pos < 0
    B = BigInteger("121122223333");
    D = BigInteger("-10000000000");
    C = A - B;
    if (C.sign() != -1)
        return 21;
    if (!(C == D))
        return 22;

    // pos - pos > 0
    B = BigInteger("101122223333");
    D = BigInteger("10000000000");
    C = A - B;
    if (C.sign() != 1)
        return 31;
    if (!(C == D))
        return 32;

    // pos - neg = pos
    B.negate();
    D = BigInteger("212244446666");
    cout << "print A: " << A << endl;
    cout << "print B: " << B << endl;
    C = A - B;
    cout << "print C: " << C << endl;
    cout << "print D: " << D << endl;
    if (C.sign() != 1)
        return 41;
    if (!(C == D))
        return 42;

    D.negate();
    cout << "print A: " << A << endl;
    cout << "print B: " << B << endl;
    C = B - A;
    cout << "print C: " << C << endl;
    cout << "print D: " << D << endl;

    printf("multiply tests\n");
    A = BigInteger("111122223333");
    B = BigInteger("111122223333");
    C = BigInteger();
    D = BigInteger("12348148518469129628889");

    // pos * pos = pos
    cout << "print A: " << A << endl;
    cout << "print B: " << B << endl;
    C = A * B;
    cout << "print C: " << C << endl;
    cout << "print D: " << D << endl;
    if (C.sign() != 1)
        return 1;
    if (!(C == D))
        return 2;

    printf("\n\n");
    // pos * neg = neg
    B.negate();
    D.negate();
    cout << "print A: " << A << endl;
    cout << "print B: " << B << endl;
    C = A * B;
    cout << "print C: " << C << endl;
    cout << "print D: " << D << endl;
    if (C.sign() != -1)
        return 3;
    if (!(C == D))
        return 4;
    printf("\n\n");
    B.makeZero();
    cout << "print A: " << A << endl;
    cout << "print B: " << B << endl;
    C = A * B;
    cout << "print C: " << C << endl;
    cout << "print D: " << D << endl;

}
