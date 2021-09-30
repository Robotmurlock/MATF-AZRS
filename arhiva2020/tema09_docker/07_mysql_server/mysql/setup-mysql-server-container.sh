docker pull mysql/mysql-server:latest

docker run --name=simple-mysql-server-db -d mysql/mysql-server:latest

apt-get install mysql-client

docker exec -it simple-mysql-server-db mysql -u root -p \
| echo "ALTER USER 'root'@'localhost' IDENTIFIED BY 'Root_12345';"

mkdir -p /root/docker/simple-mysql-server-db/conf.d
echo '[mysqld]' >> /root/docker/simple-mysql-server-db/conf.d/my-custom.cnf
echo 'max_connections=250' >> /root/docker/simple-mysql-server-db/conf.d/my-custom.cnf