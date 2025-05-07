#include"atm.h"
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif
#define SIZE 100
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
int main()
{
user customer;
int  opt,i=1;
printf(RED"\t\t\n\n\t\t\t////////----::::"RESET BLUE"🏦 WELCOME TO INDIA NO-1 ATM 🏧"RESET RED"::::----////////\n\n"RESET);
intialize(&customer);
while(i==1)
{
    int check=0;
printf(BLUE"\nPlease enter the card\n\nDid you entered your card:\n1.YES\n2.NO\n"RESET);
printf(CYAN"Enter the option : "RESET);
scanf("%d",&check);
i=check;
if(check==1)
{
    int k=0,sel=0;
    printf(RED"\n\n1.ENGLISH"RESET YELLOW"\n2.తెలుగు\n"RESET);
    printf(MAGENTA"please select one option : "RESET);
    scanf("%d",&k);
    switch(k)
    {
        case 1:
        printf(RED"\n1.Balance enquiry\n2.withdraw\n3.deposit\n4.pin change\n5.Exit"RESET);
        printf(CYAN"\nplease select one option : "RESET);
        scanf("%d",&sel);
        switch(sel)
        {
            case 1:
            balance(&customer);
            break;
            case 2:
            withdrwal(&customer);
            break;
            case 3:
            deposite(&customer);
            break;
            case 4:
            pin(&customer);
            break;
            case 5:
            save(&customer);
            i=2;
            break;
            default:
            break;
        }
        break;
        case 2:
        printf(YELLOW"\n1.బ్యాలెన్స్ విచారణ  \n2.డబ్బు తీసుకోవడం  \n3.dడిపాజిట్  \n4.పిన్ మార్పు  \n5.నిష్క్రమించు  "RESET);
        printf(MAGENTA"\nదయచేసి ఒక ఎంపికను ఎంచుకోండి:  "RESET);
        scanf("%d",&sel);
        switch(sel)
        {
            case 1:
            balt(&customer);
            break;
            case 2:
            withdt(&customer);
            break;
            case 3:
            depot(&customer);
            break;
            case 4:
            pt(&customer);
            break;
            case 5:
            save(&customer);
            i=2;
            break;
            default:
            break;
        }
        break;
        default:
        break;
              
    }
    
}

}
}