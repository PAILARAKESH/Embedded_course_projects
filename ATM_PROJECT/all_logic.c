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
#define DATE "1/04/2025"
#define TIME "11:00" 
void bill_print(user* user,int,int);

void intialize(user* user)
{
    int cscount=0;
    load(user);
}
void playWithdrawalSound() {
    #ifdef _WIN32
        Beep(1000, 300);  // Beep at 1000 Hz for 300 ms
        Beep(1200, 300);
        Beep(900, 300);
    #else
        system("paplay atm_sound.wav");  // Ensure you have an audio file
    #endif
}

void balance(user* user)
{
    char pwd[5];
    int flg = 0;
    
    printf(MAGENTA"Enter the 4-digit pin: "RESET);
    scanf(" %4s", pwd);

    for (int i = 0; i < user->cscount; i++)
    {
        if (strcmp(pwd, user->customer[i].pin) == 0)
        {
            printf(RED"\t\t::: %s :::\n"RESET,user->customer[i].name);
            flg = 1;
            printf(GREEN"\nThe balance in your account is: %.2lf\n"RESET, user->customer[i].amt);
            save(user);
            break;
        }
    }
    
    if (flg == 0)
    {
        printf(RED"\t\tIncorrect PIN\n"RESET);
    }
}
void withdrwal(user* user)
{
    char pwd[5];
    int flg=0,wd=0;
    printf(MAGENTA"Enter the 4-digit pin : "RESET);
    scanf("%4s",pwd);
    for(int i=0;i<user->cscount;i++)
    {
        if((strcmp(pwd,user->customer[i].pin))==0)
        {
            printf(RED"\t\t::: %s :::\n"RESET,user->customer[i].name);
            printf(MAGENTA"The Balance is: %lf\n"RESET,user->customer[i].amt);
            printf(YELLOW"\nEnter how much you want to withdraw: "RESET);
            scanf("%d",&wd);
            if((wd>0&&(wd%100)==0)&&(wd<=user->customer[i].amt))
            {
            flg=1;
            user->customer[i].amt -= wd;
          //  playWithdrawalSound();
            printf(GREEN"\nThe balance amount is : %lf\n"RESET,user->customer[i].amt);
            bill_print(user,0,i);
            save(user);
            }
            else
            {
                printf(CYAN"\n\tplease enter the multiples of 100 or 500\n"RESET);
            }
        }
    }
    if(flg==0)
    {
        printf(RED"\t\tIncorrect pin\n"RESET);
    }

}
void deposite(user* user)
{
    char pwd[5];
    int flg=0,wd=0,dep=0;
    printf(MAGENTA"Enter the 4-digit pin : "RESET);
    scanf("%4s",pwd);
    for(int i=0;i<user->cscount;i++)
    {
        if((strcmp(pwd,user->customer[i].pin))==0)
        {
            printf(RED"\t\t::: %s :::\n"RESET,user->customer[i].name);
            flg=1;
            printf(YELLOW"Enter how mucch amount you want to deposite : "RESET);
            scanf("%d",&dep);
            if(dep>0)
            {
            (user->customer[i].amt) = (user->customer[i].amt)+(double)dep;
           // playWithdrawalSound();
            printf(BLUE"The amount in your account is :  %lf\n"RESET, (user->customer[i].amt) );
            printf(GREEN"\n\t\tSuccessfully deposited\n"RESET);
            bill_print(user,1,i);
            save(user);
            }
        }
    }
    if(flg==0)
    {
        printf(RED"\t\tIncorrect pin\n"RESET);
    }
}
void pin(user* user)
{
    int flg=0;
    char p[5],new[5],rp[5];
    printf(RED"Enter the old pin: "RESET);
    scanf("%4s",p);
    for(int i=0;i<user->cscount;i++)
    {
        if((strcmp(p,user->customer[i].pin))==0)
        {
            printf(RED"\t\t::: %s :::\n"RESET,user->customer[i].name);
            flg=1;
            printf(YELLOW"Enter the new 4-digit pin : "RESET);
            scanf("%4s",new);
            printf(BLUE"Re-enter the pin : "RESET);
            scanf("%4s",rp);
            if((strcmp(new,rp))==0)
            {
                strcpy(user->customer[i].pin,new);
                printf(GREEN"\n\t\tPin changed successfully\n"RESET);
            }
            else{
                printf(RED"\t\tInvalid pin\n"RESET);
            }

        }
    }
}
void balt(user* user)
{
    char pwd[5];
    int flg = 0;
    
    printf(YELLOW"దయచేసి 4 అంకెల పిన్ నమోదు చేయండి: "RESET);
    scanf(" %4s", pwd);

    for (int i = 0; i < user->cscount; i++)
    {
        printf("%s\n",user->customer[i].pin);
        if (strcmp(pwd, user->customer[i].pin) == 0)
        {
            printf(RED"\t\t::: %s :::\n"RESET,user->customer[i].name);
            flg = 1;
            printf(GREEN"\nమీ ఖాతాలోని బ్యాలెన్స్:  %.2lf\n"RESET, user->customer[i].amt);
            save(user);
            break;
        }
    }
    
    if (flg == 0)
    {
        printf(RED"\t\tమీరు తప్పు పిన్‌ను నమోదు చేసారు\n"RESET);
    }
}
void withdt(user* user)
{
    char pwd[5];
    int flg=0,wd=0;
    printf(MAGENTA"దయచేసి 4 అంకెల పిన్ నమోదు చేయండి: "RESET);
    scanf("%4s",pwd);
    for(int i=0;i<user->cscount;i++)
    {
        if((strcmp(pwd,user->customer[i].pin))==0)
        {

            printf(RED"\t\t::: %s :::\n"RESET,user->customer[i].name);
            printf(BLUE"బ్యాలెన్స్:   %lf\n"RESET,user->customer[i].amt);
            printf(YELLOW"ఎంత మొత్తాన్ని తీసుకోవాలనుకుంటున్నారో నమోదు చేయండి: "RESET);
            scanf("%d",&wd);
            if((wd>0&&(wd%100)==0)&&(wd<=user->customer[i].amt))
            {
            flg=1;
            user->customer[i].amt -= wd;
            printf("\n");
            printf(GREEN"మిగిలిన మొత్తం:  %lf\n"RESET,user->customer[i].amt);
            bill_print(user,1,i);
            save(user);
            }
            else
            {
                printf("\n\t");
                printf(RED"దయచేసి 100 లేదా 500 యొక్క గుణితపరిమాణాలను నమోదు చేయండి\n"RESET);
            }
        }
    }
    if(flg==0)
    {
        printf(RED"\t\tమీరు తప్పు పిన్‌ను నమోదు చేసారు\n"RESET);
    }

}
void depot(user* user)
{
    char pwd[5];
    int flg=0,wd=0,dep=0;
    printf(MAGENTA"దయచేసి 4 అంకెల పిన్ నమోదు చేయండి: "RESET);
    scanf("%4s",pwd);
    for(int i=0;i<user->cscount;i++)
    {
        if((strcmp(pwd,user->customer[i].pin))==0)
        {
            printf(RED"\t\t::: %s :::\n"RESET,user->customer[i].name);
            flg=1;
            printf(YELLOW"మీరు డిపాజిట్ చేయాలనుకునే మొత్తం నమోదు చేయండి: "RESET);
            scanf("%d",&dep);
            if(dep>0)
            {
            (user->customer[i].amt) = (user->customer[i].amt)+(double)dep;
            printf(BLUE"మీ ఖాతాలో ఉన్న మొత్తం:   %lf\n"RESET, (user->customer[i].amt) );
            printf(GREEN"\n\t\t సఫలంగా డిపాజిట్ చేయబడింది  \n"RESET);
            bill_print(user,1,i);
            save(user);
            }
        }
    }
    if(flg==0)
    {
        printf(RED"\t\tమీరు తప్పు పిన్‌ను నమోదు చేసారు\n"RESET);
    }
}
void pt(user* user)
{
    int flg=0;
    char p[5],new[5],rp[5];
    printf(RED"పాత పిన్‌ను నమోదు చేయండి:  "RESET);
    scanf("%4s",p);
    for(int i=0;i<user->cscount;i++)
    {
        if((strcmp(p,user->customer[i].pin))==0)
        {
            printf(RED"\t\t::: %s :::\n"RESET,user->customer[i].name);
            flg=1;
            printf(YELLOW"కొత్త 4 అంకెల పిన్‌ను నమోదు చేయండి:  "RESET);
            scanf("%4s",new);
            printf(BLUE"పిన్‌ను మరల నమోదు చేయండి:  "RESET);
            scanf("%4s",rp);
            if((strcmp(new,rp))==0)
            {
                strcpy(user->customer[i].pin,new);
                printf(GREEN"\n\t\tపిన్ విజయవంతంగా మార్చబడింది  \n"RESET);
            }
            else{
                printf(RED"\t\tచెల్లని పిన్  \n"RESET);
            }

        }
    }
}
void bill_print(user* user,int x,int i)
{
    printf(YELLOW"\t\t---Please take your receipt-- \n\n"RESET);
    printf(BLUE"\t\t------------------------------------\n"RESET);
    printf(BLUE"\t\t|  --\\\\ INDIAN NO-1 ATM \\\\--       |\n"RESET);
    printf(BLUE"\t\t|BRANCH -ARILOVA                   |\n"RESET);
    printf(BLUE"\t\t|CODE-142356                       |\n"RESET);
    printf(BLUE"\t\t|----------------------------------|\n"RESET);
    printf(BLUE"\t\t|ACC NO-718*******567              |\n"RESET);
    if(x==0)
    printf(BLUE"\t\t|THE AMOUNT IS SUCCESSFULLY DEBITED|\n"RESET);
else
    printf(BLUE"\t\t|THE  AMOUNT SUCCESSFULLY DEPOISTED|\n"RESET);
    printf(BLUE"\t\t|THE BALANCE AMT         - %.2lf|\n"RESET,user->customer[i].amt);
    printf(BLUE"\t\t|"DATE"                 "TIME"AM |\n"RESET);
    printf(BLUE"\t\t|----------------------------------|\n"RESET);
    printf(BLUE"\t\t|       THANK FOR YOUR SUPPORT     |\n"RESET);
    printf(BLUE"\t\t|----------------------------------|\n"RESET);
}