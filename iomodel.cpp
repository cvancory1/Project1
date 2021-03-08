/*
    Chloe VanCory
    Cosc 320 Project 1


   Used to calculate the dependencies for a nxn given matrix with inustries and sectors.
   Run by ./iomodel textfile

*/

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include<unistd.h>
#include<cmath>
#include <string>
#include <fstream>

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>// defines s_iread and s_iwrite
#include <stdio.h>


#include "matrix.h"
#include "heapq.h"

using namespace std;

// TODO: follow procedure to input the information from the file and store in an array??? 

int main(){
    string sectorName;
    string temp;

    ifstream infile;
    infile.open("data");
   
    if(!infile){
        cout << "Cannot find the file." << endl; 
    } else if(infile.peek() == EOF){
        cout<<endl;
        cout<<"The data.txt file is empty."<<endl;  
    }else{

        int fd;
        char buff[1];
        int numBytes;
        int offset=0;
        int numSectors=0; // determines the number of sectors
        char temp = '-';
        int dash = (int)temp;

        fd= open("data", O_RDONLY);
        if(fd!= -1){


            while ((numBytes = pread(fd, buff, 1,offset))>0 ){
                    cout<<"buff="<<buff[0]<<endl;
                  
                    if(buff[0]== '\n'){
                        cout<<"offset="<<offset<<endl;
                        numSectors++;
                    }else if(buff[0]== '-'){
                         break;

                    }
                    offset++;

                }
            }

        cout<<"numLines="<<numSectors<<endl;

        string *sectors = new string[numSectors];

        for(int i=0 ;i < numSectors ;i++){
            infile>>sectorName; 
            sectors[i]= sectorName;

        }
        cout<<"here"<<endl;
        infile>>sectorName;
        cout<<sectorName<<endl;

        for(int i=0 ;i < numSectors ;i++){
            cout<<sectors[i]<<endl;
        }

        Matrix iomodel(numSectors,numSectors);
        for(int i=0 ;i < numSectors ;i++){
             for(int j=0 ;j < numSectors ;j++){
                 double num;
                 infile>>num;
                //  cout<<"num="<<num<<endl;

                 iomodel.arr[i][j]= num;
                 cout<<"iomodel.arr[i][j]="<<iomodel.arr[i][j]<<endl;

                 
         
            }
        }
        cout<<"Printing matrix"<<endl;
        iomodel.print();




    }


    infile.close();

    /*
        TODO: main
        read in the file
        - strings
        - matrix
        - vector/matrix

        calculate the inverse 
        - call the algorithm

        returns a matrix inverse
        - multiply inverse matrix * the vector given from the input file
        - 
        


    */


    // cout<<"Amount of each product needed:"<<endl;

}