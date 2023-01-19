#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(int *options, char **temp, int temp_n, char *f_name, int m_f);
int find_temp_line(char *line, char **temp, int temp_n, char *buf);
int find_temp_line_i(char *line, char **temp, int temp_n, char *buf);

int main(int argc, char *argv[]) {
  char **temp = malloc(100 * sizeof(char *));
  char *tem = malloc(1000 * 100 * sizeof(char));
  for (int i = 0; i < 100; i++) {
    temp[i] = tem + 1000 * i;
  }
  int m_f = 0;
  int temp_n = 0;
  int is_temp = 1;
  int options[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (unsigned long int j = 1; j < strlen(argv[i]); j++) {
        if ('e' == argv[i][j]) {
          options[0] = 1;
          if (i + 1 < argc) {
            strcpy(temp[temp_n], argv[i + 1]);
            i++;
            temp_n++;
            is_temp = 0;
          }
        }
        if ('i' == argv[i][j]) {
          options[1] = 1;
        }
        if ('v' == argv[i][j]) {
          options[2] = 1;
        }
        if ('c' == argv[i][j]) {
          options[3] = 1;
        }
        if ('l' == argv[i][j]) {
          options[4] = 1;
        }
        if ('n' == argv[i][j]) {
          options[5] = 1;
        }
        if ('h' == argv[i][j]) {
          options[6] = 1;
        }
        if ('s' == argv[i][j]) {
          options[7] = 1;
        }
        if ('f' == argv[i][j]) {
          options[8] = 1;
          if (i + 1 < argc) {
            FILE *fp2;
            char t_file[100];
            strcpy(t_file, argv[i + 1]);
            fp2 = fopen(t_file, "r");
            if (fp2 != NULL) {
              char *line = NULL;
              size_t len = 0;
              ssize_t read;
              while ((read = getline(&line, &len, fp2)) != -1) {
                char *pos = strchr(line, '\n');
                if (pos != NULL) {
                  pos[0] = '\0';
                }
                strcpy(temp[temp_n], line);
                temp_n++;
              }
              free(line);
              fclose(fp2);
            } else {
              printf("%s do not exist", t_file);
            }
            i++;
            is_temp = 0;
          }
        }
        if ('o' == argv[i][j]) {
          options[9] = 1;
        }
      }
    } else {
      if (is_temp) {
        strcpy(temp[temp_n], argv[i]);
        temp_n++;
        is_temp = 0;
      } else {
        if (i + 1 < argc) {
          m_f = 1;
        }
        grep(options, temp, temp_n, argv[i], m_f);
      }
    }
  }
  free(tem);
  free(temp);
  return 0;
}

void grep(int *options, char **temp, int temp_n, char *f_name, int m_f) {
  FILE *fp;
  char buf[1000];
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int counter_m = 0;
  int file_l = 1;
  char s_buf[100];
  int s_b_s;
  int is_ok;
  if ((fp = fopen(f_name, "r")) != NULL) {
    while ((read = getline(&line, &len, fp)) != -1) {
      char file_l_s[100];
      sprintf(file_l_s, "%d", file_l);
      strcpy(s_buf, "");
      s_b_s = 0;
      is_ok = 0;
      if (options[1]) {
        is_ok = find_temp_line_i(line, temp, temp_n, buf);
      } else {
        is_ok = find_temp_line(line, temp, temp_n, buf);
      }
      if (options[2]) {
        is_ok = !is_ok;
      }
      if (is_ok) {
        counter_m++;
        if (!options[3] && !options[4]) {
          if (m_f && !options[6]) {
            for (unsigned long int i = 0; i < strlen(f_name); i++) {
              s_buf[s_b_s] = f_name[i];
              s_b_s++;
            }
            s_buf[s_b_s] = ':';
            s_b_s++;
          }
          if (options[5]) {
            for (unsigned long int i = 0; i < strlen(file_l_s); i++) {
              s_buf[s_b_s] = file_l_s[i];
              s_b_s++;
            }
            s_buf[s_b_s] = ':';
            s_b_s++;
            s_buf[s_b_s] = '\0';
          }
          if (!options[9]) {
            printf("%s%s", s_buf, line);
          } else {
            if (options[2]) {
              printf("%s%s", s_buf, line);
            } else {
              printf("%s%s", s_buf, buf);
            }
          }
        }
      }
      file_l++;
    }
    free(line);
    if (options[3]) {
      printf("%d\n", counter_m);
    }
    if (options[4] && counter_m > 0) {
      printf("%s\n", f_name);
    }
    fclose(fp);
  } else {
    if (!options[7]) {
      printf("%s do not exist", f_name);
    }
  }
}

int find_temp_line(char *line, char **temp, int temp_n, char *buf) {
  int ans = 0;
  regmatch_t pmatch[10];
  regex_t reegex;
  int value;
  int b_s = 0;
  for (int i = 0; i < temp_n; i++) {
    value = regcomp(&reegex, temp[i], 0);
    value = regexec(&reegex, line, 10, pmatch, 0);
    if (value == 0) {
      ans = 1;
      int j = 0;
      while (pmatch[j].rm_eo != -1) {
        for (int k = pmatch[j].rm_so; k < pmatch[j].rm_eo; k++) {
          buf[b_s] = line[k];
          b_s++;
        }
        j++;
        buf[b_s] = '\n';
        b_s++;
      }
    }
    buf[b_s] = '\0';
  }
  regfree(&reegex);
  return ans;
}

int find_temp_line_i(char *line, char **temp, int temp_n, char *buf) {
  int ans = 0;
  regmatch_t pmatch[10];
  regex_t reegex;
  int value;
  int b_s = 0;
  for (int i = 0; i < temp_n; i++) {
    value = regcomp(&reegex, temp[i], REG_ICASE);
    value = regexec(&reegex, line, 10, pmatch, 0);
    if (value == 0) {
      ans = 1;
      int j = 0;
      while (pmatch[j].rm_eo != -1) {
        for (int k = pmatch[j].rm_so; k < pmatch[j].rm_eo; k++) {
          buf[b_s] = line[k];
          b_s++;
        }
        j++;
        buf[b_s] = '\n';
        b_s++;
      }
    }
    buf[b_s] = '\0';
  }
  regfree(&reegex);
  return ans;
}
