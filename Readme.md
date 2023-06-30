# Curso ESP32 
## Programación de ESP32 en Arduino IDE

Primero procedemos a clickear en preferencias y pegamos el siguiente texto en la opción "Additional boards manager URLs":https://dl.espressif.com/dl/package_esp32_index.json, https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Con eso hecho seleccionamos el board "ESP32 Dev Module" y empezamos a programar!

**Nota**. En caso no reconozca el módulo debemos instalar el driver que corresponda usando la siguiente página: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers.

A la hora de subir el programa se debe aplastar el boton de booteo.

La disposición de pines se muestra en la siguiente imagen:
<img src="https://cdn.shopify.com/s/files/1/0609/6011/2892/files/doc-esp32-pinout-reference-wroom-devkit.png" alt="JuveR" width="700px">


## Clase 1: Blink

Para el parpadeo de LED usaremos

## Clase 2: Station Mode (STA) y Access Point Mode.

Modo Station (STA). Este modo nos permitirá configurar el WLAN en ESP32 como host para que otros clientes se conecten a él. Esto es muy útil para entornos donde no dispones de router y necesitas conectarte al ESP32, o simplemente si quieres prescindir de él y crear una red propia.

