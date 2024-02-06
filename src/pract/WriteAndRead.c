#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 255


void print_w_scanf();
void print_w_fgets(int argc, char** argv);
void print_fgets2(int arg_cntr, char** arg_vctr);

int main(int arg_cntr, char** arg_vctr)
{
    //print_w_scanf();
    //print_w_fgets(arg_cntr, arg_vctr);
    print_fgets2(arg_cntr, arg_vctr);
    return 0;
}




/// @brief /////////////////////////////
////////////////////////////////////////
////////////////////////////////////////


void print_fgets2(int arg_cntr,char **arg_vctr)
{
    FILE *fp;
    char buffer[BUFFER_SIZE];

    fp = fopen(arg_vctr[1], "r");
    if (fp != NULL)
    {
        while (1)
        {
        // fgets(write to | string length | stream (from where))
        // soo that's how fgets works 
        fgets(buffer, 255, fp); // soo it is "fgets("write to" | "string length" | "stream (from where)")"
        printf("%s", buffer);
        if (feof(fp) == 1) break;
        }
    }
    
    else
    {
        printf("error bruddahh\n");
        exit(1);
    }
}



void print_w_scanf()
{
    char buffer[BUFFER_SIZE];
    scanf("%2000[^\n]", buffer);
    printf("%s", buffer);
}



void print_w_fgets(int argc, char** argv)
{
    FILE *file_pointer;
    char buffer[BUFFER_SIZE];
    if ((file_pointer = fopen(argv[1], "r")) == NULL ) // if fopen returns NULL
    {
        printf("Error, cannot open file.\n");
        exit(1);
    }

    else
    {
        while(1) // what is feof?
        {
            fgets(buffer, 255, file_pointer); // how exactly does fgets works?
            printf("%s", buffer);
            if (feof(file_pointer)) // soo "feof" is checking for file end. If feof is true - break
                break;
        }

    }

}