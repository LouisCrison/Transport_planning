#ifndef DISPLAYTOURNEE_H
#define DISPLAYTOURNEE_H

#include <QDialog>

namespace Ui {
class DisplayTournee;
}

class DisplayTournee : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayTournee(QWidget *parent = nullptr);
    ~DisplayTournee();

private:
    Ui::DisplayTournee *ui;
};

#endif // DISPLAYTOURNEE_H
