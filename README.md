# Esp32_Cardan
Code pour les capteurs des cardans. Pour l'instant avec deux ESP32 qui fonctionnent comme client et le server qui ne log pas les données ils est possible d'atteindre un peu plus que 7k5SPS avec chaque capteur.

![SystemDiagram](SystemDiagram.drawio.png)

### Client
Le code du client est celui qui vas dans les ESP32 sur les cardans. Il permet de lire l'entré analogue de l'amplificateur.
### Server
Le code du server est pour le ESP32 sur le Baja. Il reçoit les données des capteurs sur les cardans.
### Setup
Chaque ESP32 a une adresse MAC unique, pour la déterminer il suffit d'upload le code de setup. Ceci est important pour savoir lequel des ESP32 est le server et où se situe les ESP32 sur le baja (arrière, devant, droite, gauche).
## Futur
Il est peut être possible que les deux capteurs à l'arrière agissent de pont entre le server et les capteurs avants pour avoir une meilleur connection.
### Resources
Vidéo utilisé pour faire le code et comprendre comment ESP-NOW fonctionne: <br/>
 - [ESP-NOW - Peer to Peer ESP32 Network](https://www.youtube.com/watch?v=bEKjCDDUPaU&ab_channel=DroneBotWorkshop)
