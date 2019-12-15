
// fichier : voiture.cpp
//MIT Licence 
//Author : Rapha�l Mahiet 
//Website : designlense.io
//Hire Me : collaborate@designlense.io

// Hypoth�ses : la voiture est identifi� par son num�ro qui joue le r�le de plaque d'immatriculation.



#include <iostream>
#include <cstdlib>
#include <vector>
#include "Voiture.h"
#include "Route.h"

using namespace std ;
	

vector <VOITURE >  Trafic ; 



// CreeVoiture : renvoie un num�ro de voiture


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
//   Une voiture n'a pas d�j� atteint la vitesse max,  acc�l�re d'une unit�.


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
// Pour �viter l'accident, si une voiture � d cellules vides devant elle, et si sa vitesse v est plus grande que d, alors elle r�duit sa vitesse � d.

void FreineSecuriteVoiture(int nVoiture, int d)
{
		int nVitesse ;
    if (nVoiture) 
	{
	  nVitesse=Trafic[nVoiture-1].nVitesse ; 
      Trafic[nVoiture-1].nVitesse=min(nVitesse,d) ; 
	}
}




// EstNashVoiture renvoie vrai si l'al�a est vrai avec une probabilit� de nProbaP , conform�ment au mod�le Nash.

bool  EstNashVoiture (int nVoiture, int nProbaP)
{
	double alea ; // double pour �viter les d�bordements.
	double aleaSeuil; 
	
	alea=rand() ; 
	aleaSeuil = ((double) nProbaP)*RAND_MAX ; 
	aleaSeuil /= 100 ;
	return (alea < aleaSeuil) ;
}



//  EstVdrVoiture renvoie vrai si l'al�a est vrai avec une probabilit� de nProbaQ si le v�hicule �tait immobile , et de nProbaP dans le cas contraire.

bool EstVdrVoiture (int nVoiture, int nProbaP, int nProbaQ)
{
  if (!nVoiture)
    return false ; 
  return EstNashVoiture(nVoiture, 
	                  (Trafic[nVoiture-1].nCurrentPosition == Trafic[nVoiture-1].nOldPosition)?nProbaQ : nProbaP) ;
}



// RalentisVoiture
//  la vitesse de  la voiture est r�duite d'une unit� en fonction d'un al�a.


void RalentisVoiture (int nVoiture, bool bAlea)
{
  if (nVoiture)
  { 
    if (bAlea && Trafic[nVoiture-1].nVitesse)
      Trafic[nVoiture-1].nVitesse-- ;
  } ;
}



// AvanceVoiture 
//  chaque voiture avance de n cases qui d�pend de sa vitesse
 

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
    
		int nVoiture ; // num�ro , index de la voiture sur le vector Trafic.
    int nVoitureMax = (int) Trafic.size();
    

  // ETAPE 1 : acc�l�ration
  if (bDebugMode)  { AfficheRoute() ; cout << "  <- 0-t\n" ; } ; 
  for (nVoiture=1 ; nVoiture<=nVoitureMax ; nVoiture++)
     AccelereVoiture(nVoiture,nVmax) ; 
  if (bDebugMode)  { AfficheRoute() ; cout << "  <- 1-Acceleration\n";  } ; 
  
    // ETAPE 2 : freinage de s�curit�
  for (nVoiture=1 ; nVoiture<=nVoitureMax ; nVoiture++) 
	 FreineSecuriteVoiture(nVoiture, CalculeDistanceSuivantRoute(Trafic[nVoiture-1].nCurrentPosition)) ; 
  if (bDebugMode)  { AfficheRoute() ; cout << "  <- 2-Freinage securite\n";  } ; 
 
    // ETAPE 3 : freinage Al�atoire
  for (nVoiture=1 ; nVoiture<=nVoitureMax ; nVoiture++) 
  { 
	  bool	bFreinage ; 
    bFreinage = (bFreinageNash)? EstNashVoiture(nVoiture, nProbaP) : EstVdrVoiture(nVoiture, nProbaP, nProbaQ) ; 
    RalentisVoiture(nVoiture,bFreinage) ;  
  } ;
  if (bDebugMode)  { AfficheRoute() ; cout << "  <- 3-Freinage aleatoire\n" ; } ; 
  
    // ETAPE 4-1 : on se pr�pare au mouvement , les anciens emplacements sur la route sont mis � z�ro.
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
  // ETAPE 4-2 : on met � jours les nouvelles positions.
  for (nVoiture=1 ; nVoiture<= nVoitureMax ; nVoiture++ )
  {
	  SetPositionRoute(nVoiture, Trafic[nVoiture-1].nCurrentPosition) ; 
  }
	
  if (bDebugMode)  { AfficheRoute() ; cout << "  <- 4-t+1\n";  } ; 
}


