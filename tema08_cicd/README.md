# Kontinualna integracija i kontinualna isporuka

**Kontinualna integracija (continuous integration)**  predstavlja praksu gde se teži ka čestom spajanju verzija koda (u kontekstu verzionisanja koda), a da pritom produkcioni kod ostane kvalitetan i pouzdan. Ovde definišemo precizno razliku između `produkcionog koda` i `isporučenog koda`, gde je isporučeni kod produkcioni kojem "klijenti" imaju pristup. Ovaj proces uglavnom automatizujemo, gde pouzdan kod dobijemo korišćenjem automatskog testiranja, a kvalitetan kod korišćenjem `linter` ili sličnih alata. Naravno, nismo ograničeni na korišćenje samo ovih grupa alata. Za testiranje se pokreću jedinični testovi, a ako svi jedinični testovi prođu, onda se koriste i integracioni testovi. Poželjno je da se integracija verzija koda vrši što češće. Tipičan niz zadataka:

- Detekcija promena u izvornom kodu u repozitorijumu na produkcionoj grani.
- Analiza kvaliteta koda.
- Izgradnja projekta (ako je to neophodno).
- Pokretanje jediničnih testova.
- Pokretanje integractionih testova.
- Generisanje izveštaja.

Ako je neki od ovih zadataka neuspešan, onda se proces zaustavlja i šalje se obaveštenje o neuspešnosti procesa.

**Kontinualna isporuka (continuous delivery)** je proširenje kontinualne integracije, koja stavlja akcenat na izgradnju i testiranje koda, kao i na isporuku koda na okruženje za testiranje i/ili za produkciju (npr. to okruženje može da bude neki server, virtuelna mašina ili kontejner). Ukoliko nije neophodno da ručno potvrdimo da se isporučen kod koristi na produkciji (kod koji koriste "klijenti"), onda se taj proces naziva **potpuno automatizovana kontinualna isporuka (continuous deployment)**.

![](https://github.com/Robotmurlock/MATF-AZRS/blob/main/tema08_cicd/images/01_manual_vs_automatic.png)

## Github Akcije

**Github akcije** nam omogućavaju automatizaciju softverskih `procesa rada (workflow)` (ne nužno samo CI/CD procesa rada). Ti procesi rada mogu da podrazumevaju <i>build</i>, testiranje, isporučivanje, ... Github nam omogućava virtuelne mašine (Linux, Windows, MacOS) za izvršavanje ovih procesa rada koji su besplatni ako se koriste u malim količinama na mesečnom nivou. 

### Komponente

Možemo da konfigurišemo da se pokrene `proces rada github akcije` kada se desi neki događaj. Taj događaj može da bude komit na master grani, otvoren `issue`, ili nešto treće. Proces rada se sastoji iz niza `job`-ova (poslova) koji mogu da se izvršavaju sekvencijalno ili paralelno. Svaki posao se izvršava u sopstvenoj virtuelnoj mašini ili u kontejneru, gde posao podrazumeva pokretanje neke skripte ili korišćenje neke već postojeće akcije. 

![](https://github.com/Robotmurlock/MATF-AZRS/blob/main/tema08_cicd/images/02_ga_components.png)

### Proces rada

Proces rada je konfigurabilan automatizovani proces koji pokreće jedan ili više poslova. Konfiguracija se vrši preko `yaml` datoteka i sastoji se iz:

- Događaja po kojima se okida proces rada:
  - Primeri: `pull request`, `issue`, `commit`, periodično okidanje, ...
  - Moguće je da se proces rada pokrene i manuelno
- Niz koraka koji se izvršavaju:
  - Svaki korak je ili `shell` skripta koja može da bude samo i jedna komanda ili akcija
  - Akcije su nešto nalik na funkcije u programskim jezicima, gde je ideja da se kod za iste operacije ne piše više puta
- Pokretači (server na kojem se izvršava proces rada)
  - Windows, Linux, MacOS

Za više informacije, pogledati [zvaničnu dokumentaciju](https://docs.github.com/en/actions/learn-github-actions/understanding-github-actions).

## Primer jednostavne akcije (01_Simple)

Svaki konfigurisan proces rada se čuva odvojeno u direktorijumu `.github/workflows`. U ovom primeru demonstriramo:

- Kako se piše konfiguracija za `github` akciju.
- Upoznavanje sa interfejsom.
- Kako izgleda uspešan proces rada.
- Kako izgleda neuspešan proces rada.

Prvo je neophodno da napravimo `public` repozitorijum za testiranje. Neka se u ovom slučaju zove `Test-Github-Actions`. Kada kloniramo novi repozitorijum, neophodno je da napravimo prvu `github` akciju:

- `mkdir -p .github/workflows`
- `cd .github/workflows`
- `vim test.yaml`

Neka nam se akcija zove `test`. To definišemo na sledeći način:

```yaml
name: test
```

Sledeći korak je da definišemo događaj koji je uslov za pokretanje procesa. U ovom slučaju želimo da pokrećemo proces na `push` na `main` grani. To znači da ako imamo `development` i `main` granu, onda se ovaj proces pokreće samo na `push` na `main` granim ali ne i `development` grani:

```yaml
on:
    push:
        branches: [ main ]
```

Poslednji korak je da definišemo poslove. Imamo samo jedan posao koji nazivamo `test` i koji hoćemo da pokrenemo na `ubuntu-latest` okruženju. Sve što želimo da se izvršu u ovom procesu je ispis `Hello World!`:

```yaml
jobs:
    test:
        runs-on: ubuntu-latest
        steps:
            - name: echo
              run: echo "Hello World!"
```

Konačno:

```yaml
name: test

on:
    push:
        branches: [ main ]

jobs:
    test:
        runs-on: ubuntu-latest
        steps:
            - name: echo
              run: echo "Hello World!"
```

Treba da gurnemo izmene na `remote` repozitorijum:

- Pozicioniranje u koren lokalnog repozitorijuma: `cd ../..`
- Dodavanje akcije na repozitorijum `git add .github`
- Komitovanje izmena `git commit -m "Initial commit"`
- `git push`

Sada možemo da otvorimo u pretraživaču naš `GitHub` repozitorijum i kliknemo na `Actions`. Tu očekujemo da se akcija uspešno završila

![](https://github.com/Robotmurlock/MATF-AZRS/blob/main/tema08_cicd/images/03_ga_test.png)

Klikom na `Initial commit` možemo da vidimo koji poslovi su se izvršili. Uvom slučaju je to samo `test`. Klikom na `test` dobijamo sledeći

## Primer akcije nad Qt aplikacijom (02_DataViewer)

Imamo program `01_DataViewer` za prikazivanje različitih tipova tabelarnih podataka. Trenutno su podržava `csv (comma-separated values)` i `tsv (tab-separated values)`. Primer `csv` datoteke:

```
"a","b","c"
"Hello","World","3"
":)",":)",":("
```

Odgovarajuća tabela:

```
+-----+-----+--+
|a    |b    |c |
+-----+-----+--+
|Hello|World|3 |
+-----+-----+--+
|:)   |:)   |:(|
+-----+-----+--+
```

Primer `tsv` datoteke za istu tabelu:

```
a    b    c
1    2    3
4    7    9
```

Čitanje i pisanje `csv` i `tsv` datoteka je implementirano kroz `Parser` biblioteku uz koji je implementiran i skup testova `ParserTest`. Deo aplikacije koji se odnosi na `GUI` je implementiran kao `DataViewer`. Pregled aplikacije:

![](https://github.com/Robotmurlock/MATF-AZRS/blob/main/tema08_cicd/images/04_dataviewer.png)

Cilj je da implementiramo `CI/CD` cevovod za `DataViewer` aplikaciju sa sledećim koracima:

1. Instalacija neophodnih biblioteka za `build` (qmake);
2. Izgradnja aplikacija i biblioteka pomoću `qmake` alata;
3. Pokretanje testova za biblioteke;
4. Zapakivanje aplikacije;
5. Postavljanje aplikacije na adresu gde je moguće tu aplikaciju preuzeti.

U ovom slučaju imamo `potpuno automatizovanu kontinualnu isporuku`. 

Preduslovi za okidanje:

- `push` na `main` grani.
- `pull_request` na `main` grani.

**Rešenje:**

```yaml
name: DataParser: build-test

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]
    
jobs:
    build-and-test:
        runs-on: ubuntu-latest

        steps:
            - uses: actions/checkout@v2 # Preuzimanje svih datoteka sa repozitorijuma (akcija)
            - name: Install Qt # Instalacija qmake alata 
                uses: jurplel/install-qt-action@v2
            - name: create-build-dir # Kreiranje direktorijuma za build
                run: mkdir build
            - name: build-qmake # Generisanje Makefile-a na osnovu qmake datoteke
                working-directory: ./build
                run: qmake -o Makefile ..
            - name: build-make # Generisanje izvrsnih datoteka
                working-directory: ./build
                run: make
            - name: run-test # Pokretanje testova
                working-directory: ./build
                run: ./ParserTest/ParserTest
            - name: zip-app # Zipovanje aplikacije
              run: zip -r dataviewer.zip build/DataViewer/DataViewer
            - name: deploy-app # Isporucivanje aplikacije - vrednosti ostaju nepopunjene
              uses: appleboy/scp-action@master
              with:
                  host: *
                  username: *
                  password: *
                  port: 22
                  source: *
                  target: *
```

**Napomena:** Za svaku akciju postoji odgovarajući `Github` repozitorijum, gde može da se pronađe implementacija i dokumentacija. 

## Primer akcije nad Python aplikacijom (03_FlaskCalculator)

Osnova za ovaj primer je [ovaj](https://github.com/alanbanks229/flask_calculator_app) `github` projekat.

Imamo `flask` server sa jednostavnim kalkulatorom. 

![](https://github.com/Robotmurlock/MATF-AZRS/blob/main/tema08_cicd/images/05_flask_calculator.png)

Struktura projekta:

```yaml
[ROOT]:
    - app.py # server na portu 5000 koji renderuje `index.html` stranicu i omogucava pristup stranici
    - templates: # skup stranica servera
        - index.html
    - static: # staticke datoteke
    	- calculator.css # css za stranicu
    - calculator: # modul za izvrsavanje jednostavnih operacija
    	- calculator.py # Implementacija
    	- test_calculator.py # Jedinicni testovi
    - utility: # Skup korisnih skripti
    	- ping_test.py # Jednostavna skripta za testiranje servera
    - requirements.txt # Skup neophodnih python biblioteka
    - Dockerfile
```

Želimo da napravimo proces preko `github` akcije koji se okida na `issue` grani:

1. Preuzimanje izvornog koda sa repozitorijuma (checkout).
2. Pokretanje jediničnih testova (unittest).
3. Pokretanje `flask` servera.
4. Pokretanje `ping` testa (smoke test).
5. Izgradnja `docker`.
6. Ažuriranje slike na `Docker Hub`.

**Rešenje:**

Za uslove okidanja postavljamo labelirane `issues`:

```yaml
on:
    issues:
        types:
            - labeled
```

Koristimo jedan `job` koji se pokreće na `ubuntu-latest` okruženju:

```yaml
jobs:
    build:
        runs-on: ubuntu-latest
        steps:
        	...
```

Sada možemo da izvršavamo sve neophodne korake u specifikaciji zadatka. Prvo je neophodno da se preuzme izvorni kod. Za to možemo da koristimo `actions/checkout@v2`. Nakon preuzimanja koda imamo `requirements.txt` i možemo odmah da instaliramo sve neophodne biblioteke za `python` preko `pip`-a:

```yaml
- uses: actions/checkout@v2
- name: install-pythob-libs
run: pip install -r requirements.txt
```

Ako je ovaj korak prošao uspešno, onda imamo instalirane `flask` i `unittest` pakete. Modul `unittest` nam je neophodan za sledeći korak tj. pokretanje jediničnih testova. Od `python` skripti za pokretanje jediničnih testova imamo samo `calculator/test_calculator.py`. U opštem slučaju imamo mnogo veći broj ovakvih skripti i želimo da pokrenemo sve njih uz opciono generisanje izveštaja za pokrivenost koda testovima. Tada možemo skupimo sve testove na osnovu njihovog naziva (npr. `*/test_*`).

```yaml
- name: run-unit-tests
run: python calculator/test_calculator.py
```

Sada želimo da pokrenemo `flask` server kako bismo na njega primenili `smoke test`. Ideja je da proverimo najjednostavnije funkcionalnosti aplikacije (da li se aplikacija pokreće?). Za to koristimo `utility/ping_test.py`:

```python
import requests

response = requests.get(url='http://localhost:5000/ping')
assert response.json()['success'], 'Ping test failed!'
print('Ping test passed!')
```

Ovde je neophodno da nam se izvršavaju dva procesa odjednom tj `flask` i `ping_test`. Možemo da pokrenemo `flask` server u pozadini tako što dodamo `&` na kraj komande za pokretanje. Stavljamo `sleep 3` kako bismo sačekali da se `flask` server pokrene i onda pokrećemo `ping_test`:

```yaml
- name: run-flask-server
run: python app.py &
- name: run-flask-server-wait
run: sleep 3
- name: ping-test
run: python utility/ping_test.py
```

Sada preostaje još samo da se napravi slika i da se postavi na `Docker Hub`. Poslednji korak tj. postavljanje na `Docker Hub` se ostavlja za domaći, a ovde se "fiktivno" rešava:

```yaml
- name: docker-build
run: docker build . --file Dockerfile --tag flask-calculator:latest
- name: docker-hub-push
run: echo 'push to Docker Hub'
```

Konačno:

```yaml
name: Flask-Pipeline

on:
    issues:
        types:
            - labeled

jobs:
    build:
        runs-on: ubuntu-latest
        steps:
            #1 Preuzimaje izvodnog koda sa repozitorijuma
            - uses: actions/checkout@v2
            - name: install-pythob-libs
              run: pip install -r requirements.txt
            #2 Pokretanje jedinicnih testova
            - name: run-unit-tests
              run: python calculator/test_calculator.py
            #3 Pokretanje flask servera
            - name: run-flask-server
              run: python app.py &
            - name: run-flask-server-wait
              run: sleep 3
            #4 Ping test
            - name: ping-test
              run: python utility/ping_test.py
            #5 Docker build
            - name: docker-build
              run: docker build . --file Dockerfile --tag flask-calculator:latest
            #6 Postavljanje na Docker Hub
            - name: docker-hub-push
              run: echo 'push to Docker Hub'
```

## Reference

[\[1\] Medium-What-Is-CICD](https://medium.com/devops-dudes/what-is-ci-cd-continuous-integration-continuous-delivery-in-2020-988765f5d116)

[\[2\] Atlassian-Continuous-Integration-vs-Delivery-vs-Deployment](https://www.atlassian.com/continuous-delivery/principles/continuous-integration-vs-delivery-vs-deployment)

[\[3\] Github-Actions](https://github.com/features/actions)

[\[4\] Flask-Calculator-App](https://github.com/alanbanks229/flask_calculator_app)

