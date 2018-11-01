#ifndef _PLOG_H
#define _PLOG_H

#include <stdio.h>
enum PloggerLevel 
{ 
  EMERG = 0,   FATAL  = 0,   ALERT  = 100, CRIT = 200, 
  ERROR = 300, WARN   = 400, NOTICE = 500, INFO = 600, 
  DEBUG = 700, NOTSET = 800 
};

class Plogger {
   private:
      FILE        *fPtr;
      PloggerLevel logLevel;

   public:
      int          log(PloggerLevel, const char *format, ...);
      void         setLevel(PloggerLevel inLevel){this->logLevel = inLevel;};

      Plogger(void);
      PloggerLevel getLevel(void){return this->logLevel;};
};

#endif //_PLOG_H
