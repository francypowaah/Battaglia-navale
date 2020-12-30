/*
Bonometti Francesco Pio e Filippo Compri
Battaglia navale
*/
const unsigned int n_elementi{5};	// Dichiarazione con lista di inizializzazione della costante globale n_elementi.
const unsigned int n_navi{3};		// Sono consentite navi grandi al massimo tre elementi.

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
	cout<<"o---o---o---o---o---o"<<endl;
	cout<<"Campo di battaglia "<<endl;
	cout<<"o---o---o---o---o---o"<<endl;
	cout<<"    ";
	//for (char i = 65; i < (65 + n_elementi); i++) 	Stampa delle lettere
	for (int i = 0; i < n_elementi; i++)	// Stampa degli indici di colonna.
	{
		cout<<i + 1<<" ";
	}
	cout<<endl<<"  # ";
	for (int i = 0; i < n_elementi; i++)	// Stampa dei caratteri separatori #.
	{
		cout<<"# ";
	}
	cout<<endl;
	for (int i = 0; i < n_elementi; i++)	
	{
		cout<<i + 1<<" # ";					// Stampa degli indici di riga.
		for (int j = 0; j < n_elementi; j++)
		{
			cout<<m[i][j]<<" ";				// Stampa della matrice.
		}
		cout<<endl;
	}
}
void chiediColpi(Colpo &arrayColpi)
{
	string coords;
	recColpo colpoEseguito;
	cout<<"o---o---o---o---o---o"<<endl;
	while (coords[0] != 'q' and coords[0] != 'Q')	// Il carattere q termina il ciclo di inserimento.
	{
		cout<<"Inserisci le coordinate, separate da un ';': ";
		cin>>coords;
		colpoEseguito.indiceRiga = coords[0] - 48;
		colpoEseguito.indiceColonna = coords[2] - 48;
		arrayColpi.push(colpoEseguito);		// Invocazione del metodo push sull'oggetto arrayColpi.
	}
	cout<<"o---o---o---o---o---o"<<endl;
}
void stampaEstratto(recColpo hit)
{
	cout<<"Colpo estratto: "<<endl;
	cout<<" Indice riga: "<<hit.indiceRiga<<endl;
	cout<<" Indice colonna: "<<hit.indiceColonna<<endl;
}
void cercaNave(recColpo hit, unsigned int c_navi[], unsigned int campo_battaglia[][n_elementi])
{
	unsigned int elementoMatrice{campo_battaglia[hit.indiceRiga][hit.indiceColonna]};
	cout<<"Ho estratto dalla matrice il numero "<<elementoMatrice<<endl;
	if (elementoMatrice != 0)
		c_navi[elementoMatrice - 1]++;
}
void estraiColpi(Colpo &arrayColpi, unsigned int counter[], unsigned int campo[][n_elementi])
{
	recColpo colpoEstratto;
	cout<<"o---o---o---o---o---o"<<endl;
	const unsigned int length = arrayColpi.getLunghezza();	// Memorizzo la lunghezza in una costante, perchè con le pop la lunghezza effettiva si ridurrà.
	for (int i = 0; i < length; i++)
	{
		colpoEstratto = arrayColpi.pop();
		stampaEstratto(colpoEstratto);
		cercaNave(colpoEstratto, counter, campo);
	}
}
void stampaEsito(unsigned int counter[])
{
	bool noAffondate{true};
	cout<<"o---o---o---o---o---o"<<endl;
	for (int i = 0; i < n_navi; i++)
	{
		if (counter[i] == i + 1)
		{
			cout<<"Nave da "<<i + 1<<" affondata!"<<endl;
			noAffondate = false;
		}	
	}
	if (noAffondate)
			cout<<"Peccato, nessuna nave e' stata affondata."<<endl;
	cout<<"o---o Developed by Bonometti Francesco Pio & Compri Filippo o---o"<<endl;
}

int main()
{
	unsigned int matrice[n_elementi][n_elementi] = {{0}}, contaNavi[n_navi] = {0};
	Colpo colpi(n_elementi * n_elementi);
	leggiDalFile(matrice);
	stampaMatrice(matrice);
	chiediColpi(colpi);
	colpi.stampaCoda();
	estraiColpi(colpi, contaNavi, matrice);
	stampaEsito(contaNavi);
	return 0;
}




//22-12-2020 ore 11:34 -> dammi 1 sec vado in bagno
