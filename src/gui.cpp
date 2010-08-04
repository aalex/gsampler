#include "./gui.h"
#include "./application.h"
#include "config.h"
#include <iostream>

SamplerWindow::SamplerWindow(Application *owner) :
    owner_(owner), 
    frame_(), 
    vbox_(true, 10),
    table_(2, 1), // rows, columns
    record_button_widget_("Start recording"), //;Gtk::Stock::MEDIA_RECORD),
    play_button_widget_("Start playing") //Gtk::Stock::MEDIA_PLAY)
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

    table_.attach(record_button_widget_, 0, 1, 0, 1); // 0th row, 0th column
    table_.attach(play_button_widget_, 0, 1, 1, 2); // 0th row, 1st column
    record_button_widget_.signal_clicked().connect(sigc::mem_fun(*this, &SamplerWindow::on_record_clicked));
    play_button_widget_.signal_clicked().connect(sigc::mem_fun(*this, &SamplerWindow::on_play_clicked));
  
    show_all_children();
}

void SamplerWindow::on_play_clicked() {
    std::cout << "on_play_clicked" << std::endl; 
    static bool toggle = true;
    // TODO: start DSP
    if (toggle) {
        play_button_widget_.set_label("Stop playing");
    } else {
        play_button_widget_.set_label("Start playing");
    }
    toggle = not toggle;
}

void SamplerWindow::on_record_clicked() {
    std::cout << "on_record_clicked" << std::endl; 
    static bool toggle = true;
    static bool dspStarted = false;
    if (not dspStarted)
    {
        owner_->sendMessage("start dsp");
        dspStarted = true;
    }
    if (toggle) {
        record_button_widget_.set_label("Stop recording");
        owner_->sendMessage("start recording");
    } else {
        record_button_widget_.set_label("Start recording");
        owner_->sendMessage("stop recording");
    }
    toggle = not toggle;
}

SamplerWindow::~SamplerWindow()
{
    std::cout << "Freeing the window" << std::endl;
}

