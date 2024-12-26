#include <iostream>
#include <cmath>
using namespace std;


void printMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

bool inverseMatrix(double** A, double** inv, int size) {
    double** temp = new double* [size];
    for (int i = 0; i < size; ++i) {
        temp[i] = new double[2 * size];
    }

    // Инициализация расширенной матрицы
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            temp[i][j] = A[i][j];
        }
        for (int j = size; j < 2 * size; ++j) {
            temp[i][j] = (i == j - size) ? 1.0 : 0.0;
        }
    }

    // Прямой ход метода Гаусса
    for (int i = 0; i < size; ++i) {
        // Найти максимальный элемент в текущем столбце
        int maxRow = i;
        for (int k = i + 1; k < size; ++k)
        {
            if (fabs(temp[k][i] > fabs(temp[maxRow][i])) )
            {
                maxRow = k;
            }
        }

        // Проверка на сингулярность
        if (temp[maxRow][i] == 0.0) {
            cout << "Матрица сингулярна!" << endl;
            for (int i = 0; i < size; ++i) {
                delete[] temp[i];
            }
            delete[] temp;
            return false;
        }

        // Поменять строки местами, если максимальный элемент не на диагонали
        if (maxRow != i) {
            for (int j = 0; j < 2 * size; ++j) {
                swap(temp[i][j], temp[maxRow][j]);
            }
        }

        // Нормализация текущей строки
        double pivot = temp[i][i];
        for (int j = 0; j < 2 * size; ++j) {
            temp[i][j] /= pivot;
        }

        // Обнуляем элементы ниже текущей строки
        for (int u = i + 1; u < size; ++u) {
            double f = temp[u][i];
            for (int j = 0; j < 2 * size; ++j) {
                temp[u][j] -= temp[i][j] * f;
            }
        }
    }

    // Обратный ход метода Гаусса
    for (int i = size - 1; i > 0; --i) {
        for (int k = i - 1; k >= 0; --k) {
            double f = temp[k][i];
            for (int j = 0; j < 2 * size; ++j) {
                temp[k][j] -= temp[i][j] * f;
            }
        }
    }

    // Заполнение обратной матрицы
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            inv[i][j] = temp[i][j + size];
        }
    }

    // Освобождение памяти
    for (int i = 0; i < size; ++i) {
        delete[] temp[i];
    }
    delete[] temp;

    return true;
}

int main() {
    setlocale(LC_ALL, "rus");
    int size;
    cout << "Введите размерность матрицы: ";
    cin >> size;

    double** A = new double* [size];
    double** inv = new double* [size];
    for (int i = 0; i < size; ++i) {
        A[i] = new double[size];
        inv[i] = new double[size];
    }

    cout << "Вводите элементы матрицы:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cin >> A[i][j];
        }
    }

    if (inverseMatrix(A, inv, size)) {
        cout << "Обратная матрица:\n";
        printMatrix(inv, size, size);
    }
    else {
        cout << "Не удалось найти обратную матрицу.\n";
    }

    // Освобождение памяти
    for (int i = 0; i < size; ++i) {
        delete[] A[i];
        delete[] inv[i];
    }
    delete[] A;
    delete[] inv;

    return 0;
}