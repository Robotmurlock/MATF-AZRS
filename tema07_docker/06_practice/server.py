# Pokretanje
# export FLASK_APP=server.py
# flask run

from flask import Flask, render_template, request
import os
import sys
from datetime import datetime
app = Flask(__name__)

prefix = os.environ.get('PREFIX')
if prefix is None:
    prefix = 'hey'
prefix = str(prefix)

@app.route('/hello', methods=['GET'])
def hello_world():
    text = request.args.get('text')
    now = str(datetime.now())
    address = request.remote_addr
    record = address + ', ' + now + ', ' + text + '\n'
    with open("/data/database.txt", "a") as myfile:
        myfile.write(record)

    return prefix + ':' + text

if __name__ == '__main__':
    app.run(host='0.0.0.0')
