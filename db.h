#ifndef DB_H
#define DB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QList>

#define CONNECT_TYPE "QODBC"
#define DB_NAME "ndelahaie_bd"

class Db : public QObject
{
    Q_OBJECT
public:
    explicit Db(QObject *parent = nullptr);

    void insererResultat(QString nomJoueur, unsigned int scoreJoueur, unsigned int scoreMachine);          //Permet d'inserer les résultats en fin de partie dans la BDD

public slots:
    unsigned short int analyseIdentifiants(QString id, QString mdp);    //Retourne 0 si les identifiants sont justes, 1 si l' identifiant est faux, 2 si le mdp est faux, 3 si la base de donnee ne s est pas ouverte
    void getScores(QList<QString> &nomJoueur, QList<QString> &scoreJoueur, QList<QString> &nomMachine, QList<QString> &scoreMachine);                                             //Retourne l enregistrement des scores

private:
    QSqlDatabase db;

};

#endif // DB_H
