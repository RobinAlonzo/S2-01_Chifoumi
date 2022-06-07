#include "presentation.h"
#include "chifoumivue.h"
#include "modele.h"
#include "parametres.h"
#include "db.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Modele *modele = new Modele();                                  //Creation du modèle
    ChifoumiVue *vue = new ChifoumiVue;                             //Creation de la vue
    Param *param = new Param(vue);                                  //Creation du la page de parametres, fils de la vue
    Db *db = new Db(vue);                                           //Creation de la page d identification, fils de la vue

    Presentation *p = new Presentation(modele, vue, param, db);     //Creation de la présentation et son association au modèle

    return a.exec();
}
