# Kontinualna integracija i kontinualna isporuka

**Kontinualna integracija (continuous integration)**  predstavlja praksu gde se teži ka čestoj spajanju verzija koda (u kontekstu verzionisanja koda), a da pritom produkcioni kod ostane kvalitetan i pouzdan. Ovde definišemo precizno razliku između `produkcionog koda` i `isporučenog koda`, gde je isporučeni kod produkcioni kod kojem "klijenti" imaju pristup. Ovaj proces uglavnom automatizujemo, gde pouzdan kod dobijemo korišćenjem automatskog testiranja, a kvalitetan kod korišćenjem `linter` ili sličnih alata. Naravno, nismo ograničeni na korišćenje samo ovih grupa alata. Za testiranje se pokreću jedinični testovi, a ako svi jedinični testovi prođu, onda se koriste i integracioni testovi. Poželjno je da se integracija verzija koda vrši što češće. Tipičan niz zadataka:

- Detekcija promena u izvornom koda u repozitorijumu na produkcionoj grani.
- Analiza kvaliteta koda.
- Izgradnja projekta (ako je to neophodno).
- Pokretanje jediničnih testova.
- Pokretanje integractionih testova.
- Generisanje izveštaja.

Ako je neki od ovih zadataka neuspešan, onda se proces zaustavlja i šalje se obaveštenje o neuspešnosti procesa.

**Kontinualna isporuka (continuous delivery)** je proširenje kontinualne integracije, koja stavlja akcenat na izgradnju i testiranje koda, i stavlja akcenat na isporuku koda na okruženje testiranje za/i produkciju (npr. to okruženje može da bude neki server). Ukoliko nije neophodno da ručno potvrdimo da se isporučen kod koristi na produkciji (koriste "klijenti"), onda se taj proces naziva **potpuno automatizovana kontinualna isporuka (continuous deployment)**.

![](/home/robotmurlock/Desktop/AZRS/MATF-AZRS/tema08_cicd/images/01_manual_vs_automatic.png)

## 01_FileParser

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
a	b	c
1	2	3
4	7	9
```

Čitanje i pisanje `csv` i `tsv` datoteka je implementirano kroz `Parser` biblioteku uz koji je implementiran i skup testova `ParserTest`. Deo aplikacije koji se odnosi na `GUI` je implementiran kao `DataViewer`. Pregled aplikacije:

![](/home/robotmurlock/Desktop/AZRS/MATF-AZRS/tema08_cicd/images/02_dataviewer.png)

Cilj je da implementiramo `CI/CD` cevovod za `DataViewer` aplikaciju sa sledećim koracima:

1. Instalacija neophodnih biblioteka za `build` (qmake);
2. Izgradnja aplikacija i biblioteka pomoću `qmake` alata;
3. Pokretanje testova za biblioteke;
4. Zapakivanje aplikacije;
5. Postavljanje aplikacije na adresu gde je moguće tu aplikaciju preuzeti.

U ovom slučaju imamo `potpuno automatizovanu kontinualnu isporuku`.

## 02_some_python_application

## Reference

[\[1\] Medium-What-Is-CICD](https://medium.com/devops-dudes/what-is-ci-cd-continuous-integration-continuous-delivery-in-2020-988765f5d116)

[\[2\] Atlassian-Continuous-Integration-vs-Delivery-vs-Deployment](https://www.atlassian.com/continuous-delivery/principles/continuous-integration-vs-delivery-vs-deployment)

