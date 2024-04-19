import requests
IP='http://192.168.137.17/'
# URL a la que deseas enviar la solicitud POST
url = IP+'led'

# Datos que quieres enviar en el cuerpo de la solicitud POST (en este caso, un diccionario)
data = {'red': 1, 'green': 2,'blue': 3}

# Realizar la solicitud POST
response = requests.post(url, data=data)

# Verificar el estado de la solicitud
if response.status_code == 200:
    print('Solicitud POST exitosa!')
    print('Respuesta del servidor:', response.text)
else:
    print('Error al realizar la solicitud POST. Código de estado:', response.status_code)
