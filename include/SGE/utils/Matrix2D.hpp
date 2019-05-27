#ifndef FACTORY_EXPERIMENTS_MATRIX2D_HPP
#define FACTORY_EXPERIMENTS_MATRIX2D_HPP

#include <string>
#include <vector>
#include <iostream>

template <class T>
class Matrix2D {
public:
    const unsigned int rows;
    const unsigned int columns;

    Matrix2D(unsigned int row_n, unsigned int col_n);
    Matrix2D(const Matrix2D<T>& that);
    virtual ~Matrix2D();

    void make_identity();
    /*!
     * \brief Prints to console a string representation of the matrix
     */
    void print_matrix(const std::string& header = "");
    /*!
     * \brief Multiplies to matrices into this matrix
     * \param first The first operand of the multiplication
     * \param second The second operand of the multiplication
     */
    void multiply(Matrix2D<T>& first,Matrix2D<T>& second);

    T* operator[](unsigned int index);
    Matrix2D<T> operator*(const Matrix2D<T>& that);
    Matrix2D<T>& operator=(const Matrix2D<T>& that);

private:
    T** m_matrix;
};



//region Constructors and destructors

template<class T>
Matrix2D<T>::Matrix2D(unsigned int row_n, unsigned int col_n)
        : rows(row_n)
        , columns(col_n) {
    m_matrix = new T*[row_n];
    for (int i = 0; i < row_n; ++i) {
        m_matrix[i] = new T[col_n];
        for (int j = 0; j < col_n; ++j) {
            m_matrix[i][j] = 0;
        }
    }
}

template<class T>
Matrix2D<T>::Matrix2D(const Matrix2D<T> &that)
        : rows(that.rows)
        , columns(that.columns) {
    std::cout << "copy constructor called" << std::endl;
    m_matrix = new T*[rows];
    for (int row = 0; row < rows; ++row) {
        m_matrix[row] = new T[columns];
        for (int column = 0; column < columns; ++column) {
            m_matrix[row][column] = that.m_matrix[row][column];
        }
    }
}

template<class T>
Matrix2D<T>::~Matrix2D() {
    //std::cout << "Destructor called" << std::endl;
    for (int i = 0; i < rows; ++i) {
        delete[](m_matrix[i]);
    }
    delete[](m_matrix);
}
//endregion


template<class T>
void Matrix2D<T>::print_matrix(const std::string& header ) {
   std::string out_lines[rows];

    for (int column = 0; column < columns; ++column) {
        // Append to_stringed rows keeping track of the longest line
        unsigned int max_index = 0;                         // Keeps track of the longest out_line index
        for (int row = 0; row < rows; ++row) {
            out_lines[row] += "| " + std::to_string(m_matrix[row][column]) + " ";
            if (out_lines[row].length() > out_lines[max_index].length()) max_index=row;
        }
        // Filling the lines of spaces to equalize lenght
        for (int row = 0; row < rows; ++row) {
            out_lines[row] += std::string(out_lines[max_index].length()-out_lines[row].length(), ' ');
        }
    }

    int fill_space = out_lines[0].length() - header.length()-2;
    std::cout << "|" + header + "\\";
    if (fill_space>0) std::cout << std::string(fill_space, '_');
    std::cout << std::endl;
    for (int row = 0; row < rows; ++row) {
        std::cout << out_lines[row] + "|\n";
    }

}

template<class T>
T* Matrix2D<T>::operator[](unsigned int index) {
    if (index < rows) return m_matrix[index];
    else {
        std::cout << "Error: invalid row index [" << index << "]";
        exit(1);
    }
}


template<class T>
void Matrix2D<T>::multiply(Matrix2D& first, Matrix2D& second) {
    if (first.columns==second.rows) {
        if (columns == second.columns && rows==first.rows) {

            for (int row = 0; row < rows; ++row) {
                for (int column = 0; column < columns; ++column) {
                    m_matrix[row][column] = 0;
                    for (int i = 0; i < first.columns; ++i) {
                        m_matrix[row][column] += (first[row][i])*(second[i][column]);
                    }
                }
            }
        } else {
            std::cout << "Error: during matrix moltiplication the given output matrix has the wrong amount of rows and/or columns";
        }
    } else {
        std::cout << "Error: tried to multiply two matrices with a different number of row and column rispectively";
    }
}

template<class T>
void Matrix2D<T>::make_identity() {
    if (columns==rows) {
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                if (row==column) m_matrix[row][column] = 1;
                else m_matrix[row][column] = 0;
            }
        }
    } else {
        std::cout << "Error: tried to make identy a non-square matrix, which makes no sense" << std::endl;
        exit(1);
    }
}

template<class T>
Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D<T> &that) {
    Matrix2D<T> res_matrix(this->rows, that.columns);

    if (this->columns==that.rows) {
        for (int row = 0; row < res_matrix.rows; ++row) {
            for (int column = 0; column < res_matrix.columns; ++column) {
                for (int i = 0; i < this->columns; ++i) {
                    res_matrix[row][column] += (this->m_matrix[row][i])*(that.m_matrix[i][column]);
                }
            }
        }
    } else {
        std::cout << "Error: tried to multiply two matrices with a different number of row and column rispectively";
    }
    return  res_matrix;
}

template<class T>
Matrix2D<T> &Matrix2D<T>::operator=(const Matrix2D<T> &that) {
    if (this->columns==that.columns && this->rows == that.rows) {
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                m_matrix[row][column] = that.m_matrix[row][column];
            }
        }
        return *this;
    } else {
        std::cout << "Error: Tried to use = operator on two matrices with different dimensions" << std::endl;
        exit(1);
    }
}




#endif //FACTORY_EXPERIMENTS_MATRIX2D_HPP
