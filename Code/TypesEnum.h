#ifndef TYPESENUM_H
#define TYPESENUM_H
<<<<<<< HEAD

enum class Type {
    agriculture,
    elevage,
    ressources,
    maritime,
    commerce,
    industrie,
    maraichage,
    entreprise,
    restauration,
    special,
}
=======
#include<string>
#include "exception.h"
using namespace std;
>>>>>>> 3843fe0ccd43655656d799e059e79e98ad6b8a9a

enum class Extension {
    Aucune,
    Marina,
    GreenValley,
    Deluxe
};

enum Type{agriculture,magasin,restauration,rouage};
string toString(Type t) {
		switch (t) {
		case Type::agriculture: return "agriculture";
		case Type::magasin: return "magasin";
		case Type::restauration: return "restauration";
		case Type::rouage: return "rouage";
		default: throw SetException("Type inconnu");
		}
	}
enum Couleur{bleu,rouge,violet,vert};
string toString(Couleur c) {
		switch (c) {
		case Couleur::bleu: return "bleu";
		case Couleur::rouge: return "rouge";
		case Couleur::violet: return "violet";
		case Couleur::vert: return "vert";
		default: throw SetException("Couleur inconnue");
		}
	}


#endif