#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cat(char *f_name, int *options);
void line_e(char *line);
void line_t(char *line);

int main(int argc, char *argv[]) {
  int options[5] = {0, 0, 0, 0, 0};
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strcmp("-b", argv[i]) == 0 ||
          strcmp("--number-nonblank", argv[i]) == 0) {
        options[0] = 1;
      }
      if (strcmp("-e", argv[i]) == 0 || strcmp("-E", argv[i]) == 0) {
        options[1] = 1;
      }
      if (strcmp("-n", argv[i]) == 0 || strcmp("--number", argv[i]) == 0) {
        options[2] = 1;
      }
      if (strcmp("-s", argv[i]) == 0 ||
          strcmp("--squeeze-blank", argv[i]) == 0) {
        options[3] = 1;
      }
      if (strcmp("-t", argv[i]) == 0 || strcmp("-T", argv[i]) == 0) {
        options[4] = 1;
      }
    } else {
      cat(argv[i], options);
    }
  }
  return 0;
}

void cat(char *f_name, int *options) {
  FILE *fp;
  char buf[1000];
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int next_l = 0;
  int counter = 1;
  if ((fp = fopen(f_name, "r")) != NULL) {
    while ((read = getline(&line, &len, fp)) != -1) {
      strcpy(buf, line);
      if (options[1]) {
        line_e(buf);
      }
      if (options[4]) {
        line_t(buf);
      }
      if (options[3]) {
        if (line[0] == '\n') {
          if (next_l) {
            continue;
          } else {
            next_l = 1;
          }
        } else {
          next_l = 0;
        }
      }

      if (options[2]) {
        printf("%6d\t%s", counter, buf);
        counter++;
      } else if (options[0]) {
        if (buf[0] != '\n') {
          printf("%6d\t%s", counter, buf);
          counter++;
        } else {
          printf("\n");
        }
      } else {
        printf("%s", buf);
        counter++;
      }
    }
    free(line);
    fclose(fp);
  } else {
    printf("file do not exist");
  }
}

void line_e(char *line) {
  char *tmp = strchr(line, '\n');
  tmp[0] = '$';
  tmp[1] = '\n';
  tmp[2] = '\0';
}

void line_t(char *line) {
  char *tmp = strchr(line, '\t');
  char next;
  char t;
  while (tmp) {
    tmp[0] = '^';
    t = 'I';
    int counter = 1;
    while (tmp[counter] != '\n') {
      next = tmp[counter];
      tmp[counter] = t;
      t = next;
      counter++;
    }
    tmp[counter] = t;
    tmp[counter + 1] = '\n';
    tmp[counter + 2] = '\0';
    tmp = strchr(line, '\t');
  }
}
