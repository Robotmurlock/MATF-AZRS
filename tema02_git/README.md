# Uvod u git

## Instalacija (linux)

Za linux distribuciju je dovoljno pokrenuti sledeće komande za instalaciju osnovnih git operacija:\
`sudo apt install git-all` \
`sudo apt install git-extra`

## Pravljenje naloga

Github nalog možete napraviti na [zvaničnoj github stranici](https://github.com/).

## Dokumentacija

Kao i za linux komande i C funkcije, postoje `man` strane za git komande: `man git [KOMANDA]`\
Primeri:\
`man git init`\
`man git commit`\
`man git branch`

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

## Reference
[medium-hackernoon-understanding-git-index](https://medium.com/hackernoon/understanding-git-index-4821a0765cf)