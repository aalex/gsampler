#include "./gui.h"
#include "config.h"
#include <iostream>

SamplerWindow::SamplerWindow():
    vbox_(true, 10),
    frame_()
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
  
    show_all_children();
}

SamplerWindow::~SamplerWindow()
{
    std::cout << "Freeing the window" << std::endl;
}

