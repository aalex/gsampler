#ifndef _GUI_H_
#define _GUI_H_

#include <gtkmm.h>

class SamplerWindow : public Gtk::Window
{
    public:
        SamplerWindow();
        virtual ~SamplerWindow();
    private:
        //Child widgets:
        Gtk::Frame frame_;
        Gtk::VBox vbox_;
        Gtk::Table table_;
        Gtk::Button record_start_button_;
        Gtk::Button play_start_button_;
        void on_play_start_clicked();
        void on_record_start_clicked();
};

#endif //_GUI_H_

