#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>


#include "salle.h"
#include "client.h"
#include "seance.h"
#include "billet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Insert_Data_clicked();

    void on_pushButton_Ajout_salle_clicked();


    void on_pushButton_Ajout_client_clicked();

    void on_pushButton_clicked();

    void on_pushButton_Billet_clicked();

    void on_pushButton_load_Filme_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase DB_Connection;

};
#endif // MAINWINDOW_H
