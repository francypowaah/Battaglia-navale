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

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cstring> // Libreria stringhe.
#include <vector> // Vettori (array con lunghezza variabile dichiarata a run-time).
#include <algorithm> // Libreria all'interno del quale è inclusa la funzione sort, che migliora di netto le tempistiche del bubbleSort, quickSort ed exchangeSort.
#include "Colpi.h"
#include "ricerca_navi.h"
using namespace std;

/*
La funzione ritorna -1 se il file non è stato aperto correttamente, ritorna -2 se i dati sul file non sono
sufficienti e ritorna 0 se invece tutto è andato a buon fine.
*/
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

vector <recNave> v_coordinate(0);
bool compara_navi(recNave a, recNave b) { return a.lung_nave < b.lung_nave; }	// Funzione utilizzata per il sort. 

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
		if (i < 9)
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
	bool prosegui_inserimento{true};
	recColpo colpoEseguito;
	cout<<"o---o---o---o---o---o---o"<<endl;
	while (prosegui_inserimento)
	{
		cout<<"Inserisci le coordinate, separate da un ';': ";
		cin>>coords;
		if (coords[0] == 'q' or coords[0] == 'Q')
		{
			prosegui_inserimento = false; // Il carattere q termina il ciclo di inserimento.
		}
		else
		{
			if (strlen(coords) <= max_len && strlen(coords) > 0) // Una stringa di coordinate vuota o più lunga della massima dimensione consentita, sarà ignorata.
			{
				bool check_lettera{true};
				estraiElemento(coords, element);
				if (element[0] > 64 && element[0] <= (64 + n_elementi))
					colpoEseguito.indiceColonna = element[0] - 64; // Conversione della lettera maiuscola da Ascii a int.
				else if (element[0] > 96 && element[0] <= (97 + n_elementi))
					colpoEseguito.indiceColonna = element[0] - 96; // Conversione della lettera minuscola da Ascii a int.
				else
					check_lettera = false;
				if (check_lettera)
				{
					estraiElemento(coords, element);
					colpoEseguito.indiceRiga = atoi(element);
					arrayColpi.push(colpoEseguito);	// Invocazione del metodo push sull'oggetto arrayColpi, secondo la logica della coda.		
				}
			}
		}
	}
}
int trovaCoordinate(recColpo hit_eseguito, int idx)
{
	int indice{0};
	while (indice < dim_navi)
	{
		if (v_coordinate[idx].coordinate_nave[indice].riga == hit_eseguito.indiceRiga && v_coordinate[idx].coordinate_nave[indice].colonna == hit_eseguito.indiceColonna)
			return indice;
		indice++;
	}
	return -1;
}
void cercaNave(recColpo hit, unsigned int campo_battaglia[][n_elementi])	// Funzione di ricerca della nave.
{
	unsigned int elementoMatrice{campo_battaglia[hit.indiceRiga][hit.indiceColonna]};
	int indiceRitorno{0};
	bool prosegui_ricerca{true};
	for (int i{0}; i < v_coordinate.size() && prosegui_ricerca; i++)
	{
		if (elementoMatrice == v_coordinate[i].lung_nave)
		{
			indiceRitorno = trovaCoordinate(hit, i);
			if (indiceRitorno >= 0)
			{
				v_coordinate[i].trovati[indiceRitorno] = true;
				prosegui_ricerca = false;
			}
		}
	}
}
void estraiColpi(Colpo &arrayColpi, unsigned int campo[][n_elementi]) // Funzione di estrazione dei colpi dalla coda.
{
	recColpo colpoEstratto;
	const unsigned int length = arrayColpi.getLunghezza(); // Memorizzo la lunghezza in una costante, perchè con le pop la lunghezza effettiva si ridurrà.
	for (int i{0}; i < length; i++)
	{
		colpoEstratto = arrayColpi.pop();
		cercaNave(colpoEstratto, campo);
	}
}
void contatoreNavi(unsigned int num, int idx) // Contatore delle navi affondate.
{
	if (num < idx && num > 0)
	{
		cout<<"Nave da "<<idx<<" colpita in parte ("<<num<<"/"<<idx<<")."<<endl;
	}
	if (num == idx)
	{
		cout<<"Nave da "<<idx<<" affondata!"<<endl;
		noAffondate = false;
	}
	if (num == 0)
	{
		cout<<"Nave da "<<idx<<" non colpita, peccato!"<<endl;	
	}	
}
unsigned int calcolaNum(int index)
{
	unsigned int num{0};
	for (int i{0}; i < dim_navi; i++)
	{
		if (v_coordinate[index].trovati[i] == true)
			num++;
	}
	return num;
}
void stampaEsito() // Funzione di stampa delle navi affondate.
{
	cout<<"o---o---o---o---o---o---o"<<endl;
	for (int i{0}; i < v_coordinate.size(); i++)
	{
		unsigned int n_colpiti{0};
		n_colpiti = calcolaNum(i);
		contatoreNavi(n_colpiti, v_coordinate[i].lung_nave);
	}
	if (noAffondate)
			cout<<"Peccato, nessuna nave e' stata affondata."<<endl;
	cout<<"o---o Developed by Bonometti Francesco Pio & Compri Filippo o---o"<<endl;
}
void ricercaRicorsiva_y(unsigned int campo[][n_elementi], int r, int c, recNave &estratta, int idx)
{
	if (r + 1 <= n_elementi && r >= 0)
	{
		if (campo[r][c] != 0)
		{
			estratta.coordinate_nave[idx].riga = r;
			estratta.coordinate_nave[idx].colonna = c;
			matrice_parallela[r][c] = true;
			ricercaRicorsiva_y(campo, r + 1, c, estratta, idx + 1);
		}
	}
}
void ricercaRicorsiva_x(unsigned int campo[][n_elementi], int r, int c, recNave &estratta, int idx)
{
	if (c + 1 <= n_elementi && c >= 0)
	{
		if (campo[r][c] != 0)
		{
			estratta.coordinate_nave[idx].riga = r;
			estratta.coordinate_nave[idx].colonna = c;
			matrice_parallela[r][c] = true;
			ricercaRicorsiva_y(campo, r, c + 1, estratta, idx + 1);
		}
	}
}
void ricercaCoordinate(unsigned int m[][n_elementi])
{
	for (int i{0}; i < n_elementi; i++)
	{
		for (int j{0}; j < n_elementi; j++)
		{
			recNave structEstratta;
			int indice{0};
			bool prosegui{true};
			if (!matrice_parallela[i][j])
			{
				matrice_parallela[i][j] = true;
				if (m[i][j] != 0)
				{
					structEstratta.coordinate_nave[indice].riga = i;
					structEstratta.coordinate_nave[indice].colonna = j;
					structEstratta.lung_nave = m[i][j];
					indice++;
					matrice_parallela[i][j + 1] = true;
					matrice_parallela[i + 1][j] = true;
					if (m[i + 1][j] == m[i][j])
					{
						ricercaRicorsiva_y(m, i + 1, j, structEstratta, indice);
					}
					if (m[i][j + 1] == m[i][j])
					{
						ricercaRicorsiva_x(m, i, j + 1, structEstratta, indice);
					}
					v_coordinate.push_back(structEstratta);
				}
			}
		}
	}
}
bool stampaMessaggio(int codice)
{
	switch(codice)
	{
		case 0:
			cout<<"Lettura del file eseguita con successo!"<<endl;
			return true;
		case -1:
			cout<<"Si e' verificato un errore nell'apertura del file."<<endl;
			return false;
		case -2:
			cout<<"Il numero di dati presenti sul file non e' sufficiente a riempire la plancia di gioco."<<endl;
			return false;
	}
}

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
		return 0;
	}
}
