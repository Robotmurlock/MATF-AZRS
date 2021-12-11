import requests
from pprint import pprint

BASE_URL = 'http://localhost:5000/'

def test_request(url, ps={}):
    response = requests.get(url=url, params=ps)
    data = response.json()
    pprint(data)

def test1():
    test_request(BASE_URL)

def test2():
    ps = {'start': 1, 'end': 10}
    url = BASE_URL + 'range'
    test_request(url, ps=ps)

def test3():
    ps = {'size': 10}
    url = BASE_URL + 'sequence'
    test_request(url, ps=ps)

def test4():
    url = BASE_URL + 'logs'
    test_request(url)
    

if __name__ == '__main__':
    test1()
    test2()
    test3()
    test4()
