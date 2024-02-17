#include "s21_cat.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    scenario_open_file(argc, argv);
  }

  else
    scenario_no_arguments();

  return EXIT_SUCCESS;
}

void scenario_open_file(int argc, char **argv) {
  flag_config opt_switcher = {0};
  funct_arguments_parser(argc, argv, &opt_switcher);

  FILE *fname;
  fname = funct_file_open(argc, argv);

  check_file_exist(fname);
  funct_file_print(fname, &opt_switcher);
}

void funct_file_print(FILE *fname_a, flag_config *opt_state) {
  int counter_s_flag = 0;
  int counter_nb_flags = 1;

  char ch_previous = '\n';
  char ch_buffer;
  while ((ch_buffer = fgetc(fname_a)) != EOF) {
    if (opt_state->s_flag == 1 && ch_previous == '\n' && ch_buffer == '\n') {
      counter_s_flag++;
      if (counter_s_flag > 1) continue;
    }

    if ((opt_state->n_flag == 1 && ch_previous == '\n' &&
         opt_state->b_flag == 0) ||
        ((opt_state->b_flag == 1) && ch_previous == '\n' &&
         ch_buffer != '\n')) {
      printf("%6d\t", counter_nb_flags);
      counter_nb_flags++;
    }

    if (opt_state->e_flag == 1 && ch_buffer == '\n') {
      printf("$");
    }

    if (opt_state->t_flag == 1 && ch_buffer == '\t') {
      printf("^");
      ch_buffer = 'I';
    }

    if (opt_state->v_flag == 1 && !(ch_buffer >= 32 && ch_previous < 127) &&
        ch_buffer != '\n' && ch_buffer != '\t') {
      if (ch_buffer == 127) {
        printf("^");
        ch_buffer = ch_buffer - 64;
      } else if (ch_buffer < 32 && ch_buffer >= 0) {
        printf("^");
        ch_buffer = ch_buffer + 64;
      }
    }

    ch_previous = ch_buffer;
    printf("%c", ch_buffer);
  }
  fclose(fname_a);
}

FILE *funct_file_open(int argc, char **argv) {
  FILE *file_pointer = NULL;
  for (int i = optind; i < argc; i++) {
    file_pointer = fopen(argv[i], "r");
    if (file_pointer != NULL) break;
  }
  return file_pointer;
}

void funct_arguments_parser(int argc, char **argv, flag_config *opt_switcher) {
  const char *SHORT_OPT = "beEnstTvh";
  int buffer_w_flag = getopt_long(argc, argv, SHORT_OPT, LONG_OPT, 0);

  while (buffer_w_flag != -1) {
    switch (buffer_w_flag) {
      case 'b':
        opt_switcher->b_flag = 1;
        break;

      case 'e':
        opt_switcher->e_flag = 1;
        opt_switcher->v_flag = 1;
        break;

      case 'n':
        opt_switcher->n_flag = 1;
        break;

      case 's':
        opt_switcher->s_flag = 1;
        break;

      case 't':
        opt_switcher->t_flag = 1;
        opt_switcher->v_flag = 1;
        break;

      case 'E':
        opt_switcher->e_flag = 1;
        break;

      case 'T':
        opt_switcher->t_flag = 1;
        break;

      case 'v':
        opt_switcher->v_flag = 1;
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

void scenario_no_arguments() {
  char usr_inpt_buffer[BUFFER_SIZE];

  while (1) {
    scanf("%2000[^\n]s", usr_inpt_buffer);
    printf("%s\n", usr_inpt_buffer);
    break;
  }
}

void check_file_exist(FILE *fname_c) {
  if (fname_c == 0) {
    printf("Error, couldn't open a file\n");
    exit(EXIT_FAILURE);
  }
}

void error_usage_print() {
  printf(
      "Error, invalid flag | Usage: [FLAG] [FILE_NAME] | flags are "
      "[-benstETuv]\n");
  exit(EXIT_FAILURE);
}

void error_help_print() {
  printf("CAT usage: [FLAG] [FILE_NAME]\n\n");
  printf("-b, --number-nonblank  | number nonempty lines, overrides -n\n");
  printf("-e                     | equivalent to -vE\n");
  printf("-E, --show-ends        | print $ at the end of each line\n");
  printf("-n, --number           | number all output lines\n");
  printf("-s, --squeeze-blank    | suppress repeated empty output lines\n");
  printf("-t                     | equivalent to -vT\n");
  printf("-T, --show-tabs        | display TAB chars as ^I\n");
  printf(
      "-v, --show-nonprinting | use ^ and M- notation, except for LFD and "
      "TAB\n");
  printf("-h                     | display this help and exit\n");
  exit(EXIT_FAILURE);
}