#include "grman/grman.h"
#include <iostream>

#include "fenetre.h"

volatile int close_button_pressed = 0;
void close_button_handler()
{
    close_button_pressed = 1;
}
END_OF_FUNCTION(close_button_handler)
LOCK_FUNCTION(close_button_handler);

int main()
{
    // A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    // Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    // Un exemple de graphe
    Fenetre g;

    set_close_button_callback(close_button_handler);

    // Vous gardez la main sur la "boucle de jeu"
    // ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] && !close_button_pressed)
    {
        // Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        // Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();

//* bug load multiple
//* numero sommet dans fichier
//* bug delete 2 fois
//* bug forte connexite
//* valeur renvoie connexe
// cout inutile
