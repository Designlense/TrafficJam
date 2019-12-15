// Projet circulation.cpp : définit le point d'entrée pour l'application console.
//

// Raf : attention Visual cpp à supprimer.

// Raf :  fin attention Visual cpp 

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <math.h>

#include <stdlib.h>

#include "Route.h" 
#include "Voiture.h"



using namespace std ;

const int NB_ROUTE_CELLULES = 79 ;

/*
 * Paramètres globaux que l'on saisira en début de programme pour faciliter la mise au point 
 *
 */
struct {
	int	nVmax	; 
	int nVinitial; 
    int	nEtape ; 
	int	nRouteCellMax ; 
	bool bFreinageNash ;
	int	nProbaP ; 
	int	nProbaQ ;
	bool bDebugMode ; 
}     ControleTrafic = {
	5 ,  // Vitesse max  5 cellules / 2 secondes
	1 , // vitesse initial
	1, 	 
	7, 
	true ,   // Freinage Nash
	10, 
	10,
	true
} ;	

	
// AfficheControleTrafic
//
//
void AfficheControleTrafic ( )
{
  cout <<" " << ControleTrafic.nEtape ; 
  if (ControleTrafic.bFreinageNash)
     cout << "Nash:"  << ControleTrafic.nProbaP ; 
  else
     cout << "VDR:" <<ControleTrafic.nProbaP <<"/" <<ControleTrafic.nProbaQ ;
  cout << "\n" ; 
}



int mainStandard(int argc, _TCHAR* argv[])
{
	char	szEntry[80] ;

  InitRoute(ControleTrafic.nRouteCellMax) ; 

  for (;true;)   // boucle forever
  {
   cout << "Entrer la commande" << "\n" ; 
   cin >> szEntry ;
   switch(szEntry[0]) 
   {
   case 'C' : 
		cout << "Etat du controle du trafic \n" ; 
		cout << "Parametre NaSh P : " << ControleTrafic.nProbaP << endl ; 
		cout << "Parametre VDR Q : " << ControleTrafic.nProbaP << endl ; 
		cout << "Reduction de la route à : " << ControleTrafic.nRouteCellMax+1 << endl ;
		if (ControleTrafic.bFreinageNash) 
		   cout << "Mode de freinage : Nash " << endl ; 
		else
		   cout << "Mode de freinage : VDR " << endl ; 
		cout << "Nombre de groupe d'etapes" << ControleTrafic.nEtape << endl ; 
		cout << "Vitesse maximale en cellules par 2 secondes " << ControleTrafic.nVmax << endl ; 
		cout << "Mode debug = " << ControleTrafic.bDebugMode << endl ; 
		break ; 
    case 'D' :
	case 'd' : 
					// 'D','d'  = Display
		AfficheRoute();
		AfficheControleTrafic() ; 
		break ; 
	case 'B' : 
	case 'b' :
		ControleTrafic.bDebugMode = (szEntry[0]== 'B') ; 
		break ; 
	case 'H' : 
	case 'h' :
		cout << "D/d: mode debug \n" ; 
		cout << "M/m: mode de freinage M=Nash/m=VDR\n" ;
		cout << "N/n: voiture en plus (N) en moins (n)\n" ;
		cout << "P/p: proba P + 10% (P) -10% (p)\n" ; 
		cout << "Q/q: proba Q + 10% (Q) -10% (q)\n" ;
		cout << "R : run lance un step \n" ;
		cout << "S/s: nombre d'étapes +1 (S) / -1 (S)\n" ;
		cout << "T/t: nombre de cellules dans la route +1 (T) / -1 (t)\n" ; 
		cout << "C:  contrôle du trafic \n"; 
		break;

    case 'M' : 
    case 'm' : 
	   ControleTrafic.bFreinageNash=(szEntry[0] == 'M') ;
	   cout << "contrôle du freinage" << "\n" ; 
	   break ;
   
	case 'N':    // si l'entrée de la route est libre on ajoute une voiture)
	  if (!AjouteVoitureSurRoute(ControleTrafic.nVinitial))
	    cout << "entrée saturée \n" ;
	  else
	    cout <<"Voiture ajoutée\n" ;
				// break omis à dessein.
    case 'n' :  
      if (szEntry[0] == 'n') 
	  {
		  int nVoiture ;
		nVoiture =EnleveVoitureSurRoute() ;
		cout << "Voiture enlevée\n" << nVoiture << endl ; 
	  }
	case 'R' : 
      for (int i=0; i < ControleTrafic.nEtape ; i++)
        CirculeVoiture (ControleTrafic.nVmax,ControleTrafic.bFreinageNash,ControleTrafic.nProbaP,ControleTrafic.nProbaQ,ControleTrafic.bDebugMode) ; 
      AfficheRoute() ;  
	  AfficheControleTrafic() ; 
      break ;
      
	case 'P' :    
	  ControleTrafic.nProbaP += 10 ; 
      ControleTrafic.nProbaP = min(ControleTrafic.nProbaP,100) ; 
	  cout << "Proba P augmentée" << "\n" ;
      break ; 
	case 'p' :
	  ControleTrafic.nProbaP -= 10 ;
	  ControleTrafic.nProbaP = max(ControleTrafic.nProbaP,0) ; 
	  cout << "Proba P diminuée" << "\n" ;
	  break ; 

	case 'Q' : 
	  ControleTrafic.nProbaQ += 10 ; 
	  ControleTrafic.nProbaQ = min(ControleTrafic.nProbaQ,100) ; 
	  cout << "Proba Q augmenté" << "\n" ;
	  break ; 
	case 'q' :
	  ControleTrafic.nProbaQ -= 10 ;
	  ControleTrafic.nProbaQ = max(ControleTrafic.nProbaQ,0) ; 
	  cout << "Proba Q diminué" << "\n" ;
      break ; 

	case 'S' : 
	  ControleTrafic.nEtape++ ;
	  cout << "Une étape de plus" << "\n" ; 
	  break ;   
	case 's' : 
	  if (ControleTrafic.nEtape) ControleTrafic.nEtape-- ; 
	  cout << "Une étape de moins" << "\n" ; 
      break ; 

    case 'T' : 	// Taille de la route 
	  ControleTrafic.nRouteCellMax=	InitRoute(ControleTrafic.nRouteCellMax+1) ;				 
	  break ; 

	case 't' :  
	  ControleTrafic.nRouteCellMax=	InitRoute(ControleTrafic.nRouteCellMax-1) ;				 
	  break ; 
    case '.' : 
	  return 0 ; 	
	default :
	  break ;
   } ;
 }
 return 0;
}





