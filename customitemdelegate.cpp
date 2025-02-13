#include "customitemdelegate.h"

QVariant customItemDelegate::data(const QModelIndex &index, int role) const
{
    if(role == Qt::BackgroundRole)
    {
        //Определение квадратов для закрашивания
        if((index.column() < 3 || index.column() > 5) && (index.row() < 3 || index.row() > 5))
            return QBrush(QColorConstants::Gray);
        else if(index.column() >= 3 && index.column() <= 5 && index.row() <=5 && index.row() >= 3 )
            return QBrush(QColorConstants::Gray);
        else
            return QIdentityProxyModel::data(index, role);
    }
    else
        return QIdentityProxyModel::data(index, role);

}
