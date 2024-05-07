# Esp32 Cardan
Code pour les capteurs des cardans.

![SystemDiagram](SystemDiagram.drawio.png)
### Client
Le code du client est celui qui vas dans les ESP32 sur les cardans. Il permet de lire l'entré analogue de l'amplificateur et de l'envoyer au server. Pour différencier les ESP32, il faut changer le ``data.flags = (numero du esp que l'on souhaite)``.
### Server
Le code du server est pour le ESP32 sur le Baja. Il reçoit les données des capteurs sur les cardans.
### Setup
Chaque ESP32 a une adresse MAC unique, pour la déterminer il suffit d'upload le code de setup. Ceci est important pour savoir lequel des ESP32 est le server.

1. D4:8A:FC:CE:D4:C4
2. FC:B4:67:F5:EC:28
3. E8:6B:EA:CF:0A:00
### LED
On définit 3 LED de couleur variables (RGB) qui ont pour fonction de nous indiquer différents états du système. <br/>
<br/>
sdLED: indique l'état du lecteur de carte SD <br/>
--> vert: Lecture terminée, aucun problème rencontré <br/>
--> jaune: Enregistrement en cours <br/>
--> rouge: Problème rencontré, enregistrement interrompu ou non commencé <br/>
<br/>
commLED: indique l'état de la communication entres les cardans <br/>
-->vert: tout fonctionne <br/>
-->jaune: fonctionnement partiel des communications <br/>
-->rouge: communication complètement planté <br/>
<br/>
GPSLED: indique l'état du GPS <br/>

### Libraries
Changer les adresses MAC du server:
```
constexpr uint8_t server_address[] = {0xFC, 0xB4, 0x67, 0xF5, 0x68, 0x20};
```
Ensuite pour pouvoir compiler le code du client et du server, il faut copier coller la librarie dans le folder des libraries Arduino ou mettre ``DataStructure.h`` dans le folder du sketch.

## Futur
- [ ] Mettre un syteme d'erreur mieux.<br/>
- [ ] Enlever les serials prints.<br/>
- [ ] Analyser les données.<br/>
- [ x ] Logger sur la carte SD avec le server.<br/>
- [ x ] Tester avec 4 ESP32.<br/>
- [ x ] Tester si les ESP32 en avant peuvent bien transmettre les donnes.<br/>

### Resources
Vidéo utilisé pour faire le code et comprendre comment ESP-NOW fonctionne: <br/>
 - [ESP-NOW - Peer to Peer ESP32 Network](https://www.youtube.com/watch?v=bEKjCDDUPaU&ab_channel=DroneBotWorkshop)
