// network.cc

#include "types.h"
#include <WinSock2.h>
#include <time.h>

bool network::init()
{
   srand((unsigned)time(0));
   WSADATA data = {};
   int result = WSAStartup(MAKEWORD(2, 2), &data);
   return result == 0;
}

void network::shut()
{
   WSACleanup();
}

void network::sleep(int64_t milliseconds)
{
   Sleep((DWORD)milliseconds);
}

int64_t network::get_ticks()
{
   static LARGE_INTEGER start = {};
   static int64_t factor = 0;
   if (!factor)
   {
      LARGE_INTEGER f = {};
      QueryPerformanceFrequency(&f);
      factor = f.QuadPart / 1000;
      QueryPerformanceCounter(&start);
   }

   LARGE_INTEGER now = {};
   QueryPerformanceCounter(&now);

   return (now.QuadPart - start.QuadPart) / factor;
}

