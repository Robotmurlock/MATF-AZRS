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

## Clang-Tidy

Alat `Clang-tidy` je deo `Clang/LLVM` projekta koji dam automatski refaktoriše `C++` kod. Ova grupa alata se nazivaju `linteri (linter)`. Linteri su alati koji proveravaju kod i pronalaze stilske i programske greške.

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


## Reference

[clang-llvm](https://clang.llvm.org/)

[kdab-clang-tidy](https://www.kdab.com/clang-tidy-part-1-modernize-source-code-using-c11c14/)