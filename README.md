# Arcade

Ce projet a pour but de réaliser le fonctionnement d'une borne d'arcade.
Donner la possibilité de créer son propre jeu sur un environnement décidé par notre groupe.
Pour démontrer la possibilité de pouvoir faire cela, nous avons développé un snake et un pacman sur cet environnement

## Résultat

<div style="display: flex; flex-wrap: wrap">
    <img src="/images/menu_ncurse.png" width=600 height=300 />
    <img src="/images/menu_sdl2.png" width=600 height=300 />
    <img src="/images/menu_sfml.png" width=600 height=300 />
    <img src="/images/pacman.png" width=600 height=300 />
    <img src="/images/snake.png" width=600 height=300 />
</div>

## Jouer aux jeu


### Prérequis
    - CSFML
    - NCURSES
    - SDL2
    - C++
    - cmake

### Lancer le projet
```bash
./run.sh
./arcade ./lib/[lib_to_use]
```