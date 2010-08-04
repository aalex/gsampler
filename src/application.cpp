#include "./application.h"
#include <iostream>
#include "gui.h"
#include <gtkmm.h>
#include <gtkmm/main.h>

Application::Application() :
    done_(false)
{
    //gui_(); ?
}

void Application::startServer(
    const std::string &receivePort,
    const std::string &sendHost,
    const std::string &sendPort
    )
{
    std::cout << "Starting server\n";
    server_ = std::tr1::shared_ptr<SamplerServer>(new SamplerServer(this, receivePort, sendHost, sendPort));
    // idle signal handler - called as quickly as possible
    Glib::signal_idle().connect(sigc::mem_fun(*this, &Application::on_idle));
}


/**
 * Called repeatedly very fast
 */
bool Application::on_idle()
{
    if (done_) {
        Gtk::Main::quit();
        return false; // return false when done
    } else {
        server_->poll();
        return true;
    }
}

void Application::quit()
{
    done_ = true;
}

/**
 * This method blocks until the application is done.
 */
void Application::run()
{
    // TODO:2010-08-04:aalex:Do not pass the window widget to Gtk:Main:run
    Gtk::Main::run(gui_);
}

