
// Fichier : Route.h
//  Raphaël MAHIET


// La route est divisée en cellule correspondant à la place d'une voiture 
// (avec une distance de sécurité envers les autres véhicules)>n
// Une cellule comporte au plus une voiture.
// La route comporte MAX_CELLULES+1. 

// La route est donc un tableau de cellules comportant ou non des voitures.
// La cellule[0] sert de point d'entrée des nouveaux véhicules.



int InitRoute(int nCelluleMax) ; 
int CalculeDistanceSuivantRoute(int nPosition) ;


// AjouteVoitureSurRoute & EnleveVoitureSurRoute
bool AjouteVoitureSurRoute(int nVinitial) ;
int EnleveVoitureSurRoute() ;

// Fonctions pour mettre à jour la position de la voiture nVoiture sur la route.
bool ResetPositionRoute(int nVoiture,int nPosition ) ; 
bool SetPositionRoute (int nVoiture, int nPosition) ; 
int CalculePositionRoute(int nPositionActuelle, int nDeplacement) ;

// AfficheRoute
void AfficheRoute () ;

