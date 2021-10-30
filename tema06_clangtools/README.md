# Clang Tools

`Clang` sa popratnim alatima je jedan od najbitnijih delova `LLVM` projekta otvorenog koda.

## Clang

`Clang` je kompilator za jezike `C`, `C++`, `Objective C` ... Tačnije, `clang` je `frontend` koji kao ulaz uzima kod napisan u prethodno navedem jezicima i prevodi ga u `međureprezenaticiju` tj `llvm IR` i to predstavlja ulaz za središnji deo na kojem se vrše optimizacije nezavisne od jezika i arhitekture. Na kraju `backend` vrši optimizacije vezane za konkretnu arhitekturu i prevodi kod na mašinski jezik.

U odnosu na `gcc`, implementiran je u `C++`-u korišćenjem modernijih tehnologija. Bolje predstavlja informacije u slučaju greške ili upozorenja, a uglavnom daje više upozorenja u odnosu na `gcc`.

Setimo se da kada smo pisalie `Makefile` da smo imali kod oblika:
```
CXX = g++
...
```
Možemo da zamenimo `g++` sa `clang++`. To i jeste ideja `CXX` promenljive, da može lako da se promeni kompilator.

![clang1](images/clang1.png)

### Instalacija

`sudo apt install clang`

### Upotreba

Upotrebljava se skoro identično kao i `gcc`: 
    * `clang [OPTIONS] input.c` za `C` datoteke
    * `clang++ [OPTIONS] input.cpp` za `C++` datoteke

## ClangTidy

Alat `ClangTidy` je deo `Clang/LLVM` projekta koji dam automatski refaktoriše `C++` kod. Ova grupa alata se nazivaju `linteri (linter)`. Linteri su alati koji proveravaju kod i pronalaze stilske i programske greške.

Dokumentacija: `man clang-tidy`

### Motivacija

Standard `C++11` je dodao mnoge nove funkcionalnosti kao što su (od direktno vidljivih) `auto`, `override`, `lambda` ... I dalje postoje kodovi koji se nisu adaptirali za ovaj standard. Takođe, dosta programera i dalje ne koristi nove funkcionalnost (uglavnom zbog lenjosti). Ideja `clang-tidy` je da donekle olakša rešavanje ovog problema tj. refaktorisanje koda tako da koristi novije funkcionalnosti.`

### Instalacija

`sudo apt install clang-tidy`

### Uvod (01_override)

Imamo sledeći primer (`old.cpp`):
```
struct Base {
    virtual void reimplementMe(int a) {}
};
struct Derived : public Base  {
    void reimplementMe(int a) {}
};

int main()
{
    Base* object = new Derived;
    return 0;
}
```

Možemo da primenimo `clang-tidy` i da vidimo potencijalna mesta za refaktorisanje. Ako želimo da alat primeni direktno popravke na kod možemo da napravimo `new.cpp` i da dodamo opciju `--fix`. Postoji lista provera koje možemo da uključimo preko opcije `--checks=[PATTERN1],[PATTERN2],...,[PATTERNK]`. Ako želimo da uključimo sve opcije, onda koristimo `--checks=*`. Želimo da modernizujemo kod pa koristimo `--checks=modernize-*`. Izlaz preusmeravamo u `log.txt`:
    * `cp old.cpp new.cpp`
    * `clang-tidy new.cpp --checks=modernize-* --fix -- --std=c++17 > log.txt`
- Očekivani izlaz:
```
4 warnings generated.
clang-tidy applied 3 of 3 suggested fixes.
```
- **Napomena:** Ovo je izlaz za greške, jer standardni izlaz preusmeravamo u `log.txt`.
- Vidimo da je uvideo neke probleme i čak ispravio neke.
- Sada želimo da pogledamo `log.txt` i prodiskutujemo (neki delovi su izbačeni zbog čitljivosti, ali razlika bi trebalo da bude očigledna):
```
new.cpp:5:10: warning: annotate this function with 'override' or (rarely) 'final' [modernize-use-override]
    void reimplementMe(int a) {}
         ^
                              override
```
- Ovde kaže da treba naglasiti koji se metodi predefinišu preko ključne reči `override`. Ako pogledamo `new.cpp`, videćemo da je to dodao. 
- Čemu služi `override`? Ako pokrenemo stari kod, trebalo bi da isto radi. Ključna reč `override` ima dve glavne uloge: 
    * Da kaže čitaocu da se metod predefiniše iz roditelje klase.
    * Da kaže kompilatoru da se metoda predefiniše kako bi mogao da vrši neke provere kojim mogu da se izbegnu potencijalne greške.
```
new.cpp:5:30: note: FIX-IT applied suggested code changes
    void reimplementMe(int a) {}
                             ^
```
- Prethodna sugestija je premenjena zbog `--fix` opcije.
- Strelica nam govori gde je dodata ključna reč
```
new.cpp:8:5: warning: use a trailing return type for this function [modernize-use-trailing-return-type]
int main()
~~~ ^
auto       -> int
```
- Ovo je moderniji način za pisanje povratnih tipova.
```
new.cpp:8:1: note: FIX-IT applied suggested code changes
int main()
^
new.cpp:8:11: note: FIX-IT applied suggested code changes
int main()
          ^
```
- Primenjena je prethodna sugestija.
```
new.cpp:10:11: warning: Value stored to 'object' during its initialization is never read [clang-analyzer-deadcode.DeadStores]
    Base* object = new Derived;
          ^
new.cpp:10:11: note: Value stored to 'object' during its initialization is never read
```
- Ovde imamo nešto veoma interesatno. `clang-analyzer` je primetio da imamo promenljivu koja se ne koristi. Pojam `dead code (mrtav kod)` se odnosi na kod koji se nikad ne koristi. U ovom primeru se promenljiva definiše (dodeljuje se vrednost) i ne koristi se.
```
new.cpp:11:5: warning: Potential leak of memory pointed to by 'object' [clang-analyzer-cplusplus.NewDeleteLeaks]
    return 0;
    ^
new.cpp:10:20: note: Memory is allocated
    Base* object = new Derived;
                   ^
new.cpp:11:5: note: Potential leak of memory pointed to by 'object'
    return 0;
    ^
```
- Takođe je primećeno potencijalno curenje memorije.
- Datoteka `noerror.cpp` ima modifikovanu `main()` f-ju:
```
auto main() -> int
{
    Base* object = new Derived;
    object->reimplementMe(1);
    delete object;
    return 0;
}
```
- Ako pokrenemo sada `clang-tidy` bez `--fix` opcija, onda bi trebalo da dobijemo prazan izlaz (nema sugestija).
- **Napomena:** Ne ispravlja svaka provera sugestije (`modernize-*` provere isrpavljaju sugestije).

Ako želimo da vidimo šta sve podrazumeva `modernize-*`, možemo da pokrenemo sledeću komandu:
* `clang-tidy --list-checks -checks='*' | grep "modernize"`
* `clang-tidy --list-checks -checks='*'` nam dohvata sve provere.
* `grep "modernize"` filtrira provere koji nisu `modernize`

### Cmake (02_cmake)

- Šta ako imamo ceo projekat koji želimo da refaktorišemo? Ako koristimo `cmake`, onda je to lako. 
- Imamo biblioteku `sorty` koja ima jednu apstraktnu klasu `AbstractSort` čiji konstruktor prima funkciju poređenja i čisto virtuelni metod `sort()` koji sortira dobijeni niz. Takođe postoje i dve nasleđenje klase `SelectionSort` i `QuickSort` koje implementiraju odgovarajuće algoritme. 
- Glavna funkcija testira ove klase.
- Želimo da izvršimo `clang-tidy` nad celim projektom.
- Potrebno je da izgradimo naš projekat:
    * `mkdir build`
    * `cd build`
    * `cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..`
- Pokrenimo program radi testiranja:
    * `make`
    * `./run`
- Očekivani izlaz:
```
1 2 3 4 5 
5 4 3 2 1 
```
- Komanda `run-clang-tidy` pokreće `clang-tidy` na svim datotekama:
    * `run-clang-tidy -checks='modernize-*' -fix`
    * **Pažnja:** Opcija `-fix` menja kod. Možda želite backup.
- Neke interesatne promene:
- `BEFORE:`
```
void vprint(const std::vector<int>& vec)
{
    for(std::vector<int>::const_iterator it=vec.cbegin(); it!=vec.cend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}
```
- `AFTER:`
```
void vprint(const std::vector<int>& vec)
{
    for(int it : vec)
        std::cout << it << " ";
    std::cout << std::endl;
}
```

### Modernize-nullptr (03_modernize)

Sledećih par kratkih primera se odnose na refaktorisanje koda pisanog po starijem standardu. Koja je razlika između `NULL` i `nullptr`?
- `#define NULL 0` (`NULL` je samo makro).
- Ovo može da napravi probleme ako zaboravimo da je ovo samo broj.
- Sa druge strane, `nullptr` je uvek pokazivač.

- Pogledajmo sledeći kod:
```
#include <stdio.h>

#define MY_NULL (void*)0

void assignment() {
  char *a = NULL;
  char *b = 0;
  char c = 0;
}

int *ret_ptr() {
  return 0;
}

void test() {
  void *p = MY_NULL;
}

int main()
{
    return 0;
}
```
- Kada kažemo `return 0` za pokazivač, to je kao da smo rekli `return NULL`. Čitljivije je da se stavi `NULL`.
- Primenjujemo `clang-tidy`:
    * `clang-tidy new.cpp --checks=modernize-use-nullptr --fix -- --std=c++17`
- Očekivani rezultat:
```
#define MY_NULL (void*)0

void assignment() {
  char *a = nullptr;
  char *b = nullptr;
  char c = 0;
}

int *ret_ptr() {
  return nullptr;
}

void test() {
  void *p = MY_NULL;
}
```
- Primetimo da ispravljeno i `return 0` i `return NULL` u `return nullptr`, ali samo tamo gde se očekuje da rezultat pokazivač.
- Po dokumentaciji bi trebalo da je zamenio i `MY_NULL` u `nullptr`, tako da to treba da uzimamo sa rezervom.

### Modernize-auto (04_modernize)

Ovde imamo sličan slučaj kao u jednom od prethodnih primera:
```
int main()
{
    std::vector<int> my_container;
    std::vector<int>::iterator I = my_container.begin();
    int val = 42;

    return 0;
}
```
- Po dokumentaciji, tip treba zameniti kada to povećava čitljivost. Ako zamenimo `int` sa `auto`, to ne povećava čitljivost. Ali ako zamenimo `std::vector<int>::iterator` sa `auto`, onda to povećava čitljivost:
- Pokrenimo `ClangTidy`:
    * `clang-tidy new.cpp --checks=modernize-use-auto --fix -- --std=c++17`
```
int main()
{
    std::vector<int> my_container;
    auto I = my_container.begin();
    int val = 42;

    return 0;
}
```

### Modernize-using (05_modernize)

Ključne reči `typedef` i `using` je manje-više isto u većini primera. Razlika je u tome što je `using` kompatabilan sa `template` programiranjem:
```
typedef int variable;

class Class{};
typedef void (Class::* MyPtrType)() const;

typedef struct { int a; } R_t, *R_p;
```
- Pokrenimo `ClangTidy`:
    * `clang-tidy new.cpp --checks=modernize-use-using --fix -- --std=c++17`
- Očekivani izlaz:
```
using variable = int;

class Class{};
using MyPtrType = void (Class::*)() const;

using R_t = struct { int a; };
using R_p = R_t *;
```
**Napomena:** Primer iz dokumentacije ne radi!

### Readibility-identifier-naming (06_readibility)

**TODO!**
[dokumentacija](https://clang.llvm.org/extra/clang-tidy/checks/readability-identifier-naming.html)
- Otvoriti `.clang-tidy` datoteku.

### Readability-container-size-empty (07_readibility)

**TODO!**
[dokumentacija](https://clang.llvm.org/extra/clang-tidy/checks/readability-container-size-empty.html)

### Performance-implicit-conversion-in-loop (08_performance)

**TODO!**
[dokumentacija](https://clang.llvm.org/extra/clang-tidy/checks/performance-implicit-conversion-in-loop.html)

### Performance-inefficient-string-concatenation (09_performance)

**TODO!**
[dokumentacija](https://clang.llvm.org/extra/clang-tidy/checks/performance-inefficient-string-concatenation.html)

### llvm-namespace-comment (10_llvm)

**TODO!**
[dokumentacija](https://clang.llvm.org/extra/clang-tidy/checks/llvm-namespace-comment.html)

## ClangFormat

Alat `ClangFormat` može da formatira kod za nas. On nam nudi više različitih stilova formatiranja. 
- Želimo sada da testiramo te stilove. Stilove biramo opcijom `--style=[STYLE]`. 
- Možemo da vidimo listu stilova preko `man strana`: 
    * `man clang-format`
```
LLVM, Google, Chromium, Mozilla, WebKit, Microsoft, GNU.
```
- Možemo da napravimo naš format ako želimo i on može da bude zasnovan na nekom već postojećem stilu. Taj format definišemo u okviru datoteke `.clang-format`, gde je svaka linija oblika `KEY: VALUE`:
```
BasedOnStyle: LLVM
IndentWidth: 8
UseTab: Always
BreakBeforeBraces: Linux
AllowShortIfStatementsOnASingleLine: false
IndentCaseLabels: false
```
- Ako pokrenemo komandu `clang-format main.cpp` dobićemo kao izlaz formatiranu datoteku. Ako dodamo opciju `-i` formatiranje se vrši `u mestu (inplace)`. 
- Ovde nemamo nešto nalik na `run-clang-tidy`, ali možemo da napišemo našu `bash` ili `python` skriptu koja rekurzivno prolazi kroz projekat i formatira datoteke.
- Odlučio sam da napravim `run-clang-format.py` skriptu. Svi stilovi se generišu preko `elnino.sh` skripte.
- Možete da izabere format koji vam se sviđa.

## Godbolt i clang alati

Već smo se upoznali sa [godbolt](https://godbolt.org/) na nekom od prethodnih časova. `Godbolt` ima padajući meni `Add tool` i tu postoje opcije `clang-tidy` i `clang-format`. Ovo je odličan alat za testiranje `clang` alata i `c++` kodova generalno. 

## Qt i analiza koda

Razvojno okruženje `qtcreator` ima opciju `Analyze` kao padajući meni i tu postoje opcije za `Clang-Tidy and Clazy...` analizu koda:
* `sudo apt install clazy`

## Reference

[clang-llvm](https://clang.llvm.org/)

[kdab-clang-tidy](https://www.kdab.com/clang-tidy-part-1-modernize-source-code-using-c11c14/)

[clang-format](https://clang.llvm.org/docs/ClangFormat.html)

[clang-tidy-modernize-use-nullptr](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-nullptr.html)

[clang-tidy-modernize-use-auto](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-auto.html)

[clang-tidy-modernize-use-override](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-override.html)

[clang-tidy-modernize-use-using](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-using.html)