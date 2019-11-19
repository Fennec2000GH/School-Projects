#include "matrix.cpp"

int main()
{
    Matrix m1 = {3, 3};
    Matrix m2 = {3, 3, 5};
    Matrix m3 = {3, 3};
    for(unsigned int i = 1; i <= 3; i++)
        for(unsigned int j = 1; j <= 3; j++)
            m3.set(i, j, i);
    cout << "3 x 3 Matrix with only 5's: " << endl;
    cout << m2 << endl;
    cout << "3 x 3 Matrix with each entry = row number: " << endl;
    cout << m3 << endl;
    cout << "Sum of the previous 2 Matrices: " << endl;
    cout << m2 + m3 << endl;
    cout << "1 x 3 vertical vector [1, 2, 3]: " << endl;
    Matrix m4 = m3.submatrix(1, 3, 3, 3);
    cout << m4 << endl;
    cout << "The transpose of the previous vector: " << endl;
    cout << m4.transpose() << endl;
    cout << "Matrix product of the first 2 matrices, " << endl;
    cout << "should be a 3 x 3 Matrix with only 30's: " << endl;
    cout << m2 * m3 << endl;
    cout << "The Matrix product of the first 2 matrices, " << endl;
    cout << "but in reverse order of multiplication: " << endl;
    cout << m3 * m2 << endl; 

    return 0;
}
