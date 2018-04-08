#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/* *************************************************************
    Ici sont proposées 3 classes fondamentales
            Vertex (=Sommet)
            Edge (=Arête ou Arc)
            Graph (=Graphe)

    Les arêtes et les sommets et le graphe qu'ils constituent
    "travaillent" étroitement ensemble : pour cette raison les
    Vertex et Edge se déclarent amis (friend) de Graph pour que
    ce dernier puisse librement accéder aux membres (y compris
    protected ou private) de Vertex et Edge.

    Ces Classes peuvent êtres complétées. Il est également possible
    de les dériver mais il est malheureusement assez difficile
    de dériver le "triplet" des 3 classes en maintenant des relations
    cohérentes ( rechercher "c++ class covariance" et "c++ parallel inheritance"
    pour commencer .. ). Il est donc sans doute préférable, si possible,
    de "customiser" ces classes de base directement, sans héritage.

    Le modèle proposé permet de représenter un graphe orienté éventuellement
    pondéré, les arcs portent une ou des informations supplémentaire(s).
    Les relations/navigations Arcs -> Sommets et Sommets -> Arcs se font
    dans les 2 sens et utilisent des INDICES et NON PAS DES ADRESSES (pointeurs)
    de telle sorte que la topologie du graphe puisse être assez facilement
    lue et écrite en fichier, et bénéficie d'une bonne lisibilité en cas de bugs...

    Chaque arc possède 2 attributs principaux (en plus de son éventuelle pondération)
        -> m_from (indice du sommet de départ de l'arc )
        -> m_to (indice du sommet d'arrivée de l'arc )

    Chaque sommet possède 2 liste d'arcs (en plus de ses attributs "internes", marquages...)
        -> m_in (liste des indices des arcs arrivant au sommet : accès aux prédécesseurs)
        -> m_out (liste des indices des arcs partant du sommet : accès aux successeurs)

    Cependant le problème des indices (par rapport aux pointeurs) et qu'en cas
    de destruction d'une entité (un arc et/ou un sommet sont enlevés du graphe) alors :

    - Soit il faut reprendre toute la numérotation pour "boucher le trou"
      (par exemple on a supprimé le sommet n°4, le sommet n°5 devient le 4, 6 devient 5 etc...)
      ce qui pose des problèmes de stabilité et de cohérence, et une difficulté à ré-introduire
      le(s) même(s) élément supprimé (au même indice)

    - Soit on admet que la numérotation des sommets et arcs n'est pas contigue, càd qu'il
      peut y avoir des "trous" : sommets 0 1 5 7 8, pas de sommets 2 ni 3 ni 4 ni 6. La numérotation
      est stable mais on ne peut plus utiliser un simple vecteur pour ranger la liste de tous
      les arcs et tous les sommets aux indices correspondants, on peut utiliser une map
      qui associe un objet arc ou sommet à des indices arbitraires (pas forcément contigus)

    C'est cette 2ème approche qui est proposée ici : dans la classe graphe vous trouverez
        -> map<int, Edge>   m_edges
        -> map<int, Vertex> m_vertices    (le pluriel de vertex est vertices)

    Il faudra être attentif au fait que par rapport à un simple vecteur, le parcours des éléments
    ne pourra PAS se faire avec un simple for (int i=0; i<m_edges.size(); ++i) ...m_edges[i]...
    et que les parcours à itérateur ne donneront pas directement des Edge ou des Vertex
    mais des pairs, l'objet d'intérêt se trouvant dans "second" ("first" contenant l'indice)
                for (auto &it = m_edges.begin(); it!=m_edges.end(); ++it) ...it->second...
    ou bien     for (auto &e : m_edges) ...e.second...

    Il n'est pas obligatoire d'utiliser ces classes pour le projet, vous pouvez faire les votres

    Au niveau de l'interface, on dissocie une classe interface associée à chaque classe fondamentale
    de telle sorte qu'il soit possible de travailler avec des graphes non représentés à l'écran
    Imaginons par exemple qu'on doive générer 1000 permutations de graphes pour tester des
    combinaisons, on ne souhaite pas représenter graphiquement ces 1000 graphes, et les
    interfaces pèsent lourd en ressource, avec cette organisation on est libre de réserver ou
    pas une interface de présentation associée aux datas (découplage données/interface)

***********************************************************************************************/

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <deque>
#include <utility>
#include <fstream>
#include <stack>
#include <bitset>

#include "grman/grman.h"
#include "grman/widget.h"
#include "const.h"
#include "basics.h"

/* **************************************************
                    VERTEX
****************************************************/

/// L'interface d'un sommet
class VertexInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Vertex;
    friend class EdgeInterface;
    friend class Graph;
    friend class Fenetre;
    friend class Select;
    friend class RGraph;


    private :

        // Les widgets de l'interface.
        //N'oubliez pas qu'il ne suffit pas de déclarer
        // ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        // le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        /// La boite qui blanche en dessous
        grman::WidgetBox m_down_box;

        /// Un label de visualisation de la valeur du sommet
        grman::WidgetText m_label_value;

        /// Une image de "remplissage"
        grman::WidgetImage m_img;

        /// Un label indiquant l'index du sommet
        grman::WidgetText m_label_idx;

        /// Un slider pour regler la valeur
        grman::WidgetVSlider m_slider;

        /// Les marques a droite
        grman::WidgetBox m_marque[8];

    public :

        /// Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        VertexInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};

/// La classe representant un sommet
class Vertex
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Graph;
    friend class VertexInterface;
    friend class Edge;
    friend class EdgeInterface;
    friend class Fenetre;
    friend class Select;
    friend class RGraph;

    private :
        /// liste des indices des arcs arrivant au sommet : accès aux prédécesseurs
        std::vector<int> m_in;

        /// liste des indices des arcs partant du sommet : accès aux successeurs
        std::vector<int> m_out;

        /// un exemple de donnée associée à l'arc, on peut en ajouter d'autres...
        double m_value;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<VertexInterface> m_interface = nullptr;



        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne précédente est en gros équivalent à la ligne suivante :
        // VertexInterface * m_interface = nullptr;


    public:

        /// Le constructeur
        Vertex (double value=0, VertexInterface *interface=nullptr) :
            m_value(value), m_interface(interface)  {  }

        /// Renvoit un sommet sans interface
        Vertex for_study() {Vertex out(m_value); out.m_in = m_in; out.m_out = m_out; return out;}

        /// L'update avant la mise a jour
        void pre_update();

        /// L'update apres la mise a jour
        void post_update();
};



/* **************************************************
                    EDGE
****************************************************/
/// L'interface d'une arrete
class EdgeInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Edge;
    friend class Graph;
    friend class Select;
    friend class RGraph;

    private :

        // Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        // ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        // le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        /// Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

        /// La boite qui contient le text
        grman::WidgetBox m_box_weight;

        /// Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_weight;

    public :

        /// Le constructeur met en place les éléments de l'interface
        EdgeInterface(Vertex& from, Vertex& to);
};

/// La classe representant une arrete
class Edge
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Graph;
    friend class EdgeInterface;
    friend class Select;
    friend class Fenetre;
    friend class RGraph;

    private :
        /// indice du sommet de départ de l'arc
        int m_from;

        /// indice du sommet d'arrivée de l'arc
        int m_to;

        /// un exemple de donnée associée à l'arc, on peut en ajouter d'autres...
        double m_weight;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<EdgeInterface> m_interface = nullptr;


    public:

        /// Le constructeur
        Edge (double weight=0, EdgeInterface *interface=nullptr) :
            m_weight(weight), m_interface(interface)  {  }

        /// Renvoit une arrete sant interface
        Edge for_study() {Edge out(m_weight); out.m_from = m_from; out.m_to = m_to; return out;}

        /// L'update avant la mise a jour
        void pre_update();

        /// L'update apres la mise a jour
        void post_update();
};




/* **************************************************
                    GRAPH & Co
****************************************************/

/// La classe representant le sommet selectionnée
class Select
{
    // Vertex = 1, Edge = 2
    /// la liste de travail
    std::deque<std::pair<int, int>> m_file;

    /// le dernier element selectionné
    std::pair<int, int> m_last;

    /// Reference sur la map de sommet du graphe
    std::map<int, Vertex> & m_mapVertex;

    /// Reference sur la map d'arret du graphe
    std::map<int, Edge> & m_mapEdge;

 public:

    /// le constructeur
    Select(std::map<int, Vertex> & mapVertex, std::map<int, Edge> & mapEdge) : m_file(), m_mapVertex(mapVertex), m_mapEdge(mapEdge) {m_file.push_back(std::pair<int, int>(-1, -1));}

    /// Si un element est selectionné
    bool st_selected() {return m_file.front() != std::pair<int, int>(-1, -1) && !m_mapVertex.empty();}

    /// Si l'element selectionné est un sommet
    bool is_vertex_selected() {return st_selected() && m_file.front().first == 1;}

    /// Si l'element selectionné est une arrete
    bool is_edge_selected() {return st_selected() && m_file.front().first == 2;}

    /// L'id du sommet selectionné
    int vertex_selected() {return is_vertex_selected() ? m_file.front().second : -1;}

    /// L'id de l'arrete selectionné
    int edge_selected() {return is_edge_selected() ? m_file.front().second : -1;}

    /// Si l'element selectionné est different du precedent
    bool is_different() {return m_last != m_file.front();}

    /// Ajout d'un sommet a la liste
    void add_vertex(int id);

    /// Ajout d'une arret a la liste
    void add_edge(int id);

    /// Le traitement de la liste
    void work();

    /// La deselection d'un elemnt
    void unselect();

    /// Remise a zero de la liste
    void clear();

};

/// l'interface du graphe
class GraphInterface
{
    friend class Graph;

    private :

        // Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        // ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        // le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        // Dans cette boite seront ajoutés les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;


        // A compléter éventuellement par des widgets de décoration ou
        // d'édition (boutons ajouter/enlever ...)

    public :

        /// Le constructeur
        GraphInterface(int x, int y, int w, int h);
};

/// La classe representant le graphe
class Graph
{
    friend class Fenetre;
    friend class RGraph;

    private :

        /// La "liste" des arêtes
        std::map<int, Edge> m_edges;

        /// La liste des sommets
        std::map<int, Vertex> m_vertices;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<GraphInterface> m_interface = nullptr;

        /// La classe ou sont stockés les éléments selectionnés
        Select m_select;


    public:

        /// Le constructeur par default
        Graph (GraphInterface *interface=nullptr) :
            m_interface(interface), m_select(m_vertices, m_edges)  {  }

        /// Le constructeur par copie
        Graph (Graph const & other);

        /// Permet d'ajouter un sommet a afficher
        void add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name="", int pic_idx=0 );

        /// Permet d'ajouter une arrete a afficher
        void add_interfaced_edge(int idx, int vert1, int vert2, double weight=0);

        /// La methode example
        void make_example();

        /// Charge un graphe depuis un fichier
        void ChargerGraphe(std::string fic, int x, int y, int w, int h);

        /// Sauvegarde le graphe dans un fichier
        void SauverGraphe(std::string fic1);

        /// Renvoit un matrice d'adjacence
        std::map<int, std::map<int, bool>> matrice_adj();

        /// La forte connexité pour une composante
        std::map<int, int> once_Sconnexe(std::map<int, std::map<int, bool>> adjacence, int s);

        /// La forte connexité du graphe
        std::vector<std::vector<int>> Sconnexe();

        /// Renvoie si le graphe est connexe
        bool connexe();

        /// Renvoit les composantes k-connee
        std::vector<std::vector<int>> kconnexe();

        /// Permet de supprimer un sommet
        void delete_vertex(int idx);

        /// Permet de supprimer une arrete
        void delete_edge(int idx);

        /// Permet de supprimer le contenu du graphe
        void close_graphe();

        /// La mise a jour dans le cas fonctionnel
        void update_time(double r = 2000, double pred = 5000, double proi = 1, double speed = 1);


        /// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
        void update();
};


#endif // GRAPH_H_INCLUDED
