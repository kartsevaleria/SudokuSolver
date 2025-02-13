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

//Передавать индекс начала прохода? чтобы не начинал обход каждый раз заново
bool Solver::solve()
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
            if(solve())
                return true;
            matrix[rowNull][colNull] = 0;
        }
    }
    return false;
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
