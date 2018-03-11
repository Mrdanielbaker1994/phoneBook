/*==============================================================================================
File:  
Project:
Version:
Programmer:
Description:
===================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>

#pragma warning (disable: 4996)

/*STUCTS*/
typedef struct phoneBook
{
	char  name[31];
	char  street[61];
	char  phoneNumber[13];
	char  province[3];
	char  city[61];
	char  postalCode[8] ;
}phoneBook;


/*CONSTANTS*/
#define kNameLimit 30
#define kExcessSize 500
#define kDash '-'
#define kDot '.'
#define kSpace ' '
#define kCurly1 '('
#define kCurly2  ')'
#define kValid 1
#define kInvalid -1

#define provinceNumber 13
#define provinceCodeLength 2
#define provinceNameLength 30
#define kMaxCityLength 61
#define kMaxStreetLength 61
#define maxLength 100
#define postalCodeLength 7
#define maxEntries 10


/*PROTOTYPES*/
bool validateName(struct phoneBook *newPerson);
bool validatePhoneNumber(struct phoneBook *newPerson);

bool provinceValidation(struct phoneBook *newPerson);
bool cityValidation(struct phoneBook *newPerson);
bool postalCode(struct phoneBook *newPerson);
bool streetAddress(struct phoneBook *newPerson);

void getInput(char* firstName, char* secondName, char* province, char* postalCode, char* streetAddress);
void clearCRLF(char *str);

