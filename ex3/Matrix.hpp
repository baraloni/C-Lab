//
// Created by baraloni, ex3 cpp 2018-19 winter semester.
// contains a generic matrix class with exceptions handling.
//

#ifndef EX3_MATRIX_HPP
#define EX3_MATRIX_HPP
#include <exception>
#include <vector>
#include "Complex.h"


//***********************************Exceptions***************************************************

/**
 * defines the type of objects thrown as exceptions to report a out of bound access to matrix error.
 */
struct MatrixOutOfBounds: public std::exception
{
    /**
     * holds the error info.
     * @return error informative msg
     */
    const char* what() const noexcept override
    {
        return "Matrix indexes out of bounds.";
    }
};

/**
 * defines the type of objects thrown as exceptions to report matrix dimension error.
 */
struct DimensionException: public std::exception
{
    /**
     * constructs new exception
     * */
    DimensionException():_msg("Dimensions Error"){};

    /**
     * holds the error info.
     * @return error informative msg
     */
    const char* what() const noexcept override
    {
        return (_msg+".\n").c_str();
    }
protected:
    /**the informative msg*/
    std::string _msg;
};

/**
 * defines the type of objects thrown as exceptions to report matrix dimension initialization error.
 */
struct InitDimension: public DimensionException

{
    /**
     * constructs new exception
     * */
    InitDimension():DimensionException()
    {
        _msg += ":\nMatrix initiation requires both zero dimensions, or both positive dimensions";
    };
};

/**
 * defines the type of objects thrown as exceptions to report matrix initialization error:
 * vector size and matrix dimensions are incompatible.
 */
struct InitVectorDimension: public DimensionException

{
    /**
     * constructs new exception
     * */
    InitVectorDimension():DimensionException()
    {
        _msg += ":\nMatrix initiation requires equality between "
                "product of dimensions and number of elements in the supplied vector";
    };
};

/**
 * defines the type of objects thrown as exceptions to report matrix dimension are
 * inconsiderate of operator.
 */
struct InconsiderateOfOperation: public DimensionException
{
    /**
     * constructs new exception
     * */
    InconsiderateOfOperation():DimensionException()
    {
        _msg += ":\ndoes not comply to operation";
    }

};

/**
 * defines the type of objects thrown as exceptions to report matrix dimension are
 * inconsiderate of operators '+', '-'
 */
struct addSubDimensions: public InconsiderateOfOperation
{
    /**
     * constructs new exception
     * */
    addSubDimensions():InconsiderateOfOperation()
    {
        _msg += ".\nadd and subtract requires equality on the matrices dimensions";
    }
};

/**
 * defines the type of objects thrown as exceptions to report matrix dimension are
 * inconsiderate of operator '*'.
 */
struct MulDimensions: public InconsiderateOfOperation
{
    /**
     * constructs new exception
     * */
    MulDimensions():InconsiderateOfOperation()
    {
        _msg += ".\nmultiply AB requires equality on the number of columns in A and the number of rows in B";
    }
};

/**
 * defines the type of objects thrown as exceptions to report matrix dimension are
 * inconsiderate of operator transpose.
 */
struct TransDimensions: public InconsiderateOfOperation
{
    /**
     * constructs new exception
     * */
    TransDimensions():InconsiderateOfOperation()
    {
        _msg += ".\ntranspose requires a squared matrix";
    }
};

//*********************************************Matrix**********************************************

/**
 * represents a General Matrix class
 * @tparam T: must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *            and copy-constructor, and zero-constructor.
 */
template <typename T>
class Matrix
{
private:
    //fields:
    /**
     * holds the matrix cells
     */
    std::vector<T> _matrix;
    /**
     * represents the matrix rows num
     */
    unsigned int _rows;
    /**
     * represents the matrix cols num
     */
    unsigned int _cols;

    //Helpers:
    /**
     * @param other matrix
     * @param b boolean value
     * @return b if the matrix is equal to this, otherwise : !b.
     */
    const bool isEqual(Matrix const& other, bool b) const;
    /**
     * @param other matrix
     * @param op function add or subtract
     * @return this matrix after applying op: op(this, other)
     */
    Matrix& addOrSubtract(Matrix const& other, void op(T&, T const&));

public:
    //Constructors:
    /**
     * constructs a new matrix of dimension 1X1 of (T)0
     */
    Matrix():Matrix(1, 1){}

    /**
     * constructs a new matrix of dimension rows X cols of (T)0
     * @param rows matrix num of rows
     * @param cols matrix num of cols
     */
    Matrix(const unsigned int rows, const unsigned int cols):
           Matrix(rows, cols, std::vector<T>(rows*cols, 0)){}

    /**
     * copy constructor
     * @param other matrix
     */
    Matrix(const Matrix& other) = default;

    /**
     * constructs a new matrix of dimensions rows X cols, filled in values from cells
     * @param rows matrix num of rows
     * @param cols matrix num of cols
     * @param cells holds the matrix entries
     */
    Matrix(const unsigned int rows, const unsigned int cols, const std::vector<T>& cells)
    :_matrix(cells), _rows(rows), _cols(cols){
        if ((rows > 0 && cols == 0) || (cols > 0 && rows == 0))
        {
            throw InitDimension{};
        }
        if(rows * cols != cells.size())
        {
            throw InitVectorDimension{};
        }
    }

    //Destructor:
    /**
     * destructor
     */
    ~Matrix() = default;

    //Operators:

        /**
         * @param other matrix
         * @return this matrix after the assignment
         */
        Matrix& operator=(Matrix const& other) = default;

        /**
         * @param other matrix
         * @return new matrix that represents the sum of adding this matrix and
         * the other matrix
         */
        Matrix operator+(Matrix const& other) const;

        /**
         * @param other matrix
         * @return new matrix that represents the difference of subtracting other
         * matrix from this matrix
         */
        Matrix operator-(Matrix const& other) const;

        /**
         * @param other matrix
         * @return new matrix that represents the product of multiplying this
         * matrix and the other matrix
         */
        Matrix operator*(Matrix const& other) const;

        /**
         * @param other matrix
         * @return true it the other matrix and this are equal, false otherwise
         */
        const bool operator==(Matrix const& other) const;

        /**
         * @param other matrix
         * @return false it the other matrix and this are equal, true otherwise
         */
        const bool operator!=(Matrix const& other) const;

        /**
         * @param r row num
         * @param c col num
         * @return the value of the matrix's cell[r,c]
         */
        T& operator()(unsigned int r, unsigned int c);

        /**
        * @param r row num
        * @param c col num
        * @return the value of the matrix's cell[r,c]
        */
        T const& operator()(unsigned int r, unsigned int c) const;

    //General functionality:
        /**
         * @return the num of cols of this matrix
         */
        inline const unsigned int cols() const {return _cols;}

        /**
         * @return the num of rows of this matrix
         */
        inline const unsigned int rows() const {return _rows;}

        /**
         * @return true if the matrix is square, false otherwise.
         */
        inline const bool isSquareMatrix() const {return _rows == _cols;}

        /**
         * @return a new matrix representing the transpose form of this matrix
         */
        Matrix trans() const;

        /**
        * names a const iterator of the matrix class
        * @tparam T: must implement the operators: +, -, -=, +=, *, ==, =, <<.
        *            and copy-constructor, and zero-constructor.
        */
        typedef typename std::vector<T>::const_iterator const_iterator;

        /**
         * @return constant iterator to the beggining of the matrix (first element)
         */
        inline const_iterator begin() const {return _matrix.cbegin();}

        /**
         * @return constant iterator to the end of the matrix (after last element)
         */
        inline const_iterator end() const {return _matrix.cend();}
};


//---------------------------------------Operators:

/**
 * prints the supplied matrix to the supplied stream
 * @tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @param os out stream
 * @param matrix matrix obj
 * @return the stream
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, Matrix<T> const& matrix)
{   unsigned int i = 0;
    const unsigned int cols = matrix.cols();
    for (auto it = matrix.begin() ; it != matrix.end(); ++it, ++i)
    {
        os << *it <<"\t";
        if(i % cols == cols -1)
        {
            os << std::endl;
        }
    }
    return os;
}

/**
 * @tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @param r row num
 * @param c col num
 * @return the value of the matrix's cell[r,c]
 */
template <typename T>
T& Matrix<T>::operator()(const unsigned int r, const unsigned int c)
{
    try{
        if(c < _cols && r < _rows)
        {
            return _matrix.at((r * _cols) + c);

        }
        throw MatrixOutOfBounds{};
    }
    catch (const std::out_of_range& e)
    {
        throw MatrixOutOfBounds{};
    }
}

/**
 * @tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @param r row num
 * @param c col num
 * @return the value of the matrix's cell[r,c]
 */
template <typename T>
const T& Matrix<T>::operator()(unsigned int r, unsigned int c) const
{
    try{
        if(c < _cols && r < _rows)
        {
            return _matrix.at((r * _cols) + c);

        }
        throw MatrixOutOfBounds{};
    }
    catch (const std::out_of_range& e)
    {
        throw MatrixOutOfBounds{};
    }
}

/**
 * @tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @param other matrix
 * @return true it the other matrix and this are equal, false otherwise
 */
template <typename T>
const bool Matrix<T>::operator==(Matrix const& other) const
{
    return this->isEqual(other, true);
}

/**
 * @tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @param other matrix
 * @return false it the other matrix and this are equal, true otherwise
 */
template <typename T>
const bool Matrix<T>::operator!=(Matrix const& other) const
{
    return this->isEqual(other, false);
}

/**
 * @tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @param other matrix
 * @return new matrix that represents the sum of adding this matrix and
 * the other matrix
 */
template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix const& other) const
{
    if (_cols == other.cols() && _rows == other.rows())
    {
        Matrix<T> tmp(*this);
        tmp.addOrSubtract(other, [](T &t1, T const &t2) -> void { t1 += t2; });
        return tmp;
    }
    throw addSubDimensions{};
}

/**
 *@tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @param other matrix
 * @return new matrix that represents the difference of subtracting other
 * matrix from this matrix
 */
template <typename T>
Matrix<T>  Matrix<T>::operator-(Matrix const& other) const
{
    if (_cols == other.cols() && _rows == other.rows())
    {
        Matrix<T> tmp(*this);
        tmp.addOrSubtract(other, [](T &t1, T const &t2) -> void { t1 -= t2; });
        return tmp;
    }
    throw addSubDimensions{};
}

/**
 *@tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @param other matrix
 * @return new matrix that represents the product of multiplying this
 * matrix and the other matrix
 */
template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix const& other) const
{
    if(_cols == other.rows())
    {
        std::vector<T> cells;
        for (unsigned int i = 0; i < _rows; ++i)
        {
            for (unsigned int j = 0; j < other.cols(); ++j)
            {
                T sum = 0;
                for (unsigned int k = 0; k < _cols; ++k)
                {
                    sum += ((*this)(i, k) * other(k, j));
                }
                cells.push_back(sum);
            }
        }
        return Matrix(_rows, other.cols(), cells);
    }
    throw MulDimensions{};
}

//-------------------------------------Heplers:

/**
 * I've implemented this function to re-use code
 * (instead of implementing one of ==, != , and negating the other)
 * @tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @param other matrix
 * @param b boolean value
 * @return b if the matrix is equal to this, otherwise : !b.
 */
template <typename T>
const bool Matrix<T>::isEqual(Matrix const& other, bool b) const
{
    if(_rows == other._rows && _cols == other.cols())
    {
        unsigned int i = 0;
        for (const_iterator it = other.begin(); it != other.end(); ++it, ++i)
        {
            if (*it != _matrix[i])
            {
                return !b;
            }
        }
        return b;
    }
    return !b;
}

/**

     */
/**
 * this function assumes that this & other are of equal dimensions
 * @tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @param other matrix
 * @param op function add or subtract
 * @return this matrix after applying op: op(this, other)
 */
template <typename T>
Matrix<T>& Matrix<T>::addOrSubtract(Matrix const& other,  void op(T&, T const&))
{
    unsigned int i = 0;
    for (auto it = other.begin(); it != other.end(); ++it, ++i)
    {
        op(_matrix[i], *it);
    }
    return *this;
}


//--------------------General functionality:

/**
 * @tparam T matrix item's type. must implement the operators: +, -, -=, +=, *, ==, =, <<.
 *        and copy-constructor, and zero-constructor.
 * @return a new matrix representing the transpose form of this matrix
 */
template <typename T>
Matrix<T> Matrix<T>::trans() const
{
    if (this->isSquareMatrix())
    {
        std::vector<T> cells;
        for (unsigned int i = 0; i < _cols; ++i)
        {
            for (unsigned int j = 0; j < _rows; ++j)
            {
                cells.push_back((*this)(j,i));
            }
        }
        return Matrix(_cols, _rows, cells);
    }
    throw TransDimensions{};
}

/**
 * @return a new matrix representing the transpose form of this Matrix<Complex>
 */
template <>
Matrix<Complex> Matrix<Complex>::trans() const
{
    if (this->isSquareMatrix())
    {
        std::vector<Complex> cells;
        for (unsigned int i = 0; i < _cols; ++i)
        {
            for (unsigned int j = 0; j < _rows; ++j)
            {
                cells.push_back((*this)(j,i).conj());
            }
        }
        return Matrix(_cols, _rows, cells);
    }
    throw TransDimensions{};
}


#endif //EX3_MATRIX_HPP
