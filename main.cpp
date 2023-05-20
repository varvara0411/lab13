#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <stdexcept>

template <class T>
class matrix {
private:
    T** mm; 
    int r; 
    int c; 
public:
  matrix() { //конструктор по умолчанию
    r = 0;
    c = 0;
    mm = nullptr; 
  }
  
  matrix(int r, int c, T val) //конструктор, создающий матрицу, элементы которой равны заданному значению
  {
    this->r = r;
    this->c = c;
    mm = new T*[r];
    for (int i = 0; i < r; i++)
      mm[i] = new T[c];
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            mm[i][j] = val;
  }

  matrix(int r, int c) //конструктор для заполнения матрицы с консоли
  {
    this->r = r;
    this->c = c;
    mm = new T*[r]; 
    for (int i = 0; i < r; i++)
      mm[i] = new T[c];
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            std::cin >> mm[i][j];
  }

  matrix(const std::string file) { //конструктор считывания матрицы из заданного файла
      std::ifstream f;
      f.open(file);
      if (f.is_open()) {
          f >> r;
          f >> c;
          mm = new T*[r];
          for (int i = 0; i < r; i++)
            mm[i] = new T[c];
          for (int i = 0; i < r; i++) {
              for (int j = 0; j < c; j++) {
                  f >> mm[i][j];
              }
	      }
       }
       else { std::cerr << "File can not be opened" << std::endl; }
	   f.close();
  }

  matrix(const matrix& M1) //конструктор копирования
  {
    r = M1.r;
    c = M1.c;
    mm = (T**) new T*[r];
    for (int i = 0; i < r; i++)
      mm[i] = (T*) new T[c];
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
        mm[i][j] = M1.mm[i][j];
  }

  matrix operator=(const matrix& M2) //перегрузка оператора присваивания
  {
    if (c > 0)
    {
      for (int i = 0; i < r; i++)
        delete[] mm[i];
    }
    if (r > 0)
    {
      delete[] mm;
    }
    r = M2.r;
    c = M2.c;
    mm = (T**) new T*[r]; 
    for (int i = 0; i < r; i++)
      mm[i] = (T*) new T[c];
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
        mm[i][j] = M2.mm[i][j];
    return *this;
  }

  ~matrix() { //деструктор
    if (c > 0)
    {
      for (int i = 0; i < r; i++)
        delete[] mm[i];
    }
    if (r > 0) {
        delete[] mm;
    }
  }
    matrix operator+(const matrix& m1) { //перегрузка оператора сложения матриц
        if ((r != m1.r)||(c != m1.c)) {
            std::cerr << "The operation cannot be performed due to different matrix sizes" << std::endl;
            return *this;
        }
        else {
            matrix b = matrix(r, c, 0);
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    b.mm[i][j] = mm[i][j] + m1.mm[i][j];
                }
            }
            return b;
        }
  }

    matrix operator-(const matrix& m2) { //перегрузка оператора вычитания матриц
        if ((r != m2.r)||(c != m2.c)) {
            std::cerr << "The operation cannot be performed due to different matrix sizes" << std::endl;
            return *this;
        }
        else {
            matrix b = matrix(r, c, 0);
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    b.mm[i][j] = mm[i][j] - m2.mm[i][j];
                }
            }
            return b;
        }
    }
    matrix operator*(T num) { //перегрузка оператора умножения матрицы на скаляр
        matrix b = matrix(r, c, 0);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                b.mm[i][j] = (T) mm[i][j] * num;
            }
        }
        return b;
    }
    matrix operator*(const matrix& a) { //перегрузка оператора умножения матриц друг на друга
        if (c != a.r ) {
            std::cerr << "It is impossible to perform the operation due to the inequality of the number of columns of the first matrix and the number of rows of the second matrix" << std::endl;
            return *this;
        }
        else {
            matrix b = matrix(r, a.c, 0);
            for (int i = 0; i < r; ++ i)
                for (int j = 0; j < a.c; ++ j)
                    for (int k = 0; k < c; ++ k)
                        b.mm[i][j] += mm[i][k] * a.mm[k][j];
            return b;
        }
    }
    
    bool operator==(const matrix& m3) { //перегрузка оператора проверки матриц на равенство
        if ((r != m3.r) || (c != m3.c)) {
            return false;
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (mm[i][j] != m3.mm[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool operator!=(const matrix& m4) { //перегрузка оператора проверки матриц на неравенство
        if ((r != m4.r)||(c != m4.c)) {
            return true;
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (mm[i][j] != m4.mm[i][j]) {
                    return true;
                }
            }
        }
        return false;
    }
    static matrix zero_matr(int r1, int c1) { //статический метод создания нулевой матрицы заданных размеров
        matrix b(r1, c1, 0);
        return b;
    }
    static matrix one_matr(int size) { //статический метод создания единичной матрицы заданного размера
        matrix a(size, size, 0);

        for (int i = 0; i < size; i++)
            a.mm[i][i] = 1;

        return a;
    }
    bool operator==(int val) { //перегрузка оператора проверки матрицы на равенство 0 или 1
        if (val == 0) {
            matrix q = matrix::zero_matr(r, c);
            if (*this == q) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (val == 1) {
            matrix w = matrix::one_matr(r);
            if (*this == w) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            std::cerr << "Matrix can only be compared with 0 or 1" << std::endl;
            return false;
        }
    }
    
    bool operator!=(int val) { //перегрузка оператора проверки матрицы на неравенство 0 или 1
        if (val == 0) {
            matrix q = matrix::zero_matr(r, c);
            if (*this == q) {
                return false;
            }
            else {
                return true;
            }
        }
        else if (val == 1) {
            matrix w = matrix::one_matr(r);
            if (*this == w) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            std::cerr << "Matrix can only be compared with 0 or 1" << std::endl;
            return false;
        }
    }

    void readtofile_full(const std::string name) { //метод для записи в заданный файл размеров матрицы и самой матрицы
	    std::ofstream par;
	    par.open(name);
	    if (par.is_open()) {
	        par << this->r << ' ' << this->c;
	        par << std::endl;
	        for (int i = 0; i < this->r; i++) {
                for (int j = 0; j < this->c; j++) {
                    par << this->mm[i][j] << '\t';
                }
                par << std::endl;
            }
	    }
	    else { std::cout << "No open" << std::endl; }
	    par.close();
    }
    void readtofile_value(const std::string name, int i, int j) { //метод для записи в заданный файл элемента из заданных строки и столбца
	    std::ofstream par;
	    par.open(name);
	    if (par.is_open()) {
	        par << i << ' ' << j;
	        par << std::endl;
	        par << this->mm[i - 1][j - 1];
	    }
	    else { std::cout << "No open" << std::endl; }
	    par.close();
    }
    void readtofile_row(const std::string name, int i) { //метод для записи в заданный файл элементов заданной строки
	    std::ofstream par;
	    par.open(name);
	    if (par.is_open()) {
	        par << i;
	        par << std::endl;
            for (int j = 0; j < this->c; j++) {
                par << this->mm[i - 1][j] << '\t';
            }
	    }
	    else { std::cout << "No open" << std::endl; }
	    par.close();
    }
    void readtofile_col(const std::string name, int j) { //метод для записи в заданный файл элементов заданного столбца
	    std::ofstream par;
	    par.open(name);
	    if (par.is_open()) {
	        par << j;
	        par << std::endl;
            for (int i = 0; i < this->r; i++) {
                par << this->mm[i][j - 1] << std::endl;
            }
	    }
	    else { std::cout << "No open" << std::endl; }
	    par.close();
    }
    void readfromfile_full(const std::string name) { //метод для считывания матрицы из заданного файла
        std::ifstream var;
        var.open(name);
        if (var.is_open()) {
            for (int i = 0; i < this->r; i++) {
                for (int j = 0; j < this->c; j++) {
                    var >> this->mm[i][j];
                }
	        }
        }
        else { std::cerr << "File can not be opened" << std::endl; }
	    var.close();
	}
    void readfromfile_value(const std::string name, int k, int t) { //метод для считывания элемента из заданных строки и столбца матрицы из заданного файла
        std::ifstream var;
        var.open(name);
        T num;
        if (var.is_open()) {
            for (int i = 0; i < this->r; ++i) {
                for (int j = 0; j < this->c; ++j) {
                    var >> num;
                    if ((i == (k - 1)) && (j == (t - 1))) {
                        this->mm[i][j] = num;
                        break;
                    }
                }
	        }
        }
        else { std::cerr << "File can not be opened" << std::endl; }
	    var.close();
	}
    void readfromfile_row(const std::string name, int p) { //метод для считывания элементов заданной строки матрицы из заданного файла
        std::ifstream var;
        var.open(name);
        T num;
        if (var.is_open()) {
            for (int i = 0; i < this->r; ++i) {
                for (int j = 0; j < this->c; ++j) {
                    var >> num;
                    if (i == (p - 1)) {
                        this->mm[i][j] = num;
                    }
                }
	        }
        }
        else { std::cerr << "File can not be opened" << std::endl; }
	    var.close();
	}
    void readfromfile_col(const std::string name, int p) { //метод для считывания элементов заданного столбца матрицы из заданного файла
        std::ifstream var;
        var.open(name);
        T num;
        if (var.is_open()) {
            for (int i = 0; i < this->r; ++i) {
                for (int j = 0; j < this->c; ++j) {
                    var >> num;
                    if (j == (p - 1)) {
                        this->mm[i][j] = num;
                    }
                }
	        }
        }
        else { std::cerr << "File can not be opened" << std::endl; }
	    var.close();
	}

    matrix matrwithout(int row, int col) { //метод, возвращающий матрицу с удалёнными заданными строкой и столбцом
        int r1 = 0;  
        int c1 = 0;  
        matrix h(this->r - 1, this->c - 1, 0); 
        for(int i = 0; i < this->r - 1; i++) { 
            if(i == row) { 
                r1 = 1;  
            } 
            c1 = 0;  
            for(int j = 0; j < this->r - 1; j++) { 
                if(j == col) { 
                    c1 = 1;  
                } 
                h.mm[i][j] = this->mm[i + r1][j + c1]; 
            } 
        } 
        return h; 
    } 
     
    
    T det() { //вычисление определителя матрицы
        if (r != c) {
            std::cerr << "Matrix is not square." << std::endl; 
            return 0;
        }
        else { 
            T d = 0; 
            int degree = 1;  
            if(this->r == 1) { 
                return this->mm[0][0]; 
            } 
            else if (this->r == 2) { 
                return this->mm[0][0] * this->mm[1][1] - this->mm[0][1] * this->mm[1][0]; 
            } 
            else { 
                for(int j = 0; j < this->r; j++) { 
                    matrix q = this->matrwithout(0, j); 
                    d = d + (degree * this->mm[0][j] * q.det()); 
                    degree = -1 * degree; 
                } 
            } 
            return d; 
        } 
    } 

    matrix algebr_addition() { //метод, возвращающий матрицу, состоящую из алгебраических дополнений к каждому элементу матрицы
        if (r != c) {
            std::cerr << "Matrix is not square." << std::endl; 
            return *this;
        }
        else {
            matrix f(r, c, 0);
            matrix a = *this; 
            for (int i = 0; i < this->r; ++i) { 
                for(int j = 0; j < this->r; ++j) { 
                    matrix q = a.matrwithout(i, j);
                    f.mm[i][j] = pow(-1, (i + j)) * q.det(); 
                }  
            } 
            return f; 
        }
    } 
    
    matrix transposition() { //метод, возвращающий транспонированную матрицу
        matrix a = *this;
        *this = matrix(c, r, 0);
        for (int i = 0; i < a.c; i++) 
            for (int j = 0; j < a.r; j++) { 
                mm[i][j] = a.mm[j][i]; 
            }
        return *this; 
    } 
    
    
    matrix operator! () { //перегрузка оператора логического отрицания для вычисления обратной матрицы
        try { 
            if (r != c) {
                throw std::logic_error("Matrix is not square. Inverse matrix does not exist."); 
            }
            else {
                T determ = this->det(); 
                if (determ == 0) { 
                    throw std::logic_error("The determinant is zero. Inverse matrix does not exist."); 
                } 
                else { 
                    T value = (T) 1 / (this->det()); 
                    auto matr = this->algebr_addition(); 
                    matr.transposition();
                    return (matr * value); 
                } 
            }
        } 
        catch(std::exception& q) { 
            std::cerr << "Exception: " << q.what() << std::endl; 
            return *this; 
        } 
        return *this; 
    }

    template<typename T1>
    friend std::ostream& operator<<(std::ostream& out, const matrix<T1>& mtr); //объявление дружественной функции (перегрузки оператора вывода)
};

template<class T>
std::ostream& operator<<(std::ostream& out, const matrix<T>& mtr) //перегрузка оператора вывода
{
    for (int i = 0; i < mtr.r; i++)
    {
        for (int j = 0; j < mtr.c; j++)
            out << mtr.mm[i][j] << '\t';
        out << std::endl;
    }

    return out;
}

int main() {
    auto my_mtrx = matrix<int>::one_matr(5);
    std::cout << my_mtrx;
    if (my_mtrx == 1) {
        std::cout << "they are equal" << std::endl;
    }
    std::cout << "------------" << std::endl;
    matrix<int> my_mtrx1(5, 5, 2);
    auto pos = my_mtrx * 2;
    std::cout << pos;
    std::cout << "------------" << std::endl;
    std::cout << pos + my_mtrx1;
    std::cout << "------------" << std::endl;
    std::cout << pos - my_mtrx1;
    std::cout << "------------" << std::endl;
    my_mtrx.readtofile_full("output.txt");
    my_mtrx.readtofile_value("output1.txt", 2, 2);
    my_mtrx.readtofile_row("output2.txt", 2);
    my_mtrx.readtofile_col("output3.txt", 3);
    matrix<int> mq(2, 2, 0);
    mq.readfromfile_full("input.txt");
    std::cout << mq;
    std::cout << "------------" << std::endl;
    matrix<int> object(2, 2, 0);
    object.readfromfile_value("input.txt", 1, 2);
    std::cout << object;
    std::cout << "------------" << std::endl;
    matrix<int> ob(2, 2, 0);
    ob.readfromfile_row("input.txt", 2);
    std::cout << ob;
    std::cout << "------------" << std::endl;
    matrix<int> r(2, 2, 0);
    r.readfromfile_col("input.txt", 1);
    std::cout << r;
    std::cout << "------------" << std::endl;
    matrix<int> u(2, 3, 5);
    std::cout << u;
    std::cout << "------------" << std::endl;
    matrix<int> t(3, 3);
    std::cout << t;
    std::cout << "------------" << std::endl;
    matrix<int> x("input1.txt");
    std::cout << x;
    std::cout << "------------" << std::endl;
    std::cout << ob * r;
    std::cout << "------------" << std::endl;
    matrix<double> house(3, 3);
    std::cout << !house;
    std::cout << "------------" << std::endl;
    matrix<double> s1(2, 2);
    std::cout << !s1;
    std::cout << "------------" << std::endl;
    matrix<int> q1(2, 3, 1);
    std::cout << !q1;
    std::cout << "------------" << std::endl;
    matrix<int> q2(3, 3, 0);
    std::cout << !q2;
    std::cout << "------------" << std::endl;
    return 0;
}
