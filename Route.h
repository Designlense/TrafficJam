
// Fichier : Route.h
//  Rapha�l MAHIET


// La route est divis�e en cellule correspondant � la place d'une voiture 
// (avec une distance de s�curit� envers les autres v�hicules)>n
// Une cellule comporte au plus une voiture.
// La route comporte MAX_CELLULES+1. 

// La route est donc un tableau de cellules comportant ou non des voitures.
// La cellule[0] sert de point d'entr�e des nouveaux v�hicules.



int InitRoute(int nCelluleMax) ; 
int CalculeDistanceSuivantRoute(int nPosition) ;


// AjouteVoitureSurRoute & EnleveVoitureSurRoute
bool AjouteVoitureSurRoute(int nVinitial) ;
int EnleveVoitureSurRoute() ;

// Fonctions pour mettre � jour la position de la voiture nVoiture sur la route.
bool ResetPositionRoute(int nVoiture,int nPosition ) ; 
bool SetPositionRoute (int nVoiture, int nPosition) ; 
int CalculePositionRoute(int nPositionActuelle, int nDeplacement) ;

// AfficheRoute
void AfficheRoute () ;

