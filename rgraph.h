#ifndef RGRAPH_H_INCLUDED
#define RGRAPH_H_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <utility>

#include "grman/grman.h"
#include "graph.h"
#include "const.h"
#include "basics.h"

/***************************************************
                    VERTEX
****************************************************/

class RVertexInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class RVertex;
    friend class REdgeInterface;
    friend class RGraph;
    friend class Fenetre;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        // Un label indiquant l'index du sommet
        grman::WidgetText m_label_idx;

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        RVertexInterface(int idx, int x, int y);
};


class RVertex
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class RGraph;
    friend class RVertexInterface;
    friend class REdge;
    friend class REdgeInterface;
    friend class Fenetre;

    private :
        /// liste des indices des arcs arrivant au sommet : accès aux prédécesseurs
        std::vector<int> m_in;

        /// liste des indices des arcs partant du sommet : accès aux successeurs
        std::vector<int> m_out;

        std::vector<int> m_equi;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<RVertexInterface> m_interface = nullptr;



        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne précédente est en gros équivalent à la ligne suivante :
        // VertexInterface * m_interface = nullptr;


    public:

        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        RVertex (RVertexInterface *interface=nullptr) :
            m_interface(interface)  {  }

        /// Vertex étant géré par Graph ce sera la méthode update de graph qui appellera
        /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
        /// Voir l'implémentation Graph::update dans le .cpp
};



/***************************************************
                    EDGE
****************************************************/

class REdgeInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class REdge;
    friend class RGraph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        REdgeInterface(RVertex& from, RVertex& to);
};


class REdge
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class RGraph;
    friend class REdgeInterface;
    friend class Fenetre;

    private :
        /// indice du sommet de départ de l'arc
        int m_from;

        /// indice du sommet d'arrivée de l'arc
        int m_to;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<REdgeInterface> m_interface = nullptr;


    public:

        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        REdge (REdgeInterface *interface=nullptr) :
            m_interface(interface)  {  }

        /// Edge étant géré par Graph ce sera la méthode update de graph qui appellera
        /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
        /// Voir l'implémentation Graph::update dans le .cpp
};




/***************************************************
                    GRAPH
****************************************************/

class RGraphInterface
{
    friend class RGraph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        /// Dans cette boite seront ajoutés les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;


        // A compléter éventuellement par des widgets de décoration ou
        // d'édition (boutons ajouter/enlever ...)

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        RGraphInterface(int x, int y, int w, int h);
};


class RGraph
{
    friend class Fenetre;

    private :

        /// La "liste" des arêtes
        std::map<int, REdge> m_edges;

        /// La liste des sommets
        std::map<int, RVertex> m_vertices;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<RGraphInterface> m_interface = nullptr;

        int equiVertex(int a);

    public:

        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        RGraph (RGraphInterface *interface=nullptr) :
            m_interface(interface)  {  }

        void add_interfaced_vertex(int idx, int x, int y);
        void add_interfaced_edge(int idx, int vert1, int vert2);

        /// Méthode spéciale qui construit un graphe arbitraire (démo)
        /// Voir implémentation dans le .cpp
        /// Cette méthode est à enlever et remplacer par un système
        /// de chargement de fichiers par exemple.

        void create(Graph const& other, std::vector<std::vector<int>> Sconnexe_vertex);
        void delete_vertex(int idx);
        void delete_edge(int idx);
        void close_graphe();


        /// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
        void update();
};

#endif // RGRAPH_H_INCLUDED
