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
	cout<<"o---o---o---o---o---o---o"<<endl;
	cout<<"Campo di battaglia "<<endl;
	cout<<"o---o---o---o---o---o---o"<<endl;
	cout<<"     ";
	for (char i = 65; i < 65 + n_elementi; i++)	// Stampa degli indici di colonna.
		cout<<i<<" ";
	cout<<endl<<"   # ";
	for (int i = 0; i < n_elementi; i++) // Stampa dei caratteri separatori #.
	{
		cout<<"# ";
	}
	cout<<endl;
	for (int i = 0; i < n_elementi; i++)	
	{
		if (i != (n_elementi - 1))
			cout<<i + 1<<"  # "; // Stampa degli indici di riga.
		else
			cout<<i + 1<<" # ";
		
		for (int j = 0; j < n_elementi; j++)
		{
			cout<<m[i][j]<<" "; // Stampa della matrice.
		}
		cout<<endl;
	}
}
void estraiElemento(char stringa_in[], char stringa_out[]) // Estrazione degli indici di riga e colonna inseriti dall'utente.
{
	int i{0}, j{0}, k{0};
	for (i = 0; stringa_in[i] != '\0' && stringa_in[i] != ';' && i < max_len; i++);
	for (j = 0; j < i; j++)
		stringa_out[j] = stringa_in[j];
	stringa_out[j] = '\0';
	for (j = i + 1; j < max_len; j++)
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
	cout<<"o---o---o---o---o---o---o"<<endl;
	while (prosegui)
	{
		cout<<"Inserisci le coordinate, separate da un ';': ";
		cin>>coords;
		if (coords[0] == 'q' or coords[0] == 'Q')
		{
			prosegui = false; // Il carattere q termina il ciclo di inserimento.
		}
		else
		{
			estraiElemento(coords, element);
			colpoEseguito.indiceColonna = element[0] - 64; // Conversione della lettera da Ascii a int.
			estraiElemento(coords, element);
			colpoEseguito.indiceRiga = atoi(element);
			arrayColpi.push(colpoEseguito);	// Invocazione del metodo push sull'oggetto arrayColpi, secondo la logica della coda.
		}
	}
	cout<<"o---o---o---o---o---o---o"<<endl;
}
void stampaEstratto(recColpo hit) // Stampa del colpo estratto dalla coda mediante invocazione del metodo pop.
{
	cout<<"Colpo estratto: "<<endl;
	cout<<" Indice riga: "<<hit.indiceRiga<<endl;
	cout<<" Indice colonna: "<<hit.indiceColonna<<endl;
}
void cercaNave(recColpo hit, unsigned int c_navi[], unsigned int campo_battaglia[][n_elementi])	// Funzione di ricerca della nave.
{
	unsigned int elementoMatrice{campo_battaglia[hit.indiceRiga][hit.indiceColonna]};
	cout<<"Ho estratto dalla matrice il numero "<<elementoMatrice<<endl;
	if (elementoMatrice != 0)
		c_navi[elementoMatrice - 1]++;
}
void estraiColpi(Colpo &arrayColpi, unsigned int counter[], unsigned int campo[][n_elementi]) // Funzione di estrazione dei colpi dalla coda.
{
	recColpo colpoEstratto;
	cout<<"o---o---o---o---o---o---o"<<endl;
	const unsigned int length = arrayColpi.getLunghezza(); // Memorizzo la lunghezza in una costante, perchè con le pop la lunghezza effettiva si ridurrà.
	for (int i = 0; i < length; i++)
	{
		colpoEstratto = arrayColpi.pop();
		stampaEstratto(colpoEstratto);
		cercaNave(colpoEstratto, counter, campo);
	}
}
void contatoreNavi(unsigned int num, int idx) // Contatore delle navi affondate (ricerca dei multipli di un numero ottimizzata nei tempi).
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
void stampaEsito(unsigned int counter[]) // Funzione di stampa delle navi affondate.
{
	cout<<"o---o---o---o---o---o---o"<<endl;
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
	bool print{true};	// Variabile booleana per determinare la stampa della matrice o meno, in presenza di numero insufficiente di dati.
	Colpo colpi(n_elementi * n_elementi);
	switch(leggiDalFile(matrice_pc))
	{
		case 0:
			cout<<"Lettura del file eseguita con successo!"<<endl;
			break;
		case -1:
			cout<<"Si e' verificato un errore nell'apertura del file."<<endl;
			print = false;
			break;
		case -2:
			cout<<"Il numero di dati presenti sul file non e' sufficiente a riempire la plancia di gioco."<<endl;
			print = false;
			break;
	}
	if (print)stampaMatrice(matrice_pc); // La matrice viene stampata solamente se la lettura è eseguita correttamente.
	chiediColpi(colpi);	// Funzione d'inserimento delle coordinate dei colpi da parte dell'utente.
	colpi.stampaCoda();	// Metodo di test: stampa della coda dei colpi.
	estraiColpi(colpi, contaNavi, matrice_pc);	// Funzione d'estrazione dei colpi dalla coda.
	stampaEsito(contaNavi);	// Stampa delle navi affondate.
	return 0;
}




//22-12-2020 ore 11:34 -> dammi 1 sec vado in bagno
