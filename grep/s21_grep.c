#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_COUNT_FLAGS 5
void realloc_memory(int *temp, int *tempCount, char **templates);
void realloc_memory_int(int *temp, int *tempCount, int **templates);
void func_flag_o(char *buffer, char *line, char *buffer_string, int reg_case_i);
void func_many_files(char *buffer_string, char *file);
void func_flag_n(char *buffer_string, int *count_string);
struct opt {
  char opt;
  int index_arg;
};
enum flags {
  FLAG_E,
  FLAG_V,
  FLAG_I,
  FLAG_L,
  FLAG_N,
  FLAG_C,
  FLAG_H,
  FLAG_S,
  FLAG_F,
  FLAG_O,
  FLAG_DONE
};

int main(int argc, char *argv[]) {
  char *grep_option = "e:vilnchsf:o";
  int options[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  int option = 0;
  int size = 1;
  int non_arg = 0;
  int flag_non_ef = 0;
  char *buffer = malloc(sizeof(char));
  int temp = 1;
  int count_e_f = 0;
  strcpy(buffer, "");
  while ((option = getopt(argc, argv, grep_option)) != -1) {
    switch (option) {
      case 'e': {
        flag_non_ef = 1;
        options[FLAG_E] = FLAG_E;
        size = strlen(optarg) + 1 + size;
        if (size > temp) {
          realloc_memory(&size, &temp, &buffer);
        }
        if (count_e_f == 0) {
          strcat(buffer, optarg);
        } else {
          strcat(buffer, "|");
          strcat(buffer, optarg);
        }
        count_e_f = 1;

        break;
      }
      case 'n': {
        options[FLAG_N] = FLAG_N;
        break;
      }
      case 'v': {
        options[FLAG_V] = FLAG_V;
        break;
      }
      case 'l': {
        options[FLAG_L] = FLAG_L;
        break;
      }
      case 'i': {
        options[FLAG_I] = FLAG_I;
        break;
      }
      case 'c': {
        options[FLAG_C] = FLAG_C;
        break;
      }
      case 'h': {
        options[FLAG_H] = FLAG_H;
        break;
      }
      case 's': {
        options[FLAG_S] = FLAG_S;
        break;
      }
      case 'f': {
        FILE *file = fopen(optarg, "r");
        if (file != NULL) {
          options[FLAG_F] = FLAG_F;
          char *line = NULL;
          size_t len = 0;
          ssize_t read;
          while ((read = getline(&line, &len, file)) != -1) {
            size = strlen(line) + 1 + size;
            if (size > temp) {
              realloc_memory(&size, &temp, &buffer);
            }
            if (line[strlen(line) - 1] == '\n') {
              line[strlen(line) - 1] = '\0';
            }
            if (!count_e_f) {
              strcpy(buffer, line);
            } else {
              strcat(buffer, "|");
              strcat(buffer, line);
            }
            count_e_f = 1;
          }
          flag_non_ef = 1;
          free(line);
          fclose(file);
        } else {
          fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
          return 1;
        }
        break;
      }
      case 'o': {
        options[FLAG_O] = FLAG_O;
        break;
      }
      case '?': {
        non_arg = 1;
        break;
      }
    }
  }

  int countFiles = argc - optind;
  int sw = 0;
  for (; optind < argc; optind++) {
    if (non_arg) {
      fprintf(stderr,
              "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' "
              "for more information.");
      break;
    }
    if (!flag_non_ef && (options[FLAG_E] == -1 && options[FLAG_F] == -1)) {
      size = strlen(argv[optind]) + 1 + size;
      if (size > temp) {
        realloc_memory(&size, &temp, &buffer);
      }
      strcpy(buffer, argv[optind]);
      countFiles -= 1;
      flag_non_ef = 1;
      continue;
    }
    regex_t arbuz_regex;
    int error = 0;
    int count_string = 1;
    int match_string = 0;
    int lenghtb_buf = 1;
    int temp = 1;
    int reg_case_i = REG_EXTENDED;
    FILE *file = fopen(argv[optind], "r");
    if (file != NULL) {
      char *line = NULL;
      size_t len = 0;
      ssize_t read;
      while ((read = getline(&line, &len, file)) != -1) {
        char *buffer_string = malloc(strlen(line) * 4 * sizeof(char));
        lenghtb_buf = strlen(line) + strlen(argv[optind]) + 2;
        if (lenghtb_buf > temp) {
          realloc_memory(&temp, &lenghtb_buf, &buffer_string);
        }
        strcpy(buffer_string, "");
        if (options[FLAG_I] == FLAG_I) {
          reg_case_i = REG_ICASE;
          options[FLAG_I] = FLAG_DONE;
        }
        if ((error = regcomp(&arbuz_regex, buffer, reg_case_i)) != 0) {
          break;
        } else {
          if (options[FLAG_V] == FLAG_V) {
            sw = REG_NOMATCH;
            options[FLAG_V] = FLAG_DONE;
          }
          error = regexec(&arbuz_regex, line, 0, NULL, 0);

          if (error == sw) {
            if (options[FLAG_L] == FLAG_L) {
              printf("%s\n", argv[optind]);
              free(buffer_string);
              regfree(&arbuz_regex);
              break;
            }

            if (options[FLAG_E] == FLAG_E || flag_non_ef ||
                options[FLAG_F] == FLAG_F) {
              if (countFiles > 1 && options[FLAG_H] != FLAG_H) {
                func_many_files(buffer_string, argv[optind]);
              } else {
                strcpy(buffer_string, "");
              }
              if (options[FLAG_C] == FLAG_C) {
                if (options[FLAG_V] == -1 && strcmp(line, "\n") != 0) {
                  match_string++;
                } else if (options[FLAG_V] == FLAG_DONE) {
                  match_string++;
                }

              } else {
                if (options[FLAG_N] == FLAG_N) {
                  func_flag_n(buffer_string, &count_string);
                }
                if (options[FLAG_O] == FLAG_O) {
                  if (options[FLAG_V] != FLAG_DONE) {
                    func_flag_o(buffer, line, buffer_string, reg_case_i);
                  } else {
                    free(buffer_string);
                    regfree(&arbuz_regex);
                    break;
                  }

                } else {
                  strcat(buffer_string, line);
                }
              }
            }

            if (options[FLAG_C] != FLAG_C && options[FLAG_O] != FLAG_O) {
              printf("%s", buffer_string);
              char *search = NULL;
              if ((search = strchr(buffer_string, '\n')) == NULL) {
                printf("\n");
              }
            }
          }
          regfree(&arbuz_regex);
        }
        count_string++;
        free(buffer_string);
      }
      free(line);
      if (countFiles > 1 && options[FLAG_H] == -1 &&
          options[FLAG_C] == FLAG_C && options[FLAG_L] != FLAG_L) {
        printf("%s:%d\n", argv[optind], match_string);
      } else if (countFiles == 1 && options[FLAG_C] == FLAG_C &&
                 options[FLAG_L] != FLAG_L) {
        printf("%d\n", match_string);
      } else if (countFiles > 1 && options[FLAG_H] == FLAG_H &&
                 options[FLAG_C] == FLAG_C && options[FLAG_L] != FLAG_L) {
        printf("%d\n", match_string);
      }
      fclose(file);
    } else {
      if (options[FLAG_S] == -1) {
        fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
      }
    }
  }
  free(buffer);
}

void realloc_memory(int *temp, int *tempCount, char **templates) {
  if ((*temp) >= (*tempCount)) {
    (*tempCount) *= 2;
    *templates = realloc(*templates, (*tempCount) * sizeof(char *));
  }
}
void realloc_memory_int(int *temp, int *tempCount, int **templates) {
  if ((*temp) >= (*tempCount)) {
    (*tempCount) *= 2;
    *templates = realloc(*templates, (*tempCount) * sizeof(int *));
  }
}

void func_flag_o(char *buffer, char *line, char *buffer_string,
                 int reg_case_i) {
  regex_t r;
  if (regcomp(&r, buffer, reg_case_i)) {
    return;
  } else {
    const char *p = line;
    const int n_matches = 10;
    regmatch_t m[n_matches];

    while (1) {
      int i = 0;
      int nomatch = regexec(&r, p, n_matches, m, 0);
      if (nomatch) {
        break;
      }
      for (i = 0; i < n_matches; i++) {
        if (m[i].rm_so == -1) {
          break;
        }
      }

      printf("%s", buffer_string);
      printf("%.*s\n", (int)(m[0].rm_eo - m[0].rm_so), p + m[0].rm_so);
      p += m[0].rm_eo;
    }
    regfree(&r);
  }
}

void func_many_files(char *buffer_string, char *file) {
  char *tempbuffer = malloc((strlen(buffer_string) + 100) * sizeof(char));
  strcpy(tempbuffer, file);
  strcat(tempbuffer, ":");
  strcat(buffer_string, tempbuffer);
  free(tempbuffer);
  return;
}
void func_flag_n(char *buffer_string, int *count_string) {
  char *tempbuffer = malloc((strlen(buffer_string) + 100) * sizeof(char));
  sprintf(tempbuffer, "%d", *count_string);
  strcat(tempbuffer, ":");
  strcat(buffer_string, tempbuffer);
  free(tempbuffer);
  return;
}
