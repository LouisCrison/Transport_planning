#include "nullrelationaldelegate.h"

TourneesRelationalDelegate::TourneesRelationalDelegate(QObject* parent) : QSqlRelationalDelegate(parent) {
    qDebug() << "in the constructor";
}


QWidget* TourneesRelationalDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    qDebug() << "before editor create";
    QWidget* editor = QSqlRelationalDelegate::createEditor(aParent, option, index);

    QComboBox* cb = qobject_cast<QComboBox*>(editor);

    cb->insertItem(0, "<Aucun>", QVariant());

    return editor;
}

void TourneesRelationalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {

    QComboBox* cb = qobject_cast<QComboBox*>(editor);

    QVariant driver = cb->currentData();

    qDebug() << driver.toString();

    QVariant name = model->index(index.row(), 0).data();

    QSqlDatabase maindb = qobject_cast<QSqlTableModel*>(model)->database();

    QSqlQuery query = QSqlQuery(maindb);



    query.prepare("UPDATE Tournees SET driver = :driver WHERE name = :name");
    query.bindValue(":driver",driver);
    query.bindValue(":name",name);
    query.exec();
}
