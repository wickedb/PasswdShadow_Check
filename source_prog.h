#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

/*ASSUMPTIONS-> FILE FORMATTING:

-> Spaces are illegal (Exception: passwd field 5)

I) passwd file
 7 fields:
1. Username = Symbols, numbers and alphabets allowed
2. Encrypted password = x
3. UID = Only integers allowed
4. GID = Only integers allowed
5. Username = Symbols, numbers and alphabets allowed. Spaces allowed.
6. Home directory = Starts with /, symbols, numbers and alphabets allowed
7. Command/shell = Starts with /, symbols, numbers and alphabets allowed

II)shadow file
 8 fields:
1. Username = Symbols, numbers and alphabets allowed
2. Encrypted password = Symbols, numbers and alphabets allowed
3. Last password change = Only integers allowed
4. Min days = Only integers allowed
5. Max days = Only integers allowed
6. Warn days = Only integers allowed
7. Inactive days = Only integers allowed (Optional)
8. Expiry days = Only integers allowed (Optional)

III) Notes:
-> If fields are left empty, for eg, root::::::, it is still a valid format
-> If the file exists, but is empty, the format check still returns success
-> This program doesnt make sure the usernames in passwd and shadow match i.e,
any pwconv command functionalities
-> Assuming the txt files scanned have less than 1000 lines, functions in this
program return 1000 on success, and -1 on failure

*/

void print_file(FILE *);
char* concat(const char *, const char *);
void delay(int );
int format_check(FILE *, int );
int myAtoi(char* );
void char_to_str(char , char []);
int is_Int(char );
int int_check(FILE *, int );
int fwd_slash_check(FILE *, int );
int delete_line(FILE * ,FILE *, int);
void rewrite(FILE *,FILE *, int );
int remove_line(FILE *, char * , int );
int scan_file(FILE * , char * , int);

