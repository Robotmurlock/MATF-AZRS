# Uvod u git

## Instalacija (linux)

Za linux distribuciju je dovoljno pokrenuti sledeće komande za instalaciju osnovnih git operacija:\
`sudo apt install git-all` \
`sudo apt install git-extra`

## Pravljenje naloga

Github nalog možete napraviti na [zvaničnoj github stranici](https://github.com/).

## Dokumentacija

Kao i za linux komande i C funkcije, postoje `man` strane za git komande: `man git [KOMANDA]`

Primeri:
- `man git init`
- `man git commit`
- `man git branch`

## Kreiranje git repozitorijuma

Lokalni repozitorijum možemo napraviti koristeći komandu `git init` koja 
pravi prazan git repozitorijum tj. kreira `.git` direktorijum koji je neophodan za rad sa git operacijama. Informacije kao što je istorija komitova se
čuvaju u okviru ovog direktorijuma. Komanda `git clone` takođe kreira `.git` direktorijum.

Na Linux-u su sve datoteke oblika `.[IME]` 
sakriveni (ignorišu se) od `ls` komande. Ako se pokrene `ls` komanda, ne može se videti `.git` direktorijum. Potrebno je dodati opciju `-a` tj. pokrenuti komandu `ls -a`.

## Git indeks

Kada menjamo kod na računaru, zapravo ažuriramo `radni direktorijum (working directory)`. Te promene se ne ažuriraju u okviru git repozitorijuma dok se 
eksplicitno ne dodaju i onda komituju. \
\
Komandom `git add [IME DATOTEKE]` se datoteka dodaje na `staging area (oblast za postavljanje)` koji
otprilike predstavlja sledeći potencijalni komit tj. izmenu git repozitorijuma. Komandom `git commit` se zapisuju izmene zabeležene u okviru `staging area` na git repozitorijum (beleži se u `.git/objects`).\
![working-staging-repository](https://miro.medium.com/max/700/1*zw0bLFWkaAP2QPfhxkoDEA.png)\
Potrebno je da se nekako razlikuju promene datoteka u okviru tri sekcije:
- radni direktorijum,
- oblast za postavljanje,
- git repozitorijum.

Ove promene se beleže u `index`-u tj. `.git/index` datoteci.\

Koristeći kamandu `git status` možemo videti koje promene posle poslednjeg komita tj. promene u okviru radnog direktorijum koji se nalaze u `staging area` i
promene koje se ne nalaze u okviru `staging area` (nalaze se samo u okviru randog direktorijuma). 


Primer:
- U radnom direktorijumu postoje dve tekstualne datoteke (neka su napravljeni u okviru prethodnog komita):
    * `1.txt`
    * `2.txt`
    * Pomoć: `touch 1.txt 2.txt`
- Dodat je `Hello World` tekst na kraju obe datoteke.
- Izvršena je komanda `git add 2.txt`.
- Očekivani rezultat `git status` komande je:
<pre>
On branch master
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

        modified:   2.txt

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   1.txt
</pre>
- Što znači da se promene na `2.txt` nalaze u okviru `staging area`, jer se izvršena komanda `git add` i zbog toga će te promene biti zabeležene na git repozitorijum kad se pozove `git commit` komanda, dok će promene na `1.txt`
ostati samo u okviru radnog direktorijum.
- Komandom `git reset 2.txt HEAD` se sklanjaju promene sa `staging area` i
one neće biti zabeležene sledećim komitom.

Datoteka `.git/index` je binarna datoteka i na sledećem [linku](https://mincong.io/2018/04/28/git-index/) se može pročitati detaljnije o strukturi indeksa.

## Istorija projekta

Komandom `git log` se u terminalu ispisuje istorija komitova:
<pre>
commit 0388628561d9d2155980f26851b46727f77ba7a2
Author: Robotmurlock <momir.adzemovic@gmail.com>
Date:   Thu Oct 8 17:49:31 2020 +0200

    Azuriranje .gitignore za qt

commit 1d6219dca4e13221e58f10d3b2d1d93140f05133
Author: Robotmurlock <momir.adzemovic@gmail.com>
Date:   Thu Oct 8 17:18:47 2020 +0200

    Dodato upustvo za instalaciju i dodavanje cppreference u qtcreator

commit 544995c2b22c158497eec9315e0a8a43f81b871d
Author: Robotmurlock <32575918+Robotmurlock@users.noreply.github.com>
Date:   Thu Oct 8 14:37:28 2020 +0200

    Initial commit
</pre>

Svaki komit ima svoj `SHA-1 hash` koji jedinstven. Koriste se različiti metapodaci kao što su ime autora, vreme komita, ... za računanje heš koda. Heš kod je jedinstven.

Skraćena verzija `git log --pretty=oneline`:
<pre>
0388628561d9d2155980f26851b46727f77ba7a2 Azuriranje .gitignore za qt
1d6219dca4e13221e58f10d3b2d1d93140f05133 Dodato upustvo za instalaciju i dodavanje cppreference u qtcreator
544995c2b22c158497eec9315e0a8a43f81b871d Initial commit
</pre>

Ako se doda opcija `--graph` ispisuje se stablo što je korisno ako želimo da vizuelizujemo grane (branches): `git log --graph`, ali umesto toga može da
se koristi neki softver za vizuelizaciju.

Postoji ogroman broj opcija i različiti format koji: `man git log`.

## Definisanje aliasa

Možemo definisati aliase (skraćenice) za neke duže komande.

Primer:
- `git config --global alias.ci commit`

Ovo je korisno ako često koristimo neku komandu sa istim parametrima (dodatnim opcijama). 

Primer(istorija):
- `git config --global alias.hist "log --pretty=format:'%h %ad | %s%d [%an]' --graph --date=short"`

## Git vizuelizacija drveta verzija/komitova

Na [ovoj stranici](https://nic-hartley.github.io/git-gud/) se možete igrati sa git-om i vežbati iz vizuelizaciju.

## Git Verzije

Postoji opcija da se vratimo na određeni komit. To znači da se sve promene koje postoje između trenutnog komita i komita na koji se prelazi postaju invertovane.
- Prelazak na drugi komit: `git checkout [KOMIT HES]`;
- Komandom `git log --pretty=oneline` se prikazuju komitovi sa njihovim heš kodovima;
- Primer: `git checkout f8d50f6f60721edc7d3663a69cf0e5e55ea989a7`
- Prethodni primer predstavlja skok na "apsolutnu verziju". Alternativa je da se skače na "relativnu verziju" preko "pokazivača" na trenutni komit `HEAD`.
- Primer: `git checkout HEAD~` skače na prethodni komit.
- Primer: `git checkout HEAD~2` skače na pretprethodni komit. Možemo izabrati proizvoljan broj.
- Primer: `git checkout master` skače na najnoviji komit na `master` grani.

Takođe je moguće stavljati tagove verzija na bitne komitove. Na te komitove 
možemo skočiti na sledeći način: `git checkout [TAG]`

Primer:
- `git tag v1`, postavlja se tag `v1` na trenutni komit;
- `git checkout HEAD~`, skače se na prethodni komit;
- `git tag v1-prior`, postavlja se tag `v1-prior` ne trenutni komit;
- `git checkout v1`, skače se na komit sa `v1` tagom.

## Invertovanje poslednjeg komita

Šta ako smo izvršili komit i shvatili da to zapravo loše promene i da ih treba odbaciti. Sledećom komandom se pravi novi komit koji invertuje promene poslednjeg komita. Ako je komit koji se briše imao poruku `[PORUKA]`, onda će novi komit imati poruku `Revert "[PORUKA]"`.

Primer:
- `git add 1.txt`
- `git commit -m "Dodat 1.txt"`
- `git revert HEAD`

Ovaj niz komandi ne menja datoteke, ali u istoriji ostaje obrisan komit, posle
kojeg ide komit koji je taj prethodni komit obrisao. To znači da se git drvo ne ažurira. Ako je potrebno da se promeni i git drvo, onda koristimo komandu `git reset --hard [KOMIT]`

Primer:
- `git add 1.txt`
- `git commit -m "Dodat 1.txt"`
- `git reset --hard HEAD~`

Ovaj niz komandi ne menja datoteka, ali ne postoje tragovi promena u istoriji. Kao da se ništa nije desilo. **Napomena:** Ova komanda briše komit u istoriji i briše promene u radnom direktorijumu. **Veoma opasno** i mogu se obrisati bitne datoteke koje su dodate prethodnim komitom ili slično. Umesto opcije `--hard`
se može koristiti opcija `--soft` koja ne briše lokalne promena nad datotekama.

Obrisani komitovi se i dalje mogu videti dodavanjem opcije `--all`:\
`git log --all --pretty=oneline`

## Izmena poslednjeg komita

Recimo da smo ažurirali `README.md` datoteku i primetili smo da ima dve stamparske greške. Jedan način da se ovo reši je da se komituju ispravke kao novi komit. Alternativa je da se koristi `--amend`, gde se stari komit zamenjuje sa novim.

Primer:
- `code README.md` (izmeniti datoteku);
- `git add README.md`;
- `git commit -m "Azurirao README.md"`;
- Ako je `remote` repozitorijum: `git push`
- ovde je primećena greška!
- `code README.md` (ispraviti greške);
- `git add README.md`
- `git commit -m "Azurirao README.md"`;
- Ako je `remote` repozitorijum: `git push --force`.

**Napomena:** Opciju `--amend` koristiti samo za komitove koji nisu deljeni sa ostalim članovima tima.

## Brisanje i pomeranje datoteka

Slično kao komande `mv` i `rm` na linux sistemima, postoje analogne komande `git mv` i `git rm` koje dodaju promene na `staging area`, što znači da je potrebno komitovati promene.

Ako želimo da se datoteka obriše iz git repozitorijuma, ali da ostane u radnom direktorijumu, koristi se komanda `git rm --cached [IME DATOTEKE]`

Primer. Potrebno je pomeriti `main.cpp` datoteku u `src` direktorijum: 
- `git mv main.cpp src`

Primer. Potrebno je obrisati `1.txt` i `2.txt` datoteke:
- `git rm 1.txt 2.txt`

## Branching (grananje)

### Kreiranje grane

Nova grana se kreira komandom `git branch [IME GRANE]`. Da bi skočili na drugu granu, potrebno je da iskoristimo komandu `git checkout [IME GRANE]`.

Primer. Prvi način:
- `git branch feature`
- `git checkout feature`

Primer. Drugi način:
- `git checkout -b feature`

Uvek možemo da skočimo nazad na `master` granu:
- `git checkout master`

### Pregled aktivnih grana

Komandom `git branch -a` se ispisuju lokalne i remote grane. Trenutna grana ima `*` sa leve strane:
<pre>
  hello
* main_input
  master
</pre>

Komandom `git branch -r` se ispisuje remote grane. 

Komandom `git show-branch` se ispisuju grane i njihovi komitova:
<pre>
! [hello] Implemented hello class
 * [main_input] Implemented n input
  ! [master] Implemented n input
---
 *+ [main_input] Implemented n input
+   [hello] Implemented hello class
+   [hello^] Implemented hello class template
+*+ [main_input^] Initial commit
</pre>

### Kada praviti grane

- Treba praviti granu svaki put kada se dodaje neka nova `funkcionalnost (feature)`.
- Treba praviti novu granu svaki put kada se vrši neki `eksperiment`.
- Grananje ima znatno više smisla kada se radi u timu.
- `git workflow`.

### Spajanje grana

Potrebno je u nekom trenutku spojiti granu (ako se grana ne odbaci) sa glavnom granom (npr. master grana). To se vrši preko komande `git merge [IME GRANE]`.
Ova komanda se generalno koristi za spajanje trenutne grane sa izabranim komitovima tj. može se koristiti u opštijem slučaju.

Primer:
- Pravimo granu koja će implementirati klasu `Hello` i njene funkcionalnost: `git checkout -b helloClass`;
- Implementira se `hello.hpp` `hello.cpp` i opciono `Makefile` (ako ne postoji). Nije toliko bitno šta je poenta klase. Neka se objekat `Hello` pravi preko konstruktora koji prima jedan ceo broj `val`. Ovaj objekat ima jednu metodu `hey()` i pozivom ove metode se ispisuje `val` puta `"Hello World!"`.
- Ovo se može odraditi kroz jedan ili više komitova:
    * `git commit -m "Implementirana osnova struktura za hello klasu"`.
    * `git commit -m "Implementiran Makefile"`. Tip: Napisati `qmake` datoteku i generisati `Makefile` datoteku.
    * `git commit -m "Implementirane osnovne funkcionalnost hello klase"`.
- Sada je potrebno spojiti `helloClass` granu sa `master` granom. Ovo je veoma jednostavno ako ne postoje promene na master grani od kad je kreirana nova grana:
    * Potrebno je prvo skočiti na `master` granu: `git checkout master`.
    * Onda je potrebno spojiti grane: `git merge helloClass`.

### Brisanje grana

Grana se može obrisati komandom `git branch -d [IME GRANE]`.

## Konflitki

Posmatramo sledeću situaciju:
- Napravili smo `Hello` klasu u okviru `helloClass` grane i potrebno je spojiti ovu granu sa `master` granom.
- Razlika u odnosu na prethodni primer je to što je `master` takođe izmenjena. Zbog toga je spajanje otežano i potrebno je odlučiti koje promene želimo da prihvatimo.

Možemo da koristimo neki alat za rešavanje `konflitka spajanja (merge conflicts)` preko komande `git mergetool`. Postoji više izbora za ovakav alat. Jedan od takvih alata je `meld`.

Alternativa je da koristimo neki napredniji editor kao što je `visual studio code` koji ima integrisan alat za rešavanje konflikta.

Još jedna alternativa je da ručno vršimo rešavanje konflitka. 

### Instalacija i konfiguracija Meld alata

`sudo apt-get update -y`\
`sudo apt-get install -y meld`\
`git config --global merge.tool meld`\
`git config --global mergetool.prompt false`

### Primer konflitka

Sledeći niz komandi pravi konflikt spajanje:
- Pravljenje novog direktorijuma za git repozitorijum: 
    * `mkdir makeconflict`
    * `cd makeconflict`
- Pravljenje novog git repozitorijuma: 
    * `git init`
- Prvi komit:
    * `touch main.txt` 
    * `echo "m1" >> main.txt` 
    * `git add .`
    * `git commit -m "Prvi komit"`
- Pravljenje nove grane `newFeature` koja implementira funkcionalnost `f1`, `f2` i `f3`:
    * `git checkout -b newFeature`
    * `echo "f1" >> main.txt`
    * `git add main.txt`
    * `git commit -m "Dodata funkcionalnost f1"`
    * `echo "f2" >> main.txt`
    * `git add main.txt`
    * `git commit -m "Dodata funkcionalnost f2"`
    * `echo "f3" >> main.txt`
    * `git add main.txt`
    * `git commit -m "Dodata funkcionalnost f3"`
- Skok na granu `master` i dodavanje nove funkcionalnost `m2` (pretpostavimo da u realnoj situaciji dva različita člana tima vrše poslednja dva koraka tj. jedan radi na `master` grani, a drugi na `newFeature` grani):
    * `git checkout master`
    * `echo "m2" >> main.txt`
    * `git add main.txt`
    * `git commit -m "Dodata funkcionalnost m2"`
- Ovde je korisno za vizuelizaciju pokrenuti komandu `git hist --all`. Očekivani oblik izlaza:
<pre>
* 77032be 2020-10-17 | Dodata funkcionalnost m2 (HEAD -> master) [Robotmurlock]
| * d9b4d4e 2020-10-17 | Dodata funkcionalnost f3 (newFeature) [Robotmurlock]
| * 8e246fc 2020-10-17 | Dodata funkcionalnost f2 [Robotmurlock]
| * 6bf37c3 2020-10-17 | Dodata funkcionalnost f1 [Robotmurlock]
|/  
* 08a4d30 2020-10-17 | Prvi komit [Robotmurlock]
</pre>
- Desna grana je `master` grana, a leva je `newFeature` grana. Komitovi su poređani hronološki.
- Sada je potrebno da se `newFeature` grana spoji sa granom `master`, jer su u "međuvremenu" implementirane sve funkcionalnosti:
    * `git checkout master`
    * `git merge newFeature`
- Očekivani izlaz:
<pre>
Auto-merging main.txt
CONFLICT (content): Merge conflict in main.txt
Automatic merge failed; fix conflicts and then commit the result.
</pre>
- Potrebno je pokrenuti alat `meld` preko komande `git mergetool` koja će otvoriti program sa tri prozora: 
    * Promene na trenutnoj grani (levo),
    * Spojene promene (sredina),
    * Promene na grani "dolaznoj" grani (desno).
- Kombinovanjem promena na trenutnoj i dolaznoj grani dobijamo spojene promene.
- Nakon rešenih konflikta je potrebno izvršiti komit:
    * `git commit -m "Rešeni konflikti"`
- Očekivani rezultat `git hist --all` komande:
<pre>
*   d63a4cd 2020-10-17 | Reseni konflikti (HEAD -> master) [Robotmurlock]
|\  
| * d9b4d4e 2020-10-17 | Dodata funkcionalnost f3 (newFeature) [Robotmurlock]
| * 8e246fc 2020-10-17 | Dodata funkcionalnost f2 [Robotmurlock]
| * 6bf37c3 2020-10-17 | Dodata funkcionalnost f1 [Robotmurlock]
* | 77032be 2020-10-17 | Dodata funkcionalnost m2 [Robotmurlock]
|/  
* 08a4d30 2020-10-17 | Prvi komit [Robotmurlock]
</pre>
- Grane su spojene u jednu granu, što je u ovom slučaju `master` grana.

## Reference
`git strane`

[githowto](https://githowto.com/)

[medium-hackernoon-understanding-git-index](https://medium.com/hackernoon/understanding-git-index-4821a0765cf)

[thoughtram-the-anatomy-of-a-git-commit](https://blog.thoughtram.io/git/2014/11/18/the-anatomy-of-a-git-commit.html)