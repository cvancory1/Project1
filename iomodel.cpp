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

int main(int argc , char * argv[] ){


    if(argc !=2){
        // TODO: throw error
        cout<<"Must pass in 2 args."<<endl;
        return 1;
    }

    ifstream infile;
    infile.open(argv[1]);
   
    if(!infile){
        cout << "Cannot find the file.\n" << endl; 
        return 2;

    } else if(infile.peek() == EOF){
        cout<<endl;
        cout<<"The data.txt file is empty.\n"<<endl;  
        return 3;

    }

    string sectorName,lines;
    int fd;
    char buff[1];
    int numBytes;
    int offset=0;
    int numSectors=0; // determines the number of sectors
    char temp = '-';
    int dash = (int)temp;

    fd= open( argv[1], O_RDONLY);
    if(fd!= -1){


        while ((numBytes = pread(fd, buff, 1,offset))>0 ){
                // cout<<"buff="<<buff[0]<<endl;
                
                if(buff[0]== '\n'){
                    // cout<<"offset="<<offset<<endl;
                    numSectors++;
                }else if(buff[0]== '-'){
                        break;

                }
                offset++;

            }
        }

    // cout<<"numLines="<<numSectors<<endl;

    string *sectors = new string[numSectors];

    for(int i=0 ;i < numSectors ;i++){
        infile>>sectorName; 
        sectors[i]= sectorName;

    }
    // cout<<"here"<<endl;
    infile>>lines;
    cout<<lines<<endl;

    for(int i=0 ;i < numSectors ;i++){
        // cout<<sectors[i]<<" sectors"<<endl;
    }

    Matrix iomodel(numSectors,numSectors);
    for(int i=0 ;i < numSectors ;i++){
            for(int j=0 ;j < numSectors ;j++){
                double num;
                infile>>num;
            //  cout<<"num="<<num<<endl;

                iomodel.arr[i][j]= num;
            //  cout<<"iomodel.arr[i][j]="<<iomodel.arr[i][j]<<endl;

                
        
        }
    }
    cout<<"\nPrinting matrix"<<endl;
    iomodel.print();


    Matrix demand (numSectors,1);
    infile>>lines;
    cout<<lines<<endl;

    for(int i=0 ;i < numSectors ;i++){
        int num;
        infile>>num;
        demand.arr[i][0]=num;
        // cout<<demand.arr[i][0]<<"dependencies"<<endl;
    }

    infile.close();

    Matrix ans = iomodel; // just to make sure the apporopriate size look over TODO:
    Matrix I=iomodel;
    I.makeIdentity();// identity

    ans= (iomodel - ans).inverse() ;
    cout<<"AFTER INVERSE IS CALLED"<<endl;
    ans.print();


    ans= ans * demand;
    

    cout<<ans.getRowNum() <<" "<<ans.getColNum()<<endl;


    
    cout<<"DEMAND"<<endl;
    demand.print();
    cout<<"Amount of each product needed:"<<endl;
     for(int i=0 ;i < numSectors ;i++){
        // cout<<demand.arr[i][0]<<"dependencies"<<endl;
    }
    ans.print();


    



    return 0;
}