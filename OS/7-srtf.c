#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

struct time
{
    int bt, at, st, wt, tat, et, rt;
    char pid[2];
} s[6];

int timeline[50];
char process[2][50];

void waiting()
{
    for(int i=0;i<6;i++)
        s[i].wt = s[i].tat-s[i].bt;
}

void turn_around()
{
    for(int i=0;i<6;i++)
        s[i].tat = s[i].et-s[i].at;
    waiting();
}

void gantt(int change)
{
    for(int i=0;i<change;i++)
        printf("---%s---|",process[i]); 
    printf("\n%d",timeline[0]);
    for(int i=1;i<=change;i++)
        printf("%9d",timeline[i]);
    printf("\n\n");
}

void srtf()
{
    int completed = 0, current=0;
    int prev=-1;
    int change=0;
    int t=-1;
    printf("|");
    while(completed!=6)
    {
        int idx = -1;
        int min = INT_MAX;
        for(int i=0;i<6;i++)
        {
            if(s[i].at <=current && s[i].rt!=0)
            {
                if(s[i].rt <min)
                {
                    min = s[i].rt;
                    idx = i;
                }
                if(s[i].rt == min)
                {
                    if(s[i].at < s[idx].at)
                    {
                        min = s[i].rt;
                        idx = i;
                    }
                }
            }
        }
        if(idx!=-1)
        {
            if(s[idx].rt == s[idx].bt)
            {
                s[idx].st = current;
            }
            if(idx!=prev)
            {
                strcpy(process[++t],s[idx].pid);
                timeline[t] = current;
                change++;
            }
            s[idx].rt -=1;
            current++;
            prev = idx;
            if(s[idx].rt == 0)
            {
                s[idx].et = current;
                completed++;
            }
        }
        else
            current++;
    }
    timeline[++t]=current;
    gantt(change);
    turn_around();
}

void main()
{
     FILE *fp;
    fp = fopen("input.txt","w");
    if(fp==NULL)
    {
        printf("Could not open file\n");
        exit(0);
    }
    //printf("Input file opened successfully\n");
    fprintf(fp,"%s\t%s\t%s\n","pid","bt","at");
    fprintf(fp,"%s\t%d\t%d\n","P1",7,0);
    fprintf(fp,"%s\t%d\t%d\n","P2",5,1);
    fprintf(fp,"%s\t%d\t%d\n","P3",3,2);
    fprintf(fp,"%s\t%d\t%d\n","P4",1,3);
    fprintf(fp,"%s\t%d\t%d\n","P5",2,4);
    fprintf(fp,"%s\t%d\t%d\n","P6",1,5);
    fclose(fp);
    fp = fopen("input.txt","r");
    if(fp==NULL)
    {
        printf("Error in opening\n");
        exit(0);
    }
    char a[5],b[5],c[5];
    fscanf(fp,"%s\t%s\t%s\n",a,b,c);
    for(int i=0;i<6;i++)
    {
        fscanf(fp,"%s\t%d\t%d\n",s[i].pid, &s[i].bt, &s[i].at);
        s[i].rt = s[i].bt;
    }
    srtf();
    fclose(fp);
    fp = fopen("output.txt","w");
    fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\n","pid","at","st","bt","wt","tat","et");
    for(int i=0;i<6;i++)
        fprintf(fp,"%s\t%d\t%d\t%d\t%d\t%d\t%d\n",s[i].pid,s[i].at,s[i].st,s[i].bt,s[i].wt,s[i].tat,s[i].et);
    fclose(fp);
    float avg_wt=0, avg_tat=0;
    for(int i=0;i<6;i++)
    {
        avg_wt +=s[i].wt;
        avg_tat += s[i].tat;
    }
    avg_wt = avg_wt/6.0;
    avg_tat = avg_tat/6.0;
    fp=fopen("output.txt","r");
    char line[128];
    while(fgets(line,sizeof(line),fp))
        printf("%s",line);
    printf("Average waiting time = %f\nAverage turn around time = %f",avg_wt,avg_tat);
}