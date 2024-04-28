#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const int MAX_ROWS = 6;
const int MAX_COLS = 6;

// Функція для вводу матриці з консолі
void inputMatrixFromConsole(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    cout << "Введіть елементи матриці:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Введіть елемент у позицію [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
}

// Функція для виводу матриці
void printMatrix(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    cout << "Матриця :" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(10) << matrix[i][j];
        }
        cout << endl;
    }
}

// Функція для знаходження кількості від'ємних елементів в матриці
int countNegativeElements(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
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
void transposeMatrix(int matrix[MAX_ROWS][MAX_COLS], int transposed[MAX_ROWS][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
}

// Функція для сортування стовпця за спаданням
void sortColumnDescending(int matrix[MAX_ROWS][MAX_COLS], int rows, int col) {
    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < rows - i - 1; ++j) {
            if (matrix[j][col] < matrix[j + 1][col]) {
                swap(matrix[j][col], matrix[j + 1][col]);
            }
        }
    }
}

int main() {


    int matrixA[MAX_ROWS][MAX_COLS];
    int matrixB[MAX_ROWS][MAX_COLS];
    int rows, cols;

    cout << "Введіть кількість рядків (min 6): ";
    cin >> rows;
    cout << "Введіть кількість стовпців (min 6): ";
    cin >> cols;

    if (rows < MAX_ROWS || cols < MAX_COLS) {
        cerr << "Помилка : недостатня кількість рядків або стовпців." << endl;
        return 1;
    }

    // Вибір методу вводу даних
    char choice;
    cout << "Ви хочете ввести дані в консолі ? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        inputMatrixFromConsole(matrixA, rows, cols);
        inputMatrixFromConsole(matrixB, rows, cols);
    }
    else {
        // Введення даних з файлу
        string filename;
        cout << "Введіть назву файлу : ";
        cin >> filename;

        ifstream file(filename);
        if (!file) {
            cerr << "Помилка : неможливо відкрити файл." << endl;
            return 1;
        }

        // Введення даних для матриці A
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file >> matrixA[i][j];
            }
        }

        // Введення даних для матриці B
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file >> matrixB[i][j];
            }
        }
        file.close();
    }

    // вивід матриць
    cout << "Matrix A: " << endl;
    printMatrix(matrixA, cols, rows);
    cout << "Matrix B: " << endl;
    printMatrix(matrixB, cols, rows);

    // знаходження кількості від'ємних елементів в обох матрицях
    int negativeCountA = countNegativeElements(matrixA, rows, cols);
    int negativeCountB = countNegativeElements(matrixB, rows, cols);
    cout << "Кількість негативних елементів у матриці A : " << negativeCountA << endl;
    cout << "Кількість негативних елементів у матриці B: " << negativeCountB << endl;

    // визначення матриці C як результат транспонування матриці A або B
    int transposed[MAX_ROWS][MAX_COLS];
    if (negativeCountA > negativeCountB) {
        transposeMatrix(matrixA, transposed, rows, cols);
    }
    else {
        transposeMatrix(matrixB, transposed, rows, cols);
    }
    cout << "Транспонована матриця C:" << endl;
    printMatrix(transposed, cols, rows);

    // сортування за спаданням значень елементів заданого стовпця
    int columnToSort;
    cout << "Введіть номер стовпця для сортування в порядку спадання (0 to " << cols - 1 << "): ";
    cin >> columnToSort;
    if (columnToSort >= 0 && columnToSort < cols) {
        sortColumnDescending(transposed, rows, columnToSort);
        cout << "Відсортований стовпець " << columnToSort << " у порядку спадання:" << endl;
        printMatrix(transposed, rows, cols);
    }
    else {
        cerr << "Помилка : недійсний номер стовпця." << endl;
    }

    return 0;
}