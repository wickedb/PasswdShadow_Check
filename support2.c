#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include"source_prog.h"
#define PASSWD_FIELDS 7
#define SHADOW_FIELDS 8

/*Some fields MUST have integer entries, like the uid or gid.
->This function scans the file, checks the fields that must have ints
and returns the line number if the wrong type is found*/
int int_check(FILE *f, int fields)
{
  rewind(f);
  switch(fields)
  {
    case PASSWD_FIELDS:
    {
      char c;
      int colon=0, line_no = 0;
      c = fgetc(f);
      while((c=fgetc(f))!=EOF){
        if(c == ':')
        {
          colon++;
          continue;}
        if(c == '\n'){
          line_no++;
          colon =0;
          continue;}
        if(colon == 1 && c!= 'x')
           return line_no;
        if(is_Int(c)==0 && (colon == 2 || colon == 3))
        {
         continue;
        }
        else if(is_Int(c)==-1 && (colon == 2 || colon == 3))
        return line_no;
      }
    }break;
    case SHADOW_FIELDS:
    {
      char c;
      int colon=0, line_no = 0;
      c = fgetc(f);
      while((c=fgetc(f))!=EOF){
        if(c == ':')
        {
          colon++;
          continue;}
        if(c == '\n'){
          line_no++;
          colon =0;
          continue;}
        if(is_Int(c)==0 && (colon == 2 || colon == 3 || colon == 4 || colon == 5||colon==6||colon==7))
        {
         continue;
        }
        else if(is_Int(c)==-1 && (colon == 2 || colon == 3|| colon == 4 || colon == 5||colon==6||colon==7))
        return line_no;
      }
    }break;
    default:{
    return -1;}
  }
  return 1000;
}

/*Some fields MUST begin with / entries, like the directories.
->This function scans the file, checks the fields that must have fwd slashes
and returns the line number if the wrong type is found*/
int fwd_slash_check(FILE *fptr, int fields)
{
  rewind(fptr);
  switch(fields)
  {
    case PASSWD_FIELDS:
    {
      char c;
      int colon=0, line_no = 0;
      c = fgetc(fptr);
      while((c=fgetc(fptr))!=EOF){
        if(c == ':')
        {
          colon++;
          continue;}
        if(c == '\n'){
          line_no++;
          colon =0;
          continue;}
        if(c == '/' && (colon == 5 || colon == 6))
        {
         continue;
        }
        else if(c=='/' && (colon == 5 || colon == 6))
        return line_no;
      }
    }break;
    case SHADOW_FIELDS:
    {
      return 1000; //slashes arent mandatory in shadow
    }break;
    default:{
    return -1;
  }
  }
  return 1000;
}

/*This function deletes a line, by skipping it while writing it to another temporary file*/
int delete_line(FILE * fptr,FILE *tmp, int line_no)
{
  rewind(fptr);
  char ch;
  int line_count=0;

      while((ch = fgetc(fptr)) != EOF)
      {
        if(ch == '\n')
          line_count++;
        if(line_count!=line_no)
           fprintf(tmp, "%c", ch);
          else
             continue;
      }
    return 0;
}

/*Removes line at the start of file if its blank*/
void rewrite(FILE * fptr,FILE *tmp, int lno)
{
  rewind(tmp);
  char ch;
  int counter=lno;
      while((ch = fgetc(tmp)) != EOF)
      {
        if(counter != 0)
           fprintf(fptr, "%c", ch);
        counter++;
      }
}

/*This function calls the delete_line() function, then
transfers contents from the temporary file that delete_line() creates
back to the original file*/
int remove_line(FILE *fptr, char * dest_file, int lineno)
{
FILE *tempFile;
tempFile = fopen("delete-line.txt", "w");
fptr = fopen(dest_file,"r+");
delete_line(fptr, tempFile, lineno);
fclose(fptr);
fclose(tempFile);
tempFile = fopen("delete-line.txt", "r");
fptr = fopen(dest_file,"w");
rewrite(fptr, tempFile,lineno);
fclose(tempFile);
fclose(fptr);
return 0;
}

/*This function calls all the checking functions, and triggers deletion of
the line if there's a problem. */
int scan_file(FILE * fptr, char * faddress, int fields)
{
  rewind(fptr);
  int format_test;
  int int_test;
  int slash_test;
  format_test = format_check(fptr,fields);
  int_test = int_check(fptr, fields);
  slash_test = fwd_slash_check(fptr, fields);
  if(format_test != 1000)
  {
    if(format_test == -1){
      printf("Error: Fields set incorrectly to %d\n",fields);
      return 1000;
    }
    printf("FOUND IMPOPER FORMATTING IN LINE %d\n",format_test);
    printf("DELETING LINE %d...\n", format_test);
    delay(1);
    remove_line(fptr, faddress, format_test);
    scan_file(fptr, faddress, fields);
  }
  else if(int_test!=1000){
    if(int_test == -1){
      printf("Error: Fields set incorrectly to %d\n",fields);
      return 1000;
    }
    printf("FOUND INVALID TYPES IN LINE %d\n",int_test);
    printf("DELETING LINE %d...\n", int_test);
    delay(1);
    remove_line(fptr, faddress, int_test);
    scan_file(fptr, faddress, fields);
  }
  else if(slash_test != 1000){
    if(slash_test == -1){
      printf("Error: Fields set incorrectly to %d\n",fields);
      return 1000;
    }
    printf("FOUND IMPOPER / FORMATTING IN LINE %d\n",slash_test);
    printf("DELETING LINE %d...\n", slash_test);
    delay(1);
    remove_line(fptr, faddress, slash_test);
    scan_file(fptr,faddress, fields);
  }
  else
    printf("\nFORMAT AND TYPE CHECK - SUCCESS\n");

  return 1000;
}

