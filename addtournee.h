#ifndef ADDTOURNEE_H
#define ADDTOURNEE_H

#include <QDialog>

namespace Ui {
class AddTournee;
}

class AddTournee : public QDialog
{
    Q_OBJECT

public:
    explicit AddTournee(QWidget *parent = nullptr);
    ~AddTournee();

private:
    Ui::AddTournee *ui;
};

#endif // ADDTOURNEE_H
