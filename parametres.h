#ifndef PARAMETRES_H
#define PARAMETRES_H

#include "presentation.h"

#include <QDialog>

namespace Ui {class Param;}

class Param : public QDialog
{
    Q_OBJECT

public:
    explicit Param(QWidget *parent = nullptr);
    ~Param();
    void connexionPresentation(Presentation *, QString nomJoueur, unsigned int scoreFin, unsigned int tempsPartie);                                      //Connexion à la présentation
    void deconnexionPresentation(Presentation *);                                    //Deconnexion de la présentation
    void afficherDialog();

    QString getNom() const;
    unsigned int getScore() const;
    unsigned int getTemps() const;

    bool nomModifie() const;            //Renvoie un boolean
    bool scoreFinModifie() const;       //Renvoie un boolean
    bool tempsPartieModifie() const;    //Renvoie un boolean

private slots:
    void param1modifie();               //SLOT permettant de modifier l'etat de _nomModifie
    void param2modifie();               //SLOT permettant de modifier létat de _pointsModifies
    void param3modifie();               //SLOT permettant de modifier l'état de _tempsModifie


private:
    Ui::Param *ui;

    bool _nomModifie;                   //Permet de voir si le nom a était modifié
    bool _pointsModifies;               //Permet de voir si les points ont était modifié
    bool _tempsModifie;                 //Permet de voir si le temps à était modifié

};

#endif // PARAMETRES_H
