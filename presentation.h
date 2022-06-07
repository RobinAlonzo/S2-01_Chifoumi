#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include <QTimer>

#include "modele.h"


class ChifoumiVue;
class Presentation : public QObject
{
    Q_OBJECT
public:    
    //Initialisaitons
    explicit Presentation(Modele* m, QObject* parent = nullptr);

    //Getters / Setters
    Modele* getModele();            //Récupere le modèle
    ChifoumiVue* getVue();          //Récupere la vue
    void setModele(Modele *m);      //Associe le modèle à la présentation
    void conexionVue(ChifoumiVue*); //Lie la vue a la presentation et l'initialise (score de fin)

    //Evenements
    void jouer(Modele::UnCoup);     //Joue en fonction du coup de l utilisateur

    //Gardes
    bool scoreAtteint();            //Indique si la partie est terminée par le score atteint
    bool tempsEpuise();             //Indique si la partie est terminée par le temps (timer = 0)

    void affichageFin();  //Affiche un dialog indiquant le gagnant avec son score et le temps restant

public slots:
    //Slots externes (activés par la vue)
    void demanderNouvellePartie();  //Signal demandant une nouvelle partie
    void demanderCiseau();          //Slot demandant de jouer le ciseau
    void demanderPierre();          //Slot demandant de jouer la pierre
    void demanderPapier();          //Slot demandant de jouer le papier
    void start_stop_timer();        //Slot activé par le bouton pause qui met en pause ou redémarre le timer

    //Slots internes (activés par la presentation) gérant le timer
    void gererTimer();              //Slot activé par la clock qui met a jour les elements en fonction du temps (maj graphique, pause du jeux du le temps utilisé...)

private:
    //Composantes
    Modele *_leModele;          //Le modèle
    ChifoumiVue *_laVue;        //La vue

    //Timer
    QTimer *timer;              //Timer redemarre des que la durée est atteintewq<
    float tempsRestant;         //Temps restant (mis a jour a chaque fois de cycle du timer)
    unsigned int tempsPartie;   //Temps de départ du temps restant

    //Proprietes
    unsigned int scoreFin;  //Score défini a l'avance au bout duquel la partie se termine si un des joueur l'atteint
};

#endif // PRESENTATION_H
