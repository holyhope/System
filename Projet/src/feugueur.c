#include <stdlib.h>

#include "data.h"
#include "server.h"

int main(int argc, char** argv){
  data_init();
  server_start(1963);
  return EXIT_SUCCESS;
}
