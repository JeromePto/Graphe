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

/* **************************************************
                    VERTEX
****************************************************/

/// L'interface d'un sommet
class RVertexInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class RVertex;
    friend class REdgeInterface;
    friend class RGraph;
    friend class Fenetre;

    private :

        // Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        // ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        // le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        /// Un label indiquant l'index du sommet
        grman::WidgetText m_label_idx;

    public :

        /// Le constructeur
        RVertexInterface(int idx, int x, int y);
};

/// La classe repesentant un sommet
class RVertex
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class RGraph;
    friend class RVertexInterface;
    friend class REdge;
    friend class REdgeInterface;
    friend class Fenetre;

    private :
        /// liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs
        std::vector<int> m_in;

        /// liste des indices des arcs partant du sommet : acc�s aux successeurs
        std::vector<int> m_out;

        /// Liste des sommets equivalant
        std::vector<int> m_equi;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<RVertexInterface> m_interface = nullptr;



        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne pr�c�dente est en gros �quivalent � la ligne suivante :
        // VertexInterface * m_interface = nullptr;


    public:

        /// Le constructeur par defaut
        RVertex (RVertexInterface *interface=nullptr) :
            m_interface(interface)  {  }

        // Vertex �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
        // le pre_update et post_update de Vertex (pas directement la boucle de jeu)
        // Voir l'impl�mentation Graph::update dans le .cpp
};



/* **************************************************
                    EDGE
****************************************************/

/// Interface de l'arrete
class REdgeInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class REdge;
    friend class RGraph;

    private :

        // Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        // ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        // le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        /// Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

    public :

        /// Le constructeur
        REdgeInterface(RVertex& from, RVertex& to);
};

/// Classe representant une arrete
class REdge
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class RGraph;
    friend class REdgeInterface;
    friend class Fenetre;

    private :
        /// indice du sommet de d�part de l'arc
        int m_from;

        /// indice du sommet d'arriv�e de l'arc
        int m_to;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<REdgeInterface> m_interface = nullptr;


    public:

        /// Le constructeur par defaut
        REdge (REdgeInterface *interface=nullptr) :
            m_interface(interface)  {  }

        // Edge �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
        // le pre_update et post_update de Edge (pas directement la boucle de jeu)
        // Voir l'impl�mentation Graph::update dans le .cpp
};




/* **************************************************
                    GRAPH
****************************************************/

/// Interface du graphe reduit
class RGraphInterface
{
    friend class RGraph;

    private :

        // Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        // ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        // le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        // Dans cette boite seront ajout�s les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;


        // A compl�ter �ventuellement par des widgets de d�coration ou
        // d'�dition (boutons ajouter/enlever ...)

    public :

        /// Le constructeur
        RGraphInterface(int x, int y, int w, int h);
};

/// Le graphe reduit
class RGraph
{
    friend class Fenetre;

    private :

        /// La "liste" des ar�tes
        std::map<int, REdge> m_edges;

        /// La liste des sommets
        std::map<int, RVertex> m_vertices;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<RGraphInterface> m_interface = nullptr;

        /// Renvoie le sommet equivalent dans le graphe reduit
        int equiVertex(int a);

    public:

        /// Le constructeur
        RGraph (RGraphInterface *interface=nullptr) :
            m_interface(interface)  {  }

        /// Permet d'ajouter un sommet a afficher
        void add_interfaced_vertex(int idx, int x, int y);

        /// Permet d'ajouter une arrete a afficher
        void add_interfaced_edge(int idx, int vert1, int vert2);

        // M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
        // Voir impl�mentation dans le .cpp
        // Cette m�thode est � enlever et remplacer par un syst�me
        // de chargement de fichiers par exemple.

        /// Permet de cr�er un graphe reduit a partir d'un graphe normal
        void create(Graph const& other, std::vector<std::vector<int>> Sconnexe_vertex);

        /// Permet de supprimer un sommet
        void delete_vertex(int idx);

        /// Permet de supprimer une arrete
        void delete_edge(int idx);

        /// Permet de fermer le graphe
        void close_graphe();


        /// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
        void update();
};

#endif // RGRAPH_H_INCLUDED
