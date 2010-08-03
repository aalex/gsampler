#include "./gui.h"
#include "config.h"
#include <iostream>

SamplerWindow::SamplerWindow()
{
    /* Set some window properties */
    set_title(PACKAGE);
    set_size_request(400, 300);
  
    /* Sets the border width of the window. */
    set_border_width(10);
  
    add(frame_);
    frame_.set_label("Sampling stuff");
    frame_.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
  
    show_all_children();
}

SamplerWindow::~SamplerWindow()
{
    std::cout << "The window is being destroyed." << std::endl;
}

