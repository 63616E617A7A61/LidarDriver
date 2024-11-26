# LidarDriver 
Il progetto consiste nello sviluppo di un modulo per la gestione di dati provenienti da un sensore LIDAR in C++. La classe principale **Lidar Driver** implementa la gestione di un buffer circolare per salvare e manipolare le scansioni eseguite dal sensore. 

## Struttura del progetto 
La struttura delle cartelle e dei file è organizzata come segue:

```plaintext
LidarDriver/
├── include/
│   ├── LidarDriver.h        # Dichiarazione della classe LidarDriver
│   └── FileReader.h         # Dichiarazione della classe FileReader 
├── src/
│   ├── LidarDriver.cpp      # Implementazione della classe LidarDriver
│   ├── FileReader.cpp       # Implementazione della classe FileReader 
│   ├── main.cpp             # File principale per i test 
│   └── scan_file.txt        # File contenente alcuni scan di test 
├── CMakeList.txt            # File CMake
└── README.md                # Documentazione del progetto
```

## Descrizione classi 
Il progetto è composto da **LidarDriver**, **FileReader** e il **main**

### 1. **`FileReader`**
Questa classe è progettata per leggere dati da un file di testo e convertire ogni riga in un vettore di valori numerici (`std::vector<double>`). 
- **Costruttore**: accetta un percorso file e lo apre
- **`getNextLine()`**: legge la prossima riga dal file e restituisce i valori come `std::vector<double>`. Se si presenta un errore o se il file è finito viene chiuso
- **`hasNextLine()`**: controlla se ci sono ancora righe da leggere nel file, restituisce `true` o `false`
  
**Uso principale**: leggere e trasformare in un dato leggibile dal programma scansioni da file, per passarli ad altre classi o moduli come `std::vector<double>`.


### 2. **`LidarDriver`**
Questa classe gestisce le scansioni acquisite da un sensore LIDAR.
- **Costruttore**: inizializza la risoluzione angolare e il buffer circolare (numero di scansioni e punti per scansione).
- **`new_scan()`**: aggiunge una nuova scansione al buffer. Se il buffer è pieno, sovrascrive la scansione meno recente.
- **`get_scan()`**: restituisce la scansione meno recente dal buffer e la rimuove.
- **`clear_buffer()`**: svuota completamente il buffer.
- **`get_distance()`**: restituisce la distanza a un dato angolo nella scansione più recente, approssimandola all'angolo più vicino se necessario.
- **Overload `operator<<`**: consente di stampare a schermo la scansione più recente senza rimuoverla.
- **Distruttore**: dealloca la memoria del buffer.

**Uso principale**: gestire le scansioni del LIDAR in modo efficiente tramite buffer circolare.


### 3. **`main.cpp`**
Questo file implementa un'interfaccia utente per testare le funzionalità di `LidarDriver` e `FileReader`.
- **Funzione `main`**:
  - Implementa un menu interattivo per generare nuove scansioni, leggere dal buffer, ottenere distanze a specifici angoli, svuotare il buffer o terminare il programma.
- **Altre funzioni**:
  - `randomNum()`: genera numeri casuali per creare scansioni simulate.
  - `generateScan()`: crea scansioni di lunghezza arbitraria con valori casuali.
  - `getScanFile()`: legge le scansioni da un file e le carica nel buffer del LidarDriver.
  - `printVect()`: stampa un vettore di valori.

**Uso principale**: testare e dimostrare le funzionalità delle classi tramite un'interfaccia a menu. 

# Suddivisione del progetto
Il progetto è stato suddiviso nel seguente modo: 
- **Classe LidarDriver**: suddivisi i metodi tra i 3 membri
- **Classe FileReader**: Zillio Nicola 
- **main**: suddiviso tra i 3 membri
- **CMake**: Rovoletto Tommaso, Sivori Leonardo
