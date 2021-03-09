/*

Chloe VanCory
project1 - main 

*/

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include<unistd.h>
#include<cmath>
#include <string>

#include "matrix.h"


using namespace std;


void fillMatrix(Matrix& A);
void fillMatrixByHand(Matrix& A);
void makeDiagnol(Matrix& A);
// void makeUpperTriang(Matrix& A);
// void makeLowerTriang(Matrix& A);
// void makeIdentity(Matrix& A);


Matrix timeAdd( Matrix A, Matrix B);
Matrix timeSub( Matrix A, Matrix B);
Matrix timeMult( Matrix A, Matrix B);



int main(){

    // Matrix A1( 1,4);
    // fillMatrix(A1);

    // Matrix A2( 4,4);
    // fillMatrix(A2);


    // cout<<"Printing A1\n"<<endl;
    // A1.print();
    // cout<<"Printing A2\n"<<endl;
    // A2.print();


    // cout<<"Calling copy ctor on A3(A1) \n"<<endl;
    // Matrix A3(A1);
    // A3.print();


    // cout<<endl;
    // cout<<"Calling op equal A3=A2 so now A3's size changes \n"<<endl;
    // A3 = A2;
    // A3.print();

    // cout<<"Testing subtraction and addtion with 2x2 \n"<<endl;

    // Matrix A4(2,2);
    // Matrix A5(2,2);
    // fillMatrix(A4);
    // fillMatrix(A5);

    // cout<<"Printing the matricies before the operations"<<endl;
    // A4.print();
    // cout<<endl;
    // A5.print();


    // cout<<"Calling op +  \n"<<endl;
    // Matrix A6 = A4+A5;
    // A6.print();

    // cout<<"Calling op- Subtraction  \n"<<endl;

    // A6 = A4-A5;
    // A6.print();


    // Matrix A7(3,2);
    // Matrix A8(1,2);
    // fillMatrix(A7);
    // fillMatrix(A8);

    // //fillMatrixByHand(A8);

    // A7.print();
    // puts("");
    // A8.print();


    // Matrix A9 = A7*A8;
    // A9.print();


    // cout<<"------------\n Upper triagnular matrix"<<endl;
    // Matrix matrix1(3,5);
    // fillMatrix(matrix1);
    // makeUpperTriang(matrix1);
    // matrix1.print();

    // cout<<"------------\n Upper triagnular matrix * vector"<<endl;

    // Matrix V (5,1);
    // fillMatrix(V);
    // Matrix temp = matrix1 * V;
    // temp.print();



    //  cout<<"------------\n lower triagnular matrix * upper triangular "<<endl;
    // Matrix matrix2(5,5);
    // fillMatrix(matrix2);
    // makeLowerTriang(matrix2);
    // matrix2.print();

    // temp = matrix1 * matrix2 ;
    // temp.print();



    // cout<<"------------\n Diag matrix + lower triangular "<<endl;
    // Matrix matrix3(5,5);
    // fillMatrix(matrix3);
    // makeDiagnol(matrix3);
    // matrix3.print();
    // temp = matrix3 * matrix2 ;


  


    // cout<<"------------\n Extra Credit- Scalar "<<endl;
    // Matrix matrix4(5,5);
    // fillMatrix(matrix4);
    // cout<<"Before Scalar"<<endl;
    // matrix4.print();
    // matrix4=matrix4*2;
    // cout<<"After Scalar"<<endl;
    // matrix4.print();
    



    // used to time the operations
    // //int arr[]={10000,20000,30000,40000};

    // for(int i =0; i< 4 ;i++){
    //     cout<<"Size="<<arr[i]<<endl;
    //     Matrix A (arr[i],arr[i]);
    //     fillMatrix(A);
    //     Matrix B= A;
    // //     cout<<"add"<<endl;
    // //    timeAdd(A,B);
    // //     cout<<"sub"<<endl;

    // //     timeSub(A,B);
    //    timeMult(A,B);

    // }



//     Matrix A (3,3);
// //    A.makeIdentity(A);
//     fillMatrix(A);
   

//     //  A.makeUpperTriang(A);
//     // A.print();

//    // A.inverse(A);
//     // // A.transpose();
//     // // cout<<A.isInvertible()<<endl;
//     // A.inverse(A);

// //    Matrix B(1,1);
// //    B= B.divideMatrix(A, 2 ,3 ,3,3 );

// //     B.print();
//     A.inverse(A);
    
    
   Matrix A(3,3);
   fillMatrix(A);


    // Matrix B=A;
    // Matrix C=A;

    // C.print();
    // Matrix D=A;

    // A.assembleMatrix(A,B,C,D);


//    int arr[]= {4,7,2,6};
   int arr[]= {2,3,1,-1,5,9,2,2,2};

    int pos=0;
   for(int i =0;i< A.getRowNum() ;i++){
     for(int j =0; j< A.getRowNum() ;j++){
         A.arr[i][j] = arr[pos++];
     }

   }

   Matrix B= A.inverse();
   cout<<"          FIN MAIN"<<endl;
   B.print();

   cout<<"          Inverse check"<<endl;

    (B*A).print();




}


// TODO: check padding nad valgrind
// [[-0.25   , -0.125  ,  0.6875 ],
//  [ 0.625  ,  0.0625 , -0.59375],
//  [-0.375  ,  0.0625 ,  0.40625]]





























/****************************************/





// Quickly populates array with numbers 1 -n 
void fillMatrix(Matrix& A){
    int data =1;
    
     for(int i=0 ;i<A.getRowNum() ;i++){
        for(int j=0; j<A.getColNum() ;j++){
            A.arr[i][j]=data++;
        
        }
    }

}

void fillMatrixByHand(Matrix& A){
    
     for(int i=0 ;i<A.getRowNum() ;i++){
        for(int j=0; j<A.getColNum() ;j++){
            int num;
            cin>>num;
            A.arr[i][j]=num;
        
        }
    }

}

void makeDiagnol(Matrix& A){
    for(int i=0 ;i<A.getRowNum() ;i++){
        for(int j=0; j<A.getColNum() ;j++){
            if(i!=j){
                A.arr[i][j]=0;
                
            }
        }
    }

}


// void makeIdentity(Matrix& A){

//      for(int i=0 ;i<A.getRowNum() ;i++){
//         A.arr[i][i]=1;
                
//     }

// }


Matrix timeAdd( Matrix A, Matrix B){

 
  auto begin = std::chrono::system_clock::now();
  
  Matrix temp= A+B;
  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  std::cout << " finished at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << " seconds\n\n";
    return temp;
    
}

Matrix timeSub( Matrix A, Matrix B){

 
  auto begin = std::chrono::system_clock::now();
  
  Matrix temp= A-B;
  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  std::cout << " finished at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << " seconds\n\n";
    return temp;
    
}

Matrix timeMult( Matrix A, Matrix B){

 
  auto begin = std::chrono::system_clock::now();
  
  Matrix temp= A*B;
  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  std::cout << " finished at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << " seconds\n\n";
    return temp;
    
}


/*
echo "# Project1" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/cvancory1/Project1.git
git push -u origin main
*/