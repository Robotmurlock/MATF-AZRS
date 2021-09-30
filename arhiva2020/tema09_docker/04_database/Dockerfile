FROM gcc:latest

COPY . /usr/src/database

WORKDIR /usr/src/database

RUN g++ -o database main.cpp

CMD ["./database"]