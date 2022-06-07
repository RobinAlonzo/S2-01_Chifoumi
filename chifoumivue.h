#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include "chifoumi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class ChifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    ChifoumiVue (QWidget *parent = nullptr);
    ~ChifoumiVue ();

    enum UnEtat {horsPartie, partieEnCours};

    UnEtat getEtatJeu();
    void setEtatJeu(UnEtat);
    Chifoumi* getModele();
    void setModele(Chifoumi*);

    void majImageCoupMachine();
    void majImageCoupJoueur();
    void majLabelScoreMachine();
    void majLabelScoreJoueur();

    void jouer(Chifoumi::UnCoup);

public slots:
    void pierre();
    void ciseau();
    void papier();
    void nouvellePartie();


private:
    Ui::ChifoumiVue *ui;
    UnEtat etatJeu;
    Chifoumi *modele;

};
#endif // CHIFOUMIVUE_H
