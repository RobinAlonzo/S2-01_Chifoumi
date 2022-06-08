#include "identification.h"
#include "ui_identification.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

Identification::Identification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Identification)
{
    ui->setupUi(this);

    //Ferme le fenetre lorsqu'on clique sur le bouton quitter
    connect(ui->bQuitter, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->bValider, SIGNAL(clicked()), this, SLOT(demandeVerif()));

    ui->lineEditMdp->setEchoMode(QLineEdit::EchoMode::Password); //Permet de masquer le mot de passe
}

Identification::~Identification()
{
    delete ui;
}

void Identification::majIdFaux()
{
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

void Identification::majMdpFaux()
{
    //Affichage du message d erreur
    QMessageBox msgErreur(this);
    msgErreur.setText("Mot de passe incorrecte");
    msgErreur.exec();

    //Effacement du mdp rate
    ui->lineEditMdp->setText("");
}
void Identification::majDbInaccessible()
{
    //Affichage du message d erreur
    QMessageBox msgErreur(this);
    msgErreur.setText("Base de donnee inaccessible donc \nauthentification impossible \n\nAu revoir");
    msgErreur.exec();

    //Effacement du mdp rate
    close();
}
void Identification::demandeVerif()
{
    emit validationId(ui->lineEditId->text(), ui->lineEditMdp->text());
}
