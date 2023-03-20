# ESP32_Data_Display

Le fichier c contient un code Arduino qui crée un serveur web et sert une page web qui affiche les données des capteurs. Le code utilise le module WiFi ESP32 et la bibliothèque WebServer pour créer un serveur qui écoute sur le port 80. Le serveur sert une page HTML avec du CSS et du JavaScript intégrés. La page HTML affiche trois valeurs de capteurs : la détection de présence, la détection de mouvement et la détection de chute.

La fonction handleRoot() du serveur gère la demande HTTP entrante en envoyant une réponse HTTP avec le contenu de la page HTML. La page HTML a un bouton Rafraîchir les données qui, lorsqu'il est cliqué, envoie une demande GET HTTP au serveur. La fonction handleRoot() du serveur gère la demande HTTP entrante en envoyant une réponse HTTP avec les valeurs de capteurs mises à jour.

Le code JavaScript intégré dans la page HTML vérifie périodiquement l'état de chute et affiche une notification s'il détecte une chute. Le code JavaScript met également à jour la date et l'heure affichées dans l'en-tête de la page web chaque seconde.
