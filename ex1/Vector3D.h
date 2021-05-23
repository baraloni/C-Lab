using namespace std;
#include <iostream>
#include <vector>
#include <cmath>

#ifndef VECTOR3D_H
#define VECTOR3D_H

/** error format for division by zero.*/
#define DIVISION_BY_ZERO "Error: attempted division by zero."
/** represents pi*/
#define PI 3.14

/** class representing a 3-dimensional vector.*/
class Vector3D
{

private:
    /**
     * holds the vector
     */
    vector<double> *_vector;

public:
    //--------------------constructors:
    /**
     * default constructor: construct a new vector of size 3 initialized to 0.
     */
    Vector3D():Vector3D(0, 0, 0){}

    /**
     * construct a new vector of size 3, that is: (a b c).
     * @param a: double representing the vector's first entry.
     * @param b: double representing the vector's second entry.
     * @param c: double representing the vector's third entry.
     */
    Vector3D(const double a, const double b, const double c): _vector(new vector<double> {a, b, c}){}

    /**
     * construct a new vector from <arr>.
     * @param arr: array of 3 doubles, holding the vector's entries.
     */
    explicit Vector3D(const double arr[3]): Vector3D(arr[0], arr[1], arr[2]){}

    /**
     * copy constructor: creates a new Vector3D object, with identical entries to <other>'s entries.
     * @param other: Vector3D object.
     */
    Vector3D(const Vector3D& other):Vector3D(other[0], other[1], other[2]){}


    //---------------------destructor:

    /**
     * deletes this Vector3D object (frees memory).
     */
    ~Vector3D()
    {
        delete _vector;
    }


    //---------------------Methods:

    /**
     * @param other: a Vector3D object.
     * @return the distance between the other Vector3D object, and this Vector3D object.
     */
    double dist(Vector3D const& other) const;

    /**
     * @return the norm of this Vector3D Object.
     */
    double norm() const;

    //---------------------Operators:

    /**
     * subtract the <second> Vector3D object from the <first> Vector3D object.
     * @param first: a Vector3D object.
     * @param second: a Vector3D object.
     * @return : a new Vector3D object, that holds the subtraction result.
     */
    friend Vector3D operator-(Vector3D const& first, Vector3D const& second);

    /**
     * adds the <second> Vector3D object to the <first> Vector3D object.
     * @param first: a Vector3D object.
     * @param second: a Vector3D object.
     * @return : a new Vector3D object, that holds the addition result.
     */
    friend Vector3D operator+(Vector3D const& first, Vector3D const& second);

    /**
     * updates this Vector3D object: adds the <other> Vector3D object to it.
     * @param other: a Vector3D object.
     * @return a reference to this object.
     */
    Vector3D& operator+= (Vector3D const& other);

    /**
      * updates this Vector3D object: subtracts the <other> Vector3D object from it.
      * @param other: a Vector3D object.
      * @return a reference to this object.
      */
    Vector3D& operator-= (Vector3D const& other);

    /**
     * updates this Vector3D object to represent it's additive inverse.
     * @return: a reference to the object.
     */
    Vector3D& operator-();

    /**
     * multiplies the <vec> Vector3D object by the <first> Vector3D object.
     * @param vec: a Vector3D object.
     * @param val: a double.
     * @return : a new Vector3D object, that holds the product.
     */
    friend Vector3D operator*(Vector3D const& vec, double val);

    /**
     * divides the <vec> Vector3D object by <val>. if val = 0: prints an error.
     * @param vec: a Vector3D object.
     * @param val: a double.
     * @return : a new Vector3D object, that holds the quotient.
     */
    friend Vector3D operator/(Vector3D const& vec, double val);

    /**
     * multiplies the <vec> Vector3D object by the <first> Vector3D object.
     * @param val: a double.
     * @param vec: a Vector3D object.
     * @return : a new Vector3D object, that holds the product.
     */
    friend Vector3D operator*(double val, Vector3D const& vec);

    /**
     * updates this Vector3D object: multiply it by <val>.
     * @param val: a double.
     * @return a reference to this object.
     */
    Vector3D& operator*=(double val);

    /**
     * updates this Vector3D object: divide it by <val>. if val = 0: prints an error.
     * @param val: a double.
     * @return a reference to this object.
     */
    Vector3D& operator/=(double val);

    /**
     * @param v1: Vector2D object.
     * @param v2: Vector2D object.
     * @return the distance between the 2 objects.
     */
    friend double operator|(Vector3D const& v1, Vector3D const& v2);

    /**
     * @param v1: Vector2D object.
     * @param v2: Vector2D object.
     * @return: the scalar product of the two objects.
     */
    friend double operator*(Vector3D const& v1, Vector3D const& v2);

    /**
     * @param v1: Vector2D object.
     * @param v2: Vector2D object.
     * @return the angle between <v1> and <v2> in radians.
     */
    friend double operator^(Vector3D const& v1, Vector3D const& v2);

    /**
     * reads the vector at the format: "vec[0] vec[1] vec[2]", from <is> to <vec>.
     * @param is: a out stream object.
     * @param vec: a Vector3D object.
     * @return the <is>. (to allow concatenating).
     */
    friend istream& operator>>(istream& is, Vector3D& vec);

    /**
     * prints the vector at the format: "vec[0] vec[1] vec[2]" and \n, to <os>.
     * @param os: a out stream object.
     * @param vec: a Vector3D object.
     * @return the <os>. (to allow concatenating).
     */
    friend ostream& operator<<(ostream& os, Vector3D const& vec);

    /**
     * assign this Vector3D with <other>'s attributes.
     * @param other : Vector3D object.
     * @return this vector, after the assignment.
     */
    Vector3D& operator=(const Vector3D& other);

    /**
     * for modifying the Vector3D at <index>.
     * @param index: represents an index in a Vector3D.
     * @return the double at <index> place in this object.
     */
    double& operator[](unsigned int index);

    /**
     * for accessing the Vector3D at <index>.
     * @param index: represents an index in a Vector3D.
     * @return the double at <index> place in this object.
     */
    double operator[](unsigned int index) const;
};
#endif //VECTOR3D_H