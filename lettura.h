#pragma once
#include <fstream>

int leggiDalFile(unsigned int m[][n_elementi]);

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
