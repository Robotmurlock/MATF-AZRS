import requests
import numpy as np

texts = np.array([
    'Hello',
    'Matey',
    'Banana',
    'Baneyney',
    'Orange',
    'Lemon',
    'Pancake',
    'Donut'
])

if __name__ == '__main__':
    URL = 'http://localhost:12345/hello'
    PARAMS = {'text': np.random.choice(texts)}

    response = requests.get(url=URL, params=PARAMS)
    data = response.text
    print(data)
