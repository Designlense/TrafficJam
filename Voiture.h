// Fichier : Voiture.h
//MIT Licence 
//Author : Raphaël Mahiet 
//Website : designlense.io
//Hire Me : collaborate@designlense.io


// Modélisation de la voiture
//    On va considérer que la voiture est caractérisé par:
//    - sa vitesse
//    - Sa position, elle correspond à l'index sur la cellule correspondante dans la route


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
//   Une voiture n'a pas déjà atteint la vitesse max accélère d'une unité.
void AccelereVoiture(int nVoiture, int nVmax) ; 


// FreineSecuriteVoiture 
// Pour éviter l'accident, si une voiture à d cellules vides devant elle, et si sa vitesse v est plus grande que d, alors elle réduit sa vitesse à d.
void FreineSecuriteVoiture(int nVoiture, int d) ; 


// EstNashVoiture renvoie vrai si l'aléa est vrai avec une probabilité de nProbaP , conformément au modèle Nash.
bool  EstNashVoiture(int nVoiture, int nProbaP); 


//  EstVdrVoiture renvoie vrai si l'aléa est vrai avec une probabilité de nProbaQ si le véhicule était immobile , et de nProbaP dans le cas contraire.
bool EstVdrVoiture (int nVoiture, int nProbaP, int nProbaQ) ; 



// RalentisVoiture
//  la vitesse de  la voiture est réduite d'une unité en fonction d'un aléa.
void RalentisVoiture (int nVoiture, bool bAlea);


// AvanceVoiture 
//  chaque voiture avance de n cases qui dépend de sa vitesse
int AvanceVoiture (int nVoiture);


// ArchivePositionVoiture : la voiture conserve sa position pour l'utilisation par les fonctions isNash ou isVDR
void  ArchivePositionVoiture(int nVoiture, int nPosition) ; 


// CirculeVoiture : permet de faire les 4 Ètapes.
void CirculeVoiture (int vMax,bool bFreinageNash,int nProbaP, int nProbaQ,bool bDebugMode) ;

