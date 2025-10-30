#ifndef DISPLAYCLIENT_H
#define DISPLAYCLIENT_H

#include "addclient.h"

#include <QDialog>

namespace Ui {
class DisplayClient;
}

class DisplayClient : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayClient(QWidget *parent = nullptr);
    ~DisplayClient();

private slots:
    void on_addClientBtn_clicked();

private:
    Ui::DisplayClient *ui;
};

#endif // DISPLAYCLIENT_H
