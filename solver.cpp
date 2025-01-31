#include "solver.h"

bool Solver::isValid(const int col, const int row)
{
    if(col < cnt_section || row < cnt_section)
        return true;
    else
        return false;
}

int Solver::getNumber(const int col, const int row)
{
    if(isValid(col, row))
        return matrix[col][row];
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
    for(int i = 0; i < cnt_section; ++i)
    {
        if(i == row)
            continue;
        if(matrix[numCol][i] == num)
            return false;
    }
    return true;
}

bool Solver::rowIsSafe(const int col, const int row, int num)
{
    int numRow = row;
    for(int i = 0; i < cnt_section; ++i)
    {
        if(i == col)
            continue;
        if(matrix[i][numRow] == num)
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

    if(endRow == 2)
        startRow = 0;
    else
        startRow = endRow - 2;

    if(endCol == 2)
        startCol = 0;
    else
        startCol = endCol - 2;


    for(int i = startCol; i <= endCol; i++)
    {
        for(int j = startRow; j <= endRow; j++)
        {
            if(i == col && j == row)
                continue;
            if(matrix[i][j] == num)
                return false;
        }
    }

    return true;
}

bool Solver::isSafe(const int col, const int row, int num)
{
    if(colIsSafe(col, row, num) && rowIsSafe(col, row, num) && squareIsSafe(col, row, num))
        return true;
    else
        return false;
}

//Передавать индекс начала прохода? чтобы не начинал обход каждый раз заново
bool Solver::solve(int colNull, int rowNull)
{
    int nextColNull;
    int nextRowNull;
    bool flagNull = false;
    for(; colNull < cnt_section; colNull++)
    {
        for(; rowNull < cnt_section; rowNull++)
        {
            if(!definedValues[colNull][rowNull])
            {
                flagNull = true;
                break;
            }

        }
        if(flagNull)
            break;
    }


    for(int i = 1; i < 10; i++)
    {

        if(isSafe(colNull, rowNull, i))
        {
            matrix[colNull][rowNull] = i;
            qDebug() << "row: " << rowNull ;
            qDebug() << "col: " << colNull;
            qDebug() << "i: " << i;
            qDebug() << " ";
            if(rowNull == 8)
            {
                nextRowNull = 0;
                nextColNull = colNull + 1;
            }
            else
            {
                nextRowNull = rowNull + 1;
                nextColNull = colNull;
            }


            if(solve(nextColNull, nextRowNull))
                return true;

            matrix[colNull][rowNull] = 0;
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
