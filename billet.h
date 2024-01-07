#ifndef BILLET_H
#define BILLET_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class billet;
}

class billet : public QDialog
{
    Q_OBJECT

public:
    explicit billet(QWidget *parent = nullptr);
    ~billet();

private slots:
    void on_pushButton_Insert_Data_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_Affichage_clicked();

private:
    Ui::billet *ui;
    QSqlDatabase DB_Connection;

};

#endif // BILLET_H
