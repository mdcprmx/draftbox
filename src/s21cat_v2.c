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
    
    return EXIT_SUCCESS;
}
//////////////////
//////////////////

void scenario_open_file(int argc, char **argv)
{
    flag_config opt_switcher = {0};
    funct_arguments_parser(argc, argv, &opt_switcher);

    FILE *fname = funct_file_open(argc, argv);

    check_file_exist(fname);
    funct_file_print(fname, &opt_switcher);
}

void funct_file_print(FILE *fname_a, flag_config *opt_state)
{
    char ch_previous_buffer = '\n';
    char ch_current_buffer = fgetc(fname_a);
    size_t lines_counter = 0;
    

    while (ch_current_buffer != EOF)
    {
        putc(ch_current_buffer, stdout);     
        ch_current_buffer = fgetc(fname_a);

        // flag 'e' logic
        if(opt_state->e_flag == 1 && ch_current_buffer == '\n' )
        {
            fputc('$', stdout);
        }

        // flag 'n' logic (n is part of 'b' and 'n' flags)
        if(opt_state->b_flag == 1 && ch_previous_buffer == '\n' && ch_current_buffer != '\n')
        {
            fprintf(stdout, "%6zu\t", lines_counter);
            lines_counter++;
        } else if (opt_state->n_flag && ch_previous_buffer == '\n')
        {
            fprintf(stdout, "%6zu\t", lines_counter);
            lines_counter++;
        }
        
        // flag



        // ch_previous_buffer = ch_current_buffer;
        // ch_current_buffer = fgetc(fname_a);
    }

    fclose(fname_a);
}

void text_squeeze(FILE* fname_b)
{
    char ch_crnt_bfr = fgetc(fname_b);
    while (ch_crnt_bfr = '\n')
    {
        ch_crnt_bfr = fgetc(fname_b);
    }
    ungetc(ch_crnt_bfr, fname_b);
}

FILE* funct_file_open(int argc, char **argv)
{
    FILE *file_pointer = NULL;
    for (int i = 1; i < argc ; i++ )           // depends of arg counter.
    {
        file_pointer = fopen(argv[i], "r");    // tries to open a file 
        if (file_pointer != NULL) break;       // if fopen returns NULL - it didnt open a file.
    }
    
}

void check_file_exist(FILE *fname_c)
{
    if (fname_c == 0)  // yeah, not 'NULL', it is '0'
    {
        printf("Error, couldn't open a file\n");
        exit(EXIT_FAILURE);
    }
}

void funct_arguments_parser(int argc, char **argv, flag_config *opt_switcher)
{
    const char *SHORT_OPT = "+beEnstTvh";
    int buffer_w_flag = getopt_long(argc, argv, SHORT_OPT, LONG_OPT, 0);

    while (buffer_w_flag != -1)
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
                opt_switcher->e_flag = 1;
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

            case 'h':
                error_help_print();
                break;

            case '?':
            default:
                error_usage_print();
        }

        buffer_w_flag = getopt_long(argc, argv, SHORT_OPT, LONG_OPT, 0);
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

void error_usage_print()
{
    printf("Error, invalid flag | Usage: [FLAG] [FILE_NAME] | flags are [-benstETuv]\n");
    exit(EXIT_FAILURE);
}

void error_help_print()
{
    printf("CAT usage: [FLAG] [FILE_NAME]\n\n");
    printf("-b, --number-nonblank  | number nonempty output lines, overrides -n\n");
    printf("-e                     | equivalent to -vE\n");
    printf("-E, --show-ends        | print $ at the end of each line\n");
    printf("-n, --number           | number all output lines\n");
    printf("-s, --squeeze-blank    | suppress repeated empty output lines\n");
    printf("-t                     | equivalent to -vT\n");
    printf("-T, --show-tabs        | display TAB chars as ^I\n");
    printf("-v, --show-nonprinting | use ^ and M- notation, except for LFD and TAB\n");
    printf("-h                     | display this help and exit\n");
    exit(EXIT_FAILURE);
}

