Spectro Project v0.1 Alpha
=========
[![GitHub version](https://img.shields.io/badge/release-initial-brightgreen.svg)](https://github.com/arturgoms/Spectro-Project)<br>
O Projeto:
-------
__________
<br>
O projeto conciste em um conjunto de plataformas trabalhando juntas para atualizar o `Spectro Watch`(que é só um exemplo), cada parte se comunica de uma forma diferente para exemplificar a variedade de formas que podemos executar o projeto. Abaixo temos o esquema de como cada parte irá funcionar:

![project](http://i64.tinypic.com/245bhc6.png)<br>
<br> 
Como vemos na imagem temos o arduino lendo os sensores e enviando via serial para a raspberry, que por sua vez é o servidor do projeto todo, após receber as leituras do arduino ele envia para o aplicativo no android que por sua vez atualiza por bluetooth o relógio. Pense nas possibilidade :)

__________

<br>

Primeiro protótipo do Spectro Watch:
-------
<br>
In the future he will can do basically display `date` and `time`, set an `alarm`, ring a `buzzer` when the time comes, `temperature`, `barometer`, `altimeter`, `snooze`, `acelerometer`, `gyroscope` and also have `Bluetooth` and `ESP8266` to communication with phones and routers.<br>
For now we just have `date`, `time`, `temperature`, `barometer`, `altimeter`, `acelerometer` and `gyroscope` all working together with hc05. <br>

THIS PICTURES IS OUTDATED, FOLLOW ME ON TWITTER [`@arturgoms`](https://twitter.com/arturgoms)<br>
--------------------------------------------------------------------------------------------------------------

<br>
Front <br>
------------
![project](http://oi66.tinypic.com/1212vj9.jpg)<br>

Back <br>
------------
![project](http://i63.tinypic.com/1smutd.jpg)<br>
<br>
<br>
`PS: This is not a bomb`
<br>
<br>
Dependencies
------------

The code makes use of the ( for now)<br>
[`sumotoy`](https://github.com/sumotoy/TFT_ILI9163C) - LCD<br>
[`rodan`](https://github.com/rodan/ds3231) libraries. - RTC ( rename to DS3231 )<br>
[`adafruit`](https://github.com/adafruit/Adafruit-BMP085-Library) - BMP180, <br>libraries.<br>

Modules 
------------

Teensy 3.2 o/ <br>
TFT Display 1,44" ILI9361 <br>
DS3231 RTC (for now) <br>
BMP180<br>
HC-05 Bluetooth <br>
MPU6050 <br>
Micro SD Reader <br>
ESP8266 01 <br>
Recharge Module <br>
Lipo Battery <br>
5x Buttons<br>
5x 680 ohms Resistors <br>

<br>
Wait for the How to.
