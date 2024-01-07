#ifndef SEANCE_H
#define SEANCE_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include<QDateTime>
#include "afficher_seance.h"

namespace Ui {
class seance;
}

class seance : public QDialog
{
    Q_OBJECT

public:
    explicit seance(QWidget *parent = nullptr);
    ~seance();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_Afficher_clicked();

private:
    Ui::seance *ui;
    QSqlDatabase DB_Connection;
};

#endif // SEANCE_H
