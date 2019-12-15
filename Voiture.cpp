
// fichier : voiture.cpp
//MIT Licence 
//Author : Raphaël Mahiet 
//Website : designlense.io
//Hire Me : collaborate@designlense.io

// Hypothèses : la voiture est identifié par son numéro qui joue le rôle de plaque d'immatriculation.



#include <iostream>
#include <cstdlib>
#include <vector>
#include "Voiture.h"
#include "Route.h"

using namespace std ;
	

vector <VOITURE >  Trafic ; 



// CreeVoiture : renvoie un numéro de voiture


int CreeVoiture(int nVinitial, int nPosition)
{
   VOITURE voiture ; 

 voiture.nVitesse=nVinitial ; 
 voiture.nCurrentPosition = nPosition ; 
 voiture.nOldPosition=nPosition ;
 Trafic.push_back(voiture) ;
 
    return ( (int) Trafic.size()) ;  
}

  
int SupprimeDerniereVoiture()
{
		int		nPosition ; 
  if (Trafic.size())
  {
	nPosition = Trafic[Trafic.size()-1].nCurrentPosition ; 
	Trafic.pop_back() ; 
	return (nPosition) ;
  } ;
  return (-1) ; 
}




// AfficheVoiture: 

void AfficheVoiture(int nVoiture)
{
  if (nVoiture)
  {
     if (nVoiture <= (int)Trafic.size())
	   cout << Trafic[nVoiture-1].nVitesse ;
	 else
	   cout << "E" ;  // Il s'agit d'une erreur 
  }
  else
     cout << "X" ;  // Pas de voiture.

} ;


// AccelereVoiture: 
//   Une voiture n'a pas déjà atteint la vitesse max,  accélère d'une unité.


void AccelereVoiture(int nVoiture, int nVmax)
{
		int nVitesse ;
  if (nVoiture)
  {
	nVitesse = Trafic[nVoiture-1].nVitesse+1 ; 
    Trafic[nVoiture-1].nVitesse=min(nVitesse,nVmax) ;
  }
}



// FreineSecuriteVoiture 
// Pour éviter l'accident, si une voiture à d cellules vides devant elle, et si sa vitesse v est plus grande que d, alors elle réduit sa vitesse à d.

void FreineSecuriteVoiture(int nVoiture, int d)
{
		int nVitesse ;
    if (nVoiture) 
	{
	  nVitesse=Trafic[nVoiture-1].nVitesse ; 
      Trafic[nVoiture-1].nVitesse=min(nVitesse,d) ; 
	}
}




// EstNashVoiture renvoie vrai si l'aléa est vrai avec une probabilité de nProbaP , conformément au modèle Nash.

bool  EstNashVoiture (int nVoiture, int nProbaP)
{
	double alea ; // double pour éviter les débordements.
	double aleaSeuil; 
	
	alea=rand() ; 
	aleaSeuil = ((double) nProbaP)*RAND_MAX ; 
	aleaSeuil /= 100 ;
	return (alea < aleaSeuil) ;
}



//  EstVdrVoiture renvoie vrai si l'aléa est vrai avec une probabilité de nProbaQ si le véhicule Ètait immobile , et de nProbaP dans le cas contraire.

bool EstVdrVoiture (int nVoiture, int nProbaP, int nProbaQ)
{
  if (!nVoiture)
    return false ; 
  return EstNashVoiture(nVoiture, 
	                  (Trafic[nVoiture-1].nCurrentPosition == Trafic[nVoiture-1].nOldPosition)?nProbaQ : nProbaP) ;
}



// RalentisVoiture
//  la vitesse de  la voiture est réduite d'une unité en fonction d'un aléa.


void RalentisVoiture (int nVoiture, bool bAlea)
{
  if (nVoiture)
  { 
    if (bAlea && Trafic[nVoiture-1].nVitesse)
      Trafic[nVoiture-1].nVitesse-- ;
  } ;
}



// AvanceVoiture 
//  chaque voiture avance de n cases qui dépend de sa vitesse
 

int AvanceVoiture (int nVoiture)
{
 if (!nVoiture)
   return 0 ; 

 return Trafic[nVoiture-1].nVitesse ;     
}


// ArchivePositionVoiture : la voiture conserve sa position pour l'utilisation par les fonctions isNash ou isVDR


void  ArchivePositionVoiture(int nVoiture, int nPosition)
{
  if (nVoiture)
  {
    Trafic[nVoiture-1].nOldPosition= Trafic[nVoiture-1].nCurrentPosition ; 
    Trafic[nVoiture-1].nCurrentPosition = nPosition ; 
  }
}


void CirculeVoiture (int nVmax, bool bFreinageNash,int nProbaP, int nProbaQ,bool bDebugMode)  
{
    
		int nVoiture ; // numéro , index de la voiture sur le vector Trafic.
    int nVoitureMax = (int) Trafic.size();
    

  // ETAPE 1 : accélération
  if (bDebugMode)  { AfficheRoute() ; cout << "  <- 0-t\n" ; } ; 
  for (nVoiture=1 ; nVoiture<=nVoitureMax ; nVoiture++)
     AccelereVoiture(nVoiture,nVmax) ; 
  if (bDebugMode)  { AfficheRoute() ; cout << "  <- 1-Acceleration\n";  } ; 
  
    // ETAPE 2 : freinage de sécurité
  for (nVoiture=1 ; nVoiture<=nVoitureMax ; nVoiture++) 
	 FreineSecuriteVoiture(nVoiture, CalculeDistanceSuivantRoute(Trafic[nVoiture-1].nCurrentPosition)) ; 
  if (bDebugMode)  { AfficheRoute() ; cout << "  <- 2-Freinage securite\n";  } ; 
 
    // ETAPE 3 : freinage Aléatoire
  for (nVoiture=1 ; nVoiture<=nVoitureMax ; nVoiture++) 
  { 
	  bool	bFreinage ; 
    bFreinage = (bFreinageNash)? EstNashVoiture(nVoiture, nProbaP) : EstVdrVoiture(nVoiture, nProbaP, nProbaQ) ; 
    RalentisVoiture(nVoiture,bFreinage) ;  
  } ;
  if (bDebugMode)  { AfficheRoute() ; cout << "  <- 3-Freinage aleatoire\n" ; } ; 
  
    // ETAPE 4-1 : on se prépare au mouvement , les anciens emplacements sur la route sont mis à zéro.
  for (nVoiture=1 ; nVoiture<= nVoitureMax ; nVoiture++ )
  {
		int nNewPosition ; 
		int nCurrentPosition ;
    	  	  // calcul de la nouvelle position sur une route circulaire
	 nCurrentPosition = Trafic[nVoiture-1].nCurrentPosition ; 
	 nNewPosition= CalculePositionRoute(nCurrentPosition,AvanceVoiture(nVoiture)) ; 
	 ArchivePositionVoiture(nVoiture,nNewPosition) ;
	 ResetPositionRoute(nVoiture, nCurrentPosition) ; 
  }
  // ETAPE 4-2 : on met à jours les nouvelles positions.
  for (nVoiture=1 ; nVoiture<= nVoitureMax ; nVoiture++ )
  {
	  SetPositionRoute(nVoiture, Trafic[nVoiture-1].nCurrentPosition) ; 
  }
	
  if (bDebugMode)  { AfficheRoute() ; cout << "  <- 4-t+1\n";  } ; 
}


