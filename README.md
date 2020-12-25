# Relazione tecnica
Implementazione del gioco della battaglia navale in linguaggio C++.
A cura di Francesco Pio Bonometti e Filippo Compri.

22/12/2020
Definita l'idea da cui partire per sviluppare il progetto. Il campo di battaglia è contenuto all'interno di un file di testo, in cui il valore zero indica l'acqua, mentre il valore 1 la presenza di una nave. Le posizioni delle navi saranno inizialmente inserite manualmente dall'utente all'interno del file. Considerare l'eventualità, se possibile, di generare le posizioni degli scafi in modo casuale, utilizzando le apposite librerie <ctime> e <cstdlib>. La dimensione prefissata per il campo di battaglia è, almeno in partenza, di 5 x 5: tale valore è inizializzato come const globale utilizzando una lista di inizializzazione.
  
23/12/2020
Realizzata la funzione di lettura della matrice dal file di testo. La funzione restituisce un valore nullo se tutto è andato a buon fine, restituisce -1 in caso di errore in lettura, -2 in caso di una quantità insufficiente di dati. Realizzata inoltre una funzione di stampa della matrice letta dal file su terminale, in modo da permettere all'utente di visualizzare la posizione delle navi.

25/12/2020
Realizzato un array dinamico di strutture recColpo. Ogni elemento di tipo recColpo è definito da un indice di riga e un indice di colonna, compresi entro un intervallo 0 < n_riga <= 5 e 0 < n_colonna <= 5. Implementata una classe Colpo dotata degli attributi privati relativi all'array dinamico (puntatore, primo elemento, ultimo elemento, lunghezza e dimensione) e dei metodi costruttori, distruttore, push e pop. In presenza del costruttore void, l'array avrà una dimensione predefinita di 100 elementi.
