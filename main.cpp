/*
Bonometti Francesco Pio e Filippo Compri
Battaglia navale
*/
const unsigned int n_elementi{5};	// Dichiarazione con lista di inizializzazione della costante globale n_elementi.
bool noAffondate = true;

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
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
	cout<<"Campo di battaglia: "<<endl;
	cout<<"    ";
	//for (char i = 65; i < (65 + n_elementi); i++) 	Stampa delle lettere
	for (int i = 0; i < n_elementi; i++)
	{
		cout<<i + 1<<" ";
	}
	cout<<endl<<"  # ";
	for (int i = 0; i < n_elementi; i++)
	{
		cout<<"# ";
	}
	cout<<endl;
	for (int i = 0; i < n_elementi; i++)
	{
		cout<<i + 1<<" # ";
		for (int j = 0; j < n_elementi; j++)
		{
			cout<<m[i][j]<<" ";
		}
		cout<<endl;
	}
}
void chiediColpi(Colpo &arrayColpi)
{
	string coords;
	recColpo colpoEseguito;
	while (coords[0] != '0')
	{
		cout<<"Inserisci le coordinate, separate da un ';': ";
		cin>>coords;
		colpoEseguito.indiceColonna = coords[0] - 48;	// Differenza Ascii.
		colpoEseguito.indiceRiga = coords[2] - 48; 		// Differenza Ascii.
		arrayColpi.push(colpoEseguito);		// Invocazione del metodo push sull'oggetto arrayColpi.
	}
}
void cercaNavi(recColpo colpo, unsigned int campo[][n_elementi], unsigned int counter[])
{
	unsigned int numeroLetto{campo[colpo.indiceRiga][colpo.indiceColonna]};
	if (numeroLetto != 0)
		counter[numeroLetto - 1]++;
	
}
void estraiColpi(Colpo &arrayColpi, unsigned int m[][n_elementi], unsigned int counterNavi[])
{
	recColpo colpoEstratto;
	for (int i = 0; i < arrayColpi.getLunghezza(); i++)
	{
		colpoEstratto = arrayColpi.pop();
		cercaNavi(colpoEstratto, m, counterNavi);
	}
}
void confrontoColpi(unsigned int counter[])
{
	for (int i = 0; i < 3; i++)
	{
		if (counter[i] % (i + 1) == 0)
		{
			noAffondate = false;
			cout<<"Nave da "<<i + 1<<" affondata!"<<endl;
		}
	}
	if (noAffondate)
		cout<<"Peccato! Nessuna nave e' stata colpita!"<<endl;
}

int main()
{
	unsigned int matrice[n_elementi][n_elementi] = {{0}}, contaNavi[3] = {0};
	Colpo colpi(n_elementi * n_elementi);
	leggiDalFile(matrice);
	stampaMatrice(matrice);
	chiediColpi(colpi);
	colpi.stampaCoda();
	estraiColpi(colpi, matrice, contaNavi);
	confrontoColpi(contaNavi);
	return 0;
}




//22-12-2020 ore 11:34 -> dammi 1 sec vado in bagno
