#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

void scenario_open_file(int argc, char **argv, FILE *fname);
void scenario_no_arguments();
void check_file_doesnt_exist(FILE *fname_c);
void funct_file_print(FILE *fname_b);
void funct_arguments_parser(int argc, char **argv);

//////////////////
//////////////////
int main(int argc, char *argv[]) {
  char buffer[BUFFER_SIZE];
  FILE *filename;

  // if arguments exist.
  if (argc > 1)  // if second argument exists (first(0th) argument is always an
                 // executable name btw) do:
  {
    // funct_arguments_parser(argc, argv);
    scenario_open_file(argc, argv, filename);  // tries to open a file
    // check_file_doesnt_exist(filename);
    // fclose(filename);
  }

  // if no arguments are present.
  else
    scenario_no_arguments();  // imitates cat behavior with no args

  return 0;
}
//////////////////
//////////////////

void scenario_open_file(int argc, char **argv, FILE *fname) {
  for (int i = 1; i < argc; i++)  // depends of arg counter.
  {
    fname = fopen(argv[i], "r+");
    if (fname != NULL)  // if fopen returns anything that is not NULL, it means
                        // that fopen have opened a file.
    {                   // so we break the cycle.
      break;  // tho, there is no scenario for multiple files.. so.. yeah =(
    }
  }

  if (fname == 0)  // yeah, not 'NULL', it is '0'
  {
    printf("Error, couldn't open a file\n");
    exit(1);
  }

  else
    funct_file_print(fname);
}

void funct_file_print(FILE *fname) {
  char ch_buffer;
  ch_buffer = fgetc(fname);
  while (ch_buffer != EOF) {
    // printf("scen_file_print while loop");
    printf("%c", ch_buffer);
    ch_buffer = fgetc(fname);
  }
}

void scenario_no_arguments() {
  char usr_inpt_buffer[BUFFER_SIZE];

  while (1) {
    scanf("%s", usr_inpt_buffer);
    printf("%s\n", usr_inpt_buffer);
    break;  // WIP
  }
}

void check_file_doesnt_exist(FILE *fname_c) {  // WIP, need to finish
  if (fname_c != NULL) {
    printf("Error, couldn't open a file.\n");
    exit(1);
  }
}

// void funct_arguments_parser(int argc,char **argv)
// {
//     const char *options_char = "benstAETuv";
//     static struct option options_string[] = {
//         {"show-all",              no_argument, 0, 'A'},
//         {"number-nonblank",       no_argument, 0, 'b'},
//         {0,                       no_argument, 0, 'e'},
//         {"show-ends",             no_argument, 0, 'E'},
//         {"number",                no_argument, 0, 'n'},
//         {"squeeze-blank",         no_argument, 0, 's'},
//         {0,                       no_argument, 0, 't'},
//         {"show-tabs",             no_argument, 0, 'T'},
//         {0,                       no_argument, 0, 'u'},
//         {"show-nonprinting",      no_argument, 0, 'v'},
//         {"help",                  no_argument, 0,   0},
//         {"version",               no_argument, 0,   0},
//         {0,                                 0, 0,   0} // why is that? well..
//         just. because.
//         };

//     // small : b e n s t
//     //  big  : A E T
//     int b_flag = 0;
//     int e_flag = 0;
//     int n_flag = 0;
//     int s_flag = 0;
//     int t_flag = 0;
//     int A_flag = 0;
//     int E_flag = 0;
//     int T_flag = 0;

//     //  additional flags, not rly need to do them.
//     //  list : u v help version
//     int u_flag = 0;
//     int v_flag = 0;
//     int help_flag = 0;
//     int version_flag = 0;

//     // buffer with flags, for cycle.
//     int buffer_w_flag;

//     while ((buffer_w_flag = getopt_long(argc, argv, options_char,
//     options_string, )) != -1) //
//     {
//         switch (option)
//         {
//             case 'b':

//             case 'e':

//             case 'n':

//             case 's':

//             case 't':

//             case 'A':

//             case 'E':

//             case 'T':

//             case 'u':

//             case 'v':

//         }
//     }

// }