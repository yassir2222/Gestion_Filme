#include "afficher_billet.h"
#include "ui_afficher_billet.h"

Afficher_Billet::Afficher_Billet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Afficher_Billet)
{
    ui->setupUi(this);
    DB_Connection.open();
    QSqlQuery QueryLoadData(DB_Connection);
    QSqlQueryModel *modal=new QSqlQueryModel();

    QueryLoadData.prepare("select * from Seance");

    QueryLoadData.exec();

    modal->setQuery(QueryLoadData);
    ui->tableView->setModel(modal);
    DB_Connection.close();
}

Afficher_Billet::~Afficher_Billet()
{
    delete ui;
}
