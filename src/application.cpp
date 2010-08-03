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
    server_ = std::tr1::shared_ptr<SamplerServer>(new SamplerServer(receivePort, sendHost, sendPort));
    // idle signal handler - called as quickly as possible
    Glib::signal_idle().connect(sigc::mem_fun(*this, &Application::on_idle));
}

Application& Application::getInstance()
{
    // Meyer singleton pattern
    static Application instance;
    return instance;
}

/**
 * Called repeatedly very fast
 */
bool Application::on_idle()
{
    if (done_)
        Gtk::Main::quit();
    else
        server_->poll();
    return true; // return false when done
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
    Gtk::Main::run(gui_);
}

