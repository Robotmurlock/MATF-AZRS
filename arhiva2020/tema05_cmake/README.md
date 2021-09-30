# CMake

## Šta je CMake?

`CMake` je projekat [otvorenog koda](https://github.com/Kitware/CMake) koji se sastoji iz alata za izgradnju (build), testiranje i rad sa paketima. Omogućava da se proces kompilacije apstrahuje u odnosu
na platformu na kojoj se projekat prevodi. `CMake`-a je proizvod [kitware](https://www.kitware.com/)-a.

## Instalacija

### Linux

`sudo apt install cmake`

### Mac

`brew install cmake`

### Windows

[Windows installer](https://cmake.org/download/)

## Uvod u CMake (01_hello)

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
    * `touch CMakeLists.txt` ili `code CMakeLists.txt`
    * Ako koristimo `VSC`, možemo da instaliramo dodatak (plugin) za rad sa `CMake` i dodatak isticanje (highlighting) koda.
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
    * `project` definiše ime projekta i njegovu verziju preko ključne reči `VERSION`. Ova komanda takođe
    vrši i neke dodatne operacije, kao što je npr. definisanje promenljive `PROJECT_NAME` koja u 
    našem slučaju ima vrednost `HelloWorld`. Dereferenciranje promenljivih (dobijanje vrednosti) se vrši preko operatora `$(...)` (kao i kod `GNU Make`).
    * `add_executable` definiše ime izvršne datoteke i ime potrebnih izvornih datoteka.
- Želimo da se naš `build` nalazi u posebnom direktorijumu. U suprotnom `cmake` generiše datoteke u
trenutnom radnom direktorijumu, što nije nešto što želimo:
    * `mkdir build`
    * `cd build` (ili `cd !$`, gde je `!$` poslednji argument prethodne komande)
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
- Postoje i dodatne opcije koje su generisane u `Makefile` datoteci preko `cmake` komande. Primer `make help` koja nam daje sve opcije za korisćenje generisanog `Makefile`-a. Očekivani izlaz:
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

## Biblioteka (02_library)

Želimo da napravimo biblioteku za rad sa niskama u `C++`-u. Standardna biblioteka nam već nudi `string` 
klasu sa funkcijama i metodama za rad sa niskama, ali postoje neke funkcije koje su nam bitne, ali se tu ne nalaze. Jedna veoma korisna f-ja, koja nije implementirana u okviru standardne biblioteke je `split` funkcija, koja prima dva argumenta: nisku i karakter razdvajanja `delimiter` i vraća niz niski razdvojenih
po tom specijalnom karakteru. Primer:
- `split("Ahoy there matey!", ' ') = ["Ahoy", "there", "matey"]`
- `split("123,456,789", ',') = ["123", "456", "789"]`

- Želimo da implementiramo ovu funkciju u našoj biblioteci i da je testiramo. Za testiranje pišemo odvojen kod `test.cpp`, a kompilaciju celog koda želimo da apstrahujemo preko `cmake`.
- Za testiranje biblioteke koristimo [Arange-Act-Assert](https://wiki.c2.com/?ArrangeActAssert) obrazac bez nekog naprednog `framework`-a za testiranje, već samo `assert` funkciju iz `assert.h` tj. `cassert` biblioteke.
- **Napomena:** Pogledati kod za datoteke `string_lib.cpp` `string_lib.hpp` i `test.cpp` u `02_library`
direktorijumu.
- Potrebno je da se napravi izvršna datoteka na osnovu prethodno navedenog izvornog koda:
    * `code CMakeLists.txt`
- Već znamo da napišemo osnovne elemente `cmake` datoteke:
```
cmake_minimum_required(VERSION 3.16)
project(SplitLibrary VERSION 1.0.0)

add_executable(run_test test.cpp)
```
- U odnosu na prethodni primer, potrebne su nam dve stvari: Dodavanje biblioteka i linkovanje biblioteka sa objektnim kodom.
- Za dodavanje biblioteka za prevođenje se koristi `add_library`:
```
add_library(
    string_library
    string_lib.hpp
    string_lib.cpp
)
```
- Prvo se navodi ime biblioteke, pa onda redom potrebne datoteke:
```
add_library(
    <name>
    [source1]
    [source2]
    ...
    [sourceK]
)
```
- Nakon toga je potrebno da se definiše linkovanje preko `target_link_libraries`:
    * `target_link_libraries(run_test PRIVATE string_library)`
- Prvo se navodi ime ciljne izvršne datoteke, pa ime biblioteke:
    * `target_link_libraries(<name> ... <lib_name> ...)`
- Konačan oblik `CMakeLists.txt` datoteke:
```
cmake_minimum_required(VERSION 3.16)
project(SplitLibrary VERSION 1.0.0)

add_library(
    string_library
    string_lib.hpp
    string_lib.cpp
)

add_executable(run_test test.cpp)

target_link_libraries(run_test PRIVATE string_library)
```
- Sada možemo da napravimo `build` direktorijum i da pokrenemo `cmake`:
    * `mkdir build`
    * `cd build`
    * `cmake -G "Unix Makefiles" ..`
- Možemo da iskoristimo generisan `Makefile` da dobijemo izvršnu datoteku:
    * `make`
- Pokrećemo testove:
    * `./run_test`
- Očekivani izlaz: `Tests passed!`
- **Napomena:** Ako promenimo kod, ne moramo opet da pokrećemo `cmake`, već će to biti urađeno kada pokrenemo komandu `make` (ne moramo da se brinemo o konfiguraciji projekta).



- Kada koristimo `add_library`, podrazumevan tip biblioteke je `STATIC`. Alternativni tipovi su `SHARED` i `MODULE`. Tip se navodi nakon imena (ako se navede):
```
add_library(
    <name>
    [STATIC|SHARED|MODULE]
    [source1]
    [source2]
    ...
    [sourceK]
)
```
- Tip `MODULE` se koristi da se označi da biblioteka predstavlja neki `plugin` i ne treba da se linkuje.
- Razlike između `STATIC` i `SHARED`:
    * Ako je biblioteka `STATIC`, onda se kod biblioteke direktno povezuje sa programom za vreme kompilacije. Program kopira kod biblioteke koji dodaje na svoj kod.
    * Ako je biblioteka `SHARED`, onda se kod biblioteke referencira od strane programa za vreme izvršavanja. 
    * Biblioteke tipa `STATIC` zauzimaju više mesta (veće binarne datoteke). Kod je već tu, pa ne postoji
    dodatan trošak referenciranja.
    * Biblioteke tipa `SHARED` zauzimaju manje mesta, ali su odvojene i samim tim zauzimaju manje mesta i imaju dodatni trošak. Prednost je u tome što se biblioteka može zameniti sa sličnom bibliotekom koja možda ima bolje performanse u nekim slučajevima a da se pritom ne prevodi opet kod.

## Projekat (03_project)

- Želimo da iskoristimo biblioteku iz prethodnog primera da implementiramo program koji vraća broj linija i broj reči ulazne datoteke. Demonstracija:
```
This is first line
This line has 5 words
This line does not have 5 words
This is just another line
Savvy
```
- Ako pokrenemo program, željeni izlaz je:
```
Number of lines: 5
Number of words: 22
```
- Sada već imamo malo komplikovaniji projekat i želimo da ga organizujemo u poddirektorijume:
    * `lib` direktorijum koji sadrži prethodno napisanu biblioteku sa testovima.
    * `src` direktorijum koji sadrži kod programa.
    * `root` direktorijum tj. roditeljski direktorijum.
- Pravimo `CMakeLists.txt` za `lib` i `root` direktorijume.
- Dodatno pravimo `build` direktorijum.
- Već imamo stari `CMakeLists.txt` za `lib` direktorijum. Potrebno je izvršiti modifikacije.
- Korenski `CMakeLists.txt`:
```
cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

add_subdirectory(string_lib)

add_executable(myprogram src/main.cpp)

target_link_libraries(myprogram PRIVATE string_lib)
```
- Nova komanda je `add_subdirectory`. Ovu komandu koristimo kada želimo da dodamo neki poddirektorijum, što u ovom slučaju želimo da uradimo za `lib` direktorijum. Dobijamo sličnu funkcionalnost kao da smo kopirali kod iz `CMakeLists.txt` iz poddirektorijuma i ažurirali relativne putanje. Datoteka `CMakeLists.txt` u `lib` direktorijumu:
```
add_library(
    string_lib
    string_lib.hpp
    string_lib.cpp
)

target_include_directories(string_lib PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")
```
- Još jedna opcija kojom definišemo `include` putanju do biblioteke, što nam omogućava da ne razmišljamo o relativnim putanjama. Umesto `#include "../string_lib/string.lib.hpp"` možemo da napišemo sad `#include <string_lib.hpp>`.
- Sada možemo da konfigurišemo projekat u `build`-u sa `cmake -G "Unix Makefiles" ..`
- Očekivani oblik izlaza:
```
-- Configuring done
-- Generating done
-- Build files have been written to: /home/mokoyo/Desktop/ALATI/MATF-AZRS/tema05_cmake/03_project/build
```
- Sada možemo da pokrenemo generisani `Makefile`:
    * `make`
- Očekivani oblik izlaza:
```
[ 25%] Building CXX object string_lib/CMakeFiles/string_lib.dir/string_lib.cpp.o
[ 50%] Linking CXX static library libstring_lib.a
[ 50%] Built target string_lib
[ 75%] Building CXX object CMakeFiles/myprogram.dir/src/main.cpp.o
[100%] Linking CXX executable myprogram
[100%] Built target myprogram
```
- Očekivani izlaz za pokrenut program:
```
Number of lines: 5
Number of words: 22
```

Kod opcije `target_include_directories` koristili smo ključnu reč `PUBLIC`. Alternative su `PRIVATE` i `INTERFACE`. Kada `CMake` kompilira ciljnu izvršnu datoteku, on koristi `INCLUDE_DIRECTORIES`, `COMPILE_DEFINITIONS` i `COMPILE_OPTIONS` promenljive. Kada koristimo `PRIVATE` opciju, `CMake` dopunjuje ove promenljive. Slična priča je i za `INTERFACE`, samo sa prefiksom `INTERFACE_*`. Ključna reč `PUBLIC` je kombinacija `PRIVATE` i `INTERFACE`. Za detaljnije informacije pogledati sledeći [artikal](https://leimao.github.io/blog/CMake-Public-Private-Interface/) ili [dokumentaciju](https://cmake.org/cmake/help/latest/command/target_include_directories.html).

## Pisanje skriptova (04_script)

Jezik `CMake` je jednostavan intepretirani jezik za skriptovanje koji nudi jednostavne funkcionalnosti kao što su: promenljive, manipulacija niski, rad sa nizovima, funkcije i ostalo. 

### Sintaksa

Oblik komandi u `CMake` je `command(<arg1> <arg2> ... <argK>)`. Komande se izvršavaju jedna za drugom.
Pored komandi, možemo da pišemo i komentare, gde je sintaksa ista  kao u `Python`-u tj. komentar počinje sa `#`.

**Napomena:** Pogledati `CMakeLists.txt` u `04_script` direktorijumu koji sadrži sve primere koji slede u nastavku.

### Promenljive i poruke

Promenljive se mogu definisati komandom `set(<name> <value>)`. Vrednosti promenljivih se dobijaju dereferenciranjem: `${<name>}`.

Poruke se pišu komandom `message([mode] <text1> <text2> ... <textK>)`, gde se vrši konkatenacija niza argumenata niski u jednu nisku i ispisuje na standardni izlaz. Za uvid u ostale modove, pogledati [ovde](https://cmake.org/cmake/help/latest/command/message.html). Važno je znati da `CMake` sve tritara kao niske. Ako želimo da dodelimo vrednost koja ima razmake, onda je potrebno da stavimo vrednost pod navodnike. Primer:
    * Izlaz za `message(STATUS One Two Three)` je `OneTwoThree`.
    * Izlaz za `message(STATUS "One Two Three")` je `One Two Three`.

- Posmatrajmo sledeći kod:
```
set(MY_VAR "[1, 2, 3, 4]")
message(STATUS "This is my variable \"${MY_VAR}\" and this is my project name \"${PROJECT_NAME}\"")
```
- Očekivani izlaz je:
```
This is my variable "[1, 2, 3, 4]" and this is my project name "MyProject"
```
- Komanda `project` takođe definiše promenljivu `PROJECT_NAME` koja sadrži ime projekta. Ovo važi i za mnoge druge komande u `CMake`-u.

### Kontrola toka

Sintaksa za `if-else`:
```
if(<condition>)
  <commands>
elseif(<condition>) # optional block, can be repeated
  <commands>
else()              # optional block
  <commands>
endif()
```
- Vrednost izraza `<condition>` je tačna ako nije netačna.
- Vrednost izraza `<condition>` je netačna ako se nalazi na [listi](https://cmake.org/cmake/help/latest/command/if.html) netačnih vrednost u dokumentaciji. Primer `FALSE` ima netačnu vrednost.
- Operator `STREQUAL` služi za poređenje niski:
    * `<lhs> STREQUAL <rhs>`
- Postoje operatori `NOT`, `AND` i `OR` i imaju očekivano ponašanje:
    * `NOT <condition>`
    * `<lhs> AND <rhs>`
    * `<lhs> OR <rhs>`
- Postoji operator `MATCH` za proveru da li se neka niska poklapa sa nekim regularnim izrazom:
    * `<lhs> MATCHES <rhs>`

U sledećim primerima su demonstrirani prethodno spomenuti operatiro:
```
if("TRUE")
    message("Example A - Case 1")
else()
    message("Example A - Case 2")
endif()

if("FALSE")
    message("Example B - Case 1")
else()
    message("Example B - Case 2")
endif()

If("This is an array [1, 2, 3, 4, 5]" MATCHES ".*[\[]([0-9]|,|[ ])+[\]].*")
    message("Example C - String contains an array!")
else()
    message("Example C - String doesn't contain an array!")
endif()
```
- Očekivani izlaz:
```
Example A - Case 1
Example B - Case 2
Example C - String contains an array!
```

Takođe, možemo koristiti petlje tj. `while` sa sledećom sintaksom:
```
while(<condition>)
  <commands>
endwhile()
```

- Za vežbu možemo napisati kod koji ispisuje neku poruku 10 puta. Brojač možemo da definišemo kao promenljivu koja ima početnu vrednost 0 i petlja se izvršava dok je vrednost brojača manja od 10. Ovde nam nedostaju logički operatori za proveru uslova petlji i aritmetički operatori za ažuriranje promenljive brojača.
- Logički operatori `LESS`, `GREATER` i `EQUAL` vraćaju tačnu ili netačnu vrednost i imaju očekivano ponašanje:
    * `<lhs> LESS <rhs>`
    * `<lhs> GREATER <rhs>`
    * `<lhs> EQUAL <rhs>`
- Komanda `math` tj. `math(EXPR <name> <expression>)` dodeljuje vrednost izraza `<expression>` promenljivoj `<name>`.
- Sada imamo sve što nam je potrebno da završimo ovu vežbu:
```
set(cnt 0)
while(cnt LESS 10)
    message(STATUS "Counter value is ${cnt}!")
    math(EXPR cnt "${cnt} + 1")
endwhile()
```
- Očekivani izlaz:
```
Counter value is 0!
Counter value is 1!
Counter value is 2!
Counter value is 3!
Counter value is 4!
Counter value is 5!
Counter value is 6!
Counter value is 7!
Counter value is 8!
Counter value is 9!
```

Postoje i `foreach` petlje i ovde možemo videti primer jednog korišćenja `foreach` petlje:
```
foreach(item IN ITEMS apple orange peach banana)
    message(STATUS "Look at this ${item}!")
endforeach()
```
- Očekivani izlaz:
```
Look at this apple!
Look at this orange!
Look at this peach!
Look at this banana!
```
- Još jedan primer `foreach` petlje sa `RANGE` operatorom koji ima dva oblika:
    * `RANGE N` su vrednosti od 0 do N.
    * `RANGE A B` su vrednosti od A do B.
```
foreach(idx RANGE 100) 
    message(STATUS "idx = ${idx}")
endforeach()
```

### Funkcije

Sintaksa za pisanje funkcija je sledeća:
```
function(<name> [<arg1> ...])
  <commands>
endfunction()
```
- Primetimo da ne postoji povratna vrednost. To se može prevazići i to ćemo videti u nastavku.
- Primer jedne jednostavne funkcije:
```
function(show_name my_name)
    message(STATUS "My name is ${my_name}!")
endfunction()

show_name("Robotmurlock")
show_name("Banana" "Ignore This")
```

- Ako u funkciju prosledimo više parametara nego što ona ima argumenata, onda funkcija ignoriše taj višak parametara. 
- Ako u funkciju prosledimo manje parametara nego što ona ima argumenata, onda dobijamo poruku o grešci.
- Ukoliko želimo da implementiramo funkciju koja može da primi proizvoljan broj parametara, onda to možemo uraditi korišćenjem specijalne promenljive `ARGV` (lista):
```
function(show_words)
    foreach(arg IN LISTS ARGV)
        message(STATUS ${arg})
    endforeach()
endfunction()

show_words(1 Two 3 Three 5)
```
- Očekivani izlaz za ovaj kod je:
```
1
Two
3
Three
5
```
- Funkcije ne mogu direktno da vraćaju povratne vrednost. Umesto toga, moramo da se igramo sa opsezima. Komanda `set` ima opciju `PARENT_SCOPRE` gde naglašavamo da se vrši izmena na promenljivoj koja se nalazi u roditeljskom opsegu funkcije (opseg programa u našem slučaju). Ako ne koristimo ovu opciju, onda će se promeniti vrednost promenljive lokalnog opsega i nakon završetka funkcije sve promenljive dobijaju svoje stare vrednosti. 

Želimo da implementiramo funkciju koja inkrementira vrednost neke promenljive. Da bismo to uradili, potrebno je da prosledimo ime promenljive (na taj način imamo i vrednost ako dereferenciramo promenljivu tj. njeno ime):
```
function(increment var)
    math(EXPR new_value "${${var}} + 1")
    set(${var} "${new_value}" PARENT_SCOPE)
endfunction()

set(value 10)
increment(value)
message("Result is ${value}!")
```
- Očekivani izlaz: `Result is 11!`.
- Potrebno je da razgraničimo neke stvari:
    * `var` ima vrednost `"var"` tj. ovo je niska.
    * `${var}` ima vrednost `"value"` tj. ime promenljive koju smo prosledili.
    * `${${var}}` ima vrednost `"10"` tj. vrednost promenljive koju smo prosledili.

## Reference i dodatni materijali

[How to CMake Good](https://www.youtube.com/watch?v=_yFPO1ofyF0&list=PLK6MXr8gasrGmIiSuVQXpfFuE1uPT615s&index=1&ab_channel=vector-of-bool)

[More Modern CMake - Deniz Bahadir](https://www.youtube.com/watch?v=y7ndUhdQuU8)

[Oh no! More Modern CMake - Deniz Bahadir](https://www.youtube.com/watch?v=y9kSr5enrSk&ab_channel=MeetingCpp)