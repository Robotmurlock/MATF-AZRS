docker run \
--detach \
--name=simple-mysql-server-db \
--env="MYSQL_ROOT_PASSWORD=Root_12345" \
--publish 6603:3306 \
--volume=/root/docker/simple-mysql-server-db/conf.d:/etc/mysql/conf.d \
mysql