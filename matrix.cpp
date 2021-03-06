
#ifndef MATRIX_H 
#define MATRIX_H

#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

// copy constructor, destructor, and overloaded assignment operator,
class Matrix{
    private:
        long unsigned rows;
        long unsigned cols;


        public:
            int ** arr;


    public:
        //ctor
        Matrix(int rowNum,int colNum);

        // rule of three
        ~Matrix();
        Matrix(const Matrix &);
        Matrix operator=(const Matrix&);

        //getters 
        int getRowNum();
        int getColNum();

        void makeIdentity( Matrix&);



        //void insert(int data);
        void print();

        //overloaded operators 
        Matrix operator+( const Matrix& );
        Matrix operator-( const Matrix& );
        Matrix operator*( const Matrix& );


        bool operator==( const Matrix& );
        bool operator!=( const Matrix& );



        //scalar operator 
        Matrix operator*( int scalar);

        // isNonSingular();
        bool isInvertible();
        Matrix cofactorExpansion();

        Matrix transpose();
        Matrix inverse(const Matrix& A);
        Matrix inverse();









}; 
#endif