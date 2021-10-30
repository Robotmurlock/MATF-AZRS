# Qt Framework

**Qt (cute)** je `framework` za razvoj softvera koji nam nudi podršku za različite platforme, kao
i razvoj `GUI` aplikacija. 

## Qt Instalacija

### Linux
`sudo apt-get install build-essential`\
`sudo apt-get install qtcreator`\
`sudo apt-get install qt5-default`
    
#### Linux docs i API:
``sudo apt install `apt-cache search 5-examples | grep qt | grep example | awk '{print $1 }' | xargs` ``\
``sudo apt install `apt-cache search 5-doc | grep "Qt 5 " | awk '{print $1}' | xargs` ``\
`sudo apt-get install build-essential qtcreator qt5-default`
  
#### Ako nešto nedostaje: 
``sudo apt install `apt-cache search qt | grep 5- | grep ^qt | awk '{print $1}' | xargs` ``

#### izvor: 
[qt linux installation guide](https://doc.qt.io/qt-5/linux.html)`\
[stackoverflow linux installation guide](https://stackoverflow.com/questions/48147356/install-qt-on-ubuntu)
    
  --- 
### Mac:
[qt macos installation guide](https://doc.qt.io/qt-5/macos.html)
    
  ---
### Windows: 
[qt windows installation guide](https://doc.qt.io/qt-5/windows.html)

## Upustvo za dodavanje cppreference u Qt Creator

### Skidanje cppreference knjige
1. Otvoriti zvaničnu cppreference stranicu: [cppreference](https://en.cppreference.com);
2. Kliknuti na `offline archive` pri dnu u okviru sekcije `News`;
3. Pronaći sekciju `Qt help book` i tu kliknuti na zipovan `qch book`;
4. Skinuti `qch book` (Napomena: Ako ne može da se skine preko Chrome pretraživača, skinuti preko drugog pretraživača).

### Dodavanje cppreference u Qt Creator (pogledati cppreference.pdf datoteku)
1. Otvoriti Qt creator; 
2. Kliknuti na `Tools` u opcijama na vrhu, pa na `Options...`;
3. Kliknuti na `Help` sa leve strana;
4. Pri vrhu kliknuti na `Documentation`;
5. Kliknuti na `Add...` i dodati `*.qch` fajl.

### Korišćenje cppreference u okviru Qt Creator-a
Sada se u okviru Qt moze koristiti cppreference tako sto se klikne na `Help`
sa leve strane i u opcijama izabrati cppreference.

