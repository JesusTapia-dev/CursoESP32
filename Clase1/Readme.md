## Introduccion: 
El módulo posee las siguientes características:
- Memoria: 448 KByte ROM, 520 KByte SRAM 16 KByte SRAM in RTC QSPI Flash/SRAM, 4 MBytes.
- Pines: 30.
- Pines Digitales GPIO: 24  (algunos pines solo como entrada)
- Pines PWM: 16.
- Pines Analógicos ADC: 18 (3.3V, 12bit: 4095, tipo SAR, ganancia programable).
- Conversor Digital a Analógico DAC: 2 (8bit).


La disposición de pines se muestra en la siguiente imagen:
<img src="https://cdn.shopify.com/s/files/1/0609/6011/2892/files/doc-esp32-pinout-reference-wroom-devkit.png" alt="JuveR" width="700px">
## Station Mode (STA) y Access Point Mode.


Modo Access Point(AP). Nos permite que el módulo "cree" su propia red Wi Fi.

Modo Station (STA). Este modo nos permitirá configurar el WLAN en ESP32 como host para que otros clientes se conecten a él. Esto es muy útil para entornos donde no dispones de router y necesitas conectarte al ESP32, o simplemente si quieres prescindir de él y crear una red propia.