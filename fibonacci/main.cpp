#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>

using namespace std;
class Matrix {
public:
    long long int n, m;
    std::vector<std::vector<int>> arr;

    Matrix(int rows, int cols) : n(rows), m(cols), arr(rows, std::vector<int>(cols, 0)) {}
    Matrix(int rows, int cols, int data) : n(rows), m(cols), arr(rows, std::vector<int>(cols, data)) {}

    ~Matrix() {}

    friend std::istream& operator>>(std::istream& input, Matrix& matrix) {
        for (int i = 0; i < matrix.n; i++) {
            for (int j = 0; j < matrix.m; j++) {
                input >> matrix.arr[i][j];
            }
        }
        return input;
    }

    friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix) {
        for (int i = 0; i < matrix.n; i++) {
            for (int j = 0; j < matrix.m; j++) {
                output << matrix.arr[i][j] << ' ';
            }
            output << std::endl;
        }
        return output;
    }

    int* operator[](int index) {
        if (index >= 0 && index < n) {
            return arr[index].data();
        } else {
            throw std::out_of_range("Index is out of bounds");
        }
    }

    Matrix operator+(const Matrix& other) const {
        if (n != other.n || m != other.m) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition");
        }
        Matrix result(n, m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                result.arr[i][j] = arr[i][j] + other.arr[i][j];
            }
        }

        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (n != other.n || m != other.m) {
            throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
        }
        Matrix result(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                result.arr[i][j] = arr[i][j] - other.arr[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (m != other.n) {
            throw std::invalid_argument("Invalid matrix multiplication. Number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        int resultRows = n;
        int resultCols = other.m;
        Matrix result(resultRows, resultCols);

        for (int i = 0; i < resultRows; i++) {
            for (int j = 0; j < resultCols; j++) {
                result.arr[i][j] = 0;
                for (int k = 0; k < m; k++) {
                    result.arr[i][j] += arr[i][k] * other.arr[k][j];
                }
            }
        }

        return result;
    }

    bool operator==(const Matrix& other) const {
        if (n != other.n || m != other.m) {
            throw std::invalid_argument("Matrices must have the same dimensions for equality comparison");
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (arr[i][j] != other.arr[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    double operator()() const {
        if (n != m) {
            throw std::invalid_argument("Matrix must be square for determinant calculation");
        }
        if (n > 2) {
            int sub_det = 0;
            for (int i = 0; i < n; i++) {
                Matrix minor = this->minor(0, i);
                int minor_det = minor();
                sub_det += pow(-1, i) * arr[0][i] * minor_det;
            }
            return sub_det;
        }
        return arr[0][0] * arr[1][1] - arr[1][0] * arr[0][1];
    }

    Matrix minor(int x, int y) const {
        if (n != m) {
            throw std::invalid_argument("Matrix must be square for minor calculation");
        }
        Matrix minor_matrix(n - 1, m - 1, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i != x || j != y) {
                    minor_matrix[i - (i > x)][j - (j > y)] = arr[i][j];
                }
            }
        }
        return minor_matrix;
    }

    Matrix power(int exponent) const {
        if (n != m) {
            throw std::invalid_argument("Matrix must be square for matrix exponentiation");
        }

        if (exponent == 0) {
            // Return identity matrix for any matrix raised to the power of 0
            Matrix identity(n, n);
            for (int i = 0; i < n; i++) {
                identity.arr[i][i] = 1;
            }
            return identity;
        }

        if (exponent % 2 == 0) {
            Matrix half_power = power(exponent / 2);
            return half_power * half_power;
        } else {
            Matrix half_power = power((exponent - 1) / 2);
            return *this * (half_power * half_power);
        }
    }

    Matrix transpose() const {
        Matrix result(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result.arr[i][j] = arr[j][i];
            }
        }
        return result;
    }

    Matrix multiply(const Matrix& A, const Matrix& B) const {
        int resultRows = A.n;
        int resultCols = B.m;
        Matrix result(resultRows, resultCols);

        for (int i = 0; i < resultRows; i++) {
            for (int j = 0; j < resultCols; j++) {
                result.arr[i][j] = 0;
                for (int k = 0; k < A.m; k++) {
                    result.arr[i][j] += A.arr[i][k] * B.arr[k][j];
                }
            }
        }

        return result;
    }
    Matrix Fib(int n){
        Matrix base (2,2,1);
        base[1][1] = 0;
        // cout<<base;
        Matrix base_in_power = base.power(n-2);
        // cout<< "this"<<*this;
        return base_in_power * (*this);
    }
};

int main() {
    try {
        Matrix f1f0(2,1);
        f1f0[0][0] = 1;
        f1f0[1][0] = 0;
        cout<<f1f0.Fib(40);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
