#include "Vector3D.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//---------------------Other methods:

    /**
     * @param other: a Vector3D object.
     * @return the distance between the other Vector3D object, and this Vector3D object.
     */
double Vector3D::dist(Vector3D const& other) const
{
    double dist = 0;
    for(unsigned int i = 0; i < 3; ++i)
    {
        dist += pow(other[i] - (*this)[i], 2);
    }
    return sqrt(dist);
}

    /**
     * @return the norm of this Vector3D Object.
     */
double Vector3D::norm() const
{
    double dist = 0;
    for(unsigned int i = 0; i < 3; ++i)
    {
        dist += pow((*this)[i], 2);
    }
    return sqrt(dist);
}

//---------------------Operators:
    /**
     * subtract the <second> Vector3D object from the <first> Vector3D object.
     * @param first: a Vector3D object.
     * @param second: a Vector3D object.
     * @return : a new Vector3D object, that holds the subtraction result.
     */
Vector3D operator-(Vector3D const& first, Vector3D const& second)
{
    Vector3D tmp(first);
    tmp += second;
    return tmp;
}

    /**
     * adds the <second> Vector3D object to the <first> Vector3D object.
     * @param first: a Vector3D object.
     * @param second: a Vector3D object.
     * @return : a new Vector3D object, that holds the addition result.
     */
Vector3D operator+(Vector3D const& first, Vector3D const& second)
{
    Vector3D tmp(first);
    tmp += second;
    return tmp;
}

    /**
     * updates this Vector3D object: adds the <other> Vector3D object to it.
     * @param other: a Vector3D object.
     * @return a reference to this object.
     */
Vector3D& Vector3D::operator+= (Vector3D const& other)
{
    for (unsigned int i = 0 ; i < 3; ++i)
    {
        (*this)[i] += other[i];
    }
    return *this;
}

    /**
      * updates this Vector3D object: subtracts the <other> Vector3D object from it.
      * @param other: a Vector3D object.
      * @return a reference to this object.
      */
Vector3D& Vector3D::operator-= (Vector3D const& other)
{
    for (unsigned int i = 0 ; i < 3; ++i)
    {
        (*this)[i] -= other[i];
    }
    return *this;
}

    /**
     * updates this Vector3D object to represent it's additive inverse.
     * @return: a reference to the object.
     */
Vector3D& Vector3D::operator-()
{
    (*this).operator*=(-1);
    return *this;
}
    /**
     * multiplies the <vec> Vector3D object by the <first> Vector3D object.
     * @param vec: a Vector3D object.
     * @param val: a double.
     * @return : a new Vector3D object, that holds the product.
     */
Vector3D operator*(Vector3D const& vec, const double val)
{
    Vector3D newVec(vec);
    newVec *= val;
    return newVec;
}

    /**
    * divides the <vec> Vector3D object by <val>. if val = 0: prints an error.
    * @param vec: a Vector3D object.
    * @param val: a double.
    * @return : a new Vector3D object, that holds the quotient.
    */
Vector3D operator/(Vector3D const& vec, const double val)
{
    Vector3D newVec(0, 0, 0);
    for (unsigned int i = 0 ; i < 3; ++i)
    {
        newVec[i] = vec[i] / val;
    }
    return newVec;
}

    /**
     * multiplies the <vec> Vector3D object by the <first> Vector3D object.
     * @param val: a double.
     * @param vec: a Vector3D object.
     * @return : a new Vector3D object, that holds the product.
     */
Vector3D operator*(const double val, Vector3D const& vec)
{
    Vector3D newVec(vec);
    newVec *= val;
    return newVec;
}

    /**
     * updates this Vector3D object: multiply it by <val>.
     * @param val: a double.
     * @return a reference to this object.
     */
Vector3D& Vector3D::operator*=(const double val)
{
    for (unsigned int i = 0 ; i < 3; ++i)
    {
        (*this)[i] *= val;
    }
    return *this;
}

    /**
     * updates this Vector3D object: divide it by <val>. if val = 0: prints an error.
     * @param val: a double.
     * @return a reference to this object.
     */
Vector3D& Vector3D::operator/=(const double val)
{
    if(val != 0)
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            (*this)[i] /= val;
        }
    }
    else
    {
        cout << DIVISION_BY_ZERO << endl;
    }
    return *this;
}

    /**
     * @param v1: Vector2D object.
     * @param v2: Vector2D object.
     * @return the distance between the 2 objects.
     */
double operator|(Vector3D const& v1, Vector3D const& v2)
{
    return v1.dist(v2);
}


    /**
     * @param v1: Vector2D object.
     * @param v2: Vector2D object.
     * @return: the scalar product of the two objects.
     */
double operator*(Vector3D const& v1, Vector3D const& v2)
{
    double res = 0;
    for (unsigned int i = 0 ; i < 3; ++i)
    {
        res += (v1[i] * v2[i]);
    }
    return res;
}

   /**
    * @param v1: Vector2D object.
    * @param v2: Vector2D object.
    * @return the angle between <v1> and <v2> in radians.
    */
double operator^(Vector3D const& v1, Vector3D const& v2)
{
    return (acos(v1*v2 / v1.norm()*v2.norm()) * PI) / 180 ;
}

    /**
     * reads the vector at the format: "vec[0] vec[1] vec[2]", from <is> to <vec>.
     * @param is: a out stream object.
     * @param vec: a Vector3D object.
     * @return the <is>. (to allow concatenating).
     */
istream& operator>>(istream& is, Vector3D& vec)
{
    is  >> vec[0] >> vec[1] >> vec[2];
    return is;
}

  /**
   * prints the vector at the format: "vec[0] vec[1] vec[2]" and \n, to <os>.
   * @param os: a out stream object.
   * @param vec: a Vector3D object.
   * @return the <os>. (to allow concatenating).
   */
ostream& operator<<(ostream& os, const Vector3D& vec)
{
    os << vec[0] << " " << vec[1] << " " << vec[2] << endl;
    return os;
}

   /**
    * assign this Vector3D with <other>'s attributes.
    * @param other : Vector3D object.
    * @return this vector, after the assignment.
    */
Vector3D& Vector3D::operator=(const Vector3D& other)
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
    * for modifying the Vector3D at <index>.
    * @param index: represents an index in a Vector3D.
    * @return the double at <index> place in this object.
    */
double& Vector3D::operator[](const unsigned int index)
{
    return this->_vector->at(index);
}
    /**
     * for accessing the Vector3D at <index>.
     * @param index: represents an index in a Vector3D.
     * @return the double at <index> place in this object.
     */
double Vector3D::operator[](const unsigned int index) const
{
    return this->_vector->at(index);
}

