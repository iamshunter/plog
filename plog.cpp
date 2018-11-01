#include <stdio.h>
#include <stdarg.h>
#include <sys/timeb.h>
#include "plog.h"
char buffer[4096];

static double timeTag(void)
{
   struct timeb tval;
   ftime(&tval);
   return (tval.time + tval.millitm/1000.0);
}

int plog(const char *format, ...)
{
   printf("%s", format);

   va_list argptr;
   va_start(argptr, format);

   //vprintf(format, argptr);
   vsnprintf(buffer, sizeof(buffer), format, argptr);

   fprintf(stdout, buffer);

   va_end(argptr);
}

Plogger::Plogger()
{
   this->logLevel = NOTSET;
   this->fPtr = stdout;
}

int Plogger::log(PloggerLevel level, const char *format, ...)
{
   if ( this->fPtr == nullptr )
   {
      return 0;
   }

   if ( level <= this->logLevel )
   {
      int safeSize;
      int numTime;

      // @todo - upgrade this to print the log level with a %s before the time
      numTime  = snprintf(buffer, sizeof(buffer), "%.4f] ", timeTag() );
      safeSize = sizeof(buffer)-numTime;
      va_list argptr;
      va_start(argptr, format);
      vsnprintf(&buffer[numTime], safeSize, format, argptr);
      fprintf(this->fPtr, buffer);
      va_end(argptr);
   }

};

