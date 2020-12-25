/*
Bonometti Francesco Pio e Filippo Compri
Battaglia navale
*/
const unsigned int n_elementi{5};	// Dichiarazione con lista di inizializzazione della costante globale n_elementi.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Colpi.h"
using namespace std;

/*
La funzione ritorna -1 se il file non è stato aperto correttamente, ritorna -2 se i dati sul file non sono
sufficienti e ritorna 0 se invece tutto è andato a buon fine.
*/
int leggiDalFile(unsigned int m[][n_elementi])
{
	ifstream fileCampo("campoBattaglia.txt");
	if (fileCampo.is_open() == false)
		return -1;
	for (int i = 0; i < n_elementi; i++)
	{
		for (int j = 0; j < n_elementi; j++)
		{
			fileCampo>>m[i][j];
			if (fileCampo.eof())
			{
				fileCampo.close();
				return -2;
			}
		}
	}
	fileCampo.close();
	return 0;
}
void stampaMatrice(unsigned int m[][n_elementi])
{
	cout<<"    ";
	for (int i = 0; i < n_elementi; i++)
	{
		cout<<i<<" ";
	}
	cout<<endl<<"  # ";
	for (int i = 0; i < n_elementi; i++)
	{
		cout<<"# ";
	}
	cout<<endl;
	for (int i = 0; i < n_elementi; i++)
	{
		cout<<i<<" # ";
		for (int j = 0; j < n_elementi; j++)
		{
			cout<<m[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main()
{
	unsigned int matrice[n_elementi][n_elementi] = {{0}}; 
	leggiDalFile(matrice);
	cout<<"Questo e' il campo di battaglia: "<<endl;
	stampaMatrice(matrice);
	return 0;
}




//22-12-2020 ore 11:34 -> dammi 1 sec vado in bagno
