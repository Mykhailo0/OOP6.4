#include <iostream>
#include <stdexcept>
#include <initializer_list>


using namespace std;

template <class T>
class Matrix {
private:
    T** data;
    int rows;
    int cols;

public:
    Matrix() : data(nullptr), rows(0), cols(0) {}

    Matrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i)
            data[i] = new T[cols]{};
    }

    Matrix(std::initializer_list<std::initializer_list<T>> values) {
        rows = values.size();
        cols = values.begin()->size();

        data = new T * [rows];
        auto rowIter = values.begin();
        for (int i = 0; i < rows; ++i, ++rowIter) {
            data[i] = new T[cols];
            auto colIter = rowIter->begin();
            for (int j = 0; j < cols; ++j, ++colIter)
                data[i][j] = *colIter;
        }
    }

    ~Matrix() {
        if (data != nullptr) {
            for (int i = 0; i < rows; ++i)
                delete[] data[i];
            delete[] data;
        }
    }

    Matrix& operator=(std::initializer_list<std::initializer_list<T>> values) {
        if (data != nullptr) {
            for (int i = 0; i < rows; ++i)
                delete[] data[i];
            delete[] data;
        }

        rows = values.size();
        cols = values.begin()->size();

        data = new T * [rows];
        auto rowIter = values.begin();
        for (int i = 0; i < rows; ++i, ++rowIter) {
            data[i] = new T[cols];
            auto colIter = rowIter->begin();
            for (int j = 0; j < cols; ++j, ++colIter)
                data[i][j] = *colIter;
        }

        return *this;
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Matrices dimensions mismatch");

        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Matrices dimensions mismatch");

        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j)
                os << matrix.data[i][j] << ' ';
            os << '\n';
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j)
                is >> matrix.data[i][j];
        }
        return is;
    }

    bool operator==(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            return false;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] != other.data[i][j])
                    return false;
            }
        }

        return true;
    }
};
int main() {
    try {
        Matrix<int> A{ {1, 2, 3}, {4, 5, 6} };
        Matrix<int> B{ {7, 8, 9}, {10, 11, 12} };

        cout << "Matrix A:\n" << A << '\n';
        cout << "Matrix B:\n" << B << '\n';

        Matrix<int> C = A + B;
        cout << "Result of matrix addition A + B:\n" << C << '\n';

        Matrix<int> D = A - B;
        cout << "Result of matrix subtraction A - B:\n" << D << '\n';
    }
    catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << '\n';
    }

    return 0;
}