#include "passMeter.h"

#define MAX 20

// define array for holding the password, and a small array for Y/N answers in menu
char password[MAX]="";
char answer[2]="";

// function prototypes
void menu             (void);
void addCharacter     (char password[]);
void addNumber        (char password[]);
void addSymbol        (char password[]);
void addMix           (char password[]); 

void generatePassword (char password[], 
                       int length, 
                       int useCharacters, 
                       int useNumbers, 
                       int useSymbols, 
                       int useMixed);

int isValid			  (char password[], 
                       int length, 
                       int useCharacters, 
                       int numbers, 
                       int symbols, 
                       int mixed);

int answerIsValid	  (char answer[]);

// checks for invalid input from user
int answerIsValid(char answer[])
{
	if (answer[0] == 'Y' || answer[0] == 'y' ||
		answer[0] == 'N' || answer[0] == 'n')
	{
		return 1;
	}
	
	printf("\nInvalid input.\n\n");
	return 0;
}
			

// main menu function
void menu(void)
{
	// seed randomizer once
	srand(time(NULL));

	// print directions
	printf("Password generator: "
			"\n\t1) Length (max 20)"
			"\n\t2) include useCharacters? [Y/N]"
			"\n\t3) include numbers? [Y/N]"
			"\n\t4) include punctuation? [Y/N]"
			"\n\t5) include upper case? [Y/N]"); 

	// variables and flags
	int check,
		length = 0, 
		requiredLength = 0, 
		useCharacters = 0, 
		useNumbers = 0, 
		useSymbols = 0, 
		useMixed= 0;

	// do...while for menu to keep it within paramters
	do 
	{
		printf("\n\nLength?: ");
		scanf("%d", &length);
		if (length > MAX )
		{
		  printf("Too long!\n");
		  continue;
		}
		
		if (length <= 0)
		{
			puts("That didn't work. Try a different number.\n");
			continue;
		}
		
		do
		{
			printf("Characters? [Y/N]: ");
			scanf("%s", answer);	
			if (answer[0] == 'Y' || answer[0] == 'y') 
			{
			  useCharacters = 1; 
			  requiredLength++;
			}
		}
		while (!answerIsValid(answer));
		
		do
		{
			printf("Numbers? [Y/N]: ");
			scanf("%s", answer);
			if (answer[0] == 'Y' || answer[0] == 'y') 
			{
			  useNumbers= 1;  
			  requiredLength++;
			}
		}
		while(!answerIsValid(answer));

		do
		{
			printf("Punctuation? [Y/N]: ");
			scanf("%s", answer);
			if (answer[0] == 'Y' || answer[0] == 'y') 
			{
			  useSymbols= 1; 
			  requiredLength++;
			}
		}
		while (!answerIsValid(answer));

		do
		{
			printf("Upper case? [Y/N]: ");
			scanf("%s", answer);
			if (answer[0] == 'Y' || answer[0] == 'y') 
			{
			  useMixed= 1; 
			  requiredLength++;
			}
		}
		while (!answerIsValid(answer));
		
		// check to make sure the length is enough to cover chosen parameters
		if (length < requiredLength) 
		{
		  printf("\n\nCannot generate a password limited by length %d.", length);
		}
		
		// checks to make sure some choices were selected
		else if (!(useCharacters + useNumbers + useSymbols + useMixed))
		{
		  puts("Cannot generate password without parameters. Please enter Y or N for your choices.");
		}
	} // end do
	// while loop repeats if length is too short or no flags are selected.
	while(length < requiredLength || 
		  !(useCharacters +
		  useNumbers +
		  useSymbols + 
		  useMixed));

	// do...while for generating a valid password
	do 
	{
		generatePassword(password,  
					     length, 
					     useCharacters,
					     useNumbers, 
					     useSymbols, 
					     useMixed);
	} 
	// based on whether password passes the validity algorithms
	while (!(isValid(password, 
					 length, 
					 useCharacters, 
					 useNumbers, 
					 useSymbols, 
					 useMixed)));

	printf("\n\nYour password is: [ %s ]\n", password);

	do
	{
		printf("\n\nWould you like to rate your password?\n[Y/N]: ");
		scanf("%s", answer);
		int check = answerIsValid(answer);

		if (answer[0] == 'Y' || answer[0] == 'y') 
		{
			passwordMeter(password);
		}
		
		if (answer[0] == 'N' || answer[0] == 'n')
			puts("\nThank you. Exiting.\n");
	}
	while (!answerIsValid);
}

// develop generation function
void generatePassword (char password[], 
                       int length, 
                       int useCharacters, 
                       int useNumbers, 
                       int useSymbols, 
                       int useMixed) 
{
	// clears any existing terms in password array
	strcpy(password, "");
	// while loop restrained until array develops enough elements to be correct chosen size.
	while (strlen(password) != length) 
	{	
		// randomizer for adding on certain types of elements to password array, 
		// based on if the function is flagged as on or not
		switch ((1+rand()%4)) {
			case 1: 
			if(useCharacters) 
				addCharacter(password);
			break;

			case 2:
			if(useNumbers) 
				addNumber(password);
			break;

			case 3: 
			if(useSymbols)
				addSymbol(password);
			break;


			case 4: 
			if(useMixed)
				addMix(password);
			break;      
		} //end switch
	} //end while
}

// validity checker
int isValid(char password[], 
            int length, 
            int useCharacters, 
            int useNumbers, 
            int useSymbols, 
            int useMixed) 
{
	// Flags are used to ensure that called functions indeed added a character.
	int characterFlag = 0, 
		digitFlag = 0, 
		punctFlag = 0, 
		upperFlag = 0; 
	// iterate over length of password
	for (int i = 0; i < length; i++) 
	{
		// checks if addCharacter() was called
		if (useCharacters && isalpha(password[i])) 
		{
			if(islower(password[i]))
			{
				characterFlag = 1;
				continue;
			}
			
			// checks for addMix() and if an uppercase is present
			if (useMixed && isupper(password[i])) 
			{
				upperFlag = 1;
				continue;
			}
		}
		
		// checks for addNumber() and if a digit is present
		if (useNumbers && isdigit(password[i]))
		{
			digitFlag = 1;
			continue;
		}
		
		
		// checks for addSymbol() and if a symbol is present
		if (useSymbols && ispunct(password[i]))
		{
			punctFlag = 1;
		}
	} // end for loop

  // final if checklist returns 0 if password is not valid, or 1 if it passes all the checks.
	if ((useCharacters && !characterFlag) ||
		(useNumbers && !digitFlag) ||
		(useSymbols && !punctFlag) ||
		(useMixed && !upperFlag))
			return 0;
    
	return 1;
}


// addNumber for digits
void addNumber (char password[MAX])
{  
	//create placeholder array that is empty and holds only 1 character.
	char placeholder[2]="";
	
	//add a random number to 0 position 
	placeholder[0]=(48 + rand()%10);
	
	//append to the end of password
	strcat(password, placeholder);
}

// all further addFunctions behave as described above
// addCharacter basic letters
void addCharacter (char password[MAX]) 
{
	char placeholder[2]="";
	placeholder[0]=(97 + rand()%26);
	strcat(password, placeholder);
}

// addSymbol for odd characters
void addSymbol (char password[MAX]) 
{  
	char placeholder[2]="";
	placeholder[0]=(33 + rand()%15);
	strcat(password, placeholder);
}

// addMix for upper/lower case
void addMix (char password[MAX]) 
{	
	char placeholder[2]="";
	placeholder[0]=(65 + rand()%26);
	strcat(password, placeholder);
}


	