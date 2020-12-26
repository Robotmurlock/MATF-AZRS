# Zadatak 1

U direktorijumu se nalazi projekat sledećeg oblika:
```
main.cpp
headers/
    lib1.hpp
    lib2.hpp
sources/
    lib1.cpp
    lib2.cpp
```
Analizirati projekat i napraviti:
1. Datoteku `main.pro` koja generiše `Makefile` preko `qmake`;
2. Datoteku `CMakeLists.txt` koja generiše `Makefile` preko `cmake`
2. Datoteku `Makefile` koja generiše izvršnu datoteku za produkciju komandom `make release` i izvršnu datoteku za razvoj i debagovanje komandom `make debug`.

