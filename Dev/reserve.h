#ifndef __RESERVE_H__
#define __RESERVE_H__

#include "etablissement.h"
#include "jeu.h"
#include "miniville.h"
#include "pile_etablissement.h"
#include "pioche.h"

class Reserve {
    unsigned int nb_etablissements;
    unsigned int nb_piles = 0;
    unsigned int nb_piles_max;
    Pile_Etablissement** liste_etablissements;

public:
    // Getters
    unsigned int getNbPile() const;
    unsigned int getNbEtablissements() const;
    unsigned int getNbPileMax() const;

    Pile_Etablissement** getListeEtablissement() const;

    // Constructors and Destructors
    
    // Constructeur pour les extensions
    Reserve(Jeu& j, Pioche& p);
    // constructeur pour le jeu de base
    Reserve(Jeu& j);
    ~Reserve();

    // Methods
    void retirer_etablissement(const Etablissement& etablissement, unsigned int quantite = 1);
    void ajouter_etablissement(const Etablissement& etablissement, unsigned int quantite = 1);
    void afficher() const;


    class Iterator{
    private:
        int count=0;
        int nombre;
        Pile_Etablissement** liste;
        Iterator(Reserve* reserve):liste(reserve->liste_etablissements), nombre(reserve->nb_piles){}
        friend class Reserve;
    public:
        ~Iterator() = default;
        void next(){count++;}
        bool contiditon(){return count<nombre?true:false;}
        Pile_Etablissement* operator*(){return liste[count];}
    };
    Iterator get_Iterator(){return Iterator(this);}


};

ostream& operator<<(ostream& f, Reserve& carte);

void testReserve();

#endif
