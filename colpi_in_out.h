#pragma once
#include <iostream>
using namespace std;

void chiediColpi(Colpo &arrayColpi);
void estraiColpi(Colpo &arrayColpi, unsigned int campo[][n_elementi]);
void estraiElemento(char stringa_in[], char stringa_out[]);

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
