#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
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


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
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


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
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

void Select::work()
{
    if(m_file.size() > 1)
    {
        std::pair<int,int> tmp = m_file.front();
        m_file.pop_front();

        while(m_file.size() > 1)
        {
            if(tmp.first == 1 && m_mapVertex[tmp.second].m_interface->m_top_box.is_selected())
            {
                m_mapVertex[tmp.second].m_interface->m_top_box.set_selected(false);
            }
            else if(tmp.first == 2 && m_mapEdge[tmp.second].m_interface->m_top_edge.is_selected())
            {
                m_mapEdge[tmp.second].m_interface->m_top_edge.set_selected(false);
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
                        if(m_file.back().first == 1 && m_mapVertex[m_file.back().second].m_interface->m_top_box.is_selected())
                        {
                            m_mapVertex[m_file.back().second].m_interface->m_top_box.set_selected(false);
                        }
                        else if(m_file.back().first == 2 && m_mapEdge[m_file.back().second].m_interface->m_top_edge.is_selected())
                        {
                            m_mapEdge[m_file.back().second].m_interface->m_top_edge.set_selected(false);
                        }
                    }
                    m_file.pop_back();
                }
            }
        }
    }
}

void Select::unselect()
{
    while(!m_file.empty())
    {
        if(m_file.back().first == 1 && m_mapVertex.count(m_file.back().second) > 0 && m_mapVertex[m_file.back().second].m_interface->m_top_box.is_selected())
        {
            m_mapVertex[m_file.back().second].m_interface->m_top_box.set_selected(false);
        }
        else if(m_file.back().first == 2 && m_mapEdge.count(m_file.back().second) > 0 && m_mapEdge[m_file.back().second].m_interface->m_top_edge.is_selected())
        {
            m_mapEdge[m_file.back().second].m_interface->m_top_edge.set_selected(false);
        }
        m_file.pop_back();
    }
}

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_main_box.set_dim(w, h);
    m_main_box.set_gravity_y(grman::GravityY::Down);
    m_main_box.set_bg_color(BLANCJAUNE);
    m_main_box.set_lock_focus(true);
}

/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(0, TAILLE_BAR, LARGEUR_FENETRE, HAUTEUR_FENETRE - TAILLE_BAR);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
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

void Graph::ChargerGraphe(std::string fic, int x, int y, int w, int h)
{
    m_interface = std::make_shared<GraphInterface>(x, y, w, h);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    std::ifstream fichier(fic.c_str());
    int nombreS, nombreA;
    double value;
    int a, b, idvalue;
    std::string image;
    int sommet1, sommet2;
    double poids;

    if(fichier)
    {
        fichier >> nombreS;
        for (int i=0; i < nombreS; i++)
        {
            fichier >> value >> a >> b >> image>> idvalue;
            add_interfaced_vertex(i, value, a, b, image, idvalue);

        }

        fichier >> nombreA;
        for (int j=0; j<nombreA; j++)
        {
            fichier >> sommet1 >> sommet2 >> poids;
            add_interfaced_edge(j,sommet1,sommet2,poids);
        }
    }
}

void Graph::SauverGraphe(std::string fic1)
{
    std::ofstream fichier(fic1.c_str());
    if (fichier)
    {
        fichier << m_vertices.size() << std::endl;
        for (auto &e : m_vertices)
        {
            fichier << e.second.m_value << " " << e.second.m_interface->m_top_box.get_posx() << " " << e.second.m_interface ->m_top_box.get_posy() << " "
                    << e.second.m_interface->m_img.get_pic_name() << " " << e.second.m_interface->m_img.get_pic_idx() << std::endl;
        }
        fichier << m_edges.size() << std::endl;
        for (auto &e : m_edges)
        {
            fichier << e.second.m_from << " " << e.second.m_to << " " << e.second.m_weight << std::endl;
        }
    }
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
        delete_edge(it);
    }

    m_interface->m_main_box.remove_child(m_vertices[idx].m_interface->m_top_box);
    m_vertices.erase(idx);
}

void Graph::delete_edge(int eidx)
{
    /// référence vers le Edge à enlever
    Edge &remed=m_edges.at(eidx);

    //std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    //std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    //std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    //std::cout << m_edges.size() << std::endl;

    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
    /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
    /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
    /* m_interface->m_main_box.add_child(ei->m_top_edge); */
    /* m_edges[idx] = Edge(weight, ei); */
    /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
    m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    //std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    //std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    //std::cout << m_edges.size() << std::endl;
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_main_box.update();
    if(m_interface->m_main_box.is_selected())
    {
        m_interface->m_main_box.set_selected(false);
        m_select.unselect();
    }

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

    m_select.work();
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
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
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_out.push_back(idx);
}

