// #include <stdio.h>
// #include <stdlib.h>

// int main(int argument_counter, char *argument_values[])
// {
//    for (int i = 0; i < argument_counter; i++)
//    {
//       printf("Argument %d: %s\n", i, argument_values[i]);
//    }

//    return 0;
// }

// int getopt(int argument_counter, char* const argument_values[], const char * optstring);

#include <stdio.h>
#include <unistd.h>

int main(int arg_cntr, char* arg_val[])
{
   int rez = 0;

   while ( (rez = getopt(arg_cntr, arg_val, "ab:C::d")) != -1)
   {


      switch (rez)
      {
         case 'a' : printf("argument a found. \n");
         break;

         case 'b' : printf("argument b found! \n");
         break;

         case 'C' : printf("found argument C!!1!\n");
         break;

         case 'd' : printf("found argument d..\n");
         break;

         case '?' : printf("error bruh\n");
         break;
      }


   }


   return 0;
}



