create database dbcustomers;
use dbcustomers;

create table customer(
    name varchar(255),
    surname varchar(255)
);

insert into 
    customer (name, surname)
values 
    ('Jeff', 'Mynameis'),
    ('Robot', 'Murlock'),
    ('Hell', 'boy');
