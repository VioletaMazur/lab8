#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Функція для вводу матриці з консолі
void inputMatrixFromConsole(int** matrix, int rows, int cols) {
    cout << "Enter the elements of the matrix:" << endl;
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols]; // Виділення пам'яті для кожного рядка
        for (int j = 0; j < cols; ++j) {
            cout << "Enter element at position [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
}

// Функція для виводу матриці
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(4) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функція для знаходження кількості від'ємних елементів в матриці
int countNegativeElements(int** matrix, int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] < 0) {
                count++;
            }
        }
    }
    return count;
}

// Функція для транспонування матриці
void transposeMatrix(int** matrix, int** transposed, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
}

// Функція для сортування стовпця за спаданням
void sortColumnDescending(int** matrix, int rows, int col) {
    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < rows - i - 1; ++j) {
            if (matrix[j][col] < matrix[j + 1][col]) {
                swap(matrix[j][col], matrix[j + 1][col]);
            }
        }
    }
}

int main() {
    int rows, cols;

    do {
        cout << "Enter the number of rows (should be 6 or more): ";
        cin >> rows;
        if (rows < 6) {
            cout << "Number of rows should be 6 or more. Please try again." << endl;
        }
    } while (rows < 6);

    do {
        cout << "Enter the number of columns (should be 6 or more): ";
        cin >> cols;
        if (cols < 6) {
            cout << "Number of columns should be 6 or more. Please try again." << endl;
        }
    } while (cols < 6);

    // Виділення пам'яті для матриць
    int** matrixA = new int* [rows];
    int** matrixB = new int* [rows];

    // Вибір методу вводу даних
    char choice;
    cout << "Do you want to enter data from console? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        inputMatrixFromConsole(matrixA, rows, cols);
        inputMatrixFromConsole(matrixB, rows, cols);
    }
    else {
        // Введення даних з файлу
        string filename;
        cout << "Enter the name of the file: ";
        cin >> filename;

        ifstream file(filename);
        if (!file) {
            cerr << "Error: Unable to open file." << endl;
            return 1;
        }

        // Перевірка кількості елементів у файлі
        int expectedElements = (rows * cols) * 2;
        int actualElements = 0;

        // Введення даних для матриці A
        for (int i = 0; i < rows; ++i) {
            matrixA[i] = new int[cols]; // Виділення пам'яті для кожного рядка
            for (int j = 0; j < cols && !file.eof(); ++j) {
                file >> matrixA[i][j];
                actualElements++;
            }
        }

        // Введення даних для матриці B
        for (int i = 0; i < rows; ++i) {
            matrixB[i] = new int[cols]; // Виділення пам'яті для кожного рядка
            for (int j = 0; j < cols && !file.eof(); ++j) {
                file >> matrixB[i][j];
                actualElements++;
            }
        }
        file.close();
        if (actualElements < expectedElements) {
            cerr << "Error: Number of elements in the file is less than expected." << endl;
            return 1;
        }
    }

    // вивід матриць
    cout << "Matrix A: " << endl;
    printMatrix(matrixA, rows, cols);
    cout << "Matrix B: " << endl;
    printMatrix(matrixB, rows, cols);

    // знаходження кількості від'ємних елементів в обох матрицях
    int negativeCountA = countNegativeElements(matrixA, rows, cols);
    int negativeCountB = countNegativeElements(matrixB, rows, cols);
    cout << "Number of negative elements in matrix A: " << negativeCountA << endl;
    cout << "Number of negative elements in matrix B: " << negativeCountB << endl;

    // визначення матриці C як результат транспонування матриці A або B
    int** transposed = new int* [cols];
    for (int i = 0; i < cols; ++i) {
        transposed[i] = new int[rows];
    }
    if (negativeCountA > negativeCountB) {
        transposeMatrix(matrixA, transposed, rows, cols);
    }
    else {
        transposeMatrix(matrixB, transposed, rows, cols);
    }
    cout << "Transposed matrix C:" << endl;
    printMatrix(transposed, cols, rows);

    // сортування за спаданням значень елементів заданого стовпця
    int columnToSort;
    cout << "Enter the column number to sort in descending order (0 to " << cols - 1 << "): ";
    cin >> columnToSort;
    if (columnToSort >= 0 && columnToSort < cols) {
        sortColumnDescending(transposed, rows, columnToSort);
        cout << "Sorted column " << columnToSort << " in descending order:" << endl;
        printMatrix(transposed, rows, cols);
    }
    else {
        cerr << "Error: Invalid column number." << endl;
    }

    // Звільнення пам'яті
    for (int i = 0; i < rows; ++i) {
        delete[] matrixA[i];
        delete[] matrixB[i];
    }
    delete[] matrixA;
    delete[] matrixB;

    for (int i = 0; i < cols; ++i) {
        delete[] transposed[i];
    }
    delete[] transposed;

    return 0;
}
