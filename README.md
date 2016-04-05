# Font-extractor

Semi-automatic extraction of characters for the generation of images and old documents


## Manual installation
```
// Opencv installation
#Ubuntu Linux distribution
$ sudo apt-get install libopencv-dev
    
#MAC distribution (with Homebrew)
$ brew install opencv

// Libnavajo installation
$ git clone https://github.com/titi38/libnavajo.git
$ cd libnavajo
$ cmake .
$ make
$ sudo make install
    
// Font-extractor installation
$ git clone https://github.com/rtisne/Pdp.git
$ cd Pdp/server
$ make
```

## Docker installation
First install docker https://docs.docker.com/engine/installation/
```    
$ docker run -dti -p  80:8080 rtisne/font-extractor
```

This may take some times.
After the installation just go to your docker ip address 

## How to use
To lauch the server, go into the server folder and make:
```    
$ ./main
```
The server will be run by default on port 8080.
You can change the port in the file libnavajo/src/WebServer.cc of libnavajo

```#define DEFAULT_HTTP_PORT 8080```

If you are in local, you can access to the server throught: http://localhost:8080

## Demo
The application is host online :
https://intranet.iut.u-bordeaux.fr/navajo/

## Building and running unit tests
Tests are available to test the algorithm part that retrieves components in the image.
To launch test go to the test folder and build:
```    
$ cmake.
$ make
$ ./Unit_test
```

## Development
Developing by:
* [Tristan Autret](https://github.com/tautret)
* [Anthony Boschet](https://github.com/aboschet)
* [Thomas Labrousse](https://github.com/Shqrk)
* [Romain Tisné](https://github.com/rtisne)

[Report link]()

## Remarques Nicholas Journet


page 9 --> avec avec
page 9 --> attention avec une virgule pas d'esapce avant et un espace après
page 10 --> figure 1.2 et 1.2 on voit rien...
page 12 --> l'étape 2 est incompréhensible pour un non expert. à mon avis soit vous détaillez chaque étape (elle sert à quoi?) soit vous enlevez tous les -  et vous mettez simplement que l'étape 2 extrait des caractères et calcule la base line (et donnez la définition de la base line)
page 13 : figure 1.4 on voit vraimen rien du tout (et encore moins la base line)
page 18 --> URL qui déborde
page 19 --> URL qui déborde
page 22 --> ces tests sont décrits
page 23 --> opensource.... mais quelle licence? donnez les licences des dépendances... et indiquez celle que vous voulez mettre
page 26 --> nécessaires
page 29 --> permettront
page 30 : à l'arrivée
page 41 --> supprimées ajoutées
page 44 --> composée (plusieurs fois), associées, il reste un <<<<<<<. mine

ou la la ... à partir de la page 44 c'est la cata sur l'orthographe... j'arrête de corriger sinon j'en ai pour la nuit...

piratez ce soir le logiciel "antidote" et passez le sur votre texte  .... en l'état c'est pas possible de rendre ça à partir de la page 44.

sinon jusque là c'est bien!


le 2.1.2.7 est totalement incompréhensible
à mon avis il faut faire un schéma... ça sera plus lisible

globalement entre 44 et 55 c'est pas très bien rédigé.



page 58 : réelles (plusieurs fois)
page 6à : afficher exporter 
page 62 : posées
page 63 : se trouvent, été implémentées
page 66 : associée
page 67 : caractères, réagi, mis 

page 67 : je suis pas fan du passage avec apache + navajo... pourquoi parler des choses que vous n'utilisez pas?


à mon avis quelque part (au début) il manque un schéma global (genre un un costaud qui prend une page) et qui schématise un scénario type (de l'input de l'image à la sauvegarde).. 



page 70 : souhaiterait

page 74 : intérêt de la figure 4.6?



ça serait super ici de générer un petit message avec la fonte extraire en 4.5  ( vous en avez pour 5 minutes)

ah ah très drole l'image 4.13 --> pas très utile non? a priori 99% de la population mondiale c'est ce qu'est une page blanche :)


page 83 : fonctionne

partout : le nombre de composanteS connexeS


page 85 : veut dire quoi "qu'elles sont toutes " ???? pas français

page 88 --> sommes, associée , dépend, 


--> vraiment moi j'ai bien aimé la partie test, bravo! (bon sauf l'orthographe)

page 89 : de choisis???? nous avons choisi, ci-dessous

tableau 4.18 très moche --> colorier première ligne/première colone, mettre les unités dans la première ligne


un peu partout : chaine de caractèreS


page 91 : négliger, graphiques comparés, comprend, 30 secondes, importants, influe, conclut, 

page 92 : choisi, liées, liées, utilisées, liées , certaines utilisées, liés liée liée 

page 97 : on voit rien....

page 98 : permis, finies



------------ ------------------------------------------------

question/remarque 1 : bilan entre ce qui a été fait et ce qui a été annoncé (des tests pas faits? Jenkins ? méthodes agiles? convex hull? ...)

remarque 2 : pourquoi ne pas avoir un peu plus détaillé comment fonctionne libnavajo?







