#include "pioche.h"
#include "time.h"
//Getters
unsigned int Pioche::getNb_etablissements() const {return nb_etablissements;}
unsigned int Pioche::getNb_piles()const {return nb_piles;}
Pile_Etablissement* Pioche::getPiles_etablissement()const {return piles_etablissement;}

//Constructeur et destructeur
Pioche:: Pioche(const Jeu& jeu) {
    nb_piles = jeu.getNbEtablissements();
    nb_etablissements=0;
    piles_etablissement= new Pile_Etablissement [nb_piles];
    for (unsigned int i = 0; i < nb_piles; i++) {
      piles_etablissement[i]= Pile_Etablissement(jeu.getEtablissements()[i], jeu.getEtablissements()[i]->getNbExemplaires());
      nb_etablissements+=jeu.getEtablissements()[i]->getNbExemplaires();
      //nb_etablissements;
      //piles_etablissement[i] = p;//VARIABLE LOCALE
      //cout<<*piles_etablissement[i];
    }
  }

Pioche::~Pioche(){delete[]piles_etablissement;}

//Autres methodes de classe
const Etablissement& Pioche::getRandomEtablissement() const {
    srand(time(NULL));
    cout<<"nb et "<<nb_etablissements<<endl;
    unsigned int numero_etablissement = rand() % nb_etablissements;
    cout<<"num random : "<<numero_etablissement;//c'est toujours 41 lol
    unsigned int nb_etablissements_parcourus = 0;
    unsigned int i = 0;
    while (nb_etablissements_parcourus < numero_etablissement) {
      nb_etablissements_parcourus += piles_etablissement[i].getEffectif();
      i++;
    }
    return *piles_etablissement[i].getEtablissement();
  }

unsigned int Pioche::getIndexPile(const Etablissement& etablissement)const {
unsigned int i=0;
while (i<nb_piles && *piles_etablissement[i].getEtablissement() != etablissement)i++;
if (*piles_etablissement[i].getEtablissement() != etablissement) SetException("l'etablissement n'est pas dans la pioche");
return i;
}

void Pioche::retirer_Etablissement(const Etablissement& etablissement, unsigned int quantite){
unsigned int indexPile = getIndexPile(etablissement);
piles_etablissement[indexPile].retirerCarte(quantite);
cout<<"nb et "<<nb_etablissements<<endl;
nb_etablissements-=quantite;
if (piles_etablissement[indexPile].getEffectif()==0){
    for (unsigned int i=indexPile; i<nb_piles;i++) piles_etablissement[i]=piles_etablissement[i+1];
    nb_piles--;
}
}//pourrait aussi etre realise avec la librairie <array>

void Pioche::afficher()const{
cout<<"******Pioche******"<<endl<<endl;
for (unsigned int i = 0; i < nb_piles; i++) cout<<piles_etablissement[i];
cout<<"******EndPioche******"<<endl<<endl;
}
//FONCTION DE TEST
int testPioche(){

//EtablissementTest();
Jeu jeu1 = Jeu();
//CONSTRUIRE LA PIOCHE
Pioche pioche1 = Pioche(jeu1);
pioche1.afficher();

//PIOCHER UN ETABLISSEMENT
/*cout<<"Etablissement pioche au hasard : "<<endl;
pioche1.getRandomEtablissement().afficher();*/

//RETIRER UN ETABLISSEMENT
/*const Etablissement& e1 = *pioche1.piles_etablissement[14].getEtablissement();
cout<<"Etablissement a retirer : "<<endl;
cout<<e1;
try{
    pioche1.retirer_Etablissement(e1,9);
}catch(const SetException e){
    cout<<e.getInfo();
}
cout<<"Nouvelle pioche : "<<endl;
pioche1.afficher();
*/
return 0;
}

