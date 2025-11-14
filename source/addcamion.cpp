#include "addcamion.h"
#include "ui_addcamion.h"

AddCamion::AddCamion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCamion)
{
    ui->setupUi(this);

    ui->immatLine->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Z]{2}-[0-9]{3}-[A-Z]{2}"), this));

    DatabaseSingleton& instance = DatabaseSingleton::get_instance();
    maindb = instance.get_db();

    QStringList types;

    types << "Porteur";
    types << "Tracteur";

    ui->typeCombo->insertItems(0,types);
}

AddCamion::~AddCamion()
{
    delete ui;
}

void AddCamion::on_addTruckBtn_clicked()
{
    QSqlQuery query(maindb);

    QString immat = ui->immatLine->text();
    QString type = ui->typeCombo->currentText();
    int pos = 0;

    if(ui->immatLine->validator()->validate(immat, pos) == QValidator::Intermediate){
        QMessageBox::critical(this, "regex error", "Format d'immatriculation : AA-999-AA");
        return;
    } else {
        query.prepare("INSERT INTO Trucks (immat, type) VALUES (:immat, :type)");
        query.bindValue(":immat", immat);
        query.bindValue(":type",type);

        if (!query.exec()) {
            QMessageBox::critical(this, "SQL Error", query.lastError().text());
        }
        this->close();
    }


}


void AddCamion::on_cancelBtn_clicked()
{
    this->close();
}

