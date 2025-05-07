#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) { //function definition to write data into contacts.csv file
    FILE* fptr=fopen("contacts.csv","w");
    if(fptr==NULL)
    {
        return;
    }
    fprintf(fptr,"%d\n",addressBook->contactCount); //fprintf() to print the contact count int contacts.csv file
    for(int i=0;i<(addressBook->contactCount);i++) //loop to print each contact into contact.csv file
    {
    fprintf(fptr,"%s,",addressBook->contacts[i].name);
    fprintf(fptr,"%s,",addressBook->contacts[i].phone);
    fprintf(fptr,"%s,",addressBook->contacts[i].email);
    fprintf(fptr,"%s\n",addressBook->contacts[i].group);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) { //function definition to read data into contacts.csv file
    FILE* fptr=fopen("contacts.csv","r");
    if(fptr==NULL)
    {
        return;
    }
    fscanf(fptr,"%d",&addressBook->contactCount); //fprintf() to read  the contactcount int contacts.csv file
    for(int i=0;i<(addressBook->contactCount);i++) // loop to read each contact from contacts.csv file
    {
    fscanf(fptr," %[^,],",addressBook->contacts[i].name);
    fscanf(fptr," %[^,],",addressBook->contacts[i].phone);
    fscanf(fptr," %[^,],",addressBook->contacts[i].email);
    fscanf(fptr," %[^\n]",addressBook->contacts[i].group);
    fgetc(fptr);
    }
    fclose(fptr);
}
