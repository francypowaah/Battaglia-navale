#pragma once

struct recColpo
{
	int indiceRiga;
	int indiceColonna;
};

class Colpo
{
	private:
		recColpo* colpi;
		unsigned int primo;
		unsigned int ultimo;
		unsigned int dim;
		unsigned int lunghezza;
	public:
		Colpo();
		Colpo(unsigned int n_colpi);
		~Colpo();
		void push(recColpo hit);
		recColpo pop();
};

Colpo::Colpo()
{
	const unsigned int k{100};	// Costante k, dichiarata con lista di inizializzazione.
	dim = k;					// Dimensione standard di 100 elementi.
	colpi = new recColpo[dim];
	primo = 0;
	ultimo = 0;
	lunghezza = 0;
}
Colpo::Colpo(unsigned int n_colpi)
{
	dim = n_colpi;
	colpi = new recColpo[dim];
	primo = 0;
	ultimo = 0;
	lunghezza = 0;
}
Colpo::~Colpo()
{
	delete [] colpi;
}
void Colpo::push(recColpo hit)
{
	if (lunghezza < dim)
	{
		if ((hit.indiceColonna > 0 && hit.indiceColonna <= n_elementi) && (hit.indiceRiga > 0 && hit.indiceRiga <= n_elementi))
		{
			colpi[ultimo].indiceColonna = hit.indiceColonna;
			colpi[ultimo].indiceRiga = hit.indiceRiga;
			++ultimo;
			if (ultimo >= dim)
				ultimo = 0;
			++lunghezza;
		}
	}
}
recColpo Colpo::pop()
{
	recColpo elementoEstratto;
	if (lunghezza > 0)
	{
		if ((colpi[primo].indiceColonna > 0 && colpi[primo].indiceColonna <= n_elementi) && (colpi[primo].indiceRiga > 0 && colpi[primo].indiceRiga <= n_elementi))
		{
			--lunghezza;
			elementoEstratto = colpi[primo];
			++primo;
			if (primo >= dim)
				primo = 0;
			return elementoEstratto;
		}
	}
}
