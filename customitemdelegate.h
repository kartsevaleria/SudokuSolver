#ifndef CUSTOMITEMDELEGATE_H
#define CUSTOMITEMDELEGATE_H

#include <QTableView>
#include <QIdentityProxyModel>


class customItemDelegate : public QIdentityProxyModel
{
    Q_OBJECT
public:
    explicit customItemDelegate(QObject *parent = 0)
        : QIdentityProxyModel(parent) {}
    virtual ~customItemDelegate() {}
    QVariant data(const QModelIndex &index, int role = Qt::EditRole) const;


};

#endif // CUSTOMITEMDELEGATE_H
