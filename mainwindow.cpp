#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Hp/Desktop/imageCpp/cinema.png");
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

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Insert_Data_clicked(){
    DB_Connection.open();
    QSqlDatabase::database().transaction();
    QSqlQuery QueryInsertData(DB_Connection);


    QueryInsertData.prepare("INSERT INTO Filme (Titre,realisateur,genre,Date_de_Sortie,Description,Affiche) VALUES(:Titre,:realisateur,:genre,:Date_de_Sortie,:Description,:Affiche)");
    qDebug() << QueryInsertData.lastError().text();
    QueryInsertData.bindValue(":Titre",ui->lineEdit->text());
    QueryInsertData.bindValue(":realisateur",ui->lineEdit_2->text());

    QueryInsertData.bindValue(":genre",ui->lineEdit_3->text());
    QueryInsertData.bindValue(":Date_de_Sortie",ui->dateTimeEdit->dateTime());

    QueryInsertData.bindValue(":Description",ui->lineEdit_4->text());
    QueryInsertData.bindValue(":Affiche",ui->lineEdit_5->text());
    if(QueryInsertData.exec()) {
        QMessageBox::information(this,":)","Données ajoutées avec succès");

    } else {
        QMessageBox::information(this,":)","Données ajoutées avec succès "+QueryInsertData.lastError().text()+"");
    }
     QSqlDatabase::database().commit();
     DB_Connection.close();

}


void MainWindow::on_pushButton_Ajout_salle_clicked()
{
        Salle salle1;
        salle1.setModal(true);
        salle1.exec();
}

void MainWindow::on_pushButton_clicked()
{
        seance seance1;
        seance1.setModal(true);
        seance1.exec();
}

void MainWindow::on_pushButton_Ajout_client_clicked()
{
        Client client1;
        client1.setModal(true);
        client1.exec();
}


void MainWindow::on_pushButton_Billet_clicked()
{
        billet billet1;
        billet1.setModal(true);
        billet1.exec();

}


void MainWindow::on_pushButton_load_Filme_clicked()
{
        DB_Connection.open();
        QSqlQuery QueryLoadData(DB_Connection);
        QSqlQueryModel *modal=new QSqlQueryModel();

        QueryLoadData.prepare("select * from Filme");

        QueryLoadData.exec();

        modal->setQuery(QueryLoadData);
        ui->tableView->setModel(modal);
        DB_Connection.close();


}

