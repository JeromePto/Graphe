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
    m_save_button.set_pos(m_load_button.get_posx(), m_load_button.get_posy() + 25);
    m_save_button.set_dim(80, 20);
    m_save_button.set_bg_color(GRISCLAIR);

    m_save_button.add_child(m_save_button_label);
    m_save_button_label.set_message("SAVE");

    m_top_box.add_child(m_close_button);
    m_close_button.set_pos(m_load_button.get_posx(), m_load_button.get_posy() + 50);
    m_close_button.set_dim(80, 20);
    m_close_button.set_bg_color(GRISCLAIR);

    m_close_button.add_child(m_close_button_label);
    m_close_button_label.set_message("CLOSE");

    m_top_box.add_child(m_load_file);
    m_load_file.set_pos(m_load_button.get_posx()+90, m_load_button.get_posy()+ 10);
    m_load_file.set_dim(150, 20);
    m_load_file.set_bg_color(SABLECLAIR);
    m_load_file.set_edit_color(JAUNECLAIR);

    m_top_box.add_child(m_move_button);
    m_move_button.set_pos(m_load_button.get_posx()+90, m_load_button.get_posy()+40);
    m_move_button.set_dim(80, 20);
    m_move_button.set_bg_color(GRISCLAIR);

    m_move_button.add_child(m_move_button_label);
    m_move_button_label.set_message("MOVE");

    m_top_box.add_child(m_edit_button);
    m_edit_button.set_pos(m_move_button.get_posx()+90, m_move_button.get_posy());
    m_edit_button.set_dim(80, 20);
    m_edit_button.set_bg_color(GRISCLAIR);

    m_edit_button.add_child(m_edit_button_label);
    m_edit_button_label.set_message("EDIT");


    m_top_box.add_child(m_mode_box);
    m_mode_box.set_gravity_y(grman::GravityY::Up);
    m_mode_box.set_posx(300);
    m_mode_box.set_dim(260, 20);
    m_mode_box.set_border(0);

    m_mode_box.add_child(m_button_structurel);
    m_button_structurel.set_gravity_x(grman::GravityX::Left);
    m_button_structurel.set_dim(128, 20);
    m_button_structurel.set_bg_color(ROSECLAIR);
    m_button_structurel.set_switch(true);

    m_button_structurel.add_child(m_button_structurel_label);
    m_button_structurel_label.set_message("Structurels");

    m_mode_box.add_child(m_button_fonctionnel);
    m_button_fonctionnel.set_gravity_x(grman::GravityX::Right);
    m_button_fonctionnel.set_dim(128, 20);
    m_button_fonctionnel.set_bg_color(GRISCLAIR);

    m_button_fonctionnel.add_child(m_button_fonctionnel_label);
    m_button_fonctionnel_label.set_message("Fonctionnels");


    m_top_box.add_child(m_delete_button);
    m_delete_button.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_delete_button.set_dim(80, 20);
    m_delete_button.set_bg_color(GRISCLAIR);
    m_delete_button.set_tmp_pos();

    m_delete_button.add_child(m_delete_button_label);
    m_delete_button_label.set_message("DELETE");

    m_top_box.add_child(m_struct_box);
    m_struct_box.set_pos(600, 0);
    m_struct_box.set_dim(300, 70);
    //m_struct_box.set_border(0);
    m_struct_box.set_padding(0);
    m_struct_box.set_tmp_pos();

    m_struct_box.add_child(m_connexe_button);
    m_connexe_button.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_connexe_button.set_dim(130, 20);
    m_connexe_button.set_bg_color(GRISCLAIR);
    m_connexe_button.set_text("FORTE CONNEXITE");

    m_struct_box.add_child(m_connexe_label);
    m_connexe_label.set_pos(m_connexe_button.get_posx()+150, m_connexe_button.get_posy()+7);
    m_connexe_label.set_message("12");

    m_struct_box.add_child(m_connexe_display);
    m_connexe_display.set_pos(m_connexe_button.get_posx()+190, m_connexe_button.get_posy());
    m_connexe_display.set_dim(100, 20);
    m_connexe_display.set_bg_color(GRISCLAIR);
    m_connexe_display.set_text("DISPLAY");

    m_struct_box.add_child(m_kconnexe_button);
    m_kconnexe_button.set_pos(m_connexe_button.get_posx(), m_connexe_button.get_posy()+25);
    m_kconnexe_button.set_dim(130, 20);
    m_kconnexe_button.set_bg_color(GRISCLAIR);
    m_kconnexe_button.set_text("K-CONNEXITE");

    m_struct_box.add_child(m_kconnexe_label);
    m_kconnexe_label.set_pos(m_kconnexe_button.get_posx()+150, m_kconnexe_button.get_posy()+7);
    m_kconnexe_label.set_message("12");

    m_struct_box.add_child(m_kconnexe_display);
    m_kconnexe_display.set_pos(m_kconnexe_button.get_posx()+190, m_kconnexe_button.get_posy());
    m_kconnexe_display.set_dim(100, 20);
    m_kconnexe_display.set_bg_color(GRISCLAIR);
    m_kconnexe_display.set_text("DISPLAY");

}

void Fenetre::update()
{
    if (!m_interface)
            return;

    m_graphe.update();
    m_interface->m_top_box.update();

    if(m_interface->m_load_button.clicked())
    {
        m_graphe.ChargerGraphe(m_interface->m_load_file.get_message(), 0, TAILLE_BAR, LARGEUR_FENETRE, HAUTEUR_FENETRE - TAILLE_BAR);
        m_interface->m_load_file.leave_edition();
        m_interface->m_load_file.clear_message();
    }

    if(m_interface->m_save_button.clicked())
    {
        m_graphe.SauverGraphe(m_interface->m_load_file.get_message());
        m_interface->m_load_file.leave_edition();
        m_interface->m_load_file.clear_message();
    }

    if(m_interface->m_close_button.clicked())
    {
        m_graphe.m_select.unselect();
        m_graphe.close_graphe();
        m_interface->m_button_structurel.set_switch(true);
        m_interface->m_button_structurel.set_bg_color(ROSECLAIR);
        m_interface->m_button_fonctionnel.set_switch(false);
        m_interface->m_button_fonctionnel.set_bg_color(GRISCLAIR);
        m_mode = 1;
    }

    if(m_interface->m_button_structurel.switching())
    {
        if(m_interface->m_button_structurel.get_switch())
        {
            m_interface->m_button_structurel.set_bg_color(ROSECLAIR);
            m_interface->m_button_fonctionnel.set_switch(false);
            m_interface->m_button_fonctionnel.set_bg_color(GRISCLAIR);
            m_mode = 1;
        }
        else
        {
            m_interface->m_button_structurel.set_switch(true);
        }
    }
    else if(m_interface->m_button_fonctionnel.switching())
    {
        if(m_interface->m_button_fonctionnel.get_switch())
        {
            m_interface->m_button_fonctionnel.set_bg_color(ROSECLAIR);
            m_interface->m_button_structurel.set_switch(false);
            m_interface->m_button_structurel.set_bg_color(GRISCLAIR);
            m_mode = 2;
        }
        else
        {
            m_interface->m_button_fonctionnel.set_switch(true);
        }
    }

    update_edit_button();

    if(m_graphe.m_select.st_selected())
    {
        m_interface->m_delete_button.back_tmp_pos();

        if(m_graphe.m_select.is_vertex_selected())
        {
            if(m_interface->m_delete_button.clicked())
            {
                m_graphe.delete_vertex(m_graphe.m_select.vertex_selected());
            }
        }
        else if(m_graphe.m_select.is_edge_selected())
        {
            if(m_interface->m_delete_button.clicked())
            {
                m_graphe.delete_edge(m_graphe.m_select.edge_selected());
            }
        }
    }
    else
    {
        m_interface->m_delete_button.set_pos(2000, 2000);
    }

    update_struct();
}

void Fenetre::update_struct()
{
    if(m_mode == 1)
    {
        m_interface->m_struct_box.back_tmp_pos();
    }
    else
    {
        m_interface->m_struct_box.set_pos(2000, 2000);
    }
}

void Fenetre::update_edit_button()
{
    if(m_interface->m_move_button.switching())
    {
        if(m_interface->m_move_button.get_switch())
        {
            m_interface->m_move_button.set_bg_color(BLEUCLAIR);
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

    if(m_interface->m_edit_button.switching())
    {
        if(m_interface->m_edit_button.get_switch())
        {
            m_interface->m_edit_button.set_bg_color(BLEUCLAIR);
            m_interface->m_move_button.set_switch(false);
        }
        else
        {
            m_interface->m_edit_button.set_bg_color(GRISCLAIR);
        }
    }

    if(m_interface->m_move_button.switching() || m_interface->m_edit_button.switching())
    {

    }
}
