#include "afficher_seance.h"
#include "ui_afficher_seance.h"

Afficher_Seance::Afficher_Seance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Afficher_Seance)
{
    ui->setupUi(this);

    DB_Connection.open();
    QSqlQuery QueryLoadData(DB_Connection);
    QSqlQueryModel *modal=new QSqlQueryModel();

    QueryLoadData.prepare("select * from billet");

    QueryLoadData.exec();

    modal->setQuery(QueryLoadData);
    ui->tableView->setModel(modal);
    DB_Connection.close();
}

Afficher_Seance::~Afficher_Seance()
{
    delete ui;
}
