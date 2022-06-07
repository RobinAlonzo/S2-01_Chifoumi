#include "db.h"
#include "ui_db.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QDebug>

Db::Db(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Db)
{
    ui->setupUi(this);

    //Initialisation des informations de la BDD
    db= QSqlDatabase::addDatabase(CONNECT_TYPE);
    db.setDatabaseName(DB_NAME);

    //Ferme le fenetre lorsqu'on clique sur le bouton quitter ou que les identifiants sont valides
    QObject::connect(ui->bQuitter, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this, SIGNAL(idJustes()), this, SLOT(close()));

    QObject::connect(ui->bValider, SIGNAL(clicked()), this, SLOT(analyseIdentifiants()));


    ui->lineEditMdp->setEchoMode(QLineEdit::EchoMode::Password); //Permet de masquer la lineEditMdp
}

Db::~Db()
{
    delete ui;
}

void Db::analyseIdentifiants()
{
    //Ouverture de la BDD
    if (!db.open())
    {
        qDebug() << "Connexion ratée";
    }
    QSqlQuery mdp;
    mdp.prepare("SELECT motDePasse FROM Utilisateur WHERE nom = ?");
    mdp.addBindValue(ui->lineEditId->text());
    mdp.exec();
    if (!mdp.next())
    {
        //Identifiant inexistant
        //Affichage du message d erreur
        QMessageBox msgErreur(this);
        msgErreur.setText("Identifiant inexistant");
        msgErreur.exec();

        //Effacement de la combinaison ratee
        ui->lineEditId->setText("");
        ui->lineEditMdp->setText("");

        //Remise du focus sur la premiere ligne
        ui->lineEditId->setFocus();
    }
    else if (mdp.value(0).toString() == ui->lineEditMdp->text())
    {
        //Mot de passe correspondant a l identfiant
        emit idJustes();
    }
    else
    {
        //Mot de passe incorrecte
        //Affichage du message d erreur
        QMessageBox msgErreur(this);
        msgErreur.setText("Mot de passe incorrecte");
        msgErreur.exec();

        //Effacement du mdp rate
        ui->lineEditMdp->setText("");
    }

    db.close(); //Fermeture de la BDD après requête
}

