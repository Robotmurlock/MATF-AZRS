# Qt Instalacija

## Linux
`sudo apt-get install build-essential`\
`sudo apt-get install qtcreator`\
`sudo apt-get install qt5-default`
    
### Linux docs i API:
``sudo apt install `apt-cache search 5-examples | grep qt | grep example | awk '{print $1 }' | xargs` ``\
``sudo apt install `apt-cache search 5-doc | grep "Qt 5 " | awk '{print $1}' | xargs` ``\
`sudo apt-get install build-essential qtcreator qt5-default`
  
### Ako nešto nedostaje: 
``sudo apt install `apt-cache search qt | grep 5- | grep ^qt | awk '{print $1}' | xargs` ``

### izvor: 
`https://doc.qt.io/qt-5/linux.html`\
`https://stackoverflow.com/questions/48147356/install-qt-on-ubuntu`
    
  --- 
## Mac:
`https://doc.qt.io/qt-5/macos.html`
    
  ---
## Windows: 
`https://doc.qt.io/qt-5/windows.html`
