#include "matrix.cpp"
#include <iostream>
using namespace std;

Matrix::Matrix(int rowNum,int colNum){

    if(rowNum >= 0 && colNum >= 0){
        rows=rowNum;
        cols=colNum;
    } 
    arr = new double * [rows];
    // cout<<"arr"<< arr<<endl;

    for(int i=0; i<rows ; i++){
        arr[i] = new double [cols];

    }
}

Matrix:: ~Matrix(){
    for(int i=0; i<rows ; i++){
        delete [] arr[i];
    }
    delete  [] arr;
}


Matrix::Matrix(const Matrix & other){
    cols= other.cols;
    rows= other.rows;

    //have to create the new matrix using the "others" info 
    arr = new double * [rows];
    for(int i=0; i<rows ; i++){
        arr[i] = new double [cols];

    }

    // copies the data over
     for(int i=0; i<rows ; i++){
         for(int j=0; j<cols ; j++){
            arr[i][j] = other.arr[i][j];
         }
    }

}


// like a combination of the copy ctor and the destructor 
Matrix Matrix ::operator=(const Matrix& copyStack){
    
    // checks that they are not the same Matrix
    if(this!= & copyStack){
        // Just in case the old matrix has stuff in it so we need to delete 
        for(int i=0; i<rows ; i++){
            delete [] arr[i];
        }
        delete [] arr;

        // change the size to the new 
        cols= copyStack.cols;
        rows= copyStack.rows;

        // creates an array of "copystack" size
        arr = new double * [rows];
        for(int i=0; i<rows ; i++){
            arr[i] = new double [cols];
        }

        // copies the data over
         for(int i=0; i<rows ; i++){
            for(int j=0; j<cols ; j++){
                arr[i][j] = copyStack.arr[i][j];
            }   
        }
    }

    return *this;

}


int Matrix::getRowNum(){
    return rows;
}

int Matrix::getColNum(){
    return cols;
}

void Matrix::print(){

    for(int i=0;i < rows ;i++){
        for(int j=0 ;j< cols ;j++){
            // cout<< arr[i][j];
          printf("%.4f ", arr[i][j]);

        }
        cout<<endl;
    }
}



Matrix Matrix:: operator+ (const Matrix& rhs ){
    // cout<<"enter op+ "<<endl;
    // cout<<"this.cols "<<this->cols <<" rows="<< this->rows<<endl;

    // if matricies are the same size
    if(cols == rhs.cols && rows==rhs.rows ){
        Matrix temp(rhs.rows, rhs.cols);
        for(int i=0;i < rows ;i ++){
            for(int j=0;j < cols ;j++){
                temp.arr[i][j]= arr[i][j]+ rhs.arr[i][j];
            }
        }
        return temp;
    }else{
        cout<<"Addiiton ERROR :Invalid sizes"<<endl;
        return *this;
    }
   
}

Matrix Matrix::operator-( const Matrix& rhs){

    if(this->cols == rhs.cols && this->rows==rhs.rows ){
         Matrix temp(rhs.rows, rhs.cols);

        for(int i=0;i < rows ;i ++){
            for(int j=0;j < cols ;j++){
                temp.arr[i][j]= arr[i][j]- rhs.arr[i][j];
            }

        }
        return temp;

    }else{
        cout<<"Subtraction ERROR :Invalid sizes"<<endl;
        return *this;
    }

}


Matrix Matrix::operator*( const Matrix& rhs){

    // a valid matrix to multiply
    if(cols == rhs.rows ){
        int tempRows = rows;
        int tempCols = rhs.cols;

        // create the new matrix of the correct size
        Matrix temp(tempRows, tempCols);

        for(int i=0;i < tempRows ;i++){
            for(int j=0;j < rhs.cols ;j++){
                double sum=0;
                for(int k=0; k< cols; k++){
                    // cout<<"this->arr[i][k]="<<this->arr[i][k]<<" arr[k][j]="<<rhs.arr[k][j]<<endl;
                    sum+= arr[i][k]* rhs.arr[k][j];
                }
                temp.arr[i][j]=sum;
              
            }
        }
        return temp;
    }else{
        cout<<"Multiplication ERROR :Invalid sizes"<<endl;
        return *this;
    }

}



// scalar multiplication
Matrix Matrix::operator*( int scalar){
    Matrix B = *this;
    for(int i=0;i < rows ;i++){
        for(int j=0;j < cols ;j++){
            B.arr[i][j]*= scalar;
        }
    }
    return B;
}


Matrix Matrix::transpose(){

    // make a new matrix switching the rows and cols
    Matrix Atranspose( cols , rows);

    //user to traverse the Atranspose array 
    int rowPos=0;
    int colPos=0;

    int rowTpos=0;
    int colTpos=0;

    // for(int i =0; i< cols*rows; i++){

    for(int i =0; i< cols; i++){
        for(int j=0 ; j< rows ;j++){
             Atranspose.arr[i][j] = arr[j][i];
       }
    }

    // cout<<"transpose "<<endl;
    // Atranspose.print();
    return Atranspose;


}


// checks if two matricies are exactly the same
bool Matrix::operator==( const Matrix rhs){
    cout<<"OP EQUALS "<<endl;
    Matrix A=*this;
    // cout<<"here is the error out of bounds"<<endl;

    cout<<A.arr[0][1]<<endl;
    if(A.getRowNum()!= rhs.rows || A.getColNum() != rhs.cols){
        return false;
    }else{
         
         for(int i=0; i<A.getRowNum() ; i++){
            for(int j=0; j<A.getColNum() ; j++){

                cout<<A.arr[i][j]<<" "<< rhs.arr[i][j]<<endl;
                if( A.arr[i][j] != rhs.arr[i][j]){
                    return false;
                }
            }   
        }

        return true;

    }

}
 bool Matrix:: operator!=( const Matrix rhs){
     Matrix A =*this;

     if(A == rhs){
         return false;
     }else {
         return true;
     }


     


    //  cout<<"!="<<endl;
    //  Matrix A =*this;

    // if(A.getRowNum() != rhs.rows || A.getColNum() != rhs.cols){
    //    // cout<<"First"<<endl;

    //     return true;
    // }else{
    //    // cout<<"second"<<endl;
         
    //      for(int i=0; i<A.getRowNum() ; i++){
    //         for(int j=0; j<A.getColNum() ; j++){
    //                cout<<"arr[i][j] != rhs.arr[i][j]="<<A.arr[i][j] <<" "<<rhs.arr[i][j]<<endl;

    //             if( A.arr[i][j] != rhs.arr[i][j]){
    //             //    cout<<"arr[i][j] != rhs.arr[i][j]="<<A.arr[i][j] <<" "<<rhs.arr[i][j]<<endl;
    //             cout<<"NOT EQUAL HERE"<<endl;

    //                 return true;
    //             }
    //         }   
    //     }

    //     return false;

    // }

}


int Matrix::calcCofactor(Matrix A ,int index){
    Matrix newMtx (A.getRowNum()-1 , A.getColNum()-1);

        // start at the 1st index because we are always removing the top row
    int rowPos=0;
    int colPos=0;
    for(int i=1 ;i <A.getRowNum(); i++){
        for(int j =0 ;j< A.getColNum(); j++){
            if(j != index){
                newMtx.arr[rowPos][colPos++]= A.arr[i][j];

                if(colPos==newMtx.getColNum()){
                    colPos=0;
                    rowPos++;
                }
            }
        }
    }
    // cout<<"FINISH DIVIDING CALLING DET"<<endl;
    // newMtx.print();

    return newMtx.determinant();

    
}



int Matrix::determinant(){

    Matrix A =*this;
    int det=0;
    // by Invertibe matrix theorem 
    if(rows != cols){
        return false;
    }else {
        // testing for the 2x2 case where det A= ad-bc
        if(rows == 2){
            det= ( A.arr[0][0] * A.arr[1][1] ) - (A.arr[0][1] * A.arr[1][0] );
            // cout<<"det"<<det<<endl;
           
        }else{
            // calulates the the summation from 0 to n 
           for(int i=0;i< A.getRowNum() ;i++){
               det += pow(-1,i) * A.arr[0][i] * calcCofactor(A, i);
             
           }

        }
    }


    // cout<<" END det"<<det<<endl;

    return det;

}

bool Matrix:: isInvertible(){
    Matrix A= *this;
    int det= A.determinant();
    if(det !=0){
        return true;
    }else {
        return false;
    }

}        



Matrix Matrix::makeIdentity(){
    Matrix A =*this;
    // Matrix A (B.getRowNum(), B.getColNum());

    // cout<<"MAKEIDENITY "<<endl;
     for(int i =0;i < A.getRowNum() ;i++){
        for(int j =0; j < A.getColNum() ;j++){

            if(i==j){
                A.arr[i][i]=1;
                
            }else{
                A.arr[i][j]=0;
            }
            //  cout<<A.arr[i][j]<<"        CHHmaking ideneity" <<endl;
        }

    }
    cout<<"In idenity funcion"<<endl;
    A.print();
    return A;

}


Matrix Matrix::makeUpperTriang(){
    Matrix A = *this;
    int partition=0;
    for(int i=0 ;i<A.getRowNum() ;i++){
        int numPrinted=0;

        for(int j=0; j<A.getColNum() ;j++){
            if(numPrinted > partition){
                A.arr[i][j]=0;
            }
            numPrinted++;
        }
        partition++;
    }

    return A;
}

Matrix Matrix::makeLowerTriang(){
    Matrix A = *this;
    int partition=0;
    for(int i=0 ;i< A.getRowNum() ;i++){
        int numPrinted=0;

        for(int j=0; j<A.getColNum() ;j++){
            if(numPrinted < partition){
                A.arr[i][j]=0;
            }
            numPrinted++;
        }
        partition++;
    }

    return A;
}
// given any matrix A makes a smaller matrix that is a subset of A which gets returned
// used for the recursiveInverse 
Matrix Matrix::divideMatrix(Matrix A, int rowStart, int colStart, int numRows, int numCols){

    Matrix temp(numRows , numCols);
    cout<< "numRows"<<temp.rows<<"cols"<<temp.cols<<endl;
    // int rowPos= rowStart;
    // int colPos= colStart-1;

    int rowPos=0;
    int colPos=0;
    
    // cout<<"here"<<A.arr[rowPos][colPos]<<endl;
    //A.print();

    // rowstart and colstart include 0's in indexing
     for(int i= rowStart ;i < A.getRowNum(); i++){
         
        for(int j=colStart; j <A.getColNum(); j++){
            //sleep(1);

                if(rowPos< numRows && colPos <numCols){
                    temp.arr[rowPos][colPos++] = A.arr[i][j];
                    //    cout<<"i="<<i<<" j="<<j<<endl;
                    //     cout<<"temp1="<<temp1<<" temp2="<<temp2<<endl;
                    //     cout<<"num"<<temp.arr[temp1][temp2-1]<<endl;
                        //    cout<<"num"<<A.arr[i][j]<<endl;

                }

        }
        rowPos++;
        colPos=0;
        
     }

    return temp;

}




// Inputs: the original matrix (top left) and the identity matrix(bottom right) 
// adds 0's in top right an bottom left 
Matrix Matrix::paddedMatrix( Matrix A , Matrix  I){
    
    int paddedRow=A.getRowNum() + I.getRowNum();
    int paddedCol=A.getColNum() + I.getColNum();
    //puts("CI print");
    // A.print();
    // I.print();

    // makes a new matrix of size A and I 
    Matrix newMtx(paddedRow ,paddedCol );

    // keeps track of indexs for the Idenitity matrix
    int rowpos=0;
    int colpos=0;

    //cout<<"paddedRow"<<paddedRow<<"paddedCol"<<paddedCol<<endl;

    for(int i =0;i < paddedRow ;i++){
        for(int j =0; j < paddedCol ;j++){
            // fill the top left quad A
            if(i < A.getRowNum() && j < A.getColNum()){ 
                newMtx.arr[i][j]=A.arr[i][j];
                cout<<"first"<<endl;

            // top right 0
            }else if (i < A.getRowNum() && j >= A.getColNum()){
                newMtx.arr[i][j]=0;
                cout<<"second"<<endl;
            // bottom left
            }else if(i >= A.getRowNum() && j < A.getColNum()){
                newMtx.arr[i][j]=0;
                cout<<"third"<<endl;

            // bottom right
            }else if(i >= A.getRowNum() && j >= A.getColNum()){
                // cout<<"rowPos="<<rowpos<<" colpos="<<colpos<< " num="<<I.arr[rowpos][colpos]<<endl;
                newMtx.arr[i][j]=I.arr[rowpos][colpos++];
                if(colpos ==  I.getColNum() ){
                    cout<<"enter"<<endl;
                    colpos=0;
                    rowpos++;
                }
            }
        }
    }
     cout<<"print padded matrix"<<endl;
     newMtx.print();
    return newMtx;

}

// R T U V

Matrix Matrix::assembleMatrix( Matrix R ,Matrix  T ,Matrix  U ,Matrix  V){
    int paddedRow= R.getRowNum() + T.getRowNum();
    int paddedCol= R.getColNum() + U.getColNum();


    cout<<"             IN ASSEMBLED MATRIX  "<<endl;

    cout<<"PRINTIING R"<<endl;
    R.print();

    cout<<"PRINTIING T"<<endl;
    T.print();

    cout<<"PRINTIING U"<<endl;
    U.print();

cout<<"PRINTIING V"<<endl;
    V.print();







    
     // makes a new matrix of size A and I 
    Matrix newMtx(paddedRow ,paddedCol );

    // keeps track of indexs for the Bottom right matrix V
    int Vrowpos=0;
    int Vcolpos=0;

    // keeps track of indexs for the top right matrix T
    int Trowpos=0;
    int Tcolpos=0;

    // keeps track of indexs for the bottom left matrix U 
    int Urowpos=0;
    int Ucolpos=0;

    for(int i =0;i < paddedRow ;i++){
        for(int j =0; j < paddedCol ;j++){
            // fill the top left quad A
            if(i < R.getRowNum() && j < R.getColNum()){ 
                newMtx.arr[i][j]=R.arr[i][j];
                // cout<<"first"<<endl;
                cout<<"TOP LEFT "<< R.arr[i][j]<<endl;

            // top right 0
            }else if (i < R.getRowNum() && j >= R.getColNum()){
                newMtx.arr[i][j]= T.arr[Trowpos][Tcolpos++];
                // cout<<"second"<<newMtx.arr[i][j]<<endl;
                cout<<"top right"<<endl;

                if(Tcolpos ==  T.getColNum() ){
                    // cout<<"enter"<<endl;
                    Tcolpos=0;
                    Trowpos++;
                }
            // bottom left
            }else if(i >= R.getRowNum() && j < R.getColNum()){
                cout<<"INDEX OF THE BOTTOM RIGHT VrowPos=" << Vrowpos <<" VcolPos="<<Vcolpos<<endl;

                newMtx.arr[i][j]= U.arr[Urowpos][Ucolpos++];
                // cout<<"third"<< U.arr[Urowpos][Ucolpos++]<<endl;
                // cout<<"third"<<newMtx.arr[i][j]<<endl;
                cout<<"bottom left "<<endl;

                if(Ucolpos ==  U.getColNum() ){
                    // cout<<"enter"<<endl;
                    Ucolpos=0;
                    Urowpos++;
                }

            // bottom right
            }else if(i >= R.getRowNum() && j >= R.getColNum()){
                cout<<"INDEX OF THE BOTTOM RIGHT VrowPos=" << Vrowpos <<" VcolPos="<<Vcolpos<<endl;

                newMtx.arr[i][j]=V.arr[Vrowpos][Vcolpos++];


                // cout<<"fourth"<<newMtx.arr[i][j]<<endl;
                cout<<"bottom right"<<endl;
                if(Vcolpos ==  V.getColNum() ){
                    // cout<<"enter"<<endl;
                    Vcolpos=0;
                    Vrowpos++;
                }
            }

            // cout <<"Assemble matrix  num="<<newMtx.arr[i][j]<<endl;

        }
    }
    //  cout<<"print assembled matrix"<<endl;
    //  newMtx.print();

    return newMtx;





}


// recursive matrix call and assumes A is nxn , n -2^k, and A is symetric (i.e. A.T = A)
Matrix Matrix:: RecurseInverse(){
    Matrix A= *this;
    cout<<"     ENTER RECURSIVE \n origina A matrix that comes in "<<endl;
    A.print();
    // sleep(1);

    // base case 
    if(A.rows == 1 && A.cols ==1){
        cout<<"\n\nEntering the base case"<<endl;

        if(arr[0][0] != 0){
            double recipricol = 1.0/A.arr[0][0];
            A.arr[0][0]= recipricol;
        cout<<"rec="<<recipricol<<endl;

        // }else{
        //     A.arr[0][0]= 0;

        }
        A.print();
        return A;
    }
    // }else if(A.rows ==2 && A.arr[0][0]==0){
    //     A.determinant();
        
    // }

    int sizeOvertwo= A.rows/2;
    //1. divide A and into sub matricies where B,D  (top left bottom right) are  of size n/2
    Matrix B = divideMatrix(A, 0,0 ,sizeOvertwo ,sizeOvertwo);
    Matrix C = divideMatrix( A,sizeOvertwo ,0 , sizeOvertwo,sizeOvertwo );// ctranspose top right
    Matrix cT = divideMatrix(A, 0,sizeOvertwo ,sizeOvertwo, sizeOvertwo); // bottom left
    Matrix D = divideMatrix(A, sizeOvertwo, sizeOvertwo , sizeOvertwo , sizeOvertwo);


    //my checks
    cout<<"PRINTING B"<<endl;
    B.print();
    cout<<"\nPRINTING D"<<endl;
    D.print();

    cout<<"\nPRINTING C"<<endl;
    C.print(); cout<<"\nPRINTING cT"<<endl;
    cT.print();


    //2. recursively compute B inverse
    B = B.RecurseInverse();


    cout<<"B AFTER the INVERSE "<<endl;
    B.print();

    //3.Compute  wT=CB^-1 and  wT =B^-1CT
    Matrix W= C*B;
    Matrix wT= B*cT;


    cout<<"PRINTING W"<<endl;
    W.print();

    cout<<"\n\nPRINTING wT"<<endl;
    wT.print();

    
    //4. compute X=WcT
    Matrix X = W*cT;
    cout<<"X PRINT"<<endl;
    X.print();

    //5. compute S=D-X
    Matrix S = D-X;
    cout<<"S PRINT"<<endl;
    S.print();

    //6. recursively compute V=S^-1 inverse
    Matrix V= S.RecurseInverse();
    // V= S.RecurseInverse();
    cout<<"V PRINT after recursion"<<endl;
    V.print();


    //7. Compute Y =S^-1 W and yT - Moved the yT to after 8. b/c U= -Y 
    cout<<"y and yT PRINT"<<endl;

    Matrix Y = V*W;
    Matrix yT= Y.transpose();
    Y.print();
    yT.print();
    cout<<endl;


    cout<<"t and U PRINT"<<endl;
    //8. SetT= −yT and U=−Y.
    Matrix T = yT*-1;
    Matrix U= Y*-1;

    T.print();
    cout<<endl;
    U.print();

    //9. ComputeZ=wT*Y and set R=B^-1+Z.


    Matrix Z = wT *Y;
    cout<<" \nZ"<<endl;
    Z.print();


    Matrix R= B +Z;



    cout<<"\n R"<<endl;
    R.print();
    cout<<" \nT"<<endl;
    T.print();

    cout<<" \nU"<<endl;
    U.print();

    cout<<"\n V"<<endl;
    V.print();

    Matrix Ainverse = assembleMatrix(R,T,U,V);
    cout<<" Printing the Assembled matrix "<<endl;
    Ainverse.print();
    

//     // TODO: somehow when i send in test it is acessing something strange
//     Matrix ID (A.rows , A.cols);
//     ID= ID.makeIdentity();
//     // cout<<"ID MAtrix "<<endl;

//     // ID.print();
 
//     Matrix Test (A.getRowNum() , A.getColNum());
//     Test = A * Ainverse;

//     cout<<"A ROWS COLS"<< A.rows <<" "<<A.cols <<endl;
//     Test.print();

//     for(int i =0 ;i < A.rows ;i++){
//         for (int j=0; j< A.cols ;j++){
//             cout<<Test.arr[i][j];
//         }
//         cout<<endl;
//     }


//     cout<<"\n\n\n"<<endl;
//    // cout<<"HERE I AM "<<Test.arr[0][1]<< "print rows and cols"<<A.getRowNum() <<" "<<A.getColNum()<<" " <<endl;

//     cout<<"test "<<endl;
//     Test.print();


// ////////////////////////////

//     if(Test == ID){
//         cout<<"ID MATRIX YAY!!!!!!!!!!!!!!!!!"<<endl;

//     }else if(Test != ID){
//         cout<<"                 error printing \n Print A*AINVERSE  "<<endl;
//         (A * Ainverse).print();
//         cout<<"\n "<<endl;
//         // ID.print();


//     }

    cout<<" TESTING A* AT should == ID   "<<endl;
    Matrix test(A.getRowNum(), Ainverse.getColNum());
    test = A* Ainverse;
    test.print();

    cout<<test.arr[0][1]<<endl;

    return Ainverse;

}




// Properly checks that the matrix can be inverted and manipulates the matrix to be inverted recursively
 Matrix Matrix:: inverse(){
        Matrix A=*this; //makes a copy of this 
        Matrix newMtx(1,1);


        // stores the original dimensions of "A" b/c "A" will get reassigned later 
        int Arows= A.getRowNum();
        int Acols= A.getColNum();

        bool usedPadding=false; 
        bool madeSymetrical=false;


        // cout<<"here"<<endl;
        // AT.print();

            //TODO: throw error and create an else to nest the other statements
        if(A.isInvertible() == false){ 
            cout<<"This is not invertible. ERROR WILL BE THROWN  "<<endl;
        
        }


        
        Matrix AT= A.transpose();
      
        // if not symetric aka AT= A Then multiply to make symmetric 
       if(A != AT){ 
            madeSymetrical=true;
            // cout<<"A != A transpose"<<endl;
            cout<<"printing transpose"<<endl;
            AT.print();

            newMtx= AT * A; // guarentees matrix is not symmetric
            cout<<"printing AT*A transpose"<<endl;
            newMtx.print();

        }


        //Matrix Ideniity (3,3);
        cout<<"POWER OF 2 CHeCK"<<endl;

        // if not power of 2
        if( ceil(log2(rows)) != floor(log2(rows)) ){
            usedPadding= true;
            cout<<"         Before Padded matrix"<<endl;
            A.print();


            // cout<<"rows"<<rows<<endl;
            int nextPow = ceil(log2(rows));
            // cout<<"ceil="<<log2(rows)<<endl;
            // cout<<"nextPow="<<nextPow<<endl;

            int k= pow(2,nextPow) - rows;
            // cout<<"k="<<k<<endl;
            cout<<"    ID matix"<<endl;
            Matrix Ideniity(k,k);
            Ideniity = Ideniity.makeIdentity();
           
            Ideniity.print();


            newMtx = paddedMatrix(A, Ideniity);
            cout<<"    after Padded matrix"<<endl;

            newMtx.print();

        }



        Matrix inverse= newMtx.RecurseInverse();

        // extract the top left of the matrix 
        if(usedPadding ==true ){
            inverse = divideMatrix( inverse ,0, 0, Arows ,Acols); // divides based upon previous measurements??
            cout<<"extract top left"<<endl;
            inverse.print();
           
        }

        if(madeSymetrical ==true){
            cout<<"\nRemuultiplied matrix FIN ANS"<<endl;
            inverse = inverse *AT;
            inverse.print();

        }
        // return (A.transpose()*A).inverse() * A.transpose();


    return inverse;
 }




