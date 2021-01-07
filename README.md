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
Implementate le funzioni push e pop per immettere ed estrarre le coordinate dei colpi dall’array dinamico del tipo recColpo. È stato riscontrato un bug relativo agli indici di riga e colonna nei colpi: la stampa prevedeva dei numeri Ascii anziché dei numeri interi. Abbiamo risolto il problema sottraendo al valore il numero Ascii 48, corrispondente al valore nullo.

30/12/2020
Implementate le funzioni di controllo dei colpi sulla matrice del campo di battaglia e di stampa delle navi affondate. Il programma prevede la stampa di un messaggio di errore nel caso in cui nessuna nave sia affondata. È stato riscontrato un bug per il quale è possibile che - in presenza di due o più navi dello stesso tipo colpite in parte - la somma dei colpi inflitti alle due navi diverse generi come risultato l’abbattimento di una nave completa. Tuttavia, in presenza di navi colpite interamente e parzialmente, il programma risulta pienamente funzionante.
01/01/2021
Modificata l’interfaccia del programma sulla base dell’effettiva griglia di gioco della battaglia navale. La dimensione della griglia risulta essere 10 x 10 anziché 5 x 5. Qualora se ne presentasse la necessità, è possibile ridimensionare il quadro della griglia con valori a proprio piacere.
Modificati con successo anche gli indici di colonna, da numeri a righe: il valore Ascii dell’indice di colonna sarà convertito in numero mediante apposita sottrazione con 64 (codice Ascii ‘A’ - 1, dal momento che una unità sarà poi sottratta anche nella memorizzazione della coda dei colpi). Persiste il bug relativo a numero multiplo di navi dello stesso tipo colpite parzialmente. L’eventuale soluzione presa in considerazione, al momento, è di creare un differente array per ogni tipo di nave presente sulla plancia di gioco.

02/01/2021
Rilevato un nuovo bug relativo agli indici di riga. Seppur gli indici di colonna tali da soddisfare la condizione 10 <= n_colonna<= 26 vengano rilevati correttamente dal programma, gli indici di colonna >= 10 non sono incapsulati correttamente nell’array element utilizzando la relativa funzione estraiElemento. La soluzione al problema è stata implementata rimuovendo alcune condizioni di controllo all'ultima iterazione della funzione estraiElemento stessa. Ora la base del programma funziona correttamente a tutti gli effetti, seppur generi tuttora problematiche in presenza di navi multiple colpite parzialmente.

06/01/2021
Sistemato il bug relativo alle navi multiple della stessa lunghezza. Ogni nave è provvista del relativo array, in cui è memorizzata la sua lunghezza, le sue coordinate e quali fra esse sono state già colpite almeno una volta nel corso della partita, così da impedire eventuali colpi aventi uguali coordinate inseriti per più volte nel corso dell’esecuzione. Inizialmente, l’idea era di compiere uno shift all’interno dell’array coordinate per ogni colpo andato a segno. Tuttavia, implementando la ricerca delle coordinate in tal modo, il programma non restituiva alcun output su console. La soluzione adottata mediante l’aggiunta di un array parallelo per le coordinate già trovate pone rimedio, oltre alla tanto discussa problematica delle navi multiple, anche al problema di eventuali colpi aventi uguali coordinate inseriti per più volte. Implementato, infine, anche un controllo sulle coordinate ricevute in input dall’utente.

07/01/2021
Funzioni del programma smistate in vari file header .h, in relazione al tipo di impiego della funzione (ricerca delle navi, lettura da file, input/output di colpi, stampe a schermo, definizione della classe Colpi). Introdotto un contatore del punteggio totale, visualizzato al termine della partita, calcolato sommando il numero di colpi andati effettivamente a buon segno.
Il programma è concluso e funziona correttamente in ogni situazione e con ogni disposizione orizzontale o verticale delle navi (secondo le regole della battaglia navale, non è possibile disporre navi in obliquo), a patto che il numero di righe e colonne sulla plancia di gioco non superi il numero di caratteri dell’alfabeto italiano. Pertanto, la costante globale n_elementi dovrà essere minore o uguale a 26.
