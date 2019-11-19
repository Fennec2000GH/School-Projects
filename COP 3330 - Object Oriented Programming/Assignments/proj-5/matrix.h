/*
Name: Caijun Qin
Course and Section: COP3330-0009
Project: 5
Summary: Creates representations of matrices using a single array of
unsigned integers. Allows basic matrix operations including summation
and matrix product.
*/
#ifndef MATRIX_H
#define MATRIX_H 
using namespace std;

class Matrix
{
public:
    //CONSTRUCTORS
    Matrix(unsigned int row = 5, unsigned int column = 5, unsigned int value = 0);
    Matrix(const Matrix & b);

    //DESTRUCTORS
    ~Matrix();

    //ACCESSORS / NON-MUTATORS
    int numofrows() const;
    int numofcols() const;
    int get(unsigned int r, unsigned int c) const;
    void printinternal() const;
    Matrix transpose() const;
    Matrix submatrix(unsigned int startrow, unsigned int endrow, unsigned int startcol, unsigned int endcol) const;

    //MUTATORS
    bool set(unsigned int r, unsigned int c, unsigned int value);
    void torowmajor();
    void tocolumnmajor();

    //OPERATOR OVERLOADING
    Matrix & operator = (const Matrix & b);
    Matrix operator + (const Matrix & b) const;
    Matrix operator * (const Matrix & b) const;
    friend ostream & operator << (ostream & out, const Matrix & b);

private:
    //MEMBER DATA
    unsigned int numRows, numCols;
    char storageType;
    unsigned int * array;

};

#endif
