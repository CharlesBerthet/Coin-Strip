# Coin Strip

## Regles du jeu

- *Sur un plateau de 13 cases sont disposés 5 jetons de manière aléatoire. Les jetons peuvent être déplacer d'une ou plusieurs cases uniquement vers la gauche sans la possibilité de sauter par dessus un jeton.*
- *Le but du jeu est simple : être le dernier à jouer, c'est-à-dire à déplacer le dernier jeton vers la gauche et ainsi gagner la partie.*



## Attendus du projet

:bulb: Une architecture **Client - Serveur** est utilisé pour ce projet 

#### Fonctionnalités 

-  La communication client-serveur doit être faite en **TCP/IP**
-  Le serveur doit disposer d’un **fichier de configuration** permettant de fournir les paramètres 
nécessaires à son paramétrage, comme le port d’écoute.
- La partie commencera dès que les deux joueurs sont connectés.
- Le serveur décidera quel joueur doit commencer.
- Le client doit disposer d’un fichier de configuration contenant **l’IP** du serveur ainsi que le 
**port de connexion**
- Le **contrôle** de la validité du mouvement d’une pièce sera fait sur le **client**.

#### Cahier des charges fonctionnel

- Présenter le projet, son contexte, sa finalité
- Préciser les **contraintes techniques**.
- Lister les **prestations attendues** 
  - *design, développement, déploiement, maintenance, livrables*
- Définir les **besoins fonctionnels** 
  - *lister toutes les fonctionnalités avec un ordre de priorité expliquer l’enchaînement logique des tâches*
- Déterminer les **ressources** 
  - *humaines, financières, matérielles et temporelles allouées au projet*
- Indiquer les **annexes** 
  - *format des fichiers, des données, des échanges*


#### Documentation technique

- Décrire le **protocole de communication**
- Données échangées entre le client et le serveur (*format, taille...*)
- Décrire les **structures de données** utilisées
  

## Accès aux logs

Commande lors de la compilation : 
    
    ```make log``` (=) ```make run + génération des logs```

Commande bash : 
    ```tail /var/log/messages | grep "CoinStrip"```
    

## Consigne du GIT

:bulb: L'architecture *client* est stocké dans **/client**, le *serveur* dans **/serveur** et les *fichiers* communs sont dans **/common**

---

#Information développeur

### Installation du package de logs

Commandes à faire (sur une machine Fedora): 
```
sudo dnf update
sudo dnf install syslog
```

**Accès aux logs :**
Suivre au fur et à mesure : 
```tail -f /var/log/messages | grep "CoinStrip"```
Voir les logs après : 
```tail /var/log/messages | grep "CoinStrip"```

