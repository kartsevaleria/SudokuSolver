#ifndef SUDOKUTABLEMODEL_H
#define SUDOKUTABLEMODEL_H


#include <QAbstractTableModel>
#include <QDebug>


class sudokuTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    sudokuTableModel(QObject* parent = 0);
    ~sudokuTableModel();

    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const {return QVariant::Int;}
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void setElemForDebug();

    void isEditable(bool flag);
    void clear();
//public slots:
//    void changeFlagLock(bool flag);

private:
    int cnt_section;
    int** m_sudoku;
    //bool** m_nullElem;
    bool flagEdit;

    //void createMatrixNullElem();

};

#endif // SUDOKUTABLEMODEL_H
