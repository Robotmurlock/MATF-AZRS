FROM gcc:latest

COPY . /usr/src/hello

WORKDIR /usr/src/hello

RUN g++ -o hello main.cpp

ENTRYPOINT ["./hello"]

CMD ["5"]