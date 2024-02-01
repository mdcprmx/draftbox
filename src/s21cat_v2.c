#include "s21_cat.h"

//////////////////
//////////////////
int main(int argc, char *argv[])
{
    // if arguments exist.
    if (argc > 1)   
    {
        scenario_open_file(argc, argv);
    }

    // if no arguments.
    else scenario_no_arguments(); 
    
    return 0;
}
//////////////////
//////////////////


void scenario_open_file(int argc, char **argv)
{
    flag_config opt_switcher = {0};
    funct_arguments_parser(argc, argv, &opt_switcher);

    FILE *fname;
    for (int i = 0; i < argc ; i++ )    // depends of arg counter.
    {
        fname = fopen(argv[i], "r");    // tries to open a file 
        if (fname != NULL) break;       // if fopen returns NULL - it didnt open a file.
    }

    check_file_exist(fname);
    funct_file_print(fname, &opt_switcher);
}

void funct_file_print(FILE *fname, flag_config *opt_state)
{
    // char **output_for_user_buffer = malloc (sizeof(char) * MEM_ALLOC_SIZE);
    // check_memory_allocation(output_for_user_buffer);

    char ch_buffer = 0;
    ch_buffer = fgetc(fname);
    
    while (ch_buffer != EOF)
    {
        printf("%c", ch_buffer);
        ch_buffer = fgetc(fname);
        
    //     if (opt_state->n_flag != 0)
    //     {
    //         int line_counter = 0;
    //         printf("%6d\t", line_counter); 
    //         line_counter++;
    //     }
    }

    fclose(fname);
    // free(output_for_user_buffer);
}

void check_memory_allocation(char **ofu_buffer)
{
    if(ofu_buffer == NULL)
    {
        printf("Allocating memory failed.\n");
        exit(1);
    }
}

void check_file_exist(FILE *fname_c)
{
    if (fname_c == 0)  // yeah, not 'NULL', it is '0'
    {
        printf("Error, couldn't open a file\n");
        exit(1);
    }
}

void funct_arguments_parser(int argc, char **argv, flag_config *opt_switcher)
{
    const char *short_opt = "+beEnstTv";
    int buffer_w_flag;
    
    while ((buffer_w_flag = getopt_long(argc, argv, short_opt, long_opt, NULL )) != -1)
    {
        switch (buffer_w_flag)
        {
            case 'b':
                opt_switcher->b_flag = 1;
                printf("b flag is on\n");
                break;

            case 'e':
                opt_switcher->e_flag = 1;
                opt_switcher->v_flag = 1;
                printf("e flag is on\n");
                break;

            case 'n':
                opt_switcher->n_flag = 1;
                printf("n flag is on\n");
                break;

            case 's':
                opt_switcher->s_flag = 1;
                printf("s flag is on\n");
                break;

            case 't':
                opt_switcher->t_flag = 1;
                opt_switcher->v_flag = 1;
                printf("t flag is on\n");
                break;

            case 'E':
                opt_switcher->E_flag = 1;
                printf("E flag is on\n");
                break;

            case 'T':
                opt_switcher->T_flag = 1;
                printf("T flag is on\n");
                break;

            case 'v':
                opt_switcher->v_flag = 1;
                printf("v flag is on\n");
                break;

            default:
                printf("Error, valid flags are [-benstETuv]\n");
                exit(1);
        }
    }
}

void scenario_no_arguments()
{
    char usr_inpt_buffer[BUFFER_SIZE];

    while (1)
    {
    scanf("%2000[^\n]s", usr_inpt_buffer);
    printf("%s\n", usr_inpt_buffer);
    break; // WIP
   }
}
