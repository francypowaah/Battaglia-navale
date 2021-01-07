/*
Bonometti Francesco Pio e Filippo Compri
Battaglia navale
*/
const unsigned int n_elementi{10};	// Dichiarazione con lista di inizializzazione della costante globale n_elementi.
const unsigned int dim_navi{5};		// Sono consentite navi grandi al massimo tre elementi.
const unsigned int max_len{5};		// Dimensione massima della stringa coords.
const unsigned int n_navi{5};		// Numero di navi disposte sulla plancia di gioco.
bool noAffondate{true};
bool matrice_parallela[n_elementi][n_elementi] = {{false}};	// Matrice parallela da scorrere.

struct recCoordinate
{
	unsigned int riga;
	unsigned int colonna;	
};
struct recNave
{
	unsigned int lung_nave;
	recCoordinate coordinate_nave[dim_navi];
	bool trovati[dim_navi] = {false};
};

#include <vector> // Vettori (array con lunghezza variabile a run-time).
using namespace std;

vector <recNave> v_coordinate(0);
bool compara_navi(recNave a, recNave b) { return a.lung_nave < b.lung_nave; }	// Funzione utilizzata per il sort. 

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cstring> // Libreria stringhe.
#include <algorithm> // Libreria all'interno del quale è inclusa la funzione sort, che migliora di netto le tempistiche del bubbleSort, quickSort ed exchangeSort.
#include "Colpi.h"
#include "ricerca_navi.h"
#include "colpi_in_out.h"
#include "funzioni_stampa.h"
#include "lettura.h"

int main()
{
	unsigned int matrice_pc[n_elementi][n_elementi] = {{0}};
	Colpo colpi(n_elementi * n_elementi);
	srand(time(NULL));
	if (stampaMessaggio(leggiDalFile(matrice_pc)))
	{
		stampaMatrice(matrice_pc); // Funzione di stampa della plancia di gioco.
		chiediColpi(colpi);	// Funzione d'inserimento delle coordinate dei colpi da parte dell'utente.
		ricercaCoordinate(matrice_pc);
		sort(v_coordinate.begin(), v_coordinate.end(), compara_navi); // Sort utilizzando la funzione compara_navi.
		estraiColpi(colpi, matrice_pc);	// Funzione d'estrazione dei colpi dalla coda.
		stampaEsito(); // Stampa delle navi affondate.*/
		stampaPunteggio();
		return 0;
	}
}
