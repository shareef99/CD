#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct ConstFold {
  char new_str[10];
  char str[10];
} Opt_Data[20];

void ReadInput(char Buffer[], FILE* Out_file);

int Gen_token(char str[], char Tokens[][10]);

int New_Index = 0;

int main() {
  FILE* In_file, * Out_file;
  char Buffer[100], ch;
  int i = 0;
  In_file = fopen("input.txt", "r");
  Out_file = fopen("output.txt", "w");
  while (1) {
    ch = fgetc(In_file);
    i = 0;
    while (1) {
      if (ch == '\n')
        break;
      Buffer[i++] = ch;
      ch = fgetc(In_file);
      if (ch == EOF) break;
    }
    if (ch == EOF) break;
    Buffer[i] = '\0';
    ReadInput(Buffer, Out_file);
  }
  return 0;
}

void ReadInput(char Buffer[], FILE* Out_file) {
  char temp[100], Token[10][10];
  int n, i, j, flag = 0;
  strcpy(temp, Buffer);
  n = Gen_token(temp, Token);
  for (i = 0; i < n; i++) {
    if (!strcmp(Token[i], "=")) {
      if (isdigit(Token[i + 1][0]) || Token[i + 1][0] == '.') {
        flag = 1;
        strcpy(Opt_Data[New_Index].new_str, Token[i
          - 1]);
        strcpy(Opt_Data[New_Index++].str, Token[i + 1]);
      }
    }
  }
  if (!flag) {
    for (i = 0; i < New_Index; i++) {
      for (j = 0; j < n; j++) {
        if (!strcmp(Opt_Data[i].new_str, Token[j]))
          strcpy(Token[j], Opt_Data[i].str);
      }
    }
  }
  if (!flag) {
    for (i = 0; i < New_Index; i++) {
      for (j = 0; j < n; j++) {
        if (!strcmp(Opt_Data[i].new_str, Token[j]))
          strcpy(Token[j], Opt_Data[i].str);
      }
    }
  }
  fflush(Out_file);
  strcpy(temp, "");
  for (i = 0; i < n; i++) {
    strcat(temp, Token[i]);
    if (Token[i + 1][0] != ',' || Token[i + 1][0] != ';')
      strcat(temp, "");
  }
  strcat(temp, "\n\0");
  fwrite(&temp, strlen(temp), 1, Out_file);
}

int Gen_token(char str[], char Token[][10]) {
  int i = 0, j = 0, k = 0;
  while (str[k] != '\0') {
    j = 0;
    while (str[k] == ' ' || str[k] == '\t')
      k++;
    while (
      str[k] != ' ' &&
      str[k] != '\0' &&
      str[k] != '=' &&
      str[k] != '/' &&
      str[k] != '+' &&
      str[k] != '-' &&
      str[k] != '*' &&
      str[k] != ',' &&
      str[k] != ';'
      )
      Token[i][j++] = str[k++];
    Token[i++][j] = '\0';
    if (str[k] == '=' || str[k] == '/' || str[k] == '+' || str[k] == '-' ||
      str[k] == '*' || str[k] == ',' || str[k] == ';')
    {
      Token[i][0] = str[k++];
      Token[i++][1] = '\0';
    }
    if (str[k] == '\0')
      break;
  }
  return i;
}