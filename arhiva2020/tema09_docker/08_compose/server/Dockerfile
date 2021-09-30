FROM python:latest

COPY . /usr/src/flaskserver

WORKDIR /usr/src/flaskserver

RUN pip install -r requirements.txt

RUN pip install mysql-connector-python

CMD ["python", "app.py"]