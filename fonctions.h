//
// Created by jossu on 11/05/2021.
//

#ifndef IFE2_FONCTIONS_H
#define IFE2_FONCTIONS_H

#endif //IFE2_FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"


int getint() {
    int n = fgetchar()-'0';
    fflush(stdin);
    return n;
}

void affGrille(Player *joueur) {
    printf("  A B C D E F G H I J\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d ",i);
        for (int j = 0; j < 10; ++j) {
            printf("%c ",*(joueur->grille + 10 * i + j));
        }
        printf("\n");
    }
}

void showFlotte(Player *joueur) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%d ",*(joueur->flotte + 10 * i + j));
        }
        printf("\n");
    }
}

Player* joueurActif(Game *partie) {
    if(partie->turn % 2 == 1){
        return &(partie->joueur1);
    } else {
        return &(partie->joueur2);
    }
}

Player* joueurInactif(Game *partie) {
    if(partie->turn % 2 == 1){
        return &(partie->joueur2);
    } else {
        return &(partie->joueur1);
    }
}

int* getBoat(Player *joueur, int x, int y){
    int *bateau = NULL;
    int bx, by, bl, bh;
    for (int i = 0; i < 10; ++i) {
        bateau = joueur->flotte + 10 * i;
        bl = *(bateau);
        bh = *(bateau+1);
        bx = *(bateau+2);
        by = *(bateau+3);

        if((by + (1-bh)*(bl-1)) >= y && by <= y && bx <= x && (bx + bh*(bl-1)) >= x)
        {
            if (bh)
            {
                return bateau + x - bx + 4;
            } else {
                return bateau + y - by + 4;
            }

        }

    }

    return NULL;
}

void checkSink(Game *partie) {

    int *bateau = NULL;
    int coule;

    Player *vise = joueurInactif(partie);

    for (int i = 0; i < 10; ++i) {

        bateau = vise->flotte + 10 * i;

        if (*bateau) {

            coule = 1;

            for (int j = 0; j < 6; ++j) {
                if (bateau[j + 4]) {
                    coule = 0;
                }
            }

            if (coule) {
                *bateau = 0;
                printf("Coule");
            }

        }



    }

}

void affFlotte(Player *joueur) {
    int *bateau;
    for (int i = 0; i < 10; ++i) {
        bateau = joueur->flotte + 10 * i;
        if (*bateau != 0)
        {
            printf("Bateau %d :\n",i+1);
            printf("Taille: %d\n",*bateau);
            printf("Orientiation : ");

            if (*(bateau+1)) {
                printf("Horizontal\n");
            } else {
                printf("Vertical\n");
            }

            printf("Coordonnees : (%d,%d)\n",*(bateau+2),*(bateau+3));

            printf("Etat : [ ");

            for (int j = 0; j < *bateau; ++j) {
                if (*(bateau+j+4))
                {
                    printf("_ ");
                } else {
                    printf("X ");
                }
            }

            printf("]\n\n");
        }
    }
}

void initGrid(char grille[100]) {
    for(int i = 0; i < 100; i++)
    {
        grille[i] = '_';
    }
}

void initFlotte(int flotte[100]) {
    for(int i = 0; i < 100; i++)
    {
        flotte[i] = 0;
    }
}

void affPlayer(Game *partie) {

    Player *joueur = joueurActif(partie);

    printf("\nTour du joueur %d\n",2 - partie->turn%2);

    if(partie->mode == 1)
    {
        printf("Grille :\n");
        affGrille(joueur);
    }
    printf("\nInventaire :\n");
    printf("Missiles simples : %d\n",joueur->inventaire.missile_s);
    printf("Missiles d'artillerie : %d\n",joueur->inventaire.missile_a);
    printf("Missiles tactiques : %d\n",joueur->inventaire.missile_t);
    printf("Bombes : %d\n",joueur->inventaire.missile_b);
    printf("\n");
    printf("Bateaux restants :\n\n");
    affFlotte(joueur);
}

void initPlayer(Player *joueur, int msimple, int mart, int mtact, int mbomb) {
    joueur->inventaire.missile_s = msimple;
    joueur->inventaire.missile_a = mart;
    joueur->inventaire.missile_t = mtact;
    joueur->inventaire.missile_b = mbomb;
    initGrid(joueur->grille);
    initFlotte(joueur->flotte);

}

int tirer(Game *partie) {
    int x,y;
    int *cible = NULL;
    Player *tireur = joueurActif(partie);
    Player *vise = joueurInactif(partie);
    printf("Entrez x : ");
    x = getint();
    printf("Entrez y : ");
    y = getint();

    cible = getBoat(vise,x,y);
    if (cible == NULL) {
        tireur->grille[10*y+x] = 'O';
        printf("Echec\n");
    } else {
        *cible = 0;
        tireur->grille[10*y+x] = 'X';
        printf("Touche\n");
    }

    checkSink(partie);

    printf("\nGrille :\n");
    affGrille(tireur);


    return 1;




}

void finTour(Game *partie){

    Player *vise = joueurInactif(partie);
    int mort = 1;
    int *bateau;

    for (int i = 0; i < 10; ++i) {
        bateau = vise->flotte + 10 * i;

        if (*bateau) {
            mort = 0;
        }

    }

    if (mort)
    {
        printf("\n\n**** Victoire du joueur %d ! ****\n",2 - partie->turn % 2);
        exit(0);
    } else {
        partie->turn++;
    }
}

void createPlayer(Player *joueur)
{
    int choix, effectif, taille, horizontal, x, y;
    int *bateau;
    effectif = 0;
    initPlayer(joueur,10,0,0,0);

    while (1)
    {
        printf("Choisissez une action :\n");
        printf("1: Ajouter bateau\n");
        printf("2: Terminer creation\n");
        choix = getint();
        if (choix == 2)
        {
            affFlotte(joueur);
            return;
        }

        bateau = joueur->flotte + 10 * effectif;

        printf("Entrez la taille du bateau : ");
        taille = getint();
        printf("Bateau horizontal : ");
        horizontal = getint();
        printf("Abcisse du bateau : ");
        x = getint();
        printf("Ordonnee du bateau : ");
        y = getint();


        for (int i = 0; i < taille; ++i) {
            *(bateau+4+i) = 1;

            if (getBoat(joueur,x,y) != NULL || x + taille*horizontal > 10 || y + taille *(1-horizontal) > 10) {

                exit(0);
            }
        }

        *bateau = taille;
        *(bateau+1) = horizontal;
        *(bateau+2) = x;
        *(bateau+3) = y;

        effectif++;


    }

}

void createGame(Game *partie) {

    partie->turn = 1;

    printf("Choisissez un mode de jeu : ");
    partie->mode = getint();

    printf("Creation joueur 1 :\n");
    createPlayer(&partie->joueur1);
    printf("Creation joueur 2 :\n");
    createPlayer(&partie->joueur2);

}

void gameMenu(Game *partie){
    int choix,fin;
    fin = 0;
    affPlayer(partie);
    printf("Choisissez une action :\n");
    printf("1: Tirer\n");
    printf("2: Sauvegarder\n");
    choix = getint();

    while (!fin) {
        if (choix == 1) {
            fin = tirer(partie);
        } else if (choix == 2) {
            exit(0);
            // sauvegarder(partie);
        } else {
            printf("\nERROR CHOICE\n");
            exit(0);
        }
    }


    finTour(partie);

}

void mainMenu(Game *partie) {
    int choix;
    printf("Choisissez une action :\n");
    printf("1: Nouvelle partie\n");
    printf("2: Charger une partie\n");
    printf("3: Quitter\n");
    choix = getint();

    switch (choix) {
        case 1:
            createGame(partie);
            break;
        case 2:
            //loadGame();
        case 3:
            exit(0);
            break;
        default:
            printf("ERROR CHOICE\n");
            exit(0);
            break;
    }

}