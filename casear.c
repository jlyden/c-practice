// Applies 'caesar' code to text user provides, shifting it by user provided 'key'

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int times_ten(int starting_value, int how_many_times);
char apply_cipher_key(int alphabet_end_ascii, int key, int plain_letter);

int main(int argc, string argv[])
{
	string help_text = "Usage: ./caesar key\n";
	int key = 0;
	
    // Offer help if user does not enter only a single 'key'
	if (argc != 2)
	{
		printf("%s", help_text);
		return 1;
	}
	else
	{
		// Evaluate chars of param to see if all are digits
		// Remember, argv[0] is the ./casear command
		int param_length = strlen(argv[1]);

		// Convert 'char' digit(s) to int(s)
		for (int i = 0; i < param_length; i++)
		{
			// Pull out ASCII int value of char
			int param_ascii = (int) argv[1][i];

			// If digit, rebuild the char 'key' as a true int
			if ('0' <= param_ascii && param_ascii <= '9')
			{
				// See explanation of times_ten at bottom
				key += (times_ten((param_ascii - '0'), (param_length - i - 1)));
			}
            else
            {
				// If user didn't enter a positive integer, offer help
				printf("%s", help_text);
	        	return 1;
            }
		}
	}
	
    // Now that we have a 'key', solicit user's input
	string plaintext = get_string("plaintext: ");

	// Set up variable to hold 'ciphertext' output (+1 for \0 at end)
	int text_length = strlen(plaintext);
	char ciphertext[text_length + 1];
    
	// Adjust key so that it is between 1 and 26 (incl)
	if (key >= 26) 
	{
		key = key % 26;
	}

	// If key = 0, no need to do anything - just print original string
	if (key == 0)
	{
		printf("ciphertext: %s\n", plaintext);	
		return 0;
	}
	else
	{
		// For each char of user's input
		for (int i = 0; i < text_length; i++)
		{
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
}

// Recursive method to support transforming a string number into a true int
// Params: starting_value - (int) char which was pulled from user entry
//		   how_many_times - int, how many times to multiply by 10
// Example: '25' becomes 25 by invoking times_ten like this ...
//   times_ten(2, 1) + times_ten (5, 0)
//   (2 * 10) + (5) = 25
int times_ten(int starting_value, int how_many_times)
{   
	if (how_many_times == 0)
	{
		return starting_value;
	}
    else if (how_many_times == 1)
	{
        return starting_value * 10;
    } 
	else 
	{
        return times_ten(starting_value * 10, how_many_times - 1);
    }
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
