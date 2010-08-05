#ifndef _GUI_H_
#define _GUI_H_

#include <gtkmm.h>

// forward declaration
class Application;

class SamplerWindow : public Gtk::Window
{
    public:
        SamplerWindow(Application *owner);
        virtual ~SamplerWindow();
        void on_play_clicked();
        void on_remove_clicked();
        void on_add_clicked();
        void on_record_clicked();
        void on_combobox_changed();
        void add_sound_to_combobox(std::string name);
    private:
        Application *owner_;
        //Child widgets:
        Gtk::Frame frame_;
        Gtk::VBox vbox_;
        Gtk::Table table_;
        Gtk::Label selection_label_widget_;
        Gtk::Label controls_label_widget_;
        Gtk::Button record_button_widget_;
        Gtk::Button play_button_widget_;
        Gtk::Button add_button_widget_;
        Gtk::Button remove_button_widget_;
        Gtk::ComboBoxText combobox_widget_;
};

#endif //_GUI_H_

