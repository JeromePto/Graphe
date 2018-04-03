#include "fenetre.h"

FenetreInterface::FenetreInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(w, h);
    m_top_box.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

    m_top_box.add_child(m_graphe_box);
    m_graphe_box.set_dim(w, h-TAILLE_BAR);
    m_graphe_box.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);

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
}
