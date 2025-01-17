#include "sudokutablemodel.h"



sudokuTableModel::sudokuTableModel(QObject* parent) : QAbstractTableModel( parent )
{

    cnt_section = 9;
    flagEdit = true;

    m_sudoku = new int*[cnt_section];
    for(int i = 0; i < cnt_section; i++)
        m_sudoku[i] = new int[9];

    //DEBUG
    for(int i = 0; i < cnt_section; i++)
    {
        for(int j = 0; j < cnt_section; j++)
            m_sudoku[i][j] = 0;
    }

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
