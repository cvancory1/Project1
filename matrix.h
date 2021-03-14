#include "matrix.cpp"
#include <iostream>
using namespace std;

int numOp=0;

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

Matrix Matrix::operator-(  Matrix& rhs){
    Matrix A = *this;
    // cout<<"PRINTINT INCOMING MARIX"<<endl;
    // A.print();
    // rhs.print();


     if(A.getColNum() == rhs.cols && A.getRowNum()==rhs.rows ){
         Matrix temp(rhs.rows, rhs.cols);

        for(int i=0;i < A.getRowNum(); i++){
            for(int j=0;j < A.getColNum(); j++){
                temp.arr[i][j]= A.arr[i][j]- rhs.arr[i][j];
                // cout<<"A.arr[i][j]= "<<A.arr[i][j]<<"rhs.arr[i][j] "<<rhs.arr[i][j]<<endl;

            }

        }
        return temp;

    }else{
        cout<<"Subtraction ERROR :Invalid sizes"<<endl;
        return *this;
    }

}


Matrix Matrix::operator*( const Matrix& rhs){
    Matrix A= *this;

    try{
            // a valid matrix to multiply
        if(A.getColNum() == rhs.rows ){
            int tempRows = A.getRowNum();
            int tempCols = rhs.cols;

            // create the new matrix of the correct size
            Matrix temp(tempRows, tempCols);

            for(int i=0;i < tempRows ;i++){
                for(int j=0;j < rhs.cols ;j++){
                    double sum=0;
                    for(int k=0; k< cols; k++){
                        // cout<<"this->arr[i][k]="<<this->arr[i][k]<<" arr[k][j]="<<rhs.arr[k][j]<<endl;
                        sum+= A.arr[i][k]* rhs.arr[k][j];
                    }
                    temp.arr[i][j]=sum;
                
                }
            }
            return temp;
        }else{
            throw "Multiplication ERROR :Invalid sizes";
        }

    } catch ( const char* s ){
            return *this;
            printf("Error: %s\n", s);
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

    for(int i =0; i< cols; i++){
        for(int j=0 ; j< rows ;j++){
             Atranspose.arr[i][j] = arr[j][i];
       }
    }

    return Atranspose;


}


// checks if two matricies are exactly the same
bool Matrix::operator==( const Matrix rhs){
    // cout<<"OP EQUALS "<<endl;
    Matrix A=*this;
    // cout<<"here is the error out of bounds"<<endl;

    // cout<<A.arr[0][1]<<endl;
    if(A.getRowNum()!= rhs.rows || A.getColNum() != rhs.cols){
        return false;
    }else{
         
         for(int i=0; i<A.getRowNum() ; i++){
            for(int j=0; j<A.getColNum() ; j++){

                // cout<<A.arr[i][j]<<" "<< rhs.arr[i][j]<<endl;
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

}




double Matrix::calcCofactor(Matrix A ,int index){
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

    return newMtx.determinant();
    
}



double Matrix::determinant(){

    Matrix A =*this;
    double det=0;

    // by Invertibe matrix theorem 
    if(rows != cols){
        return false;
    }else {
        // testing for the 2x2 case where det A= ad-bc
        if(rows == 2){
            // A.print();
              det= ( A.arr[0][0] * A.arr[1][1] ) - (A.arr[0][1] * A.arr[1][0] );
           
        }else{
            // calulates the the summation from 0 to n 
           for(int i=0;i< A.getRowNum() ;i++){
                det += (pow(-1,i) * A.arr[0][i] )* calcCofactor(A, i);

           }
        }
    }

    return det;

}

bool Matrix:: isInvertible(){
    Matrix A= *this;
    int det= A.determinant();
    // cout<<"is invertible det="<<det<<endl;


    if(A.determinant() ==0){
        return false;
    }else {
        return true;
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
        }

    }
    return A;

}


// Matrix Matrix::makeUpperTriang(){
//     Matrix A = *this;
//     int partition=0;
//     for(int i=0 ;i<A.getRowNum() ;i++){
//         int numPrinted=0;

//         for(int j=0; j<A.getColNum() ;j++){
//             if(numPrinted > partition){
//                 A.arr[i][j]=0;
//             }
//             numPrinted++;
//         }
//         partition++;
//     }

//     return A;
// }

// Matrix Matrix::makeLowerTriang(){
//     Matrix A = *this;
//     int partition=0;
//     for(int i=0 ;i< A.getRowNum() ;i++){
//         int numPrinted=0;

//         for(int j=0; j<A.getColNum() ;j++){
//             if(numPrinted < partition){
//                 A.arr[i][j]=0;
//             }
//             numPrinted++;
//         }
//         partition++;
//     }

//     return A;
// }


Matrix Matrix:: makeZero(){
    Matrix A=*this;

    for(int i=0; i< A.getRowNum();i++){
        for(int j=0; j< A.getRowNum();j++){

            A.arr[i][j]=0;
        }
    }
    return A;
}

// given any matrix A makes a smaller matrix that is a subset of A which gets returned
// used for the recursiveInverse 
Matrix Matrix::divideMatrix(Matrix A, int rowStart, int colStart, int numRows, int numCols){

    Matrix temp(numRows , numCols);

    int rowPos=0;
    int colPos=0;

    // rowstart and colstart include 0's in indexing
     for(int i= rowStart ;i < A.getRowNum(); i++){
         
        for(int j=colStart; j <A.getColNum(); j++){
            //sleep(1);

                if(rowPos< numRows && colPos <numCols){
                    temp.arr[rowPos][colPos++] = A.arr[i][j];

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
                // cout<<"first"<<endl;

            // top right 0
            }else if (i < A.getRowNum() && j >= A.getColNum()){
                newMtx.arr[i][j]=0;
                // cout<<"second"<<endl;
            // bottom left
            }else if(i >= A.getRowNum() && j < A.getColNum()){
                newMtx.arr[i][j]=0;
                // cout<<"third"<<endl;

            // bottom right
            }else if(i >= A.getRowNum() && j >= A.getColNum()){
                // cout<<"rowPos="<<rowpos<<" colpos="<<colpos<< " num="<<I.arr[rowpos][colpos]<<endl;
                newMtx.arr[i][j]=I.arr[rowpos][colpos++];
                if(colpos ==  I.getColNum() ){
                    // cout<<"enter"<<endl;
                    colpos=0;
                    rowpos++;
                }
            }
        }
    }
    //  cout<<"print padded matrix"<<endl;
    //  newMtx.print();
    return newMtx;

}

// R T U V

Matrix Matrix::assembleMatrix( Matrix R ,Matrix  T ,Matrix  U ,Matrix  V){
    int paddedRow= R.getRowNum() + T.getRowNum();
    int paddedCol= R.getColNum() + U.getColNum();

    
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
                // cout<<"TOP LEFT "<< R.arr[i][j]<<endl;

            // top right 0
            }else if (i < R.getRowNum() && j >= R.getColNum()){
                newMtx.arr[i][j]= T.arr[Trowpos][Tcolpos++];
                // cout<<"second"<<newMtx.arr[i][j]<<endl;
                // cout<<"top right"<<endl;

                if(Tcolpos ==  T.getColNum() ){
                    // cout<<"enter"<<endl;
                    Tcolpos=0;
                    Trowpos++;
                }
            // bottom left
            }else if(i >= R.getRowNum() && j < R.getColNum()){
                // cout<<"INDEX OF THE BOTTOM RIGHT VrowPos=" << Vrowpos <<" VcolPos="<<Vcolpos<<endl;

                newMtx.arr[i][j]= U.arr[Urowpos][Ucolpos++];
                // cout<<"third"<< U.arr[Urowpos][Ucolpos++]<<endl;
                // cout<<"third"<<newMtx.arr[i][j]<<endl;
                // cout<<"bottom left "<<endl;

                if(Ucolpos ==  U.getColNum() ){
                    // cout<<"enter"<<endl;
                    Ucolpos=0;
                    Urowpos++;
                }

            // bottom right
            }else if(i >= R.getRowNum() && j >= R.getColNum()){
                // cout<<"INDEX OF THE BOTTOM RIGHT VrowPos=" << Vrowpos <<" VcolPos="<<Vcolpos<<endl;

                newMtx.arr[i][j]=V.arr[Vrowpos][Vcolpos++];


                // cout<<"fourth"<<newMtx.arr[i][j]<<endl;
                // cout<<"bottom right"<<endl;
                if(Vcolpos ==  V.getColNum() ){
                    // cout<<"enter"<<endl;
                    Vcolpos=0;
                    Vrowpos++;
                }
            }
        }
    }
    //  cout<<"print assembled matrix"<<endl;
    //  newMtx.print();

    return newMtx;





}


// recursive matrix call and assumes A is nxn , n -2^k, and A is symetric (i.e. A.T = A)
Matrix Matrix:: RecurseInverse(){
    Matrix A= *this;

    // base case 
    if(A.rows == 1 && A.cols ==1){
        // cout<<"\n\nEntering the base case"<<endl;

        if(arr[0][0] != 0){
            double recipricol = 1.0/A.arr[0][0];
            A.arr[0][0]= recipricol;
            // cout<<"rec="<<recipricol<<endl;

        }
        // A.print();
        return A;
    }

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

    // cout<<"\nPRINTING C"<<endl;
    // C.print(); cout<<"\nPRINTING cT"<<endl;
    // cT.print();


    //2. recursively compute B inverse
    B = B.RecurseInverse();


    // cout<<"B AFTER the INVERSE "<<endl;
    // B.print();

    //3.Compute  wT=CB^-1 and  wT =B^-1CT
    Matrix W= C*B;
    Matrix wT= B*cT;


    // cout<<"PRINTING W"<<endl;
    // W.print();

    // cout<<"\n\nPRINTING wT"<<endl;
    // wT.print();

    
    //4. compute X=WcT
    Matrix X = W*cT;
    // cout<<"X PRINT"<<endl;
    // X.print();

    //5. compute S=D-X
    Matrix S = D-X;
    // cout<<"S PRINT"<<endl;
    // S.print();

    //6. recursively compute V=S^-1 inverse
    Matrix V= S.RecurseInverse();
    // // V= S.RecurseInverse();
    // cout<<"V PRINT after recursion"<<endl;
    // V.print();


    //7. Compute Y =S^-1 W and yT - Moved the yT to after 8. b/c U= -Y 
    // cout<<"y and yT PRINT"<<endl;

    Matrix Y = V*W;
    Matrix yT= Y.transpose();
    // Y.print();
    // yT.print();
    // cout<<endl;


    // cout<<"t and U PRINT"<<endl;
    //8. SetT= −yT and U=−Y.
    Matrix T = yT*-1;
    Matrix U= Y*-1;

    // T.print();
    // cout<<endl;
    // U.print();

    //9. ComputeZ=wT*Y and set R=B^-1+Z.


    Matrix Z = wT *Y;
    // cout<<" \nZ"<<endl;
    // Z.print();


    Matrix R= B +Z;



    // cout<<"\n R"<<endl;
    // R.print();
    // cout<<" \nT"<<endl;
    // T.print();

    // cout<<" \nU"<<endl;
    // U.print();

    // cout<<"\n V"<<endl;
    // V.print();

    Matrix Ainverse = assembleMatrix(R,T,U,V);

    return Ainverse;

}




// Properly checks that the matrix can be inverted and manipulates the matrix so it can be inverted recursively
// to the function above
 Matrix Matrix:: inverse(){
        Matrix A=*this; //makes a copy of this 
        Matrix newMtx(1,1); 

        // stores the original dimensions of "A" b/c "A" will get reassigned later 
        int Arows= A.getRowNum();
        int Acols= A.getColNum();

        bool usedPadding=false; 
        bool madeSymetrical=false;



        try{
            // calcs the determinat to determine if the matrix is invertible 
            if(A.isInvertible() == false){ 
                throw "This is not invertible. ERROR!";

            }

        }catch ( const char* s ){
            printf("Error: %s\n", s);
        }
        

        if(A.getRowNum() ==1 && A.getColNum()==1){
            double det= 1/A.arr[0][0];
            newMtx.arr[0][0]= det;
            return newMtx;

        }else if(A.getRowNum() ==2 && A.getColNum()==2){
            Matrix temp (2,2);
            double det= A.determinant();
            det= 1/det;
            temp.arr[0][0]= A.arr[1][1] * det;
            temp.arr[0][1]= A.arr[0][1] * det *-1;
            temp.arr[1][0]= A.arr[1][0] * det*-1;
            temp.arr[1][1]= A.arr[0][0] * det;

            return temp;

        }

        // if not symetric aka AT= A Then multiply to make symmetric 
       Matrix AT= A.transpose();
       if(A != AT){ 
            madeSymetrical=true;
            newMtx= AT * A; // guarentees matrix is not symmetric

            // // cout<<"A != A transpose"<<endl;
            // cout<<"printing transpose"<<endl;
            // AT.print();

            // cout<<"printing AT*A transpose"<<endl;
            // newMtx.print();
        }


        // if not power of 2 padd the matrix with as [A, 0,0 ID]
        if( ceil(log2(rows)) != floor(log2(rows)) ){
            usedPadding= true;
            // cout<<"         Before Padded matrix"<<endl;
            // newMtx.print();
            // cout<<"rows"<<rows<<endl;
            int nextPow = ceil(log2(rows));
            int k= pow(2,nextPow) - rows;
            // cout<<"ceil="<<log2(rows)<<endl;
            // cout<<"nextPow="<<nextPow<<endl;
            // cout<<"k="<<k<<endl;
            // cout<<"    ID matix"<<endl;
            Matrix Ideniity(k,k);
            Ideniity = Ideniity.makeIdentity();

            newMtx = paddedMatrix( newMtx, Ideniity);


        }



        Matrix inverse= newMtx.RecurseInverse();

        // extract the top left of the matrix 
        if(usedPadding ==true ){
            inverse = divideMatrix( inverse ,0, 0, Arows ,Acols); // divides based upon previous measurements??
            // cout<<"extract top left"<<endl;
            // inverse.print();
           
        }

        if(madeSymetrical ==true){
            // cout<<"\nRemuultiplied matrix FIN ANS"<<endl;
            inverse = inverse *AT;
            // inverse.print();

        }




    return inverse;
 }


Matrix Matrix::padStrassen( Matrix A, int nextPow){
    Matrix  B (nextPow,nextPow) ;
    int rowNum = 0;
    int colNum = 0;

    // cout<<rowNum<<" "<<colNum<<endl;

    for(int i=0; i< nextPow ; i++){
        for(int j=0; j<nextPow ; j++){
            // cout<<"here"<<endl;

            if( i< A.getRowNum() && j<A.getColNum()){
                B.arr[i][j] = A.arr[rowNum][colNum++];

                if(colNum == A.getColNum()){
                    colNum=0;
                    rowNum++;
                }


            }else {
                B.arr[i][j]= 0;
            }

        }
    }
    return B;
}


/*
    Uses Strassens Algorithm . But also tests for 1x1 and if the input matrix is a power of 2. 
    If the input matrix isnt a power of 2 then the matricies get padded. Then the new matrix is exracted and 
    returned
*/

Matrix Matrix::strassen(Matrix B, Matrix C){
    
    //cant multiply 
    if(B.getColNum() != C.getRowNum()){
        cout<<"ERROR MULTIPLYING"<<endl;

    }else if((B.getRowNum() ==1 && B.getColNum()==1) && (C.getRowNum() ==1 && C.getColNum()==1) ){ //1x1 case
        Matrix mtx (1,1);
        mtx.arr[0][0]= B.arr[0][0] * C.arr[0][0];
        return mtx;
        
    }else if(ceil(log2(B.getColNum())) != floor(log2(B.getColNum()))){ // not a power of 2 so needs padding
        // cout<<"here in if statement printing the matricixies"<<endl;
        // B.print();
        // cout<<endl;
        // C.print();

        int nextPow = ceil(log2(B.getColNum()));
        int k= pow(2,nextPow);
        // cout<<"nextpow"<<k<<endl;
        // cout<<"here in if statement printing the matricixies"<<endl;

        Matrix newB = padStrassen( B, k);
        Matrix newC = padStrassen( C, k);

        // newB.print();
        // newC.print();

        // cout<<"here in if statement printing the matricixies"<<endl;

        // Matrix newMtx= strassen(newB,newC);
        // newMtx.print();


        return divideMatrix(strassen(newB,newC), 0, 0, B.getRowNum(), C.getColNum());


    }else { 

        int nOver2 = B.getRowNum()/2;

        Matrix A11 = B.divideMatrix(B,0,0, nOver2, nOver2);
        Matrix A12 = B.divideMatrix(B, 0,nOver2, nOver2, nOver2);
        Matrix A21 = B.divideMatrix(B,nOver2,0, nOver2, nOver2);
        Matrix A22 = B.divideMatrix(B,nOver2,nOver2, nOver2, nOver2);

        Matrix B11 = C.divideMatrix(C , 0 , 0 , nOver2, nOver2);
        Matrix B12 = C.divideMatrix(C , 0 , nOver2 , nOver2, nOver2);
        Matrix B21 = C.divideMatrix(C , nOver2, 0 , nOver2, nOver2);
        Matrix B22 = C.divideMatrix(C ,  nOver2, nOver2 , nOver2, nOver2);


        Matrix S1 = B12 - B22;
        Matrix S2 = A11 + A12;
        Matrix S3 = A21 +A22;
        Matrix S4 = B21 -B11;
        Matrix S5 = A11 +A22;
        Matrix S6 = B11 +B22;
        Matrix S7 = A12 -A22;
        Matrix S8 = B21 + B22;
        Matrix S9 = A11 - A21;
        Matrix S10 = B11+B12;

      

        Matrix P1 = A11 * S1;
        Matrix P2 = S2 * B22;
        Matrix P3 = S3 * B11;
        Matrix P4 = A22 * S4;
        Matrix P5 = S5 * S6;
        Matrix P6 = S7 * S8;
        Matrix P7 = S9 * S10;


        Matrix C11 = P5 + P4 - P2 +P6;
        Matrix C12 = P1 + P2;
        Matrix C21 = P3 + P4;
        Matrix C22 = P5 + P1 - P3 - P7;


        return assembleMatrix(C11, C12, C21, C22);

    }

}
