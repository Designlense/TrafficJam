// Fichier : Voiture.h
//MIT Licence 
//Author : Rapha�l Mahiet 
//Website : designlense.io
//Hire Me : collaborate@designlense.io


// Mod�lisation de la voiture
//    On va consid�rer que la voiture est caract�ris� par:
//    - sa vitesse
//    - Sa position, elle correspond � l'index sur la cellule correspondante dans la route


struct VOITURE  {
 	int	nVitesse ; 
    int	nCurrentPosition ;
	int	nOldPosition ; 

} ;


int CreeVoiture(int nVinitial, int nPosition) ; 


// IndiquePositionVoiture
int SupprimeDerniereVoiture() ; 



// AfficheVoiture: 
void AfficheVoiture(int nVoiture) ; 

// AccelereVoiture: 
//   Une voiture n'a pas d�j� atteint la vitesse max acc�l�re d'une unit�.
void AccelereVoiture(int nVoiture, int nVmax) ; 


// FreineSecuriteVoiture 
// Pour �viter l'accident, si une voiture � d cellules vides devant elle, et si sa vitesse v est plus grande que d, alors elle r�duit sa vitesse � d.
void FreineSecuriteVoiture(int nVoiture, int d) ; 


// EstNashVoiture renvoie vrai si l'al�a est vrai avec une probabilit� de nProbaP , conform�ment au mod�le Nash.
bool  EstNashVoiture(int nVoiture, int nProbaP); 


//  EstVdrVoiture renvoie vrai si l'al�a est vrai avec une probabilit� de nProbaQ si le v�hicule �tait immobile , et de nProbaP dans le cas contraire.
bool EstVdrVoiture (int nVoiture, int nProbaP, int nProbaQ) ; 



// RalentisVoiture
//  la vitesse de  la voiture est r�duite d'une unit� en fonction d'un al�a.
void RalentisVoiture (int nVoiture, bool bAlea);


// AvanceVoiture 
//  chaque voiture avance de n cases qui d�pend de sa vitesse
int AvanceVoiture (int nVoiture);


// ArchivePositionVoiture : la voiture conserve sa position pour l'utilisation par les fonctions isNash ou isVDR
void  ArchivePositionVoiture(int nVoiture, int nPosition) ; 


// CirculeVoiture : permet de faire les 4 �tapes.
void CirculeVoiture (int vMax,bool bFreinageNash,int nProbaP, int nProbaQ,bool bDebugMode) ;

