# Valgrind

[Valgrind](https://valgrind.org/) je `framework` za alate za dinamički analizu programa. Koristi se kao pomoć u otklanjanju bagova sa memorijom i nitima. Dakle, `Valgrind` je debager, jer predstavlja alat za debagovanje. Ovaj alat se pretežno koristi za `C/C++`.

## Instalacija

### Linux

`sudo apt install valgrind` (Ubuntu, Debian, etc.)
`sudo yum install valgrind` (RHEL, CentOS, Fedora, etc.)

## Uvod u Valgrind (01_malloc)

Najbolje da prvo testiramo `Valgrind` na nekom jednostavnom primeru:
```
#include <stdlib.h>

int main() {
    char* string = malloc(5 * sizeof(char)); //LEAK: not freed!
    return 0;
}
```
- Unapred znamo da dolazi do curenja memorije koju ne oslobađamo nakon što pozovemo `malloc`.
- Postoje `man` strane za `Valgrind` dokumentaciju: `man valgrind`.
- Analizu započinjemo komandom `valgrind [options] [exe_file]` na izvršnom datotekom.

Opcije:
- `--leak-check=full`: Ispisuje u detalje svako curenje memerije;
- `--show-leak-kinds=all`: Prikazuje `definite, indirect, possible, reachable` tipove curenja memorije (`definite, possible` su podrazumevani);
- `--track-origins=yes`: Pomaže u pronalaženju uzroka curenja memorije, ali značajno usporava rad analize;
- `--log-file=[output_file]`: Izlaz smešta u izabranu datoteku.

Konačno:
```
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --log-file=log.txt \
         ./main.out
```
- Sada možemo da pogledamo `log.txt` datoteku (ovde je podeljeno na više delova):
```
Memcheck, a memory error detector
Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
```
- Informacije o licenci i verziji `Valgrind`-a. Ovaj deo nam nije toliko interesantan trenutno.
- Prefiks svake linije je izbačen zbog vidljivosti.
```
Command: ./main.out
Parent PID: 4994
```
- Ime programa i `PID (Process ID)` programa. 
```
HEAP SUMMARY:
    in use at exit: 5 bytes in 1 blocks
  total heap usage: 1 allocs, 0 frees, 5 bytes allocated
```
- Ovde vidimo da je pri kraju programa ostalo 5 bajtova u memoriji (što jeste tačno, jer smo toliko i alocirali).
- Takođe vidimo da imamo jednu alokaciju i nula oslobađanja (curenje memorije).
```
5 bytes in 1 blocks are definitely lost in loss record 1 of 1
   at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x10915E: main (in /home/mokoyo/Desktop/ALATI/MATF-AZRS/tema06_valgrind/01_malloc/main.out)
```
- Ovaj deo predstavlja niz blokova memorije koji su procureli. 
- Vidimo da je `malloc` u `main`-u "izazvao" curenje memorije. To nam je dovoljno informacija da sada ispravimo grešku za ovaj jednostavan program. Šta ako imamo 15 poziva `malloc` u `main`-u?
```
LEAK SUMMARY:
   definitely lost: 5 bytes in 1 blocks
   indirectly lost: 0 bytes in 0 blocks
     possibly lost: 0 bytes in 0 blocks
   still reachable: 0 bytes in 0 blocks
        suppressed: 0 bytes in 0 blocks

For lists of detected and suppressed errors, rerun with: -s
ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
- Ovde vidimo krajnje statistike.

- Bilo bi mnogo mnogo bolje kad bi `Valgrind` mogao da nam preciznije kaže gde je došlo do curenja memorije (npr. linija komande koja je alocirala blok koji nije oslobođen). Odgovor je pozitivan. Potrebno je da prevedemo naš program sa opcijom `-g` čime dodajemo potrebne informacije: `gcc -g -o main.out main.c`
- Ako opet pokrenemo `valgrind` komandu, onda ćemo videti sledeće:
```
5 bytes in 1 blocks are definitely lost in loss record 1 of 1
   at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x10915E: main (main.c:4)
```
- Tačno znamo koji blok nije oslobođen sad!
- Ako dodamo `free(string);` na na kraj `main` f-je dobijamo sledeći očekivani rezultat:
```
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: 1 allocs, 1 frees, 5 bytes allocated

All heap blocks were freed -- no leaks are possible

For lists of detected and suppressed errors, rerun with: -s
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
- Ovo je idealan slučaj: `All heap blocks were freed -- no leaks are possible`.
- **Napomena:** `Valgrind` nam govori koji blok je alociran, a nije oslobođen i na to nam je i pokazao u kodu.

## Primer izgubljene reference (02_function_local_pointer)

Imamo sledeći kod:
```
#include <stdlib.h>
#include <stdint.h>

struct _List {
    int32_t* data;
    int32_t length;
};
typedef struct _List List;

List* resizeArray(List* array) {
    int32_t* dPtr = array->data;
    dPtr = realloc(dPtr, 15 * sizeof(int32_t)); //doesn't update array->data
    return array;
}

int main() {
    List* array = calloc(1, sizeof(List));
    array->data = calloc(10, sizeof(int32_t));
    array = resizeArray(array);

    free(array->data);
    free(array);
    return 0;
}
```
- Ovo je slična greška koja se pojavljuje u jednom primeru za `gdb` alat. Međutim, ovaj program ima `nevidljiv` bag u smislu da ako pokrenemo program, on će raditi bez problema. Ovaj bag utiče samo na performanse (koristi više memorije). Ako pokrenemo program, možemo čak da pomislimo da sve radi kako treba. Uvek možemo `za svaki slučaj` da pokrenemo `valgrind`:
```
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --log-file=log.txt \
         ./main.out
```
- Očekivani oblik izlaza:
```
Invalid free() / delete / delete[] / realloc()
   at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x109215: main (main.c:21)
 Address 0x4a61090 is 0 bytes inside a block of size 40 free'd
   at 0x483DFAF: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x1091B4: resizeArray (main.c:12)
   by 0x109202: main (main.c:19)
 Block was alloc'd at
   at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x1091EC: main (main.c:18)
```
- Možemo da primetimo sledeće iz prvog dela analize:
    * Imamo jedno neuspešno oslobadjanje (npr. oslobadjanje pogrešno bloka).
    * Blok od 40 bajtova tj. `calloc(10, sizeof(int32_t))` blok je oslobođen u f-ji `realloc` na `12.` liniji, što je i očekivano ponašanje. 
    * Blok od 60 bajtova tj. `realloc(dPtr, 15 * sizeof(int32_t))` blok nije oslobođen i procureo je.
```
 HEAP SUMMARY:
     in use at exit: 60 bytes in 1 blocks
   total heap usage: 3 allocs, 3 frees, 116 bytes allocated
 
 60 bytes in 1 blocks are definitely lost in loss record 1 of 1
    at 0x483DFAF: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
    by 0x1091B4: resizeArray (main.c:12)
    by 0x109202: main (main.c:19)
 
 LEAK SUMMARY:
    definitely lost: 60 bytes in 1 blocks
    indirectly lost: 0 bytes in 0 blocks
      possibly lost: 0 bytes in 0 blocks
    still reachable: 0 bytes in 0 blocks
         suppressed: 0 bytes in 0 blocks
 
 For lists of detected and suppressed errors, rerun with: -s
 ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```
- Ovde vidimo da postoje 3 alokacije i 3 dealokacije. Pošto je jedna dealokacije neuspešna, ostaje nam jedan procureo blok.
- Razlog zašto je blok iz f-je `resizeArray` procureo je zbog toga štoa `array->data` nije ažuriran. Ako se doda linija `array->data = dPtr` pre `return` naredbe, problem je rešen.
- **Problem:** izgubljena referenca na blok memorije.

## RAII (03_raii)

- Zadatak nam je da učitamo uzorak iz `input.txt` datoteke i izračunamo sredinu i standardnu devijaciju tog uzorka koristeći dinamičke nizove u c-u:

![mean](https://latex.codecogs.com/svg.latex?mean(x)%20=%20\frac{\sum_{i=1}^{n}x_i}{n})

![std](https://latex.codecogs.com/svg.latex?std(x)%20=%20\sqrt{\frac{\sum_{i=1}^{n}(\overline{x}-x_i)^2}{n-1}})

- Imamo dve problematične operacije ovde:
  * Otvaranje datoteke `input.txt` (potrebno ju je zatvoriti);
  * Alokacija memorije za niz (potrebno je osloboditi memoriju);
- U sledećim situacijama je potrebno prekinuti program:
  * Ako datoteka ne postoji (ovo nije problematično, jer se datoteka ne otvara i niz se ne alocira);
  * Ako je `n<0`, gde je `n` prvi veličina uzorka (čita se iz datoteke);
  * Ako je `n=1`;
  * Ako je neki broj u nizu jednak `666`.
- Ono što je posebno problematično u ovom slučaju je to što curenje memorije ne nastaje uvek. Nema curenja memorije u slučaju ispravnog ulaza. Ovde je korisno da se prave `unit` testovi za specijalne slučajeve (`za domaći`).

### main_v1.c

- Pogledajmo sledeći ulaz:
```
5
1 2 3 4 5
```
- Za ovaj ulaz nam `valgrind ./main.out` daje sledeći izlaz:
```
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: 4 allocs, 4 frees, 5,632 bytes allocated

All heap blocks were freed -- no leaks are possible
```
- Pogledajmo sledeći ulaz:
```
5
1 2 666 4 5
```
- Za ovaj ulaz nam `valgrind ./main.out` daje sledeći izlaz:
```
HEAP SUMMARY:
    in use at exit: 512 bytes in 2 blocks
  total heap usage: 4 allocs, 2 frees, 5,632 bytes allocated

LEAK SUMMARY:
   definitely lost: 40 bytes in 1 blocks
   indirectly lost: 0 bytes in 0 blocks
     possibly lost: 0 bytes in 0 blocks
   still reachable: 472 bytes in 1 blocks
        suppressed: 0 bytes in 0 blocks
```

### main_v2.c

- Možemo da vodimo računa da u svakom trenutku oslobodimo sve resurse pre nego što prekinemo funkciju. 
- Problem kod ovog rešenja je što previše puta pišemo sličan kod za oslobađanje resursa, a velike su šanse da nam nešto promakne u nekom slučaju.

### main_v3.c

- Bolje rešenje je da imamo jednu promenljivu `status` u kojoj čuvamo status funkcije:
  * `OKAY       0`
  * `NEGATIVE_N 1`
  * `SMALL_N    2`
  * `EVIL       4`
- Funkcija se "uvek" izvršava do kraja. Na kraju funkcije se oslobađaju resursi i proverava se status funkcije. U ovom slučaju je to `check_status` funkcija. Na ovaj način manje razmišljamo o oslobađanju memorije u svakom specijalno slučaju. Jedini nezgodan slučaj koji ostaje je neuspešna alokacija niza, jer tada tada ne smemo da koristimo taj resurs (taj slučaj rešavamo na isti način). Takođe ovo rešenje nam omogućava da ispišemo sve greške koje su se desile ako nam je to od koristi. Potrebno je samo da koristimo stepeni dvojke za makroe ili enume i posmatramo celobrojnu promenljivu kao registar sa zastavicama. Ako je vrednost bita `1`, onda je došlo do te greške, a u suprotnom nije došlo do te greške. Ako je vrednost tog registra `0` svuda, onda nije došlo do greške.
- Ovo predstavlja bolju praksu za programiranje u C-u, ali i dalje moramo da vodimo računa da ne koristimo resurse koji su "pokvareni".

### main_v4.cpp

- Ako radimo u `C++`-u, postoji mnogo lakše rešenje: `RAII (Resource Acquisition Is Initialization)`. Ideja je jednostavna: Želimo da spojimo životni vek resursa sa životnim vekom objekta:
  * Pravimo `raii` strukturu za rad sa datotekama (ne koristimo klase i enkapsulaciju, jer želimo da nam kod što više liči na početni).
  * Pravimo `raii` struktura za rad sa dinamičkim nizovima.
- Ovi objekti funkcionišu na sledeći način:
  * Konstruktor zauzima resurse;
  * Destruktor oslobađa resurse.
- **Dobitak:** Gde god da prekinemo funkciju, poziva se destruktor objekta i oslobađa se memorija. 

### main_v5.cpp

- Još bolje rešenje je da koristimo strukture (klase) koje već postoje u `C++`-u:
  * Vektor je `raii` dinamički niz;
  * Strimovi mogu da zamene rad sa datotekama.

## Reference



[Valgrind](https://valgrind.org/)

[Stackoverflow-Joshua-Detwiler](https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks)