# PasswdShadow_Check

Checks if the entered passwd/shadow linux command has a valid syntax

# ASSUMPTIONS - FILE FORMATTING
 -> Spaces are illegal (Exception: passwd field 5)
## I) passwd file
 7 fields:
1. Username = Symbols, numbers and alphabets allowed
2. Encrypted password = x
3. UID = Only integers allowed
4. GID = Only integers allowed
5. Username = Symbols, numbers and alphabets allowed. Spaces allowed.
6. Home directory = Starts with /, symbols, numbers and alphabets allowed
7. Command/shell = Starts with /, symbols, numbers and alphabets allowed

## II) shadow file
 8 fields:
1. Username = Symbols, numbers and alphabets allowed
2. Encrypted password = Symbols, numbers and alphabets allowed
3. Last password change = Only integers allowed
4. Min days = Only integers allowed
5. Max days = Only integers allowed
6. Warn days = Only integers allowed
7. Inactive days = Only integers allowed (Optional)
8. Expiry days = Only integers allowed (Optional)

## III) Notes:
* If fields are left empty, for eg, root::::::, it is still a valid format
* If the file exists, but is empty, the format check still returns success
* This program doesnt make sure the usernames in passwd and shadow match i.e,
any pwconv command functionalities
* Assuming the txt files scanned have less than 1000 lines, functions in this
program return 1000 on success, and -1 on failure

