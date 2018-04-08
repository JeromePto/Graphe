#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include <cmath>

#include "graph.h"
#include "rgraph.h"
#include "const.h"
#include "basics.h"

/// L'interface de la fenetre
class FenetreInterface
{
    friend class Fenetre;

    private :

        // Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        // ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        // le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

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

        grman::WidgetButtonText m_add_vertex;
        grman::WidgetButtonSwitch m_add_edge_button;
        grman::WidgetText m_add_edge_label;
        grman::WidgetButton m_delete_button;
        grman::WidgetText m_delete_button_label;

        grman::WidgetBox m_struct_box;
        grman::WidgetButtonText m_connexe_button;
        grman::WidgetText m_connexe_label;
        grman::WidgetButtonSwitch m_connexe_display;
        grman::WidgetText m_connexe_display_label;
        grman::WidgetButtonText m_kconnexe_button;
        grman::WidgetText m_kconnexe_label;
        grman::WidgetButtonSwitch m_kconnexe_display;
        grman::WidgetText m_kconnexe_display_label;
        grman::WidgetButtonSwitch m_rgraphe_button;
        grman::WidgetText m_rgraphe_button_label;

        grman::WidgetBox m_fonc_box;
        grman::WidgetButtonSwitch m_play_button;
        grman::WidgetText m_play_button_label;
        grman::WidgetVSlider m_slider_coefr;
        grman::WidgetText m_label_coefr;
        grman::WidgetVSlider m_slider_coefpred;
        grman::WidgetText m_label_coefpred;
        grman::WidgetVSlider m_slider_coefproi;
        grman::WidgetText m_label_coefproi;
        grman::WidgetVSlider m_slider_speed;
        grman::WidgetText m_label_speed;


    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        FenetreInterface(int x, int y, int w, int h);
};

/// La classe representant la fenetre contenant les boutons
class Fenetre
{
    private :

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<FenetreInterface> m_interface = nullptr;

        /// le graphe
        Graph m_graphe;

        /// Le graphe reduit
        RGraph m_rgraphe;

        /// Le mode actuel 1=structurel 2=fonctionnel
        int m_mode = 1;

        /// Si l'on est en edition
        bool m_edition = false;

        /// Le dernier etat de l'edition
        bool m_last_edition = false;

        /// La chaine de caractère de l'edition en cours
        std::string m_string_edit;

        /// Le buffer de selection pour l'ajout d'arrete
        std::vector<int> m_selected_buffer;

        /// Si un bouton a été activer
        bool m_change = true;

        /// Si la suppression est possible
        bool m_delete = true;

        /// Le coefficient r de l'etude fonctionnelle
        double m_coefr = 2000;

        /// Le coefficient de predateur de l'etude fonctionnelle
        double m_coefpred = 5000;

        /// La vitesse de simulation
        double m_coefproi = 1;

        /// Le coefficient r de l'etude fonctionnelle
        double m_speed = 1;

        /// La matrice de forte connexité
        std::vector<std::vector<int>> m_Sconnexe_vertex;

        /// La matrice de k-connexité
        std::vector<std::vector<int>> m_kconnexe_vertex;

    public:

        /// LE constructeur
        Fenetre (FenetreInterface *interface=nullptr) : m_interface(interface), m_graphe(Graph()), m_rgraphe(RGraph())  {m_interface = std::make_shared<FenetreInterface>(0, 0, 1024, 768);}

        /// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
        void update();

        /// update des éléments fonctionnant avec selection, edit et delete
        void update_selected();

        /// update du module de simulation
        void update_fonc();

        /// update du bouton add edge
        void update_fixe_button();

        /// update avant mise a jour des sliders
        void pre_update();

        /// update apres mise a jour des sliders
        void post_update();

        /// update avant mise a jour des boutons
        void pre_update_button();

        /// update apres mise a jour des boutons
        void post_update_button();

        /// fermetrue du graphe
        void close();

        /// rappel de la fonction make_example du graphe
        void make_example() {m_graphe.make_example();}
};

#endif // FENETRE_H_INCLUDED
