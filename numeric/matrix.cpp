template <typename T>
class Matrix {
public:
  vector<vector<T>> matrix;
  int _rows;
  int _columns;
  
  Matrix() = default;
  
  Matrix(int row_count, int column_count) :
      matrix(row_count),
      _rows(row_count),
      _columns(column_count) {
    matrix.resize(row_count, vector<T>(column_count, T{}));
    for (auto& row : matrix) {
      row.resize(_columns);
    }
  }
  
  Matrix(int row_count, int column_count, const T& value) :
      matrix(row_count),
      _rows(row_count),
      _columns(column_count) {
    for (int i = 0; i < _rows; ++i) {
      matrix[i].resize(_columns, value);
    }
  }
  
  Matrix(vector<vector<T>> x) :
      _rows(x.size()),
      _columns(x[0].size()) {
    matrix = x;
  }
  
  Matrix(const Matrix& other) = default;
  
  Matrix& operator=(const Matrix& other) = default;
  
  // Scalar Multiplication
  Matrix& operator*=(const T& scalar) {
    for (auto& row : matrix) {
      for (auto& cell : row) {
        cell *= scalar;
      }
    }
    return *this;
  }
  
  // Scalar Division
  Matrix& operator/=(const T& scalar) {
    for (auto& row : matrix) {
      for (auto& cell : row) {
        cell /= scalar;
      }
    }
    return *this;
  }
  
  // Modular Operator
  Matrix& operator%=(const T& mod) {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        matrix[i][j] %= mod;
      }
    }
    return *this;
  }
  
  // Matrix Multiplication
  Matrix& operator*=(const Matrix& other) {
    if (_columns != other._rows) {
      throw logic_error("column count of lhs and row count of rhs are not equal\n");
    }
    Matrix temp(_rows, other._columns, 0);
  
    for (int i = 0; i < temp._rows; i++) {
      for (int j = 0; j < temp._columns; j++) {
        for (int k = 0; k < _columns; k++) {
          temp[i][j] += matrix[i][k] * other[k][j];
        }
      }
    }
    swap(matrix, temp.matrix);
    swap(_columns, temp._columns);
    return *this;
  }
  
  // addition Operator
  Matrix& operator+=(const Matrix& other) {
    if (_rows != other._rows || _columns != other._columns) {
      throw logic_error("either or both of row count and column count of lhs and rhs are not equal\n");
    }
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        matrix[i][j] += other[i][j];
      }
    }
    return *this;
  }
  
  // Subtraction Operator
  Matrix& operator-=(const Matrix& other) {
    if (_rows != other._rows || _columns != other._columns) {
      throw logic_error("either or both of row count and column count of lhs and rhs are not equal\n");
    }
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        matrix[i][j] -= other[i][j];
      }
    }
    return *this;
  }
  
  Matrix<T> cofactor(int p, int q, int n) {
    int i = 0, j = 0;
    Matrix<T> temp(n, n);
    for (int row = 0; row < _rows; row++) {
      for (int col = 0; col < _columns; col++) {
        if (row != p && col != q) {
          temp[i][j++] = matrix[row][col];
          if (j == n - 1) {
            j = 0;
            i++;
          }
        }
      }
    }
    return temp;
  }
  
  T determinant() {
    int n = _rows;
    int num1, num2, det = 1, index, total = 1; // Initialize result
    
    T temp[n + 1];
    for (int i = 0; i < n; i++) {
      index = i;
      while (matrix[index][i] == 0 && index < n) {
        index++;
      }
      if (index == n) {
        continue;
        
      }
      if (index != i) {
        for (int j = 0; j < n; j++) {
          swap(matrix[index][j], matrix[i][j]);
        }
        det = det * pow(-1, index - i);
      }
      
      for (int j = 0; j < n; j++) {
        temp[j] = matrix[i][j];
        
      }
      for (int j = i + 1; j < n; j++) {
        num1 = temp[i];
        num2 = matrix[j][i];
        for (int k = 0; k < n; k++) {
          matrix[j][k] = (num1 * matrix[j][k]) - (num2 * temp[k]);
        }
        total = total * num1;
      }
    }
    for (int i = 0; i < n; i++) {
      det = det * matrix[i][i];
      
    }
    return (det / total); //Det(kA)/k=Det(A);
  }
  
  // Number of Rows
  int rows() const { return _rows; }
  
  // Number of Columns
  int columns() const { return _columns; }
  
  vector<T>& operator[](int row) { return matrix[row]; }
  
  const vector<T>& operator[](int row) const { return matrix[row]; }
  static Matrix<T> Identity(int n);
};

template <typename T>
Matrix<T> Matrix<T>::Identity(int n) {
  Matrix<T> res(n, n, 0);
  for (int i = 0; i < n; ++i) {
    res[i][i] = 1;
  }
  return res;
}

//Matrix Transpose
template <typename T>
Matrix<T> transpose(const Matrix<T>& other) {
  Matrix<T> res(other.columns(), other.rows());
  for (int row = 0; row < other.rows(); ++row) {
    for (int col = 0; col < other.columns(); ++col) {
      res[col][row] = other[row][col];
    }
  }
  return res;
}

//Equals Operator
template <typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
  if (lhs.rows() != rhs.rows() || lhs.columns() != rhs.columns()) {
    return false;
  }
  for (auto i = 0; i < lhs.rows(); i++) {
    for (auto j = 0; j < lhs.columns(); j++) {
      if (lhs[i][j] != rhs[i][j]) {
        return false;
      }
    }
  }
  return true;
}

//Not-Equals Operator
template <typename T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs) { return !(lhs == rhs); }

//Add matrices
template <typename T>
Matrix<T> operator+(Matrix<T>& lhs, const Matrix<T>& rhs) { return lhs += rhs; }

//Subtract matrices
template <typename T>
Matrix<T> operator-(Matrix<T>& lhs, const Matrix<T>& rhs) { return lhs -= rhs; }

// Multiply Matrices
template <typename T>
Matrix<T> operator*(Matrix<T>& lhs, const Matrix<T>& rhs) { return lhs *= rhs; }

//Scalar multiplication
template <typename T, typename U>
Matrix<T> operator*(Matrix<T>& lhs, const U& rhs) { return lhs *= rhs; }

//Scalar Division
template <typename T, typename U>
Matrix<T> operator/(Matrix<T>& lhs, const U& rhs) { return lhs /= rhs; }

//Scalar modulo
template <typename T, typename U>
Matrix<T> operator%(Matrix<T>& lhs, const U& mod) { return lhs %= mod; }

template <typename T, typename U>
Matrix<T> operator*(const U& scalar, const Matrix<T>& lhs) { return lhs *= scalar; }

template <typename T>
Matrix<T> operator*(const T& lhs, const Matrix<T>& rhs) { return rhs *= lhs; }

// Power of a Matrix
template <typename T, typename U>
Matrix<T> power(Matrix<T> base, U exp) {
  Matrix<T> res = Matrix<T>::Identity(base.rows());
  while (exp > 0) {
    if (exp & 1) {
      res *= base;
    }
    exp >>= 1;
    base *= base;
  }
  return res;
}

// Trace of Matrix
template <typename T>
T trace(Matrix<T>& matrix) {
  if (matrix.rows() != matrix.columns()) {
    throw logic_error("Not a square matrix\n");
  }
  T res = 0;
  for (int i = 0; i < matrix.rows(); ++i) {
    res += matrix[i][i];
  }
  return res;
}

template <typename T>
istream& operator>>(istream& is, Matrix<T>& matrix) {
  for (int i = 0; i < matrix.rows(); i++) {
    for (int j = 0; j < matrix.columns(); j++) {
      is >> matrix[i][j];
    }
  }
  return is;
}

template <typename T>
ostream& operator<<(ostream& os, const Matrix<T>& matrix) {
  for (int i = 0; i < matrix.rows(); i++) {
    for (int j = 0; j < matrix.columns(); j++) {
      os << matrix[i][j] << " \n"[j == matrix.columns() - 1];
    }
  }
  return os;
}

template <typename T>
string to_string(const Matrix<T> &m) {
  return to_string(m.matrix);
}
