FROM mysql:latest

COPY . /usr/src/database

WORKDIR /usr/src/database

CMD mysql -uroot -pRoot_12345 -h127.0.0.1 -P6603 < input.sql