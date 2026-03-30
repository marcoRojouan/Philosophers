🧭 🧠 ROADMAP COMPLÈTE — PHILOSOPHERS



🟢 1. Parsing & validation

👉 (déjà fait chez toi ✅)

Objectif :

lire les arguments
vérifier qu’ils sont valides
remplir ta struct globale



🟡 2. Initialisation des structures

🔹 2.1 Créer t_table (ou t_data)
stocke tous les paramètres
tableau de philosophes
tableau de mutex (forks)
🔹 2.2 Initialiser les philosophes
malloc tableau
boucle :
id
pointeur vers data
meals_eaten = 0
last_meal = 0 (temporaire)

👉 (tu es ICI actuellement)

🔹 2.3 Initialiser les forks (mutex)
malloc tableau de mutex
boucle :
pthread_mutex_init
🔹 2.4 Associer les forks aux philosophes

👉 chaque philo doit avoir :

fork gauche
fork droite

💥 étape CRUCIALE (beaucoup se trompent ici)



🔵 3. Gestion du temps

🔹 créer une fonction get_time()

👉 retourne le temps actuel en ms

🔹 stocker start_time
au lancement de la simulation
🔹 timestamps relatifs

👉 pour afficher :

current_time - start_time



🟣 4. Création des threads
🔹 un thread par philosophe
pthread_create
🔹 lancer une routine

👉 fonction principale du philo



🔴 5. Routine des philosophes

Chaque philo fait en boucle :

🍴 prendre fork gauche
🍴 prendre fork droite
🍝 manger
😴 dormir
🤔 penser
⚠️ À gérer ici :
ordre de prise des forks (éviter deadlock)
affichage sécurisé
mise à jour last_meal



⚫ 6. Protection des données

👉 utiliser des mutex pour :

forks (déjà fait)
affichage (important)
variables partagées (stop, etc.)


🟤 7. Détection de mort
🔹 créer un “monitor”

👉 boucle qui vérifie :

current_time - last_meal > time_to_die

👉 si oui :

afficher mort
stop simulation



🟠 8. Condition d’arrêt

Arrêter si :

un philosophe meurt
OU tous ont mangé assez (si option)

👉 mettre stop = 1



🔵 9. Synchronisation & clean
pthread_join tous les threads
destroy mutex
free
💥 LES 3 GROS PIÈGES DU PROJET
1. Deadlock (tout le monde prend une fourchette)

👉 solution :

ordre différent (pair/impair)
2. Race conditions

👉 accès non protégé aux variables

3. Timing imprécis

👉 mauvais usleep / mauvais calcul temps