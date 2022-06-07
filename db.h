#ifndef DB_H
#define DB_H

#include <QDialog>
#include <QSqlDatabase>

#include "presentation.h"

#define CONNECT_TYPE "QODBC"
#define DB_NAME "BDD_NDELAHAIE_BD"

namespace Ui {class Db;}

class Db : public QDialog
{
    Q_OBJECT

public:
    explicit Db(QWidget *parent = nullptr);
    ~Db();
    void conexionPresentation(Presentation *p);

private slots:
    void analyseIdentifiants();                 //En fonction des identifiatns juste ou faux : affiche un message d'erreur ou ouvre la page principale

signals:
    void idJustes();                            //Signal qui ferme la fentre pour afficher le jeux

private:
    Ui::Db *ui;
    QSqlDatabase db;
};

#endif // DB_H
