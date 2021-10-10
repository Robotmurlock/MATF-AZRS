# Uvod u debagovanje

## Bagovi i otklanjanje bagova

**Bag** je greška ili propust u programu ili sistemu zbog koje taj program ili sistem daju pogrešan rezultat, neočekivani rezultat, lošije performanse ili u najgorem slučaju, dovode do pada sistema ili gubljenje podataka. **Debagovanje** je proces otklanjanja bagova u programu ili sistemu. 

Tehnike debagovanja koje znamo:
- Posmatranje i analiza koda;
- Menjanje koda i ponovno pokretanje;
- Dodavanje privremenog koda koji služi samo za debagovanje (print);
- ...

## Debageri

**Debager** je program (alat) koji se koristi za debagovanje drugog programa. Alati za debagovanje obično nude i neke funkcionalnosti koje ne moraju u potpunosti da budu vezane samo za debagovanje.

Primeri debagera:
- **GDB (the GNU Project debugger)**
- LLDB (LLVM debager)
- Microsoft Visual Studio Debugger
- Valgrind
- ...

Debageri su moćan alat, ali to ne znači da treba uvek da ih koristimo. Ako pretpostavimo da je greška jednostavna, onda možemo da probamo da popravimo tako što koristimo neku prethodno navedenu tehniku. Ako se ispostavi da greška nije trivijalna, onda možemo da uključimo neki naš debager. 

Jedan od najčešćih razloga za teške bagove je upravo rastojanje od izvora greške do neočekivanog ponašanja. U ovim situacijama su veoma bitne metode debagovanja, pa i alati koji se koriste za debagovanje.

# GDB alat

![maskota](https://www.gnu.org/software/gdb/images/archer.svg)

**GDB (the GNU Project debugger)** je debager koji ima podršku za sledeće jezike:
- Ada
- Assembly
- C
- C++
- D
- Fortran
- Go
- Objective-C
- OpenCL
- Modula-2
- Pascal
- Rust

GDB je veoma dominantan na Unix sistemima, ali ima podršku i za Microsoft Windows i Mac OS.
U praksi neki drugi debageri (LLDB za Mac OS, VSD za Windows) se više koriste na drugim sistemima zbog bolje podrške.

## Uvod u GDB 

Ako želimo da koristimo `gdb` na izvršnoj datoteci, potrebno je da prilikom kompilacije dodamo opciju `-g`, čime kažemo kompilatoru da sačuva tabelu simbola sa odgovarajućim informacijama. To podrazumeva (pored ostalog):
- Imena promenljivih
- Tipove promenljivih
- Informacije od datoteci i liniji gde je promenljiva definisana

Dodavanjem opcije `-g` kompilator potencijalno odbacuje neke optimizacije. To je jedan od razloga zašto često imamo `release` i `debug` verziju programa. 

Debager `gdb` nudi interfejs tj. `TUI (Textual User Interface)`. Za neke jezike postoji i `GUI` podrška.

### GDB cheat sheet

Ovde možete da pronađete [gdb cheat sheet](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf).

### 01_basic
```
#include <iostream>

int main() {
    int j = 3;
    int k = 7;

    j += k;
    k = j*2;
    std::cout << "Hello there!" << std::endl;
    return 0;
}
```

- Prvo je potrebno da izvršimo kompilaciju programa u okviru `01_basic` direktorijuma (potrebno je da se pozicioniramo, ako već nismo pozicionirani):
    * `g++ -g -o basic main.cpp`
- Sada možemo da pokrenemo `gdb` nad izvršnom datotekom:
    * `gdb ./basic`
- Očekivani izlaz:
```
GNU gdb (Ubuntu 9.2-0ubuntu1~20.04) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
--Type <RET> for more, q to quit, c to continue without paging--
```
- Ako pretisnemo `ENTER`, dobijemo ostatak:
```
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./basic...
```
- Sada je otvoren `(gdb)` interfejs. Tu možemo da unosimo debager komande.

Program pokrećemo komandom `run` (ili `r` skraćeno), što se u ovom slučaju svodi na normalno pokretanje programa (kao preko `./a.out`). U nastavku komande `run` možemo da dodamo argumente komandne linije. Primer: `run input.txt`. 

Program `gdb` prekidamo komandom `quit`, `q` ili prečicom `ctrl + d`.

Da bi komanda `run` bila smislena, potrebno je da postavimo neki `breakpoint (tačka prekida)`. Koncept `breakpoint`-a je relativno jednostavan. Ideja je da kažemo debageru da zaustavi izvšavanje programa u nekoj tački. Ta tačka može biti:
- Funkcija: `break func_name`
- Linija (apsolutna lokacija): `break line_num`
- Relativna lokacija: `break +offset` `break -offset`
- itd... Pogledati sve mogućnosti [ovde](https://ftp.gnu.org/old-gnu/Manuals/gdb/html_node/gdb_28.html)

**Primer**. Postavljanje `breakpoint`-a na funkciju:

- Postavljamo `breakpoint` na `main` funkciju:
    * `break main` (ili skraćeno `b main`)
- Očekivani oblik izlaza:
```
Breakpoint 1 at 0x5555555551a9: file main.cpp, line 3.
```
- Pokrenimo program:
    * `run`
- Očekivani izlaz:
```
Breakpoint 1, main () at main.cpp:3
3       int main() {
```
- Ako želimo da izvršimo trenutnu liniju i da se zaustavimo na sledećoj liniji, onda to možemo da uradimo preko komande `next` koja pokreće (nastavlja) program i zaustavlja se na sledećoj liniji:
    * `next` (ili skraćeno samo `n`)
- Očekivani izlaz:
```
4           int j = 3;
```
- Ako želimo da vidimo okolinu koda (gde se nalazimo), možemo da pokrenemo komandu `list` koja prikazuje deo izvornog koda:
    * `list` (ili skraćeno `l`)
- Očekivani oblik izlaza:
```
1       #include <iostream>
2
3       int main() {
4           int j = 3;
5           int k = 7;
6
7           j += k;
8           k = j*2;
9           std::cout << "Hello there!" << std::endl;
10          return 0;
```
- Ako želimo da vidimo sadržaj neke promenljive u trenutnom delu koda, to možemo da uradimo preko komande `print` tj. `print [expression]`. Komanda `print` je napredna u smislu da može, pored ispisivanje vrednosti promenljive, da izračuna vrednost izraza. 
    * `run`
    * `next`
    * `print j` (ili skraćeno `p j`), izlaz: `$1 = 0`
    * `next`
    * `print j`, izlaz: `$2 = 3$`
    * `next`
    * `print k`, izlaz: `$4 = 7`
    * `print k+j`, izlaz: `$5 = 10`
    * `print 2*k-3*j`, izlaz : `$6 = 5`

### Drugi primer (02_list)
```
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
} Node;

Node* newNode(int val)
{
    Node n;
    n.value = val;
    n.next = NULL;
    return &n;
}

int main()
{
    Node* n = newNode(5);
    printf("%d\n", n->value);

    return 0;
}
```
- Već imamo `Makefile` implementiran za ovaj program:
    * `make`, izlaz: `list.out`
- Pokrećemo izvršnu datoteku: 
    * `./list.out`
- Očekivana greška:
```
Segmentation fault (core dumped)
```
- Ovo je ona najgora greška koja može da nastane iz više razloga, a kompilator nam daje veoma malo informacija o grešci.
- Ako posmatramo `main` f-ju, do greške je moglo da dođe u f-ji `newNode` ili u f-ji `printf`. 
- Pokrećemo debager:
    * `gdb list.out`
- Postavljamo `breakpoint` na `main`:
    * `b main`, izlaz: `Breakpoint 1 at 0x11b0: file main.c, line 18.`
- Pokrećemo program:
    * `r`, program staje na liniji 18 
- Ova linija sadrži samo `{` i nije nam mnogo interesatna:
    * `n`, izlaz: `Node* n = newNode(5);`
- Ako opet pokrenemo `n`, program će preći na sledeću liniju u `main` f-ji. Ako želimo da uđemo u `newNode()` f-ju, potrebno je da pokrenemo komandu `step` (odnosno `s`):
    * `step`, izlaz: `10      {` (f-ja `newNode` počinje na 9-toj liniji)
- Možemo odmah da pređemo na sledeći liniju
    * `n`
- **Napomena:** Trenutna linija je linija koja još nije izvršena.
- Ako se zagubimo u kodu, uvek možemo da pokrenemo komandu `list`.
- Komandom `p [exp]` možemo da posmatramo promene:
    * `p n.value`
    * `p n.next`
    * `p n` (ovo nam daje `n.value` i `n.next`)
    * `p &n`
- Kada dođemo na liniju `14` i proverimo `n` i `&n`, sve deluje dobro:
    * `n` ima očekivanu vrednost
    * `&n` nije `NULL`
- Probajmo da preskočimo sledeće dve komande u nadi da ćemo se vratitu u `main`. 
- Sada znamo da u `newNode` f-ji ne dolazi do greške, ali ako pokrenemo `p n` na `printf` liniji, onda uviđamo grešku:
    * `p n`, izlaz: `(Node *) 0x0`
- Ovo znači da je `n` zapravo `NULL` pokazivač. To je zato što smo vratili adresu lokalne promenljive koje se briše sa steka nakon što se završi f-ja `newNode`. 
- Ako pređemo na sledeću liniju, dolazimo do greške:
```
Program received signal SIGSEGV, Segmentation fault.
0x00005555555551ce in main () at main.c:20
20          printf("%d\n", n->value);
```
- Umesto da stalno pišemo `next` pa `print n` za svaku liniju, možemo da iskoristimo komandu `display [var_name]`:
    * `display n`
- Svaki put kad se zaustavimo na nekoj liniji (u odgovarajućem opsegu), vrednost ove promenljive se ispiše. Ukoliko u nekom trenutku ne želimo više da se ispisuje vrednost neke promenljive, možemo da iskoristimo komandu `undisplay [var_id]`. **Napomena:** Primetimo da se za `undisplay` piše `[var_id]` umesto `[var_name]`. To je zato što svaka promenljiva (tačnije izraz) koju ispisujemo ima neki svoj `id`.

### Treći primer (03_stack)
```
void A();
void B();
void C() {}
void D();
void E() {}
void F();
void G() {}

void F(){
    D();
}
void D() {
    G();
}
void B(){
    C();
    D();
}
void A(){
    B();
    E();
    F();
}
int main(){
    A();
    return 0;
}
```
Ovo je program koji ne radi ništa, a opet nije toliko jednostavno da se odredi šta se tačno dešava na steku tokom izvršavanja programa. Debuger `gdb` nam tu olakšava posao.

Kompilator je dovoljno pametan da uvidi da je prethodni kod semantički ekvivalentan sledećem kodu:
```
int main(){
    return 0;
}
```
Ovo je nešto što očekujemo sa `-O2` optimizacijom (drugi nivo). Postoji alat [godbolt](https://godbolt.org/) koji će nam pomoći da se uverimo u to. Ovaj sajt nam nudi opciju da pišemo kod, gde nam se sa desne strane prikazuje `asembler` kod. Nas ovde konkretno zanima `C` i `C++`, ali postoje i druge opcije tj. jezici. Ako prekopiramo naš kod, dobićemo odgovarajući asembler kod koji ima oko 50 linija. Svaka linija u našem kodu ima neku boju preko koje možemo da odredimo asembler kod koji odgovara toj liniji. Podrazumevana opcija za prevođenje na asembler kod je `-g`. Možemo da zamenimo tu opciju sa `-O2` i dobićemo asembler kod dužine 15-20 linija. Ovde vidimo da su samo deklarisanje f-je i da `main` f-ja ima samo `return 0`. Povratna vrednost f-je je vrednost u registru `eax`, a `xor eax, eax` postavlja vrednost `eax` na nulu. Sada smo se uverili da je prethodna pretpostavka tačna.

Kada radimo na nekom projektu, želimo da imamo `produkcioni` kod na koji se primenjuje optimizacija nekog nivoa (efikasniji program) i `kod za debagovanje` koji nema nikakve optimizacija i uključuje dodatne opcije koje usporavaju rad programa (manje efikasan program). Zbog toga ima smisla da imamo dve različite `izgradnje (build)` koda tj. jednu za produkciju i jednu za debagovanje. Ako koristimo neko okruženje kao što je `qtcreator`, onda nam on već nudi lak način da se prebacimo sa jednog `build`-a na drugi `build`. Ako radimo u nekom običnom `editor`-u, onda možemo da to izvedemo koristeći `GNU make` tj. `Makefile`. 
```
CXX      = g++ 
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET   = stack
DEBFLAGS = -g
RELFLAGS = -O2

ifneq ($(BUILD),release)
    BUILD = debug
	FLAGS = $(DEBFLAGS)
else
	FLAGS = $(RELFLAGS)
endif

$(BUILD)_$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) $(FLAGS) -o $@ $<

.PHONY: release debug clean

release debug:
	$(MAKE) BUILD=$@

clean:
	rm -r release_$(TARGET) debug_$(TARGET)
```
Ključna razlika u odnosu na klasičan `Makefile` (koji smo do sada viđali) je `grananje`. U zavisnosti od `BUILD` opcije možemo da postavimo određene opcije kompilatoru. Ako pokrenemo `make debug` (ili samo `make`), onda se kod kompilira sa dodatnom opcijom `-g` i ime izvršne datoteke je `debug_stack`, a ako pokrenemo `make release`, onda se kod kompilira sa dodatnom opcijom `-O2` i ime izvršne datoteke je `release_stack`. Alternativan način kompilacije je `make BUILD=debug` i `make BUILD=release`. Sada možemo uporedo da imamo kompiliramo program za debagovanje i produkciju u zavisnosti od potrebe.

- Vratimo se sada na `gdb`. Pokrećemo debager:
    * `gdb debug_stack`
- Postavljamo `breakpoint` na `main`:
    * `b main`
- Pokrećemo program sa `r` i preskačemo prvu liniju sa `n`.
- Očekivana linija je `25` tj. `A();`
- Želimo da uđemo u ovu f-ju: `step`, i da pređemo na sledeću liniju `n`.
- Očekivana linija je `20` tj. `B();`
- Možemo da se podsetimo gde se nalazimo u kodu komandom `list`.
- Preskačemo dve linije i ulazimo u f-ju `F()` komandom `step` i tu preskačemo prvu liniju.
- Očekivana linija je `10` tj. `D();`
- Sada smo verovatno već malo izgubljeni na steku. Ovo je skroz realno situacija ne nekom ozbiljnom kodu. Komandom `backtrace` ili `where`. Očekivani izlaz:
```
#0  F () at main.cpp:9
#1  0x0000555555555196 in A () at main.cpp:22
#2  0x00005555555551a6 in main () at main.cpp:25
```
- Ovde vidimo trenutan stek. Komandama `down` i `up` možemo da se pomeramo po steku. Očekivani izlaz za `up`:
```
#1  0x0000555555555196 in A () at main.cpp:22
22          F();
```
- Očekivani izlaz za `down` nakon prethodne komande:
```
#0  F () at main.cpp:10
10          D();
```
- Ako želimo da zaustavimo program, to možemo da uradimo komandom `kill`.
- Ako želimo da završimo f-ju na trenutnom stek okviru i vidimo njenu povratnu vrednost, to možemo da uradimo komandom `finish`.

### Četvrti primer (04_factorial)
```
#include <iostream>

int a = 3, b = 5, c = 7;

int factorial(int n)
{
    int sol = 1;
    while(n--)
    {
        a = a*c - b;
        sol *= n;
        b = 3*c - a;
        c = 20*a - 7*(a-b+c*c);
    }
    return sol;
}

int main()
{
    std::cout << "5! = " << factorial(5) << std::endl;  
    return 0;
}
```
- Prvo je potrebno da kompiliramo program:
    * `g++ -g -o fact main.cpp`
- Kada pokrenemo program dobijamo sledeći rezultat: `5! = 0`.
- Imamo `bag` koji želimo da popravimo. Pokrećemo debager:
    * `gdb fact`
- U f-ji `factorial` imamo svakakva računanja, ali nas samo interesuje `sol` i `n`. Umesto da idemo liniju po liniju kroz kod i u svakoj liniji da ispisujemo preko `display` vrednosti ovih promenljivih, možemo da postavimo `breakpoint`-ove na kritične lokacije i da preskačemo linije koje nas ne interesuju koristeći komandu `continue` (ili `c` skraćeno). Komanda `continue` je slična kao `run`, samo što nastavlja program umesto da ga opet pokrene:
    * `b 8`
    * `b 11`
    * `b 15`
    * `b 20`
- Pokrećemo program i očekujemo da nas zaustavi na liniji 20. Nastavljamo dalje sa `continue`.
- Ulazimo u f-ju `factorial` i zaustavlja nas na `while` naredbi. Ovde možemo da postavimo ispisivanje promenljivih `n` i `sol` preko `display`, jer smo u odgovarajućem opsegu:
    * `display n`
    * `display sol`
- Nastavljamo dalje... U nekom trenutku stižemo u sledeće stanje:
```
Breakpoint 2, factorial (n=0) at main.cpp:11
11              sol *= n;
1: n = 0
2: sol = 24
```
- Rezultat faktorijel funkcije je već izračunat, ali imamo poslednje množenje sa nulom, pri čemu dobijamo rezultat nula. Ako nastavimo dalje, videćemo da stvarno i jeste problem:
```
Breakpoint 1, factorial (n=0) at main.cpp:8
8           while(n--)
1: n = 0
2: sol = 0
```
- Iz f-je `factorial` izlazimo sa `sol = 0`.
- Program na kraju ispisuje `5! = 0`.
- Popravka:
```
while(n)
{
    a = a*c - b;
    sol *= n;
    b = 3*c - a;
    c = 20*a - 7*(a-b+c*c);
    n--;
}
```
- Sada program radi kako to i želimo.

Postoji i alternativni način i bolji način za debagovanje ovog problema korišćenjem komande `watch` koja postavlja `watchpoint` na promenljivu (izraz). U tom slučaju se program zaustavlja svaki put kada se ta promenljiva (izraz) promeni, što je u suštini baš ono što smo mi želimo i što smo simulirali u prethodnom rešenju. 

- Pokrećemo opet program: 
    * `gdb fact`
- Postavljamo `breakpoint` na `factorial` f-ju i pokrećemo program:
    * `b factorial`
    * `run`
- Program bi trebalo da se zaustavi na početku `factorial` f-je. Postavljamo `watchpoint`-ove:
    * `watch sol`
    * `watch n`
- Sada možemo da nastavljamo program sa komandom `continue` i posmatra šta se dešava i kako se menjaju promenljive. Možemo nastavljati program i sa `ENTER`.

Ponekad želimo da neki `watchpoint` ili `breakpoint` obrišemo ili isključimo, pa kasnije opet uključimo. Za to postoje komande `delete [breakpoint/watchpoint]`, `disable [breakpoint/watchpoint]`, `enable [breakpoint/watchpoint]`. Postoji i komanda `clear` koja briše sve `breakpoint`-ove.

Postoji komanda `info` koja može da nam da svakakve informacije u zavisnosti od argumenta:
- `info args`, ispisuje argumente f-je na trenutnom stek okviru;
- `info breakpoint`, ispisuje informacije o `breakpoint`-ovima;
- `info display`;
- `info locals`, ispisuje informacije o lokalnim promenljivima na trenutnom stek okviru;
- `info threads`, ispisuje informacije o nitima;
- `info watchpoint`, ispisuje informacije o `watchpoint`-ovima;
- itd...

Postoji komanda `whatis` koja može da nas podseti kojeg je šta je neka promenljiva tj. kojeg je ona tipa:
- `whatis sol`, izlaz: `type = int`

### Peti primer (05_parser)

Primeniti prethodno naučeno znanje i popraviti program.

Problem: `05_parser/main.cpp`

Rešenje: `05_parser/solution.cpp`

## LLDB

Alternativa za `gdb` debager je `lldb` (`LLVM` projekat) debager koji se koristi na sličan način. Debager `lldb` se pokreće preko komandne linije za debagovanje `C`, `C++` ili `Objective C` programskog jezika. Komande se razlikuju, ali postoji [mapa](http://lldb.llvm.org/use/map.html) preslikavanja komandi. Ovaj debager je verovatno bolje koristiti na `MacOS`-u, zbog bolje podrške, a `gdb` je bolji za `unix` sisteme (jer duže postoji i ima implementirane sve funkcionalnosti). Debager `lldb` je implementiran u modernijem `c++`-u i ima potencijala da u budućnosti zameni `gdb` i na `unix` sistemima.

## Reference

[gdb](https://www.gnu.org/software/gdb/)

[Debagovanje-sa-LLDB](https://github.com/Robotmurlock/MSNR-20-4MS/blob/master/05_LLDBDebager_Adzemovic_Mikovic_Spasic_Dobrasinovic.pdf)

[GBD-Tutorial](https://www.youtube.com/watch?v=svG6OPyKsrw&ab_channel=CS246)
