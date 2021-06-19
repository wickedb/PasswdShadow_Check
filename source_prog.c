/*This program checks that all entries in passwd and shadow have the proper format
and contain valid data.

A more detailed description given in the source_prog.h file*/

#include<stdio.h>
#include<errno.h>
#include "source_prog.h"

#define MAX 256
#define PASSWD_FIELDS 7
#define SHADOW_FIELDS 8

int main(void)
{
  char folder_address[MAX];
  if (getcwd(folder_address, sizeof(folder_address)) != NULL) {
      printf("Current working dir: %s\n", folder_address);
  } else {
      perror("getcwd() error");
      return 1;
  }
  char *env_address;
  env_address = concat("PFILE=",folder_address);

  //setting environment variable
  char *env_var;
  env_var = getenv("PFILE");
  putenv(env_address);
  env_var = getenv("PFILE");
  printf("\nPFILE set to = %s\n(Please make sure the txt files are stored here)\n\n",env_var);

  char passwd_filename[MAX],shadow_filename[MAX];

  //input from user
  printf("Enter passwd file name (eg, : /passwdx.txt)\n");
  scanf("%s", passwd_filename);
  char * passwd_address = concat(env_var,passwd_filename);
  FILE *fpasswd;
  fpasswd = fopen(passwd_address,"r+");
   if (!fpasswd)
  {
          fprintf(stderr, "Passwd file error: %s\n", strerror(errno));
          return 0;
  }

  //input from user
  printf("Enter shadow file name (eg, : /shadowx.txt)\n");
  scanf("%s", shadow_filename);
  char * shadow_address = concat(env_var,shadow_filename);
  FILE *fshadow;
  fshadow = fopen(shadow_address,"r");
  if (!fshadow)
  {
          fprintf(stderr, "Shadow file error:  %s\n", strerror(errno));
          return 0;
  }

  printf("\nMENU:\n1.View files\n2.Scan files\n");
  printf("Enter choice: \n");
  int choice;
  scanf("%d",&choice);

  switch (choice) {
    case 1: /*prints the files*/
    {
      printf("@@@@PRINTING PASSWD\n\n");
      print_file(fpasswd);
      printf("\n\n");

      printf("@@@@PRINTING SHADOW\n\n");
      print_file(fshadow);
      printf("\n\n");
    }break;
    case 2:/*scans the files for improper formatting or illegal entries*/
    {
      printf("\n\n@@@@SCANNING PASSWD\n");
      scan_file(fpasswd,passwd_address, PASSWD_FIELDS);
      printf("\n\n@@@@SCANNING SHADOW\n");
      scan_file(fshadow,shadow_address, SHADOW_FIELDS);

    }break;
    default:
    printf("Wrong choice!\n");
  }

  fclose(fpasswd);
  fclose(fshadow);

  return 0;
}



