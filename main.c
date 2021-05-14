
#include "fonctions.h"

int main() {

    Game partie;

    // Code temporaire

    /*partie.mode = 1;
    partie.turn = 1;

    initPlayer(&partie.joueur1,10,0,0,0);
    initPlayer(&partie.joueur2,10,0,0,0);

    int defaultFlotte[] =
            {
            3,0,2,3,1,1,1,0,0,0,
            2,1,2,8,1,1,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            };

    for (int i = 0; i < 100; ++i) {
        *(partie.joueur1.flotte + i) = defaultFlotte[i];
        *(partie.joueur2.flotte + i) = defaultFlotte[i];

    }*/

    //Fin code temporaire

    mainMenu(&partie);

    while (1) {
        gameMenu(&partie);
        printf("\n\nTour suivant\n\n");
//        getint();
    }

    return 0;
}
