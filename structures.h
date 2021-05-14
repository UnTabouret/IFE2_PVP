//
// Created by jossu on 11/05/2021.
//

#ifndef IFE2_STRUCTURES_H
#define IFE2_STRUCTURES_H

#endif //IFE2_STRUCTURES_H

typedef struct Inventory Inventory;

typedef struct Player Player;

typedef struct Game Game;

struct Inventory {

    int missile_s, missile_a, missile_b, missile_t;

};

struct Player {

    char grille[100];

    int flotte[100];

    Inventory inventaire;

};

struct Game {

    Player joueur1, joueur2;

    int mode, turn;

};
