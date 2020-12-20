docker pull mysql/mysql-server:latest

docker run --name=mysql-server-db -d mysql/mysql-server:latest

apt-get install mysql-client

docker exec -it mysql-server-db mysql -u root -p \
| echo "ALTER USER 'root'@'localhost' IDENTIFIED BY 'Root_12345';"

mkdir -p /root/docker/mysql-server-db/conf.d
echo '[mysqld]' >> /root/docker/mysql-server-db/conf.d/my-custom.cnf
echo 'max_connections=250' >> /root/docker/mysql-server-db/conf.d/my-custom.cnf