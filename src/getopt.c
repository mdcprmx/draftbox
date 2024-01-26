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
   int arg_eater = 0;

    // soo, u have to insert ":" after char that must have a parameter.
    // first example, "a:bCd" (in this case "flag a" will have a parameter, number or etc)
   
    // second example, "abC:d" (in this case "flag C" will have a parameter)

    // third example, "a:b:C:d:" (in this case every flag will have a parameter)

    //////////////
    // also, if flag may, or may not have a parameter (number) u must type "::" after supposed char.
    // first example, "a::"
    // second example, "a::bcdesxa"
    // third example, "ab::c::des::x"

    opterr = 0; // yeah it looks like an error, but it actually turns off error msgs! nice.
    while ( (arg_eater = getopt(arg_cntr, arg_val, "abCd")) != 1)

    {


      switch (arg_eater)
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



