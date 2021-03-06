
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
            double ** arr;
            int operations;


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



        Matrix makeIdentity();
        Matrix makeUpperTriang();
        Matrix makeLowerTriang();
        Matrix makeZero();


        //void insert(int data);
        void print();

        //overloaded operators 
        Matrix operator+( const Matrix& );
        Matrix operator-(  Matrix& );
        Matrix operator*( const Matrix& );
        Matrix strassen(Matrix A, Matrix B);



        bool operator==( const Matrix );
        bool operator!=( const Matrix );

        //scalar operator 
        Matrix operator*( int scalar);


        double calcCofactor(Matrix A ,int index);
        double determinant();   

        bool isInvertible();       //  AKA isNonSingular(); 

        Matrix transpose();
        Matrix RecurseInverse( ); //TODO make private eventually
        Matrix inverse();

        Matrix padStrassen( Matrix , int );

        Matrix paddedMatrix( Matrix ,Matrix );
        Matrix assembleMatrix( Matrix ,Matrix  ,Matrix ,Matrix );
        Matrix divideMatrix(Matrix , int , int , int , int );


}; 
#endif