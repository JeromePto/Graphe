#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(100, 120);
    m_top_box.set_lock_focus(true);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_y(grman::GravityY::Up);
    }

    m_top_box.add_child(m_down_box);
    m_down_box.set_dim(100, 20);
    m_down_box.set_gravity_y(grman::GravityY::Down);
    m_down_box.set_bg_color(BLANC);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_label_value.set_margin(4);


    m_top_box.add_child( m_label_idx );
    m_label_idx.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);
    m_label_idx.set_margin(4);
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel � l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex apr�s l'appel � l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    m_top_edge.add_child(m_box_weight);
    m_box_weight.set_dim(24, 12);

    // Label de visualisation de valeur
    m_box_weight.add_child(m_label_weight);
    m_label_weight.set_dim(24, 12);
    m_label_weight.set_bg_color(BLANC);

    m_top_edge.set_lock_focus(true);

}


/// Gestion du Edge avant l'appel � l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge apr�s l'appel � l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;
}



/***************************************************
                    GRAPH & Co
****************************************************/

void Select::add_vertex(int id, Vertex & vertex)
{
    m_file.push_back(std::pair<int, int>(1, id));
}

void Select::add_edge(int id, Edge & edge)
{
    m_file.push_back(std::pair<int, int>(2, id));
}

void Select::work(std::map<int, Vertex> mapVertex, std::map<int, Edge> mapEdge)
{
    if(m_file.size() > 1)
    {
        std::pair<int,int> tmp = m_file.front();
        m_file.pop_front();

        while(m_file.size() > 1)
        {
            if(tmp.first == 1 && mapVertex[tmp.second].m_interface->m_top_box.is_selected())
            {
                mapVertex[tmp.second].m_interface->m_top_box.set_selected(false);
            }
            else if(tmp.first == 2 && mapEdge[tmp.second].m_interface->m_top_edge.is_selected())
            {
                mapEdge[tmp.second].m_interface->m_top_edge.set_selected(false);
            }
            if(m_file.front() == tmp)
            {
                m_file.pop_front();
            }
            else
            {
                while(m_file.size() > 1)
                {
                    if(m_file.back() != tmp && m_file.back() != m_file.front())
                    {
                        if(m_file.back().first == 1 && mapVertex[m_file.back().second].m_interface->m_top_box.is_selected())
                        {
                            mapVertex[m_file.back().second].m_interface->m_top_box.set_selected(false);
                        }
                        else if(m_file.back().first == 2 && mapEdge[m_file.back().second].m_interface->m_top_edge.is_selected())
                        {
                            mapEdge[m_file.back().second].m_interface->m_top_edge.set_selected(false);
                        }
                    }
                    m_file.pop_back();
                }
            }
        }
    }
}

/// Ici le constructeur se contente de pr�parer un cadre d'accueil des
/// �l�ments qui seront ensuite ajout�s lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(w, h);
    m_top_box.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(w, h);
    m_main_box.set_bg_color(BLANCJAUNE);
}

/// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
/// Cette m�thode est � enlever et remplacer par un syst�me
/// de chargement de fichiers par exemple.
/// Bien s�r on ne veut pas que vos graphes soient construits
/// "� la main" dans le code comme �a.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(0, TAILLE_BAR, LARGEUR_FENETRE, HAUTEUR_FENETRE - TAILLE_BAR);
    // La ligne pr�c�dente est en gros �quivalente � :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent �tre d�finis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent �tre d�finis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
}

void Graph::delete_vertex(int idx)
{
    std::vector<int> aDel;
    for(auto it = m_edges.begin() ; it != m_edges.end() ; ++it)
    {
        //std::cout << it->second.m_from << " " << it->second.m_to << std::endl;
        if(it->second.m_from == idx || it->second.m_to == idx)
        {
            aDel.push_back(it->first);
        }
    }
    for(auto it : aDel)
    {
        m_interface->m_main_box.remove_child(m_edges[it].m_interface->m_top_edge);
        m_edges.erase(it);
    }

    m_interface->m_main_box.remove_child(m_vertices[idx].m_interface->m_top_box);
    m_vertices.erase(idx);
}

void Graph::delete_edge(int idx)
{
    m_interface->m_main_box.remove_child(m_edges[idx].m_interface->m_top_edge);
    m_edges.erase(idx);
}

/// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
    {
        elt.second.post_update();
        if(elt.second.m_interface->m_top_box.is_selected())
        {
            m_select.add_vertex(elt.first, elt.second);
        }
    }

    for (auto &elt : m_edges)
    {
        elt.second.post_update();
        if(elt.second.m_interface->m_top_edge.is_selected())
        {
            m_select.add_edge(elt.first, elt.second);
        }
    }

    m_select.work(m_vertices, m_edges);
}

/// Aide � l'ajout de sommets interfac�s
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Cr�ation d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide � l'ajout d'arcs interfac�s
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(id_vert1, id_vert2, weight, ei);
}

