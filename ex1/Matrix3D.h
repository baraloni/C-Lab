#include <iostream>
#include <vector>
#include <cmath>
#include "Vector3D.h"

#ifndef MATRIX3D_H
#define MATRIX3D_H
/** error format for division by zero.*/
#define DIVISION_BY_ZERO "Error: attempted division by zero."

/** represents a 3X3 matrix of doubles*/
class Matrix3D
{
private:
    /**
     * holds the matrix (3 vectors of size 3).
     */
    vector<Vector3D> *_matrix;

public:

//-----------Constructors:

/**
 * initializes a new Matrix3D of the format:
 * d1 d2 d3
 * d4 d5 d6
 * d7 d8 d9
 * @param d1: double.
 * @param d2: double.
 * @param d3: double.
 * @param d4: double.
 * @param d5: double.
 * @param d6: double.
 * @param d7: double.
 * @param d8: double.
 * @param d9: double.
 */
Matrix3D(const double d1, const double d2, const double d3, const double d4, const double d5,
         const double d6, const double d7, const double d8, const double d9):
         _matrix(new vector<Vector3D>{Vector3D(d1, d2, d3), Vector3D(d4, d5, d6), Vector3D(d7, d8, d9)}){};

      /**
        * default constructor: construct a new matrixr of size 3x3 initialized to 0.
        */
Matrix3D():
         Matrix3D(0, 0, 0, 0, 0, 0, 0, 0, 0)
         {}

         /**
          * initializes a new Matrix3D which has the value d in its main diagonal. (other places : 0)
          * @param d: the value on the diagonal.
          */
explicit Matrix3D(double d):
         Matrix3D(d, 0, 0, 0, d, 0, 0, 0, d)
         {}

         /**
          * initializes a new Matrix3D of the format:
          * digits[0] digits[1] digits[2]
          * digits[3] digits[4] digits[5]
          * digits[6] digits[7] digits[8]
          * @param digits : array of doubles.
          */
explicit Matrix3D(double digits[9]):
         Matrix3D(digits[0], digits[1], digits[2], digits[3],
         digits[4], digits[5], digits[6], digits[7], digits[8])
         {}

         /**
          * initializes a new Matrix3D of the format:
          * digits[0][0] digits[0][1] digits[0][2]
          * digits[1][0] digits[1][1] digits[1][2]
          * digits[2][0] digits[2][1] digits[2][2]
          * @param digits: array of 3 arrays that holds 3 doubles.
          */
explicit Matrix3D(double digits[3][3]):
         Matrix3D(digits[0][0], digits[0][1], digits[0][2], digits[1][0],
         digits[1][1], digits[1][2], digits[2][0], digits[2][1], digits[2][2])
         {}

         /**
          * initializes a new Matrix3D of the format:
          * <v1>
          * <v2>
          * <v3>
          * @param v1 : Vector3D object.
          * @param v2 : Vector3D object.
          * @param v3 : Vector3D object.
          */
Matrix3D(Vector3D v1, Vector3D v2, Vector3D v3):
         Matrix3D(v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], v3[0], v3[1], v3[2])
         {}

         /**
          * copy constructor: creates a new Matrix3D object, with identical entries to <other>'s entries.
          * @param other: Matrix3D object.
          */
Matrix3D(Matrix3D const& other):
         Matrix3D(other[0][1], other[0][1], other[0][2], other[1][0],
         other[1][1], other[1][2], other[2][0], other[2][1], other[2][2])
         {}

//-----------Destructor:

/**
 * deletes this Matrix3D object (frees memory).
 */
~Matrix3D()
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            delete &_matrix[i];
        }
        delete _matrix;
    }

//-----------Operators:

    /**
     * updates this Matrix3D object: adds the <other> Matrix3D object to it.
     * @param other: a Matrix3D object.
     * @return a reference to this object.
     */
    Matrix3D& operator+=(Matrix3D const& other);

    /**
     * updates this matrix3D object: subtracts the <other> Matrix3D object from it.
     * @param other: a Matrix3D object.
     * @return a reference to this object.
     */
    Matrix3D& operator-=(Matrix3D const& other);

    /**
     * multiply this Matrix3D object by the supplied Matrix3D object.
     * @param matrix: a Matrix3D object.
     * @return this Matrix3D object.
     */
    Matrix3D operator*=(Matrix3D const& matrix);

    /**
     * adds the <second> Metrix3D object to the <first> Matrix3D object.
     * @param first: a Matrix3D object.
     * @param second: a Matrix3D object.
     * @return : a new Matrix3D object, that holds the addition result.
     */
    friend Matrix3D operator+(Matrix3D const& first, Matrix3D const& second);

    /**
     * subtract the <second> Vector3D object from the <first> Vector3D object.
     * @param first: a Matrix3D object.
     * @param second: a Matrix3D object.
     * @return : a new Matrix3D object, that holds the subtraction result.
     */
    friend Matrix3D operator-(Matrix3D const& first, Matrix3D const& second);

    /**
     * multiply the 2 supplied matrix.
     * @param m1 : a Matrix3D object.
     * @param m2 : a Matrix3D object.
     * @return : the product.
     */
    friend Matrix3D operator*(Matrix3D const& m1, Matrix3D const& m2);

    /**
     * updates this Matrix3D object: multiply it by <val>.
     * @param val: a double.
     * @return a reference to this object.
     */
    Matrix3D& operator*=(double val);

    /**
     * updates this Matrix3D object: divide it by <val>. if val = 0: prints an error.
     * @param val: a double.
     * @return a reference to this object.
     */
    Matrix3D& operator/=(double val);

    /**
     * multiply the supplied matrix and vector.
     * @param matrix: a Matrix3D object.
     * @param vec: a Vector3D object.
     * @return : the product.
     */
    friend Vector3D operator*(Matrix3D const& matrix, Vector3D const& vec);

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
    friend istream& operator>>(istream& is, Matrix3D& matrix);

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
    friend ostream& operator<<(ostream& os, Matrix3D const& matrix);

    /**
     * assign this Matrix3D with <other>'s attributes.
     * @param other : Matrix3D object.
     * @return this Matrix, after the assignment.
     */
    Matrix3D& operator=(const Matrix3D& other);


    /**
     * for modifying the Matrix3D at row number <index>.
     * @param index: 0<=short<=2 ,represents a row in a Matrix3D.
     * @return the row at <index> place in this object.
     */
    Vector3D& operator[](unsigned short index);

    /**
     * for accessing the Matrix3D's <index> row.
     * @param index: 0<=short<=2 ,represents a row in a Matrix3D.
     * @return the row at <index> place in this object.
     */
    const Vector3D& operator[](unsigned short index) const;

//-----------Methods:
    /**
     * @param index : 0 <= short <= 2
     * @return a new Vector3D object that represents the Matrix's row at <index>.
     */
    Vector3D row(short index);

    /**
     * @param index : 0 <= short <= 2
     * @return a new Vector3D object that represents the Matrix's coloumn at <index>.
     */
    Vector3D column(short index);

        /**
         * @return the trace of this Matrix3D object.
         */
    double trace();

    /**
     * @return the determinant of this Matrix3D object.
     */
    double determinant();
};
#endif //MATRIX3D_H
