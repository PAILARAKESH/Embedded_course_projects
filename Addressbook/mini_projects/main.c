/*
Project Title :    ADDRESSBOOK PROJECT
Batch : 24038
Batch ID : 24038_031
Name : P. RAKESH
Date : 12/03/2025
Description : The Address Book project is a console-based application that allows users to manage their contact list. 
              Users can store, retrieve, search, and modify contacts based on Name, Phone Number, or Email ID. 
              The program helps users efficiently find and organize contact information.
			  Add New Contacts: Store a person's name, phone number, and email ID.
              Search Contacts: Find a contact using Name, Phone, or Email.
            Handle Duplicates: If multiple contacts have the same name, the user can refine the search using phone or email.
            Display Contact Information: Once found, the program displays the details.
             Error Handling: Displays appropriate messages for invalid inputs or when a contact is not found.
Sample input: search by name
              Enter one option:
              1. Name
              2. Phone
              3. Email-id
              Please enter one option: 1
              Enter the name: Alice
Sample output: 
                              -------::: Contact Details :::-------

                     Name      : Alice
                     Mobile No : 9876543210
                     Email ID  : alice@example.com
*/

#include "contact.h"
int main()
{ 
	printf("\t\t\t\t----------Welcome To AddressBook-----------\n\n");
	AddressBook addressBook; //intializing struct variable
    int c=0;
	initialize(&addressBook); //function call for intializing contactcount and loading data from files
    do{
	printf("\nAddress Book Menu:\n");
	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Exit\n");
	printf("Enter your choice: ");
	scanf("%d",&c);
	switch(c) //switch case for the function call for selected option
	{
		case 1:
		createContact(&addressBook);
		break;
		case 2:
		searchContact(&addressBook); 
		break;
		case 3:
		editContact(&addressBook);
		break;
		case 4:
		deleteContact(&addressBook);
		break;
		case 5:
		listContacts(&addressBook);
		break;
		case 6:
		saveAndExit(&addressBook);
		break;
		default:
		printf("Invalid input\n");
		break;
	}
	}while(c!=6);
}