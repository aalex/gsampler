#include "./gui.h"
#include "config.h"
#include <iostream>

SamplerWindow::SamplerWindow():
    frame_(), 
    vbox_(true, 10),
    table_(10, 2) // rows, columns
{
    /* Set some window properties */
    set_title(PACKAGE);
    set_size_request(400, 300);
  
    /* Sets the border width of the window. */
    set_border_width(10);
    
    // A VBox
    vbox_.set_border_width(5);
    vbox_.pack_start(frame_);
    add(vbox_);
    
    // A frame
    frame_.set_label("Sampling stuff");
    frame_.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    frame_.add(table_);
    
    // The table contains buttons and labels
    //TODO:2010-08-03:aalex:get the size of the table
    //int rows = 10;
    //guint rows;
    //guint columns; 
    //table_.get_size(&rows, &columns);
    
    //TODO:2010-08-03:aalex:create a table of buttons and labels
    // for (int i = 0; i < rows; i++) {
    //     Gtk::Label label = Gtk::Label("Hello");
    //     table_.attach(label, 0, 1, i, i + 1);
    //     Gtk::Button button = Gtk::Button("Hello");
    //     table_.attach(button, 1, 2, i, i + 1);
    // }
  
    show_all_children();
}

SamplerWindow::~SamplerWindow()
{
    std::cout << "Freeing the window" << std::endl;
}

