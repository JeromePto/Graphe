#include "graph.h"

/* **************************************************
                    VERTEX
****************************************************/

// Le constructeur met en place les �l�ments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(TAILLE_IMAGE + 20, TAILLE_IMAGE + HAUTEUR_BAR_IMAGE);
    m_top_box.set_lock_focus(true);
    m_top_box.set_padding(0);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
        m_img.set_padding(0);
        m_img.set_margin(0);
    }

    m_top_box.add_child(m_down_box);
    m_down_box.set_dim(m_top_box.get_dimx()-6-20, HAUTEUR_BAR_IMAGE);
    m_down_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_down_box.set_bg_color(BLANC);
    m_down_box.set_padding(0);
    m_down_box.set_margin(0);
    m_down_box.set_border(0);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_label_value.set_posx(m_label_value.get_posx() - 45);
    m_label_value.set_margin(3);


    m_top_box.add_child( m_label_idx );
    m_label_idx.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);
    m_label_idx.set_posx(m_label_idx.get_posx() + 30);
    m_label_idx.set_margin(3);
    m_label_idx.set_message( std::to_string(idx) );

    m_top_box.add_child(m_slider);
    m_slider.set_padding(0);
    m_slider.set_margin(0);
    m_slider.set_dim(20, m_top_box.get_dimy());
    m_slider.set_gravity_x(grman::GravityX::Left);
    m_slider.set_range(0.0 , 100.0);
    m_slider.set_lim_max(false);

    for(int i = 0 ; i < 8 ; ++i)
    {
        m_top_box.add_child(m_marque[i]);
        m_marque[i].set_border(0);
        m_marque[i].set_margin(0);
        m_marque[i].set_padding(0);
        m_marque[i].set_pos(102, 10*i);
        m_marque[i].set_dim(10, 10);
        m_marque[i].set_bg_color(-1);
    }
}


// Gestion du Vertex avant l'appel � l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    // Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_slider.set_value(m_value);
    m_interface->m_label_value.set_message( toString(m_value) );
}


// Gestion du Vertex apr�s l'appel � l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    m_value = m_interface->m_slider.get_value();
}



/* **************************************************
                    EDGE
****************************************************/

// Le constructeur met en place les �l�ments de l'interface
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


// Gestion du Edge avant l'appel � l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    // Copier la valeur locale de la donn�e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( toString( m_weight ) );
}

// Gestion du Edge apr�s l'appel � l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;
}



/* **************************************************
                    GRAPH & Co
****************************************************/

void Select::add_vertex(int id)
{
    m_file.push_back(std::pair<int, int>(1, id));
}

void Select::add_edge(int id)
{
    m_file.push_back(std::pair<int, int>(2, id));
}

void Select::work()
{
//    std::cout << m_file.size() << " ! " << m_last.first << " " << m_last.second << " : ";
//    for(auto it : m_file) std::cout << it.first << " " << it.second << " . ";
    m_last = m_file.front();
    if(m_file.size() > 1 && !m_mapVertex.empty())
    {

        m_file.pop_front();

        while(m_file.size() > 1)
        {
            if(m_last.first == 1 && m_mapVertex[m_last.second].m_interface->m_top_box.is_selected())
            {
                m_mapVertex[m_last.second].m_interface->m_top_box.set_selected(false);
            }
            else if(m_last.first == 2 && m_mapEdge[m_last.second].m_interface->m_top_edge.is_selected())
            {
                m_mapEdge[m_last.second].m_interface->m_top_edge.set_selected(false);
            }
            if(m_file.front() == m_last)
            {
                m_file.pop_front();
            }
            else
            {
                while(m_file.size() > 1)
                {
                    if(m_file.back() != m_last && m_file.back() != m_file.front())
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
    m_file.push_back(m_file.front());
    m_file.push_back(std::pair<int, int>(-1, -1));

}

void Select::clear()
{
    m_file.clear();
    m_file.push_back(std::pair<int, int>(-1, -1));
}

// Ici le constructeur se contente de pr�parer un cadre d'accueil des
// �l�ments qui seront ensuite ajout�s lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_main_box.set_dim(w, h);
    m_main_box.set_gravity_y(grman::GravityY::Down);
    m_main_box.set_bg_color(BLANCJAUNE);
    m_main_box.set_lock_focus(true);
}

Graph::Graph (Graph const & other)
    :m_edges(), m_vertices(), m_select(m_vertices, m_edges)
{
    for(auto it : other.m_vertices)
    {
        m_vertices[it.first] = it.second.for_study();
    }
    for(auto it : other.m_edges)
    {
        m_edges[it.first] = it.second.for_study();
    }
}

// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
// Cette m�thode est � enlever et remplacer par un syst�me
// de chargement de fichiers par exemple.
// Bien s�r on ne veut pas que vos graphes soient construits
// "� la main" dans le code comme �a.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(0, TAILLE_BAR, LARGEUR_FENETRE, HAUTEUR_FENETRE - TAILLE_BAR);
    // La ligne pr�c�dente est en gros �quivalente � :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    // Les sommets doivent �tre d�finis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    // Les arcs doivent �tre d�finis entre des sommets qui existent !
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
    // La ligne pr�c�dente est en gros �quivalente � :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    std::ifstream fichier(fic.c_str());
    int nombreS, nombreA;
    double value;
    int a, b, idvalue;
    std::string image;
    int sommet1, sommet2;
    double poids;
    int id;

    if(fichier)
    {
        fichier >> nombreS;
        for (int i=0; i < nombreS; i++)
        {
            fichier >> id >> value >> a >> b >> image>> idvalue;
            add_interfaced_vertex(id, value, a, b, image, idvalue);

        }

        fichier >> nombreA;
        for (int j=0; j<nombreA; j++)
        {
            fichier >> id >> sommet1 >> sommet2 >> poids;
            add_interfaced_edge(id,sommet1,sommet2,poids);
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
            fichier << e.first << " " << e.second.m_value << " " << e.second.m_interface->m_top_box.get_posx() << " " << e.second.m_interface->m_top_box.get_posy() << " "
                    << e.second.m_interface->m_img.get_pic_name() << " " << e.second.m_interface->m_img.get_pic_idx() << std::endl;
        }
        fichier << m_edges.size() << std::endl;
        for (auto &e : m_edges)
        {
            fichier << e.first << " " << e.second.m_from << " " << e.second.m_to << " " << e.second.m_weight << std::endl;
        }
    }
}

std::map<int, std::map<int, bool>> Graph::matrice_adj()
{
    std::map<int, std::map<int, bool>> out;

//    for(unsigned i = 0 ; i < m_vertices.size() ; ++i)
//    {
//        out.push_back(std::vector<bool>());
//        for(unsigned j = 0 ; j < m_vertices.size() ; ++j)
//        {
//            out[i].push_back(false);
//        }
//    }

    for(auto it : m_edges)
    {
        out[it.second.m_from][it.second.m_to] = true;
    }

    return out;
}

std::map<int, int> Graph::once_Sconnexe(std::map<int, std::map<int, bool>> adjacence, int s)
{
    std::map<int, int> c1, c2, c, marques;
    std::vector<int> x;
    std::vector<int> y;
    int ajoute = 1;

    for(auto it : m_vertices)
    {
        x.push_back(it.first);
        y.push_back(it.first);
        c1[it.first] = 0;
        c2[it.first] = 0;
        c[it.first] = 0;
    }

    c1[s] = 1;
    c2[s] = 1;

    while(ajoute)
    {
        ajoute = 0;
        for(auto itx : x)
        {
            if(!marques.count(itx) && c1.at(itx))
            {
                marques[itx] = 1;
                for(auto ity : y)
                {
                    if(adjacence[itx][ity] && !marques.count(ity))
                    {
                        c1[ity] = 1;
                        ajoute = 1;
                    }
                }
            }
        }
    }


    marques.clear();

    ajoute = 1;
    while(ajoute)
    {
        ajoute = 0;
        for(auto itx : x)
        {
            if(!marques.count(itx) && c2.at(itx))
            {
                marques[itx] = 1;
                for(auto ity : y)
                {
                    if(adjacence[ity][itx] && !marques.count(ity))
                    {
                        c2[ity] = 1;
                        ajoute = 1;
                    }
                }
            }
        }
    }

    for(auto it : m_vertices)
    {
        c[it.first] = c1[it.first] & c2[it.first];
    }

    return c;
}

std::vector<std::vector<int>> Graph::Sconnexe()
{
    if(m_vertices.empty() || !connexe()) return std::vector<std::vector<int>>();

    std::map<int, std::map<int, bool>> adjacence = matrice_adj();
    std::map<int, std::map<int, int>> tabc;
    std::map<int, bool> marques;
    std::vector<int> x;
    std::vector<int> y;
    unsigned tmp = 0;
    std::vector<std::vector<int>> out;
    std::vector<std::pair<int, int>> aDel;

    for(auto it : m_vertices)
    {
        x.push_back(it.first);
        y.push_back(it.first);
    }

    for(auto itx : x)
    {
        if(!marques.count(itx))
        {
            tabc[itx] = once_Sconnexe(adjacence, itx);
            marques[itx] = 1;
            for(auto ity : y)
            {
                if(tabc[itx][ity] && !marques.count(ity))
                    marques[ity] = 1;
            }
        }
    }

    for(auto it = tabc.begin() ; it != tabc.end() ; ++it)
    {
        tmp = 0;
        for(auto it2 : it->second)
            if(it2.second == 1) tmp++;

        if(tmp <= 1)
        {
            aDel.push_back({it->first, -1});
        }
        else
        {
            for(auto it2 = it->second.begin() ; it2 != it->second.end() ; ++it2)
            {
                if(it2->second == 1)
                {
                    it2->second = it2->first;
                }
                else if(it2->second == 0)
                {
                    aDel.push_back({it->first, it2->first});
                }
            }
        }
    }
    for(auto it : aDel)
    {
        if(it.second == -1)
            tabc.erase(it.first);
        else
        {
            tabc.at(it.first).erase(it.second);
        }
    }
    for(auto iti : tabc)
    {
        out.push_back(std::vector<int>());
        for(auto itj : iti.second)
        {
            out.back().push_back(itj.second);
        }
    }

    return out;
}

bool Graph::connexe()
{
    if(m_vertices.empty()) return false;

    std::stack<int> pile;
    int s;
    std::map<int, bool> marques;
    std::map<int, std::vector<int>> adjacent;
    bool tmp(false);
    std::vector<int> out;

    for(auto it : m_vertices)
    {
        s = it.first;
        marques[it.first] = false;
        adjacent[it.first] = std::vector<int>();
        tmp = false;
        for(auto it2 : it.second.m_in)
        {
            adjacent.at(it.first).push_back(m_edges.at(it2).m_from);
        }

        for(auto it2 : it.second.m_out)
        {
            for(auto it3 : adjacent.at(it.first))
            {
                if(it3 == m_edges.at(it2).m_to)
                {
                    tmp = true;
                }
            }
            if(!tmp)
                adjacent.at(it.first).push_back(m_edges.at(it2).m_to);
        }
    }

    marques.at(s) = true;
    pile.push(s);

    while(!pile.empty())
    {
        s=pile.top();
        pile.pop();

        for (unsigned a=0; a<adjacent[s].size(); ++a)
        {
            if (!marques.at(adjacent[s][a]))
            {
                marques[adjacent[s][a]] = true;
                pile.push(adjacent[s][a]);
            }
        }
        out.push_back(s);
    }

    return out.size() == m_vertices.size();
}

std::vector<std::vector<int>> Graph::kconnexe()
{
    std::bitset<64> binaire(0);
    unsigned int kmin = 10000;
    int pos;
    unsigned int nb_tour = puis(2, m_vertices.size());
    std::vector<std::vector<int>> out;
    std::vector<int> aDel;

    for(unsigned int i = 0 ; i < nb_tour ; ++i)
    {
        Graph etude(*this);
        pos = 0;
        binaire = binaire.to_ulong() + 1;
        aDel.clear();
        for(auto it2 : etude.m_vertices)
        {
            if(binaire[pos])
            {
                aDel.push_back(it2.first);
            }
            pos++;
        }
        for(auto it2 : aDel)
        {
            etude.delete_vertex(it2);
        }

        if(!etude.connexe() && (m_vertices.size() - etude.m_vertices.size()) < kmin)
        {
            kmin = (m_vertices.size() - etude.m_vertices.size());
            out.clear();
            out.push_back(std::vector<int>());
            for(auto it : m_vertices)
            {
                if(!etude.m_vertices.count(it.first))
                {
                    out.back().push_back(it.first);
                }
            }
        }
        else if(!etude.connexe() && (m_vertices.size() - etude.m_vertices.size()) == kmin)
        {
            out.push_back(std::vector<int>());
            for(auto it : m_vertices)
            {
                if(!etude.m_vertices.count(it.first))
                {
                    out.back().push_back(it.first);
                }
            }
        }
    }

    return out;
}

void Graph::delete_vertex(int idx)
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

void Graph::delete_edge(int eidx)
{
    // r�f�rence vers le Edge � enlever
    Edge &remed=m_edges.at(eidx);

    //std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    // Tester la coh�rence : nombre d'arc entrants et sortants des sommets 1 et 2
    //std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    //std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    //std::cout << m_edges.size() << std::endl;

    // test : on a bien des �l�ments interfac�s
    if (m_interface && remed.m_interface)
    {
    // Ne pas oublier qu'on a fait �a � l'ajout de l'arc :
    /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
    /* m_interface->m_main_box.add_child(ei->m_top_edge); */
    /* m_edges[idx] = Edge(weight, ei); */
    // Le new EdgeInterface ne n�cessite pas de delete car on a un shared_ptr
    // Le Edge ne n�cessite pas non plus de delete car on n'a pas fait de new (s�mantique par valeur)
    // mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
    m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    // Il reste encore � virer l'arc supprim� de la liste des entrants et sortants des 2 sommets to et from !
    // References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    // Le Edge ne n�cessite pas non plus de delete car on n'a pas fait de new (s�mantique par valeur)
    // Il suffit donc de supprimer l'entr�e de la map pour supprimer � la fois l'Edge et le EdgeInterface
    // mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );

    // Tester la coh�rence : nombre d'arc entrants et sortants des sommets 1 et 2
    //std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    //std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    //std::cout << m_edges.size() << std::endl;
}

void Graph::close_graphe()
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

void Graph::update_time(double r, double pred, double proi, double speed)
{
    double k, a;
    static double cmp = 1.0;

    cmp += speed;
    while (cmp > 1.0)
    {
        cmp -= 1.0;
        for(auto &it : m_vertices)
        {
            std::cout << it.first << ":";
            k = 1;
            for(auto it2 : it.second.m_in)
            {
                k += (m_edges.at(it2).m_weight) / proi * m_vertices.at(m_edges.at(it2).m_from).m_value;
            }
            std::cout << " a = " << it.second.m_value;
            std::cout << "\tk : " << k;
            std::cout << "\tn/k : " << (it.second.m_value / k);
            a = it.second.m_value + (1/r) * it.second.m_value * (1.0 - (it.second.m_value / k));
            std::cout << "\ta pos : " << a;
            for(auto it2 : it.second.m_out)
            {
                a = a - (m_edges.at(it2).m_weight) / pred * m_vertices.at(m_edges.at(it2).m_to).m_value;
            }
            std::cout << "\ta : " << a << std::endl;
            a > 0 ? it.second.m_value = a : it.second.m_value = 0;
        }
        std::cout << std::endl;
    }
}

// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
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
            m_select.add_vertex(elt.first);
        }
    }

    for (auto &elt : m_edges)
    {
        elt.second.post_update();
        if(elt.second.m_interface->m_top_edge.is_selected())
        {
            m_select.add_edge(elt.first);
        }
    }

    m_select.work();
}

// Aide � l'ajout de sommets interfac�s
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

// Aide � l'ajout d'arcs interfac�s
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
    m_vertices[id_vert2].m_in.push_back(idx);

}

