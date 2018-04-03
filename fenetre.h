#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include "graph.h"

class FenetreInterface
{
    friend class Fenetre;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;

    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        FenetreInterface(int x, int y, int w, int h);
};


class Fenetre
{
    private :

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<FenetreInterface> m_interface = nullptr;
        Graph m_graphe;

    public:

        Fenetre (FenetreInterface *interface=nullptr) : m_interface(interface), m_graphe(Graph())  {if(!m_interface) m_interface = std::make_shared<FenetreInterface>(0, 0, 1024, 768);}

        /// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
        void update() {m_graphe.update();}
        void make_example() {m_graphe.make_example();}
};

#endif // FENETRE_H_INCLUDED
