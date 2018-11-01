#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/timeb.h>
#include <time.h>
#include "plog.h"

char *Plogger::logTag(PloggerLevel level)
{
   struct timeb tval;
   double dTime;
   time_t tTime;

   const char *levelPtr;
   switch(level)
   {
      case FATAL:
         levelPtr = "(FATL)";
         break;
      case ALERT:
         levelPtr = "(ALRT)";
         break;
      case CRIT:
         levelPtr = "(CRIT)";
         break;
      case ERROR:
         levelPtr = "(ERR) ";
         break;
      case WARN:
         levelPtr = "(WARN)";
         break;
      case NOTICE:
         levelPtr = "(NOTE)";
         break;
      case INFO:
         levelPtr = "(INFO)";
         break;
      case DEBUG:
         levelPtr = "(DEBG)";
         break;
      case NOTSET:
      default:
         levelPtr = "(NSET)";
         break;
   }

   ftime(&tval);
   dTime = (tval.time + tval.millitm/1000.0);
   tTime = (time_t)dTime;
   snprintf(this->tagBuf, sizeof(this->tagBuf), "%s", ctime(&tTime));
   int frac = round( (dTime-tTime)*1000 );
   snprintf(&this->tagBuf[19], sizeof(this->tagBuf)-19, ".%03d]%s", frac, levelPtr);
   return &this->tagBuf[10];
}

Plogger::Plogger()
{
   this->logLevel   = NOTSET;
   this->fPtr       = stdout;
   this->hdrOneShot = true;
   this->echoFlag   = true;
}

Plogger::~Plogger()
{
   if ( this->fPtr != stdout )
   {
      fclose(this->fPtr);
   }
}

bool Plogger::open(const char *name)
{
   printf("Opening %s\n", name);
   time_t tTime = time(0);
   snprintf(buffer, sizeof(buffer)-4, "%s_%s", name, ctime(&tTime));
   buffer[strlen(buffer)-1]=0;
   sprintf(buffer, "%s.log", buffer); // No snprintf needed, we know there's room for 4 bytes from 
                                      // the prev snprintf.
   for ( int ii = 0; ii < strlen(buffer); ii++ )
   {
      if ( buffer[ii] == ' ')
      {
         buffer[ii] = '_';
      }
   }
   FILE *file = fopen(buffer, "w");
   if ( file != nullptr )
   {
      this->fPtr = file;
      printf("Open:: fPtr %X stdout %X\n", this->fPtr, stdout);
      return true;
   }
   else
   {
      perror("\n\nERROR");
      this->fPtr = stdout;
      printf("Open:: fPtr %X stdout %X\n", this->fPtr, stdout);
   }
   return false;
}

int Plogger::log(PloggerLevel level, const char *format, ...)
{
   if ( this->fPtr == nullptr )
   {
      return 0;
   }

   if ( this->hdrOneShot )
   {
      this->hdrOneShot = false;
      time_t tTime = time(0);
      fprintf(this->fPtr, "Log file created :: %s", ctime(&tTime));
   }
   if ( level <= this->logLevel )
   {
      int safeSize;
      int numTime;

      // @todo - upgrade this to print the log level with a %s before the time
      numTime  = snprintf(this->buffer, sizeof(this->buffer), "%s::", logTag(level) );
      safeSize = sizeof(this->buffer)-numTime;
      va_list argptr;
      va_start(argptr, format);
      vsnprintf(&this->buffer[numTime], safeSize, format, argptr);
      va_end(argptr);
      fprintf(this->fPtr, this->buffer);
      if ( this->echoFlag )
      {
         printf(this->buffer);
      }
   }

};

void  Plogger::setLevel(PloggerLevel inLevel)
{
   const char *levelPtr;
   this->logLevel = inLevel;
   switch(inLevel)
   {
      case FATAL:
         levelPtr = "(FATL)";
         break;
      case ALERT:
         levelPtr = "(ALRT)";
         break;
      case CRIT:
         levelPtr = "(CRIT)";
         break;
      case ERROR:
         levelPtr = "(ERR) ";
         break;
      case WARN:
         levelPtr = "(WARN)";
         break;
      case NOTICE:
         levelPtr = "(NOTE)";
         break;
      case INFO:
         levelPtr = "(INFO)";
         break;
      case DEBUG:
         levelPtr = "(DEBG)";
         break;
      case NOTSET:
      default:
         levelPtr = "(NSET)";
         this->logLevel = NOTSET; // Catching an illegal log level
         break;
   }
   fprintf(this->fPtr, "%s::Log level changed to %s ********\n", logTag(inLevel), levelPtr);
   if ( this->echoFlag )
   {
      printf(             "%s::Log level changed to %s ********\n", logTag(inLevel), levelPtr);
   }
};
