#ifndef JOUEUR_H
#define JOUEUR_H

#include <string.h>
#include <random>

#include "Main.h"

class Joueur{
    int id;
    string pseudo;
    int de=1;
    int de_lance;
    int compte=3;
    int placement_StartUp=0;
    static const int max_joueurs = 4;
    static const int min_joueurs = 2;
    Monument* monuments[nb_monuments];
    friend Partie;

public:
    Joueur();
    ~Joueur();
    
    //Getter
    int getNbDes() const;
    int getCompte() const;
    int getPlacement_StartUp() const;
    static int getNbMaxJoueurs();
    static int getNbMaxJoueurs();
    
    //Setter
    void setPseudo(string pseudo);
    void setPlacement_StartUp(int placement_StartUp);
    void setNbDes(int nbDe);
    void setCompte(int montant);
    
    //Autres méthodes
    void ajouterMontant(int montant);
    bool victoire();
    int lancerDés();
};

#endif
