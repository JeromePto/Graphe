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
        grman::WidgetTextEdit m_load_file;
        grman::WidgetButton m_close_button;
        grman::WidgetText m_close_button_label;
        grman::WidgetButtonSwitch m_move_button;
        grman::WidgetText m_move_button_label;
        grman::WidgetButtonSwitch m_edit_button;
        grman::WidgetText m_edit_button_label;

        grman::WidgetBox m_mode_box;
        grman::WidgetButtonSwitch m_button_structurel;
        grman::WidgetText m_button_structurel_label;
        grman::WidgetButtonSwitch m_button_fonctionnel;
        grman::WidgetText m_button_fonctionnel_label;

        grman::WidgetButton m_delete_button;
        grman::WidgetText m_delete_button_label;

        grman::WidgetBox m_struct_box;
        grman::WidgetButtonText m_connexe_button;
        grman::WidgetText m_connexe_label;
        grman::WidgetButtonText m_connexe_display;
        grman::WidgetButtonText m_kconnexe_button;
        grman::WidgetText m_kconnexe_label;
        grman::WidgetButtonText m_kconnexe_display;

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
        // 1 = structurel, 2 = fonctionnel
        int m_mode = 1;

    public:

        Fenetre (FenetreInterface *interface=nullptr) : m_interface(interface), m_graphe(Graph())  {m_interface = std::make_shared<FenetreInterface>(0, 0, 1024, 768);}

        /// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
        void update();
        void update_struct();
        void update_edit_button();

        void make_example() {m_graphe.make_example();}
};

#endif // FENETRE_H_INCLUDED
