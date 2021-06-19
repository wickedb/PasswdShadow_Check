#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include"source_prog.h"
#define PASSWD_FIELDS 7
#define SHADOW_FIELDS 8

/*prints the whole file*/
void print_file(FILE *fptr)
{
    rewind(fptr);
    char ch;

    while((ch = fgetc(fptr)) != EOF)
        putchar(ch);
}

/*Concatenates two strings*/
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    if(!result)
        perror(":");
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/*Introduces a small delay*/
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
    // Storing start time
    clock_t start_time = clock();
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

/*Checks for valid format:
This function checks if there are the correct number of fields. It also
checks for improper indentation or spacing. Assuming we know field count for
passwd=8 and shadow=7.*/
int format_check(FILE *f, int fields)
{

switch(fields)
{
  case PASSWD_FIELDS:
  {
    rewind(f);
    char c;
    int lines=0,colon=0; //fields are seperated by colons
    fields = fields - 1;
    c = fgetc(f);
    while((c=fgetc(f))!=EOF)
    {
      if(c==':')
        colon++;
      if(c=='\n'){
       lines++;
       if(colon == fields)
        colon = 0;
      else
        return lines-1;
     }
     if(fields == PASSWD_FIELDS-1 && c == ' ' && colon != 4)/*spaces are allowed only in the fifth field for passwd*/
       return lines;
    }
  }break;
  case SHADOW_FIELDS:
  {
    rewind(f);
    char c;
    int lines=0,colon=0; //fields are seperated by colons
    c = fgetc(f);
    while((c=fgetc(f))!=EOF)
    {
      if(c==':')
        colon++;
      if(c=='\n'){
       lines++;
       if(colon == fields)
        colon = 0;
      else
        return lines-1;
     }
     if(fields == SHADOW_FIELDS && c == ' ') //No spaces are allowed in shadow
       return lines;
    }
  }break;
  default:{
  return -1;}
}
return 1000;
}

/*custom atoi function ->
-> this converts string to int, eg, "5" to 5;
-> re-written because the lib function atoi() returns 0 for all non-ints,
 which gets confused with returning 0 for "0"*/
int myAtoi(char* str)
{
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
    return res;
}

/*this function converts char to string, eg, 'o' to "o"*/
void char_to_str(char ch, char str[])
{
  str[0] = ch;
  str[1] = '\0';
}

/*checks if the char is an integer. Eg, '5' is 5 which is an
integer; 't' is a letter.*/
int is_Int(char c)
{
  char str[2];
  int i;
  char_to_str(c,str);
  i = myAtoi(str);
  if(i>=0 && i<10)
   return 0;
  return -1;
}
