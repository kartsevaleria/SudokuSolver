#include "customitemdelegate.h"

QVariant customItemDelegate::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::BackgroundRole:
        {
        //    Определение квадратов для закрашивания
            if((index.column() < 3 || index.column() > 5) && (index.row() < 3 || index.row() > 5))
                return QBrush("#d8d8d8");
            else if(index.column() >= 3 && index.column() <= 5 && index.row() <=5 && index.row() >= 3 )
                return QBrush("#d8d8d8");
            else
                return QIdentityProxyModel::data(index, role);
        }
    case Qt::ForegroundRole:
        {
            bool isNull;
            emit updateIsNull(index, isNull);
            if(isNull)
                return QBrush("#b22222");
            else
                return QBrush(QColorConstants::Black);
        }
    case Qt::TextAlignmentRole:
        {
            return Qt::AlignCenter;
        }
    default:
       return QIdentityProxyModel::data(index, role);
    }

}
