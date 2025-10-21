#ifndef ADDCHAUFFEUR_H
#define ADDCHAUFFEUR_H

#include <QDialog>

namespace Ui {
class AddChauffeur;
}

class AddChauffeur : public QDialog
{
    Q_OBJECT

public:
    explicit AddChauffeur(QWidget *parent = nullptr);
    ~AddChauffeur();

private:
    Ui::AddChauffeur *ui;
};

#endif // ADDCHAUFFEUR_H
