#include "gui.hpp"

GUI::GUI() {
  handle = dlopen("./ncurseslib/libncurses.so", RTLD_LAZY);
  if (dlerror() != NULL)  {
    std::cout << "Couldn't load libnurses. :'(" << '\n';
    exit(0);
  }
  create = (DynamicGUI* (*)())dlsym(handle, "create_gl");
  destroy = (void (*)(DynamicGUI*))dlsym(handle, "destroy_gl");
  lib = create();
}

GUI::~GUI() {
   destroy(lib);
   dlclose(handle);
}

int GUI::drawFrame(Vector mapsize, std::list<Vector> apples, std::list<Vector> playerCords) {
  lib->drawFrame(mapsize, apples, playerCords);
  return (0);
}

int GUI::getUserResponse() {
  int response = lib->userResponse();
  if (response == -1) {
    destroy(lib);
    dlclose(handle);
    std::cout << "Bye :)" << '\n';
    exit(0);
  }
  return response;
}
