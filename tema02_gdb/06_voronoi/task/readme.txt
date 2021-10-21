Neka je data bela slika i na njoj N tacaka gde svaka ima neku svoju boju. Voronoi dijagram se dobija
tako sto se svakom pikselu na slici dodeli boja najblize tacke. 

Tim neiskusnih C++ programera je odlucio da napravi 
program koji od slike koja je predstavljena kao matrica karaktera napravi voronoi dijagram. Posto nisu sigurni koji
voronoi dijagram je najlepsi, odlucili su da program generise nekoliko verzija generisanih pseudo nasumicnim brojevima.

Proces:
a. Program se pokrece sa argumentima `count` (zeljeni broj voronoi dijagrama).
b. Generise se `count` specifikacija (svaka specifikacija ima svoje seme i identifikator).
c. Za svaku specifikaciju se desava sledece:
  1. Na osnovu semena se generise dimenzija voronoi dijagrama (pravougaonik AxB) i N `oznacenih` tacaka.
  2. Formira se prazan voronoi dijagram i popunjava se oznakama najblizih tacaka
 
Primer: Dijagram je dimenzije 5x6 sa 3 `oznacene` tacke: a(0, 0), b(2, 4), c(4, 4)

Pre popunjavanja:
a*****
******
****b*
******
****c*

Nakon popunjavanja (centri su oznaceni velikim slovima u ovom primeru zbog preglednosti):
Aaaabb
aaabbb
aabbBb
aabbbb
acccCc

Napomena:
Ako se za <count> parametara unese "test", pokrecu se testovi umesto pravog programa
Nakon sto se napravid build direktorijum, neophodno je da se `testovi/test{i}.txt` prebace
u taj direktorijum. Ova funkcionalnost moze biti korisna za testiranje.

Zahtevi i pitanja: 
- Napraviti git repozitorijum.
- Popraviti sve bagove u programu.
- Za svaku ispravku treba da postoji odgovarajuci git komit.
- Da li nacin testiranja moze da se unapredi?

odgovor: ...
