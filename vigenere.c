#include <cs50.h>
#include <stdio.h>
#include <string.h>

int shift(char c);
char apply_cipher_key(int alphabet_end_ascii, int key, int plain_letter);

int main(int argc, string argv[])
{
	string help_text = "Usage: ./vigenere keyword\n";
	
    // Offer help if user does not enter only a single 'key'
	if (argc != 2)
	{
		printf("%s", help_text);
		return 1;
	}
	// Validate argv parameter - should be all alphabetical
	int param_length = strlen(argv[1]);
	for (int i = 0; i < param_length; i++)
	{
		int param_ascii = (int) argv[1][i];
		if (('a' <= param_ascii && param_ascii <= 'z')
			|| ('A' <= param_ascii && param_ascii <= 'Z'))
		{
			// Keep going
		}
        else
        {
			// If user didn't enter a alphabetical char, offer help
			printf("%s", help_text);
        	return 1;
        }
	}
	// Solicit plaintext
	string plaintext = get_string("plaintext: ");

	// Set up variable to hold 'ciphertext' output (+1 for \0 at end)
	int text_length = strlen(plaintext);
	char ciphertext[text_length + 1];
 
	// Apply cipher
	// For each char of user's input
	for (int i = 0; i < text_length; i++)
	{
		// Set up key int based on keyword letter
		int key_length = strlen(argv[1]);
		// TODO: This isn't quite right
		int key = shift(argv[1][i % key_length]);

		// Transform char to int
		int plain_letter = (int) plaintext[i];
		
		// Handle 'char' whether it is uppercase  or lowercase
		if ('A' <= plain_letter && plain_letter <= 'Z')
		{
			ciphertext[i] = apply_cipher_key('Z', key, plain_letter);
		}
		else if ('a' <= plain_letter && plain_letter <= 'z')
		{
			ciphertext[i] = apply_cipher_key('z', key, plain_letter);
		}
		else 
		{
			// If 'char' is not a letter, add it as-is to cipertext array
			ciphertext[i] = plaintext[i];
		}
	}
	// End the char array with \0
	ciphertext[text_length] = '\0';

	// Print out the cipertext for the user, and end program
	printf("ciphertext: %s\n", ciphertext);
	return 0;
}

int shift(char c)
{
	int int_key = 0;
	// Handle uppercase
	if ('A' <= c && c <= 'Z')
	{
		int_key = c % 65;
	}
	// Handle lowercase
	else if ('a' <= c && c <= 'z')
	{
		int_key = c % 97;
	}
	return int_key;
}

// Method to transform the provided char to the cipher char
// Params: alphabet_end_ascii - int, either 'Z' or 'z'
//		   key - int based on user entry
//		   plain_letter - (int) char from the user plaintext to encode
// Example: Letter to change is 'y' and key is 5
//			So end_of_alphabet = 'z' - 'y' = 1
// 			End_of_alphabet < key (1 < 5)
// 			So our new letter is ('z' - 26) + (5 - 1) = 'a' + 4 = 'd'
char apply_cipher_key(int alphabet_end_ascii, int key, int plain_letter)
{
	char cipher_letter;
	
	int end_of_alphabet = alphabet_end_ascii - plain_letter;

	if (end_of_alphabet < key) {
		// Handle wrap-around
		cipher_letter = (alphabet_end_ascii - 26) + (key - end_of_alphabet);
	}
	else
	{
		// Or just add the key, if wrap-around is not an issue
		cipher_letter = plain_letter + key;
	}

	return cipher_letter;
}
