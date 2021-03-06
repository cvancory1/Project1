
#ifndef MATRIX_H 
#define MATRIX_H

#include <iostream>
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


        //void insert(int data);
        void print();

        //overloaded operators 
        Matrix operator+( const Matrix& );
        Matrix operator-( const Matrix& );
        Matrix operator*( const Matrix& );

        //extra credit
        Matrix operator*( int scalar);

        Matrix transpose();
        Matrix inverse();



}; 
#endif