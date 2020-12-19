FROM gcc:latest

COPY . /usr/src/hello-world

WORKDIR /usr/src/hello-world

RUN g++ -o hello-world main.cpp

CMD ["./hello-world"]