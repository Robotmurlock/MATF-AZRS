create database if not exists practice;
use practice;

create table if not exists customer(
    name varchar(255),
    surname varchar(255)
);

insert into 
    customer (name, surname)
values 
    ('Jeff', 'Mynameis'),
    ('Robot', 'Murlock'),
    ('Hell', 'boy');