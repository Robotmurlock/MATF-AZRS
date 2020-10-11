# credit: https://doc.qt.io/qt-5/qmake-tutorial.html
# U okviru SOURCES definisemo izvorne fajlove
# SOURCES += hello.cpp
# SOURCES += main.cpp
# Alternativa:
# SOURCES = hello.cpp \
#           main.cpp

# ------------------------------------------
# U okviru HEADERS definisemo header fajlove
# HEADERS += hello.hpp

# ------------------------------------------
# U okviru TARGET definisemo ime izvrsnog fajla
# TARGET = helloworld

# ------------------------------------------
# Konfiguracija:
# CONFIG += debug
# Grananje na osnovu verzije sistema:
# win32 {
#     SOURCES += hellowin.cpp
# }
# unix {
#     SOURCES += hellounix.cpp
# }
# Neophodno za program!!!
# CONFIG += console

# ------------------------------------------
# Uslovnosti:
# !exists( hello.txt ) {
#     error( "No hello.txt file found" )
# }

# ------------------------------------------
# Konacno:
CONFIG += console debug
SOURCES += hello.cpp
SOURCES += main.cpp
HEADERS += hello.hpp
TARGET  = helloworld
!exists( hello.txt ) {
    error( "No hello.txt file found" )
}

# Prevodjenje u Makefile se vrsi preko qmake
# qmake -o Makefile hello.pro

# Dodatno:
# TEMPLATE: Da li je izlaz aplikacija, biblioteka ili plugin? To se definise u okviru TEMPLATE!
# TEMPLATE = app

# pogledati:
# https://doc.qt.io/qt-5/qmake-project-files.html

# Rezultat je Makefile (+ make)
# Ocekujemo nesto nalik na ovo:
#
# TARGET   = helloworld
# CXX      = clang++
# CXXFLAGS = -Wall -Wextra -std=c++17
# OBJECTS  = main.o \
#            hello.o
# 
# $(TARGET): $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^
# 	
# main.o: main.cpp hello.hpp
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<
# 	
# hello.o: hello.cpp hello.hpp
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<
