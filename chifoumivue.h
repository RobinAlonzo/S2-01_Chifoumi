#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include "modele.h"
#include "presentation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class ChifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    //initialisation
    ChifoumiVue (QWidget *parent = nullptr);        //Constructeur du chifoumiVue
    ~ChifoumiVue ();                                //Destructeur du chifoumiVue
    void conexionPresentation(QObject *);           //Connexion à la présentation
    void deconexionPresentation(QObject *);         //Deconnexion de la présentation

    //Maj des boutons
    void setEtatBoutons(bool);                      //Active/Desactive les boutons de jeux

    //Maj des labels
    void majImageCoupMachine(Modele::UnCoup);       //Met à jour l image du coup de la machine en fonction du coup en parametre
    void majImageCoupJoueur(Modele::UnCoup);        //Met à jour l image du coup du joueur en fonction du coup en parametre
    void majLabelScoreMachine(unsigned int);        //Met à jour le label représentant le score de la machine en fonction du nombre en parametre
    void majLabelScoreJoueur(unsigned int);         //Met à jour le label représentant le score du joueur en fonction du nombre en parametre
    void majScoresCoups(unsigned int, unsigned int, Modele::UnCoup, Modele::UnCoup);    //Met a jour l ensemble des elements graphiques de scores et de coups en fonction des parametres.

    //Autre
    void setJoueurEnBleu(bool); //Met la partie du joueur en bleu ou en noir en fonction du booleen
    void focusBJouer();         //Met le focus sur le bouton de partie

public slots:
    //Slots internes
    void aPropos();             //Affiche une box indiquant la version et les créateurs

private:
    Ui::ChifoumiVue *ui;
};
#endif // CHIFOUMIVUE_H
