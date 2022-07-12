#ifndef Matrix_h
#define Matrix_h
#include <iostream>
#include <string.h>

#define EPSILON 0.00001
#define DEFAULT 0.00000


template <int rows, int cols, typename T = int>
class Matrix
{
private:
    T matrixData[rows][cols];

public:
    /* *************************************************************************************
                            CONSTRACTOR / DISTRACTOR FUNCTIONS
    ************************************************************************************* */
    /**DEFAULT CONSTRACTOR**/
/// Creating new matrix, while for each new row ,providing new colum.
/// Changing each element to requested value (if provided).
/// If not provided, initialazing the cells with defult value (0).
    Matrix(T x = DEFAULT)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrixData[i][j] = x;

    }
    /**COPY CONSTRACTOR**/
/// Creating new matrix, while for each new row ,providing new colum.
/// Changing each element in index (i,j) to the (i,j) value of RHS metrix element by element.
    Matrix(const Matrix < rows, cols, T>& rhs)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrixData[i][j] = rhs.matrixData[i][j];
    }
    /* *************************************************************************************
                            ELEMENT FUNCTIONS
    ************************************************************************************* */
    /**GET IDENTITY MATRIX**/
/// Creating new matrix with the defult zero value.
/// And changing each element in main diagonal to 1.
/// This function returns: pointer to new identity matrix that created.
    static Matrix<rows, cols, T> getIdentityMatrix()
    {
        Matrix<rows, cols, T> result;
        int x = rows <= cols ? rows : cols;
        for (int i = 0; i < x; i++)
        {
            result.matrixData[i][i] = 1;
        }
        return result;
    }
    /**GET DIAGONAL**/
/// Creating new array size of the largest between rows and columns.
/// Initialazing the array with value on main diagonal (with index (i,i)).
/// This function returns: pointer to the created array.
    T* getDiag(int& x) const
    {
        x = rows <= cols ? rows : cols;
        T* diagArr = new T[x];

        for (int i = 0; i < x; i++)
            diagArr[i] = matrixData[i][i];

        return diagArr;
    }

    /** CONVERTING FUNCTION**/
/// Creating integer to sum into it the main daigonal elements.
/// Going over (i,i) elements, while i is growingg till it is size of the largest between rows and columns.
/// Adding to the sum the value on main diagonal (with index (i,i)).
/// This function returns: the sum of main diagonal.
    operator T() const
    {
        T sum = 0;
        for (int i = 0; i < (rows >= cols ? cols : rows); i++)
            sum += matrixData[i][i];

        return sum;
    }
    /* *************************************************************************************
                            THE << OPERATOR
    ************************************************************************************* */
    /** PRINT FUNCTION **/
/// This function provided with the text output and matrix.
/// Going over a nested for loop and adding each element to the output followed by space.
/// After each row we adding a linebreake.
/// This function returns: the output.
    friend std::ostream& operator<< (std::ostream& output, const Matrix<rows, cols, T>& rhs)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                output << rhs.matrixData[i][j] << " ";
            }
            output << std::endl;
        }
        return output;
    }
    /* *************************************************************************************
                        THE = OPERATOR
    ************************************************************************************* */
    /// This function provided with RHS matrix we would like to copy into calling matix.
    /// Changing each element in index (i,j) to the (i,j) value of RHS metrix element by element.
    /// This function returns: referance to the changed matrix.
    Matrix<rows, cols, T>& operator= (const T& rhs)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrixData[i][j] = rhs;
        return *this;
    }
/* *************************************************************************************
                        THE + OPERATOR
************************************************************************************* */
    /**MATRIX + MATRIX (ELEMENT BY ELEMENT)**/
/// This function provided with RHS matrix we would like to add to the calling matix.
/// We create new matrix and going over its cells in a nested for loop.
/// Changing each element in index (i,j) to the (i,j) value of RHS metrix + the (i,j) value of calling metrix.
/// This function returns: referance to the new matrix that contains the wanted sum.

    Matrix<rows, cols, T> operator + (const Matrix<rows, cols, T>& rhs) const
    {
        Matrix<rows, cols, T> newMat;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                newMat.matrixData[i][j] = matrixData[i][j] + rhs.matrixData[i][j];
        return newMat;
    }
    /**MATRIX + SCALAR (ELEMENT BY ELEMENT)**/
/// This function provided with RHS scalar we would like to add to the calling matrix.
/// Here, we are using Scalar + Matrix function ,while using its syntax.
/// As we know, the sum of both cases is the same, so we just return referance to the new 
/// matrix with the right values that was created in the Scalar + Matrix function.
    Matrix<rows, cols, T> operator+ (const T& rhs) const
    {
        return *this + Matrix<rows, cols, T>(rhs);
    }

    /* *************************************************************************************
                             THE - OPERATOR
    ************************************************************************************* */
    /**MATRIX - MATRIX (ELEMENT BY ELEMENT)**/
/// This function provided with RHS matrix we would like to add to the calling matrix.
/// Here, we are using Matrix + Matrix function ,while using its syntax.
/// We return referance to the new matrix with the right values that was created in the Matrix + Matrix function.
    Matrix<rows, cols, T> operator - (const Matrix<rows, cols, T>& rhs) const
    {
        return *this + (-rhs);
    }
    /**MATRIX - SCALAR (ELEMENT BY ELEMENT)**/
/// This function provided with RHS scalar we would like to add to the calling matrix.
/// Here, we are using  Matrix + Scalar function ,while using its syntax.
/// We return referance to the new matrix with the right values that was created in the Matrix + Scalar function.
    Matrix<rows, cols, T> operator - (const T& rhs) const
    {
        return *this + (-rhs);
    }
    /* *************************************************************************************
                            THE * OPERATOR
    ************************************************************************************* */
    /**MATRIX * MATRIX (BY THE DEFINITION)**/
/// This function provided with RHS matrix we would like to multiply by the calling matrix.
/// Here, we are using  Matrix + Scalar function ,while using its syntax.
/// We return referance to the new matrix with the right values that was created in the Matrix + Scalar function.
    Matrix<rows, cols, T> operator* (const Matrix<rows, cols, const T>& rhs) const
    {
        if (cols == rows)//Else the multiplication not defined.
        {
            Matrix <rows, cols, T> resultMat; // New matrix suitable size.

            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    for (int k = 0; k < rows; k++)
                        resultMat->matrixData[i][j] += matrixData[i][k] * matrixData[k][j];

            return resultMat;
        }
        return *this;
    }

    /**MATRIX * SCALAR (ELEMENT BY ELEMENT)**/
    /// This function provided with RHS scalar we would like to multiply to the calling matrix.
    /// Here, we are using  Scalar * Matrix function ,while using its syntax.
    /// We return referance to the new matrix with the right values that was created in the Scalar * Matrix function.
        Matrix<rows, cols, T> operator* (const T& rhs) const
    {
        Matrix<rows, cols, T> newM(*this);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols;j++)
                newM.matrixData[i][j] *= rhs;
        return newM;
    }
    /* *************************************************************************************
                            THE == / != OPERATOR
    ************************************************************************************* */
    /**IF RHS MATRIX EQUAL TO THE LHS, THE FUNCTION WILL RETURN TRUE. IF NOT - FALSE.**/
    bool operator== (const Matrix<rows, cols, T>& rhs) const
    {
        //Check if the difference betwen the elements are more then 0.000001.
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                if ((this->matrixData[i][j] - rhs.matrixData[i][j] > EPSILON) || (rhs.matrixData[i][j] - this->matrixData[i][j] > EPSILON))
                    return false;
            }
        }
        return true;
    }
    /**IF RHS MATRIX EQUAL TO THE LHS, THE FUNCTION WILL RETURN FALSE. IF NOT - TRUE.**/
///This function provided with RHS matrix we would like to compare to calling matrix.
//It returns the oposite of what operator == returns . 
    bool operator!= (const Matrix<rows, cols, T>& rhs) const
    {
        return !(*this == rhs);
    }
    /* *************************************************************************************
                            THE -- / ++ OPERATOR
    ************************************************************************************* */
    /**MATRIX -- WITH - OPERATOR**/
///
    Matrix<rows, cols, T> operator-- (int)
    {
        Matrix<rows, cols, T>* temp(*this);
        *this = (*this - T(1));
        return temp;
    }
    /**--MATRIX WITH - OPERATOR**/
    Matrix<rows, cols, T>& operator-- ()
    {
        *this = (*this - T(1));
        return *this;
    }

    /**++MATRIX WITH + OPERATOR**/
    Matrix<rows, cols, T>& operator++ ()
    {
        *this = (*this + T(1));
        return *this;
    }
    /**MATRIX++ WITH + OPERATOR**/
    Matrix<rows, cols, T> operator++(int)
    {
        Matrix<rows, cols, T> temp(*this);
        *this = *this + T(1);
        return temp;
    }
    /* *************************************************************************************
                            THE () OPERATOR
    ************************************************************************************* */
    /**GET SPESIFIC ELEMENT OF MATRIX**/
    T& operator() (int n_rows, int n_cols)
    {
        if (n_rows >= 0 && n_rows < rows && n_cols >= 0 && n_cols < cols)
            return matrixData[n_rows][n_cols];
        else
        {
            std::cout << "Wrong Input!" << std::endl;
            return matrixData[0][0];
        }
    }
    const T& operator() (int n_rows, int n_cols) const
    {
        if (n_rows >= 0 && n_rows < rows && n_cols >= 0 && n_cols < cols)
            return matrixData[n_rows][n_cols];
        else
        {
            std::cout << "Wrong Input!" << std::endl;
            return matrixData[0][0];
        }
    }
    /* *************************************************************************************
                           THE -MAT OPERATOR (UNARI)
   ************************************************************************************* */
    Matrix<rows, cols, T> operator-()
    {
        return (*this * T(-1));
    }

};



/**SCALAR + MATRIX (ELEMENT BY ELEMENT)**/
/// This function is a friend of the Matrix class.
/// It's provided with LHS scalar and RHS matrix we would like to add to scalar.
/// We create new matrix and going over its cells in a nested for loop.
/// Changing each element in index (i,j) to the (i,j) value of RHS metrix + the scalar value.
/// This function returns: referance to the new matrix that contains the wanted sum.
/// 

template <int rows, int cols, typename T = int>
Matrix<rows, cols, T> operator+ (const T& lhs, const Matrix<rows, cols, T>& rhs)
{
    return rhs + lhs;
}


/**SCALAR * MATRIX (ELEMENT BY ELEMENT)**/
/// This function is a friend of the Matrix class.
/// It's provided with LHS scalar and RHS matrix we would like to multiply to scalar.
/// We create new matrix and going over its cells in a nested for loop.
/// Changing each element in index (i,j) to the (i,j) value of RHS metrix * the scalar value.
/// This function returns: referance to the new matrix that contains the wanted multiplication sum.

template <int rows, int cols, typename T = int>
Matrix<rows, cols, T> operator* (const T& lhs, const Matrix<rows, cols, T>& rhs)
{
    return rhs * lhs;
}
/**SCALAR - MATRIX (ELEMENT BY ELEMENT)**/
/// This is a friend function provided with RHS Matrix we would like to add to the LHS scalar.
/// Here, we are using Scalar + Matrix function ,while using its syntax.
/// We return referance to the new matrix with the right values that was created in the Scalar + Matrix function.
template <int rows, int cols, typename T = int>
Matrix<rows, cols, T> operator - (const T& lhs, const Matrix<rows, cols, T>& rhs)
{
    return lhs + (-rhs);
}

/* *************************************************************************************
                        THE << OPERATOR
************************************************************************************* */
/** PRINT FUNCTION **/
// This function provided with the text output and matrix.
// Going over a nested for loop and adding each element to the output followed by space.
// After each row we adding a linebreake.
// This function returns: the output.
template <int rows, int cols, typename T = int>
 std::ostream& operator<< (std::ostream& output, const Matrix<rows, cols, T>& rhs)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            output << rhs(i,j) << " ";
        }
        output << std::endl;
    }
    return output;
}
#endif
