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



void fillMatrix(Matrix& A, int arr[]){

 int pos=0;
    for(int i =0;i< A.getRowNum() ;i++){
        for(int j =0; j< A.getColNum() ;j++){
            A.arr[i][j] = arr[pos++];
        }

    }
}

void fillRand(Matrix& A){

    srand(time(NULL));
     for(int i=0;i<A.getRowNum();i++){
        for(int j=0;j<A.getRowNum();j++){

            A.arr[i][j]= rand() % 10+ 2; 
        }
    }

}


Matrix timeInverse(Matrix A){
   
  auto begin = std::chrono::system_clock::now();
  Matrix temp = A.inverse();

  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  std::cout << " finished at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << " seconds\n\n" ;
  
    return temp;
    
}
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

Matrix timeStrassen( Matrix A, Matrix B){

 
  auto begin = std::chrono::system_clock::now();
  
  Matrix temp= A.strassen(A,B);
  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  std::cout << " finished at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << " seconds\n\n";
    return temp;
    
}




int main(){

    
    // Matrix B(2,2);
    // fillMatrix(B);
    // Matrix C=B;

    // cout<<"\nPrinting Matrix C and B"<<endl;
    // B.print();
    // cout<<endl;
    // C.print();

    // cout<<"\nPrinting B*C"<<endl;
    // timeMult(B,C);
    // (B*C).print();

    // cout<<"\nPrinting B-C"<<endl;
    // timeSub(B,C);
    // (B-C).print();
    

    // int size = 2;
    // Matrix A(size,size);
    // int arr[]= {4,7,2,6};
    // fillMatrix(A,arr);
   
    // cout<<"printing A"<<endl;
    // // A.print();
    // cout<<"here";
    // Matrix temp=timeInverse(A);
    // cout<<"The inverse of  A is "<<endl;
    // temp.print();
    // cout<<"\n\n Check A*Ainverse"<<endl;
    // (A*temp).print();





    // cout<<"\nPrinting E"<<endl;
    // size=3;
    // int arr3[]= {4,3,0,6,5,2,9,7,3};
    // Matrix E (size,size);
    // fillMatrix(E,arr3);
    // E.print();

    // cout<<"\nFinding E^inverse"<<endl;
    //  temp=timeInverse(E);

    // temp.print();
    // cout<<"\nChecking the answer. SHould equal the idenity "<<endl;
    // (E* E.inverse()).print() ;

    //  int arr4[]= {2,3,1,-1,5,9,2,2,2};// from Dr. Anderson the inverse is below 
    //  Matrix K(size,size);


    // cout<<"\nCalc D^inverse printing D"<<endl;

    // size=4;
    // Matrix D (size,size);
    // int arr2[]= {5,-7,2,2,0,3,0,-4,-5,-8,0,3,0,5,0,-6};
    // fillMatrix(D, arr2);

    // cout<<"\nThe Matrix  D is "<<endl;
    // D.print();


    // cout<<"Testing D+D"<<endl;
    // timeAdd(D,D);
    // cout<<"Testing D-D"<<endl;
    // timeSub(D,D);


    // cout<<"\nThe inverse of  D is "<<endl;
    // (D.inverse()).print();

    // timeInverse(D);
    // cout<<"\n\n D*Dinverse\n"<<endl;
    // (D*D.inverse()).print();

    // cout<<"\n\ntesting extra credit Determinant On matrix D "<< D.determinant() <<endl;



    //  size=5;
    // Matrix F(size,size);
    // // int arr[]= {6,0,0,5,1,7,2,-5,2,0,0,0,8,3,1,8,}; // for testing det
    // int arr5[]= {1,3,-1,0,-2,0,2,-4,-2,-6,-2,-6,2,3,10,1,5,-6,2,-3,0,2,-4,5,9}; 
    
    // fillMatrix(F,arr5);
    // cout<<"Printing R "<<endl;
    // F.print();
    // cout<<"find inverse"<<endl;
    // temp=timeInverse(F);
    // temp.print();
    // cout<<"Checking inverse"<<endl;

    // (temp*F).print();





    int size=25;
    cout<<"Size="<<size<<endl;
    Matrix G(size,size);
    fillRand(G);
    cout<<"Printing G "<<endl;
    G.print();

    cout<<"find inverse"<<endl;
    Matrix temp=timeInverse(G);
    // Matrix temp = G.inverse();
    cout<<""<<endl;

    temp.print();
    cout<<"Checking inverse"<<endl;

    (temp*G).print();


    sleep(1);

    cout<<"making matricies of larger sizes and testing the inverse time "<<endl;


    // TODO: DONT PRINT THEM JUST FIND THE TIME IT TAKES TO CALCULATE THE INVERE 
    size=100;

    while(size!=1100){
        cout<<"Size="<<size<<endl;
         
        Matrix H(size,size);
        fillRand(H);
        // cout<<"Printing H "<<endl;
        // H.print();
        cout<<"find inverse"<<endl;
        temp=timeInverse(H);

        cout<<"find Add"<<endl;

        timeAdd(H,H);
        cout<<"find Sub"<<endl;

        timeSub(H,H);
        cout<<"find Mult"<<endl;

        timeMult(H,H);
        // temp.print();
        // cout<<"Checking inverse"<<endl;
        // Matrix ID(size,size);
        // ID=ID.makeIdentity();
        // (temp*H).print();
    

        size+=100;

    }
  











    // //    int arr[]= {1,0,1,2,0,2,2,4,1,2,3,4,2,4,4,4};
    // int arr[]= {1,-2,5,2,};


    //    int arr[]= {0,7,2,6};
    // int arr[]= {2,3,1,-1,5,9,2,2,2};// from Dr. Anderson


    // Matrix K(5,5);
    // fillMatrix(K);
    // Matrix l=K;
    // l=l*2;
    // l.print();
    // K.print();

    // l.strassen(l,K).print();

    // (l*K).print();


    cout<<" Strassens! - testing extra credit "<<endl;
    // Matrix J (3,3);
    // int arr8 [] = {1,2,3,1,2,3,1,2,3};
    // fillMatrix(J,arr8);
    // // J.inverse();

    // // J.paddStrassen(J, 4).print();
    // cout<<endl;

    // Matrix I (3,1);
    // int arr9 [] = {1,2,3};
    // fillMatrix(I,arr9);

    // // I.paddStrassen(I, 4).print();
    // cout<<endl;

    // Matrix newM = J.strassen(J,I);
    // newM.print();

    // cout<<" Multplying I * D with and without Strassens"<<endl;
    // (I.strassen(I, D)).print();
    // cout<<endl;
    // (I*D).print()
    



    // // Used to compare the times betwen regular matrix multiplication and Strassens ALgorithm
    // int power =9;
    // int size=2830;
   

    // while (size != 10000 ){
    //      Matrix A (size,size);
    //      fillMatrix(A);

    //     Matrix B=A;

    //     cout<<"\n\nSize="<<size<<endl;
    //     cout<<"Print regular multi"<<endl;
    //      timeMult(A,B);
    //      sleep(1);
    //     cout<<"\n\nPrint strassen "<<endl;
    //      timeStrassen(A,B);

    //     power++;
    //     size=pow(2,power);
    // }




    

}









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




