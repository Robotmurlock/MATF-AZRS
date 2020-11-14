# CMake

## Šta je CMake?

`CMake` je projekat [otvorenog koda](https://github.com/Kitware/CMake) koji se sastoji iz alata za izgradnju (build), testiranje i rad sa paketima. Omogućava da se proces kompilacije apstrahuje u odnosu
na platformu na kojoj se projekat prevodi. Autor `CMake`-a je [kitware](https://www.kitware.com/).

## Instalacija

### Linux

`sudo apt install cmake`

### Mac

`brew install cmake`

### Windows

[Windows installer](https://cmake.org/download/)

## Prvi primer (01_hello)

- Želimo prvo da vidimo kako funkcioniše `cmake` na jednostavnom `hello world` programu. Nakon toga možemo da vidimo šta tu može da se poboljša.
- Pravimo direktorijum za novi projekat: `mkdir 01_hello`, `cd 01_hello`
- Pravimo `main.cpp` datoteku i okviru nje `hello world` program:
```
#include <iostream>

int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}
```
- Podrazumevano ime za `cmake` datoteku je `CMakeLists.txt` (slično kao `Makefile` za `GNU Make`):
    * `touch CMakeLists.txt` ili odmah `code CMakeLists.txt`
    * Ako koristimo `VSC`, možemo da instaliramo dodatak (plugin) za isticanje (highlighting) koda.
- Potrebno je da napišemo jednostavan `cmake`:
```
cmake_minimum_required(VERSION 3.16)
project(HelloWorld VERSION 1.0.0)

add_executable(hello main.cpp)
``` 
- Objašnjenje:
    * `cmake_minimum_required` definiše minimalnu verziju `cmake`-a. Za izbor verzije je potrebno
    pogledati koje funkcionalnosti koristimo. Tada možemo da izaberemo najstariju verziju koja
    sadrži sve funkcionalnosti. U našem slučaju je dovoljno da stavimo verziju našeg `cmake`.
    Verziju `cmake`-a možemo proveriti komandom: `cmake --version` (3.16.3 u mom slučaju).
    * `project` definiše ime projekta i njegovu verziju preko ključne reči `VERSION`. Ovo takođe
    vrši i neke dodatne funkcije, kao što je npr. definisanje promenljive `PROJECT_NAME` koja u 
    našem slučaju ima vrednost `HelloWorld`. Dereferenciranje promenljivih (dobijanje vrednosti) se vrši preko operatora `$(...)` (kao i kod `GNU Make`).
    * `add_executable` definiše ime izvršne datoteke i ime potrebne izvorne datoteke.
- Želimo da se naš `build` nalazi u posebnom direktorijumu. U suprotnom `cmake` generiše datoteke u
trenutnom radnom direktorijumu, što nije nešto što želimo:
    * `mkdir build`
    * `cd build` (ili `cd !$`, gde je `!$` poslednji argument pretodne komande)
- Pokrećemo `cmake` komandu koja izvršava konfigurisanje, generisanje datoteka za `build`:
    * `cmake -G "Unix Makefiles" ..` 
    * Dodatna opcija `-G "Unix Makefiles"` služi za izbor sistema za generisanje izgradnje (pogledati `man cmake`) 
    * U roditeljskom direktorijumu `..` se nalazi `CmakeLists.txt` datoteka
- Očekivani rezultat:
```
-- The C compiler identification is GNU 9.3.0
-- The CXX compiler identification is GNU 9.3.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/mokoyo/Desktop/ALATI/MATF-AZRS/tema05_cmake/01_hello/build
```
- Primetimo da je `cmake` sam pronašao `C/C++` kompilator. Piše `CXX` umesto `C++` samo kako bi se izbegli problemi u parsiranju. U `build` direktorijumu možemo pronaći sledeće datoteke:
    * `CMakeCache.txt` u kojem se može pronaći niz `KEY:TYPE=VALUE`. Ovde se mogu konfigurisati neke opcije za `cmake`.
    * `cmake_install.cmake`
    * `CMakeFiles`
    * `Makefile`
- Koristeći `Makefile` datoteku, možemo generisati izvršnu datoteku:
    * `make`
- Postoje i dodatne opcije koje su generisane u `Makefile` datoteci preko `cmake` komande. Primer `make help` koja nam daje sve opcije za korisćenje genrisanog `Makefile`-a. Očekivani izlaz:
```
The following are some of the valid targets for this Makefile:
... all (the default if no target is provided)
... clean
... depend
... rebuild_cache
... edit_cache
... hello
... main.o
... main.i
... main.s
```
- Možemo da prevedemo naš kod na asembler:
    * `make main.s`
- Očekivani izlaz: `Compiling CXX source to assembly CMakeFiles/hello.dir/main.cpp.s`
- Rezultat se nalazi na navedenoj relativnoj putanji:
    * `code CMakeFiles/hello.dir/main.cpp.s`
- Naravno, komandom `make` (ili `make hello`) dobijamo izvršnu datoteku koju možemo da pokrenemo.


