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
    set_size_request(320, 100);
  
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

    // a combo box (drop-down menu)
    table_.attach(combobox_widget_, 0, 2, 0, 1); // left, right, top, bottom
    combobox_widget_.append_text("Sample 1");
    combobox_widget_.append_text("Sample 2");
    combobox_widget_.append_text("Sample 3");
    combobox_widget_.set_active_text("Sample 1");
    combobox_widget_.signal_changed().connect(sigc::mem_fun(*this, &SamplerWindow::on_combobox_changed) );
    
    // The buttons:
    table_.attach(record_button_widget_, 0, 1, 1, 2); 
    table_.attach(play_button_widget_, 1, 2, 1, 2); 
    record_button_widget_.signal_clicked().connect(sigc::mem_fun(*this, &SamplerWindow::on_record_clicked));
    play_button_widget_.signal_clicked().connect(sigc::mem_fun(*this, &SamplerWindow::on_play_clicked));
    // Done: 
    show_all_children();
}

void SamplerWindow::on_combobox_changed() {
    std::cout << "on_combobox_changed" << std::endl; 
    Glib::ustring text = combobox_widget_.get_active_text();
    if(!(text.empty()))
        std::cout << "Combo changed: " << text << std::endl;
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

