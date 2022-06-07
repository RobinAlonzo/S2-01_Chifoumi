#include "presentation.h"
#include "chifoumivue.h"
#include "QDebug"
#include <QMessageBox>

Presentation::Presentation(Modele *m, QObject *parent)
    : QObject{parent}, _leModele(m)
{
    timer = new QTimer(this);

    //Initialisation score max
    scoreFin = 3;

    //initialisation timer
    tempsPartie = 20;
    tempsRestant = tempsPartie;
    connect(timer, SIGNAL(timeout()), this, SLOT(gererTimer()));
    timer->setInterval(100);
}
void Presentation::conexionVue(ChifoumiVue *v)
{
    //Conexion a la vue
    _laVue = v;

    //Initialisations score final et temps de depart
    _laVue->initScoreFin(scoreFin);
    _laVue->majTimer(tempsRestant);
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
            // -- mise a jour du modele --
            timer->stop();
            // -- changement d'état --
            _leModele->setEtatJeu(Modele::partieTerminee);
            // -- mise à jour de l'interface --
            _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());
            _laVue->setJoueurEnBleu(false);
            _laVue->setFocusBJouer();

            _laVue->setEtatsBJeu(false);
            _laVue->setEtatBPause(false);
            affichageFin();
        }
        else
        {
            //Score non atteint
            // -- mise a jour du modele --
            // -- changement d'état --
            _leModele->setEtatJeu(Modele::partieEnCours);
            // -- mise à jour de l'interface --
            _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());
            _laVue->setJoueurEnBleu(false);
            _laVue->setFocusBJouer();
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
bool Presentation::tempsEpuise()
{
    if (tempsRestant <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Presentation::affichageFin()
{
    unsigned int scoreJoueur =_leModele->getScoreJoueur();
    unsigned int scoreMachine =_leModele->getScoreMachine();

    // -- Maj de l interface --
    QMessageBox boiteFin(_laVue);
    boiteFin.setWindowTitle("Game over");
    QString messageFin;

    //Gestion du temps final
    if (tempsRestant <= 0)
    {
        //Temps ecoule
        messageFin.append("Temps ecoulé :");
    }
    else
    {
        //Temps non ecoule
        messageFin.append("Au bout de " + QString::number(static_cast<float>(static_cast<unsigned int>((tempsPartie - tempsRestant)*10))/10) + " seconde :");
    }

    //Gestion des scores finaux
    if (scoreJoueur > scoreMachine)
    {
        //Joueur gagne
        messageFin.append(" joueur gagne avec " + QString::number(scoreJoueur) + " points.");
    }
    else if (scoreJoueur < scoreMachine)
    {
        //Machine gagne
        messageFin.append(" machine gagne avec " + QString::number(scoreMachine) + " points.");
    }
    else
    {
        //Aucun gagnant (scores egaux)
        messageFin.append(" aucun gagnant.");
    }

    boiteFin.setText(messageFin);
    boiteFin.exec();
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
        timer->start();
        // -- mise à jour de l'interface --
        _laVue->setEtatsBJeu(true);
        _laVue->setFocusBJouer();
        _laVue->setJoueurEnBleu(true);
        _laVue->setEtatBPause(true);
    }
    else if (_leModele->getEtatJeu() == Modele::partieEnCours)
    {
        // Partie en cours
        // Activite 3
        // -- mise a jour du modele --
        _leModele->initCoups();
        _leModele->initScores();
        tempsRestant = tempsPartie;
        // -- changement d'état --
        _leModele->setEtatJeu(Modele::partieEnCours);
        timer->start();
        // -- mise à jour de l'interface --
        _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());   //Maj des elements graphiques et coloration en bleu
        _laVue->setJoueurEnBleu(true);
        _laVue->setFocusBJouer();
    }
    else
    {
        //Partie terminee
        // Activite 4
        // -- mise a jour du modele --
        _leModele->initCoups();
        _leModele->initScores();
        tempsRestant = tempsPartie;
        // -- changement d'état --
        _leModele->setEtatJeu(Modele::partieEnCours);
        timer->start();
        // -- mise à jour de l'interface --
        _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());   //Maj des elements graphiques et coloration en bleu
        _laVue->setJoueurEnBleu(true);
        _laVue->setEtatsBJeu(true);
        _laVue->setFocusBJouer();
        _laVue->setEtatBPause(true);
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


void Presentation::gererTimer()
{
    if (_leModele->getEtatJeu() == Modele::partieEnCours)
    {
        // Activite 5
        // -- mise a jour du modele --
        tempsRestant -= 0.1 ;
        // -- mise à jour de l'interface --
        _laVue->majTimer(tempsRestant+1);       //+1 pour que le temps se decremente sur l'interface seulement lorsque la seconde est entierement ecoulée

        if (tempsEpuise())
        {
            // -- mise a jour du modele --
            timer->stop();
            // -- changement d'état --
            _leModele->setEtatJeu(Modele::partieTerminee);
            // -- mise à jour de l'interface --
            _laVue->setEtatsBJeu(false);
            _laVue->setEtatBPause(false);
            affichageFin();
        }
    }
}
void Presentation::start_stop_timer()
{
    if (timer->isActive())
    {
        //Arrete le timer
        timer->stop();                          //Stop le timer
        _laVue->setEtatsBJeu(false);            //Desactive les boutons pour jouer
        _laVue->setEtatBPartie(false);          //Desactive le bouton pour recommencer une partie
        _laVue->majLabelBPause("Reprendre");    //Change le nom du bouton en "reprendre"
        _laVue->setFocusBPause();               //Met le focus sur le bouton de pause
    }
    else
    {
        //Redemarre le timer
        timer->start();                         //Démarre le timer
        _laVue->setEtatsBJeu(true);             //Re active les boutons de jeux
        _laVue->setEtatBPartie(true);           //Re active le bouton de partie
        _laVue->majLabelBPause("Pause");        //Change le nom du bouton en "Pause"
        _laVue->setFocusBJouer();               //Met le focus sur le bouton de partie
    }
}

