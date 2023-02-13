#ifndef SRC_CAT_H_
#define SRC_CAT_H_
#include <limits.h>
int condition_args(char *argv);
void flag_e(char ch, int option);
void flag_n(char ch, int *count, int *end_str, int *start_str);
int void_string(char ch, int *flag_end_str, int *flag_str_void,
                int *count_void_str);
void open_file(int argc, char *argv[1000], int option, int isFlag);
void flag_b(char ch, int *word, int *n);
void flag_s(char ch, int count_string);
void non_flag(char ch);
void flag_v(char ch, int option);
void flag_t(char ch, int option);
#endif  // SRC_CAT_H_
