# Pokretanje
# export FLASK_APP=app.py
# flask run

from flask import Flask, request
import os
import random
from datetime import datetime as dt
app = Flask(__name__)

import mysql.connector

class Database:
    def __init__(self):
      self.db = mysql.connector.connect(
                  host='127.0.0.1',
                  user='root',
                  password='Root_12345',
                  port='10001',
                  auth_plugin='mysql_native_password'
                )
      self.cursor = self.db.cursor()
      
      self.cursor.execute('create database if not exists random')
      self.cursor.execute('use random')
      self.cursor.execute("""
        create table if not exists logs(
          id int auto_increment primary key,
          type varchar(255),
          result varchar(1000),
          client_ip varchar(255),
          time varchar(255)
        )
      """)

    def save(self, addr, result, request_type):
      now = str(dt.now())
      self.cursor.execute(f"""
        insert into 
          logs (type, result, client_ip, time)
        values
          ('{request_type}', '{result}', '{addr}', '{now}')
      """)
      self.db.commit()

    def load(self):
      self.cursor.execute('select * from logs')
      return str(self.cursor.fetchall())

          
database = Database()           

@app.route('/', methods=['GET'])
def resp_basic():
    result = random.random()
    database.save(request.remote_addr, str(result), 'basic')
    return {'result': result}

@app.route('/range', methods=['GET'])
def resp_range():
    start = int(request.args.get('start'))
    end = int(request.args.get('end'))
    result = random.randint(start, end)
    database.save(request.remote_addr, str(result), 'range')
    return {'result': result}

@app.route('/sequence', methods=['GET'])
def resp_sequence():
    size = int(request.args.get('size'))
    result = [random.random() for i in range(size)]
    database.save(request.remote_addr, str(result), 'sequence')
    return {'result': result}

@app.route('/logs', methods=['GET'])
def resp_logs():
    return {'result': database.load()}

if __name__ == '__main__':
    app.run(host='0.0.0.0')
