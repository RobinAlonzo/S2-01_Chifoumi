#include "presentation.h"
#include "chifoumivue.h"
#include "QDebug"
#include <QMessageBox>

Presentation::Presentation(Modele *m, QObject *parent)
    : QObject{parent}, _leModele(m)
{
}
void Presentation::conexionVue(ChifoumiVue *v)
{
    _laVue = v;
    //Initialisation score max
    scoreFin = 3;
    _laVue->initScoreFin(scoreFin);
}


Modele *Presentation::getModele()
{
    return _leModele;
}
ChifoumiVue *Presentation::getVue()
{
    return _laVue;
}


void Presentation::jouer(Modele::UnCoup c)
{
    if (_leModele->getEtatJeu() == Modele::partieEnCours)
    {
        // Activite 2
        // -- mise a jour du modele --
        _leModele->setCoupJoueur(c);
        _leModele->setCoupMachine(_leModele->genererUnCoup());
        _leModele->majScores(_leModele->determinerGagnant());


        if (scoreAtteint())
        {
            // -- changement d'état --
            _leModele->setEtatJeu(Modele::partieTerminee);
            // -- mise à jour de l'interface --
            _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());
            _laVue->setJoueurEnBleu(false);
            _laVue->focusBJouer();
            _laVue->setEtatBoutonsJeux(false);
            _laVue->affichageFin(_leModele->getScoreJoueur(),  _leModele->getScoreMachine());
        }
        else
        {
            // -- changement d'état --
            _leModele->setEtatJeu(Modele::partieEnCours);
            // -- mise à jour de l'interface --
            _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());
            _laVue->setJoueurEnBleu(false);
            _laVue->focusBJouer();
        }
    }
    else if (_leModele->getEtatJeu() == Modele::partieTerminee)
    {
        // Activite X
        // -- mise a jour du modele --
        // -- changement d'état --
        // -- mise à jour de l'interface --
    }
    else
    {
        // Activite X
        // -- mise a jour du modele --
        // -- changement d'état --
        // -- mise à jour de l'interface --
    }
}


bool Presentation::scoreAtteint()
{
    if ((_leModele->getScoreJoueur() == scoreFin) ||
        (_leModele->getScoreMachine() == scoreFin))
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Presentation::demanderNouvellePartie()
{
    if (_leModele->getEtatJeu() == Modele::horsPartie)
    {
        // Hors partie
        // Activite 1
        // -- mise a jour du modele --
        // -- changement d'état --
        _leModele->setEtatJeu(Modele::partieEnCours);
        // -- mise à jour de l'interface --
        _laVue->setEtatBoutonsJeux(true);
        _laVue->setJoueurEnBleu(true);
        _laVue->focusBJouer();
    }
    else if (_leModele->getEtatJeu() == Modele::partieEnCours)
    {
        // Partie en cours
        // Activite 3
        // -- mise a jour du modele --
        _leModele->initCoups();
        _leModele->initScores();
        // -- changement d'état --
        _leModele->setEtatJeu(Modele::partieEnCours);
        // -- mise à jour de l'interface --
        _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());   //Maj des elements graphiques et coloration en bleu
        _laVue->setJoueurEnBleu(true);
        _laVue->focusBJouer();
    }
    else
    {
        //Partie terminee
        // Activite 5
        // -- mise a jour du modele --
        _leModele->initCoups();
        _leModele->initScores();
        // -- changement d'état --
        _leModele->setEtatJeu(Modele::partieEnCours);
        // -- mise à jour de l'interface --
        _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());   //Maj des elements graphiques et coloration en bleu
        _laVue->setJoueurEnBleu(true);
        _laVue->setEtatBoutonsJeux(true);
        _laVue->focusBJouer();
    }
}
void Presentation::demanderCiseau()
{
    jouer(Modele::ciseau);
}
void Presentation::demanderPierre()
{
    jouer(Modele::pierre);
}
void Presentation::demanderPapier()
{
    jouer(Modele::papier);
}

