#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include "graph.h"
#include "const.h"

class FenetreInterface
{
    friend class Fenetre;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;

        grman::WidgetButton m_save_button;
        grman::WidgetText m_save_button_label;
        grman::WidgetButton m_load_button;
        grman::WidgetText m_load_button_label;
        grman::WidgetButtonSwitch m_move_button;
        grman::WidgetText m_move_button_label;

        grman::WidgetButton m_delete_button;
        grman::WidgetText m_delete_button_label;

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        FenetreInterface(int x, int y, int w, int h);
};


class Fenetre
{
    private :

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<FenetreInterface> m_interface = nullptr;
        Graph m_graphe;

    public:

        Fenetre (FenetreInterface *interface=nullptr) : m_interface(interface), m_graphe(Graph())  {m_interface = std::make_shared<FenetreInterface>(0, 0, 1024, 768);}

        /// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
        void update();
        void make_example() {m_graphe.make_example();}
};

#endif // FENETRE_H_INCLUDED
