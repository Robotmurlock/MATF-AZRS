# Zadatak 2

Dobili ste celu aplikaciju koja se zove `HelloComputerWorld`. Aplikacija predstavlja onlajn
prodavnicu i sastoji se iz sledećih komponenti:
1. `store-server` web server (za klijente);
2. `postgresql-db` baza podataka;
3. `redis-struct` skladište (ubrzava operacije čitanja keširanjem);
4. `analytics-server` web server za analitiku (za zaposlene).

**Osnovne informacije o aplikaciji:**
- `store-server` omogućava klijentima da pretražuju prodavnicu na `http://hellocomputerworld.com:80`;
- `store-server` koristi `postgresql-db` bazu podataka za čuvanje podataka o proizvodima, klijentima i transakcijama (priključuje se pri pokretanju).
- Bazi podataka se pristupa na portu `7001` preko `host` mašine, a `postregsql-db` se pokreće na podrazumevanom portu `5432`;
- `store-server` koristi `redis-struct` na portu `7002` za bolje performanse (priključuje se pri pokretanju). 
- Strukturi `redis-struct` se pristupa na portu `7002`, a `redis-struct` se pokreće na podrazumevanom portu `6379`;
- `analytics-server` omogućava zaposlenima da pretražuju prodavnicu na `https://analytics.hellocomputerworld.com.com:443`.
- `analytics-server` koristi `postgresql-db` bazu podataka.

**Informacije za doker slike:**
- Za `store-server` postoji `Dockerfile` unutar direktorijuma `store`;
- Za `postgresql-db` postoji slika `postgresql`;
- Za `redis-struct` postoji slika `redis`;
- Za `analytics-server` postoji `Dockerfile` unutar direktorijuma `analytics`.

**Zahtev:**
- Napisati `docker-compose.yml` datoteku koja pokreće sva četiri kontejnera i omogućava odgovarajuću komunikaciju.

**Dodatni zahtevi:**
- Potrebno je da se nađe rešenje za slučaj da se server pokrene pre baze podataka ili keša.

**Napomena:**
- Ne mora da se prevodi.