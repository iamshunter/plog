#include <unistd.h>
#include "plog.h"
int main(void)
{
   Plogger logger;

   int nn;// = plog("This is a log %f %d\n", 1.0, 2);
   nn = logger.log(WARN, "This is a log %f %d\n", 1.0, 2);
   // logger.setLevel(FATAL);
   usleep(5000);
   nn = logger.log(WARN, "This is a log %f %d\n", 1.0, 2);

   if ( nn <= 0 )
   {
      printf("Failed\n");
   }
}
