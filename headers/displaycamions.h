#ifndef DISPLAYCAMIONS_H
#define DISPLAYCAMIONS_H

#include <QDialog>

namespace Ui {
class DisplayCamions;
}

class DisplayCamions : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayCamions(QWidget *parent = nullptr);
    ~DisplayCamions();

private:
    Ui::DisplayCamions *ui;
};

#endif // DISPLAYCAMIONS_H
