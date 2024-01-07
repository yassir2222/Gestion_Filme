#ifndef AFFICHER_BILLET_H
#define AFFICHER_BILLET_H

#include <QDialog>
#include <QtSql>
namespace Ui {
class Afficher_Billet;
}

class Afficher_Billet : public QDialog
{
    Q_OBJECT

public:
    explicit Afficher_Billet(QWidget *parent = nullptr);
    ~Afficher_Billet();

private:
    Ui::Afficher_Billet *ui;
    QSqlDatabase DB_Connection;

};

#endif // AFFICHER_BILLET_H
