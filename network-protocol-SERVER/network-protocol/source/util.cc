// util.cc

#include "util.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void debugf(const char *format, ...)
{
   char message[1024] = {};
   va_list args;
   va_start(args, format);
   vsprintf_s(message, sizeof(message), format, args);
   va_end(args);
   printf("%s\n", message);
}

void zero_memory(void *pointer, uint64_t size)
{
   uint8_t *dst = (uint8_t *)pointer;
   for (uint64_t index = 0;
        index < size;
        index++)
   {
      dst[index] = 0;
   }
}
