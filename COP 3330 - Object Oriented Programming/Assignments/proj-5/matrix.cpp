/*
Name: Caijun Qin
Course and Section: COP3330-0009
Project: 5
Summary: Creates representations of matrices using a single array of
unsigned integers. Allows basic matrix operations including summation
and matrix product.
*/
#include <iostream> 
#include "matrix.h"

//CONSTRUCTORS
Matrix::Matrix(unsigned int row, unsigned int column, unsigned int value)
{
    //storage type is row major by default
    numRows = row;
    numCols = column;
    storageType = 'r';
    unsigned int size = row * column;
    array = new unsigned int[size];
    for(unsigned int i = 0; i < size; i++)
        array[i] = value;
}

Matrix::Matrix(const Matrix & b)
{
    //copies all member data of Matrix b to the calling Matrix object
    numRows = b.numRows;
    numCols = b.numCols;
    storageType = b.storageType;
    unsigned int size = b.numRows * b.numCols;
    array = new unsigned int[size];
    for(unsigned int i = 0; i < size; i++)
        array[i] = b.array[i];
}

//DESTRUCTORS
Matrix::~Matrix()
{
    delete [] array;
}

//ACCESSORS / NON-MUTATORS
int Matrix::numofrows() const
{
    return numRows;
}

int Matrix::numofcols() const
{
    return numCols;
}

int Matrix::get(unsigned int r, unsigned int c) const
{
    //index of array containing the entry (*this)_ij
    unsigned int index;
    unsigned int size = numRows * numCols;
    if(storageType == 'r')
    {
        index = (r - 1) * numCols + (c - 1);
        if(index >= 0 && index <= size - 1)
            return array[index];
    } else if(storageType == 'c') {
        index = (c - 1) * numRows + (r - 1);
        if(index >= 0 && index <= size - 1)
            return array[index];
    }
    return -1;
}

void Matrix::printinternal() const
{
    //prints out the entries from array in one line
    unsigned int size = numRows * numCols;
    for(unsigned int i = 0; i < size; i++)
        cout << array[i] << "\t";
    cout << endl;
    return;
}

Matrix Matrix::transpose() const
{
    //converts row i into column i
    //the same thing as converting column i into row i
    //each entry (*this)_ij turns into (*this)_ji
    Matrix b(numCols, numRows);

    //creates a copy of array by making a copy of the object
    Matrix copy(*this);

    //assigning values to array in b
    for(unsigned int i = 1; i <= b.numRows; i++)
        for(unsigned int j = 1; j <= b.numCols; j++)
            b.set(i, j, copy.get(j, i));
    return b;
}

Matrix Matrix::submatrix(unsigned int startrow, unsigned int endrow, unsigned int startcol, unsigned int endcol) const
{
    //crop and return a copy of the matrix with dimensions no larger than the original dimensions
    if(endrow < startrow || endcol < startcol ||startrow > numRows || startcol > numCols ||
            startrow < 0 || endrow < 0 || startcol < 0 || endcol < 0)
        {
            Matrix b(numRows, numCols);
            return b;
        } else {
            unsigned int b_numRows = endrow - startrow + 1;
            unsigned int b_numCols = endcol - startcol + 1;
            Matrix b(b_numRows, b_numCols);
            unsigned int index = 0;
            for(int i = startrow; i <= endrow; i++)
                for(int j = startcol; j <= endcol; j++)
                {
                    b.array[index] = get(i, j);
                    ++index;
                }
            return b;
        }
}

//MUTATORS
bool Matrix::set(unsigned int r, unsigned int c, unsigned int value)
{
    //sets a value to the entry at the ith row and jth column
    unsigned int index;
    unsigned int size = numRows * numCols;
    if(storageType == 'r')
    {
        index = (r - 1) * numCols + (c - 1);
        if(index >= 0 && index <= size - 1)
        {
            array[index] = value;
            return true;
        }
    } else if(storageType == 'c')
    {
        index = (c - 1) * numRows + (r - 1);
        if(index >= 0 && index <= size - 1)
        {
            array[index] = value;
            return true;
        }
    }
    return false;
}

void Matrix::torowmajor()
{
    //if storage is by column, converts to by row
    if(storageType == 'r')
        return;
    else {
        //creates a copy of array by making a copy of the object
        Matrix copy(*this);

        //reconfigures original array with a different storage format
        unsigned int index = 0;
        for(unsigned int i = 1; i <= numRows; i++)
            for(unsigned int j = 1; j <= numCols; j++)
                {
                    array[index] = copy.get(i, j);
                    ++index;
                }
        storageType = 'r';
        return;
    }
}

void Matrix::tocolumnmajor()
{
    //if storage is by row, converts to by column
    if(storageType == 'c')
        return;
    else
    {
        //creates a copy of array by making a copy of the object
        Matrix copy(*this);

        //reconfigures original array with a different storage format
        unsigned int index = 0;
        for(unsigned int j = 1; j <= numCols; j++)
            for(unsigned int i = 1; i <= numRows; i++)
            {
                array[index] = copy.get(i, j);
                ++index;
            }
        storageType = 'c';
        return;
    }
}

//OPERATOR OVERLOADING
Matrix & Matrix::operator = (const Matrix & b)
{
    if(this != &b) {
        delete [] array;
        numRows = b.numRows;
        numCols = b.numCols;
        unsigned int size = b.numRows * b.numCols;
        array = new unsigned int[size];
        for(unsigned int i = 0; i < size; i++)
            array[i] = b.array[i];
    }
    return *this;
}
Matrix Matrix::operator + (const Matrix & b) const
{
    //returns the summation of two Matrix objects
    //both matrices must have same dimensions
    Matrix c(numRows, numCols);
    if(numRows == b.numRows && numCols == b.numCols) {
        for(unsigned int i = 1; i <= numRows; i++)
            for(unsigned int j = 1; j <= numCols; j++)
                c.set(i, j, get(i, j) + b.get(i, j));
    }
    return c;
}

Matrix Matrix::operator * (const Matrix & b) const
{
    //returns the matrix product of two Matrix objects
    Matrix c(numRows, b.numCols);

    //matrices must have dimensions m x n and n x p
    if(numCols == b.numRows)
    {
        unsigned int size = c.numRows * c.numCols;
        delete [] c.array;
        c.array = new unsigned int[size];
        for(unsigned int i = 1; i <= c.numRows; i++)
            for(unsigned int j = 1; j <= c.numCols; j++)
            {
                //entry of C at the ith row and jth column
                unsigned int entry = 0;
                for(unsigned int k = 1; k <= numCols; k++)
                    entry += get(i, k) * b.get(k, j);
                c.set(i, j, entry);
            }
    }
    return c;
}

ostream & operator << (ostream & out, const Matrix & b)
{
    //prints out the Matrix object
    for(unsigned int i = 1; i <= b.numRows; i++)
        for(unsigned int j = 1; j <= b.numCols; j++)
        {
            if(j < b.numCols)
                out << b.get(i, j) << "\t";
            else
                out << b.get(i, j) << endl;
        }
    return out;
}
