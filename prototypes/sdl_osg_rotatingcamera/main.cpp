#include <iostream>
using std::cout; using std::endl; using std::cerr;
#include <string>
using std::string;

#include "gameManager.h"

int main(int argc, char **argv)
{
  try{
    GameManager manager;
    cerr << "Initialization completed!"<< endl;
    manager.runEventLoop();
  }
  catch(const string& error){
    cerr << error << endl;
    return 1;
  }
  return 0;
}
