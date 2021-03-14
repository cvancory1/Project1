/*
    Chloe VanCory
    Cosc 320 Project 1


   Used to calculate the dependencies for a nxn given matrix with inustries and sectors.
   Run by ./iomodel textfile

   - Uses pread to record the number of sectors that the program will have without moving the "cursor". 
   So when infile is invoked the program knows exactly how many to read in before the "--- " In additon, the matris is nxn 
   and also based on the number of sectors, so the matrix is also constructed using this number. 
- Program also checks to make sure the file is not empty and that two arguments are passed in 
   

*/

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include<cmath>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>// defines s_iread and s_iwrite



#include "matrix.h"

using namespace std;


void makeSpaces(int numSpaces){
    for(int i=0; i< numSpaces ;i++){
        printf(" ");
    }
}


int main(int argc , char * argv[] ){

    if(argc !=2){
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
                
                if(buff[0]== '\n'){
                    numSectors++;
                }else if(buff[0]== '-'){
                        break;

                }
                offset++;

            }
        }


    string *sectors = new string[numSectors];

    for(int i=0 ;i < numSectors ;i++){
        infile>>sectorName; 
        sectors[i]= sectorName;

    }
    infile>>lines;


    Matrix iomodel(numSectors,numSectors);
    for(int i=0 ;i < numSectors ;i++){
            for(int j=0 ;j < numSectors ;j++){
                double num;
                infile>>num;
                iomodel.arr[i][j]= num;

                
        
        }
    }

    Matrix demand (numSectors,1);
    infile>>lines;

    for(int i=0 ;i < numSectors ;i++){
        int num;
        infile>>num;
        demand.arr[i][0]=num;
    }

    infile.close();

    Matrix ID(numSectors,numSectors);
    ID=ID.makeIdentity();




    Matrix x  =(ID-iomodel).inverse() * demand; 
    cout<<"Amount of each product needed:"<<endl;
     for(int i=0 ;i < numSectors ;i++){
        int length = strlen(sectors[i].data());
        
        printf("%s: ", sectors[i].data());
        makeSpaces(15- length);
        printf("%.2f units   \n",*x.arr[i]);

    }


    return 0;
}