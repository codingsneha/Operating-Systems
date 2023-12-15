#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct time
{
    int bt, at, st, wt, tat, et, rt;
    char pid[2];
} s[6];

int timeline[50];
char process[50][50];
int n;
struct time queue[100];
int qh=0, qt=-1;

void enqueue(struct time p)
{
    for(int i=qh;i<=qt;i++)
    {
        if(strcmp(queue[i].pid,p.pid)==0)
            return;
    }
    queue[++qt] = p;
}
struct time dequeue()
{
    struct time p = queue[qh];
    qh++;
    return p;
}

void waiting()
{
    for(int i=0;i<n;i++)
        s[i].wt = s[i].tat-s[i].bt;
}

void turn_around()
{
    for(int i=0;i<n;i++)
        s[i].tat = s[i].et-s[i].at;
    waiting();
}

void gantt(int change)
{
    printf("\n|");
    for(int i=0;i<change;i++)
        printf("---%s---|",process[i]); 
    printf("\n%d",timeline[0]);
    for(int i=1;i<=change;i++)
        printf("%9d",timeline[i]);
    printf("\n\n");
}

void round_robin(int quantam)
{
    int completed=0, current=s[0].at, t=-1, change=0;
    enqueue(s[0]);
    while(completed!=n)
    {
        struct time p = dequeue();
        int j=0;
        while(strcmp(s[j].pid,p.pid)!=0)
            j++;
        if(s[j].rt==s[j].bt)
            s[j].st=current;
        if(s[j].rt<=quantam && s[j].rt>0)
        {
            strcpy(process[++t],s[j].pid);
            timeline[t]=current;
            change++;
            current=current+s[j].rt;
            s[j].rt=0;
            completed++;
            s[j].et = current;
            for(int i=j+1;i<n;i++)
            {
            if(s[i].at<=current && s[i].rt!=0)
                enqueue(s[i]);
            }   
        }
        else
        {
            strcpy(process[++t],s[j].pid);
            timeline[t]=current;
            change++;
            current = current+quantam;
            s[j].rt = s[j].rt-quantam;
            for(int i=j+1;i<n;i++)
            {
                if(s[i].at<=current && s[i].rt!=0)
                    enqueue(s[i]);
            }
            enqueue(s[j]);
        }
        
    }
    timeline[++t]=current;
    gantt(change);
    turn_around();
}

void main()
{
     FILE *fp;
    fp = fopen("input.txt","w");
    //printf("Input file opened successfully\n");
    fprintf(fp,"%s\t%s\t%s\n","pid","bt","at");
    fprintf(fp,"%s\t%d\t%d\n","P1",5,5);
    fprintf(fp,"%s\t%d\t%d\n","P2",6,4);
    fprintf(fp,"%s\t%d\t%d\n","P3",7,3);
    fprintf(fp,"%s\t%d\t%d\n","P4",9,1);
    fprintf(fp,"%s\t%d\t%d\n","P5",2,2);
    fprintf(fp,"%s\t%d\t%d\n","P6",3,6);
    fclose(fp);
    n=6;
    fp = fopen("input.txt","r");
    char a[5],b[5],c[5];
    fscanf(fp,"%s\t%s\t%s\n",a,b,c);
    for(int i=0;i<n;i++)
    {
        fscanf(fp,"%s\t%d\t%d\n",s[i].pid, &s[i].bt, &s[i].at);
        s[i].rt = s[i].bt;
    }
    fclose(fp);
    //sorting according to arrival time
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(s[j].at>s[j+1].at)
            {
                struct time k = s[j];
                s[j] = s[j+1];
                s[j+1] = k;
            }
        }
    }
    round_robin(3);
    fp = fopen("output.txt","w");
    fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\n","pid","at","st","bt","wt","tat","et");
    for(int i=0;i<n;i++)
        fprintf(fp,"%s\t%d\t%d\t%d\t%d\t%d\t%d\n",s[i].pid,s[i].at,s[i].st,s[i].bt,s[i].wt,s[i].tat,s[i].et);
    fclose(fp);
    float avg_wt=0, avg_tat=0;
    for(int i=0;i<n;i++)
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