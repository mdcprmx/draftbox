#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char** argv)
{
    int counter;
    int dig_opt = 0;

    while (1)
    {
        int current_option = optind ? optind : 1;
        // int current_option;
        // if (optind == optind)
        // {
        //     current_option = optind;
        // }
        // else
        // {
        //     current_option = 1;
        // }
        int option_index = 0;

        static struct option long_options[] = {
            {"add",     required_argument,    0,  0 },
            {"append",  no_argument,          0,  0 },
            {"delete",  required_argument,    0,  0 },
            {"verbose", no_argument,          0,  0 },
            {"create",  required_argument,    0, 'c'},
            {"file",    required_argument,    0,  0 },
            {0,         0,                    0,  0 },
        };

        counter = getopt_long(argc, argv, "abc:d:012", long_options, &option_index);
        if ( counter == -1) break;

        switch (counter)
        {
            case 0:
            printf("option %s", long_options[option_index].name);
            if (optarg)
                printf(" with argument %s\n", optarg);
            break;

            case '0':
            case '1':
            case '2':
                if (dig_opt != 0 && dig_opt != current_option)
                    printf("digits occur in two different arg-vector elements.\n");
                else
                {
                    dig_opt = current_option;
                    printf("option %c\n", counter);
                    break;
                }

            case 'a':
                printf("option a\n");
                break;
            
            case 'b':
                printf("optionn bb chosen!\n");

            case 'c':
                printf("option c with value '%s'\n", optarg);
                break;

            case 'd':
                printf("option d withh value '%s'\n", optarg);
            
            case '?':
                printf("error bruddah\n");
                break;

            default:
                printf("?? error, getopt returned char code 0%o ??\n", counter);

        }
    }



    if (optind < argc)
    {
        printf("this argument is not viable: ");
        while (optind < argc)
        printf("%s \n", argv[optind++]);
    }

    else
    {
        exit(EXIT_SUCCESS);
    }

    return 0;
}