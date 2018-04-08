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


    m_top_box.add_child(m_add_vertex);
    m_add_vertex.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_add_vertex.set_dim(100, 20);
    m_add_vertex.set_bg_color(GRISCLAIR);
    m_add_vertex.set_text("ADD VERTEX");

    m_top_box.add_child(m_add_edge_button);
    m_add_edge_button.set_pos(m_add_vertex.get_posx(), m_add_vertex.get_posy() + 25);
    m_add_edge_button.set_dim(100, 20);
    m_add_edge_button.set_bg_color(GRISCLAIR);

    m_add_edge_button.add_child(m_add_edge_label);
    m_add_edge_label.set_message("ADD EDGE");

    m_top_box.add_child(m_delete_button);
    m_delete_button.set_pos(m_add_vertex.get_posx(), m_add_vertex.get_posy() + 50);
    m_delete_button.set_dim(100, 20);
    m_delete_button.set_bg_color(GRISCLAIR);
    m_delete_button.set_tmp_pos();

    m_delete_button.add_child(m_delete_button_label);
    m_delete_button_label.set_message("DELETE");


    m_top_box.add_child(m_struct_box);
    m_struct_box.set_pos(600, 0);
    m_struct_box.set_dim(300, TAILLE_BAR-9);
    m_struct_box.set_border(0);
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
    m_connexe_display.set_pos(m_connexe_button.get_posx()+200, m_connexe_button.get_posy());
    m_connexe_display.set_dim(90, 20);
    m_connexe_display.set_bg_color(GRISCLAIR);

    m_connexe_display.add_child(m_connexe_display_label);
    m_connexe_display_label.set_message("DISPLAY");

    m_struct_box.add_child(m_kconnexe_button);
    m_kconnexe_button.set_pos(m_connexe_button.get_posx(), m_connexe_button.get_posy()+25);
    m_kconnexe_button.set_dim(130, 20);
    m_kconnexe_button.set_bg_color(GRISCLAIR);
    m_kconnexe_button.set_text("K-CONNEXITE");

    m_struct_box.add_child(m_kconnexe_label);
    m_kconnexe_label.set_pos(m_kconnexe_button.get_posx()+150, m_kconnexe_button.get_posy()+7);

    m_struct_box.add_child(m_kconnexe_display);
    m_kconnexe_display.set_pos(m_kconnexe_button.get_posx()+200, m_kconnexe_button.get_posy());
    m_kconnexe_display.set_dim(90, 20);
    m_kconnexe_display.set_bg_color(GRISCLAIR);

    m_kconnexe_display.add_child(m_kconnexe_display_label);
    m_kconnexe_display_label.set_message("DISPLAY");

    m_struct_box.add_child(m_rgraphe_button);
    m_rgraphe_button.set_pos(m_kconnexe_button.get_posx()+75, m_kconnexe_button.get_posy()+28);
    m_rgraphe_button.set_dim(200, 20);
    m_rgraphe_button.set_bg_color(GRISCLAIR);

    m_rgraphe_button.add_child(m_rgraphe_button_label);
    m_rgraphe_button_label.set_message("DISPALY GRAPHE REDUIT");

    m_top_box.add_child(m_fonc_box);
    m_fonc_box.set_pos(600, 0);
    m_fonc_box.set_dim(300, TAILLE_BAR-9);
    m_fonc_box.set_border(0);
    m_fonc_box.set_padding(0);
    m_fonc_box.set_tmp_pos();

    m_fonc_box.add_child(m_play_button);
    m_play_button.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_play_button.set_dim(80, 20);
    m_play_button.set_padding(0);
    m_play_button.set_margin(0);
    m_play_button.set_bg_color(GRISCLAIR);

    m_play_button.add_child(m_play_button_label);
    m_play_button_label.set_message("RUN");

    m_fonc_box.add_child(m_label_coefr);
    m_label_coefr.set_pos(5, 30);
    m_label_coefr.set_message("r");

    m_fonc_box.add_child(m_slider_coefr);
    m_slider_coefr.set_padding(0);
    m_slider_coefr.set_margin(0);
    m_slider_coefr.set_border(0);
    m_slider_coefr.set_dim(20, m_fonc_box.get_dimy());
    m_slider_coefr.set_gravity_y(grman::GravityY::Center);
    m_slider_coefr.set_posx(90);
    m_slider_coefr.set_range(0.0 , 20.0);
    m_slider_coefr.set_value(log(2000));

    m_fonc_box.add_child(m_label_coefpred);
    m_label_coefpred.set_pos(5, 40);
    m_label_coefpred.set_message("pred");

    m_fonc_box.add_child(m_slider_coefpred);
    m_slider_coefpred.set_padding(0);
    m_slider_coefpred.set_margin(0);
    m_slider_coefpred.set_border(0);
    m_slider_coefpred.set_dim(20, m_fonc_box.get_dimy());
    m_slider_coefpred.set_gravity_y(grman::GravityY::Center);
    m_slider_coefpred.set_posx(112);
    m_slider_coefpred.set_range(0.0 , 10.0);
    m_slider_coefpred.set_value(log(5000));

    m_fonc_box.add_child(m_label_coefproi);
    m_label_coefproi.set_pos(5, 50);
    m_label_coefproi.set_message("proi");

    m_fonc_box.add_child(m_slider_coefproi);
    m_slider_coefproi.set_padding(0);
    m_slider_coefproi.set_margin(0);
    m_slider_coefproi.set_border(0);
    m_slider_coefproi.set_dim(20, m_fonc_box.get_dimy());
    m_slider_coefproi.set_gravity_y(grman::GravityY::Center);
    m_slider_coefproi.set_posx(134);
    m_slider_coefproi.set_range(1.0 , 100.0);
    m_slider_coefproi.set_value(1);

    m_fonc_box.add_child(m_label_speed);
    m_label_speed.set_pos(5, 60);
    m_label_speed.set_message("speed");

    m_fonc_box.add_child(m_slider_speed);
    m_slider_speed.set_padding(0);
    m_slider_speed.set_margin(0);
    m_slider_speed.set_border(0);
    m_slider_speed.set_dim(20, m_fonc_box.get_dimy());
    m_slider_speed.set_gravity_y(grman::GravityY::Center);
    m_slider_speed.set_posx(156);
    m_slider_speed.set_range(0.0 , 2.0);
    m_slider_speed.set_value(1);
}

void Fenetre::close()
{
    m_graphe.m_select.clear();
    m_graphe.close_graphe();
    m_interface->m_button_structurel.set_switch(true);
    m_interface->m_button_fonctionnel.set_switch(false);
    m_mode = 1;
    m_string_edit.clear();
    m_interface->m_edit_button.set_switch(false);
    m_interface->m_move_button.set_switch(false);
    m_interface->m_play_button.set_switch(false);
    m_interface->m_add_edge_button.set_switch(false);
    m_interface->m_connexe_display.set_switch(false);
    m_interface->m_kconnexe_display.set_switch(false);
    m_interface->m_rgraphe_button.set_switch(false);
    m_kconnexe_vertex.clear();
    m_Sconnexe_vertex.clear();
    m_interface->m_kconnexe_label.set_message("");
    m_interface->m_connexe_label.set_message("");
    m_change = true;
}

void Fenetre::update()
{
    if (!m_interface)
            return;

    pre_update();



    m_graphe.update();
    m_interface->m_top_box.update();

    if(m_interface->m_rgraphe_button.get_switch())
        m_rgraphe.update();

    m_last_edition = m_edition;

    pre_update_button();
    update_fixe_button();
    update_fonc();
    post_update_button();
    update_selected();
    post_update();
}

void Fenetre::update_fixe_button()
{
    if(m_interface->m_add_edge_button.get_switch())
    {
        if(m_graphe.m_select.st_selected() && m_graphe.m_select.is_different() && m_graphe.m_select.is_vertex_selected())
        {
            if(m_selected_buffer.empty())
                m_selected_buffer.push_back(m_graphe.m_select.vertex_selected());
            else if(m_selected_buffer.front() != m_graphe.m_select.vertex_selected())
                m_selected_buffer.push_back(m_graphe.m_select.vertex_selected());
        }

        if(m_selected_buffer.size() == 2)
        {
            int i = 0;
            while(m_graphe.m_edges.count(i) != 0)
            {
                i++;
            }
            m_graphe.add_interfaced_edge(i, m_selected_buffer.at(0), m_selected_buffer.at(1), 10);
            m_interface->m_add_edge_button.set_switch(false);
            m_kconnexe_vertex.clear();
            m_Sconnexe_vertex.clear();
            m_interface->m_kconnexe_label.set_message("");
            m_interface->m_connexe_label.set_message("");
            m_change = true;
        }
    }
}

void Fenetre::update_fonc()
{
    if(m_mode == 2)
    {
        if(m_interface->m_play_button.get_switch())
        {
            m_graphe.update_time(m_coefr, m_coefpred, m_coefproi, m_speed);
        }
    }
}

void Fenetre::update_selected()
{
    if(m_graphe.m_select.st_selected() && m_edition)
    {
        //std::cout << (char)grman::key_last << " " << (int)grman::key_last << " " << m_string_edit << std::endl;
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
        else if(m_graphe.m_select.is_edge_selected())
        {
            if(m_graphe.m_select.is_different() || (m_edition !=m_last_edition) )
            {
                m_string_edit.clear();
                m_string_edit = toString(m_graphe.m_edges.at(m_graphe.m_select.edge_selected()).m_weight);
            }
            m_graphe.m_edges.at(m_graphe.m_select.edge_selected()).m_weight = toDouble(m_string_edit);
        }
    }


    if(m_graphe.m_select.st_selected() && m_delete)
    {
        m_interface->m_delete_button.back_tmp_pos();
        if(m_graphe.m_select.is_vertex_selected())
        {
            if(m_interface->m_delete_button.clicked())
            {
                m_graphe.delete_vertex(m_graphe.m_select.vertex_selected());
                m_kconnexe_vertex.clear();
                m_Sconnexe_vertex.clear();
                m_interface->m_kconnexe_label.set_message("");
                m_interface->m_connexe_label.set_message("");
                m_graphe.m_select.clear();
            }
        }
        else if(m_graphe.m_select.is_edge_selected())
        {
            if(m_interface->m_delete_button.clicked())
            {
                m_graphe.delete_edge(m_graphe.m_select.edge_selected());
                m_kconnexe_vertex.clear();
                m_Sconnexe_vertex.clear();
                m_interface->m_kconnexe_label.set_message("");
                m_interface->m_connexe_label.set_message("");
                m_graphe.m_select.clear();
            }
        }
    }
    else
    {
        m_interface->m_delete_button.set_pos(2000, 2000);
    }
}

void Fenetre::pre_update()
{
    //m_interface->m_slider_coefr.set_value(m_coefr);
    m_interface->m_label_coefr.set_message("r=" + std::to_string((int)m_coefr));

    //m_interface->m_slider_coefpred.set_value(m_coefpred);
    m_interface->m_label_coefpred.set_message("pred=" + std::to_string((int)m_coefpred));

    //m_interface->m_slider_coefproi.set_value(m_coefproi);
    m_interface->m_label_coefproi.set_message("proi=" + std::to_string((int)m_coefproi));

    //m_interface->m_slider_speed.set_value(m_coefproi);
    m_interface->m_label_speed.set_message("speed=" + toString(m_speed));
}


void Fenetre::post_update()
{
    m_coefr = exp(m_interface->m_slider_coefr.get_value());
    m_coefpred = exp(m_interface->m_slider_coefpred.get_value());
    m_coefproi = m_interface->m_slider_coefproi.get_value();
    m_speed = pow(m_interface->m_slider_speed.get_value(), 2);
}

void Fenetre::pre_update_button()
{
    /// bouton fixe


    if(m_interface->m_load_button.clicked())
    {
        close();
        m_graphe.ChargerGraphe(m_interface->m_load_file.get_message(), 0, TAILLE_BAR, LARGEUR_FENETRE, HAUTEUR_FENETRE - TAILLE_BAR);
        m_interface->m_load_file.leave_edition();
        m_interface->m_load_file.clear_message();
        m_change = true;
    }

    if(m_interface->m_save_button.clicked())
    {
        m_graphe.SauverGraphe(m_interface->m_load_file.get_message());
        m_interface->m_load_file.leave_edition();
        m_interface->m_load_file.clear_message();
        m_change = true;
    }

    if(m_interface->m_close_button.clicked())
    {
        close();
        m_change = true;
    }

    if(m_interface->m_add_vertex.clicked())
    {
        m_interface->m_add_edge_button.set_switch(false);
        m_interface->m_rgraphe_button.set_switch(false);
        m_kconnexe_vertex.clear();
        m_Sconnexe_vertex.clear();

        int i = 0;
        while(m_graphe.m_vertices.count(i) != 0)
        {
            i++;
        }
        m_graphe.add_interfaced_vertex(i, 10, 500, 500, "tchoupi.jpg", 0);
        m_change = true;
    }

    if(m_interface->m_add_edge_button.switching())
    {
        if(m_interface->m_add_edge_button.get_switch())
        {
            m_selected_buffer.clear();
        }
        m_graphe.m_select.unselect();
        m_interface->m_rgraphe_button.set_switch(false);
        m_interface->m_connexe_display.set_switch(false);
        m_interface->m_kconnexe_display.set_switch(false);
        m_change = true;
    }


    /// bouton move & edit


    if(m_interface->m_move_button.switching())
    {
        m_interface->m_edit_button.set_switch(false);
        if(m_interface->m_move_button.get_switch())
        {
            m_interface->m_rgraphe_button.set_switch(false);
        }

        m_change = true;
    }

    if(m_interface->m_edit_button.switching())
    {
        m_interface->m_move_button.set_switch(false);
        if(m_interface->m_edit_button.get_switch())
        {
            m_interface->m_rgraphe_button.set_switch(false);
        }

        m_change = true;
    }


    /// Bouton de switch mode


    if(m_interface->m_button_structurel.switching())
    {
        if(m_interface->m_button_structurel.get_switch())
        {
            m_interface->m_button_fonctionnel.set_switch(false);
            m_interface->m_play_button.set_switch(false);
            m_mode = 1;
        }
        else
        {
            m_interface->m_button_structurel.set_switch(true);
        }

        m_change = true;
    }

    if(m_interface->m_button_fonctionnel.switching())
    {
        if(m_interface->m_button_fonctionnel.get_switch())
        {
            m_interface->m_button_structurel.set_switch(false);
            m_interface->m_connexe_display.set_switch(false);
            m_interface->m_kconnexe_display.set_switch(false);
            m_interface->m_rgraphe_button.set_switch(false);
            m_mode = 2;
        }
        else
        {
            m_interface->m_button_fonctionnel.set_switch(true);
        }

        m_change = true;
    }


    /// bouton de struct


    if(m_mode == 1)
    {
        if(m_interface->m_connexe_button.clicked())
        {
            m_Sconnexe_vertex = m_graphe.Sconnexe();
            m_interface->m_connexe_label.set_message(std::to_string(m_Sconnexe_vertex.size()));
            m_interface->m_connexe_display.set_switch(false);
            m_change = true;
        }

        if(m_interface->m_kconnexe_button.clicked())
        {
            m_interface->m_kconnexe_label.set_message("working");
            m_interface->m_kconnexe_label.set_posx(m_interface->m_kconnexe_label.get_posx()-10);
            m_interface->m_kconnexe_label.update();
            grman::mettre_a_jour();
            m_interface->m_kconnexe_label.set_posx(m_interface->m_kconnexe_label.get_posx()+10);
            m_kconnexe_vertex = m_graphe.kconnexe();
            m_interface->m_kconnexe_label.set_message(std::to_string(m_kconnexe_vertex.front().size()));
            update();
            m_interface->m_kconnexe_display.set_switch(false);
            m_change = true;
        }

        if(m_interface->m_connexe_display.switching())
        {
            m_interface->m_kconnexe_display.set_switch(false);
            m_interface->m_rgraphe_button.set_switch(false);

            m_change = true;
        }

        if(m_interface->m_kconnexe_display.switching())
        {
            m_interface->m_connexe_display.set_switch(false);
            m_interface->m_rgraphe_button.set_switch(false);

            m_change = true;
        }

        if(m_interface->m_rgraphe_button.switching())
        {
            m_interface->m_kconnexe_display.set_switch(false);
            m_interface->m_connexe_display.set_switch(false);
            m_interface->m_add_edge_button.set_switch(false);
            m_interface->m_edit_button.set_switch(false);
            m_interface->m_move_button.set_switch(false);

            m_change = true;
        }
    }


    /// bouton de fonc


    if(m_mode == 2)
    {
        if(m_interface->m_play_button.switching())
        {
            m_change = true;
        }
    }
}

void Fenetre::post_update_button()
{
    if(m_change)
    {
        if(m_interface->m_add_edge_button.get_switch())
        {
            m_interface->m_add_edge_button.set_bg_color(BLEUCLAIR);
        }
        else
        {
            m_interface->m_add_edge_button.set_bg_color(GRISCLAIR);
        }


        /// bouton move & edit


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


        /// Bouton de switch mode


        if(m_interface->m_button_structurel.get_switch())
        {
            m_interface->m_button_structurel.set_bg_color(ROSECLAIR);
        }
        else
        {
            m_interface->m_button_structurel.set_bg_color(GRISCLAIR);
        }

        if(m_interface->m_button_fonctionnel.get_switch())
        {
            m_interface->m_button_fonctionnel.set_bg_color(ROSECLAIR);
        }
        else
        {
            m_interface->m_button_fonctionnel.set_bg_color(GRISCLAIR);
        }


        /// bouton de struct


        if(m_mode == 1)
        {
            m_interface->m_struct_box.back_tmp_pos();
            m_interface->m_fonc_box.set_pos(2000, 2000);

            if(!m_interface->m_connexe_display.get_switch())
            {
                m_interface->m_connexe_display.set_bg_color(GRISCLAIR);
//                if(!m_Sconnexe_vertex.empty())
//                {
//                    for(unsigned int i = 0 ; i < m_Sconnexe_vertex.size() ; ++i)
//                    {
//                        for(unsigned int j = 0 ; j < m_Sconnexe_vertex.at(i).size() ; ++j)
//                        {
//                            m_graphe.m_vertices.at(m_Sconnexe_vertex.at(i).at(j)).m_interface->m_marque[i].set_bg_color(-1);
//                        }
//                        if(i == 7) {break;}
//                    }
//                }
            }

            if(!m_interface->m_kconnexe_display.get_switch())
            {
                m_interface->m_kconnexe_display.set_bg_color(GRISCLAIR);
//                if(!m_kconnexe_vertex.empty())
//                {
//                    for(unsigned int i = 0 ; i < m_kconnexe_vertex.size() ; ++i)
//                    {
//                        for(unsigned int j = 0 ; j < m_kconnexe_vertex.at(i).size() ; ++j)
//                        {
//                            m_graphe.m_vertices.at(m_kconnexe_vertex.at(i).at(j)).m_interface->m_marque[i].set_bg_color(-1);
//                        }
//                        if(i == 7) {break;}
//                    }
//                }
            }

            if(!m_interface->m_connexe_display.get_switch() || !m_interface->m_kconnexe_display.get_switch())
            {
//                for(unsigned int i = 0 ; i < m_kconnexe_vertex.size() ; ++i)
//                {
//                    for(unsigned int j = 0 ; j < m_kconnexe_vertex.at(i).size() ; ++j)
//                    {
//                        m_graphe.m_vertices.at(m_kconnexe_vertex.at(i).at(j)).m_interface->m_marque[i].set_bg_color(-1);
//                    }
//                }
                for(auto it : m_graphe.m_vertices)
                {
                    for(unsigned int i = 0 ; i < 8 ; ++i)
                    {
                        //m_graphe.m_vertices.at(m_kconnexe_vertex.at(i).at(j)).m_interface->m_marque[i].set_bg_color(-1);
                        it.second.m_interface->m_marque[i].set_bg_color(-1);
                    }
                }
            }

            if(m_interface->m_connexe_display.get_switch())
            {
                m_interface->m_connexe_display.set_bg_color(CYANCLAIR);

                if(!m_Sconnexe_vertex.empty())
                {
                    for(unsigned int i = 0 ; i < m_Sconnexe_vertex.size() ; ++i)
                    {
                        for(unsigned int j = 0 ; j < m_Sconnexe_vertex.at(i).size() ; ++j)
                        {
                            m_graphe.m_vertices.at(m_Sconnexe_vertex.at(i).at(j)).m_interface->m_marque[i].set_bg_color(COLOR[i]);
                        }
                        if(i == 7) {std::cout << "NO MORE PLACE TO TAG\n"; break;}
                    }
                }
            }

            if(m_interface->m_kconnexe_display.get_switch())
            {
                m_interface->m_kconnexe_display.set_bg_color(CYANCLAIR);

                if(!m_kconnexe_vertex.empty())
                {
                    for(unsigned int i = 0 ; i < m_kconnexe_vertex.size() ; ++i)
                    {
                        for(unsigned int j = 0 ; j < m_kconnexe_vertex.at(i).size() ; ++j)
                        {
                            m_graphe.m_vertices.at(m_kconnexe_vertex.at(i).at(j)).m_interface->m_marque[i].set_bg_color(COLOR[i]);
                        }
                        if(i == 7) {std::cout << "NO MORE PLACE TO TAG\n"; break;}
                    }
                }
            }

            if(m_interface->m_rgraphe_button.get_switch())
            {
                m_interface->m_rgraphe_button.set_bg_color(CYANCLAIR);
                if(!m_Sconnexe_vertex.empty())
                {
                    if(m_rgraphe.m_interface == nullptr)
                        m_rgraphe.create(m_graphe, m_Sconnexe_vertex);
                }

            }
            else
            {
                m_interface->m_rgraphe_button.set_bg_color(GRISCLAIR);
                m_rgraphe.close_graphe();
            }
        }


        /// bouton de fonc


        if(m_mode == 2)
        {
            m_interface->m_struct_box.set_pos(2000, 2000);
            m_interface->m_fonc_box.back_tmp_pos();

            if(m_interface->m_play_button.get_switch())
            {
                m_interface->m_play_button.set_bg_color(CYANCLAIR);
            }
            else
            {
                m_interface->m_play_button.set_bg_color(GRISCLAIR);
            }
        }

        m_change = false;
    }
}
