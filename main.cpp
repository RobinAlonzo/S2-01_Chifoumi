#include "presentation.h"
#include "chifoumivue.h"
#include "modele.h"
#include "parametres.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Modele *m = new Modele();               //Creation du modèle
    ChifoumiVue *v = new ChifoumiVue;       //Creation de la vue
    Param *d = new Param(v);                //Creation du la page de parametres qui a pour parent la vue

    Presentation *p = new Presentation(m, v, d);  //Creation de la présentation et son association au modèle

    return a.exec();
}
