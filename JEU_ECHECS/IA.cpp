#include "IA.h"
#include <iostream>
#include <cstdlib> // Include the <cstdlib> header for 'rand'
using namespace std;

void IA::jouerCoup(Plateau& plateau, int joueur) {
    // Logique pour déterminer le meilleur coup pour le joueur IA
    // et mettre à jour l'échiquier en conséquence en utilisant les méthodes fournies par la classe Plateau

    // Déplacement de (1, 6) à (3, 6)
    int ld = 1; // ligne de départ
    int cd = 2; // colonne de départ
    int la = 3; // ligne d'arrivée
    int ca = 2; // colonne d'arrivée

    // Déplacer la pièce sur l'échiquier
    int x = plateau.deroulement(ld, cd, la, ca);

    if (x == 0) {
        cout << "Déplacement impossible" << endl;
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
            cout << "Le roi blanc est en échec !" << endl;
        }
        if (plateau.RoiN())
        {
            cout << "Le roi noir est en échec !" << endl;
        }
        else if(plateau.Null())
        {
            cout << "LA PARTIE EST NULLE !" << endl;
        }
        else if(plateau.Mate())
        {
            cout << "ÉCHEC ET MAT !" << endl;
        }
        
        cout << "Déplacement réussi" << endl;
    }
    
    // Afficher l'échiquier mis à jour
    plateau.afficherPlateau();
}

