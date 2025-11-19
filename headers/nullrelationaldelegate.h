#ifndef NULLRELATIONALDELEGATE_H
#define NULLRELATIONALDELEGATE_H

#include <QSqlRelationalDelegate>
#include <QStyledItemDelegate>
#include <QWidget>
#include <QComboBox>
#include <QVariant>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlTableModel>

class TourneesRelationalDelegate : public QSqlRelationalDelegate
{
public:

    explicit TourneesRelationalDelegate(QObject *parent = nullptr);

    QWidget* createEditor(QWidget *aParent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
};

#endif // NULLRELATIONALDELEGATE_H
