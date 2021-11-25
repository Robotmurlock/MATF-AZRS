# CMake

## Šta je CMake?

`CMake` je projekat [otvorenog koda](https://github.com/Kitware/CMake) koji se sastoji iz alata za izgradnju (build), testiranje i rad sa paketima. Omogućava da se proces kompilacije apstrahuje u odnosu
na platformu na kojoj se projekat prevodi. `CMake`-a je proizvod [kitware](https://www.kitware.com/)-a.

## Instalacija

**Linux:** `sudo apt install cmake`

**Mac:** `brew install cmake`

**Windows:** [Windows installer](https://cmake.org/download/)

## Uvod u CMake (01_hello)

- Želimo prvo da vidimo kako funkcioniše `cmake` na jednostavnom `hello world` programu. Nakon toga možemo da vidimo šta tu može da se poboljša.
- Pravimo direktorijum za novi projekat: `mkdir 01_hello`, `cd 01_hello`
- Pravimo `main.cpp` datoteku i okviru nje `hello world` program:
```c++
#include <iostream>

int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}
```
- Podrazumevano ime za `cmake` datoteku je `CMakeLists.txt` (slično kao `Makefile` za `GNU Make`):
    * `touch CMakeLists.txt` ili `vim CMakeLists.txt`
    * Ako koristimo `VSC`, možemo da instaliramo dodatak (plugin) za rad sa `CMake` i dodatak isticanje (highlighting) koda.
- Potrebno je da napišemo jednostavan `cmake`:
```cmake
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
    * `add_executable` definiše ime izvršne datoteke i ime potrebnih izvornih datoteka (zavisnosti).
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
    * `vim CMakeFiles/hello.dir/main.cpp.s`
- Naravno, komandom `make` (ili `make hello`) dobijamo izvršnu datoteku koju možemo da pokrenemo.

## Konfiguracije kompilatora (02_hello)

Naš `HelloWorld` program je modifikovan:

```c++
#include <iostream>
#include <numeric>

int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << std::gcd(9, 12) << std::endl;
    return 0;
}
```

Da bi se ovaj kod preveo, neophodan nam je `c++17` standard. Jednostavno je da modifikujemo naš `CMake` postavljanjem promenljive `CMAKE_CXX_STANDARD` na `17` tj. `set(CMAKE_CXX_STANDARD 17)`. `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(HelloWorld VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(hello main.cpp)
```

Slično, možemo da definišemo i druge opcije preko promenljive `CMAKE_CXX_FLAGS`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(HelloWorld VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

add_executable(hello main.cpp)
```

Time što smo naveli `${CMAKE_CXX_FLAGS}` na početku, zapravo dodajemo opcije na kraj niske (Sve promenljive u CMake su niske), umesto da samo dodamo njih.

## Release/Debug verzija (03_hello)

Kod `Makefile` smo mogli da podesimo posebne zastavice za `debug` verziju i `release` verziju našeg programa. Isto možemo da uradimo i sa `CMake`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(HelloWorld VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2")

add_executable(hello main.cpp)
```

**Build:**

- `mkdir [build]`
- `cd [build]`
- `cmake -DCMAKE_BUILD_TYPE=[build] -G "Unix Makefiles" ..` 
- `make`

## Biblioteka (04_library)

Želimo da napravimo biblioteku za rad sa niskama u `C++`-u. Standardna biblioteka nam već nudi `string` 
klasu sa funkacijama i metodama za rad sa niskama, ali postoje neke funkcije koje su nam bitne, ali se tu ne nalaze. Jedna veoma korisna f-ja, koja nije implementirana u okviru standardne biblioteke je `split` funkcija, koja prima dva argumenta: nisku i karakter razdvajanja `delimiter` i vraća niz niski razdvojenih
po tom specijalnom karakteru. Primer:

- `split("Ahoy there matey!", ' ') = ["Ahoy", "there", "matey"]`
- `split("123,456,789", ',') = ["123", "456", "789"]`

- Želimo da implementiramo ovu funkciju u našoj biblioteci i da je testiramo. Za testiranje pišemo odvojen kod `test.cpp`, a kompilaciju celog koda želimo da apstrahujemo preko `cmake`.
- Za testiranje biblioteke koristimo [Arange-Act-Assert](https://wiki.c2.com/?ArrangeActAssert) obrazac bez nekog naprednog `framework`-a za testiranje, već samo `assert` funkciju iz `assert.h` tj. `cassert` biblioteke.
- **Napomena:** Pogledati kod za datoteke `string_lib.cpp` `string_lib.hpp` i `test.cpp` u `02_library`
direktorijumu.
- Potrebno je da se napravi izvršna datoteka na osnovu prethodno navedenog izvornog koda:
    * `vim CMakeLists.txt`
- Već znamo da napišemo osnovne elemente `cmake` datoteke:
```cmake
cmake_minimum_required(VERSION 3.16)
project(SplitLibrary VERSION 1.0.0)

add_executable(run_test test.cpp)
```
- U odnosu na prethodni primer, potrebne su nam dve stvari: 
  - Dodavanje biblioteka 
  - Linkovanje biblioteka sa objektnim kodom.
- Za dodavanje biblioteka za prevođenje se koristi `add_library`:
```cmake
add_library(
    string_library
    string_lib.hpp
    string_lib.cpp
)
```
- **Objašnjenje:** Prvo se navodi ime biblioteke, pa onda redom potrebne datoteke:
```cmake
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
```cmake
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
```cmake
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

## Projekat (05_project)

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
```cmake
cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

add_subdirectory(string_lib)

add_executable(myprogram src/main.cpp)
add_executable(run_test string_lib/test.cpp)

target_link_libraries(myprogram PRIVATE string_lib)
```
- Nova komanda je `add_subdirectory`. Ovu komandu koristimo kada želimo da dodamo neki poddirektorijum, što u ovom slučaju želimo da uradimo za `lib` direktorijum. Dobijamo sličnu funkcionalnost kao da smo kopirali kod iz `CMakeLists.txt` iz poddirektorijuma i ažurirali relativne putanje. Datoteka `CMakeLists.txt` u `lib` direktorijumu:
```cmake
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

## Projekat sa testovima (06_project_with_tests)

U prethodnom smo konfigurisali `CMake` tako da nam `build` podrazumeva i izvršnu datoteku za testiranje. Ukoliko bismo imali više biblioteka i za svaku biblioteku jednu ili više izvršnih datoteka, onda želimo nekako da automatizujemo testiranje. To možemo da uradimo preko `add_test` funkcionalnosti, gde definišemo šta nam sve čini skup testova. Kada izvršimo build, onda možemo da pokrenemo sve testove sa `make test`, gde dobijamo informacije koji su sve testovi prošli tj. nisu prošli. Da bismo koristili ovu funkcionalnost, neophodno je da definišemo `enable_testing()` na početku `CMakeLists.txt` (posle `project`). Modifikujemo `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

enable_testing()

add_subdirectory(string_lib)

add_executable(myprogram src/main.cpp)
add_executable(run_test string_lib/test.cpp)

add_test(
    NAME run_test
    COMMAND run_test
)

target_link_libraries(myprogram PRIVATE string_lib)
target_link_libraries(run_test PRIVATE string_lib)
```

Proces za `build`-ovanje je isti:

- `mkdir build`
- `cd build`
- `cmake -G "Unix Makefiles" ..`
- `make test`. Očekivani rezultat:

```
Test project ...
	Start 1: run_test
1/1 Test #1: run_test .........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```

## Analiza kvaliteta testova (07_project_gcov)

`Pokrivenost koda (Code Coverage)` je metrika za koja određuje apsolutni ili relativni broj linija, grana ili putanja koje su uspešno proverene našim procesom testiranja. 

- Broj pokrivenih linija predstavlja broj linija koje su izvršene u nekom od testova. Ova metrika se u suštini uvek i proverava, pored ostalih metrika za pokrivenost koda. Jasno je da ako nam je pokrivenost koda 100% kada posmatramo linije, da to ne znači da je kod potpuno testiran. Primer:

```c++
int f(int x)
{
	// pretpostavka: x == 100
	int y = x/2 + 10; // y == 60
	if(x > y) // true
		y = y + 5; // y == 65
	return y;
}

void test_f()
{
	assert(f(100) == 65);
}
```

- Prethodni kod izvršava svaku liniju u kodu, ali ne uzima u obzir ponašanje funkcije `f` kada se ne ispuni uslov u `if` naredbi. Zbog toga često gledamo i pokrivenost grana u kodu, jer ta metrika uzima u obzir koje grane u kodu su izvršene.
- Pokrivenost koda putanja je zahtevno za izračunavanje, jer to podrazumeva proveru pokrivenosti svih mogućih puteva u programu. Ako imamo program koji ima samo 10 puta `if`, onda je to već `2^10` putanja koje moraju da se provere. Petlje su još problematičnije, jer zahteva provere (grananje) u svakoj iteraciji.
- Pomoću alata za analizu pokrivenosti koda, možemo lako da uočimo da li smo preskočili da testiramo neki deo koda ili da li smo slabo testirali neki deo koda. Idealno je da pokrivenost linijama u testovima bude skoro `100%` . 
- Detaljnija priča o ovoj temi izlazi iz opsega kursa. Ovde želimo da demonstriramo još mogućnosti `CMake` alata.

Za dalji rad nam je neophodna nam je [Kolekcija CMake modula](https://github.com/bilke/cmake-modules). Neophodno je preuzimanje i čuvanje u projektu u poddirektorijumu. Možda neki od ovih modula može da bude koristan i za projekte? Za ovaj primer je nama samo neophodan `CodeCoverage.cmake`. Da bismo koristili ove module, dovoljno je da nakon `project` funkcije u `CMakeLists.txt` dodamo sledeću komandu:

- `list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)`

Da bismo generisali izveštaj za pokrivenost koda, neophodno je da prevodimo izvršnje datoteke sa opcijom `--coverage`:

- `set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra --coverage")`

Poslednja stavka se odnosi na generisanje samih izveštaja koju navodimo nakon definisanjih izvršnih datoteka:

```
if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    SETUP_TARGET_FOR_COVERAGE_LCOV(NAME coverage EXECUTABLE run_test)
endif()
```

Sada možemo da generišemo `build`:

- `mkdir build`
- `cd build`
- `cmake -G "Unix Makefiles" ..`
- `make coverage`
- `google-chrome coverage/index.html`. Očekivani rezultat.

![](https://raw.githubusercontent.com/Robotmurlock/MATF-AZRS/main/tema05_cmake/images/01-lcov.png)

![](https://raw.githubusercontent.com/Robotmurlock/MATF-AZRS/main/tema05_cmake/images/02-lcov.png)

## Reference i dodatni materijali

[\[1\] How to CMake Good](https://www.youtube.com/watch?v=_yFPO1ofyF0&list=PLK6MXr8gasrGmIiSuVQXpfFuE1uPT615s&index=1&ab_channel=vector-of-bool)

[\[2\] More Modern CMake - Deniz Bahadir](https://www.youtube.com/watch?v=y7ndUhdQuU8)

[\[3\] Oh no! More Modern CMake - Deniz Bahadir](https://www.youtube.com/watch?v=y9kSr5enrSk&ab_channel=MeetingCpp)