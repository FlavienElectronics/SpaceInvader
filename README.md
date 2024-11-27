    LIBRAIRIES

Pour utiliser le programme correctement, il faut installer les librairies suivantes (LINUX) avec les commandes suivantes:

[Libraire graphique]
    sudo apt install libsfml-dev

[Librairie de lecture USART]
    sudo apt install libboost-all-dev 

    COMPILATION 

Pour compiler le programme un Makefile existe.
Il faut se rendre dans le dossier /src

Les commandes utiles sont les suivantes :

[Compilation] 
    make   

[Compilation et execution]
    make r

    PLUS D'INFORMATION

A noter :
    Le programme a été testé sur un machine virtuelle linux, le port de liaison USB pour la communication USART est le suivant : 
        /dev/ttyUSB0
    Ce n'est pas sur mais peut-être que ce port doit être modifié si d'autres périphériques USB sont déjà connectés à la machine linux.
        /dev/ttyUSB1 ou /dev/ttyUSB2 ...