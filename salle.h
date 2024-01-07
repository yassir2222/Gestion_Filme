#ifndef SALLE_H
#define SALLE_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Salle;
}

class Salle : public QDialog
{
    Q_OBJECT

public:
    explicit Salle(QWidget *parent = nullptr);
    ~Salle();

private slots:
    void on_Ajout_clicked();

    void on_Affiche_clicked();

private:
    Ui::Salle *ui;
    QSqlDatabase DB_Connection;

};

#endif // SALLE_H
