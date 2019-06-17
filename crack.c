// Password cracking tool

#include <cs50.h>
#include <stdio.h>
#include <crypt.h>

int main(int argc, string argv[])
{
    // Validate command-line entry
    if(argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // Unpack this hash - 2 chars (salt) + 11 chars (hash)
    printf("param: %s\n", argv[1]);
	char salt[] = {argv[1][0], argv[1][1], '\0'};
    char hash[12];
    for(int i = 0; i < 11; i++)
    {
        hash[i] = argv[1][2+i];
    }
    hash[11] = '\0';
    
    // Crack hashed password (quickly)
    
    // crypt(key, salt)
    string hash = crypt("LOL", salt);
    printf("hash: %s\n", hash);
    
    // key = user's password (5 char or fewer, alphabetical(upper/lower))
    // salt = two char string from [a-zA-Z0-9./]
    // hashed key = 13 chars, first two chars = salt

    // Take lowest 7 bits of first 8 chars of key = 56 bit key
    // encrypt contstant string - probably all 0000000000
    
    // Print unhashed password\n and return 0

}
