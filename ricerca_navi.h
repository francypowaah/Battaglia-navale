#pragma once
#include <iostream>
#include <vector>
using namespace std;

int trovaCoordinate(recColpo hit_eseguito, int idx);
void cercaNave(recColpo hit, unsigned int campo_battaglia[][n_elementi]);
void contatoreNavi(unsigned int num, int idx);
unsigned int calcolaNum(int index);
void ricercaRicorsiva_y(unsigned int campo[][n_elementi], int r, int c, recNave &estratta, int idx);
void ricercaRicorsiva_x(unsigned int campo[][n_elementi], int r, int c, recNave &estratta, int idx);
void ricercaCoordinate(unsigned int m[][n_elementi]);

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
