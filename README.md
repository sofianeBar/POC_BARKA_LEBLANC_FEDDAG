# README - Coffre-fort Sécurisé et Connecté

## 1. CONTEXTE

Dans le cadre de notre module sur les Objets Connectés à faible consommation d'énergie, nous avons participé à des travaux pratiques guidés. Ces exercices nous ont permis d'appliquer diverses notions liées à l'IoT, telles que la gestion de la consommation énergétique des dispositifs connectés, ainsi que l'utilisation concrète du microcontrôleur ESP32, un outil clé pour les projets IoT à faible consommation.

Fort de ces apprentissages, notre équipe, composée de Sofiane Feddag, Barka Sofiane et Yann le Blanc, a développé un Proof of Concept (PoC) visant à démontrer notre maîtrise des concepts théoriques et pratiques à travers un système IoT fonctionnel que nous présenterons lors de la séance finale. Ce projet doit répondre aux contraintes suivantes :

- Chaque membre de l'équipe a une fonctionnalité distincte à développer.
- Le système IoT doit interagir avec son environnement via des capteurs, des LED, des moteurs ou des écrans.
- Le système doit être relié à l'extérieur via une API, un serveur web, un autre dispositif connecté ou un service d'envoi d'emails.
- L'architecture et le code du projet doivent être optimisés pour minimiser la consommation d'énergie.

Ce projet nous offre l'opportunité de mettre en œuvre nos compétences en conception, programmation et optimisation de systèmes embarqués, tout en respectant les impératifs de faible consommation énergétique.

## 2. PRÉSENTATION DU PROJET

Notre Proof of Concept consiste à concevoir un coffre-fort sécurisé et connecté, alliant praticité et innovation technologique. L’idée principale est de proposer un système de protection renforcé grâce à des fonctionnalités électroniques avancées et une connectivité intelligente, répondant aux besoins de sécurité modernes.

### Fonctionnalités du Système :

- **Mécanisme de Verrouillage :** Un servomoteur simule l'ouverture et la fermeture du coffre.
- **Accès Sécurisé :** L'utilisateur entre un code secret via un pavé numérique à 9 touches. Trois tentatives d'accès sont autorisées.
  - À chaque tentative incorrecte, un buzzer se déclenche et le nombre de tentatives restantes s'affiche sur un écran LCD.
  - Si le code est incorrect après trois essais, le système se verrouille temporairement pour renforcer la sécurité.
- **Ouverture du Coffre :** Si le code est correct, le servomoteur s'active pour ouvrir le coffre et un message "Le coffre est ouvert" s'affiche sur l'écran.
- **Notifications en Temps Réel :** Un SMS est envoyé au propriétaire du coffre pour l'informer de l'ouverture, offrant ainsi une couche supplémentaire de surveillance à distance.

Ce concept de coffre-fort intelligent combine des technologies de l'IoT et de la sécurité domestique pour offrir une solution pratique et efficace. Il vise à répondre aux besoins de sécurisation tant des particuliers que des entreprises. Avec un design axé sur l'optimisation de la consommation énergétique, cette solution respecte les exigences d'efficacité énergétique, un élément clé dans les dispositifs connectés d'aujourd'hui.

## 3. CONFIGURATION ET UTILISATION

### Matériel Nécessaire :

- Microcontrôleur ESP32
- Servomoteur
- Pavé numérique 4x4
- Écran LCD
- Buzzer
- Module de communication (ex. : GSM pour l'envoi de SMS)
- Breadboard et câbles de connexion


## 4. CONCLUSION

Ce projet représente une étape importante dans notre apprentissage des objets connectés et de la gestion de l'énergie. Nous espérons que ce coffre-fort sécurisé et connecté répondra aux attentes des utilisateurs en matière de sécurité et de praticité tout en respectant les enjeux d’efficacité énergétique.
