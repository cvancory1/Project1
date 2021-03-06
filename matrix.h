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

    cout<<"transpose "<<endl;
    Atranspose.print();
    return Atranspose;


}



