# Pokretanje
# export FLASK_APP=app.py
# flask run

from flask import Flask, render_template
import os
app = Flask(__name__)

color = os.environ.get('BACKGROUND_COLOR')

@app.route('/')
def hello_world():
    return render_template('index.html', color=color)

if __name__ == '__main__':
    app.run(host='0.0.0.0')