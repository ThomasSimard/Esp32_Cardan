# Esp32_Cardan
Code pour les capteurs des cardans.

### Client
Le code du client est celui qui vas dans les ESP32 sur les cardans. Il permet de lire l'entré analogue de l'amplificateur.
### Server
Le code du server est pour le ESP32 sur le Baja. Il reçoit les données des capteurs sur les cardans.
### Setup
Chaque ESP32 a une adresse MAC unique, pour la déterminer il suffit d'upload le code de setup. Ceci est important pour savoir lequel des ESP32 est le server et où se situe les ESP32 sur le baja (arrière, devant, droite, gauche).

Resources utilisé pour faire le code: <br/>
[ESP-NOW](https://www.youtube.com/watch?v=bEKjCDDUPaU&ab_channel=DroneBotWorkshop)
