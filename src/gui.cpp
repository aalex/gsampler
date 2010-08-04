#include "./gui.h"
#include "./application.h"
#include "config.h"
#include <iostream>

//TODO:2010-08-04:aalex:Pass the application to the window
SamplerWindow::SamplerWindow(Application *owner) :
    owner_(owner), 
    frame_(), 
    vbox_(true, 10),
    table_(2, 1), // rows, columns
    record_start_button_(Gtk::Stock::MEDIA_RECORD),
    play_start_button_(Gtk::Stock::MEDIA_PLAY)
{
    /* Set some window properties */
    set_title(PACKAGE);
    set_size_request(200, 100);
  
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

    table_.attach(record_start_button_, 0, 1, 0, 1); 
    table_.attach(play_start_button_, 0, 1, 1, 2);
    record_start_button_.signal_clicked().connect(sigc::mem_fun(*this, &SamplerWindow::on_record_start_clicked));
    play_start_button_.signal_clicked().connect(sigc::mem_fun(*this, &SamplerWindow::on_play_start_clicked));
  
    // = Gtk::Button("Hello");
    show_all_children();
}

void SamplerWindow::on_play_start_clicked() {
    std::cout << "on_play_start_clicked" << std::endl; 
}

void SamplerWindow::on_record_start_clicked() {
    std::cout << "on_record_start_clicked" << std::endl; 
    static bool toggle = true;
    static bool dspStarted = false;
    if (not dspStarted)
    {
        owner_->sendMessage("start dsp");
        dspStarted = true;
    }
    if (toggle)
        owner_->sendMessage("start recording");
    else
        owner_->sendMessage("stop recording");
    toggle = not toggle;
}

SamplerWindow::~SamplerWindow()
{
    std::cout << "Freeing the window" << std::endl;
}

