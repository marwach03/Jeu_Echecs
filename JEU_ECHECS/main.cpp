#include <iostream>
#include "Plateau.h"
#include <stdlib.h>
#include "IA.h"
using namespace std;

Plateau p;
IA ai;

void afficherPlateau(Plateau p)
{
	cout<<"__________________________________________________________________"<<endl;

	//cout<<p.getIndice(0,0);
	cout<<"__________________________________________________________________"<<endl;

	cout<<"Colonne: |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7 "<<endl;
	cout<<"__________________________________________________________________"<<endl;
	cout<<"Ligne 0:";
	for(int i=0;i<=7;i++)
	{
		for(int j=0;j<=7;j++)
		{
			//cout<<" | "<<p.getIndice(i,j);
			switch(p.getIndice(i,j))
			{
				case 0: cout<<" |     ";
						break;
				case 1: cout<<" |  KB ";
						break;

				case 2: cout<<" |  QB ";
						break;

				case 3: cout<<" |  FB ";
						break;

				case 4: cout<<" |  CB ";
						break;

				case 5: cout<<" |  TB ";
						break;

				case 6: cout<<" |  PB ";
						break;

				case -1: cout<<" |  KN ";
						break;

				case -2: cout<<" |  QN ";
						break;

				case -3: cout<<" |  FN ";
						break;

				case -4: cout<<" |  CN ";
						break;

				case -5: cout<<" |  TN ";
						break;

				case -6: cout<<" |  PN ";
						break;
			}
		}
		cout<<endl;
		cout<<"__________________________________________________________________"<<endl;
		if(i!=7)cout<<"Ligne "<<i+1<<":";
	}
	cout<<"__________________________________________________________________"<<endl;

}

saisirCoordD(int &i, int &j,int joueur)
{
	do{
		cout<<"Veuillez saisir la ligne de depart : ";
		cin>>i;	
		cout<<"Veuillez saisir la colonne de depart : ";
		cin>>j;
	}while(i < 0 || i > 7 || j < 0 || j > 7);
	
	if ((joueur % 2 == 1 && p.getIndice(i, j) < 0) || (joueur % 2 == 0 && p.getIndice(i, j) > 0))
    {
        cout << "Erreur :Ce sont pas tes pieces" << endl;
    }

}

saisirCoordA(int &i,int &j)
{
	do{
		cout<<"Veuillez saisir la ligne d'arrivee: ";
		cin>>i;
	}while((i>7)||(i<0));
	do{
		cout<<"Veuillez saisir la colonne d'arrivee: ";
		cin>>j;
	}while((j>7)||(j<0));
}

void deplacerpiece(Plateau &p, int joueur)
{
	int ld, cd, la, ca;
	
	do
    {
        saisirCoordD(ld, cd, joueur);
    } while ((joueur % 2 == 1 && p.getIndice(ld, cd) < 0) || (joueur % 2 == 0 && p.getIndice(ld, cd) > 0));

	do{
		saisirCoordA(la,ca);
	}while((p.getIndice(la,ca)<0 && p.getIndice(ld,cd)<0) || (p.getIndice(la,ca)>0 && p.getIndice(ld,cd)>0));
	
	int x = p.deroulement(ld, cd, la, ca);
	
	if(x==0) 
	{
		cout<<"Deplacement impossible"<<endl;
	}
	else if(x==1)
	{
		if ((p.getIndice(la, ca) == 6 && la == 0) || (p.getIndice(la, ca) == -6 && la == 7)) 
		{
    		p.Promotion(ld, cd, la, ca);
		}
		else if ((p.getIndice(ld, cd) == -1 && la == 0))
		{
    		p.RoockNoir(ld, cd, la, ca);
		}
		else if ((p.getIndice(ld, cd) == 1 && la == 7)) 
		{
    		p.RoockBlanc(ld, cd, la, ca);
		}
		
		if (p.getIndice(ld, cd) == 6 && p.getIndice(la, ca) == 0 && la == ld - 1 && (ca - cd == 1 || ca - cd == -1)) 
        {
            p.PriseEnPassant(ld, cd, la, ca);
        }
        else if (p.getIndice(ld, cd) == -6 && p.getIndice(la, ca) == 0 && la == ld + 1 && (ca - cd == 1 || ca - cd == -1)) 
        {
            p.PriseEnPassant(ld, cd, la, ca);
        }
        if (p.RoiB())
    	{
        	cout << "Le roi blanc est en echec !" << endl;
    	}
    	if (p.RoiN())
    	{
        	cout << "Le roi noir est en echec !" << endl;
    	}
		else if(p.Null())
		{
			cout<<"LA PARTIE EST NULL !"<<endl;
		}
		else if(p.Mate())
		{
			cout<<"ECHEC ET MATE !"<<endl;
		}
		
		cout<<"Deplacement reussi"<<endl;
	}
}

int main()
{
    int ld, cd, la, ca;
    int joueur=0;
    int choix;
    

    
    //p.Save(joueur);
    
    cout<<endl;
    cout<<"   -------   --------  --      --    ----------       --   --------    --------    -         -    --------    --------"<<endl;
	cout<<"  --------  ---------  --      --    -----------      --  ---------   ---------    -         -   ---------   ---------"<<endl;
	cout<<"        --  --         --      --    --        --     --  --          --           -         -   --          --       "<<endl;
	cout<<"        --  --         --      --    --          --    -  --          --           -         -   --          --       "<<endl;
	cout<<"        --  --         --      --    --           --   -  --          --           -         -   --          --       "<<endl;
	cout<<"        --  --         --      --    --           --   -  --          --           -         -   --          --       "<<endl;
	cout<<"        --  ---------  --      --    --           --  -   ---------   --           -----------   ---------   --       "<<endl;
	cout<<"        --  ---------  --      --    --           --      ---------   --           -----------   ---------   --       "<<endl;
	cout<<"        --  --         --      --    --          --       --          --           -         -   --          --       "<<endl;
	cout<<"  --   ---  --         --      --    --         --        --          --           -         -   --          --       "<<endl;
	cout<<"  --  ----  --         --      --    --        --         --          --           -         -   --          --       "<<endl;
	cout<<"  -------   ---------  ----------    -----------          ---------   ---------    -         -   ---------   ---------"<<endl;
	cout<<"   -----     --------   --------     ----------            --------    --------    -         -    --------    --------"<<endl<<endl;
    
    int choixT;
    
    cout<<"Veuiller choisir : \n 1-HUMAIN VS HUMAIN  !\n 2-HUMAIN VS MACHINE !\n "<<endl;
    cout<<"VEUILLEZ SAISIR VOTRE CHOIX : (1-2) : ";
    cin>>choixT;
    
    switch(choixT)
    {
    	case 1:
    		cout<<"Veuiller choisir : \n 1-Jouer une nouvelle partie !\n 2-Continuer la partie precedente !\n "<<endl;
		    cout<<"VEUILLEZ SAISIR VOTRE CHOIX : (1-2) : ";
		    cin>>choix;
		    
		    switch(choix)
		    {
		    	case 1:
		    		afficherPlateau(p);
				    /*cout << "Player 1 : BLANC" << endl;
				    deplacerpiece(p, joueur);
				    afficherPlateau(p);*/
				    do {
		    		    joueur++;
		    		    p.Save(joueur);
				        if (joueur % 2 == 0) 
						{
		            		cout << "Player 2 : NOIR" << endl;
			            	deplacerpiece(p,joueur);
		    	    	} 
						else 
						{
		            		cout << "Player 1 : BLANC" << endl;
		            		deplacerpiece(p,joueur);
		        		}
		        		afficherPlateau(p);
		        		p.Save(joueur);
		    		} while(p.Finpartie() == false);
		    		break;
		    		
		    	case 2:
		    		p.Load(joueur);
				    afficherPlateau(p);
		    		/*cout << "Player 1 : BLANC" << endl;
		    		deplacerpiece(p, joueur);
		    		afficherPlateau(p);*/
		    		do {
		        		joueur++;
		        		p.Save(joueur);
		    	    	if (joueur % 2 == 0) 
						{
		            		cout << "Player 2 : NOIR" << endl;
		        	    	deplacerpiece(p,joueur);
		        		}	 
						else 
						{
		            		cout << "Player 1 : BLANC" << endl;
		            		deplacerpiece(p,joueur);
		        		}
		        		afficherPlateau(p);
		        		p.Save(joueur);
		    		} while (p.Finpartie() == false);
		    		
		    	default:
		    		break;
			}
		break;
		
		case 2:
            afficherPlateau(p);

            do {
                joueur++;

                if (joueur % 2 == 0) {
                    cout << "Player 2 : NOIR" << endl;
                    ai.jouerCoup(p, joueur);  // Appel de la méthode jouerCoup de l'IA
                    //afficherPlateau(p);
                } else {
                    cout << "Player 1 : BLANC" << endl;
                    deplacerpiece(p, joueur);
                }

                //afficherPlateau(p);
            } while (p.Finpartie() == false);

            break;
	}
    
    
	
    return 0;
}
