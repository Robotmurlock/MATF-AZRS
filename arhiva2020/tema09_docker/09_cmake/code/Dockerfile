FROM ubuntu:20.04

RUN apt-get update
RUN apt-get -y install curl
RUN apt-get install -y software-properties-common
RUN apt-get update
RUN apt-get -y install cmake
RUN apt-get -y install gcc
RUN apt-get -y install g++
RUN apt-get -y upgrade

COPY . /usr/workdir

WORKDIR /usr/workdir

WORKDIR /usr/workdir/build

RUN cmake -G "Unix Makefiles" ..

RUN make

CMD cp -r . ../result