#include "sudokutablemodel.h"



sudokuTableModel::sudokuTableModel(QObject* parent) : QAbstractTableModel( parent )
{

    cnt_section = 9;
    flagEdit = true;

    m_sudoku = new int*[cnt_section];
    for(int i = 0; i < cnt_section; i++)
        m_sudoku[i] = new int[9];


    for(int i = 0; i < cnt_section; i++)
    {
        for(int j = 0; j < cnt_section; j++)
            m_sudoku[i][j] = 0;
    }

     //DEBUG
    m_sudoku[0][0] = 5;
    m_sudoku[0][1] = 3;
    m_sudoku[0][4] = 7;

    m_sudoku[1][0] = 6;
    m_sudoku[1][3] = 1;
    m_sudoku[1][4] = 9;
    m_sudoku[1][5] = 5;

    m_sudoku[2][1] = 9;
    m_sudoku[2][2] = 8;
    m_sudoku[2][7] = 6;

    m_sudoku[3][0] = 8;
    m_sudoku[3][4] = 6;
    m_sudoku[3][8] = 3;

    m_sudoku[4][0] = 4;
    m_sudoku[4][3] = 8;
    m_sudoku[4][5] = 3;
    m_sudoku[4][8] = 1;

    m_sudoku[5][0] = 7;
    m_sudoku[5][4] = 2;
    m_sudoku[5][8] = 6;

    m_sudoku[6][1] = 6;
    m_sudoku[6][6] = 2;
    m_sudoku[6][7] = 8;

    m_sudoku[7][3] = 4;
    m_sudoku[7][4] = 1;
    m_sudoku[7][5] = 9;
    m_sudoku[7][8] = 5;

    m_sudoku[8][4] = 8;
    m_sudoku[8][7] = 7;
    m_sudoku[8][8] = 9;

}

int sudokuTableModel::rowCount(const QModelIndex &parent) const
{
    return cnt_section;
}

int sudokuTableModel::columnCount(const QModelIndex &parent) const
{
    return cnt_section;
}

QVariant sudokuTableModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();
    return m_sudoku[index.row()][index.column()];
}

Qt::ItemFlags sudokuTableModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(index.isValid() && this->flagEdit)
         flags |= Qt::ItemIsEditable;

    return flags;
}

bool sudokuTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    int valueInt = value.toInt();
    if(!index.isValid() || valueInt < 0 || valueInt > 9)
        return false;
    m_sudoku[index.row()][index.column()] = valueInt;
    emit dataChanged(index, index);
    //Слот обновления таблицы?
    return true;
}

void sudokuTableModel::isEditable(bool flag)
{
    this->flagEdit = flag;
}

//void sudokuTableModel::changeFlagLock(bool flag)
//{
//    this->flagLockEdit = flag;
//    qDebug() << this->flagLockEdit;
//}

sudokuTableModel::~sudokuTableModel()
{

}
