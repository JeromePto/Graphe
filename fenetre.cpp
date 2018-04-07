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
    m_load_file.set_bg_color(JAUNECLAIR);
    m_load_file.set_edit_color(SABLECLAIR);

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

    m_struct_box.add_child(m_kconnexe_display);
    m_kconnexe_display.set_pos(m_kconnexe_button.get_posx()+190, m_kconnexe_button.get_posy());
    m_kconnexe_display.set_dim(100, 20);
    m_kconnexe_display.set_bg_color(GRISCLAIR);
    m_kconnexe_display.set_text("DISPLAY");

}

void Fenetre::close()
{
    m_graphe.m_select.clear();
    m_graphe.close_graphe();
    m_interface->m_button_structurel.set_switch(true);
    m_interface->m_button_structurel.set_bg_color(ROSECLAIR);
    m_interface->m_button_fonctionnel.set_switch(false);
    m_interface->m_button_fonctionnel.set_bg_color(GRISCLAIR);
    m_mode = 1;
    m_interface->m_edit_button.set_switch(false);
    m_interface->m_edit_button.set_bg_color(GRISCLAIR);
    m_edition = false;
    m_string_edit.clear();
    m_interface->m_move_button.set_switch(false);
    m_interface->m_move_button.set_bg_color(GRISCLAIR);
}

void Fenetre::update()
{
    if (!m_interface)
            return;

    m_graphe.update();
    m_interface->m_top_box.update();

    m_last_edition = m_edition;

    update_fixe_button();
    update_edit_button();
    update_selected();
    update_struct();
    update_fonc();
}

void Fenetre::update_fixe_button()
{
    if(m_interface->m_load_button.clicked())
    {
        close();
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
        close();
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
}

void Fenetre::update_struct()
{
    if(m_mode == 1)
    {
        m_interface->m_struct_box.back_tmp_pos();
        if(m_interface->m_connexe_button.clicked())
        {
            std::vector<std::vector<int>> tmp = m_graphe.Sconnexe();
            m_interface->m_connexe_label.set_message(std::to_string(tmp.size()));
            for(unsigned i = 0 ; i < tmp.size() ; i++)
            {
                for(unsigned j = 0 ; j < tmp[i].size() ; j++)
                {
                    std::cout << tmp[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

        if(m_interface->m_kconnexe_button.clicked())
        {
            m_graphe.connexe();
        }
    }
    else
    {
        m_interface->m_struct_box.set_pos(2000, 2000);
    }
}

void Fenetre::update_fonc()
{
    if(m_mode == 2)
    {
       m_graphe.update_time();
    }
    else
    {

    }
}

void Fenetre::update_edit_button()
{
    bool change(false);

    if(m_interface->m_move_button.switching())
    {
        change = true;
        if(m_interface->m_move_button.get_switch())
            m_interface->m_edit_button.set_switch(false);
    }

    if(m_interface->m_edit_button.switching())
    {
        change = true;
        if(m_interface->m_edit_button.get_switch())
            m_interface->m_move_button.set_switch(false);
    }

    if(change)
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

        if(m_interface->m_edit_button.get_switch())
        {
            m_interface->m_edit_button.set_bg_color(BLEUCLAIR);
            m_edition = true;
        }
        else
        {
            m_interface->m_edit_button.set_bg_color(GRISCLAIR);
            m_edition = false;
            m_string_edit.clear();
        }
    }
}

void Fenetre::update_selected()
{
    if(m_graphe.m_select.st_selected())
    {
        if(m_edition)
        {
            std::cout << (char)grman::key_last << " " << (int)grman::key_last << " " << m_string_edit << std::endl;
            switch(grman::key_last)
            {
            case 8:
                if(m_string_edit.size() > 0)
                    m_string_edit.pop_back();
                break;
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case 46:
                m_string_edit += grman::key_last;
                break;
            default:
                break;
            }

            if(m_graphe.m_select.is_vertex_selected())
            {
                if(m_graphe.m_select.is_different() || (m_edition && !m_last_edition))
                {
                    m_string_edit.clear();
                    m_string_edit = toString(m_graphe.m_vertices.at(m_graphe.m_select.vertex_selected()).m_value);
                }
                m_graphe.m_vertices.at(m_graphe.m_select.vertex_selected()).m_value = toDouble(m_string_edit);
            }
            else if(m_graphe.m_select.is_edge_selected() || (m_edition && !m_last_edition))
            {
                if(m_graphe.m_select.is_different())
                {
                    m_string_edit.clear();
                    m_string_edit = toString(m_graphe.m_edges.at(m_graphe.m_select.edge_selected()).m_weight);
                }
                m_graphe.m_edges.at(m_graphe.m_select.edge_selected()).m_weight = toDouble(m_string_edit);
            }
        }
        else
        {
            m_interface->m_delete_button.back_tmp_pos();
            if(m_graphe.m_select.is_vertex_selected())
            {
                if(m_interface->m_delete_button.clicked())
                {
                    m_graphe.delete_vertex(m_graphe.m_select.vertex_selected());
                    m_graphe.m_select.clear();
                }
            }
            else if(m_graphe.m_select.is_edge_selected())
            {
                if(m_interface->m_delete_button.clicked())
                {
                    m_graphe.delete_edge(m_graphe.m_select.edge_selected());
                    m_graphe.m_select.clear();
                }
            }
        }
    }
    else
    {
        m_interface->m_delete_button.set_pos(2000, 2000);
    }
}
