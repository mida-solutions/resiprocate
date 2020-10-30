# Guida alla compilazione di recon

Autore: Simone Gaiarin
Data: 18/9/2020
Versione di Visual Studio: 2019

Pagine web di riferimento (seppur molti passi sono obsoleti):
- https://www.resiprocate.org/Recon_Overview
- https://www.resiprocate.org/Building_recon
- https://www.resiprocate.org/Using_testUA

File di riferimento:

- `resiprocate\resip\recon\readme.txt`



## Compilazione rapida di resiprocate-1.12

```
mkdir resiprocate_root
cd resiprocate_root
git clone --branch resiprocate-1.12_mida-fix https://github.com/mida-solutions/resiprocate.git resiprocate
git clone --branch resiprocate-1.12_mida-fix https://github.com/mida-solutions/sipXtapi-svn-mirror.git sipXtapi
```

- VS2019
  - Aprire `resiprocate_root\resiprocate\resip\recon\recon_1_15.sln`
  - Selezionare build type Release dal menu a tendina
  - Compilare il progetto `libSRTP`
  - Compilare il progetto `recon`
  - [opzionale] Compilare il progetto `testUA`
- VS successivo a 2019
  - Aprire `resiprocate_root\resiprocate\resip\recon\recon_1_15.sln`
  - Acconsentire al retarget dei progetti
  - Tasto destro sulla solution > Retarget solution
  - Seguire gli stessi passi riportati sopra per VS2019

Vedere la sezione "Testare la libreria con testUA"

## Compilazione da zero

Seguire in ordine tutti i passi riportati nelle seguenti sezioni. I passi si riferiscono a resiprocate-1.12 con una specifica versione di sipXtapi. Per versioni diverse è molto probabile che serva applicare altri fix.

## Clonare i repository

- Creare una cartella `resiprocate_root`
- Clonare https://github.com/resiprocate/resiprocate nella cartella `resiprocate_root\resiprocate`
- Fare checkout del tag (o branch sono allineati) 'resiprocate-1.12'
- Clonare https://github.com/sipXtapi/sipXtapi-svn-mirror.git nella cartella `resiprocate_root\sipXtapi`
- Fare checkout del commit 652d8fcb8fff9228592cdf8917d513353250c6d3 (master al 18/9/2020)
- Scaricare `Win32 OpenSSL v1.1.1h exe` da https://slproweb.com/products/Win32OpenSSL.html e installarlo in `\resiprocate_root\resiprocate\contrib\openssl` (occhio che non crei sottocartelle). Selezionare di installare le dll nella sottocartella `bin`.
- Scaricare `boost_1_74_0.zip` (o più nuovo) da https://www.boost.org/users/download/ e estrarlo in `\resiprocate_root\resiprocate\contrib\boost` (occhio che non crei sottocartelle, rinominando opportunamente la cartella estratta)

### Stato dei repository di sipXtapi (18/9/2020)

Ci sono tre repository tutti de-sincronizzati tra loro:

- https://sipxsvn.sipez.com/rep/sipX/ ad oggi è il più aggiornato

- https://github.com/sipXtapi/sipXtapi-svn-mirror dovrebbe tracciare il repo svn ma in pratica è indietro rispetto al repo svn
- https://github.com/sipXtapi/sipXtapi boh! questo è l'unico che contiene dei tag. La versione di sipXtapi in debian stable è `3.3.0~test17` mentre in debian testing è `3.3.0~test18`. Quest'ultima è usata anche in altre distro, vedere https://repology.org/project/sipxtapi/versions.

### .gitignore

Per semplificare il debugging, nei vari repository è possibile aggiungere un file `.gitignore` con questo contenuto

```
Debug/
Release/
```

e scaricare da gitignore.io i template per VS e C++

## Configurare i progetti di Visual Studio

### Fix a path dei progetti e retarget

- Dalla cartella `resiprocate_root\resiprocate\resip\recon` editare i seguenti file (attualmente alla versione 15 per MSVS 2017):

  -  `recon_15_0.sln`
  -  `test\testUA_15_0.vcxproj`
  - `test\unitTests_15_0.vcxproj` 
  - `MOHParkServer\MOHParkServer_15_0.vcxroj`

  e sostituire la stringa `-msvc8` con una stringa vuota.

  ```sed -i 's/-msvc8//g' resip/recon/recon_15_0.sln resip/recon/test/{testUA_15_0.vcxproj,unitTests_15_0.vcxproj}```

- Nei seguenti file:

  -  `recon_15_0.sln`
  - `MOHParkServer\MOHParkServer_15_0.vcxproj`

  sostituire la stringa `VS2005` con `VS2003` per il progetto `libilbc`

  ```sed -i 's/VS2005/VS2003/g' resiprocate_root/resiprocate/resip/recon/recon_15_0.sln resiprocate_root/resiprocate/resip/recon/MOHParkServer/MOHParkServer_15_0.vcxproj```

- Aprire `recon_15_0.sln` chiede di fare il retarget dei progetti a Visual Studio 2019, dire di sì

- Tasto destro sulla solution e `Retarget solution`

### Selezionare il build type

- Selezionare `SSL-Release` nel menu a tendina di VS per fare il build in Release
- Tutte le modifiche alle proprietà dei progetti elencate in seguito vanno effettuate per ogni tipo di build type. Per la maggior parte dei progetti è possibile selezionare `All Configurations` nel menu a tendina della finestra `Properties` del progetto.

### sipXtapi

- - Per i progetti `sipXmediaAdapterLib`, `sipXmedaLib` e `sipXportLib`. Tasto destro sul progetto > Properties >  VC++ Directories > Include Directories > Edit... e aggiungere `..\..\resiprocate\contrib\pcre` [nota che `resiprocate` nel path è il nome della cartella dove abbiamo clonato localmente il repository di resiprocate]
- Compilare `sipXportLib` e `sipXmediaAdapterLib` per verificare che tutto sia corretto fino a qui
- La compilazione di `sipXmediaLib` fallisce con un errore `ambigiuos symbol` in `sipXportLib\include\os\OsAtomics.h`
- In quel file sostituire `memory_order_seq_cst` con `::memory_order_seq_cst` da riga 54 a 82 (non sostituirlo nella definizione dell'enum)
- Eliminare selettivamente i codec `plgilbc`, `plgpcmapcmu`, `plgspeex`, `plgl16` dalla sezione `References` del progetto `sipXmediaLib` e la libreria verrà compilata senza questi codec
  - Vedere la sezione codec per applicare i fix, una volta fatto è possibile ri-aggiungerli
- Compilare `sipXmediaLib` per verificare che tutto sia corretto fino a qui

### libSRTP

- Fare il build di questo progetto
- Se non viene fatto il build di questo progetto a mano, quando si compila `recon` o `testUA` compaiono errori incomprensibili tipo:
  - redefinition of `uint64_t`

### recon

- Tasto destro sul progetto > Properties >  VC++ Directories > Include Directories > Edit... e aggiungere:
  - `..\..\..\sipXtapi\sipXcallLib\include` 
    - (risolve cannot find `sipXtapiEvents.h`)
  - [Non dovrebbe servire se è stato fatto il build di libSRTP] `..\..\contrib\pcre`

### testUA

- Tasto destro sul progetto > Properties >  VC++ Directories > Include Directories > Edit... e aggiungere:
  - `..\..\..\..\sipXtapi\sipXcallLib\include`
    - nota che è un livello in più rispetto al path usato nel progetto recon
    - cannot find `sipXtapiEvents.h`
  - `..\..\..\contrib\pcre` 
    - aggiungi solo se mancante
    - nota che è un livello in più rispetto al path usato nel progetto recon
- [IMPORTANTE] I reference di testUA sono sbagliati e puntano a progetti vecchi, quindi vanno aggiornati. Dalla sezione `References` del progetto `testUA`, rimuovere tutte le reference e dopo aggiungere tutti i seguenti progetti come reference:
  
  - ares
  - dum
  - libspeex
  - libspeexdsp
  - libSRTP
  - pcre
  - plgilbc [se compila]
  - plgl16 [se compila]
  - plgpcmapcmu [se compila]
  - plgspeex [se compila]
  - plgtones [se compila]
  - recon
  - reflow
  - resiprocate
  - reTurnClient
  - rutil
  - sipXmediaAdapterLib
  - sipXmediaLib
  - sipXportLib
  - sipXsdpLib
  
- Eliminare selettivamente i codec `plgilbc`, `plgpcmapcmu`, `plgspeex`, `plgl16` dalla sezione `References` del progetto `sipXmediaLib` e la libreria verrà compilata senza questi codec

  - Vedere la sezione codec per applicare i fix, una volta fatto è possibile ri-aggiungerli

  - Ricordarsi che devono essere stati eliminati anche da `sipXmediaLib`

- Compilare `testUA` per vedere che sia tutto corretto

## unitTests

- TODO

## codec

### Codec in ordine di utilità

plgpcmapcmu, plgg729, plgg722, plgopus!, plgaac, plgamr, plgamrwb

### plgilbc

??

### plgl16

Sostituire `<CodecL16.h>` con `"CodecL16.h"`

### plgpcmapcmu

Dovrebbe compilare

### plgspeex

??

## Testare la libreria con testUA

- Tasto destro sul progetto `testUA` > Properties > Debugging > Command Arguments e settare a:
  `-a  192.168.2.195 -u sip:9212@192.168.0.21 -p PASSWORD -aa`
  - -a specificare l'IP del PC locale
  - sip:9212 è l'utente SIP con cui vogliamo connetterci
  - 102.168.0.21 è l'indirizzo del server SIP
  - -p è la password dell'utente
  - -aa imposta la risposta automatica
- Tasto destro sul progetto `testUA` e selezionare `Set as Startup Project`
- Potrebbe essere necessario copiare i codec.dll nella stessa cartella dell'eseguibile, leggere la guida qui sotto.

Leggere https://www.resiprocate.org/Using_testUA per capire come funziona. Lanciare testUA e poi eseguire i seguenti comandi:

- `i` mostra info
- `crp 1 9209` Fa una chiamata al numero 9209crp 

## Troubleshooting

### Errore MSB4211 quando si compila sipXmediaLib

Per qualche motivo retarget project sembra funzionare ma non aggiorna una voce dentro alcuni file di progetto facendo fallire la compilazione.

Editare a mano i seguenti file:

- `\resiprocate_root\sipXtapi\sipXmediaLib\contrib\libspeex\win32\VS2003\libspeex\libspeex.vcxproj`
- `\resiprocate_root\sipXtapi\sipXmediaLib\contrib\libspeex\win32\VS2003\libspeexdsp\libspeexdsp.vcxproj`

e sostituire `<PlatformToolset>v120</PlatformToolset>` con `<PlatformToolset>v142</PlatformToolset>` per VS 2019

### Errore MSB4211 quando si compila testUA

- Eliminare e aggiungere le reference come spiegato nella sezione `testUA`

### Linker errors

Indica problemi nella sezione `References` di un progetto. Aggiungere i progetti verso cui si deve linkare.

