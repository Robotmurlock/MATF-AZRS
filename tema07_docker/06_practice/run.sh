docker run --name echo-server-hey -e PREFIX="hey" -p 12345:5000 -v $PWD/data:/data echo-server
