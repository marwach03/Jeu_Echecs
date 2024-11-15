#include "IA.h"
#include <iostream>
#include <cstdlib> // Include the <cstdlib> header for 'rand'
using namespace std;

void IA::jouerCoup(Plateau& plateau, int joueur) {
    // Logique pour d�terminer le meilleur coup pour le joueur IA
    // et mettre � jour l'�chiquier en cons�quence en utilisant les m�thodes fournies par la classe Plateau

    // D�placement de (1, 6) � (3, 6)
    int ld = 1; // ligne de d�part
    int cd = 2; // colonne de d�part
    int la = 3; // ligne d'arriv�e
    int ca = 2; // colonne d'arriv�e

    // D�placer la pi�ce sur l'�chiquier
    int x = plateau.deroulement(ld, cd, la, ca);

    if (x == 0) {
        cout << "D�placement impossible" << endl;
    } else if (x == 1) {
        if ((plateau.getIndice(la, ca) == 6 && la == 0) || (plateau.getIndice(la, ca) == -6 && la == 7)) 
        {
            plateau.Promotion(ld, cd, la, ca);
        }
        else if ((plateau.getIndice(ld, cd) == -1 && la == 0))
        {
            plateau.RoockNoir(ld, cd, la, ca);
        }
        else if ((plateau.getIndice(ld, cd) == 1 && la == 7)) 
        {
            plateau.RoockBlanc(ld, cd, la, ca);
        }
        
        if (plateau.getIndice(ld, cd) == 6 && plateau.getIndice(la, ca) == 0 && la == ld - 1 && (ca - cd == 1 || ca - cd == -1)) 
        {
            plateau.PriseEnPassant(ld, cd, la, ca);
        }
        else if (plateau.getIndice(ld, cd) == -6 && plateau.getIndice(la, ca) == 0 && la == ld + 1 && (ca - cd == 1 || ca - cd == -1)) 
        {
            plateau.PriseEnPassant(ld, cd, la, ca);
        }
        if (plateau.RoiB())
        {
            cout << "Le roi blanc est en �chec !" << endl;
        }
        if (plateau.RoiN())
        {
            cout << "Le roi noir est en �chec !" << endl;
        }
        else if(plateau.Null())
        {
            cout << "LA PARTIE EST NULLE !" << endl;
        }
        else if(plateau.Mate())
        {
            cout << "�CHEC ET MAT !" << endl;
        }
        
        cout << "D�placement r�ussi" << endl;
    }
    
    // Afficher l'�chiquier mis � jour
    plateau.afficherPlateau();
}

