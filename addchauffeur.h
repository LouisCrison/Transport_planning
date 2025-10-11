#ifndef ADDCHAUFFEUR_H
#define ADDCHAUFFEUR_H

#include <QDialog>

namespace Ui {
class addChauffeur;
}

class addChauffeur : public QDialog
{
    Q_OBJECT

public:
    explicit addChauffeur(QWidget *parent = nullptr);
    ~addChauffeur();

private:
    Ui::addChauffeur *ui;
};

#endif // ADDCHAUFFEUR_H
