#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define ALPHABET 26
#define DIGITS 10
#define SYMBOLS 15
#define LOWERSTART 97
#define UPPERSTART 65
#define SYMBOLSTART 33
#define NUMBERSTART 48

void passwordMeter(char password[]);


// arrays
int lowercaseArray[ALPHABET];
int uppercaseArray[ALPHABET];
int numberArray[DIGITS];
int symbolArray[SYMBOLS];


void passwordMeter(char password[])
{
	int score = 0;
	int length = 0;
	int hasAlpha = 0;
	int hasDigit = 0;
	int hasSymbol = 0;

	// initialize all frequency arrays
	for (int i = 0; i < ALPHABET; i++) 
	{
		lowercaseArray[i] = 0;
		uppercaseArray[i] = 0;
	}

	for (int i = 0; i < DIGITS; i++) 
	{
		numberArray[i] = 0;
	}

	for (int i = 0; i < SYMBOLS; i++) {
		symbolArray[i] = 0;
	}

	// Begin scoring
	// flat rate for characters and length
	length = strlen(password);
	score += (length * 4);
	if (length >= 8 )
		score += 2; // meets minimum


	// LOWER CHARACTER SCORE
	// fill lower character array
	for (int i = 0; i < length; i++) 
	{
		if (islower(password[i])) 
		{
			// determine frequency of each lowercase letter
			int ASCIIvalue = (int)(password[i]);
			int offsetPosition = ASCIIvalue - LOWERSTART;
		
			++lowercaseArray[offsetPosition];
		}
	}

	// calculate additions to score
	int lowerTotal = 0;
	for (int i = 0; i < ALPHABET; i++) 
		lowerTotal += lowercaseArray[i];
	
	if (lowerTotal) 
	{
		score += (unsigned)(length - lowerTotal) * 2;
		hasAlpha = 1; 
		score += 2; // meets minimum
	}


	// calculate deductions from score
	// if only letters (upper or lower)
	int numberOfLetters = 0;
	
	// check for sequential letters (upper or lower)
	for (int i = 0; i < length - 2; i++) 
	{
		if (isalpha(password[i])) 
		{
			numberOfLetters += 1;
			hasAlpha=1;
		}
		
		if (isalpha(password[i]) && 
			isalpha(password[i+1]) && 
			isalpha(password[i+2])) 
		{
			if (( (int)tolower(password[i]) ) ==  
				( (int)tolower(password[i+1]) - 1 ) == 
				( (int)tolower(password[i+2]) - 2 ) )
			{
					score -= 3;
			}
		}
		// check for consecutive lowercase letters
		if ( islower(password[i]) && 
			islower(password[i+1]) )
		{
			score -= 2;
		}
	}
	
	// if only letters (upper or lower)
	if (numberOfLetters == length) 
		score -= length;

	// UPPERCASE CHARACTER SCORE
	// fill array
	for (int i = 0; i < length; i++) 
	{
		if (isupper(password[i])) 
	  {
			int ASCIIvalue = (int)(password[i]);
			int offsetPosition = ASCIIvalue - UPPERSTART;
		
			++uppercaseArray[offsetPosition];
		}
	}

	// calculate uppercase additions to score
	int upperTotal = 0;
	for (int i = 0; i < ALPHABET; i++) 
	{
		upperTotal += uppercaseArray[i];
	}
	
	if (upperTotal) 
	{
		score += (unsigned)(length - upperTotal) *2;
		score += 2; // meets minimum
	}

	// calculate deductions from score
	// consecute uppercase letters
	for (int i = 0; i < length-1; i++) 
	{
		if ( isupper(password[i]) && 
			isupper(password[i+1]) )
		{
			score -= 2;
		}
	}

	// SYMBOL CHARACTER SCORE
	// fill frequency array
	for (int i = 0; i < length; i++) 
	{
		if (ispunct(password[i])) 
	  {
			int ASCIIvalue = (int)(password[i]);
			int offsetPosition = ASCIIvalue - SYMBOLSTART;
			hasSymbol =1;
			++symbolArray[offsetPosition];
		}
	}

	// score for symbol
	for (int i = 0; i < length; i++) 
	{
		if (ispunct(password[i]))
			score += 6;
	}

	// subtract for sequential symbols
	for (int i = 0; i < length-2; i++) 
	{
		if (ispunct(password[i]) &&
			ispunct(password[i+1]) && 
			ispunct(password[i+2])) 
		{
			if (( (int)(password[i]) ) == 
				( (int)(password[i+1]) - 1 ) == 
				( (int)(password[i+2]) - 2 ) )
			{
				score -= 3;
			}
		}
	}

	// NUMBER CHARACTER SCORE
	// fill array
	for (int i=0; i <length; i++) 
	{
		if (isdigit(password[i])) 
		{
			int ASCIIvalue = (int)(password[i]);
			int offsetPosition = ASCIIvalue - NUMBERSTART;
			++numberArray[offsetPosition];
			hasDigit = 1; 
	  `	}
	}

	// number score conditional on other types available
	if (hasAlpha || hasSymbol) 
	{
		for (int i = 0; i < length; i++) 
		{
			if (isdigit(password[i]))
			{
				score += 6;
			}
		}
	}


	// subtraction for consecutive numbers
	for (int i = 0; i < length-1; i++) 
	{
		if (isdigit(password[i]) && 
			isdigit(password[i+1]))
		{
			score -= 2;
		}
	}

	// subtraction for sequential numbers
	for (int i = 0; i < length-2; i++) 
	{
		if (isdigit(password[i]) &&
			isdigit(password[i+1]) && 
			isdigit(password[i+2])) 
		{
			if (( (int)(password[i]) ) == 
				( (int)(password[i+1]) - 1 ) == 
				( (int)(password[i+2]) - 2 ) )
			{
				score -=3;
			}
		}
	}

	// subtraction for numbers only
	int numberOfDigits = 0;
	for (int i = 0; i < length; i++) 
	{
		if (isdigit(password[i])) 
		{
			numberOfDigits += 1;
			hasAlpha = 1;
		}
	}	
	
	if (numberOfDigits == length) 
		score -= length;

	// score addition for symbols/numbers in middle
	for (int i = 1; i < length-1; i++) 
	{
		if (isdigit(password[i]))
			score += 2;
		if (ispunct(password[i]))
			score += 2;
	}

	// tabulate score
	if (score < 50)
		printf("\n\nScore %d: Very Poor", score);
	else if (score >= 50 && score < 75)
		printf("\n\nScore %d: Poor", score);
	else if (score >= 75 && score < DIGITS0)
		printf("\n\nScore %d: Moderate", score);
	else if (score >=DIGITS0 && score < 125)
		printf("\n\nScore %d: Good", score);
	else if (score >=125 && score < SYMBOLS0)
		printf("\n\nScore %d: Very Good", score);
	else if (score >= SYMBOLS0)
		printf("\n\nScore %d: Excellent", score);

}