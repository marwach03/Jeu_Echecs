#include <iostream>
#include <fstream>
#include "Plateau.h"
using namespace std;

Plateau::Plateau()
{
	for(int i=2;i<=5;i++)
	{
		for(int j=0;j<=7;j++)
		{
			t[i][j]=0;
		}
	}
	for(int j=0;j<=7;j++)
	{
		t[1][j]=-6;
	}	
	for(int j=0;j<=7;j++)
	{
		t[6][j]=6;
	}	
	//noir
	t[0][0]=-5;//tour
	t[0][1]=-4;//cavalier
	t[0][2]=-3;//fou
	t[0][3]=-2;//dame
	t[0][4]=-1;//roi
	t[0][5]=-3;//fou
	t[0][6]=-4;//cavalier
	t[0][7]=-5;//tour	
	//blanc
	t[7][0]=5;//tour
	t[7][1]=4;//cavalier
	t[7][2]=3;//fou
	t[7][3]=2;//dame
	t[7][4]=1;//roi
	t[7][5]=3;//fou
	t[7][6]=4;//cavalier
	t[7][7]=5;//tour
}
////////////////////////////////////////////////////////////////
Plateau::~Plateau()
{
	
}

/////////////////////////////
int Plateau::nbPiecesIA() {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (t[i][j] > 0) {
                count++;
            }
        }
    }
    return count;
}

int Plateau::nbPiecesAdversaire() {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (t[i][j] < 0) {
                count++;
            }
        }
    }
    return count;
}


////////////////////////////////////
void Plateau::afficherPlateau()
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
			switch(getIndice(i,j))
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

//////////////////////////////////////////////////////
int Plateau::getIndice(int i,int j)
{
	return t[i][j];
}
///////////////////////////////////////////////////////////
int Plateau::finpartie()
{
	return 1;
}
////////////////////////////////////////////////////////////////////////////////////
int Plateau::firstmoveB(int ld,int cd,int la,int ca)
{
	if(t[ld][cd]==6 && ld==6)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
///////////////////////////////////////////////////////////////////////////////////////
int Plateau::firstmoveN(int ld,int cd,int la,int ca)
{
	if(t[ld][cd]==-6 && ld==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
int Plateau::movpion(int ld,int cd,int la,int ca)
{
	if(t[ld][cd]==-6)//noir
	{
		if(firstmoveN(ld,cd,la,ca))
		{
			if((la==ld+1)&&(cd==ca))
			{
				t[la][ca]=t[ld][cd];
				t[ld][cd]=0;
				return 1;			
			}
			if((la==ld+2)&&(cd==ca))
			{
				t[la][ca]=t[ld][cd];
				t[ld][cd]=0;
				return 1;
			}
		}
		else
		{
			if((ld+1==la)&&(cd==ca))
			{
				t[la][ca]=t[ld][cd];
				t[ld][cd]=0;
				return 1;			
			}
			else if (((ld + 1 == la) && (cd + 1 == ca)) || ((ld + 1 == la) && (cd - 1 == ca))) // diagonal attack
			{
				if (t[la][ca] > 0) // capture opponent piece
				{
					t[la][ca] = t[ld][cd];
					t[ld][cd] = 0;
					return 1;
				}
				else // illegal move
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	else if(t[ld][cd]==6)//blanc
	{
		if(firstmoveB(ld,cd,la,ca))
		{
			if(((ld-1==la)&&(cd==ca)) || ((ld-2==la)&&(cd==ca)))
			{
				t[la][ca]=t[ld][cd];
				t[ld][cd]=0;
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else 
		{
			if((ld-1==la)&&(cd==ca))
			{
				t[la][ca]=t[ld][cd];
				t[ld][cd]=0;
				return 1;
			}
			else if (((ld - 1 == la) && (cd + 1 == ca)) || ((ld - 1 == la) && (cd - 1 == ca))) // diagonal attack
			{
				if (t[la][ca] < 0) // capture opponent piece
				{
					t[la][ca] = t[ld][cd];
					t[ld][cd] = 0;
					return 1;
				}
				else // illegal move
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
int Plateau::chlibretour(int ld, int cd, int la, int ca)
{
    
    if(t[ld][cd] == 5)
    {
        for(int i = ld+1; i <= la-1; i++)
        {
            if(t[i][cd] != 0)
            {
                return 0; 
            }
        }
        
        for(int j = cd+1; j <= ca-1; j++)
        {
            if(t[ld][j] != 0)
            {
                return 0; 
            }
        }
        
        
        for(int k = ld-1; k >= la+1; k--)
        {
            if(t[k][cd] != 0)
            {
                return 0; 
            }
        }
        
       
        for(int r = cd-1; r >= ca+1; r--)
        {
            if(t[ld][r] != 0)
            {
                return 0;
            }
        }
        
        return 1;
    }
    else if(t[ld][cd] == -5)
    {
        for(int i = ld+1; i <= la-1; i++)
        {
            if(t[i][cd] != 0)
            {
                return 0; 
            }
        }
        
        
        for(int j = cd+1; j <= ca-1; j++)
        {
            if(t[ld][j] != 0)
            {
                return 0; 
            }
        }
        
        for(int k = ld-1; k >= la+1; k--)
        {
            if(t[k][cd] != 0)
            {
                return 0;
            }
        }
        
        for(int r = cd-1; r >= ca+1; r--)
        {
            if(t[ld][r] != 0)
            {
                return 0; 
            }
        }
        
        return 1;
    }
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
int Plateau::chlibrefou(int ld, int cd, int la, int ca)
{
    if( t[ld][cd] == -3)
    {
        if(la > ld && ca > cd)
        {
        	for(int i = 1; i <= la-ld; i++)
        	{
        		if(t[ld+i][cd+i] != 0)
            	{
					return 0; 
            	}
        	}
		}
        
        if(la > ld && ca < cd)
        {
        	for(int j = 1; j <= la-ld; j++)
        	{
        		if(t[ld+j][cd-j] != 0)
            	{
					return 0; 
            	}
        	}
		}

        if(la < ld && ca > cd)
        {
        	for(int k = 1; k <= la-ld; k++)
        	{
        		if(t[ld-k][cd+k] != 0)
            	{
					return 0; 
            	}
        	}
		}
        
        if(la < ld && ca < cd)
        {
        	for(int r = 1; r <= la-ld; r++)
        	{
        		if(t[ld-r][cd-r] != 0)
            	{
					return 0; 
            	}
        	}
		}
        
        return 1;
    }
    
    else if(t[ld][cd] == 3)
    {
        if(la < ld && ca < cd)
        {
        	for(int i = 1; i <= la-ld; i++)
        	{
        		if(t[ld+i][cd+i] != 0)
            	{
					return 0; 
            	}
        	}
		}
         
        if(la < ld && ca > cd)
        {
        	for(int j = 1; j <= la-ld; j++)
        	{
        		if(t[ld+j][cd-j] != 0)
            	{
					return 0; 
            	}
        	}
		}

        if(la > ld && ca < cd)
        {
        	for(int k = 1; k <= la-ld; k++)
        	{
        		if(t[ld-k][cd+k] != 0)
            	{
					return 0; 
            	}
        	}
		}
        
        if(la > ld && ca > cd)
        {
        	for(int r = 1; r <= la-ld; r++)
        	{
        		if(t[ld-r][cd-r] != 0)
            	{
					return 0;
            	}
        	}
		}
        
        return 1;
    }

    return 0;
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

int Plateau::chlibredame(int ld, int cd, int la, int ca)
{
    if(t[ld][cd] == 2)
    {
        for(int i = ld+1; i <= la-1; i++)
        {
            if(t[i][cd] != 0)
            {
                return 0; 
            }
        }
        
        for(int j = cd+1; j <= ca-1; j++)
        {
            if(t[ld][j] != 0)
            {
                return 0; 
            }
        }
        
        for(int k = ld-1; k >= la+1; k--)
        {
            if(t[k][cd] != 0)
            {
                return 0; 
            }
        }
        
        for(int r = cd-1; r >= ca+1; r--)
        {
            if(t[ld][r] != 0)
            {
                return 0; 
            }
        }
        
        return 1;
    }
    else if(t[ld][cd] == -2)
    {
        for(int i = ld+1; i <= la-1; i++)
        {
            if(t[i][cd] != 0)
            {
                return 0;
            }
        }
        
        for(int j = cd+1; j <= ca-1; j++)
        {
            if(t[ld][j] != 0)
            {
                return 0; 
            }
        }
        
        for(int k = ld-1; k >= la+1; k--)
        {
            if(t[k][cd] != 0)
            {
                return 0; 
            }
        }
        
        for(int r = cd-1; r >= ca+1; r--)
        {
            if(t[ld][r] != 0)
            {
                return 0; 
            }
        }
        
        return 1;
    }
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
int Plateau::movtour(int ld,int cd,int la,int ca)
{
	int i,j,r,k,cp;
	
	if(t[ld][cd]==5) // Blanc
	{
		for(i=0;i<=7;i++) //en bas
		{	
			if(la==ld+i && ca==cd )//la +i
			{
				if (chlibretour(ld, cd, la, ca)) 
				{
					t[ld+i][cd]=5;
					t[ld][cd]=0;
					cp=ld+i;
				}
			}
			if(cp==la)//pour arriver a la et sortir de la boucle
			{
				i=8;
				return 1;
			}
		}
		
		for(k=0;k<=7;k++) //a droite
		{	
			if(la==ld && ca==cd+k)
			{
				if (chlibretour(ld, cd, la, ca)) 
				{
					t[ld][cd+k]=5;
					t[ld][cd]=0;
					cp=ld+k;
				}
			}
			if(cp==la)
			{
				k=8;
				return 1;
			}
		}
		
		for(j=7;j>=0;j--) //en haut
		{	
			if(la==ld-j && ca==cd )
			{
				if (chlibretour(ld, cd, la, ca)) 
				{
					t[ld-j][cd]=5;
					t[ld][cd]=0;
					cp=ld-j;
				}
			}
			if(cp==la)
			{
				j=-1;
				return 1;
			}
		}
		for(r=7;r>=0;r--)//a gauche
		{	
			if(la==ld && ca==cd-r && chlibretour(ld,cd,la,ca))
			{
				t[ld][cd-r]=5;
				t[ld][cd]=0;
				cp=ld-r;
			}
			if(cp==la)
			{
				r=-1;
				return 1;
			}
		}
	}
	
	else if(t[ld][cd]==-5) // Noir
	{
		for(i=0;i<=7;i++) //en bas
		{
			if(la==ld+i && ca==cd)
			{
				if (chlibretour(ld, cd, la, ca)) 
				{
					t[ld+i][cd]=-5;
					t[ld][cd]=0;
					cp=ld+i;
				}
			}
			if(cp==la)
			{
				i=8;
				return 1;
			}
		}
		for(k=0;k<=7;k++)//a droite
		{	
			if(la==ld && ca==cd+k)
			{
				if (chlibretour(ld, cd, la, ca)) 
				{
					t[ld][cd+k]=-5;
					t[ld][cd]=0;
					cp=ld+k;
				}
			}
			if(cp==la)
			{
				k=8;
				return 1;
			}
		}
		for(j=7;j>=0;j--)//en haut
		{	
			if(la==ld-j && ca==cd)
			{
				if (chlibretour(ld, cd, la, ca)) 
				{
					t[ld-j][cd]=-5;
					t[ld][cd]=0;
					cp=ld-j;
				}
			}
			if(cp==la)
			{
				j=-1;
				return 1;
			}
		}
		for(r=7;r>=0;r--)//a gauche
		{	
			if(la==ld && ca==cd-r && chlibretour(ld,cd,la,ca))
			{
				t[ld][cd-r]=-5;
				t[ld][cd]=0;
				cp=ld-r;
			}
			if(cp==la)
			{
				r=-1;
				return 1;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
int Plateau::movroi(int ld,int cd,int la,int ca)
{
	if(t[ld][cd]==-1 || t[ld][cd]==1)
	{
		if( ((la==ld)&&(ca==cd+1)) || ((la==ld)&&(ca==cd-1)) || ((la==ld-1)&&(ca==cd)) || ((la==ld+1)&&(ca==cd)) )
		{
			t[la][ca]=t[ld][cd];
			t[ld][cd]=0;
			return 1;			
		}
		else if((la==ld-1)&&(ca==cd-1) || ((la==ld-1)&&(ca==cd+1)) || ((la==ld+1)&&(ca==cd-1)) || ((la==ld+1)&&(ca==cd+1)))
		{
			t[la][ca]=t[ld][cd];
			t[ld][cd]=0;
			return 1;	
		}
		else
		{
			return 0;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
int Plateau::movcavalier(int ld,int cd,int la,int ca)
{
	if(t[ld][cd]==4 || t[ld][cd]==-4)
	{
		if(((la==ld-1)&&(ca==cd+2)) || ((la==ld-1)&&(ca==cd-2)) || ((la==ld-2)&&(ca==cd-1)) || ((la==ld-2)&&(ca==cd+1)))
		{
			t[la][ca]=t[ld][cd];
			t[ld][cd]=0;
			return 1;			
		}
		else if(((la==ld+1)&&(ca==cd+2)) || ((la==ld+1)&&(ca==cd-2)) || ((la==ld+2)&&(ca==cd-1)) || ((la==ld+2)&&(ca==cd+1)))
		{
			t[la][ca]=t[ld][cd];
			t[ld][cd]=0;
			return 1;			
		}
		else
		{
			return 0;
		}
	}
}
//////////////////////////////////////////////////////////////////
int Plateau::movfou(int ld, int cd, int la, int ca) 
{
    int i, j, k, r, cp;

    // Check if the fou is currently at ld, cd
    if (t[ld][cd] == -3) 
	{
        // Move diagonally to la, ca (bottom-right)
        if (la > ld && ca > cd) 
		{
            for (i = 1; i <= la - ld; i++) 
			{
                if (t[ld+i][cd+i] != 0) 
				{
                    if (t[ld+i][cd+i] > 0) // Attaque possible
                    {
                        cp = t[ld+i][cd+i]; // Sauvegarde de la pièce attaquée
                        t[ld+i][cd+i] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = -3;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }
                }
            }
            t[la][ca] = -3;
        }
        // Move diagonally to la, ca (bottom-left)
        else if (la > ld && ca < cd) 
		{
            for (j = 1; j <= la - ld; j++) 
			{
                if (t[ld+j][cd-j] != 0) 
				{
                    if (t[ld+j][cd-j] > 0) // Attaque possible
                    {
                        cp = t[ld+j][cd-j]; // Sauvegarde de la pièce attaquée
                        t[ld+j][cd-j] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = -3;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }
                }
            }
            t[la][ca] = -3;
        }
        // Move diagonally to la, ca (top-right)
        else if (la < ld && ca > cd) 
		{
            for (k = 1; k <= ld - la; k++) 
			{
                if (t[ld-k][cd+k] != 0) 
				{
                    if (t[ld-k][cd+k] > 0) // Attaque possible
                    {
                        cp = t[ld-k][cd+k]; // Sauvegarde de la pièce attaquée
                        t[ld-k][cd+k] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = -3;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }
                }
            }
            t[la][ca]=-3;
        }
        else if (la < ld && ca < cd) 
		{
            for (r = 1; r <= ld - la; r++) 
			{
			    if (t[ld-r][cd+r] != 0) 
    			{
        			if (t[ld-r][cd+r] > 0) // Attaque possible
        			{
            			cp = t[ld-r][cd+r]; // Sauvegarde de la pièce attaquée
            			t[ld-r][cd+r] = 0;  // La pièce attaquée est retirée du plateau
            			t[la][ca] = -3;
            			t[ld][cd] = 0;
            			return cp;          // On retourne la valeur de la pièce attaquée
        			}
        			else
        			{
        			    return 0;  // Square is not empty, path is blocked
        			}
    			}
			}
			t[la][ca] = -3;
			t[ld][cd] = 0;
			return 1;
        }
        t[ld][cd] = 0;
        return 1;
    }
    if (t[ld][cd] == 3) 
	{
        // Move diagonally to la, ca (bottom-right)
        if (la > ld && ca > cd) 
		{
            for (i = 1; i <= la - ld; i++) 
			{
                if (t[ld+i][cd+i] != 0) 
				{
                    if (t[ld+i][cd+i] < 0) // Attaque possible
                    {
                        cp = t[ld+i][cd+i]; // Sauvegarde de la pièce attaquée
                        t[ld+i][cd+i] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = 3;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }
                }
            }
            t[la][ca] = 3;
        }
        // Move diagonally to la, ca (bottom-left)
        else if (la > ld && ca < cd) 
		{
            for (j = 1; j <= la - ld; j++) 
			{
                if (t[ld+j][cd-j] != 0) 
				{
                    if (t[ld+j][cd-j] < 0) // Attaque possible
                    {
                        cp = t[ld+j][cd-j]; // Sauvegarde de la pièce attaquée
                        t[ld+j][cd-j] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = 3;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }
                }
            }
            t[la][ca] = 3;
        }
        // Move diagonally to la, ca (top-right)
        else if (la < ld && ca > cd) 
		{
            for (k = 1; k <= ld - la; k++) 
			{
                if (t[ld-k][cd+k] != 0) 
				{
                    if (t[ld-k][cd+k] < 0) // Attaque possible
                    {
                        cp = t[ld-k][cd+k]; // Sauvegarde de la pièce attaquée
                        t[ld-k][cd+k] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = 3;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }
                }
            }
            t[la][ca]=3;
        }
        else if (la < ld && ca < cd) //top-left
		{
            for (r = 1; r <= ld - la; r++) 
			{
			    if (t[ld-r][cd-r] != 0) 
    			{
        			if (t[ld-r][cd-r] < 0) // Attaque possible
        			{
            			cp = t[ld-r][cd-r]; // Sauvegarde de la pièce attaquée
            			t[ld-r][cd-r] = 0;  // La pièce attaquée est retirée du plateau
            			t[la][ca] = 3;
            			t[ld][cd] = 0;
            			return cp;          // On retourne la valeur de la pièce attaquée
        			}
        			else
        			{
        			    return 0;  // Square is not empty, path is blocked
        			}
    			}
			}
			t[la][ca] = 3;
			t[ld][cd] = 0;
			return 1;
	    }
        t[ld][cd] = 0;
        return 1;
    }
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
int Plateau::movdame(int ld,int cd,int la,int ca)
{
	int i,j,k,r,cp;
	if(t[ld][cd]==2)
	{
		for(i=0;i<=7;i++) //en bas
		{	
			if(la==ld+i && ca==cd )//la +i
			{
				if (chlibredame(ld, cd, la, ca)) 
				{
					t[ld+i][cd]=2;
					t[ld][cd]=0;
					cp=ld+i;
				}
			}
			if(cp==la)//pour arriver a la et sortir de la boucle
			{
				i=8;
				return 1;
			}
		}
		
		for(k=0;k<=7;k++) //a droite
		{	
			if(la==ld && ca==cd+k)
			{
				if (chlibredame(ld, cd, la, ca)) 
				{
					t[ld][cd+k]=2;
					t[ld][cd]=0;
					cp=ld+k;
				}
			}
			if(cp==la)
			{
				k=8;
				return 1;
			}
		}
		
		for(j=7;j>=0;j--) //en haut
		{	
			if(la==ld-j && ca==cd )
			{
				if (chlibredame(ld, cd, la, ca)) 
				{
					t[ld-j][cd]=2;
					t[ld][cd]=0;
					cp=ld-j;
				}
			}
			if(cp==la)
			{
				j=-1;
				return 1;
			}
		}
		for(r=7;r>=0;r--)//a gauche
		{	
			if(la==ld && ca==cd-r && chlibredame(ld,cd,la,ca))
			{
				t[ld][cd-r]=2;
				t[ld][cd]=0;
				cp=ld-r;
			}
			if(cp==la)
			{
				r=-1;
				return 1;
			}
		}
		if (la > ld && ca > cd) //en bas a droite
		{
            for (i = 1; i <= la - ld; i++) 
			{
                if (t[ld+i][cd+i] != 0) 
				{
					if (t[ld+i][cd+i] < 0) // Attaque possible
                    {
                        cp = t[ld+i][cd+i]; // Sauvegarde de la pièce attaquée
                        t[ld+i][cd+i] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = 2;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }   
				}
            }
            t[la][ca] = 2;
            t[ld][cd] = 0;
        }
		else if (la > ld && ca < cd) //en bas a gauche
		{
            for (j = 1; j <= la - ld; j++) 
			{
                if (t[ld+j][cd-j] != 0) 
				{
					if (t[ld+j][cd-j] < 0) // Attaque possible
                    {
                        cp = t[ld+j][cd-j]; // Sauvegarde de la pièce attaquée
                        t[ld+j][cd-j] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = 2;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }   
				}
            }
            t[la][ca] = 2;
            t[ld][cd] = 0;
        }
		else if (la < ld && ca > cd) //en haut a droite
		{
            for (k = 1; k <= ld - la; k++) 
			{
                if (t[ld-k][cd+k] != 0) 
				{
					if (t[ld-k][cd+k] < 0) // Attaque possible
                    {
                        cp = t[ld-k][cd+k]; // Sauvegarde de la pièce attaquée
                        t[ld-k][cd+k] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = 2;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }   
				}
            }
            t[la][ca] = 2;
            t[ld][cd] = 0;
        }
		 else if (la < ld && ca < cd) //en haut a gauche
		{
            for (r = 1; r <= ld - la; r++) 
			{
                if (t[ld-r][cd-r] != 0) 
				{
					if (t[ld-r][cd-r] < 0) // Attaque possible
                    {
                        cp = t[ld-r][cd-r]; // Sauvegarde de la pièce attaquée
                        t[ld-r][cd-r] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = 2;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }   
				}
            }
            t[la][ca] = 2;
            t[ld][cd] = 0;
        }
        return 1;
	}
	else if(t[ld][cd]==-2)
	{
		for(i=0;i<=7;i++) //en bas
		{
			if(la==ld+i && ca==cd)
			{
				if (chlibredame(ld, cd, la, ca)) 
				{
					t[ld+i][cd]=-2;
					t[ld][cd]=0;
					cp=ld+i;
				}
			}
			if(cp==la)
			{
				i=8;
				return 1;
			}
		}
		for(k=0;k<=7;k++)//a droite
		{	
			if(la==ld && ca==cd+k)
			{
				if (chlibredame(ld, cd, la, ca)) 
				{
					t[ld][cd+k]=-2;
					t[ld][cd]=0;
					cp=ld+k;
				}
			}
			if(cp==la)
			{
				k=8;
				return 1;
			}
		}
		for(j=7;j>=0;j--)//en haut
		{	
			if(la==ld-j && ca==cd)
			{
				if (chlibredame(ld, cd, la, ca)) 
				{
					t[ld-j][cd]=-2;
					t[ld][cd]=0;
					cp=ld-j;
				}
			}
			if(cp==la)
			{
				j=-1;
				return 1;
			}
		}
		for(r=7;r>=0;r--)//a gauche
		{	
			if(la==ld && ca==cd-r && chlibredame(ld,cd,la,ca))
			{
				t[ld][cd-r]=-2;
				t[ld][cd]=0;
				cp=ld-r;
			}
			if(cp==la)
			{
				r=-1;
				return 1;
			}
		}
		if (la > ld && ca > cd) //en bas a droite
		{
            for (i = 1; i <= la - ld; i++) 
			{
               if (t[ld+i][cd+i] != 0) 
				{
					if (t[ld+i][cd+i] > 0) // Attaque possible
                    {
                        cp = t[ld+i][cd+i]; // Sauvegarde de la pièce attaquée
                        t[ld+i][cd+i] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = -2;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }   
				}
            }
            t[la][ca] = -2;
            t[ld][cd] = 0;
        }
		else if (la > ld && ca < cd) //en bas a gauche
		{
            for (j = 1; j <= la - ld; j++) 
			{
                if (t[ld+j][cd-j] != 0) 
				{
					if (t[ld+j][cd-j] > 0) // Attaque possible
                    {
                        cp = t[ld+j][cd-j]; // Sauvegarde de la pièce attaquée
                        t[ld+j][cd-j] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = -2;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }   
				}
            }
            t[la][ca] = -2;
            t[ld][cd] = 0;
        }
		else if (la < ld && ca > cd) //en haut a droite
		{
            for (k = 1; k <= ld - la; k++) 
			{
                if (t[ld-k][cd+k] != 0) 
				{
					if (t[ld-k][cd+k] > 0) // Attaque possible
                    {
                        cp = t[ld-k][cd+k]; // Sauvegarde de la pièce attaquée
                       	t[ld-k][cd+k] = 0;  // La pièce attaquée est retirée du plateau
                       	t[la][ca] = -2;
                      	t[ld][cd] = 0;
                       	return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    	else
                    	{
                        	return 0;  // Square is not empty, path is blocked
                    	}   
				}              
            }
            t[la][ca] = -2;
            t[ld][cd] = 0;
        }
		else if (la < ld && ca < cd) //en haut a gauche
		{
            for (r = 1; r <= ld - la; r++) 
			{
                if (t[ld-r][cd-r] != 0) 
				{
					if (t[ld-r][cd-r] > 0) // Attaque possible
                    {
                        cp = t[ld-r][cd-r]; // Sauvegarde de la pièce attaquée
                        t[ld-r][cd-r] = 0;  // La pièce attaquée est retirée du plateau
                        t[la][ca] = -2;
                        t[ld][cd] = 0;
                        return cp;          // On retourne la valeur de la pièce attaquée
                    }
                    else
                    {
                        return 0;  // Square is not empty, path is blocked
                    }   
				}
            }
            t[la][ca] = -2;
            t[ld][cd] = 0;
        }
        return 1;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
int Plateau::deroulement(int ld,int cd,int la,int ca)
{
	if(t[ld][cd]==1 || t[ld][cd]==-1)
	{
		movroi(ld,cd,la,ca);
		return 1;
	}
	if(t[ld][cd]==2 || t[ld][cd]==-2)
	{
		movdame(ld,cd,la,ca);
		return 1;
	}
	if(t[ld][cd]==3 || t[ld][cd]==-3)
	{
		movfou(ld,cd,la,ca);
		return 1;
	}
	if(t[ld][cd]==4 || t[ld][cd]==-4)
	{
		movcavalier(ld,cd,la,ca);
		return 1;
	}
	if(t[ld][cd]==5 || t[ld][cd]==-5)
	{
		movtour(ld,cd,la,ca);
		return 1;
	}
	if(t[ld][cd]==6 || t[ld][cd]==-6)
	{
		movpion(ld,cd,la,ca);
		return 1;
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Plateau::Promotion(int ld , int cd , int la , int ca)
{
	int choix;
	if(t[0][ca]==6 ) // check if white pawn has reached the end of the board
	{
		//BLANC
		cout<<"CHANGEMENT POSSIBLE : "<<endl;
		cout<<"1-CAVALIER (CB)"<<endl<<"2-FOU (FB)"<<endl<<"3-TOUR (TB)"<<endl<<"4-DAME (QB)"<<endl;
		cin>>choix;
		switch(choix)
		{
			case 1 :
				t[0][ca]=4; // place cavalier
			break;
			case 2 :
				t[0][ca]=3; // place fou
			break;
			case 3 :
				t[0][ca]=5; // place tour
			break;
			case 4 :
				t[0][ca]=2; // place dame
			break;
			default:
				break;
		}
	}
	//NOIR
	else if(t[7][ca]==-6 ) // check if black pawn has reached the end of the board
	{
		cout<<"CHANGEMENT POSSIBLE : "<<endl;
		cout<<"1-CAVALIER (CN)"<<endl<<"2-FOU (FN)"<<endl<<"3-TOUR (TN)"<<endl<<"4-DAME (QN)"<<endl;
		cin>>choix;
		switch(choix)
		{
			case 1 :
				t[7][ca]=-4; // place cavalier
			break;
			case 2 :
				t[7][ca]=-3; // place fou
			break;
			case 3 :
				t[7][ca]=-5; // place tour
			break;
			case 4 :
				t[7][ca]=-2; // place dame
			break;
			default:
				break;
		}
	}
}
/////////////////////////////////////////////////////

void Plateau::RoockNoir(int ld , int cd , int la , int ca)
{
	int choix;
	if(t[0][4]==-1 && t[0][7]==-5 && t[0][6]==0 && t[0][5]==0)
	{
		cout<<"Voulez vous appliquer un roque entrer [1] sinon entrer [2] pour passer"<<endl;
		cin>>choix;
		switch(choix)
		{
			case 1:
				t[0][5]=-5;
				t[0][6]=-1;
				t[0][4]=0;
				t[0][7]=0;
			break;
			default:
				break;
		}
	}
	if(t[0][4]==-1 && t[0][0]==-5 && t[0][1]==0 && t[0][2]==0 && t[0][3]==0)
	{
		cout<<"Voulez vous appliquer un roque entrer [1] sinon entrer [2] pour passer"<<endl;
		cin>>choix;
		switch(choix)
		{
			case 1:
				t[0][3]=-5;
				t[0][2]=-1;
				t[0][4]=0;
				t[0][0]=0;
				t[0][1]=0;
			break;
			default:
				break;
		}
	}
}
//////////////////////////////////////////////////
void Plateau::RoockBlanc(int ld , int cd ,int la,int ca)
{
	int choix;
	if(t[7][4]==1 && t[7][7]==5 && t[7][6]==0 && t[7][5]==0)
	{
		cout<<"Voulez vous appliquer un roque entrer [1] sinon entrer [2] pour passer "<<endl;  
		cin>>choix;
		switch(choix)
		{
			case 1 :t[7][5]=5;
					t[7][6]=1;
					t[7][4]=0;
					t[7][7]=0; break;
			default :
				break;
		}		
	}
	if(t[7][4]==1 && t[7][0]==5 && t[7][1]==0 && t[7][2]==0 && t[7][3]==0)
	{	
		cout<<"Voulez vous appliquer un roque entrer [1] sinon entrer [2] pour passer"<<endl;  
		cin>>choix;
		switch(choix)
		{
			case 1: t[7][2]=1;
					t[7][3]=5;
					t[7][4]=0;
					t[7][0]=0;
					t[7][1]=0; break;
			default : 
				break;
		}
	}
}

void Plateau::afficher()
{
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			cout<<t[i][j]<<" ";
		}
		cout<<endl;
	}
	
}

void Plateau::PriseEnPassant(int ld , int cd ,int la,int ca)
{
	
	if(t[3][cd]==6 && t[3][cd+1]==-6 || t[3][cd-1]==-6 && firstmoveB(ld,cd,la,ca)==1)
	{
		if(la==ld-1 && ca==cd-1)
		{
			t[ld-1][cd-1]=6;
			t[ld][cd]=0;
			t[ld][cd-1]=0;
		}
		if(la==ld-1 && ca==cd+1)
		{
			t[ld-1][cd+1]=6;
			t[ld][cd]=0;
			t[ld][cd+1]=0;
		}
	}
	if(t[4][cd]==-6 && t[4][cd+1]==6 || t[4][cd-1]==6 && firstmoveB(ld,cd,la,ca)==1)
	{
		if(la==ld+1 && ca==cd+1)
		{
			t[ld+1][cd+1]=-6;
			t[ld][cd]=0;
			t[ld][cd+1]=0;
		}
		if(la==ld+1 && ca==cd-1)
		{
			t[ld+1][cd-1]=-6;
			t[ld][cd]=0;
			t[ld][cd-1]=0;
		}
	}
}

void Plateau::Save(int joueur)
{
    ofstream f("chess.txt",ios::out | ios::trunc); // Use default open mode of "out" which truncates existing content
    if (f.is_open()) // Check if file is successfully opened
    {
        if (joueur % 2 == 1)
        {
            f << "Blanc" << endl;
        }
        else // Use "else" instead of "else if" for clarity since there are only two possibilities
        {
            f << "Noir" << endl;
        }
        
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                switch (t[i][j]) // Use switch statement for better readability and maintainability
                {
                    case 5: f << "Tour Blanc\n" ; break;
                    case -5: f << "Tour Noir\n" ; break;
                    case 4: f << "Cavalier Blanc\n" ; break;
                    case -4: f << "Cavalier Noir\n" ; break;
                    case 3: f << "Fou Blanc\n" ; break;
                    case -3: f << "Fou Noir\n" ; break;
                    case 2: f << "Dame Blanc\n"; break;
                    case -2: f << "Dame Noir\n"; break;
                    case 1: f << "Roi Blanc\n" ; break;
                    case -1: f << "Roi Noir\n" ; break;
                    case 6: f << "Pion Blanc\n" ; break;
                    case -6: f << "Pion Noir\n"; break;
                    case 0: f << "Vide\n" ;  break;
                    default: f << "ERREUR\n" ; break; // Add default case to handle unexpected values
                }
            }
        }
        
        f.close();
        
    }
    else
    {
        cout << "Erreur d'ouverture du fichier !" << endl; // Add line break to the end of the error message
    }
}


	
void Plateau::Load(int &joueur)
{
    ifstream f("chess.txt");
    if (f.is_open())
    {
    	
        string couleur;
        getline(f, couleur); // Read the first line which contains the color of the next player
        //cout<<"nom : "<<nom<<endl;
        if (couleur == "Blanc")
        {
            joueur = 2;
        }
        else if (couleur == "Noir")
        {
            joueur = 1;
        }
        else
        {
            cout << "ERREUR: Couleur invalide !" << endl;
            return;
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                string nom;
                getline(f, nom); // Read the name of the piece
                //cout<<"NOM : "<<nom<<endl;
                if (nom == "Tour Blanc")
                {
                    t[i][j] = 5;
                }
                else if (nom == "Tour Noir")
                {
                    t[i][j] = -5;
                }
                else if (nom == "Cavalier Blanc")
                {
                    t[i][j] = 4;
                }
                else if (nom == "Cavalier Noir")
                {
                    t[i][j] = -4;
                }
                else if (nom == "Fou Blanc")
                {
                    t[i][j] = 3;
                }
                else if (nom == "Fou Noir")
                {
                    t[i][j] = -3;
                }
                else if (nom == "Dame Blanc")
                {
                    t[i][j] = 2;
                }
                else if (nom == "Dame Noir")
                {
                    t[i][j] = -2;
                }
                else if (nom == "Roi Blanc")
                {
                    t[i][j] = 1;
                }
                else if (nom == "Roi Noir")
                {
                    t[i][j] = -1;
                }
                else if (nom == "Pion Blanc")
                {
                    t[i][j] = 6;
                }
                else if (nom == "Pion Noir")
                {
                    t[i][j] = -6;
                }
                else if (nom == "Vide")
                {
                    t[i][j] = 0;
                }  
            }
        }
        f.close();
    }
    else
    {
        cout << "Erreur d'ouverture du fichier !" << endl;
    }
}


////////////////////////////////////////////////////////////////////////////

bool Plateau::CheckRoiBlanc(int line , int colonne)
{
	int ld,cd,la,ca;
	int i,j,roiI,roiJ;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(t[i][j]==1)
			{
				roiI=i;
				roiJ=j;
			}
		}
	}
	
	for(i=0;i<8;i++) 
	{
		for(j=0;j<8;j++)
		{
			if(t[i][j]==-1)
			{
				if(i-1==roiI && j-1==roiJ || i-1==roiI && j==roiJ || i-1==roiI && j+1==roiJ || i==roiI && j-1==roiJ || i==roiI && j+1==roiJ || i+1==roiI && j-1==roiJ || i+1==roiI && j==roiJ || i+1==roiI && j+1==roiJ)
				{
					return true;
				}
			}
			if(t[i][j]==-5)
			{
				if((i+1==roiI && j==roiJ) || (i+2==roiI && j==roiJ) || (i+3==roiI && j==roiJ) || (i+4==roiI && j==roiJ) || (i+5==roiI && j==roiJ) || (i+6==roiI && j==roiJ) || (i+7==roiI && j==roiJ) || (i==roiI && j+1==roiJ) || (i==roiI && j+2==roiJ) || (i==roiI && j+3==roiJ) || (i==roiI && j+4==roiJ) || (i==roiI && j+5==roiJ) || (i==roiI && j+6==roiJ) || (i==roiI && j+7==roiJ) || (i-1==roiI && j==roiJ) || (i-2==roiI && j==roiJ) || (i-3==roiI && j==roiJ) || (i-4==roiI && j==roiJ) || (i-5==roiI && j==roiJ) || (i-6==roiI && j==roiJ) || (i-7==roiI && j==roiJ) || (i==roiI && j-1==roiJ) || (i==roiI && j-2==roiJ) || (i==roiI && j-3==roiJ) || (i==roiI && j-4==roiJ) || (i==roiI && j-5==roiJ) || (i==roiI && j-6==roiJ) || (i==roiI && j-7==roiJ))
				{
					if(chlibretour(ld,cd,la,ca))
					{
						return true;	
					}
				}
			}
	
			if(t[i][j]==-4)
			{
			   if((i-2==roiI && j-1==roiJ )||(i-1==roiI && j-2==roiJ )||(i+1==roiI && j-2==roiJ )||(i+2==roiI && j-1==roiJ )||(i-2==roiI && j+1==roiJ )||(i-1==roiI && j+2==roiJ )||(i+1==roiI && j+2==roiJ )||(i+2==roiI && j+1==roiJ ))
				{
		 			return true;
				}
			}
	
			if(t[i][j]==-3)
			{
				if((i-1==roiI && j-1==roiJ)||(i-2==roiI && j-2==roiJ)||(i-3==roiI && j-3==roiJ)||(i-4==roiI && j-4==roiJ)||(i-5==roiI && j-5==roiJ)||(i-6==roiI && j-6==roiJ)||(i-7==roiI && j-7==roiJ)||(i-1==roiI && j+1==roiJ)||(i-2==roiI && j+2==roiJ)||(i-3==roiI && j+3==roiJ)||(i-4==roiI && j+4==roiJ)||(i-5==roiI && j+5==roiJ)||(i-6==roiI && j+6==roiJ)||(i-7==roiI && j+7==roiJ)||(i+1==roiI && j+1==roiJ)||(i+2==roiI && j+2==roiJ)||(i+3==roiI && j+3==roiJ)||(i+4==roiI && j+4==roiJ)||(i+5==roiI && j+5==roiJ)||(i+6==roiI && j+6==roiJ)||(i+7==roiI && j+7==roiJ)||(i+1==roiI && j-1==roiJ)||(i+2==roiI && j-2==roiJ)||(i+3==roiI && j-3==roiJ)||(i+4==roiI && j-4==roiJ)||(i+5==roiI && j-5==roiJ)||(i+6==roiI && j-6==roiJ)||(i+7==roiI && j-7==roiJ))
				{
					if(chlibrefou(ld,cd,la,ca))
					{
						return true;	
					}
				}
			}
			if(t[i][j]==-2)
			{
				if((i-1==roiI && j-1==roiJ)||(i-2==roiI && j-2==roiJ)||(i-3==roiI && j-3==roiJ)||(i-4==roiI && j-4==roiJ)||(i-5==roiI && j-5==roiJ)||(i-6==roiI && j-6==roiJ)||(i-7==roiI && j-7==roiJ)||(i-1==roiI && j+1==roiJ)||(i-2==roiI && j+2==roiJ)||(i-3==roiI && j+3==roiJ)||(i-4==roiI && j+4==roiJ)||(i-5==roiI && j+5==roiJ)||(i-6==roiI && j+6==roiJ)||(i-7==roiI && j+7==roiJ)||(i+1==roiI && j+1==roiJ)||(i+2==roiI && j+2==roiJ)||(i+3==roiI && j+3==roiJ)||(i+4==roiI && j+4==roiJ)||(i+5==roiI && j+5==roiJ)||(i+6==roiI && j+6==roiJ)||(i+7==roiI && j+7==roiJ)||(i+1==roiI && j-1==roiJ)||(i+2==roiI && j-2==roiJ)||(i+3==roiI && j-3==roiJ)||(i+4==roiI && j-4==roiJ)||(i+5==roiI && j-5==roiJ)||(i+6==roiI && j-6==roiJ)||(i+7==roiI && j-7==roiJ)||(i+1==roiI && j==roiJ) || (i+2==roiI && j==roiJ) || (i+3==roiI && j==roiJ) || (i+4==roiI && j==roiJ) || (i+5==roiI && j==roiJ) || (i+6==roiI && j==roiJ) || (i+7==roiI && j==roiJ) || (i==roiI && j+1==roiJ) || (i==roiI && j+2==roiJ) || (i==roiI && j+3==roiJ) || (i==roiI && j+4==roiJ) || (i==roiI && j+5==roiJ) || (i==roiI && j+6==roiJ) || (i==roiI && j+7==roiJ) || (i-1==roiI && j==roiJ) || (i-2==roiI && j==roiJ) || (i-3==roiI && j==roiJ) || (i-4==roiI && j==roiJ) || (i-5==roiI && j==roiJ) || (i-6==roiI && j==roiJ) || (i-7==roiI && j==roiJ) || (i==roiI && j-1==roiJ) || (i==roiI && j-2==roiJ) || (i==roiI && j-3==roiJ) || (i==roiI && j-4==roiJ) || (i==roiI && j-5==roiJ) || (i==roiI && j-6==roiJ) || (i==roiI && j-7==roiJ))
				{
					if(chlibredame(ld,cd,la,ca))
					{
						return true;	
					}
				}		
			}
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////


bool Plateau::CheckRoiNoir(int ligne , int colonne)
{
	int ld,cd,la,ca;
	int i,j,roiI,roiJ;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(t[i][j]==-1)
			{
				roiI=i;
				roiJ=j;
			}		
		}	
	}

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(t[i][j]==1)
			{
				if(i-1==roiI && j-1==roiJ || i-1==roiI && j==roiJ || i-1==roiI && j+1==roiJ || i==roiI && j-1==roiJ || i==roiI && j+1==roiJ || i+1==roiI && j-1==roiJ || i+1==roiI && j==roiJ || i+1==roiI && j+1==roiJ)
				{
					return true;
				}
			}
			if(t[i][j]==5)
			{
				if((i+1==roiI && j==roiJ) || (i+2==roiI && j==roiJ) || (i+3==roiI && j==roiJ) || (i+4==roiI && j==roiJ) || (i+5==roiI && j==roiJ) || (i+6==roiI && j==roiJ) || (i+7==roiI && j==roiJ) || (i==roiI && j+1==roiJ) || (i==roiI && j+2==roiJ) || (i==roiI && j+3==roiJ) || (i==roiI && j+4==roiJ) || (i==roiI && j+5==roiJ) || (i==roiI && j+6==roiJ) || (i==roiI && j+7==roiJ) || (i-1==roiI && j==roiJ) || (i-2==roiI && j==roiJ) || (i-3==roiI && j==roiJ) || (i-4==roiI && j==roiJ) || (i-5==roiI && j==roiJ) || (i-6==roiI && j==roiJ) || (i-7==roiI && j==roiJ) || (i==roiI && j-1==roiJ) || (i==roiI && j-2==roiJ) || (i==roiI && j-3==roiJ) || (i==roiI && j-4==roiJ) || (i==roiI && j-5==roiJ) || (i==roiI && j-6==roiJ) || (i==roiI && j-7==roiJ))
				{
					if(chlibretour(ld,cd,la,ca))
					{
						return true;	
					}
				}
			}
	
			if(t[i][j]==4)
			{
			   if((i-2==roiI && j-1==roiJ )||(i-1==roiI && j-2==roiJ )||(i+1==roiI && j-2==roiJ )||(i+2==roiI && j-1==roiJ )||(i-2==roiI && j+1==roiJ )||(i-1==roiI && j+2==roiJ )||(i+1==roiI && j+2==roiJ )||(i+2==roiI && j+1==roiJ ))
				{
		 			return true;
				}
			}
	
			if(t[i][j]==3)
			{
				if((i-1==roiI && j-1==roiJ)||(i-2==roiI && j-2==roiJ)||(i-3==roiI && j-3==roiJ)||(i-4==roiI && j-4==roiJ)||(i-5==roiI && j-5==roiJ)||(i-6==roiI && j-6==roiJ)||(i-7==roiI && j-7==roiJ)||(i-1==roiI && j+1==roiJ)||(i-2==roiI && j+2==roiJ)||(i-3==roiI && j+3==roiJ)||(i-4==roiI && j+4==roiJ)||(i-5==roiI && j+5==roiJ)||(i-6==roiI && j+6==roiJ)||(i-7==roiI && j+7==roiJ)||(i+1==roiI && j+1==roiJ)||(i+2==roiI && j+2==roiJ)||(i+3==roiI && j+3==roiJ)||(i+4==roiI && j+4==roiJ)||(i+5==roiI && j+5==roiJ)||(i+6==roiI && j+6==roiJ)||(i+7==roiI && j+7==roiJ)||(i+1==roiI && j-1==roiJ)||(i+2==roiI && j-2==roiJ)||(i+3==roiI && j-3==roiJ)||(i+4==roiI && j-4==roiJ)||(i+5==roiI && j-5==roiJ)||(i+6==roiI && j-6==roiJ)||(i+7==roiI && j-7==roiJ))
				{
					if(chlibrefou(ld,cd,la,ca))
					{
						return true;	
					}
				}
			}
			if(t[i][j]==2)
			{
				if((i-1==roiI && j-1==roiJ)||(i-2==roiI && j-2==roiJ)||(i-3==roiI && j-3==roiJ)||(i-4==roiI && j-4==roiJ)||(i-5==roiI && j-5==roiJ)||(i-6==roiI && j-6==roiJ)||(i-7==roiI && j-7==roiJ)||(i-1==roiI && j+1==roiJ)||(i-2==roiI && j+2==roiJ)||(i-3==roiI && j+3==roiJ)||(i-4==roiI && j+4==roiJ)||(i-5==roiI && j+5==roiJ)||(i-6==roiI && j+6==roiJ)||(i-7==roiI && j+7==roiJ)||(i+1==roiI && j+1==roiJ)||(i+2==roiI && j+2==roiJ)||(i+3==roiI && j+3==roiJ)||(i+4==roiI && j+4==roiJ)||(i+5==roiI && j+5==roiJ)||(i+6==roiI && j+6==roiJ)||(i+7==roiI && j+7==roiJ)||(i+1==roiI && j-1==roiJ)||(i+2==roiI && j-2==roiJ)||(i+3==roiI && j-3==roiJ)||(i+4==roiI && j-4==roiJ)||(i+5==roiI && j-5==roiJ)||(i+6==roiI && j-6==roiJ)||(i+7==roiI && j-7==roiJ)||(i+1==roiI && j==roiJ) || (i+2==roiI && j==roiJ) || (i+3==roiI && j==roiJ) || (i+4==roiI && j==roiJ) || (i+5==roiI && j==roiJ) || (i+6==roiI && j==roiJ) || (i+7==roiI && j==roiJ) || (i==roiI && j+1==roiJ) || (i==roiI && j+2==roiJ) || (i==roiI && j+3==roiJ) || (i==roiI && j+4==roiJ) || (i==roiI && j+5==roiJ) || (i==roiI && j+6==roiJ) || (i==roiI && j+7==roiJ) || (i-1==roiI && j==roiJ) || (i-2==roiI && j==roiJ) || (i-3==roiI && j==roiJ) || (i-4==roiI && j==roiJ) || (i-5==roiI && j==roiJ) || (i-6==roiI && j==roiJ) || (i-7==roiI && j==roiJ) || (i==roiI && j-1==roiJ) || (i==roiI && j-2==roiJ) || (i==roiI && j-3==roiJ) || (i==roiI && j-4==roiJ) || (i==roiI && j-5==roiJ) || (i==roiI && j-6==roiJ) || (i==roiI && j-7==roiJ))
				{
					if(chlibredame(ld,cd,la,ca))
					{
						return true;	
					}
				}		
			}	
	    }
    }
	return false;

}

bool Plateau::RoiB() 
{
    // Recherche de la position du roi blanc
    int rbLigne = -1;
    int rbColonne = -1;
    for (int i = 0; i < 8; i++) 
	{
        for (int j = 0; j < 8; j++) 
		{
            if (t[i][j] == 1) 
			{  // le roi blanc a la valeur 1 dans la matrice
                rbLigne = i;
                rbColonne = j;
            }
        }
    } 
    // Vérification s'il est en échec
    if (CheckRoiBlanc(rbLigne, rbColonne)) 
	{
        return true;
    } 
	else 
	{
        return false;
    }
}

bool Plateau::RoiN() {
    // Recherche de la position du roi noir
    int rnLigne = -1;
    int rnColonne = -1;
    for (int i = 0; i < 8; i++) 
	{
        for (int j = 0; j < 8; j++) 
		{
            if (t[i][j] == 6) 
			{  // le roi noir a la valeur 6 dans la matrice
                rnLigne = i;
                rnColonne = j;
            }
        }
    }
    // Vérification s'il est en échec
    if (CheckRoiNoir(rnLigne, rnColonne)) 
	{
        return true;
    } 
	else 
	{
        return false;
    }
}

bool Plateau::Null() 
{
    // Recherche s'il y a assez de pièces pour continuer la partie
    int nbPiecesBlanches = 0;
    int nbPiecesNoires = 0;
    for (int ligne = 0; ligne < 8; ligne++) 
	{
        for (int colonne = 0; colonne < 8; colonne++) 
		{
            if (t[ligne][colonne] > 0) 
			{  // la valeur positive représente une pièce noire
                nbPiecesNoires++;
            } 
			else if (t[ligne][colonne] < 0) 
			{  // la valeur négative représente une pièce blanche
                nbPiecesBlanches++;
            }
        }
    }
    if (nbPiecesBlanches == 1 && nbPiecesNoires == 1) 
	{
        return true;
    }
	else 
	{
        return false;
    }
}

int Plateau::nbCoupsPossibles(int couleur) 
{
    int nbCoups = 0;
    for (int i = 0; i < 8; i++) 
	{
        for (int j = 0; j < 8; j++) 
		{
            if (t[i][j] * couleur > 0) 
			{ // la couleur de la pièce est identifiée par la valeur de couleur
                // Vérifie chaque case que la pièce peut atteindre
                for (int l = 0; l < 8; l++) 
				{
                    for (int c = 0; c < 8; c++) 
					{
                        if (deroulement(i, j, l, c)) 
						{ // MouvementValide est une autre fonction qui vérifie si un mouvement est légal
                            nbCoups++;
                        }
                    }
                }
            }
        }
    }
    return nbCoups;
}

bool Plateau::Mate() 
{
    // Recherche si le roi blanc est en échec et s'il n'a pas de coups possibles
    if (RoiB() && nbCoupsPossibles(-1) == 0) 
	{
        return true;
    }
    // Recherche si le roi noir est en échec et s'il n'a pas de coups possibles
    if (RoiN() && nbCoupsPossibles(1) == 0) 
	{
        return true;
    }
    return false;
}

bool Plateau::Finpartie() 
{
    // Recherche s'il y a mat ou si la partie est nulle
    if (Mate()) 
	{
		cout<<"ECHEC ET MATE !"<<endl;
        return true;
        
    } 
	else if (Null()) 
	{
        return true;
    } 
	else 
	{
        return false;
    }
}


