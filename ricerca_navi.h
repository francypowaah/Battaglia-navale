#pragma once
#include <iostream>
#include <vector>
using namespace std;

unsigned int punteggio{0};

void stampaMatrice(unsigned int m[][n_elementi]);
void stampaEsito();
bool stampaMessaggio(int codice);
void stampaPunteggio();

void stampaMatrice(unsigned int m[][n_elementi])
{
	cout<<"o---o---o---o---o---o---o"<<endl;
	cout<<"Campo di battaglia "<<endl;
	cout<<"o---o---o---o---o---o---o"<<endl;
	cout<<"     ";
	for (char i{65}; i < 65 + n_elementi; i++)	// Stampa degli indici di colonna.
		cout<<i<<" ";
	cout<<endl<<"   # ";
	for (int i{0}; i < n_elementi; i++) // Stampa dei caratteri separatori #.
	{
		cout<<"# ";
	}
	cout<<endl;
	for (int i{0}; i < n_elementi; i++)	
	{
		if (i < 9)
			cout<<i + 1<<"  # "; // Stampa degli indici di riga.
		else
			cout<<i + 1<<" # ";
		for (int j{0}; j < n_elementi; j++)
		{
			cout<<m[i][j]<<" "; // Stampa della matrice.
		}
		cout<<endl;
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
void stampaEsito() // Funzione di stampa delle navi affondate.
{
	cout<<"o---o---o---o---o---o---o"<<endl;
	for (int i{0}; i < v_coordinate.size(); i++)
	{
		unsigned int n_colpiti{0};
		n_colpiti = calcolaNum(i);
		punteggio+=n_colpiti;
		contatoreNavi(n_colpiti, v_coordinate[i].lung_nave);
	}
	if (noAffondate)
			cout<<"Peccato, nessuna nave e' stata affondata."<<endl;
}
void stampaPunteggio()	// Funzione di stampa del punteggio complessivo, dato dalla somma dei colpi andati a buon segno.
{
	cout<<"Punteggio totalizzato: "<<punteggio<<endl;
	cout<<"o---o Developed by Bonometti Francesco Pio & Compri Filippo o---o"<<endl;
}
