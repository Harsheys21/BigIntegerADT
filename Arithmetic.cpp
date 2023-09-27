/********************************************************************************* 
* Harsh Jha, hjha 
* 2023 Winter CSE101 PA6 
* Arithmetic.cpp 
* Arithmetic client for BigInteger ADT 
*********************************************************************************/ 
#include<iostream>
#include<string>
#include <cstring>
#include"List.h"
#include "BigInteger.h"
#include<fstream>


using namespace std;
#define MAX_LEN 300


int main(int argc, char * argv[]){
    ifstream in;
    ofstream out;
    string linea;
    string lineb;


    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // read each line of input file
    getline(in, linea); 
    getline(in, lineb);
    getline(in, lineb);
    if(linea[linea.length()-1] == '\n'){
        linea.pop_back();
    }

    if(lineb[lineb.length()-1] == '\n'){
        lineb.pop_back();      
    }

    // create the bigInteger
    BigInteger A = BigInteger(linea);
    BigInteger B = BigInteger(lineb);
    // print out the big integers
    out << A << endl << endl;
    out << B << endl << endl;
    out << A+B << endl << endl;
    out << A-B << endl << endl;
    out << A-A << endl << endl;
    BigInteger C = BigInteger("3");
    BigInteger D = BigInteger("2");
    out << (C*A)-(D*B) << endl << endl;
    out << A*B << endl << endl;
    out << A*A << endl << endl;
    out << B*B << endl << endl;
    BigInteger E = BigInteger("9");
    BigInteger F = BigInteger("16");
    out << (E*(A*A*A*A)) + (F*(B*B*B*B*B)) << endl << endl;

    // close files 
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
