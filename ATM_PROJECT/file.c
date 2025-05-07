#include"atm.h"
void save(user* user)
{
    FILE * fp=fopen("atm.csv","w");
    if(fp==NULL)
    {
        printf("Error\n");
        return;
    }
    fprintf(fp,"%d\n",user->cscount);
    for(int i=0;i<user->cscount;i++)
    {
        fprintf(fp,"%s,%s,%.2lf\n",user->customer[i].name,user->customer[i].pin,user->customer[i].amt);
    }
    fclose(fp);
}
void load(user* user)
{
    FILE * fp=fopen("atm.csv","r");
    if(fp==NULL)
    {
        printf("Error\n");
        return;
    }
    fscanf(fp,"%d\n",&user->cscount);
    for(int i=0;i<user->cscount;i++)
    {
        fscanf(fp,"%[^,],%[^,],%lf\n",user->customer[i].name,user->customer[i].pin,&user->customer[i].amt);
    }
    fclose(fp);
}