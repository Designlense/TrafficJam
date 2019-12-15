

// Fichier : Route.cpp
//MIT Licence 
//Author : Rapha�l Mahiet 
//Website : designlense.io
//Hire Me : collaborate@designlense.io


// La route est divis�e en cellule correspondant � la place d'une voiture 
// (avec une distance de s�curit� envers les autres v�hicules)>n
// Une cellule comporte au plus une voiture.
// La route comporte MAX_CELLULES+1. 

// La route est donc un tableau de cellules comportant ou non des voitures.
// La cellule[0] sert de point d'entr�e des nouveaux v�hicules.


#include <iostream>
#include <cstdio>
#include "Route.h" 
#include "Voiture.h"
#include <vector>

using namespace std ;



const int MAX_CELLULES = 79;
const int EMPTY_CELL=-1 ; 

struct ROUTE {
int     nCelluleMax;
int		cellules[MAX_CELLULES+1];
} route ; 


// initRoute
int InitRoute(int nCelluleMax)
{

	nCelluleMax = nCelluleMax ; 
	nCelluleMax = max(0,nCelluleMax); 
	nCelluleMax = min (MAX_CELLULES,nCelluleMax);
	route.nCelluleMax = nCelluleMax ; 
	return route.nCelluleMax ; 
}



int CalculeDistanceSuivantRoute(int nPosition) 
{
   	int nDistance ; 
	int i ; 

   nDistance = 0 ; 
   for (  i=(nPosition+1)% (route.nCelluleMax+1) ; i!= nPosition ; i=(i+1)%(route.nCelluleMax+1), nDistance++)     
   {
      if (route.cellules[i])
        return (nDistance) ;  
   } ;
   return (route.nCelluleMax) ; 
}


// CalculePositionRoute : calcule la nouvelle position sur une route circulaire pour un deplacement de nDeplacement cellules.
//    le calcul se fait par modulo sur le nombre de cellules.
int CalculePositionRoute(int nPositionActuelle, int nDeplacement) 
{
		int nPositionCible ; 

  nPositionCible=(nPositionActuelle+nDeplacement)%(route.nCelluleMax+1) ;
  return (nPositionCible) ; 
}









// AjouteVoitureSurRoute : les voitures entrent par la case 0.
bool AjouteVoitureSurRoute(int nVinitial)  
{
  if (route.cellules[0])
    return (false) ;  
  route.cellules[0] = CreeVoiture (nVinitial,0) ;
  return (route.cellules[0]!=0) ;
}
  

// EnleveVoitureSurRoute : en pratique cela enleve la derniere voiture ins�r�.
int EnleveVoitureSurRoute()
{
	int nPosition =-1 ; 

   nPosition=SupprimeDerniereVoiture() ;
   if ((nPosition < 0) && (nPosition > route.nCelluleMax))
     return -1 ; 

   route.cellules[nPosition] = NULL ;
   return (nPosition) ; 
}


// ResetPositionRoute & SetPositionRoute permettent de mettre la position de la voiture sur la route
bool ResetPositionRoute(int nVoiture,int nPosition )
{		bool  bIncoherence ;
    
    bIncoherence =(route.cellules[nPosition] != nVoiture) ; 

	if (bIncoherence)
	  cout << "Attention il y a un probleme\n" ;   
	route.cellules[nPosition] = NULL ;
	return bIncoherence ; 
}

bool SetPositionRoute (int nVoiture, int nPosition)
{
		bool  bIncoherence ; 

    bIncoherence = (route.cellules[nPosition] != NULL) ; 
	if (bIncoherence)
	  cout << "Attention il y a un probleme\n" ;   
	route.cellules[nPosition] = nVoiture ;
	return bIncoherence; 
}


// AfficheRoute
void AfficheRoute ()
{
	int i ; 

  for ( i=0; i <=  route.nCelluleMax ; i++) AfficheVoiture(route.cellules[i]) ; 		
}


