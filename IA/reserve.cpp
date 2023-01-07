#include "reserve.h"

// Getters
unsigned int Reserve::getNbPile() const
{
    return nb_piles;
}
unsigned int Reserve::getNbPileMax() const
{
    return nb_piles_max;
}

unsigned int Reserve::getNbEtablissements() const
{
    return nb_etablissements;
}
Pile_Etablissement** Reserve::getListeEtablissement() const
{
    return liste_etablissements;
}

// Constructors and Destructors
Reserve::Reserve(Jeu& j)
{
    // Proposition d'amelioration : tableau de string ordre_reserve stocke dans jeu
    nb_piles_max = j.getNb_pile_reserve_MAX();
    auto etablissements = j.getEtablissements();
    liste_etablissements = new Pile_Etablissement*[nb_piles_max];
    for (unsigned int i = 0; i < nb_piles_max; i++) {
        liste_etablissements[i] = new Pile_Etablissement(etablissements[i], etablissements[i]->getNbExemplaires());
        nb_piles++;
        // ajouter_etablissement(*j.getEtablissementFromName(ordre_reserve[i]),j.getEtablissementFromName(ordre_reserve[i])->getNbExemplaires());
        // ajouter_etablissement(*etablissements[i],etablissements[i]->getNbExemplaires());
    }
}

Reserve::Reserve(Jeu& j, Pioche& p)
{
    //nb_piles_max = j.getNb_pile_reserve_MAX();
    nb_piles_max = 10;
    nb_etablissements=0;
    nb_piles = 0;
    liste_etablissements = new Pile_Etablissement*[nb_piles_max];
    for (unsigned int i = 0; i < nb_piles_max; i++)
        liste_etablissements[i] = new Pile_Etablissement;
    while (nb_piles < nb_piles_max) {
       const Etablissement* e = p.retirerRandomEtablissement();
        ajouter_etablissement(e);
    }
};
Reserve::~Reserve()
{
    for (unsigned int i = 0; i < nb_piles_max; i++)
        delete liste_etablissements[i];
    delete liste_etablissements;
};

// Methodes de classe
void Reserve::ajouter_etablissement(const Etablissement* etablissement,unsigned int quantite)
{
    unsigned int i = 0;
    while (i < nb_piles && etablissement != liste_etablissements[i]->getEtablissement()) {
        i++;
    }
    if (liste_etablissements[i] && liste_etablissements[i]->getEtablissement() && etablissement == liste_etablissements[i]->getEtablissement()) {
        liste_etablissements[i]->ajouterCarte(quantite);
        nb_etablissements += quantite;
    } else {
        if (i < nb_piles_max) {
            liste_etablissements[i] = new Pile_Etablissement(etablissement, quantite);
            nb_etablissements += quantite;
            nb_piles++;
        } else {
            SetException("la reserve est complete");
        }
    }
}

void Reserve::retirer_etablissement(const Etablissement* etablissement, Pioche& p,  unsigned int quantite)
{
    unsigned int indexPile = 0;
    while (indexPile < nb_piles && etablissement != liste_etablissements[indexPile]->getEtablissement()) {
        indexPile++;
    }
    if (liste_etablissements[indexPile]->getEtablissement() && *etablissement == *liste_etablissements[indexPile]->getEtablissement()) {
        liste_etablissements[indexPile]->retirerCarte(quantite);
        nb_etablissements -= quantite;
        // Si la pile est désormais vide
        if (liste_etablissements[indexPile]->getEffectif() == 0) {
            //on la supprime
            Pile_Etablissement* old = liste_etablissements[indexPile];
            for (unsigned int i = indexPile; i < nb_piles - 1; i++)
                {liste_etablissements[i] = liste_etablissements[i + 1];}
            liste_etablissements[nb_piles-1]=nullptr;
            delete old;
            nb_piles--;
            while (nb_piles < nb_piles_max) {
        const Etablissement* e = p.getRandomEtablissement();
        this->ajouter_etablissement(e);
    }
       // }
    } else {
        SetException("l'etablissement n'est pas dans la reserve");
    }
}
}

void Reserve::afficher()const
{ // Fomatage, pas parfait
    cout << "******Reserve******" << endl
         << endl;
    for (unsigned int i = 0; i < nb_piles; i++) {
        cout << "\t" << i + 1;
        if (i < 9)
            cout << " ";
        cout.width(40);
        cout << liste_etablissements[i]->getEtablissement()->getNom() << " (" << liste_etablissements[i]->getEffectif() << ")";
        cout.width(20);
        if (liste_etablissements[i]->getEffectif() != 0) cout << "Prix : " << liste_etablissements[i]->getPrix(); cout << " " << endl;
    }
    cout << "*****End*Reserve*****" << endl
         << endl;
}

// Autres methodes
ostream& operator<<(ostream& f, Reserve& carte)
{
    f << "" << endl;
    return f;
}

void testReserve()
{
    Jeu& j = Jeu::getInstance(Extension::Marina);
    Pioche p = Pioche(j);
    //p.afficher();
    // Reserve r = Reserve(j);
    // r.afficher();
    // r.retirer_etablissement(*j.getEtablissementFromName("Champs de ble"),4);
    // r.retirer_etablissement(*j.getEtablissementFromName("Verger"),6);
    // r.ajouter_etablissement(*j.getEtablissementFromName("Verger"),6);
    // r.afficher();
    Reserve* r = new Reserve(j, p);
    r->afficher();
    //p.afficher();
    //delete r;
}
