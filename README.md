# Microcontro_20231212
## Avant de commencer 
https://www.youtube.com/watch?v=KjETPxv_VR4

Regardez cette vidéo pour apprendre les bases. Par exemple, l'ajout d'une bibliothèque.

![Image text](https://github.com/romainbbb/Microconti/blob/main/image/1.png)

aussi important, apres le connecter le board, TOOLS---FIRMWARE UPTATER
Mettez à jour votre tableau, c'est un must.

![Image text](https://github.com/romainbbb/Microconti/blob/main/image/2.png)


## dht 11
J'ai échoué celui-ci et j'espère que la prochaine personne le terminera. Je crois que c'est très simple.

## heart rate  MAX30102
pin:
3v3 -----    3v3
gnd---gnd
sda--sda
scl--scl

### code:max30102--max30102

### Ce qu'il faut faire : 
Le formulaire de sortie est trop simple.
Il ne s'agit plus que de trois nombres consécutifs. Veuillez ajouter un texte descriptif. Par exemple : battement de coeur : 100 BP/min

## led

### code
led-led

Juste pour le fun.

## heart+led
pin

gnd-gnd

vcc-5v

sda,scl-sda,scl

### code
max30102_led-meme

### Ce qui doit être modifié
L'écran comporte deux lignes et trois ou quatre lignes de données. Il ne peut donc pas être affiché en une seule fois. Ma solution actuelle est de le faire tourner. (L'écran dispose également d'autres méthodes d'affichage)
Veuillez apporter les modifications correspondantes après avoir ajouté les données dht11.

## heart+wifi

### code
max30102_wifi

### Modifier
Il y a beaucoup à modifier dans cette partie.

Dans l'espace réservé au nom du wifi, écrivez le nom de votre wifi. Si vous ne le savez pas, vous pouvez utiliser scanwifi par exemple.

Remplissez ensuite votre mot de passe wifi comme mot de passe.

Le résultat de sortie est une adresse IP. Vous saisissez cette adresse sur votre ordinateur ou votre téléphone portable et vous pouvez voir les données.

Le site Web doit être rendu plus beau.

# heart+bluetooth 

C'est la chose la plus gênante.

## bluetooth taper(Cette étape peut être ignorée, juste pour le plaisir)
Nous ne transmettons pas de données en premier, nous essayons de communiquer entre la carte et le téléphone mobile.

aller ce cite
https://forum.arduino.cc/t/connecting-an-arduino-nano-33-iot-to-a-mobile-device-over-bluetooth-classic/967208/2

![Image text](https://github.com/romainbbb/Microconti/blob/main/image/3.png)

Effectuez les étapes 1, 2, 3 et 4, ne faites pas l'étape 5.(Suivez exactement les étapes sur le site Web.)

Téléchargez l'application sur votre téléphone.

dans ce site
https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/

![Image text](https://github.com/romainbbb/Microconti/blob/main/image/4.png)

Remplacez Serial.begin par (19200). Dans le même temps, le moniteur série a également été remplacé par 19 200.

Lorsque « RTS pin », appuyez et maintenez le petit point sur la carte.

Sur votre téléphone mobile, recherchez « ESP32-BT-SLAVE » et connectez-vous-y.

Dans l'application, dans l'appareil, connectez-vous. Entrez simplement dans le terminal.

Ensuite, vous pouvez parler à votre ordinateur et à votre téléphone portable.

"The device with name "ESP32-BT-Slave" is started.
Now you can pair it with Bluetooth!"






