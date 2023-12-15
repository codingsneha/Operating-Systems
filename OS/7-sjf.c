#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct time
{
    int bt, st, wt, tat, et, at;
    char pid[2];
} s[4];

void start_time(int i, int current_time) {
    s[i].st = current_time;
}

void end_time(int i) {
    s[i].et = s[i].st + s[i].bt;
}

void waiting_time(int i) {
    s[i].wt = s[i].st - s[i].at;
}

void turn_around(int i) {
    s[i].tat = s[i].wt + s[i].bt;
}

void sjf()
{
    int current_time = 0;

    for (int i = 0; i < 4; i++) {
        if (s[i].at > current_time) {
            current_time = s[i].at;
        }

        start_time(i, current_time);
        end_time(i);
        waiting_time(i);
        turn_around(i);
        current_time = s[i].et;
    }

}

void gantt()
{
    int t=0;
    int end=s[t].et;
    printf("\n|");
    for(int i=0;i<4;i++)
        printf("---%s---|",s[i].pid);
    printf("\n%d",s[0].st);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<7;j++)
            printf(" ");
        printf("%2d",end);
        end = s[++t].et;
    }
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
    fprintf(fp,"%s\t%d\t%d\n","P1",8,0);
    fprintf(fp,"%s\t%d\t%d\n","P2",4,1);
    fprintf(fp,"%s\t%d\t%d\n","P3",9,2);
    fprintf(fp,"%s\t%d\t%d\n","P4",5,3);
    fclose(fp);
    fp = fopen("input.txt","r");
    if(fp==NULL)
    {
        printf("Error in opening\n");
        exit(0);
    }
    char a[5],b[5],c[5];
    fscanf(fp,"%s\t%s\t%s\n",a,b,c);
    for(int i=0;i<4;i++)
        fscanf(fp,"%s\t\t%d\t%d\n",&s[i].pid, &s[i].bt, &s[i].at);
    fclose(fp);
    //sorting acc to arrival time
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3-i;j++)
        {
            if(s[j].at>s[j+1].at)
            {
                struct time k = s[j];
                s[j] = s[j+1];
                s[j+1] = k;
            }
        }
    }
    sjf();
    fp = fopen("output.txt","w");
    fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\n","pid","bt","at","st","et","wt","tat");
    for(int i=0;i<4;i++)
        fprintf(fp,"%s\t%d\t%d\t%d\t%d\t%d\t%d\n",s[i].pid,s[i].bt,s[i].at,s[i].st,s[i].et,s[i].wt,s[i].tat);
    fclose(fp);
    fp=fopen("output.txt","r");
    char line[128];
    while(fgets(line,sizeof(line),fp))
        printf("%s",line);
    fclose(fp);
    gantt();
    printf("\n");
    float avg_wt=0;
    float avg_tat=0;
    for(int i=0;i<4;i++)
    {
        avg_wt += s[i].wt;
        avg_tat += s[i].tat;
    }
    avg_wt = avg_wt/4.0;
    avg_tat = avg_tat/4.0;
    printf("Average waiting time = %f\nAverage turn around time = %f",avg_wt,avg_tat);
}