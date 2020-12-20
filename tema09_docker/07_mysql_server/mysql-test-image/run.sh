docker build -t mysql-test-image .
docker run --network=host mysql-test-image