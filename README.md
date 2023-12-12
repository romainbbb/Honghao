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




