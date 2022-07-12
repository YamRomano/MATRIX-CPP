#ifndef MatrixContainer_h
#define MatrixContainer_h
#include <iostream>
#include "Matrix.h"

#define INIT_SIZE 1
template <int rows, int cols, typename T = int>
class MatrixContainer
{
private:

    int top;
    int max;
    Matrix <rows, cols, T>* matArr;                           

public:
    /* *************************************************************************************
                                       CONSTRACTOR / DESTRUCTOR
    ************************************************************************************* */
    /**DEFAULT CONSTRACTOR**/
    MatrixContainer() :max(INIT_SIZE), matArr(new Matrix <rows, cols, T>[INIT_SIZE]), top(0) {};

    /**COPY CONSTRACTOR**/
    MatrixContainer( const MatrixContainer<rows, cols, T>& rhs) :max(rhs.max), matArr(new Matrix <rows, cols, T>[rhs.max]), top(rhs.top)
    {
        for (int i = 0; i < rhs.getTop; i++)
            addMatrix(rhs.getArray[i]);
    }

    /**DESTRUCTOR**/
    ~MatrixContainer()
    {
         delete[] matArr;
    }

    /* *************************************************************************************
                            ELEMENT FUNCTIONS
    ************************************************************************************* */
    /**ADD MATRIX TO THE MATRIX ARRAY**/
    void addMatrix( Matrix <rows, cols, T> mat)
    {
        if (isFull())
            increase();

        matArr[top] = mat;
        top++;
    }

    /**REMOVE LAST MATRIX IN MATRIX ARRAY**/
    void removeLastMatrix()
    {
        top--;
        if (isEmpty())
            decrease();
    }

    /* *************************************************************************************
                            SIZE MENTAIN FUNCTIONS
    ************************************************************************************* */

    /**RETURNS TRUE IF THE MATRIX ARRAY IS FULL AND FALSE IF NOT**/
    bool isFull()
    {
        return (top >= max);
    }

    /**RETURNS TRUE IF THE MATRIX ARRAY IS HALF FULL OR EMPTYER, AND TRUE IF NOT**/
    bool isEmpty()
    {
        return (top <= (max / 4));
    }

    /** IF THE MATRIX ARRAY IF FULL , DOUBLE THE ARRAY SIZE AND COPY THERE THE MATRIX ARRAY DATA**/
    void increase()
    {
        Matrix<rows, cols, T>* newMat = new Matrix<rows, cols, T>[max * 2];
        Matrix<rows, cols, T>* temp;
        temp = matArr;
        for (int i = 0; i < max; i++)
        {
            newMat[i] = matArr[i];
        }
        max *= 2;
        matArr = newMat;
        delete[] temp;
    }

    /** IF THE MATRIX ARRAY IF MORE THAN 1/4 EMPTY , HALVE THE ARRAY SIZE AND COPY THERE THE MATRIX ARRAY DATA**/
    void decrease()
    {
        Matrix <rows, cols, T>* newMat = new  Matrix <rows, cols, T>[max / 2];
        Matrix<rows, cols, T>* temp = matArr;
        for (int i = 0; i < max; i++)
        {
            newMat[i] = matArr[i];
        }
        max = max / 2;
        matArr = newMat;
        delete[] temp;
    }
    /**RETURNS THE AMOUNT OF MATRICES AT THE ARRAY**/
    int size()
    {
        return top;
    }
    /** RETURNS THE SIZE OF THE WHOLE ARRAY**/
    int limit()
    {
        return max;
    }

    /* *************************************************************************************
                            THE << OPERATOR
    ************************************************************************************* */
    /** PRINT FUNCTION **/
    friend std::ostream& operator << (std::ostream& os, const MatrixContainer<rows, cols, T>& arr)
    {
        std::cout << "There are " << arr.top << " matrices in the container.The matrices :"<< std::endl;
        for (int i = 0; i < arr.top; i++)
        {
            os << arr.matArr[i] << std::endl;
        }

        return os;
    }

    /* *************************************************************************************
                            ELEMENT FUNCTIONS
    ************************************************************************************* */
    /** MULTIPLICATION OF THE MATRIX IN SPECIFIC INDEX BY SCALAR **/
    Matrix <rows, cols, T> mulMatAtIndexByScalar(int i, int n) const
    {
        if (i < max && i >= 0)
            return matArr[i] * n;
        return matArr[0];
    }

    /** SUM OF TWO MATRICES IN SPECIFIC INDEXES **/
    Matrix<rows, cols, T> addMatricesAtIndexes(int i1, int i2)
    {
        if (i1 < max && i1 >= 0 && i2 < max && i2 >= 0)
            return (matArr[i1] + matArr[i2]);
        return matArr[0];
    }
};
#endif

