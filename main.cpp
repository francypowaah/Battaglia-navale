/*
Bonometti Francesco Pio e Filippo Compri
Battaglia navale
*/
const unsigned int n_elementi{10};	// Dichiarazione con lista di inizializzazione della costante globale n_elementi.
const unsigned int n_navi{5};		// Sono consentite navi grandi al massimo tre elementi.
const unsigned int max_len{5};		// Dimensione massima della stringa coords.
bool noAffondate{true};

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
	cout<<"     ";
	for (char i = 65; i < 65 + n_elementi; i++)
	//for (int i = 0; i < n_elementi; i++)
	{
		cout<<i<<" ";
	}
	cout<<endl<<"   # ";
	for (int i = 0; i < n_elementi; i++)	// Stampa dei caratteri separatori #.
	{
		cout<<"# ";
	}
	cout<<endl;
	for (int i = 0; i < n_elementi; i++)	
	{
		if (i != (n_elementi - 1))
			cout<<i + 1<<"  # ";					// Stampa degli indici di riga.
		else
			cout<<i + 1<<" # ";
		
		for (int j = 0; j < n_elementi; j++)
		{
			cout<<m[i][j]<<" ";				// Stampa della matrice.
		}
		cout<<endl;
	}
}
void estraiElemento(char stringa_in[], char stringa_out[])
{
	int i{0}, j{0}, k{0};
	for (i = 0; stringa_in[i] != '\0' && stringa_in[i] != ';' && j < max_len; i++);
	for (j = 0; j < i; j++)
		stringa_out[j] = stringa_in[j];
	stringa_out[j] = '\0';
	for (j = i + 1; stringa_in[j] != '\0' && stringa_in[j] != ';' && j < max_len; j++)
	{
		stringa_in[k] = stringa_in[j];
		k++;
	}
}

void chiediColpi(Colpo &arrayColpi)
{
	char coords[max_len] = {'\0'}, element[max_len] = {'\0'};
	bool prosegui{true};
	recColpo colpoEseguito;
	cout<<"o---o---o---o---o---o"<<endl;
	while (prosegui)
	{
		cout<<"Inserisci le coordinate, separate da un ';': ";
		cin>>coords;
		if (coords[0] == 'q' or coords[0] == 'Q')
		{
			prosegui = false;	// Il carattere q termina il ciclo di inserimento.
		}
		else
		{
			estraiElemento(coords, element);
			//colpoEseguito.indiceRiga = atoi(element);
			colpoEseguito.indiceColonna = element[0] - 64;	// Conversione della lettera da Ascii a int.
			estraiElemento(coords, element);
			colpoEseguito.indiceRiga = atoi(element);
			//cout<<"Indice colonna: "<<colpoEseguito.indiceColonna<<endl;
			//cout<<"Indice riga: "<<colpoEseguito.indiceRiga<<endl;
			arrayColpi.push(colpoEseguito);		// Invocazione del metodo push sull'oggetto arrayColpi.
		}
		
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
void contatoreNavi(unsigned int num, int idx)
{
	bool check{true};
	int j{0};
	while (check)
	{
		j+=idx + 1;
		if (j <= num)
		{
			cout<<"Nave da "<<idx + 1<<" affondata!"<<endl;
			noAffondate = false;
		}
		if (j >= num)
			check = false;
	}
}
void stampaEsito(unsigned int counter[])
{
	cout<<"o---o---o---o---o---o"<<endl;
	for (int i = 0; i < n_navi; i++)
	{
		cout<<"Counter["<<i<<"]:"<<counter[i]<<endl;
		contatoreNavi(counter[i], i);
	}
	if (noAffondate)
			cout<<"Peccato, nessuna nave e' stata affondata."<<endl;
	cout<<"o---o Developed by Bonometti Francesco Pio & Compri Filippo o---o"<<endl;
}
int main()
{
	
	unsigned int matrice_pc[n_elementi][n_elementi] = {{0}}, contaNavi[n_navi] = {0};
	Colpo colpi(n_elementi * n_elementi);
	leggiDalFile(matrice_pc);
	stampaMatrice(matrice_pc);
	chiediColpi(colpi);
	colpi.stampaCoda();
	estraiColpi(colpi, contaNavi, matrice_pc);
	stampaEsito(contaNavi);
	return 0;
}




//22-12-2020 ore 11:34 -> dammi 1 sec vado in bagno
