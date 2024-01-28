#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

#define BUFFER_SIZE 2048

// soo, "int main" is basic stuff, and "return 0" is not rly needed, but u should type it anyway for consistency sake.

void open_and_print (int arg_cntr, char** arg_vctr);

struct smartphone {
    char model[50];
    int price;
    int user_rating; // 0-10 range
};

void print_struct (struct smartphone*,  )
{

}

int main(int arg_cntr, char** arg_vctr)
{
    
    // open_and_print(arg_cntr, arg_vctr);

    
    return;
}






























/// @brief /////////////////////////////
////////////////////////////////////////
////////////////////////////////////////


// void open_and_print(int arg_cntr,char **arg_vctr)
// {
//     FILE *fp;
//     char buffer[BUFFER_SIZE];

//     fp = fopen(arg_vctr[1], "r");
//     if (fp != NULL)
//     {
//         while (1)
//         {
//         // fgets(write to | string length | stream (from where))
//         // soo that's how fgets works 
//         fgets(buffer, 255, fp); // soo it is "fgets("write to" | "string length" | "stream (from where)")"
//         printf("%s", buffer);
//         if (feof(fp) == 1) break;
//         }
//     }
    
//     else
//     {
//         printf("error bruddahh\n");
//         exit(1);
//     }
// }
