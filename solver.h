#ifndef SOLVER_H
#define SOLVER_H

#include <sudokutablemodel.h>
#include <QElapsedTimer>
#include <list>
#include <iterator>
#include <vector>
//#include <boost/container/flat_map.hpp>
#define BACKTRAKING 0
#define SORT_BACKTRAKING 1

// Решение
//1. Матрица судоку копируется из объекта модели.
//2. Строится график с ожидаемыми элементами (с QModelIndex для определения местоположения), у которых больше всего чисел рядом
//3. Рекурсивное заполнение с проверкой на безопасность.
struct CellAddress
{
    int row; // Строка
    int col; // Столбец
};

using weightedCells = std::vector<std::pair<int, CellAddress>>;

class Solver
{
private:
    int** matrix;
    bool** definedValues;
    const int cnt_section;

    //Проверка безопасности матрицы после вставки элемента
    bool isSafe(const int col, const int row, int num);
    bool colIsSafe(const int col, const int row, int num);
    bool rowIsSafe(const int col, const int row, int num);
    bool squareIsSafe(const int col, const int row, int num);

    bool isValid(const int col, const int row);
    bool solve_backtraking();
    //Ссылка на определенный узел?
    bool solve_sort_backtraking();
    bool backtraking_on_map(const weightedCells* way);
    int getNumSquare(int i, int j);


public:
    Solver(int cnt) : cnt_section{cnt}
    {
        //Заполнение матрицы значений
        matrix = new int*[cnt_section];

        for(int i = 0; i < cnt_section; i++)
            matrix[i] = new int[cnt_section];


    };

    ~Solver();

    bool setMatrix(const sudokuTableModel* model);
    //Возвращает исключение, если не может решить
    bool solve(qint64& time, int algorithm = 0);
    int getNumber(const int col, const int row);
};


#endif // SOLVER_H
