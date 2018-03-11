/*==============================================================================================
File:
Project:  
Version:
Programmer:
Description:
===================================================================================================*/

#include "astA4.h"

//
int main()
{

	struct phoneBook PhoneEntries[maxEntries];
	struct phoneBook *newPerson = NULL;

	bool programFlow = true;
	
	int i = 0;
	while (programFlow != false &&  i < maxEntries )
	{
		newPerson = &PhoneEntries[i];
		//functions shall call the next function once in updates phonebook
		// For now I'm having function calls in main just to make it easier on us
		// for debugging purposes.
		programFlow = validateName(newPerson);
		programFlow = validateName(newPerson);
		programFlow = streetAddress(newPerson);
		programFlow = cityValidation(newPerson);
		programFlow = provinceValidation(newPerson);
		programFlow = postalCode(newPerson);
		programFlow = validatePhoneNumber(newPerson);

		i++;
	}


//Before I start making major changes this is my thought.
//Our while loop, loops as long as i < 10 and program flow does not equal false.
//We have a pointer to the struct and make all the data members within our struct pointers.
//In our functional call in main we pass into our function validateName(). 
//When we jump to validateName() if we find the user entered valid input we 
// 1) append the struct doing standard     strcpy(newPerson->name, storeFirstName    strcpy(newPerson->name, storeLastName )
// we will have to make sure that there is a space after first name. 
// 2) now function returns true, allowing loop to continue... Now we jump to the next function streetAddress() . 
// repeat steps


	//please unomment the function call you want to test 


	
	
	
	
	
	



	return 0;
}
