#ifndef AFFICHER_SEANCE_H
#define AFFICHER_SEANCE_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Afficher_Seance;
}

class Afficher_Seance : public QDialog
{
    Q_OBJECT

public:
    explicit Afficher_Seance(QWidget *parent = nullptr);
    ~Afficher_Seance();

private:
    Ui::Afficher_Seance *ui;
    QSqlDatabase DB_Connection;

};

#endif // AFFICHER_SEANCE_H
