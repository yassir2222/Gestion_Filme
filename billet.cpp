#include "billet.h"
#include "ui_billet.h"
#include "afficher_billet.h"

billet::billet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::billet)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/Hp/Desktop/imageCpp/ticket.png");
    ui->label_pic->setPixmap(pix);

    DB_Connection =QSqlDatabase::addDatabase("QSQLITE");
    DB_Connection.setDatabaseName("C:/Users/Hp/Desktop/gestion_film/Gestion_Filme.db");
    if(DB_Connection.open()){
        qDebug() <<"Database Is Connected";
    }else{
        qDebug() <<"Database Is Not Connected";
        qDebug() <<"Error : "<<DB_Connection.lastError();

    }


    QSqlQuery QueryLoadeDataSeance(DB_Connection);

    QueryLoadeDataSeance.prepare("SELECT id_seance FROM Seance");
    QSqlQueryModel * modal=new QSqlQueryModel();
    if(QueryLoadeDataSeance.exec()) {
        qDebug() << "Données ajoutées avec succès.1";
    } else {
        qDebug() << "Erreur lors de l'ajout1 :" << QueryLoadeDataSeance.lastError().text();
    }


    modal->setQuery(QueryLoadeDataSeance);
    ui->comboBox->setModel(modal);

}

billet::~billet()
{
    delete ui;
}

void billet::on_pushButton_Insert_Data_clicked()
{
    DB_Connection.open();
    QSqlDatabase::database().transaction();
    QSqlQuery QueryInsertData_Billet(DB_Connection);
    QSqlQuery QuerySelectNbrPlace_Seance(DB_Connection);
    QSqlQuery QuerySelectId_Client(DB_Connection);
    QSqlQuery QueryUpdatNbrPlace_Seance(DB_Connection);




    int id_Client=0;



    QuerySelectId_Client.prepare("SELECT id FROM client where nom='"+ui->lineEdit_Nom_Client->text()+"' AND prenom='"+ui->lineEdit_Prenom_Client->text()+"'");
    if(QuerySelectId_Client.exec()){
        while(QuerySelectId_Client.next()){
            id_Client=QuerySelectId_Client.value(0).toInt();
        }
    }

    int nbrePlace=0;
    QuerySelectNbrPlace_Seance.prepare("SELECT nbrPlace FROM Seance where id_seance=:id_input");
    QuerySelectNbrPlace_Seance.bindValue(":id_input",ui->comboBox->currentText().toInt());
    if(QuerySelectNbrPlace_Seance.exec()){
        while(QuerySelectNbrPlace_Seance.next()){
            nbrePlace=QuerySelectNbrPlace_Seance.value(0).toInt();
            ui->nbrPlace->setText(QuerySelectNbrPlace_Seance.value(0).toString());
        }
    }


    nbrePlace=nbrePlace-1;


    if(nbrePlace>0){
    QueryUpdatNbrPlace_Seance.prepare("UPDATE Seance SET nbrPlace=:nbrePlace WHERE id_seance=:id_seance");

    QueryUpdatNbrPlace_Seance.bindValue(":nbrePlace",nbrePlace);
    QueryUpdatNbrPlace_Seance.bindValue(":id_seance",ui->comboBox->currentText().toInt());

    if(QueryUpdatNbrPlace_Seance.exec()) {
        qDebug() << "Données update avec succès.";
    } else {
        qDebug() << "Erreur lors de la mise a jour :" << QueryUpdatNbrPlace_Seance.lastError().text();
    }



    QueryInsertData_Billet.prepare("INSERT INTO billet (prix,date_Achat,id_client,id_seance) VALUES (:prix,:date_Achat,:id_client,:id_seance)");
    qDebug() << "Erreur 1 :" << QueryInsertData_Billet.lastError().text();

    QueryInsertData_Billet.bindValue(":prix",ui->lineEdit_Prix->text());
    QueryInsertData_Billet.bindValue(":date_Achat",ui->dateEdit_Achat->text());
    QueryInsertData_Billet.bindValue(":id_client",id_Client);
    QueryInsertData_Billet.bindValue(":id_seance",ui->comboBox->currentText().toInt());



    if(QueryInsertData_Billet.exec()) {
        QMessageBox::information(this,":)"," Données ajoutées avec succès.");
    } else {
        QMessageBox::information(this,":("," Erreur lors de l'ajout '"+QueryInsertData_Billet.lastError().text()+"'");

    }

    }else{
    QMessageBox::information(this,":("," Salle est Plein");

    }
    QSqlDatabase::database().commit();
    DB_Connection.close();
}


void billet::on_comboBox_activated(int a)
{
    int id_filme=0;
    QString NameFilme;
    DB_Connection.open();
    QSqlDatabase::database().transaction();
    QSqlQuery QuerySelectIdFilm(DB_Connection);
    QSqlQuery QuerySelectNameFilm(DB_Connection);
    QSqlQuery QuerySelectNbrPlace_Seance(DB_Connection);

    QuerySelectNbrPlace_Seance.prepare("SELECT nbrPlace FROM Seance where id_seance=:id_input");
    QuerySelectNbrPlace_Seance.bindValue(":id_input",ui->comboBox->currentText().toInt());
    if(QuerySelectNbrPlace_Seance.exec()){
    while(QuerySelectNbrPlace_Seance.next()){
        ui->nbrPlace->setText(QuerySelectNbrPlace_Seance.value(0).toString());
    }
    }


    QuerySelectIdFilm.prepare("SELECT id_filme FROM Seance WHERE id_seance=:id_Input");
    QuerySelectIdFilm.bindValue(":id_Input",ui->comboBox->currentText());
    if(QuerySelectIdFilm.exec()){
        while(QuerySelectIdFilm.next()){
            id_filme=QuerySelectIdFilm.value(0).toInt();
        }
    }

    QuerySelectNameFilm.prepare("SELECT Titre FROM Filme where ID_Filme=:id_filme");
    QuerySelectNameFilm.bindValue(":id_filme",id_filme);

    if(QuerySelectNameFilm.exec()){
        while(QuerySelectNameFilm.next()){
            ui->name_Filme->setText( QuerySelectNameFilm.value(0).toString());
        }
    }
}


void billet::on_pushButton_Affichage_clicked()
{
    Afficher_Billet Billet2;
    Billet2.setModal(true);
    Billet2.exec();

}

