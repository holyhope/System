#include <stdlib.h>

#include "data.h"
#include "server.h"

int main(int argc, char** argv)
{
  data_init();
  server_start();
  return EXIT_SUCCESS;
}
