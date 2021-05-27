# #progetto1000 il Robot che risolve il Cubo di Rubik
Questo è il primo progetto del [:arrow_forward: Canale YouTube "PROGETTI con Emanuele Frisoni"](https://youtube.com/c/fremsoft), un progetto collaborativo che nasce al raggiungimento di 1000 iscritti: [:movie_camera: Guarda la Playlist completa del progetto](https://www.youtube.com/watch?v=VcB0eAnL97o&list=PLxAafib4pWc7LSfuXC9RSEif6I1dyx5FP)

1. [Parte la progettazione in Live Streaming su Twitch](README.md#parte-la-progettazione-in-live-streaming-su-twitch)
2. [Definizione delle specifiche](README.md#definizione-delle-specifiche)
3. [Attività da svolgere e svolte](README.md#attivit%C3%A0-da-svolgere-e-svolte)
4. [Codici sorgenti](README.md#codici-sorgenti)
5. [Sostieni PROGETTO1000](README.md#sostieni-progetto1000)
6. [Lista della spesa](README.md#lista-della-spesa)

   6.1 [Attrezzature da laboratorio e Kit](README.md#attrezzature-da-laboratorio-e-kit)
   
   6.2 [Materiale e schede elettroniche](README.md#materiale-e-schede-elettroniche)
   
   6.3 [Materiale vario per assemblaggio prototipo](README.md#materiale-vario-per-assemblaggio-prototipo)
   

## Parte la progettazione in Live Streaming su Twitch
**Ogni Giovedì sera alle 22:00** ci incontriamo su [Twitch Tv](https://www.twitch.tv/fremsoft) per progettare insieme il Robot che risolve il Cubo di Rubik, partendo da zero. Affronteremo tutti i passaggi in maniera approfondita. Ho deciso di utilizzare tecnologie che conosco "per sentito dire", ma su cui non ho mai lavorato. In questo modo vedrai tutto il processo che sta dietro alla ricerca di una soluzione. A differenza di altri progetti che trovi in rete, #progetto1000 non esiste ancora, lo possiamo creare insieme. 

Lo scopo non è mostrare al mondo quanto siamo bravi, ma mostrare agli aspiranti progettisti quali sono tutte le difficoltà che potranno incontrare nel loro percorso e suggerire un modo per affrontarle e superarle.

:clapper: Canale Twitch:  [https://www.twitch.tv/fremsoft](https://www.twitch.tv/fremsoft)

[^ Torna su](README.md#progetto1000-il-robot-che-risolve-il-cubo-di-rubik)

## Definizione delle specifiche
Siccome si tratta di un progetto collaborativo, per definire le specifiche di progetto sono stati fatti alcuni sondaggi esplorativi per determinare quali tecnologie utilizzare in questo primo progetto. I risultati del sondaggio sono i seguenti:

1. Arduino o Microchip PIC? **ARDUINO** [4 voti / 2]

2. Encoder Ottico o Accelerometro Gravitazionale? **ENCODER OTTICO** [3 voti / 1]

3. Costruzioni LEGO o Particolari stampati con Stampante 3D? **STAMPA 3D** [3 voti / 4]

4. Stand alone o Connesso a un PC/Smartphone? **SIA STANDALONE CHE COMANDATO** [4 voti / 4]

5. Muto o Sonoro? **SONORO** [3 voti / 4]

6. Cieco o con Telecamera? **TELECAMERA** [0 voti / 4]

7. Procedurale o Intelligenza Artificiale? **A.I.** [0 voti / 5 ]

[^ Torna su](README.md#progetto1000-il-robot-che-risolve-il-cubo-di-rubik)

## Attività da svolgere e svolte
Ogni progetto che si rispetti deve prevedere una serie di fasi da svolgere. Maggiore sarà la difficoltà del progetto e maggiori sono le incognite, tanto più sarà difficile riuscire a prevedere con esattezza tutte le fasi. Ciononostante, è sempre buona norma prevedere con la massima accuratezza tutte le fasi del progetto in una sorta di planning. Ad ogni modo il progetto può essere periodicamente rivisitato, modificato e corretto, in corso d'opera.

L'utilità di suddividere il progetto in attività elementari, consente al progettista di avere un approccio più razionale ed evitare di disperdersi. Inoltre, laddove sia possibile lavorare in Team, la suddivisione del progetto in attività consente di stabilire se alcune attività possano essere svolte simultaneamente da più attori, per esempio dopo aver definito le specifiche di progetto con precisione, si può affidare il progetto meccanico ad un Team ed il progetto elettronico ad un altro Team di sviluppatori.

- [x] [Analisi di fattibilità](https://youtu.be/We6UntzGp7k)
- [ ] Raccolta della documentazione e prove sperimentali con prototipi
  - [x] Dimensioni meccaniche e forze necessarie a manipolare il cubo di Rubik
  - [x] Caratteristiche elettriche e meccaniche dei motori c.c.
  - [x] Caratteristiche elettriche del driver (ponte-H) per motori c.c.
  - [x] Specifiche elettriche dei sensori ottici (fotoresistori/TCUT1350x01)
  - [x] Funzionamento di Arduino (uscite PWM, uscite parallele, timers)
  - [x] DAC e amplificatore audio per speaker 8 ohm
  - [x] Slot per Micro SD Card per Arduino per storage file audio
  - [x] Funzionamento Chip Camera OV7670 e acquisizione immagini
  - [x] Ottica del sensore OV7670
  - [x] Funzionamento del modulo WiFi per comunicazione con Smartphone
  - [x] Alimentazione 5V @ 10A
  - [ ] Selezione molle per mano robotica
- [ ] Progettazione meccanica 
  - [ ] Realizzazione delle parti che compongono il Robot (esportati in STL)
  - [ ] Stampare in 3D le componenti meccaniche
  - [ ] Assemblare le parti meccaniche con le parti elettriche (motori, encoder, etc)
- [ ] Progettazione elettronica
   - [x] Alimentazione
   - [ ] Shield p1000 
     - [x] DAC e Amplificatore per altoparlante
     - [x] Modulo SD-Card
     - [x] Interfacciamento Chip Camera OV7670
     - [x] Modulo WiFi
     - [x] Circuiti di condizionamento dei sensori ottici
     - [x] Comando motori
     - [x] Protezioni e filtri EMC/EMI
     - [ ] Montare i componenti elettronici
     - [ ] Collaudo generale dell'elettronica
- [ ] Progettazione del programma su Arduino
  - [ ] Movimentazione elementare (attraverso la porta seriale invieremo i comandi per eseguire i movimenti)
  - [ ] Acquisizione delle immagini da telecamera per distinguere i colori e mappare gli elementi del cubo di Rubik
  - [ ] Implementare gli algoritmi del metodo CFOP semplificato
    - [ ] Croce bianca
    - [ ] Faccia bianca e primo strato
    - [ ] Secondo strato
    - [ ] Croce gialla
    - [ ] OLL
    - [ ] PLL (primo passaggio)
    - [ ] PLL (secondo passaggio)
    - [ ] Allineamento terzo strato 
  - [ ] Implementare i suoni
- [ ] Progettazione della rete neurale
  - [ ] Addestramento di una rete neurale per riconoscere tutti gli OLL e PLL
  - [ ] Implementazione della rete neurale nell'algoritmo 
- [ ] Progettazione dell'applicativo per Android per mescolare il cubo con una specifica scramble o altro (forse questa fase salta)
- [ ] Dare un nome al robot

[^ Torna su](README.md#progetto1000-il-robot-che-risolve-il-cubo-di-rubik)

## Codici sorgenti
**#progetto1000** è un progetto Open-Source collaborativo. Tutti i sorgenti elaborati in fase di progettazione sono presenti su questo canale GitHub. Esplora le cartelle di [001-progetto1000](https://github.com/fremsoft/001-progetto1000) e troverai i sorgenti del progetto meccanico, elettronico, software e altro materiale prodotto in fase di progettazione.

Il codice sorgente di **Arduino** è disponibile anche a questo link: [Sorgenti Arduino](https://create.arduino.cc/editor/fremsoft/6501effc-6729-46f5-a2f1-0bfa0e9eb691/preview)

[^ Torna su](README.md#progetto1000-il-robot-che-risolve-il-cubo-di-rubik)

## Sostieni PROGETTO1000 
Se **#progetto1000** ti sta appassionando e desideri sostenere la progettazione, puoi acquistare i componenti necessari alla creazione del prototipo o le attrezzature necessarie all'allestimento del laboratorio, facendoli recapitare al mio indirizzo. La lista dei desideri completa dove trovi tutte le cose che servono:

:notebook: "Wish list Amazon" - https://amzn.to/2BDtwIV

Un altro modo per sostenere il canale è seguendo il [canale YouTube](https://youtube.com/c/fremsoft), semplicemente guardando i video, iscrivendoti al canale, mettendo like e interagendo con i commenti, ma soprattutto condividendo i video che preferisci con i tuoi amici progettisti, sono tutti modi per sostenere gratuitamente il canale.

[^ Torna su](README.md#progetto1000-il-robot-che-risolve-il-cubo-di-rubik)

## Lista della spesa
**#progetto1000** sta nascendo, non abbiamo ancora una BOM (Bill Of Material), ma stiamo già acquistando un po' di materiale per realizzare il prototipo e fare le prime prove pratiche. Se vuoi sviluppare insieme a noi e vuoi eseguire le stesse prove a casa tua, ti indico quale materiale ho acquistato qui di seguito:

### Attrezzature da laboratorio e Kit
* [Kit Elettronico con breadboard](https://amzn.to/2QTgOw7)
* [Super Starter Kit UNO project](https://amzn.to/2QJrnNc)
* [Calibro digitale](https://amzn.to/36QMR6w)
* [Bilancia digitale](https://amzn.to/3nxseCa)

### Materiale e schede elettroniche
* [Arduino Mega 2560](https://amzn.to/30RCvj6)
* [Telecamera a colori per Arduino](https://amzn.to/3nbS0Ma)
* [Set 6 motori con accessori](https://amzn.to/3nhQrfy)
* [Fotoresistore](https://amzn.to/370EtBg)

### Materiale vario per assemblaggio prototipo
* [Sfere in acciaio 4mm](https://amzn.to/3lzfDwr)

Trovi la lista completa al seguente link:
🛒 [Lista della spesa di #progetto1000](https://www.amazon.it/hz/wishlist/ls/8D7WPLCAZ7KL?tag=p-ef-21)


[^ Torna su](README.md#progetto1000-il-robot-che-risolve-il-cubo-di-rubik)
