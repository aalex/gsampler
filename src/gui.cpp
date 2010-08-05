#include "./gui.h"
#include "./application.h"
#include "config.h"
#include <iostream>


SamplerWindow::SamplerWindow(Application *owner) :
    owner_(owner), 
    frame_(), 
    vbox_(true, 10),
    table_(3, 3), // args: rows, columns
    selection_label_widget_("Selection:"),
    controls_label_widget_("Controls:"),
    record_button_widget_("Start recording"), 
    play_button_widget_("Start playing"),
    add_button_widget_("Create a sound"),
    remove_button_widget_("Delete this sound"),
    combobox_widget_()
{
    /* Set some window properties */
    set_title(PACKAGE);
    set_size_request(300, 200);
  
    /* Sets the border width of the window. */
    set_border_width(10);
    
    // A VBox
    vbox_.set_border_width(5);
    vbox_.pack_start(frame_);
    add(vbox_);
    
    // A frame:
    frame_.set_label("Sampling stuff");
    frame_.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    // A table:
    frame_.add(table_);
    // ||-----------||-----||------||
    // || sel label || combobox    || 
    // ||           || add || rm   ||
    // || ctl label || rec || play ||
    // ||-----------||-----||------||
    // Arguments for table.add: left, right, top, bottom
    // Some labels:
    table_.attach(selection_label_widget_, 0, 1, 0, 1); 
    table_.attach(controls_label_widget_, 0, 1, 2, 3);
    // a combo box (drop-down menu)
    table_.attach(combobox_widget_, 1, 3, 0, 1);
    combobox_widget_.append_text("Sample 1");
    combobox_widget_.append_text("Sample 2");
    combobox_widget_.append_text("Sample 3");
    combobox_widget_.set_active_text("Sample 1");
    combobox_widget_.signal_changed().connect(sigc::mem_fun(*this, &SamplerWindow::on_combobox_changed) );
    
    // The add/remove buttons:
    table_.attach(add_button_widget_, 1, 2, 1, 2); 
    table_.attach(remove_button_widget_, 2, 3, 1, 2); 
    add_button_widget_.signal_clicked().connect(sigc::mem_fun(*this, &SamplerWindow::on_add_clicked));
    remove_button_widget_.signal_clicked().connect(sigc::mem_fun(*this, &SamplerWindow::on_remove_clicked));
    // The play/rec buttons:
    table_.attach(record_button_widget_, 1, 2, 2, 3); 
    table_.attach(play_button_widget_, 2, 3, 2, 3); 
    record_button_widget_.signal_clicked().connect(sigc::mem_fun(*this, &SamplerWindow::on_record_clicked));
    play_button_widget_.signal_clicked().connect(sigc::mem_fun(*this, &SamplerWindow::on_play_clicked));
    // Done: 
    show_all_children();
}

void SamplerWindow::on_combobox_changed() {
    //std::cout << "on_combobox_changed" << std::endl; 
    Glib::ustring text = combobox_widget_.get_active_text();
    if(text.empty()) {
        remove_button_widget_.set_sensitive(false);
    } else {
        std::cout << "Combo changed: " << text << std::endl;
        remove_button_widget_.set_sensitive(true);
    }
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

void SamplerWindow::on_add_clicked() {
    std::cout << "on_add_clicked" << std::endl;
    add_sound_to_combobox("Fill me");
    // TODO:2010-08-04:aalex:We could pop a dialog to ask for a name for the new sound. We could also allocate them incrementally.
}

void SamplerWindow::add_sound_to_combobox(std::string name) {
    // TODO:2010-08-04:aalex:How can we know if an element is already in the combo box? I think we can get an iterator to the model data, and iterated it.
    // See Gtk::TreeModel::iterator
    // TODO:2010-08-04:aalex:We could also use a ComboBoxEntry
    // Gtk::TreeIter *iter = combobox_widget_.get_model()->get_children();
    // Gtk::TreeModel::Row row = *iter;
    std::cout << "add_sound_to_combobox " << name << std::endl;
    combobox_widget_.append_text(name.c_str());
}

void SamplerWindow::on_remove_clicked() {
    Glib::ustring text = combobox_widget_.get_active_text();
    if(! (text.empty())) {
        std::cout << "on_remove_clicked " << text << std::endl;
    } else {
        std::cout << "on_remove_clicked but no item selected" << std::endl;
    }
}

SamplerWindow::~SamplerWindow()
{
    std::cout << "Freeing the window" << std::endl;
}

// We used to use:
//Gtk::Stock::MEDIA_RECORD),
//Gtk::Stock::MEDIA_PLAY)

