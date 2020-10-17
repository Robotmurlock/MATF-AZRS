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

## Reference
`git strane`

[githowto](https://githowto.com/)

[medium-hackernoon-understanding-git-index](https://medium.com/hackernoon/understanding-git-index-4821a0765cf)

[thoughtram-the-anatomy-of-a-git-commit](https://blog.thoughtram.io/git/2014/11/18/the-anatomy-of-a-git-commit.html)