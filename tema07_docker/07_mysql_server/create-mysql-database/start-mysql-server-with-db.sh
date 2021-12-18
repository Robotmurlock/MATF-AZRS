docker run \
--detach \
--name=mysql-server-customers-db \
--env="MYSQL_ROOT_PASSWORD=Root_12345" \
--publish 6603:3306 \
--volume=/root/docker/simple-mysql-server-db/conf.d:/etc/mysql/conf.d \
mysql

sleep 10

mysql -uroot -pRoot_12345 -h127.0.0.1 -P6603 < init-database.sql
