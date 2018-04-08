#include "rgraph.h"

RVertexInterface::RVertexInterface(int idx, int x, int y)
{
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(TAILLE_IMAGE + 20, TAILLE_IMAGE + HAUTEUR_BAR_IMAGE);
    m_top_box.set_bg_color(BLANC);
    //m_top_box.set_lock_focus(true);
    m_top_box.set_padding(0);

    m_top_box.add_child( m_label_idx );
    //m_label_idx.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);
    //m_label_idx.set_posx(m_label_idx.get_posx() + 30);
    //m_label_idx.set_margin(3);
    m_label_idx.set_message( std::to_string(idx) );
}


REdgeInterface::REdgeInterface(RVertex& from, RVertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating REdgeInterface between vertices having no interface" << std::endl;
        throw "Bad REdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();
}


RGraphInterface::RGraphInterface(int x, int y, int w, int h)
{
    m_main_box.set_dim(w, h);
    m_main_box.set_gravity_y(grman::GravityY::Down);
    m_main_box.set_bg_color(BLANCJAUNE);
    //m_main_box.set_lock_focus(true);
}


/* **************************************************
                    GRAPH
****************************************************/

int RGraph::equiVertex(int a)
{
    for(auto it : m_vertices)
    {
        for(auto it2 : it.second.m_equi)
        {
            if(a == it2)
                return it.first;
        }
    }
    return -1;
}

void RGraph::create(Graph const& other, std::vector<std::vector<int>> Sconnexe_vertex)
{
    std::vector<std::pair<int, int>> aAdd;

    m_interface = std::make_shared<RGraphInterface>(0, TAILLE_BAR, LARGEUR_FENETRE, HAUTEUR_FENETRE - TAILLE_BAR);
    for(auto it : other.m_vertices)
    {
        add_interfaced_vertex(it.first, it.second.m_interface->m_top_box.get_posx(), it.second.m_interface->m_top_box.get_posy());
    }
    for(auto it : Sconnexe_vertex)
    {
        for(auto it2 = it.begin()+1 ; it2 != it.end() ; ++it2)
        {
            delete_vertex(*it2);
            m_vertices.at(it.at(0)).m_equi.push_back(*it2);
        }
    }

    for(auto it : m_vertices)
    {
        std::string aff;
        for(auto it2 : it.second.m_equi)
        {
            aff += std::to_string(it2);
            aff += " ";
        }
        aff.pop_back();
        it.second.m_interface->m_label_idx.set_message(aff);
    }

    for(auto it : other.m_edges)
    {
        if(equiVertex(it.second.m_from) != equiVertex(it.second.m_to))
        {
            add_interfaced_edge(it.first, equiVertex(it.second.m_from), equiVertex(it.second.m_to));
        }
    }
}

void RGraph::delete_vertex(int idx)
{
    std::vector<int> aDel;
    for(auto it = m_edges.begin() ; it != m_edges.end() ; ++it)
    {
        if(it->second.m_from == idx || it->second.m_to == idx)
        {
            aDel.push_back(it->first);
        }
    }
    for(auto it : aDel)
    {
        delete_edge(it);
    }

    if(m_interface)
        m_interface->m_main_box.remove_child(m_vertices.at(idx).m_interface->m_top_box);

    m_vertices.erase(idx);
}

void RGraph::delete_edge(int eidx)
{
    // référence vers le Edge à enlever
    REdge &remed=m_edges.at(eidx);

    //std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    // Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    //std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    //std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    //std::cout << m_edges.size() << std::endl;

    // test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
    // Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
    /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
    /* m_interface->m_main_box.add_child(ei->m_top_edge); */
    /* m_edges[idx] = Edge(weight, ei); */
    // Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
    // Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    // mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    // Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    // References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    // Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    // Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    // mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );

    // Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    //std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    //std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    //std::cout << m_edges.size() << std::endl;
}

void RGraph::close_graphe()
{
    std::vector<int> aDel;
    for(auto it = m_edges.begin() ; it != m_edges.end() ; ++it)
    {
        aDel.push_back(it->first);
    }
    for(auto it : aDel)
    {
        delete_edge(it);
    }
    aDel.clear();
    for(auto it = m_vertices.begin() ; it != m_vertices.end() ; ++it)
    {
        m_interface->m_main_box.remove_child(m_vertices.at(it->first).m_interface->m_top_box);
        aDel.push_back(it->first);
    }
    for(auto it : aDel)
    {
        m_vertices.erase(it);
    }
    m_interface.reset();

}

// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void RGraph::update()
{
    if (!m_interface)
        return;

    m_interface->m_main_box.update();

}

// Aide à l'ajout de sommets interfacés
void RGraph::add_interfaced_vertex(int idx, int x, int y)
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding Rvertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding Rvertex";
    }
    // Création d'une interface de sommet
    RVertexInterface *vi = new RVertexInterface(idx, x, y);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = RVertex(vi);
    m_vertices[idx].m_equi.push_back(idx);
}

// Aide à l'ajout d'arcs interfacés
void RGraph::add_interfaced_edge(int idx, int id_vert1, int id_vert2)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding Redge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding Redge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding Redge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding Redge";
    }

    REdgeInterface *ei = new REdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = REdge(ei);
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);

}
