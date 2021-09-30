FROM ubuntu:16.04

RUN apt-get update -y && \
    apt-get install -y python-pip python-dev

COPY . /usr/src/flaskserver

WORKDIR /usr/src/flaskserver

RUN pip install -r requirements.txt

CMD ["python", "app.py"]