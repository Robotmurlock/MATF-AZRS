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

 
## Reference



[Valgrind](https://valgrind.org/)

[Stackoverflow-Joshua-Detwiler](https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks)