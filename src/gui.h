#ifndef _GUI_H_
#define _GUI_H_

#include <gtkmm.h>

class SamplerWindow : public Gtk::Window
{
    public:
        SamplerWindow();
        virtual ~SamplerWindow();
    protected:
        //Child widgets:
        Gtk::Frame frame_;
};

#endif //_GUI_H_

