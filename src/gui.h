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
        void on_record_clicked();
        void on_combobox_changed();
    private:
        Application *owner_;
        //Child widgets:
        Gtk::Frame frame_;
        Gtk::VBox vbox_;
        Gtk::Table table_;
        Gtk::Button record_button_widget_;
        Gtk::Button play_button_widget_;
        Gtk::ComboBoxText combobox_widget_;
};

#endif //_GUI_H_

