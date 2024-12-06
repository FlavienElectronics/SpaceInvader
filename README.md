# Space Invaders 🎮🚀

Bienvenue dans **Space Invaders**, un jeu rétro classique où vous devrez combattre de méchants envahisseurs venus de l'espace !
Ce jeu est entièrement contrôlable via une manette ESP8266 connectée au système, offrant une expérience immersive et rétro digne d'une ATARI 2600 ou d'un COMMODORE 64 !

## ⚙️ Faire fonctionner le Space Invaders

**Installation**

    make install
En executant «make install», les librairies sont installées automatiquement.
### 📚 Librairies

Pour utiliser correctement ce programme, il faut installer les librairies (LINUX) avec les commandes suivantes (dans le cas où «make install» échoue) :

#### 🖥️ Librairie graphique
    sudo apt install libsfml-dev
#### ⚡ Librairie USART
    sudo apt install libboost-all-dev 

### 📦 Compilation

Pour aisément compiler le programme, nous avons fournis un fichier Makefile.
Il suffit donc de se rendre dans le dossier **/src** puis d'utiliser les commandes suivantes :

**Compilation simple**

    make   

**Compilation et execution**

    make r

## 📝 Etapes importantes pour le bon fonctionnement des programmes

* Connectez l’ESP8266 sur la carte shield
* Connectez le buzzer sur la connectique D6 du shield
* Connectez l’écran LCD sur la connectique I2C n°1 du shield
* Connectez le potentiomètre rotatif sur la connectique A0 du shield
* Connectez la LED sur la connectique D7 du shield
* Connectez le bouton poussoir sur la connectique D5 du shield
* Branchez la carte en USB au PC
* Exécutez le programme “SpaceInvader” sur le PC en ayant vérifié que la carte ESP8266 ait bien été identifiée par le système (sur le port /dev/ttyUSB0)
* Si la télécommande est détectée et qu’elle se synchronise avec le jeu, cette dernière affichera le message “Connexion avec succès” durant 3 secondes
* Vous pouvez enfin appuyer sur le bouton pour lancer une partie


## ℹ️ Plus d'informations

### ⚠️A noter :
Le programme a été testé sur un machine virtuelle linux, le port de liaison USB pour la communication USART est le suivant : **/dev/ttyUSB0**.
Ce n'est pas sur mais peut-être que ce port doit être modifié si d'autres périphériques USB sont déjà connectés à la machine linux (/dev/ttyUSB1 ou /dev/ttyUSB2 ...)

## 🎮 Contrôles

Utilisez votre manette pour naviguer grâce au potentiomètre rotatif et tirer sur les envahisseurs grâce au magnifique bouton poussoir ! Profite d'une expérience rétro et amusante sans limite !

## ♥️ Remerciements

Nous tenons sincèrement à remercier nos tuteurs encadrant pour ce Bureau d'Etude en C++ qui nous ont beaucoup aidés et motivés dans ce magnifique projet.

## 📑 License

Ce projet est sous licence MIT. N'hésitez pas à contribuer, créer des issues ou soumettre des pull requests pour améliorer le jeu !
