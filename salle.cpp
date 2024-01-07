#include "salle.h"
#include "ui_salle.h"

Salle::Salle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Salle)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Hp/Desktop/imageCpp/salle.png");
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

Salle::~Salle()
{
    delete ui;
}

void Salle::on_Ajout_clicked()
{
    DB_Connection.open();
    QSqlDatabase::database().transaction();
    QSqlQuery QueryInsertData_Salle(DB_Connection);
qDebug() <<"Error : "<<DB_Connection.lastError();
    QueryInsertData_Salle.prepare("INSERT INTO Salle(capacite,disponibilite,equipement) VALUES(:capacite,'disponible',:equipment)");
    qDebug() <<"Error : "<<QueryInsertData_Salle.lastError().text();
    QueryInsertData_Salle.bindValue(":capacite",ui->capacite->text().toInt());
    QueryInsertData_Salle.bindValue(":equipment",ui->equipement->text());

    if(QueryInsertData_Salle.exec()) {
        qDebug() <<"Error : "<<QueryInsertData_Salle.lastError().text();
        qDebug() << "Données ajoutées avec succès.";
    } else {
        qDebug() << "Erreur lors de l'ajout :" << QueryInsertData_Salle.lastError().text();
    }
    QSqlDatabase::database().commit();
    DB_Connection.close();

}


void Salle::on_Affiche_clicked()
{
    DB_Connection.open();
    QSqlQuery QueryLoadData(DB_Connection);
    QSqlQueryModel *modal=new QSqlQueryModel();

    QueryLoadData.prepare("select id_Salle,capacite,equipement from Salle");

    QueryLoadData.exec();

    modal->setQuery(QueryLoadData);
    ui->tableView->setModel(modal);
    DB_Connection.close();
}

