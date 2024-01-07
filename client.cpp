#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Hp/Desktop/imageCpp/user.png");
    ui->label_pic->setPixmap(pix);

    DB_Connection =QSqlDatabase::addDatabase("QSQLITE");
    DB_Connection.setDatabaseName("C:/Users/Hp/Desktop/gestion_film/Gestion_Filme.db");
    if(DB_Connection.open()){
        qDebug() <<"Database Is Connected";
    }else{
        qDebug() <<"Database Is Not Connected";
        qDebug() <<"Error : "<<DB_Connection.lastError();

    }
}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_Data_clicked()
{
    DB_Connection.open();
    QSqlDatabase::database().transaction();
    QSqlQuery QueryInsertData_Client(DB_Connection);
    QueryInsertData_Client.prepare("INSERT INTO client(CIN,nom,prenom) VALUES(:CIN,:nom,:prenom)");

    QueryInsertData_Client.bindValue(":CIN",ui->lineEdit_CIN->text());
    QueryInsertData_Client.bindValue(":nom",ui->lineEdit_Nom->text());
    QueryInsertData_Client.bindValue(":prenom",ui->lineEdit_Prenom->text());

    if(QueryInsertData_Client.exec()) {
        QMessageBox::information(this,":)","Données ajoutées avec succès");
    } else {
        QMessageBox::critical(this,":(","Erreur lors de l'ajout : '"+QueryInsertData_Client.lastError().text()+"'");
    }
    QSqlDatabase::database().commit();
    DB_Connection.close();
}


void Client::on_pushButton_updat_clicked()
{
    DB_Connection.open();
    QSqlDatabase::database().transaction();
    QSqlQuery QueryUpdatData_Client(DB_Connection);
    QueryUpdatData_Client.prepare("UPDATE client SET CIN=:CIN ,nom=:nom,prenom=:prenom WHERE CIN=:CIN");

    QueryUpdatData_Client.bindValue(":CIN",ui->lineEdit_CIN->text());
    QueryUpdatData_Client.bindValue(":nom",ui->lineEdit_Nom->text());
    QueryUpdatData_Client.bindValue(":prenom",ui->lineEdit_Prenom->text());

    if(QueryUpdatData_Client.exec()) {
        QMessageBox::information(this,":)","Données Modifié avec succès");
    } else {
        QMessageBox::critical(this,":(","Erreur lors de La modification : '"+QueryUpdatData_Client.lastError().text()+"'");
            }
    QSqlDatabase::database().commit();
    DB_Connection.close();
}


void Client::on_pushButton_Delet_clicked()
{
    DB_Connection.open();
    QSqlDatabase::database().transaction();
    QSqlQuery QueryDeletData_Client(DB_Connection);
    QueryDeletData_Client.prepare("DELETE FROM client WHERE CIN=:CIN");

    QueryDeletData_Client.bindValue(":CIN",ui->lineEdit_CIN->text());

    if(QueryDeletData_Client.exec()) {
        QMessageBox::information(this,":)","Données Supprimé avec succès");
    } else {
        QMessageBox::critical(this,":(","Erreur lors de La Suppression : '"+QueryDeletData_Client.lastError().text()+"'");
    }
    QSqlDatabase::database().commit();
    DB_Connection.close();
}


void Client::on_pushButton_load_Data_clicked()
{
    DB_Connection.open();
    QSqlQuery QueryLoadData(DB_Connection);
    QSqlQueryModel *modal=new QSqlQueryModel();

    QueryLoadData.prepare("select * from client");

    QueryLoadData.exec();

    modal->setQuery(QueryLoadData);
    ui->tableView->setModel(modal);
    DB_Connection.close();
}

