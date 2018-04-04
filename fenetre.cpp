#include "fenetre.h"

FenetreInterface::FenetreInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(w, h);
    m_top_box.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

    m_top_box.add_child(m_save_button);
    m_load_button.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_load_button.set_dim(80, 20);
    m_load_button.set_bg_color(GRISCLAIR);

    m_load_button.add_child(m_load_button_label);
    m_load_button_label.set_message("LOAD");

    m_top_box.add_child(m_load_button);
    m_save_button.set_pos(m_load_button.get_posx(), m_load_button.get_posy() + 20);
    m_save_button.set_dim(80, 20);
    m_save_button.set_bg_color(GRISSOMBRE);

    m_save_button.add_child(m_save_button_label);
    m_save_button_label.set_message("SAVE");

    m_top_box.add_child(m_move_button);
    m_move_button.set_pos(m_load_button.get_posx()+90, m_load_button.get_posy());
    m_move_button.set_dim(80, 20);
    m_move_button.set_bg_color(GRISCLAIR);

    m_move_button.add_child(m_move_button_label);
    m_move_button_label.set_message("MOVE");


    m_top_box.add_child(m_delete_button);
    m_delete_button.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_delete_button.set_dim(80, 20);
    m_delete_button.set_bg_color(GRISCLAIR);

    m_delete_button.add_child(m_delete_button_label);
    m_delete_button_label.set_message("DELETE");
}

void Fenetre::update()
{
    if (!m_interface)
            return;

    m_graphe.update();
    m_interface->m_top_box.update();

    if(m_interface->m_load_button.clicked())
    {
        std::cout << "clic" << std::endl;
    }

    if(m_interface->m_move_button.switching())
    {
        std::cout << "ll" << std::endl;
        if(m_interface->m_move_button.get_switch())
        {
            m_interface->m_move_button.set_bg_color(BLEU);
            for(auto it = m_graphe.m_vertices.begin() ; it != m_graphe.m_vertices.end() ; ++it)
            {
                it->second.m_interface->m_top_box.set_moveable(true);
            }
        }
        else
        {
            m_interface->m_move_button.set_bg_color(GRISCLAIR);
            for(auto it = m_graphe.m_vertices.begin() ; it != m_graphe.m_vertices.end() ; ++it)
            {
                it->second.m_interface->m_top_box.set_moveable(false);
            }
        }
    }

    if(m_interface->m_delete_button.clicked())
    {
        std::cout << "del\n";
        m_graphe.delete_vertex(2);
    }
}
