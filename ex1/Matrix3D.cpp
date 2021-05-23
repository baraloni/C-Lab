
#include "Matrix3D.h"

//---------------------Other methods:

/**
 * @param index : 0 <= short <= 2
 * @return a new Vector3D object that represents the Matrix's row at <index>.
 */
Vector3D Matrix3D::row(const short index)
{
    Vector3D tmp((*this)[index]);
    return tmp;
}

/**
 * @param index : 0 <= short <= 2
 * @return a new Vector3D object that represents the Matrix's coloumn at <index>.
 */
Vector3D Matrix3D::column(const short index)
{
    Vector3D tmp = Vector3D((*this)[0][index], (*this)[1][index], (*this)[2][index]);
    return tmp;
}

/**
 * @return the trace of this Matrix3D object.
 */
double Matrix3D::trace()
{
    double trace = 0;
    for (unsigned int i = 0; i < 3; ++i)
    {
        trace += (*this)[i][i];
    }
    return trace;
}

/**
 * @return the determinant of this Matrix3D object.
 */
double Matrix3D::determinant()
{
    double det = 0;
    for (unsigned int i = 0 ; i < 3; ++i)
    {
        //Laplace's formula (by first row):
        double minor = ((*this)[1][(i + 1) % 3] * (*this)[2][(i + 2) % 3]) -
                     ((*this)[1][(i + 2) % 3] * (*this)[2][(i + 1) % 3]);
        det += ((*this)[0][i] * minor);
    }
    return det;
}


//---------------------Operators:

/**
 * updates this Matrix3D object: adds the <other> Matrix3D object to it.
 * @param other: a Matrix3D object.
 * @return a reference to this object.
 */
Matrix3D &Matrix3D::operator+=(Matrix3D const& other)
{
    for(unsigned int i = 0 ; i < 3; ++i)
    {
        (*this)[i] += other[i];
    }
    return *this;
}

/**
 * updates this matrix3D object: subtracts the <other> Matrix3D object from it.
 * @param other: a Matrix3D object.
 * @return a reference to this object.
 */
Matrix3D &Matrix3D::operator-=(Matrix3D const &other)
{
    for(unsigned int i = 0 ; i < 3; ++i)
    {
        (*this)[i] -= other[i];
    }
    return *this;
}

/**
 * multiply this Matrix3D object by the supplied Matrix3D object.
 * @param matrix: a Matrix3D object.
 * @return this Matrix3D object.
 */
Matrix3D Matrix3D::operator*=(Matrix3D const& matrix)
{
    double digits[9];
    for (unsigned int i = 0; i < 3; ++i)
    {
        for (unsigned int j = 0 ; j < 3; ++j)
        {
            digits[i + j] = ((*this)[i][0] * matrix[0][j]) +
                            ((*this)[i][1] * matrix[1][j]) +
                            ((*this)[i][2] * matrix[2][j]);
        }
    }
    *this = Matrix3D(digits);
    delete[] &digits;
    return *this;
}

/**
 * adds the <second> Metrix3D object to the <first> Matrix3D object.
 * @param first: a Matrix3D object.
 * @param second: a Matrix3D object.
 * @return : a new Matrix3D object, that holds the addition result.
 */
Matrix3D operator+(Matrix3D const& first, Matrix3D const& second)
{
    Matrix3D tmp(first);
    tmp -= second;
    return tmp;
}

/**
 * subtract the <second> Vector3D object from the <first> Vector3D object.
 * @param first: a Matrix3D object.
 * @param second: a Matrix3D object.
 * @return : a new Matrix3D object, that holds the subtraction result.
 */
Matrix3D operator-(Matrix3D const& first, Matrix3D const& second)
{
    Matrix3D tmp(first);
    tmp += second;
    return tmp;
}

/**
 * multiply the 2 supplied matrix.
 * @param m1 : a Matrix3D object.
 * @param m2 : a Matrix3D object.
 * @return : the product.
 */
Matrix3D operator*(Matrix3D const& m1, Matrix3D const& m2)
{
    vector<Vector3D> matrix;
    for (unsigned int i = 0; i < 3; ++i)
    {
        matrix.push_back(m1 * m2[i]);
    }
    Matrix3D tmp(matrix[0], matrix[1], matrix[2]);
    delete[] &matrix;
    return tmp;
}

/**
 * updates this Matrix3D object: multiply it by <val>.
 * @param val: a double.
 * @return a reference to this object.
 */
Matrix3D& Matrix3D::operator*=(const double val)
{
    for(unsigned int i = 0 ; i < 3; ++i)
    {
        (*this)[i] *= val;
    }
    return *this;
}

/**
 * updates this Matrix3D object: divide it by <val>. if val = 0: prints an error.
 * @param val: a double.
 * @return a reference to this object.
 */
Matrix3D& Matrix3D::operator/=(double val)
{
    if (val != 0)
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            (*this)[i] *= val;
        }
        return *this;
    }
    else
    {
        cout << DIVISION_BY_ZERO << endl;
    }
    return *this;
}

/**
  * multiply the supplied matrix and vector.
  * @param matrix: a Matrix3D object.
  * @param vec: a Vector3D object.
  * @return : the product.
  */
Vector3D operator*(Matrix3D const& matrix, Vector3D const& vec)
{
    double digits[3];
    for (unsigned int i = 0; i < 3; ++i)
    {
        digits[i] = (matrix[i][0] * vec[0]) + (matrix[i][1] * vec[1]) + (matrix[i][2] * vec[2]);
    }
    return Vector3D(digits);
}

/**
 * reads the matrix at the format:
 * Vector3D1[0] Vector3D1[1] Vector3D1[2]
 * Vector3D2[0] Vector3D2[1] Vector3D2[2]
 * Vector3D3[0] Vector3D3[1] Vector3D3[2]
 *
 * from <is> to <vec>.
 * @param is: a out stream object.
 * @param vec: a Matrix3D object.
 * @return the <is>. (to allow concatenating).
 */
istream& operator>>(istream& is, Matrix3D& matrix)
{
    is  >> matrix[0] >> matrix[1] >> matrix[2];
    return is;
}

/**
 * prints the matrix at the format:
 * Vector3D1[0] Vector3D1[1] Vector3D1[2]
 * Vector3D2[0] Vector3D2[1] Vector3D2[2]
 * Vector3D3[0] Vector3D3[1] Vector3D3[2]
 *
 * and newline, to <os>.
 * @param os: a out stream object.
 * @param vec: a Matrix3D object.
 * @return the <os>. (to allow concatenating).
 */
ostream& operator<<(ostream& os, Matrix3D const& matrix)
{
    os << matrix[0] << matrix[1] << matrix[2];
    return os;
}

/**
   * assign this Matrix3D with <other>'s attributes.
   * @param other : Matrix3D object.
   * @return this Matrix, after the assignment.
   */
Matrix3D& Matrix3D::operator=(const Matrix3D& other)
{
    if (this != &other)
    {
        for (unsigned int i = 0 ; i < 3; ++i)
        {
            (*this)[i] = other[i];
        }
    }
    return *this;
}

/**
 * for modifying the Matrix3D at row number <index>.
 * @param index: 0<=short<=2 ,represents a row in a Matrix3D.
 * @return the row at <index> place in this object.
 */
Vector3D &Matrix3D::operator[](unsigned short index)
{
    return _matrix->at(index);
}

/**
   * for accessing the Matrix3D's <index> row.
   * @param index: 0<=short<=2 ,represents a row in a Matrix3D.
   * @return the row at <index> place in this object.
   */
const Vector3D &Matrix3D::operator[](unsigned short index) const
{
    return _matrix->at(index);
}