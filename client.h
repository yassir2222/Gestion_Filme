#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_pushButton_Data_clicked();

    void on_pushButton_updat_clicked();

    void on_pushButton_Delet_clicked();

    void on_pushButton_load_Data_clicked();

private:
    Ui::Client *ui;
    QSqlDatabase DB_Connection;

};

#endif // CLIENT_H
