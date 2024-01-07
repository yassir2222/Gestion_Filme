#include "seance.h"
#include "ui_seance.h"


seance::seance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::seance)

{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Hp/Desktop/imageCpp/Seance.jpg");
    ui->label_pic->setPixmap(pix);

    DB_Connection =QSqlDatabase::addDatabase("QSQLITE");
    DB_Connection.setDatabaseName("C:/Users/Hp/Desktop/gestion_film/Gestion_Filme.db");
    if(DB_Connection.open()){
        qDebug() <<"Database Is Connected";
    }else{
        qDebug() <<"Database Is Not Connected";
        qDebug() <<"Error : "<<DB_Connection.lastError();

    }

    QSqlQuery QueryLoadeDataFilme(DB_Connection);

    QueryLoadeDataFilme.prepare("SELECT Titre FROM Filme");
    QSqlQueryModel * modal=new QSqlQueryModel();
    if(QueryLoadeDataFilme.exec()) {
        qDebug() << "Données ajoutées avec succès.1";
    } else {
        qDebug() << "Erreur lors de l'ajout1 :" << QueryLoadeDataFilme.lastError().text();
    }
    modal->setQuery(QueryLoadeDataFilme);
    ui->comboBox->setModel(modal);


}

seance::~seance()
{
    delete ui;
}

void seance::on_pushButton_clicked()
{
    DB_Connection.open();
    QSqlDatabase::database().transaction();
    QSqlQuery QueryInsertData(DB_Connection);
    QSqlQuery QuerySelectId(DB_Connection);
    QSqlQuery QueryVerify(DB_Connection);
    QSqlQuery QueryCapaciter(DB_Connection);


    QString filmeName=ui->comboBox->currentText();
    int id_filme=0;
    int count=0;
    int capacite=0;
    QuerySelectId.prepare("SELECT ID_Filme FROM Filme where Titre='"+filmeName+"'");
    if(QuerySelectId.exec()){
        while(QuerySelectId.next()){
            id_filme=QuerySelectId.value(0).toInt();
        }
    }
    QueryVerify.prepare("SELECT * FROM Seance where id_filme=:id_filme1 AND Date_Debut=:Date_Debut1 AND Heure_Debut<=:Heure_Debut1 AND Heure_Fin>=:Heure_Fin1");
    qDebug() <<"error3" <<QueryVerify.lastError().text();
    QueryVerify.bindValue(":id_filme1",id_filme);

    QueryVerify.bindValue(":Date_Debut1",ui->dateEdit->text());
    QueryVerify.bindValue(":Heure_Debut1",ui->Input_debut->text().toInt());
    QueryVerify.bindValue(":Heure_Fin1",ui->Input_Fin->text().toInt());
    if(QueryVerify.exec()) {

        while(QueryVerify.next()){
            count++;
        }
        if(count<1){
            QueryCapaciter.prepare("SELECT capacite FROM Salle where id_Salle=:id_input");
            QueryCapaciter.bindValue(":id_input",ui->Input_salle->text().toInt());
            qDebug() <<"error4" <<QueryCapaciter.lastError().text();

            if(QueryCapaciter.exec()){
                while(QueryCapaciter.next()){
                    capacite=QueryCapaciter.value(0).toInt();
                }
            }



            QueryInsertData.prepare("INSERT INTO Seance(id_salle,id_filme,Date_Debut,Heure_Debut,Heure_Fin,nbrPlace) VALUES(:id_salle,:id_filme,:Date_Debut,:Heure_Debut,:Heure_Fin,:nbrPlace)");
            qDebug() <<"error1" <<QueryInsertData.lastError().text();

            qDebug() << QueryInsertData.lastError().text();
            QueryInsertData.bindValue(":id_salle",ui->Input_salle->text().toInt());
            QueryInsertData.bindValue(":id_filme",id_filme);
            QueryInsertData.bindValue(":nbrPlace",capacite);
            QueryInsertData.bindValue(":Date_Debut",ui->dateEdit->date());
            QueryInsertData.bindValue(":Heure_Debut",ui->Input_debut->text().toInt());
            QueryInsertData.bindValue(":Heure_Fin",ui->Input_Fin->text().toInt());

            if(QueryInsertData.exec()) {

                QMessageBox::information(this,":)","Données ajoutées avec succès");
            } else {
                QMessageBox::critical(this,":(","Erreur lors de l'ajout : '"+QueryInsertData.lastError().text()+"'");
            }

        }else{
            QMessageBox::information(this,":("," Salle ocuppé dans cette période");

        }
    }

    QSqlDatabase::database().commit();
    DB_Connection.close();
}





void seance::on_pushButton_Afficher_clicked()
{
    Afficher_Seance seance2;
    seance2.setModal(true);
    seance2.exec();
}

