#include "solver.h"


bool Solver::isValid(const int col, const int row)
{
    if(col < cnt_section || row < cnt_section)
        return true;
    else
        return false;
}

int Solver::getNumber(const int row, const int col)
{
    if(isValid(col, row))
        return matrix[row][col];
    else
        return -1;
}

int Solver::getNumSquare(int i, int j)
{
    return (i/3)*3+(j/3);
}

bool Solver::setMatrix(const sudokuTableModel* sudokuModel)
{
    bool noError = 1;
    definedValues = new bool*[cnt_section];

    for(int i = 0; i < cnt_section; i++)
        definedValues[i] = new bool[cnt_section];

    for(int i = 0; i < cnt_section; i++)
    {
        for(int j = 0; j < cnt_section; j++)
        {
            QVariant elem = sudokuModel->data(sudokuModel->index(i, j, QModelIndex()), Qt::EditRole);
            if(elem.Int)
                matrix[i][j] = elem.toInt();
            else
                return 0;

            if(matrix[i][j] == 0)
                definedValues[i][j] = false;
            else
                definedValues[i][j] = true;
        }

    }

    return noError;
}


bool Solver::colIsSafe(const int col, const int row, int num)
{
    int numCol = col;
    for(int i = 0; i < cnt_section; i++)
    {
        if(i == row)
            continue;
        if(matrix[i][numCol] == num)
            return false;
    }
    return true;
}

bool Solver::rowIsSafe(const int col, const int row, int num)
{
    int numRow = row;
    for(int i = 0; i < cnt_section; i++)
    {
        if(i == col)
            continue;
        if(matrix[numRow][i] == num)
            return false;
    }
    return true;
}

bool Solver::squareIsSafe(const int col, const int row, int num)
{
    int startCol, endCol;
    int startRow, endRow;

    //Определение нужного квадрата
    for(endCol = 2; endCol < cnt_section; endCol+=3)
        if(col <= endCol) break;

    for(endRow = 2; endRow < cnt_section; endRow+=3)
        if(row <= endRow) break;


    startRow = endRow - 2;
    startCol = endCol - 2;


    for(int i = startRow; i <= endRow; i++)
    {
        for(int j = startCol; j <= endCol; j++)
        {
            if(i == row && j == col)
                continue;
            if(matrix[i][j] == num)
                return false;
        }
    }

    return true;
}

bool Solver::isSafe(const int row, const int col, int num)
{
    if(colIsSafe(col, row, num) && rowIsSafe(col, row, num) && squareIsSafe(col, row, num))
        return true;
    else
        return false;
}

bool Solver::solve_backtraking()
{
    bool flagNull = false;
    int rowNull, colNull;
    for(int i = 0; i < cnt_section; i++)
    {
        for(int j = 0; j < cnt_section; j++)
        {
            if(matrix[i][j] == 0)
            {
                rowNull = i;
                colNull = j;
                flagNull = true;
                break;
            }

        }

        if(flagNull)
            break;
    }
    //Если значения флага не поменялось, значит больше нет пустых клеток
    if(!flagNull)
        return true;

    for(int i = 1; i < 10; i++)
    {
        if(isSafe(rowNull, colNull, i))
        {
            matrix[rowNull][colNull] = i;
            if(solve_backtraking())
                return true;
            matrix[rowNull][colNull] = 0;
        }
    }
    return false;
}

bool Solver::solve_sort_backtraking()
{
    //Считается вес для каждой пустой клетке
    //Записывается сортированный порядок ячеек
    //Вызывается функция по проходу и заполнению

    int rowDefineNum[9] = {9};
    int colDefineNum[9] = {9};
    int squareDefineNum[9] = {9};

    for (int i = 0; i < cnt_section; i++)
    {
        for (int j = 0; j < cnt_section; j++)
        {
            if(!definedValues[i][j])
            {
                colDefineNum[j]--;
                rowDefineNum[i]--;
                squareDefineNum[getNumSquare(i, j)]--;
            }
        }
    }

    weightedCells way;

    for(int i = 0; i < cnt_section; i++)
    {
        for(int j = 0; j < cnt_section; j++)
        {
            if(!definedValues[i][j])
            {
                way.push_back({(colDefineNum[j] + rowDefineNum[i] + squareDefineNum[getNumSquare(i, j)]), {i, j}});
            }

        }
    }

    // Сортировка по первому элементу пары (весу)
    // В качестве компаратора использовано лямбда-выражение
    std::sort(way.begin(), way.end(), [](auto a, auto b) {return a.first > b.first;});
    bool rezult;
    rezult = backtraking_on_map(&way);
    return rezult;
}

bool Solver::backtraking_on_map(const weightedCells* way)
{
    bool flagNull = false;
    auto currentCell = way->begin();
    for(; currentCell < way->end(); currentCell++)
    {
        if(matrix[currentCell->second.row][currentCell->second.col] == 0)
        {
            flagNull = true;
            break;
        }
    }

    if(!flagNull)
        return true;

    for(int i = 1; i < 10; i++)
    {
        if(isSafe(currentCell->second.row, currentCell->second.col, i))
        {
            matrix[currentCell->second.row][currentCell->second.col] = i;
            if(backtraking_on_map(way))
                return true;
            matrix[currentCell->second.row][currentCell->second.col] = 0;
        }
    }

    return false;
}

//Передавать индекс начала прохода? чтобы не начинал обход каждый раз заново
bool Solver::solve(qint64& time, int algorithm)
{
    for(int i = 0; i < cnt_section; i++)
    {
        for(int j = 0 ; j < cnt_section; j++)
        {
            if(!definedValues[i][j])
                continue;
            if(!isSafe(i, j, matrix[i][j]))
                throw "В исходной матрице есть повторяющиеся числа!";
        }
    }

    QElapsedTimer timer;

    switch(algorithm)
    {
    case BACKTRAKING:
    {
        bool isSolve;
        timer.start();
        isSolve = solve_backtraking();
        time = timer.nsecsElapsed();
        return isSolve;
    }
    case SORT_BACKTRAKING:
    {
        bool isSolve;
        timer.start();
        isSolve = solve_sort_backtraking();
        time = timer.nsecsElapsed();
        return isSolve;
    }
    default:
        return false;
    }

}

Solver::~Solver()
{
    for(int i = 0; i < cnt_section; i++)
    {
        delete[] matrix[i];
        delete[] definedValues[i];
    }


    delete [] matrix;
    delete [] definedValues;
}
