/*==============================================================================================
File:
Project:
Version:
Programmer:
Description:
===================================================================================================*/

#include "astA4.h"
//

/*================================================================================================
Function:  
Description:
Parameters:
Return Values:
=================================================================================================*/
bool validateName()
{

	bool returnValue = false;

	char holdTheFirstName[kExcessSize] = { 0 };
	char storeFirstName[kExcessSize] = { 0 };
	char holdTheSecondName[kNameLimit] = { 0 };
	char storeSecondName[kNameLimit] = { 0 };


	int validateFirstName = 0; //will be used for the strlen
	int validateLastName = 0; //will be used for the strlen


	printf("Please Enter Your First Name: ");
	fgets(holdTheFirstName, kExcessSize, stdin); //we are letting the user enter how many characters they want
	clearCRLF(holdTheFirstName); //cleaning '\n'

	validateFirstName = strlen(holdTheFirstName); //get the string length


	if (validateFirstName == 0) //if the first name is blank
	{
		printf("ERROR: Sorry, your first name cannot be blank\n");
		returnValue = false;

	}
	else //the first name is not blank - we can continue...
	{
		if (validateFirstName > kNameLimit) //if the length that the user entered for the first name is more than accepted - erroor
		{
			printf("ERROR: You exceeded the number of characters for the first name \n");
			returnValue = false;
		}
		else //the length of the first name is in the correct range, we can continue with the program
		{
			if (sscanf(holdTheFirstName, "%[a-z A-z . ']s", &storeFirstName) == 1) //check if the characters for the first name are correct - continue
			{
				validateFirstName = strlen(holdTheFirstName); //check the length

				int checkParsed = 0;
				checkParsed = strlen(storeFirstName);

				if (checkParsed == validateFirstName) //comparing the size of the string before it is parsed by sscanf and then after it - if same same sscanf didn't find invalid characters
				{

					printf("Please Enter Your Last Name: "); //there are acceptable characters, lets continue
					fgets(holdTheSecondName, kNameLimit, stdin);
					clearCRLF(holdTheSecondName); //clear '\n'

					validateLastName = strlen(holdTheSecondName);

					if (validateLastName == 0) //check if the second name is blank
					{
						printf("ERROR: Sorry, your last name cannot be blank\n");
						returnValue = false;
					}
					else //the second name is not blank
					{
						if (validateLastName > kNameLimit)
						{
							printf("ERROR: You exceeded the number of characters for the last name \n");
							returnValue = false;
						}
						else
						{
							if (sscanf(holdTheSecondName, "%[a-z A-z . ']s", &storeSecondName) == 1)  //check if the characters for the first name are correct - continue
							{
								validateFirstName = strlen(holdTheSecondName); //check the length

								int checkParsed = 0;
								checkParsed = strlen(storeSecondName);

								if (checkParsed == validateFirstName) //comparing the size of the string before it is parsed by sscanf and then after it - if same same sscanf didn't find invalid characters
								{
									printf("Your first name is [ %s ]\n", storeFirstName); //print the first name
									printf("Your last name is [ %s ]\n", storeSecondName); //print the second name
									returnValue = true; //the has not trolled us so far - we can return true :)
								}
								else
								{
									printf("ERROR: [%s] is an invalid input\n", holdTheSecondName); //characters for the last name are not corret - exit
									returnValue = false;
								}
							}	
						}
					}
				} //first name, successfully parsed by sscanf
				else  //characters for the first name are not corret - exit
				{
					printf("ERROR: [%s] is an invalid input\n", holdTheFirstName);
					returnValue = false;
				}
			} //end of sscanf for the first name
			
		} //end of else if the first name was in the correct range 
			
	} //end of else if the first name was not blank

	
	return returnValue;
}





/*================================================================================================
Function:
Description:
Parameters:
Return Values:
=================================================================================================*/
bool streetAddress()
{

	bool returnValue = false;
	
	printf("Please Enter a street address: ");
	char streetAddress[kExcessSize];
	fgets(streetAddress, kExcessSize, stdin);
	clearCRLF(streetAddress);

	int streetLength = strlen(streetAddress);
	
	char streetTypes[4][5]
	{
		{ "RR" },
		{ "R.R." },
		{ "PO" },
		{ "P.O." }
	};
	char invalidPosition[3][1]
	{
		{ '.' },
		{ '-' },
		{ ' ' }
	};

	
	//check for street length greater than 60
	if (streetLength > kMaxStreetLength)
	{
		printf("ERROR: You many not enter a street that is greater than 60 characters.");
		returnValue = false;
	}

	//check for input at invalid positions
	char* oneCharacter = streetAddress;
	for (int i = 0; i < streetLength; i++)
	{
		//dot is invalid for start of street address
		if ((oneCharacter[0] == *invalidPosition[i + 1]))
		{
			printf("ERROR: You may not enter a '.' for the start of the street address.");
			returnValue = false;
		}
		// dot can be entered at the end of a street address
		else if ((oneCharacter[0] == *invalidPosition[i]) || (oneCharacter[streetLength - 1] == *invalidPosition[i + 1]))
		{
			printf("ERROR: You may not enter a space OR a '-' at the start or end of a street address. \n ");
			returnValue = false;
		}
	}

	//checking for multiple hyphens, spaces or periods in a row
	for (int i = 0; i < streetLength; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((oneCharacter[i] == *invalidPosition[j]) && (oneCharacter[i + 1] == *invalidPosition[j]))
			{
				printf("ERROR: You may not enter a space OR a '-' OR '.' consecutively... \n");
				returnValue = false;
			}
		}
	}

	//checking for character appearing 5 times
	for (int i = 0; i < streetLength; i++)
	{
		if (isalpha(oneCharacter[i]))
		{
			if ((oneCharacter[i] == oneCharacter[i + 1]) && (oneCharacter[i] == oneCharacter[i + 2]) &&
				(oneCharacter[i] == oneCharacter[i + 3]) && (oneCharacter[i] == oneCharacter[i + 4]))
			{
				printf("ERROR: You many not enter a character 5 times in a row.");
				returnValue = false;
			}
		}

	}


	return returnValue;
}




/*================================================================================================
Function:
Description:
Parameters:
Return Values:
=================================================================================================*/
bool cityValidation()
{

	printf("Please enter a city: ");
	char cityPassed[kExcessSize];
	fgets(cityPassed, kExcessSize, stdin);
	clearCRLF(cityPassed);

	char cityPrint[kMaxCityLength] = { "\0" };
	char foundGarbage[kMaxCityLength] = { "\0" };
	bool retValue = false;
	int userPassedLength = 0;
	int parsedLength = 0;

	userPassedLength = strlen(cityPassed);
	if (userPassedLength == 0)
	{
		printf("ERROR: your input cannot be blank\n");
	}
	else
	{
		if (userPassedLength >= 0 && userPassedLength <= kMaxCityLength)
		{
			if (sscanf(cityPassed, "%[A-Za-z.,0-9 ]", &cityPrint))
			{
				parsedLength = strlen(cityPrint);
				if (parsedLength == userPassedLength)
				{
					printf("%s", cityPrint);
					retValue = true;
				}
				else
				{
					printf("ERROR: Sorry, invalid input\n");
					retValue = false;
				}
			}
			else
			{
				printf("ERROR: Sorry, invalid input\n");
				retValue = false;
			}
		}
	}

	return retValue;
}


/*================================================================================================
Function:
Description:
Parameters:
Return Values:
=================================================================================================*/

bool provinceValidation()
{
	bool returnValue = false;
	int checkLength = 0;

	printf("Please enter a Canadian Province: ");
	char provinces[kExcessSize];
	fgets(provinces, kExcessSize, stdin);
	clearCRLF(provinces);


	char provinceCodes[provinceNumber][provinceCodeLength + 1]
	{
		{ "AB" },
	{ "BC" },
	{ "MB" },
	{ "NB" },
	{ "NL" },
	{ "NS" },
	{ "NT" },
	{ "NU" },
	{ "ON" },
	{ "PE" },
	{ "QC" },
	{ "SK" },
	{ "YT" }
	};
	char provinceNames[provinceNumber][provinceNameLength]
	{
		{ "Alberta" },
		{ "British Columbia" },
		{ "Manitoba" },
		{ "New Brunswick" },
		{ "Newfoundland and Labrador" },
		{ "Nova Scotia" },
		{ "Northwest Territories" },
		{ "Nunavut" },
		{ "Ontario" },
		{ "Prince Edward Island" },
		{ "Quebec" },
		{ "Saskatchewan" },
		{ "Yukon" }
	};
	char provinceShortNames[provinceNumber][provinceNameLength]
	{
		{ "Alta" },
		{ "B.C." },
		{ "Man" },
		{ "N.B" },
		{ "N.L" },
		{ "N.S." },
		{ "N.W.T" },
		{ "Nut" },
		{ "Ont" },
		{ "P.E.I." },
		{ "Que" },
		{ "Sask" },
		{ "Yuk" }
	};

	checkLength = strlen(provinces);
	if (checkLength < provinceCodeLength)
	{
		returnValue = false;

	}
	else if (checkLength == provinceCodeLength)
	{
		for (int i = 0; i < provinceNumber; i++)
		{
			if ((stricmp(provinces, provinceCodes[i])) == 0)
			{
				printf("%s", provinceCodes[i]);
				returnValue = true;
			}
		}
	}
	else if (checkLength > provinceCodeLength && checkLength < provinceNameLength)
	{
		for (int i = 0; i < provinceNumber; i++)
		{
			//check for short form names and also province names
			if ((stricmp(provinces, provinceNames[i])) == 0 || (stricmp(provinces, provinceShortNames[i])) == 0)
			{
				printf("%s", provinceNames[i]);
				returnValue = true;
			}
		}
	}

	return returnValue;
}


/*================================================================================================
Function:
Description:
Parameters:
Return Values:
=================================================================================================*/

bool postalCode()
{
	printf("Please enter a postal code: ");
	char postalPassed[kExcessSize];
	fgets(postalPassed, kExcessSize, stdin);
	clearCRLF(postalPassed);

	char postalParsed[postalCodeLength + 1] = { '\0' };

	int postalLength = 0;
	int parsedPostalLength = 0;
	char junkArray[kExcessSize] = { "" };
	int junkArrayInt[kExcessSize] = { 0 };
	postalLength = strlen(postalPassed);
	bool retValue = false;


	if (postalCodeLength == postalLength)
	{
		char* oneCharacter = &postalPassed[3];
		//check for space at index 3
		if (*oneCharacter == ' ')
		{
			// check for characters at correct positions
			if (sscanf(postalPassed, "%c %c %c", &junkArray[0], &junkArray[2], &junkArray[5]) == 3)
			{
				//check for decimal at correct positions
				if (sscanf(postalPassed, "%d %d %d", &junkArrayInt[1], &junkArrayInt[4], &junkArrayInt[6]) == 3)
				{
					//check for unacceptable postal letters
					if (sscanf(postalPassed, "%[^OQUDFIoqudfi]", &postalParsed) == 1)
					{
						parsedPostalLength = strlen(postalParsed);

						if (parsedPostalLength == postalCodeLength)
						{
							//check for unnaceptable postal letters at index 0
							oneCharacter = &postalParsed[0];
							if (*oneCharacter != 'W' && *oneCharacter != 'Z' && *oneCharacter != 'w' && *oneCharacter != 'z')
							{
								printf("my postal code %s \n", postalParsed);
								retValue = true;
							}
							else
							{
								printf("ERROR: Postal codes do not begin with W or Z\n");
								retValue = false;
							}
						}
						else
						{
							printf("ERROR: You have entered an invalid character \n");
							retValue = false;
						}
					}
					else
					{
						printf("ERROR:You have entered an invalid character \n");
						retValue = false;
					}
				}

			}
		}
		else
		{
			printf("ERROR: There needs to be a space after the 3rd letter \n");
			retValue = false;
		}

	}
	return retValue;
}



/*================================================================================================
Function:
Description:
Parameters:
Return Values:
=================================================================================================*/
bool validatePhoneNumber()
{
	bool returnValue = false;
	int digitValidator = kInvalid;
	char numInput[kExcessSize] = { 0 };
	char holdTheNum[kExcessSize] = { 0 };
	int numSize = 0; //this variable will check the size of the input
	int i = 0;

	//multi-dimensional array with the first three digits
	char myDigits[40][4] =
	{
		{ "403" },
	{ "587" },
	{ "780" },
	{ "825" },
	{ "236" },
	{ "250" },
	{ "604" },
	{ "778" },
	{ "204" },
	{ "431" },
	{ "506" },
	{ "709" },
	{ "902" },
	{ "782" },
	{ "226" },
	{ "249" },
	{ "289" },
	{ "343" },
	{ "365" },
	{ "416" },
	{ "437" },
	{ "519" },
	{ "548" },
	{ "613" },
	{ "647" },
	{ "705" },
	{ "807" },
	{ "905" },
	{ "418" },
	{ "438" },
	{ "450" },
	{ "514" },
	{ "579" },
	{ "581" },
	{ "819" },
	{ "873" },
	{ "306" },
	{ "639" },
	{ "867" }
	};

	printf("Please Enter a Phone Number: ");
	fgets(holdTheNum, kExcessSize, stdin); //we are letting the user enter how many characters they want
	clearCRLF(holdTheNum); //cleaning '\n'

	numSize = strlen(holdTheNum); //check the length

	if (numSize == 0) //no input entered
	{
		printf("ERROR: Are you sure your phone number is blank? \n");
		returnValue = false;
	}
	else
	{

		if (sscanf(holdTheNum, "%[0-9 .-()]s", &numInput) == 1)
		{
			numSize = strlen(holdTheNum); //check the length

			int checkParsed = 0;
			checkParsed = strlen(numInput);

			if (checkParsed == numSize) //comparing the size of the string before it is parsed by sscanf and then after it - if same same sscanf didn't find invalid characters
			{

				if (numSize == 12)
				{

					/***************************** Cases for dash ************************************/
					if ((holdTheNum[3] == kDash) && (holdTheNum[7] == kDash))
					{
						char temporary[kExcessSize] = { 0 }; //temporary string
						strcpy(temporary, holdTheNum);
						char* checkDigits = &temporary[3]; //point to elements after the [3]
						*checkDigits = '\0'; //fill the array with '\0' after [3]

						int i = 0;

						while ((digitValidator != kValid) && (i < kExcessSize))
						{
							if ((strcmp(myDigits[i], temporary) == 0))//lets check if the input is in the correct range
							{
								digitValidator = kValid;
							}

							i++;
						}

						if (digitValidator == kValid)
						{
							printf("Your number is [ %s ]\n", holdTheNum); //correct input
						}
						else if (digitValidator == kInvalid)
						{
							printf("ERROR: [ %s ] does not contain valid area code\n", holdTheNum);
						}

					}
					/**************************** Cases for dots *********************************/
					else if ((holdTheNum[3] == kDot) && (holdTheNum[7] == kDot))
					{
						char temporary[kExcessSize] = { 0 }; //temporary string
						strcpy(temporary, holdTheNum);
						char* checkDigits = &temporary[3]; //point to elements after the [3]
						*checkDigits = '\0'; //fill the array with '\0' after [3]

						int i = 0;

						while ((digitValidator != kValid) && (i < kExcessSize))
						{
							if ((strcmp(myDigits[i], temporary) == 0))//lets check if the input is in the correct range
							{
								digitValidator = kValid;
							}

							i++;
						}

						if (digitValidator == kValid)
						{
							printf("Your number is [ %s ]\n", holdTheNum); //correct input
						}
						else if (digitValidator == kInvalid)
						{
							printf("ERROR: [ %s ] does not contain valid area code\n", holdTheNum);
						}

					}
					/*************************** Cases for space *************************************/
					else if ((holdTheNum[3] == kSpace) && (holdTheNum[7] == kSpace))
					{
						char temporary[kExcessSize] = { 0 }; //temporary string
						strcpy(temporary, holdTheNum);
						char* checkDigits = &temporary[3]; //point to elements after the [3]
						*checkDigits = '\0'; //fill the array with '\0' after [3]

						int i = 0;

						while ((digitValidator != kValid) && (i < kExcessSize))
						{
							if ((strcmp(myDigits[i], temporary) == 0))//lets check if the input is in the correct range
							{
								digitValidator = kValid;
							}

							i++;
						}

						if (digitValidator == kValid)
						{
							printf("Your number is [ %s ]\n", holdTheNum); //correct input
						}
						else if (digitValidator == kInvalid)
						{
							printf("ERROR: [ %s ] does not contain valid area code\n", holdTheNum);
						}

					}
					else
					{
						printf("ERROR: Your input is out of range\n"); //in case something wrong happens
					}
				}
				else if (numSize < 15) //if there are curly brackets or an extension number
				{

					/************************************************************************************************************/
					/*								We are working with curly braces situations									*/
					/************************************************************************************************************/

					/*********************************** Cases for curly braces with dashes *************************************/
					if (((holdTheNum[0] == kCurly1) && (holdTheNum[4] == kCurly2)) && ((holdTheNum[5] == kSpace) && (holdTheNum[9] == kDash)))
					{
						char temporary[kExcessSize] = { 0 };
						char* hereIsToken1 = NULL;
						char* hereIsToken2 = NULL;

						strcpy(temporary, holdTheNum);

						hereIsToken1 = strtok(temporary, "(");
						hereIsToken2 = strtok(hereIsToken1, ")");

						int i = 0;
						while ((digitValidator != kValid) && (i < kExcessSize))
						{
							if ((strcmp(myDigits[i], hereIsToken2) == 0))//lets check if the input is in the correct range
							{
								digitValidator = kValid;
							}

							i++;
						}

						if (digitValidator == kValid)
						{
							printf("Your number is [ %s ]\n", holdTheNum); //correct input
						}
						else if (digitValidator == kInvalid)
						{
							printf("[ %s ] does not contain valid area code\n", hereIsToken2);
						}

					} //end of case if there were dashes

					  /*********************************** Cases for curly braces with dots *************************************/
					else if (((holdTheNum[0] == kCurly1) && (holdTheNum[4] == kCurly2)) && ((holdTheNum[5] == kSpace) && (holdTheNum[9] == kDot)))
					{
						char temporary[kExcessSize] = { 0 };
						char* hereIsToken1 = NULL;
						char* hereIsToken2 = NULL;

						strcpy(temporary, holdTheNum);

						hereIsToken1 = strtok(temporary, "(");
						hereIsToken2 = strtok(hereIsToken1, ")");

						int i = 0;
						while ((digitValidator != kValid) && (i < kExcessSize))
						{
							if ((strcmp(myDigits[i], hereIsToken2) == 0))//lets check if the input is in the correct range
							{
								digitValidator = kValid;
							}

							i++;
						}

						if (digitValidator == kValid)
						{
							printf("Your number is [ %s ]\n", holdTheNum); //correct input
						}
						else if (digitValidator == kInvalid)
						{
							printf("[ %s ] does not contain valid area code\n", hereIsToken2);
						}

					} //end of case if there were dots

					  /*********************************** Cases for curly braces with spaces *************************************/
					else if (((holdTheNum[0] == kCurly1) && (holdTheNum[4] == kCurly2)) && ((holdTheNum[5] == kSpace) && (holdTheNum[9] == kSpace)))
					{
						char temporary[kExcessSize] = { 0 };
						char* hereIsToken1 = NULL;
						char* hereIsToken2 = NULL;

						strcpy(temporary, holdTheNum);

						hereIsToken1 = strtok(temporary, "(");
						hereIsToken2 = strtok(hereIsToken1, ")");

						int i = 0;
						while ((digitValidator != kValid) && (i < kExcessSize))
						{
							if ((strcmp(myDigits[i], hereIsToken2) == 0))//lets check if the input is in the correct range
							{
								digitValidator = kValid;
							}

							i++;
						}

						if (digitValidator == kValid)
						{
							printf("Your number is [ %s ]\n", holdTheNum); //correct input
						}
						else if (digitValidator == kInvalid)
						{
							printf("[ %s ] does not contain valid area code\n", hereIsToken2);
						}

					}

					/************************************************************************************************************/
					/*								We are working with extension codes											*/
					/************************************************************************************************************/

					/*********************************** Cases for extions braces with dashes *************************************/
					else if ((holdTheNum[1] == kDash) && (holdTheNum[5] == kDash) && (holdTheNum[9] == kDash))
					{
						char temporary[kExcessSize] = { 0 }; //temporary array
						strcpy(temporary, holdTheNum);

						char* deleteThis = &temporary[5];
						*deleteThis = '\0';

						char* deleteThis2 = &temporary[2];

						int i = 0;
						while ((digitValidator != kValid) && (i<kExcessSize))
						{
							if ((strcmp(myDigits[i], deleteThis2) == 0))//lets check if the input is in the correct range
							{
								digitValidator = kValid;
							}

							i++;
						}

						if (digitValidator == kValid)
						{
							printf("Your number is [ %s ]\n", holdTheNum); //correct input
						}
						else if (digitValidator == kInvalid)
						{
							printf("[ %s ] does not contain valid area code\n", deleteThis2);
						}
					}

					/*********************************** Cases for curly braces with dots *************************************/
					else if ((holdTheNum[1] == kDot) && (holdTheNum[5] == kDot) && (holdTheNum[9] == kDot))
					{
						char temporary[kExcessSize] = { 0 }; //temporary array
						strcpy(temporary, holdTheNum);

						char* deleteThis = &temporary[5];
						*deleteThis = '\0';

						char* deleteThis2 = &temporary[2];

						int i = 0;
						while ((digitValidator != kValid) && (i<kExcessSize))
						{
							if ((strcmp(myDigits[i], deleteThis2) == 0))//lets check if the input is in the correct range
							{
								digitValidator = kValid;
							}

							i++;
						}

						if (digitValidator == kValid)
						{
							printf("Your number is [ %s ]\n", holdTheNum); //correct input
						}
						else if (digitValidator == kInvalid)
						{
							printf("[ %s ] does not contain valid area code\n", holdTheNum);
						}
					}

					/*********************************** Cases for curly braces with spaces *************************************/
					else if ((holdTheNum[1] == kSpace) && (holdTheNum[5] == kSpace) && (holdTheNum[9] == kSpace))
					{
						char temporary[kExcessSize] = { 0 }; //temporary array
						strcpy(temporary, holdTheNum);

						char* deleteThis = &temporary[5];
						*deleteThis = '\0';

						char* deleteThis2 = &temporary[2];

						int i = 0;
						while ((digitValidator != kValid) && (i<kExcessSize))
						{
							if ((strcmp(myDigits[i], deleteThis2) == 0))//lets check if the input is in the correct range
							{
								digitValidator = kValid;
							}

							i++;
						}

						if (digitValidator == kValid)
						{
							printf("Your number is [ %s ]\n", holdTheNum); //correct input
						}
						else if (digitValidator == kInvalid)
						{
							printf("[ %s ] does not contain valid area code\n", holdTheNum);
						}
					}
					else //in case something wrong happens with all our validation (it belongs to our first if statement)
					{
						printf("ERROR: Sorry, Invalid input\n");
					}
				}
				else //input too long
				{
					printf("ERROR: Your input is out of the correct range\n");
				}

			}//end of validations if there was correct input
			else
			{
				printf("ERROR: Sorry, Invalid input\n"); //in case something bad happens
			}
		}
		else  //else for sscanf
		{
			printf("ERROR: Sorry, Invalid input\n");
		}
	} //end of else if the input was not blank

	return returnValue;

}



/*================================================================================================
Function:
Description:
Parameters:
Return Values:
=================================================================================================*/
void getInput(char* firstName, char* secondName, char* province, char* postalCode, char* streetAddress)
{

	//in case we decide to get input in one place
	//I am really tired and I dont know yet what is going to be the best way to design the struct array and 
	//all the information... :(


}


/*=====================================================================================================================
Function:		clearCRLF
Description:	This function will search through the string and clean the '\n', it will end the string with '/0'
character. It is important to say that this function was made by Carlo Sgro.
Parameters:		char *buf: the string that will be cleared.
Return Values:	none.
=========================================================================================================================*/

void clearCRLF(char *str)
{
	char *whereIsCRLF = strchr(str, '\n');
	if (whereIsCRLF != NULL)
	{
		*whereIsCRLF = '\0';
	}
}

