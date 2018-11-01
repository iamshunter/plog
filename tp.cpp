#include <unistd.h>
#include "plog.h"
int main(void)
{
   Plogger logger;
   Plogger logger2;

   int nn;

   bool stat = logger2.open("logout");
   if ( stat )
   {
      printf("stat == TRUE\n");
   }
   else
   {
      printf("stat == FALSE\n");
   }

   //nn = logger.log (WARN, "This is a log %f %d\n", 1.0, 2);
   nn = logger2.log(WARN, "This is a log %f %d\n", 1.0, 2);
   //logger.setLevel (FATAL);
   logger2.setLevel(FATAL);
   usleep(5000);
   //nn = logger.log (FATAL, "This is a log %f %d\n", 1.0, 2);
   nn = logger2.log(FATAL, "This is a log %f %d\n", 1.0, 2);
   //nn = logger.log (WARN, "This is a log %f %d\n", 1.0, 2);
   nn = logger2.log(WARN, "This is a log %f %d\n", 1.0, 2);

   if ( nn <= 0 )
   {
      printf("Failed\n");
   }
}
