// main.cc

#include "util.h"
#include "server.h"
#include "client.h"

#include <stdio.h>

static int
usage(const char *argv0)
{
   printf("usage: %s [server adapter-index|list]\n", argv0);
   return 0;
}

int main(int argc, char **argv)
{
   if (argc < 2) 
      return usage(argv[0]);

   bool is_list = strcmp(argv[1], "list") == 0;
   if (is_list)
   {
      printf("adapter addresses:\n");

      ip_address addresses[16];
      int address_count = ip_address::local_addresses(16, addresses);
      for (int index = 0;
           index < address_count;
           index++)
      {
         printf("  [%d]: %s\n", index, addresses[index].as_string());
      }

      return 0;
   }

   if (strcmp(argv[1], "server") != 0)
      return usage(argv[0]);

   if (!network::init())
   {
      debugf("error: could not initialize winsock!");
      return -1;
   }

   int adapter_index = 0;
   if (argc == 3)
      adapter_index = atoi(argv[2]);

   server srv = {};
   if (server_init(srv, adapter_index))
      server_run(srv);

   network::shut();

   return 0;
}
