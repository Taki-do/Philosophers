# Philosopher

## French version below

## Introduction
Philosopher is a project that simulates the famous Dining Philosophers problem using multithreading and synchronization techniques. The goal is to manage multiple philosophers who alternate between eating, thinking, and sleeping while ensuring no deadlocks or race conditions occur.

## Compilation
To compile the project, use the following command:

```sh
make
```

This will generate the `philo` executable.

## Usage
Run the program with the following command:

```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Arguments:
- `<number_of_philosophers>`: The number of philosophers (and forks) at the table.
- `<time_to_die>`: Time in milliseconds before a philosopher dies without eating.
- `<time_to_eat>`: Time in milliseconds a philosopher takes to eat.
- `<time_to_sleep>`: Time in milliseconds a philosopher spends sleeping.
- `[number_of_times_each_philosopher_must_eat]` (optional): If provided, the simulation stops when each philosopher has eaten this many times.

### Example:
```sh
./philo 5 800 200 200 7
```
This runs a simulation with 5 philosophers, where each dies after 800ms without eating, takes 200ms to eat, sleeps for 200ms, and must eat 7 times before stopping.

## Features
- Uses **threads** to simulate each philosopher.
- Implements **mutexes** to handle forks and avoid race conditions.
- Ensures **no deadlock** occurs.
- Optional stopping condition when all philosophers have eaten a certain number of times.

## Known Issues
- If the number of philosophers is **1**, the program will exit after the philosopher starves (since there is only one fork available).
- High values for philosophers or time constraints may lead to unexpected behavior due to system limitations.

## Author
Taki-do (github) and taomalbe (42).

## Licence
This project is under MIT licence.



## Version française 🇫🇷

## Description
Philosopher est une implémentation du problème des philosophes mangeurs en C.
Ce projet simule des philosophes assis autour d'une table avec des fourchettes (une pour chaque philosophe) et gère leur synchronisation pour éviter les dataraces (accès concurrent) et les deadlocks (interblocage).

## Compilation
Pour compiler le programme, utilisez la commande suivante :

```bash
make
```

Cela générera l'exécutable `philo`.

## Utilisation

Le programme s'exécute avec la syntaxe suivante :

```bash
./philo <nombre_de_philosophes> <temps_à_mourir> <temps_à_manger> <temps_à_dormir> [nombre_de_repas]
```

### Paramètres :
- `<nombre_de_philosophes>` : Nombre de philosophes autour de la table.
- `<temps_à_mourir>` : Temps (en millisecondes) avant qu'un philosophe meure s'il ne mange pas.
- `<temps_à_manger>` : Temps (en millisecondes) qu'un philosophe met pour manger.
- `<temps_à_dormir>` : Temps (en millisecondes) qu'un philosophe met pour dormir.
- `[nombre_de_repas]` *(optionnel)* : Nombre de repas qu'un philosophe doit manger avant d'arrêter la simulation.

### Exemple :

```bash
./philo 5 800 200 200 7
```

Dans cet exemple, 5 philosophes sont créés avec les délais suivants :
- Un philosophe meurt après 800ms sans manger.
- Il met 200ms à manger.
- Il met 200ms à dormir.
- Il doit manger 7 fois avant d'arrêter la simulation.

## Fonctionnalités
- Gestion des threads pour simuler le comportement des philosophes.
- Synchronisation avec des mutex pour gérer les fourchettes.
- Protection contre les interblocages.
- Support du nombre de repas optionnel pour limiter la simulation.

## Remarque
Le programme ne doit jamais provoquer de comportement indéfini (segmentation fault, interblocage non géré, etc.).

## Auteur
Taki-do (github) et taomalbe (42).

## Licence
Ce projet est sous licence MIT.
