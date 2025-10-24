#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QDialog>
#include <QDate>

namespace Ui {
class AddEvent;
}

class AddEvent : public QDialog
{
    Q_OBJECT

public:
    explicit AddEvent(QWidget *parent = nullptr);
    ~AddEvent();
    void setDefaultDate(QDate date);

private:
    Ui::AddEvent *ui;
};

#endif // ADDEVENT_H
