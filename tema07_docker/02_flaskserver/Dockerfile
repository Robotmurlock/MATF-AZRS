FROM ubuntu:20.04

RUN apt-get update -y && \
    apt-get install -y python3-pip python3-dev

COPY . /usr/src/flaskserver

WORKDIR /usr/src/flaskserver

RUN pip install -r requirements.txt

CMD ["python3", "app.py"]
