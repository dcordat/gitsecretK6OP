# Bluetooth Raspberry Pi
-----------------------------
 - Le code c permet de construire l'en-tête hid, l'écrire en format hex dans le fichier tmp.txt.
 - Le code python permet d'établir la connexion bluetooth avec le host, puis lit le fichier tmp.txt, transforme l'en-tête en format ASCII et l'envoie.
- Le script pairing.sh permet de lancer la commande pour faire l'appairage, il suffit de choisir l'adresse MAC du host (je compte mettre en place un menu linux réactif pour améliorer l'ergonomie)

### Execution
1) Lancer le code python
2) Dans une nouvelle fenêtre, lancer le script pairing.sh et suivre les instructions
3) Une fois le pairing est effectué, choisir le type de mouvement ou de click dans le menu qui s'affichera dans la première fenêtre.
