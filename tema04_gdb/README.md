# Uvod u debagovanje

## Bagovi i otklanjanje bagova

**Bag** je greška ili propust u programu ili sistemu zbog koje taj program ili sistem daju pogrešan rezultat, neočekivani rezultat, lošije performanse ili u najgorem slučaju, dovode do pada sistema ili gubljenje podataka. **Debagovanje** je proces otklanjanja bagova u programu ili sistemu. 

Tehnike debagovanja koje znamo:
- Posmatranje i analiza koda;
- Menjanje koda i ponovno pokretanje;
- Dodavanje privremog koda koji služi samo za debagovanje (print);
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

GDB je veoma dominantan na Unix sistemima, ali ima podršku (u teoriji) i za Microsoft Windows i Mac OS.
U praksi neki drugi debageri (LLDB za Mac OS, VSD za Windows) se više koriste na drugim sistemima zbog bolje podrške.

## Uvod u GBD 

Ako želimo da koristimo `gdb` na izvršnoj datoteci, potrebno je da prilikom kompilacije dodamo opciju `-g`, čime kažemo kompilatoru da sačuva tabelu simbola sa odgovarajućim informacijama. To podrazumeva (pored ostalog):
- Imena promenljivih
- Tipove promenljivih
- Informacije od datoteci i liniji gde je promenljiva definisana

Dodavanjem opcije `-g` kompilator potencijalno odbacuje neke optimizacije. To je jedan od razloga zašto često imamo `release` i `debug` verziju programa. 

Debager `gdb` nudi interfejs tj. `TUI (Textual User Interface)`. Za neke jezike postoji i `GUI` podrška.

### Prvi primer (01_basic)

- Izvršiti kompilaciju programa u okviru `01_basic` direktorijuma (potrebno je da se pozicioniramo):
    * `g++ -g -o basic main.cpp`
- Pokrenuti gdb nad izvršnom datotekom:
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
- Program pokrećemo komandom `run`, što se u ovom slučaju svodi na normalno pokretanje programa (kao preko `./a.out`). 



## Reference

[gdb](https://www.gnu.org/software/gdb/)

[Debagovanje-sa-LLDB](https://github.com/Robotmurlock/MSNR-20-4MS/blob/master/05_LLDBDebager_Adzemovic_Mikovic_Spasic_Dobrasinovic.pdf)

[GBD-Tutorial](https://www.youtube.com/watch?v=svG6OPyKsrw&ab_channel=CS246)