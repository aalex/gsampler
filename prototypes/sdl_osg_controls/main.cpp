#include <iostream>
using std::cout; using std::endl; using std::cerr;
#include <string>
using std::string;

#include "system_controller.h"

int main(int argc /*argc*/, char **argv /*argv[]*/){
    try{
        System_Controller controller;
        cerr << "SDL Initialization Succeeded!"<< endl;
        controller.start_event_loop();
    }
    catch(string error){
        cerr << error << endl;
        return 1;
    }
    return 0;
}
