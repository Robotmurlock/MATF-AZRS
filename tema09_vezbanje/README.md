# Vežbanje

Dodatna tema za pomoć pri spremanju za pismeni ispit.

## Format ispita

Ispit se radi pismeno na računaru 3 sata i nosi 70 poena. Postoje 8 zadataka na ispitu označeni od `zad1` do `zad8`, gde su neparni zadaci sa vežbi, a parni zadaci sa predavanja. Zadaci `zad1` i `zad2` su obimniji zadaci koji nose po 15 poena. U tim zadacima je dat program koji ne radi ispravno po nekoj specifikaciji i cilj je popraviti taj program debagovanjem. Pored debagovanja je neophodno i da se reše manji zadaci u okviru tog zadatka, gde se od studenta traži da primene neki alat (clang-tidy, callgrind, ...) ili reše neki problem (data je bash skripta, a traži se Makefile, ...). Ostali zadaci nose po 5 poena i čine pitanja ili kraće zadatke. Preporuka je da se prvo rešavaju zadaci od po 5 poena.

## Primeri pitanja

Ovo se odnosi na zadatke od po 5 poena. Očekuju se odgovori u par linija.

1. Koja je razlika između DVCS i CVCS?

2. Šta su konflikti (git)?

3. Šta je indeks (git)? 

4. Koja je razlika između komandi `git revert` i `git reset --hard`?

5. Šta je `Gitflow Workflow`? Skicirati model i označiti tipove komitova na slici (bez objašnjenja).

6. ```
         A---B---C feature
        /
   D---E---F---G master
   ```

   Vizualizovati sledeće:

   - `git checkout master`, `git merge feature``
   - ``git checkout feature`, `git rebase master`
   - `git checkout master`,`git cherry-pick A C`

7. Objasniti razliku i vezu između `git pull` i `git fetch`.

8. Šta je `godbolt`?

9. Šta je `gdb`

10. Objasniti sledeće `gdb` komande:

    - `display`
    - `continue`
    - `break`

11. Navesti primer upotrebe za `watchpoint` i primer upotrebe za `breakpoint`.

12. Šta je `qmake/cmake/Makefile`? Šta je izlaz ovog alata?

13. Šta je `Valgrind`, a šta `Callgrind`.

14. Navesti jedan primer gde za velike ulaze (milijardu) algoritam sa većom vremenskom složenošću brže radi od algoritma sa manjom vremenskom složenošću. 

15. Ako dva algoritma imaju istu vremensku složenost, kako da znamo koji da iskoristimo. Navesti barem jedan alat koji može da se iskoristi u ovoj situaciji. 

16. Kako možemo u `C++`-u da automatski odredimo da li neka jedinica nije testirana?

17. Šta je `clang`? 

18. Da li je moguće automatski (barem delimično) refaktorisati `C++` kod u standardu `03` u `C++` kod u standardu `11`. Ako može, onda kako?

19. Koja je razlika između kontejnera i virtuelnih mašina?

20. Šta je `docker-compose`?

21. Koje su prednosti korišćenja kontinualne integracije?

Pogledati `01_zad` i `02_zad`. Ovi zadaci mogu da budu kao pitanja od po 5 poena ili deo zadataka od 15 poena.

## Zadaci

Ovo se odnosi na zadatke od po 15 poena. Očekuje se da se na osnovu specifikacije popravi program (sa dokumentovanim ispravkama) i odgovori na dodatna pitanja. Pogledati zadatake `tema02_gdb/05_parser`, `tema02_gdb/06_voronoi`, `tema02_gdb/07_aggregator`, `tema08_cicd/01_DataViewer` (ovaj primer je "ispravan", ali zadaci mogu da budu tog tipa). Za ovu grupu zadataka je najbitnije da se obnovi sintaksa za `C/C++`!