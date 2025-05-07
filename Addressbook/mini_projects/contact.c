#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    /* Define the logic for print the contacts */
    //printf("%s\n", addressBook->contacts[addressBook->contactCount].name);
   // initialize(addressBook);
   int opt=0;
   printf("\n1.you want to list all contacts\n2.you want specific group contacts\n");
   printf("\nPlease enter one option: ");
   scanf("%d",&opt);
   if(opt==1)
   {
   printf("\t\t\t\t-------------------------:::AddressBook Contacts:::-------------------------\n\n\n");
   printf("\t\t----------------------------------------------------------------------------------------------------------------------\n");
   printf("\t\t|S.NO%15cContact Name%15cPhone no%15cEmail id%25cGroup%10c\n",124,124,124,124,124);
    for(int i=0;i<(addressBook->contactCount);i++) //loop for printing the addressbook
    {
        printf("\t\t----------------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t|%-18d|%-26s|%22s|%32s|%-14s|\n",i+1, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email,addressBook->contacts[i].group);

    }
    printf("\t\t----------------------------------------------------------------------------------------------------------------------\n");
}
else if(opt ==2){
     printf("Wich group you want to list out:\n1.Family\n2.Friends\n3.Community\n4.Office\n5.Others\n");
     int k=0;
     printf("\nPlease enter one option: ");
     scanf("%d",&k);
     char grp[50];
     switch(k)   //switch case to check which group to store
     {
        case 1:
        strcpy(grp,"Family");
        break;
        case 2:
        strcpy(grp,"Friends");
        break;
        case 3:
        strcpy(grp,"Community");
        break;
        case 4:
        strcpy(grp,"Office");
        break;
        case 5:
        strcpy(grp,"Others");
        break;
        default:
        printf("Invalid input");
        break;
     }
     printf("\t\t\t\t-------------------------:::AddressBook Contacts:::-------------------------\n\n\n");
     printf("\t\t----------------------------------------------------------------------------------------------------------------------\n");
     printf("\t\t|S.NO%15cContact Name%15cPhone no%15cEmail id%25cGroup%11c\n",124,124,124,124,124);
      for(int i=0;i<(addressBook->contactCount);i++) //loop for printing the addressbook
      {
        if(strcmp(addressBook->contacts[i].group,grp)==0)
        {
          printf("\t\t-----------------------------------------------------------------------------------------------------------------------\n");
          printf("\t\t|%-18d|%-26s|%22s|%32s|%-15s|\n",i+1, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email,addressBook->contacts[i].group);
        }
      }
      printf("\t\t-----------------------------------------------------------------------------------------------------------------------\n");

}
else{
    printf("Invalid input\n");
}

}
int search(AddressBook *addressBook,int n) //function definition for search a contact to get that index
{
    int k=0;
    for(int i=0;i<n;i++) //loop for the validation only n times
    {
        int flag=0,c=0,ind=0,opt=0,flg=0,duplicate=1; //intializing variables

        printf("You have %d chances are there:",n);
        char name1[20],phone2[20],mailid[20],mobile_d[20],mail_d[20];
        char *mobile_dup,*mail_dup;
        printf("\nEnter one option:\n1.Name\n2.Phone\n3.Email-id\n");
        printf("Please enter one option: ");
       int ret=scanf("%d",&k);
       if(ret)
       {
        switch(k) //switch case to check by 1.name 2.phone 3.email
        {
            case 1:
            printf("Enter the name: ");
            scanf(" %[^\n]",name1);
            for(int k=0;k<(addressBook->contactCount);k++) // loop for finding whether the contact is present with entered name or not and print the contact
            {
                if((strcmp(addressBook->contacts[k].name,name1))==0) //string function to compare two strings
                {
                    printf("\t\t-------:::Contact detailes::::-------\n\n");
                    printf("Name : %s\n",addressBook->contacts[k].name);
                    printf("Mobile no : %s\n",addressBook->contacts[k].phone);
                    printf("Email-id : %s\n",addressBook->contacts[k].email);
                    printf("\n");
                    ind=k;
                    c++;
                    flag=1;
                }

             }
             if(c>1)  //condition check to check for duplicate contacts
             {
                do{
                printf("There are duplicate contacts will you give me details about either:\n1.phone number\n2.email id");
                printf("\n\nPlease enter one option: ");
                scanf("%d",&opt);
                switch(opt) //switch to validate with phone or email
                {
                    case 1:
                    mobile_dup = read_mobile_num(mobile_d);
                     for(int j=0;j<(addressBook->contactCount);j++) //loop for finding the phone number
                    {
                        if((strcmp(addressBook->contacts[j].phone,mobile_dup))==0 && (strcmp(addressBook->contacts[j].name,name1)==0))
                        {
                            flg=1;
                            return j;
                        }
                    }
                    printf("Contact not found\n");
                    break;
                    case 2:
                    mail_dup=read_mail_id(mail_d);
                    for(int j=0;j<(addressBook->contactCount);j++) //loop for finding email
                    {
                        if((strcmp(addressBook->contacts[j].email,mail_dup))==0 && (strcmp(addressBook->contacts[j].name,name1)==0))
                        {
                            return j;
                        }
                    }
                     printf("Contact not found\n");
                    break;
                    default:
                    printf("Invalid input\n");
                    break;

                }
                duplicate++;
             }while(duplicate!=3);
            }
             else if(flag==0)
             printf("Contact not found\n");
            else
            return ind;
        break;
    case 2:
        printf("Enter the phone number: ");
            scanf(" %[^\n]",phone2);
            for(int k=0;k<(addressBook->contactCount);k++)  // loop for finding whether the contact is present with entered phone-no or not
            {
                if((strcmp(addressBook->contacts[k].phone,phone2))==0) //string function to compare two strings
                {
                    flag=1;
                }
                if(flag==1)
                {
            
                    printf("\t\t-------:::Contact detailes::::-------\n\n");
                    printf("Name : %s\n",addressBook->contacts[k].name);
                    printf("Mobile no : %s\n",addressBook->contacts[k].phone);
                    printf("Email-id : %s\n",addressBook->contacts[k].email);
                    printf("\n");
                    return k;
                }
             }
             if(flag==0)
             printf("Contact not found\n");
        break;
        case 3:
        printf("Enter the email id: ");
        scanf(" %[^\n]",mailid);
    
                for(int k=0;k<(addressBook->contactCount);k++)   // loop for finding whether the contact is present with entered email-id or not
                {
                    if((strcmp(addressBook->contacts[k].email,mailid))==0)
                    {
                        flag=1;
                    }
                    if(flag==1)
                    {
            
                    printf("\t\t-------:::Contact detailes::::-------\n\n");
                    printf("Name : %s\n",addressBook->contacts[k].name);
                    printf("Mobile no : %s\n",addressBook->contacts[k].phone);
                    printf("Email-id : %s\n",addressBook->contacts[k].email);
                    printf("\n");
                    return k;
                    }
                 }
                 if(flag==0)
                 printf("Contact not found\n");
        break;
        default:
        printf("Invalid input\n");
        break;
    }
}
else
{
    printf("Invalid input\n");
    return -1;
}
if((flag==0)||(flg==0))
return -1;
}
}


char* read_name(char name1[]) //function definition for reading  name
{
    int k=1;
    do{
    int flag=0,i=0;
    printf("Enter the name: ");
    scanf(" %[^\n]",name1);
    while(name1[i]!='\0') // to check string upto the null charcter using while loop
    {
        if((name1[i]>='A' && name1[i]<='Z')||(name1[i]>='a' && name1[i]<='z')||name1[i] == 32) //condition to check it is alphabetical character or not or we can use isalpha() function
        {
            i++;
        }
        else
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
    return name1; //returning name1 address
    }
    else{
        printf("Invalid name\n");
    }
}while(k);

}


 char * read_mobile_num(char phone[]) //function definition for reading mobile number it return address
 {
    int i=1;
    do{
        int flag=0,f1=0;
        printf("Enter the mobile number: ");
        scanf(" %[^\n]",phone);
        int l=strlen(phone); // find the length of the string
        if(l==10)
        {
            int m=0;
            while(phone[m]!='\0') //loop upto the '\0' 
            {
                if(phone[m]>=48 && phone[m]<=57)// for checking the characterv is digit or not we can use isdigit() also.
                {
                    m++;
                }
                else{
                    f1=1;
                    break;
                }
            }
            if(f1==0)
            {
                return phone;
            }
            else{
                printf("Invalid number\n");
            }
            
    }
    else{
        printf("Invalid input\n");
    }
 }while(i);
}


char * read_mail_id(char email[]) //function definition for email checking
 {
    int i = 1;
    do {
        int flag = 0,count=0;
        printf("Enter the email id: ");
        scanf(" %[^\n]", email);

        int j = 0;
        while(email[j]!='\0') // loop will run upto null character '\0'
        {
          if(email[j] == '@')
          {
            count++; //to count the @ in the string
          }
          j++;
        }
        j=0;
        while (email[j]!='@'&&email[j]!='\0') //while loop upto '@' or '\0'
         {
            if ((email[j] >= 'a' && email[j] <= 'z') || (email[j] >= '0' && email[j] <= '9')) //condtion for checking lower case and digits
            {
                j++;
            } 
            else
            {
                flag = 1;
                break;
            }
        }

        if (email[j]!='@') {
            flag = 1;
        }

        if (flag == 0 && count == 1) {
            int k = 0;
            char *ptr = email + j;
            while (ptr[k] != '\0') //loop will run upto '\0'
             {
                if (ptr[k] == '.')  //for checking the '.'
                {
                    if (strcmp(ptr + k, ".com") == 0) //strcmp i will check .com with string upto null character
                    {
                        return email; 
                    }
                    break;
                }
                k++;
            }
        }

        printf("Invalid email\n");

    } while (i);
}

void initialize(AddressBook *addressBook) { //function definition for intialization
    addressBook->contactCount = 0; //intializing contact count
   // populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook); //function call to load the data from files
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    printf("\n");
	printf("\t\t\t\t--------Thank you--------\n\n");
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{

    /* Define the logic to create a Contacts */

    // Read the name from the user
        char name1[20];
        char* name2=read_name(name1);
    strcpy(addressBook->contacts[addressBook->contactCount].name,name2);
    
    // Read the contact
    // - Check whether the count is 10 or not
    // - Check all 10 characters are digits or not.
    // - Check the given number is already exist or not
    char number[11];
    int i=1;
    do{
        int flag=0;
          char* number1=read_mobile_num(number);
            for(int k=0;k<(addressBook->contactCount);k++) // loop to check for unique data only for the mobile number
            {
                if((strcmp(addressBook->contacts[k].phone,number1))==0)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                strcpy(addressBook->contacts[addressBook->contactCount].phone,number1); //copy the number using strcpy to addressbook
                i=0;
            }
            else{
                printf("Contact phone number should be unique\n");
            }
        }while(i);

    
    // Read the email ID
    // - Check whether the character array contains lowercase, digits and special characters or not
    // - Check whether char - @ and .com is present or not

    // Increment the contact count.
    char mail[20];
    int p=1;
    do{
        int flag=0;
        char * mail_id=read_mail_id(mail);
        for(int k=0;k<(addressBook->contactCount);k++)   // loop to check for unique data only for the email 
            {
                if((strcmp(addressBook->contacts[k].email,mail_id))==0)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
               strcpy(addressBook->contacts[addressBook->contactCount].email,mail_id); // copy the mail using strcpy to addressbook
               i=0;
                p=0;
            }
            else{
                printf("email already existed\n");
            }
         
       
    }while(p);
    


    char group[30];
    int opt,ind=0;
    printf("In which group you want to add:\n1.Family\n2.Friends\n3.Community\n4.Office\n5.Others\n");
    printf("\nPlease enter one option: ");
    scanf("%d",&opt);
    switch(opt) //switch case to add the contack in which group
    {
        case 1:
        strcpy(addressBook->contacts[addressBook->contactCount].group,"Family");
        break;
        case 2:
        strcpy(addressBook->contacts[addressBook->contactCount].group,"Friends");
        break;
        case 3:
        strcpy(addressBook->contacts[addressBook->contactCount].group,"Community");
        break;
        case 4:
        strcpy(addressBook->contacts[addressBook->contactCount].group,"Office");
        break;
        case 5:
        strcpy(addressBook->contacts[addressBook->contactCount].group,"Others");
        break;
        default:
        printf("Invalid input");
        break;
    }
    (addressBook->contactCount)++;
    printf("\t\t---------:::Successfully contact created:::-------------\n\n");
}


void searchContact(AddressBook *addressBook) //function definition for search a particular contact and print the contact
{
    /* Define the logic for search */
    int c=0,m1=1;
    do{
        int k=0,flag=0,m=1,count=0,flg=0,duplicate=1;
        char name2[20],phone1[20],email1[20],mobile_d[20],mail_d[20];
        char* mobile_dup,*mail_dup;
        printf("\nOn which basis you want to search:\n1.Search by name\n2.Search by phone\n3.Search by email\n4.Exit\n\n");
        printf("Please enter one option: ");
        scanf("%d",&k);
        switch(k)
        {
            case 1:
            do{
            char* name=read_name(name2);

            for(int k=0;k<(addressBook->contactCount);k++) //loop to search with name
            {
                if((strcmp(addressBook->contacts[k].name,name))==0) //conditon to compare name
               {
                    flag=1;
                    printf("\t\t-------:::Contact detailes::::-------\n\n");
                    printf("Name : %s\n",addressBook->contacts[k].name);
                    printf("Mobile no : %s\n",addressBook->contacts[k].phone);
                    printf("Email-id : %s\n",addressBook->contacts[k].email);
                    count++;
                }
             }
             if(count>1) //condition to check duplicte contacts
             {
                do{
                    int opt=0;
                    printf("There are duplicate contacts will you give me details about either:\n1.phone number\n2.email id");
                    printf("\n\nPlease enter one option: ");
                    scanf("%d",&opt);
                    switch(opt) //Evaluate with phone no and email id
                    {
                        case 1:
                        mobile_dup = read_mobile_num(mobile_d);
                         for(int j=0;j<(addressBook->contactCount);j++) //loop for the mobile no checking
                        {
                            if((strcmp(addressBook->contacts[j].phone,mobile_dup))==0 && (strcmp(addressBook->contacts[j].name,name))==0) //condition for mobile and name
                            {
                                printf("\t\t-------:::Contact detailes::::-------\n\n");
                                printf("Name : %s\n",addressBook->contacts[j].name);
                                printf("Mobile no : %s\n",addressBook->contacts[j].phone);
                                printf("Email-id : %s\n",addressBook->contacts[j].email);
                                flg=1;
                                duplicate=2;
                                m=0;
                                m1=0;
                            }
                        }
                        if(flg!=1)
                        {
                            printf("Contact not found\n");
                        }
                        break;
                        case 2:
                        mail_dup=read_mail_id(mail_d);
                        for(int j=0;j<(addressBook->contactCount);j++) //loop for emailid checking
                        {
                            if((strcmp(addressBook->contacts[j].email,mail_dup))==0 && (strcmp(addressBook->contacts[j].name,name))==0) //condition for mail and name
                            {
                                printf("\t\t-------:::Contact detailes::::-------\n\n");
                                printf("Name : %s\n",addressBook->contacts[j].name);
                                printf("Mobile no : %s\n",addressBook->contacts[j].phone);
                                printf("Email-id : %s\n",addressBook->contacts[j].email);
                                flg=1;
                                duplicate=2;
                                m=0;
                                m1=0;
                            }
                        }
                        if(flg!=1)
                        {
                            printf("Contact not found\n");
                        }
                        break;
                        default:
                        printf("Inavalid input\n");
                        break;
    
                    }
                    duplicate++;
                 }while(duplicate!=3);

             }
             else
             {
                m=0;
                m1=0;
             }
             if(flag==0)
             printf("Contact not found\n");
            }while(m);
        break;
        case 2:
        do{
        char* phone2=read_mobile_num(phone1);

            for(int k=0;k<(addressBook->contactCount);k++) //loop for mobile no
            {
                if((strcmp(addressBook->contacts[k].phone,phone2))==0) //condtion for mobile no using strcmp() funtion
                {
                    flag=1;
                }
                if(flag==1)
                {
            
                    printf("\t\t-------:::Contact detailes::::-------\n\n");
                    printf("Name : %s\n",addressBook->contacts[k].name);
                    printf("Mobile no : %s\n",addressBook->contacts[k].phone);
                    printf("Email-id : %s\n",addressBook->contacts[k].email);
                    m=0;
                    m1=0;
                    break;
                }
             }
             if(flag==0)
             printf("Contact not found\n");
            }while(m);
        break;
        case 3:
        do{
            char* email2=read_mail_id(email1);
    
                for(int k=0;k<(addressBook->contactCount);k++) //loop for checking email 
                {
                    if((strcmp(addressBook->contacts[k].email,email2))==0) //condition to check for mail id
                    {
                        flag=1;
                    }
                    if(flag==1)
                    {
            
                    printf("\t\t-------:::Contact detailes::::-------\n\n");
                    printf("Name : %s\n",addressBook->contacts[k].name);
                    printf("Mobile no : %s\n",addressBook->contacts[k].phone);
                    printf("Email-id : %s\n",addressBook->contacts[k].email);
                    m=0;
                    m1=0;
                    break;
                    }
                 }
                 if(flag==0)
                 printf("Contact not found\n");
                }while(m);
        break;
        case 4:
        m1=0;
        break;
        default:
        printf("Invalid input\n");
        break;
    }


        }while(m1);
    }


void editContact(AddressBook *addressBook) //funtion definition for edit a contact
{
    // Define the logic for Editcontact 
    int n=1,p=3,in=0;
    do{
        int t=1;
        if(p>0)
    {
        printf("\nFor updating details:\n");
    
     int k=search(addressBook,p); 
     if(k>=0)
     {
    while(t)
    {
        int i=0,flag=0,dup=0,ind=0,c=0,j;
     printf("which data you want to change:\n1.Contact Name\n2.Contact Phoneno\n3.Contact mail_id\n4.exit");
     printf("\n\nPlease enter the option:");
     scanf("%d",&i);
     char name1[20],phone1[20],mail1[20],phone_d[20],email_d[20];
     char* name2,*phone2,*mail2,*phone_dup,*email_dup;
    switch(i)
    {
        case 1:
        name2=read_name(name1);
        strcpy(addressBook->contacts[k].name,name2); //strcpy() to change name
        break;
        case 2:
        phone2=read_mobile_num(phone1);
        for(j=0;j<(addressBook->contactCount);j++) //loop to check for the unique data
            {
                if((strcmp(addressBook->contacts[j].phone,phone2))==0) //condition to compare with mobile number
                {
                    flag=1;
                    break;
                }
            }
        if(flag==0)
        {
        strcpy(addressBook->contacts[k].phone,phone2); //strcpy() to copy the data
        }
        else{
            printf("Mobile number already existed\n");
        }
        break;
        case 3:
        mail2=read_mail_id(mail1);
        for(j=0;j<(addressBook->contactCount);j++) //loop to check for the unique data
        {
            if((strcmp(addressBook->contacts[j].email,mail2))==0)  //condition to check with mail id
            {
                flag=1;
                break;
            }
        }
    if(flag==0)
    {
        strcpy(addressBook->contacts[k].email,mail2); //strcpy() to copy the mail id
    }
    else{
        printf("email_id already existed\n");
    }
        break;
        case 4:
        t=0;
        break;
        default:
        printf("Invalid input\n");
        getchar();
        break; 
    }
    if(t)
    {
    printf("Do yo want change another data :\n1.YES\n0.NO\n");
    printf("Please enter the option: ");
    scanf("%d",&t);
    }
    

}
printf("Do you want to re-search the people:\n1.YES\n0.NO\n");
printf("Please enter the option: ");
scanf("%d",&n);
}
p--;
if(p==0)
n=0;
    }
}while(n);
}
void deleteContact(AddressBook *addressBook) // function definition to delete a contact
{
    /* Define the logic for deletecontact */
    int t=1,p=3;
    do{
        if(p>0)
        {
     int k=search(addressBook,p);  //function call to search a contact
     if(k>=0)
     {
    int i=0,count=0;
     printf("\nyou want to delete this contact:\n1.YES\n2.NO\n");
     printf("Please enter the option:");
     scanf("%d",&i);
     if(i==1)
     {
     for(int j=0;j<(addressBook->contactCount);j++) //loop to overwrite the addressbook or delete a contact
     {
        if((addressBook->contacts[j].phone) != (addressBook->contacts[k].phone))
        {
            addressBook->contacts[count++]=addressBook->contacts[j];
        }
     }
     (addressBook->contactCount)=count;
     printf("Do you want to delete another data:\n1.YES\n2.NO\n");
     printf("Please enter the option: ");
     scanf("%d",&t);
    }
    else if(i==2){
        printf("Do you want to delete another data:\n1.YES\n2.NO\n");
        printf("Please enter the option: ");
        scanf("%d",&t);
       }
    }
    else{
        t=2;
    }
    p--;
    if(p==0)
    t=2;
}
}while(t!=2);
}
