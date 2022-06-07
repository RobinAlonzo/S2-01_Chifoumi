#include "chifoumivue.h"

#include "ui_chifoumivue.h"
#include <QMetaObject>

ChifoumiVue ::ChifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
{
    ui->setupUi(this);   
    //Connection des signals et des slots
    QObject::connect(ui->boutonPartie,SIGNAL(clicked()),this,SLOT(nouvellePartie()));
    QObject::connect(ui->boutonCiseau, SIGNAL(clicked()),this,SLOT(ciseau()));
    QObject::connect(ui->boutonPierre, SIGNAL(clicked()),this,SLOT(pierre()));
    QObject::connect(ui->boutonPapier, SIGNAL(clicked()),this,SLOT(papier()));

    setEtatJeu(horsPartie);

}

ChifoumiVue ::~ChifoumiVue()
{
    delete ui;
}

ChifoumiVue::UnEtat ChifoumiVue::getEtatJeu()
{
    return etatJeu;
}

void ChifoumiVue::setEtatJeu(UnEtat etat)
{
    etatJeu = etat;
}

Chifoumi *ChifoumiVue::getModele()
{
    return modele;
}

void ChifoumiVue::setModele(Chifoumi * m)
{
    modele = m;
}

void ChifoumiVue::majImageCoupMachine()
{
    Chifoumi::UnCoup c;
    c = modele->getCoupMachine();

    switch (c) {
    case Chifoumi::pierre:
        ui->imageCoupMachine->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/pierre.gif")));
        break;
    case Chifoumi::ciseau:
        ui->imageCoupMachine->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/ciseau.gif")));
        break;
    case Chifoumi::papier:
        ui->imageCoupMachine->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/papier.gif")));
        break;
    case Chifoumi::rien:
        ui->imageCoupMachine->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/rien.gif")));
        break;
    default: break;
    }
}

void ChifoumiVue::majImageCoupJoueur()
{
    Chifoumi::UnCoup c;
    c = modele->getCoupJoueur();

    switch (c) {
    case Chifoumi::pierre:
        ui->imageCoupJoueur->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/pierre.gif")));
        break;
    case Chifoumi::ciseau:
        ui->imageCoupJoueur->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/ciseau.gif")));
        break;
    case Chifoumi::papier:
        ui->imageCoupJoueur->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/papier.gif")));
        break;
    case Chifoumi::rien:
        ui->imageCoupJoueur->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/rien.gif")));
        break;
    default: break;
    }
}

void ChifoumiVue::majLabelScoreMachine()
{
    unsigned int s;
    QString inutile;

    s = modele->getScoreMachine();
    ui->labelScoreMachine->setText(inutile.setNum(s));
}

void ChifoumiVue::majLabelScoreJoueur()
{
    unsigned int s;
    QString inutile;
    s = modele->getScoreJoueur();

    ui->labelScoreJoueur->setText(inutile.setNum(s));
}

void ChifoumiVue::jouer(Chifoumi::UnCoup coup)
{
    switch(etatJeu)
    {
    case horsPartie:
        //neant
        break;
    case partieEnCours :
        // -- activte 2 --
        // mise a jour du modele
        modele->setCoupJoueur(coup);
        modele->setCoupMachine(modele->genererUnCoup());
        modele->majScores(modele->determinerGagnant());

        // changement d'état
        setEtatJeu(partieEnCours);

        // mise à jour de l'interface
        majImageCoupMachine();
        majImageCoupJoueur();
        majLabelScoreMachine();
        majLabelScoreJoueur();

        break;
    default :
        break;
    }
}

void ChifoumiVue::pierre()
{
    ChifoumiVue::jouer(Chifoumi::pierre);
}

void ChifoumiVue::ciseau()
{
    ChifoumiVue::jouer(Chifoumi::ciseau);
}

void ChifoumiVue::papier()
{
    ChifoumiVue::jouer(Chifoumi::papier);
}

void ChifoumiVue::nouvellePartie()
{
    switch(etatJeu)
    {
    case horsPartie:
        // -- activite 1 --
        // mise a jour du modele
        // changement d'état
        setEtatJeu(partieEnCours); // on reste ds le même état

        // mise à jour de l'interface
        ui->boutonCiseau->setEnabled(true);
        ui->boutonPapier->setEnabled(true);
        ui->boutonPierre->setEnabled(true);
        ui->boutonPartie->setFocus();

        break;

    case partieEnCours :
        // -- activite 3 --
        // mise a jour du modele
        modele->initCoups();
        modele->initScores();

        // changement d'état
        setEtatJeu(partieEnCours); // on reste dans le même état

        // mise à jour de l'interface
        majImageCoupJoueur();
        majImageCoupMachine();
        majLabelScoreJoueur();
        majLabelScoreMachine();
        ui->boutonPartie->setFocus();

        break;

    default :
        break;
    }

}
