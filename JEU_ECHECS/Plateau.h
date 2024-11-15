#ifndef PLATEAU_H
#define PLATEAU_H

class Plateau
{
	public:
		Plateau();
		~Plateau();
		int getIndice(int,int);
		int movpion(int ld,int cd,int la,int ca);
		int finpartie();
		int firstmoveN(int ld,int cd,int la,int ca);
		int firstmoveB(int ld,int cd,int la,int ca);
		int deroulement(int ld,int cd,int la,int ca);
		void Promotion(int ld, int cd, int la, int ca);
		void afficher();
		int movtour(int ld,int cd,int la,int ca);
		int movcavalier(int ld,int cd,int la,int ca);
		int movfou(int ld,int cd,int la,int ca);
		int movdame(int ld,int cd,int la,int ca);
		int movroi(int ld,int cd,int la,int ca);
		int chlibretour(int ld,int cd,int la,int ca);
		int chlibrefou(int ld, int cd, int la, int ca);
		int chlibredame(int ld, int cd, int la, int ca);
		void RoockNoir(int ld , int cd , int la , int ca);
		void RoockBlanc(int ld , int cd ,int la,int ca);
		void PriseEnPassant(int ld , int cd ,int la,int ca);
		void Save(int joueur);
		void Load(int &joueur);
		bool RoiB();
		bool RoiN();
		bool Null();
		bool Mate();
		bool Finpartie();
		int nbCoupsPossibles(int joueur);
		bool CheckRoiBlanc(int line , int colonne);
		bool CheckRoiNoir(int line , int colonne);
		void afficherPlateau();
		
		////////////
		int nbPiecesIA();
		int nbPiecesAdversaire();
	private:
		int t[8][8];
};

#endif
