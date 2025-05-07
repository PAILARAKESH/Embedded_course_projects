#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

#define MAX_CONTACTS 100

typedef struct Contact{
    char name[50];
    char phone[20];
    char email[50];
    char group[30];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;
/* funtion prototpyes for functions in contacts.c*/
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void saveAndExit(AddressBook *addressBook);
char* read_data(char name[]);
char* read_name(char name1[]);
char * read_mobile_num(char phone[]) ;
char * read_mail_id(char email[]);

#endif
