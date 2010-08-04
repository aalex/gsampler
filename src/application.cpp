#include "./application.h"
#include "./samplerServer.h"
#include <iostream>
#include <string>
#include "gui.h"
#include <gtkmm.h>
#include <gtkmm/main.h>

Application::Application() :
    server_(),
    gui_(),
    audio_(),
    done_(false)
{
}

void Application::startServer(
    const std::string &receivePort,
    const std::string &sendHost,
    const std::string &sendPort
    )
{
    std::cout << "Starting server\n";
    server_.reset(new SamplerServer(this, receivePort, sendHost, sendPort));
    // idle signal handler - called as quickly as possible
    Glib::signal_idle().connect(sigc::mem_fun(*this, &Application::on_idle));
}


/**
 * Called repeatedly very fast
 */
bool Application::on_idle()
{
    if (done_) 
    {
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

/**
 * Send a command destined for one of the components of Application, like AudioManager or Gui.
 * This avoids exposing the API of our components to each other.
 * \param msg the command being sent, like an OSC path
 * \return true if the message was handled, false otherwise
 */
bool Application::sendMessage(const std::string &msg)
{
    // for now audio is the only one that handles messages
    return audio_.handleMessage(msg);
}

