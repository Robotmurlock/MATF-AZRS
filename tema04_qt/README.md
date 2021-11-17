# Qt Framework

**Qt (cute)** je `framework` za razvoj softvera koji nam nudi podršku za različite platforme, kao
i razvoj `GUI` aplikacija. 

## Qt Instalacija

### Linux
`sudo apt-get install build-essential`\
`sudo apt-get install qtcreator`\
`sudo apt-get install qt5-default`
    

**Linux docs i API:**

``sudo apt install `apt-cache search 5-examples | grep qt | grep example | awk '{print $1 }' | xargs` ``\
``sudo apt install `apt-cache search 5-doc | grep "Qt 5 " | awk '{print $1}' | xargs` ``\
`sudo apt-get install build-essential qtcreator qt5-default`

**Ako nešto nedostaje:**

``sudo apt install `apt-cache search qt | grep 5- | grep ^qt | awk '{print $1}' | xargs` ``

**izvor:**

- [qt linux installation guide](https://doc.qt.io/qt-5/linux.html)`
- [stackoverflow linux installation guide](https://stackoverflow.com/questions/48147356/install-qt-on-ubuntu)

#### Ostale platforme

- **Mac:** [qt macos installation guide](https://doc.qt.io/qt-5/macos.html)
- **Windows:** [qt windows installation guide](https://doc.qt.io/qt-5/windows.html)

## Upustvo za dodavanje cppreference u Qt Creator

**Preuzimanje cppreference knjige:**

1. Otvoriti zvaničnu cppreference stranicu: [cppreference](https://en.cppreference.com);
2. Kliknuti na `offline archive` pri dnu u okviru sekcije `News`;
3. Pronaći sekciju `Qt help book` i tu kliknuti na zipovan `qch book`;
4. Skinuti `qch book` (Napomena: Ako ne može da se skine preko Chrome pretraživača, skinuti preko drugog pretraživača).

**Dodavanje cppreference u Qt Creator (pogledati cppreference.pdf datoteku)**:

1. Otvoriti Qt creator; 
2. Kliknuti na `Tools` u opcijama na vrhu, pa na `Options...`;
3. Kliknuti na `Help` sa leve strana;
4. Pri vrhu kliknuti na `Documentation`;
5. Kliknuti na `Add...` i dodati `*.qch` fajl.

**Korišćenje cppreference u okviru Qt Creator-a**:

Sada se u okviru Qt moze koristiti cppreference tako sto se klikne na `Help`
sa leve strane i u opcijama izabrati cppreference.

## 01_nonqt_aplikacija

Razvojno okruženje `Qt Creator` možemo da koristimo i bez `Qt` biblioteka. Korišćenje okruženja je intuitivno, a ovaj primer je samo test da li je okruženje podešeno kako treba.

- Projekat možemo da započnemo pokretanjem `qtcreator`-a. 
- Otvaranje već postojećeh projekta se svodi na odabiru odgovarajuće `*.pro` ili `CMakeLists.txt` datoteke u okviru projekta.

## 02_qt_aplikacija

Signali i slotovi se koriste za komunikaciju između objekata, a ova dva pojma su centralna funkcionalnost `Qt` `framework`-a zbog kojeg se on i razlikuje od ostalih `framework`-ova slične prirode. Ideja je sledeća: Pretpostavimo da imamo neki prozor i dugme za isključivanje prozora. Kada kliknemo na odgovarajuće dugme, želimo da se pozove `close()` metoda prozora. Ovde možemo da naznačimo četiri ključne komponente:

- **Objekat (aktivni):** `CloseButton`
- **Signal:** `CloseButton::clicked`
- **Objekat (pasivni):** `Window`
- **Slot:** `Window::close()`

![](https://raw.githubusercontent.com/Robotmurlock/MATF-AZRS/main/tema04_qt/images/qt-signals-slots-01.png)

**Signale** se emituju objekti kada se njihovo stanje promeni, a da pritom ta promena može da bude interesantna za neki drugi objekat. Kada se emituju signali, odgovarajući **slotovi** se obično izvršavaju odmah tj. kao normalne funkcije osim ako nije podešeno drugačije. Ukoliko postoji više slotova koji zavise od nekog signala, onda se izvršavaju u odgovarajućem redosledu definisanja `connect` veza. [Detaljnije](https://doc.qt.io/qt-5/signalsandslots.html).

Imamo jednostavnu igricu, gde treba da implementiramo da kada se klikne na odgovarajuće dugme, da se promeni tekst (brojač):

![](https://raw.githubusercontent.com/Robotmurlock/MATF-AZRS/main/tema04_qt/images/qt-signals-slots-02.png)

**Komponente:**

- **Objekat (aktivni):** `pbtnIncrement`
- **Signal:** `CloseButton::clicked`
- **Objekat (pasivni):** `MainWindow`
- **Slot:** `MainWindow::inc`

**Odgovarajući kod (u MainWindow metodi):**

```
connect(
	ui->pbtnIncrement,
	&QPushButton::clicked,
	this,
    &MainWindow::inc
);
```

Za detaljnije objašnjene, pogledajte kod i popratne komentare u kodu.

## 03_qmake

Pogledati `03_qmake`.
