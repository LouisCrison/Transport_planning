#ifndef DISPLAY_CHAUFFEURS_H
#define DISPLAY_CHAUFFEURS_H

#include <QWidget>

namespace Ui {
class DisplayCHauffeurs;
}

class DisplayCHauffeurs : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayCHauffeurs(QWidget *parent = nullptr);
    ~DisplayCHauffeurs();

private:
    Ui::DisplayCHauffeurs *ui;
};

#endif // DISPLAY_CHAUFFEURS_H
