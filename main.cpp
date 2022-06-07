#include "presentation.h"
#include "chifoumivue.h"
#include "modele.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Modele *m = new Modele();               //Creation du modèle
    Presentation *p = new Presentation(m);  //Creation de la présentation et son association au modèle
    ChifoumiVue v;                          //Creation de la vue
    p->conexionVue(&v);                     //Association de la vue à la présentation
    v.conexionPresentation(p);              //Connexion des signaux de la vue avec les slots de la présentation

    v.show();
    return a.exec();
}
