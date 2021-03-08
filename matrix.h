#include "matrix.cpp"

using namespace std;

Matrix::Matrix(int rowNum,int colNum){

    if(rowNum >= 0 && colNum >= 0){
        rows=rowNum;
        cols=colNum;
    } 
    arr = new int * [rows];
    // cout<<"arr"<< arr<<endl;

    for(int i=0; i<rows ; i++){
        arr[i] = new int [cols];

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
    arr = new int * [rows];
    for(int i=0; i<rows ; i++){
        arr[i] = new int [cols];

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
        arr = new int * [rows];
        for(int i=0; i<rows ; i++){
            arr[i] = new int [cols];
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
          printf("%d ", arr[i][j]);

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
                int sum=0;
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
    for(int i=0;i < rows ;i++){
        for(int j=0;j < cols ;j++){
            arr[i][j]*= scalar;
        }
    }
    return *this;
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

Matrix Matrix::cofactorExpansion(){




}



// checks if two matricies are exactly the same
bool Matrix::operator==( const Matrix& rhs){

    if(rows != rhs.rows || cols != rhs.cols){
        return false;
    }else{
         
         for(int i=0; i<rows ; i++){
            for(int j=0; j<cols ; j++){
                if( arr[i][j] != rhs.arr[i][j]){
                    return false;
                }
            }   
        }

        return true;

    }

}
 bool Matrix:: operator!=( const Matrix& rhs){
     cout<<"!="<<endl;
    if(rows != rhs.rows || cols != rhs.cols){
        cout<<"First"<<endl;

        return true;
    }else{
        cout<<"second"<<endl;
         
         for(int i=0; i<rows ; i++){
            for(int j=0; j<cols ; j++){
                   // cout<<"arr[i][j] != rhs.arr[i][j]="<<arr[i][j] <<" "<<rhs.arr[i][j]<<endl;

                if( arr[i][j] != rhs.arr[i][j]){

                    return true;
                }
            }   
        }

        return false;

    }

}


bool Matrix::isInvertible(){

    // by Invertibe matrix theorem 
    if(rows != cols){
        return false;
    }else {
        // testing for the 2x2 case where det A= ad-bc
        if(rows == 2){
             int det= (arr[0][0] * arr[1][1] ) - (arr[0][1] *arr[1][0] );
             cout<<"det"<<det<<endl;
             if(det !=0){
                 return true;
             }else {
                 return false;
             }
             
        }
        // TODO: make case when n is greater than a 2x2
        // call another function to calculate using kramers rule
    }

}


void Matrix::makeIdentity( Matrix& A){

     for(int i =0;i < A.getRowNum() ;i++){
        for(int j =0; j < A.getColNum() ;j++){

            if(i==j){
                A.arr[i][i]=1;
                
            }else{
                A.arr[i][j]=0;

            }
        }

    }

}


void Matrix::makeUpperTriang(Matrix& A){
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
}

void Matrix::makeLowerTriang(Matrix& A){
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
}
// given any matrix A makes a smaller matrix that is a subset of A which gets returned
// used for the recursiveInverse 
Matrix Matrix::divideMatrix(Matrix& A, int rowStart, int colStart, int numRows, int numCols){

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


// recursive matrix call and assumes A is nxn , n -2^k, and A is symetric (i.e. A.T = A)
Matrix Matrix:: RecurseInverse( Matrix& A){

    if(A.rows == 1 && A.cols ==1){
        if(A.arr[0][0]==0){
            A.arr[0][0]= 0;

        }else{
             double recipricol = 1.0/A.arr[0][0];
            //cout<<"rec="<<recipricol<<endl;
             A.arr[0][0]= recipricol;

        }
       
    }else{
            cout<<"hi="<<endl;

    }

    return A;
    

}

// Inputs: the original matrix (top left) and the identity matrix(bottom right) 
// adds 0's in top right an bottom left 
Matrix Matrix::paddedMatrix( Matrix& A , Matrix & I){
    
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
    // cout<<"print"<<endl;
    // newMtx.print();
    return newMtx;

}





// Properly checks that the matrix can be inverted and manipulates the matrix to be inverted recursively
 Matrix Matrix:: inverse( Matrix & A){
        // stores the original dimensions of "A" b/c "A" will get reassigned later 
        int Arows= A.getRowNum();
        int Acols= A.getColNum();

        
        Matrix Inverse(2,2); 
        // makeIdentity(A);
        Matrix Ideniity (3,3);

        bool usedPadding=false; 
        bool madeSymetrical=false;


        Matrix AT= A.transpose();
        // cout<<"here"<<endl;
        // AT.print();

        // if(!isInvertible()){ // non-Sing== Determinant. if det != 0 -> invertible
        //     cout<<"THis is not invertible "<<endl;
        //     //TODO: throw error and create an else to nest the other statements
        
        // }

        // if not symetric aka AT= A Then multiply to make symmetric 
       if(A != AT){ 
            cout<<"A != A transpose"<<endl;
            A= AT * A; // guarentees matrix is not symmetric
            cout<<"here2"<<endl;
            AT.print();
            madeSymetrical=true;

        }

        // if not power of 2
        if( ceil(log2(rows)) != floor(log2(rows)) ){
            // 
            int nextPow = ceil(log2(rows));
             cout<<"nextPow="<<nextPow<<endl;
            
            int k= pow(2,nextPow) - rows;
            cout<<"k="<<k<<endl;
            Matrix temp (k,k);
            Ideniity=temp;
            //Matrix Ideniity (2,2);

            makeIdentity(Ideniity);
            Ideniity.print();
            usedPadding= true;

        }


        cout<<"Before Padded matrix"<<endl;
        // Ideniity.print();
        A=paddedMatrix(A, Ideniity);
        A.print();


        // Matrix newMtx=RecurseInverse(A);
        Matrix newMtx=A;



        // extract the top left of the matrix 
        if(usedPadding ==true ){
            newMtx = divideMatrix( newMtx ,0, 0, Arows ,Acols); // divides based upon previous measurements??
            cout<<"extract top left"<<endl;
            newMtx.print();
        }

        if(madeSymetrical ==true){
            cout<<"\nRemuultiplied"<<endl;
            newMtx = newMtx *AT;
            newMtx.print();

        }

    return Inverse;
 }




