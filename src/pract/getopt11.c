#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

void user_input_error()
{
    printf("Error. Use only \"a\" or \"b\" flags.\n");
    exit(2);
}

int main(int arg_cnt, char** arg_vctr)
{
    if (arg_cnt < 2)
    {
        user_input_error();
    }

    int option;
    int a_flag = 0;
    int b_flag = 0;
    while ((option = getopt(arg_cnt, arg_vctr, "ab")) !=-1 ) // when getopt returns "-1" cycle will stop.
    {                                                        // cuz it returns arguments usually.
        switch (option) // options is... well, it reads options bruh.
        {
            case 'a' :
                if (b_flag == 1)
                {
                    user_input_error();
                }

                else
                {
                    a_flag++;
                    printf("flag a found!\n");
                    break;
                }
                
            
            case 'b' :
                if (a_flag == 1)
                {
                    user_input_error();
                }

                else
                {
                    b_flag++;
                    printf("flag b founddd broo!\n");
                    break;
                }
            default :
                printf("Errorr bruddah\n");
        }
    }

    return 0;
}