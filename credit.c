// Reports the card type of a inputed valid credit card number, or Invalid

#include <cs50.h>
#include <stdio.h>

int limited_digit_count(long big_number);
int credit_card_validation (long big_number, int digit_count);
string get_credit_card_type(int digit_count, int first_two_digits);

int main(void)
{
    // Prompt user for input with 'get_long'
    long user_number = get_long("Number: ");
    
    // Check length of number
	// limited_digit_count() returns 0 if len not 13, 15, or 16, hence INVALID
    int digit_count = limited_digit_count(user_number);
    if (digit_count == 0)
    {
        printf("INVALID\n");
    }
    else 
    {
        // Then use checksum to determine if this is a valid cc number
        int first_two_digits = credit_card_validation(user_number, digit_count);
        // credit_card_validation() returns 0 if it fails, hence INVALID!
        if (first_two_digits == 0) 
        {
            printf("INVALID\n");
        } else 
		{
        // Since credit_card_validation() returns first two digits of card 
		//   number if valid, determine type of card
		string cardType = get_credit_card_type(digit_count, first_two_digits);
        printf("%s", cardType);
		}
    }
}

// Returns whether 'big_number' has 13, 15, or 16 digits 
// (or 0 if any other digit count)
int limited_digit_count(long big_number)
{
    // Initialize digit_count to 0; updated to 13, 15, or 16 if applicable 
    int digit_count = 0;
    if(1000000000000 < big_number && big_number < 9999999999999)
    {
        digit_count = 13;
    }
    else if(100000000000000 < big_number && big_number < 999999999999999)
    {
        digit_count = 15;
    }
    else if(1000000000000000 < big_number && big_number < 9999999999999999)
    {
        digit_count = 16;
    }
    return digit_count;
}

// Returns first two digits if big_number is a valid credit card number, 
// 0 if not
int credit_card_validation (long big_number, int digit_count)
{
    // Declare variables to record the sum of 'outside' digits 
	//   (alternates starting with last)
    // and 'inside' digits (alternates starting with second to last)
	// and the first two digits of card number (for determining card type)
    int sum_outside = 0;
    int sum_inside = 0;
    int first_two_digits = 0;

    // Loop through the credit card number
    for (int i=0; i<digit_count; i++)
    {
		int digit_to_process = big_number % 10;
		
		// Store last two digits processed (== first two digits of card number)
		if(i == digit_count - 2)
		{
			// Second to last digit is 'ones' place of our return value
			first_two_digits = digit_to_process;
		} else if (i == digit_count - 1)
		{
			// Final digit will be the 'tens' place of our return value
			first_two_digits += digit_to_process*10;
		}
		
        // Sum outside digits
        if(i % 2 == 0)
        {
            sum_outside += digit_to_process;
        }
        // For each inside digit ... 
        else if (i % 2 == 1)
        {
            // Double the inside digit
            int inside_digit_doubled = 2 * (digit_to_process);
            // Now sum the digits of the doubling (it can't be greater than 18)
            // If it's a two digit number, sum both digits
            if (inside_digit_doubled > 9) 
			{
                // add ones digits
                sum_inside += inside_digit_doubled % 10;
                // add tens digits
                sum_inside += inside_digit_doubled / 10;
            }
            // If one digit number, just add it
            else 
			{
                sum_inside += inside_digit_doubled;
            }
        }
		// Strip off the final digit so next digit processed on next loop
        big_number = big_number / 10;
    }

    // If result of (sum_outside + sum_inside) % 10 = 0, card is valid!
	// Return first_two_digits to determine later what kind of card it is
    if ((sum_outside + sum_inside) % 10 == 0)
    {
        return first_two_digits;
    }
	// Otherwise, return 0, which signals invalid.
    else
    {
        return 0;
    }
}

// Returns type of card based on card number digit count 
//   and first two digits of valid card number
string get_credit_card_type(int digit_count, int first_two_digits){
	// Output AMEX\n or MASTERCARD\n or VISA\n or INVALID\n with printf
	string cardType;
	if(digit_count == 15 && (first_two_digits == 34 || first_two_digits == 37))
	{
		cardType = "AMEX\n";
	} else if (digit_count == 16 
		&& (first_two_digits > 50 && first_two_digits < 56))
	{
		cardType = "MASTERCARD\n";
	} else if ((digit_count == 13 || digit_count == 16) 
		&& (first_two_digits > 39 && first_two_digits < 50))
	{
		cardType = "VISA\n";
	} else 
	{
		cardType = "INVALID\n";
	}
	return cardType;
}