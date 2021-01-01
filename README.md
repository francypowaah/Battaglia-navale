# Relazione tecnica
Implementazione del gioco della battaglia navale in linguaggio C++.
A cura di Francesco Pio Bonometti e Filippo Compri.

22/12/2020
Definita l'idea da cui partire per sviluppare il progetto. Il campo di battaglia è contenuto all'interno di un file di testo, in cui il valore zero indica l'acqua, mentre il valore 1 la presenza di una nave. Le posizioni delle navi saranno inizialmente inserite manualmente dall'utente all'interno del file. Considerare l'eventualità, se possibile, di generare le posizioni degli scafi in modo casuale, utilizzando le apposite librerie ctime e cstdlib. La dimensione prefissata per il campo di battaglia è, almeno in partenza, di 5 x 5: tale valore è inizializzato come const globale utilizzando una lista di inizializzazione.
  
23/12/2020
Realizzata la funzione di lettura della matrice dal file di testo. La funzione restituisce un valore nullo se tutto è andato a buon fine, restituisce -1 in caso di errore in lettura, -2 in caso di una quantità insufficiente di dati. Realizzata inoltre una funzione di stampa della matrice letta dal file su terminale, in modo da permettere all'utente di visualizzare la posizione delle navi.

25/12/2020
Realizzato un array dinamico di strutture recColpo. Ogni elemento di tipo recColpo è definito da un indice di riga e un indice di colonna, compresi entro un intervallo 0 < n_riga <= 5 e 0 < n_colonna <= 5. Implementata una classe Colpo dotata degli attributi privati relativi all'array dinamico (puntatore, primo elemento, ultimo elemento, lunghezza e dimensione) e dei metodi costruttori, distruttore, push e pop. In presenza del costruttore void, l'array avrà una dimensione predefinita di 100 elementi.

27/12/2020
Implementate le funzioni push e pop per immettere ed estrarre le coordinate dei colpi dall’array dinamico del tipo recColpo. È stato riscontrato un bug relativo agli indici di riga e colonna nei colpi: la stampa prevedeva dei numeri Ascii anziché dei numeri interi. Abbiamo risolto il problema sottraendo al valore il numero Ascii 48, corrispondente al valore 0.

30/12/2020
Implementate le funzioni di controllo dei colpi sulla matrice del campo di battaglia e di stampa delle navi affondate. Il programma prevede la stampa di un messaggio di errore nel caso in cui nessuna nave sia affondata. È stato riscontrato un bug per il quale è possibile che - in presenza di due o più navi dello stesso tipo colpite in parte - la somma dei colpi inflitti alle due navi diverse generi come risultato l’abbattimento di una nave completa. Tuttavia, in presenza di navi colpite interamente e parzialmente, il programma risulta pienamente funzionante.

01/01/2021
Modificata l’interfaccia del programma sulla base dell’effettiva griglia di gioco della battaglia navale. La dimensione della griglia risulta essere 10 x 10 anziché 5 x 5. Qualora se ne presentasse la necessità, è possibile ridimensionare il quadro della griglia con valori a proprio piacere.
Modificati con successo anche gli indici di colonna, da numeri a righe: il valore Ascii dell’indice di colonna sarà convertito in numero mediante apposita sottrazione con 65 (codice Ascii ‘A’). Persiste il bug relativo a numero multiplo di navi dello stesso tipo colpite parzialmente. L’eventuale soluzione presa in considerazione, al momento, è di creare un differente array per ogni tipo di nave presente sulla plancia di gioco.

