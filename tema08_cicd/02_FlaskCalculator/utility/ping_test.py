import requests

response = requests.get(url='http://localhost:5000/ping')
assert response.json()['success'], 'Ping test failed!'
print('Ping test passed!')
