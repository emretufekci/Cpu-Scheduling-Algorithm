
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#define LINE_MAX 1024
struct node
{
    int burstTime,arrivalTime,priority,pNum;
    struct node *next;
};
struct node * header;

struct calc
{
    int turnArroundTime,waitingTime,serviceTime;
    struct calc *next;
};
struct calc * root;

unsigned int num[LINE_MAX];
//SORT FUNCTIONS - AND THERE IS SOME LL FUNC. IT USED FOR SORTING
void sortArrival(struct node *header);
void sortBurst(struct node *header);
void sortPriority(struct node *header);
void swap();
//FILE FUNCTIONS
void write_file();
void read_file();
void fcfs();
void sjf();
void priority();
void reset_file();
void print_file();
//VARIABLES FOR INPUT - OUTPUT SECTION
char *input_file=NULL;
char *output_file=NULL;


//BELOW FUNCTIONS ARE FOR THE LL OPERATIONS
bool is_empty(struct node *header);
struct node * createNode(int bt,int at,int p, int pNum);
struct node * insertBack(struct node *header, int bt,int at, int p,int pNum);
struct node * deleteFront(struct node *header);
int sizeOfLL(struct node *header);
void display(struct node *header);

//MENU
void menu();
char *mod="Nonpreemptive";
int mode=0;
//MAIN FUNCTION STARTS HERE
int main (int argc, char **argv){
    root=(struct calc*)malloc(sizeof(struct calc*));
    root->serviceTime=0;
    root->waitingTime=0;

    int option_index = 0;
    while (( option_index = getopt(argc, argv, "f:o:"))  != -1) {
        switch (option_index) {
            case 'f':
                input_file = optarg;
                read_file();
                break;
            case 'o':
                output_file = optarg;
                reset_file();
                break;
            default:
                printf("Incorrect Option\n");
                return 1;
        }
    }
menu();
  return 0;
}






//MENU 
void menu(){

int select;
printf("\t\t\tCPU SCHEDULER SIMULATOR  ");
printf("[MODE:%s]\n",mod);
printf("\t1) Scheduling Method\n");
printf("\t2) Preemptive Mod\n");
printf("\t3) Non-Preemtpive Mod\n");
printf("\t4) Show Result\n");
printf("\t5) End Program\n");
printf("Option >");
int input;
scanf("%d",&input);
switch(input){
case 1:
printf("In THE NON PREEMPTIVE MODE\n");
printf("1) First Come First Served Scheduling\n");
printf("2) Shortest Job First Scheduling\n");
printf("3) Shortest Job First Scheduling[PREEMPTIVE][X]\n");
printf("4) Priority Scheduling\n");
printf("5) Priority Scheduling[X]\n");
printf("6) Rouind Robin Scheduling[PREEMPTIVE][X]\n");
printf("7) Back To Menu\n");
printf("Option>");
scanf("%d",&select);
if(select==1)
{
fcfs();
menu();
}
else if(select==2)
{
sjf();
menu();
}
else if(select==4)
{
priority();
menu();
}
else if(select==7)
menu();
else
{
printf("Wrong Selection");
menu();
}
break;
case 2:
printf("<<<<<THIS MOD IS NOT READY YET>>>>>>\n");
menu();
break;
case 3:
mod="Nonpreemptive";
mode = 0;
menu();
scanf("%d",&input);
break;
case 4:
print_file();
menu();
break;
case 5:
exit(0);
break;
default:
printf("\n\n");
printf("YOU SELECTED WRONG OPTION PLEASE CHECK THE MENU AGAIN\n");
printf("\n\n");
menu();
break;
}
}


//WHEN PROGRAM START - THIS IS RESET THE OUTPUT FILE
void reset_file(){
    FILE *fp;
    
    fp = fopen(output_file, "w");
    fprintf(fp,"");
    fclose(fp);
    
    return;}

//THIS FOR READ(GET) THE VALUES FROM INPUT
void read_file(){
    
    FILE *fp;
    char line[LINE_MAX];
    int bt,at,p;
    int pn=1;
    
    if ((fp = fopen(input_file, "r")) == NULL)
        return;
    while (fgets(line, LINE_MAX, fp) != NULL) {

        sscanf(line,"%d:%d:%d\n",&bt,&at,&p);
        header=insertBack(header,bt,at,p,pn);
        pn++;
    }
    fclose(fp);
}

void print_file(){
  FILE *fp;
    char line[LINE_MAX];

    if ((fp = fopen(output_file, "r")) == NULL)
        exit(0);
    while (fgets(line, LINE_MAX, fp) != NULL) {

        printf("%s",line);
    }
    fclose(fp);
}


/*BELOW OF THIS CODES FOR SCHEDULER ALGORITHM */

//NON-PREEMPTIVE
void fcfs(){
    struct node *tempHeader;
    struct calc *tempRoot;
    double avgWaitingTime=0;
    tempHeader=header;
    tempRoot=root;
    int i=1;
    int SIZE = sizeOfLL(tempHeader);
    FILE *fp;
    fp = fopen(output_file,"a");
    
    
    fprintf(fp,"===========================================\n");
    fprintf(fp,"Scheduling Method: First Come First Served\n");
    fprintf(fp,"Process Waiting Times:\n");
    for(i=1; i<=SIZE; i++){
        
        avgWaitingTime+=tempRoot->waitingTime;
        fprintf(fp,"P%d: %d ms\n",(tempHeader->pNum),(tempRoot->waitingTime));
        
        tempRoot->next=(struct calc*)malloc(sizeof(struct calc*));
        tempRoot->next->serviceTime=tempRoot->serviceTime+tempHeader->burstTime;
        
        if(tempHeader->next!=NULL){
            tempRoot->next->waitingTime=tempRoot->next->serviceTime-tempHeader->next->arrivalTime;
            
            
            tempHeader=tempHeader->next;
            tempRoot=tempRoot->next;
        }
        
    }
    avgWaitingTime=avgWaitingTime/SIZE;
    fprintf(fp,"Average Waiting Time: %f ms\n",avgWaitingTime);
    fprintf(fp,"===========================================\n");
    fclose(fp);
printf("\n\n");
    printf("FIRST COME FIRST SERVED SCHEDULER ANSWER STORED IN THE <<<%s>>>\n",output_file);
printf("\n\n");
}

void sjf(){
    struct node *tempHeader;
    struct calc *tempRoot;
        struct node *sortedId;
    double avgWaitingTime=0;
        int checker=0;
        struct node *tempChecker;

    tempHeader=header;
    tempRoot=root;
        tempChecker=tempHeader;
        sortBurst(tempHeader);
        sortArrival(tempHeader);
    int i=1;
    int SIZE = sizeOfLL(tempHeader);
        int sorterpNum[SIZE];
        int sorterWt[SIZE];
        int k,temp,j,n,temp2;
        n=SIZE;

    FILE *fp;
    fp = fopen(output_file,"a");

    fprintf(fp,"===========================================\n");
    fprintf(fp,"Scheduling Method: Shortest Job First\n");
    fprintf(fp,"Process Waiting Times:\n");
    for(i=1; i<=SIZE; i++){
        avgWaitingTime+=tempRoot->waitingTime;
        sorterpNum[i-1]=tempHeader->pNum;
        sorterWt[i-1]=tempRoot->waitingTime;

        tempRoot->next=(struct calc*)malloc(sizeof(struct calc*));
        tempRoot->next->serviceTime=tempRoot->serviceTime+tempHeader->burstTime;

        if(tempHeader->next!=NULL){

            tempHeader=tempHeader->next;
            tempRoot=tempRoot->next;
                if(tempHeader->next!=NULL);
                sortBurst(tempHeader);
            tempRoot->waitingTime=tempRoot->serviceTime-tempHeader->arrivalTime;

    }
}

for(k=0;k<n;++k)
for(j=0;j<(n-k);++j)
if(sorterpNum[j]>sorterpNum[j+1])
{
    temp=sorterpNum[j];
    sorterpNum[j]=sorterpNum[j+1];
    sorterpNum[j+1]=temp;

    temp2=sorterWt[j];
    sorterWt[j]=sorterWt[j+1];
    sorterWt[j+1]=temp2;

}

        for(i=0; i<n; i++)
{
        fprintf(fp,"P%d: %d ms\n",sorterpNum[i],sorterWt[i]);

}

    avgWaitingTime=avgWaitingTime/SIZE;
    fprintf(fp,"Average Waiting Time: %f ms\n",avgWaitingTime);
    fprintf(fp,"===========================================\n");
    fclose(fp);
printf("\n\n");
    printf("Shortest Job First SCHEDULER ANSWER STORED IN THE <<<%s>>>\n",output_file);
printf("\n\n");
}

void priority(){
    struct node *tempHeader;
    struct calc *tempRoot;
        struct node *sortedId;
    double avgWaitingTime=0;
        int checker=0;
        struct node *tempChecker;

    tempHeader=header;
    tempRoot=root;
        tempChecker=tempHeader;
        sortPriority(tempHeader);
        sortArrival(tempHeader);
    int i=1;
    int SIZE = sizeOfLL(tempHeader);
        int sorterpNum[SIZE];
        int sorterWt[SIZE];
        int k,temp,j,n,temp2;
        n=SIZE;

    FILE *fp;
    fp = fopen(output_file,"a");

    fprintf(fp,"===========================================\n");
    fprintf(fp,"Scheduling Method: Priority\n");
    fprintf(fp,"Process Waiting Times:\n");
    for(i=1; i<=SIZE; i++){
        avgWaitingTime+=tempRoot->waitingTime;
        sorterpNum[i-1]=tempHeader->pNum;
        sorterWt[i-1]=tempRoot->waitingTime;

        tempRoot->next=(struct calc*)malloc(sizeof(struct calc*));
        tempRoot->next->serviceTime=tempRoot->serviceTime+tempHeader->burstTime;

        if(tempHeader->next!=NULL){

            tempHeader=tempHeader->next;
            tempRoot=tempRoot->next;
                if(tempHeader->next!=NULL);
                sortPriority(tempHeader);
            tempRoot->waitingTime=tempRoot->serviceTime-tempHeader->arrivalTime;

    }
}

for(k=0;k<n;++k)
for(j=0;j<(n-k);++j)
if(sorterpNum[j]>sorterpNum[j+1])
{
    temp=sorterpNum[j];
    sorterpNum[j]=sorterpNum[j+1];
    sorterpNum[j+1]=temp;

    temp2=sorterWt[j];
    sorterWt[j]=sorterWt[j+1];
    sorterWt[j+1]=temp2;

}

        for(i=0; i<n; i++)
{
        fprintf(fp,"P%d: %d ms\n",sorterpNum[i],sorterWt[i]);

}

    avgWaitingTime=avgWaitingTime/SIZE;
    fprintf(fp,"Average Waiting Time: %f ms\n",avgWaitingTime);
    fprintf(fp,"===========================================\n");
    fclose(fp);
printf("\n\n");
    printf("Priority SCHEDULER ANSWER STORED IN THE <<<%s>>>\n",output_file);
printf("\n\n");
}

/* BELOW OF THIS CODES FOR  LL QUEUE OPERATIONS */
bool is_empty(struct node *header){
    if(header==NULL)
        return true;
    else
        return false;
}

struct node * createNode(int bt,int at,int p,int pn){
    
    struct node * temp;
    temp = (struct node *)malloc(sizeof(struct node));
    //VALUES ARE COMING FROM TEXT FILE!
    temp->burstTime=bt;
    temp->arrivalTime=at;
    temp->priority=p;
    temp->pNum=pn;
    temp->next=NULL;
    return temp;
}

struct node * insertBack(struct node *header, int bt,int at,int p,int pn){
    struct node * temp = createNode(bt,at,p,pn);
    struct node * headertemp;
    if (header == NULL)
    {
        header = temp;
        return header;
    }
    headertemp=header;
    while(headertemp->next != NULL)
        headertemp=headertemp->next;
    headertemp->next = temp;
    return header;
}
struct node *deleteFront(struct node *header)
{
    struct node *temp;
    if(header==NULL)
        return header;
    temp=header;
    header= header->next;
    free(temp);
    return header;
}


void display(struct node *header)
{
    int cnt=1;
    if (header == NULL)
        printf("List is empty\n");
    
    struct node *temp = header;
    printf("===============================================================\n");
    while (temp != NULL)
    {
        printf("FOR P%d ---> Burst Time:%d ||  Arrival Time:%d ||  Priority:%d \n",temp->pNum,temp->burstTime,temp->arrivalTime,temp->priority);
        cnt++;
        temp=temp->next;
    }
    printf("===============================================================\n");
    
    printf("\n");
}

int sizeOfLL(struct node *header){
    struct node *temp=header;
    int cnt=0;
    if(temp!=NULL)
        while(temp!=NULL){
            temp=temp->next;
            cnt++;
        }
    free(temp);
    return cnt;
    
}

//SORT ALGORITHMS

void swap(struct node * x, struct node * y){
    
    int temp_burstTime=x->burstTime;
    x->burstTime=y->burstTime;
    y->burstTime=temp_burstTime;
    
    int temp_arrivalTime=x->arrivalTime;
    x->arrivalTime=y->arrivalTime;
    y->arrivalTime=temp_arrivalTime;
    
    int temp_priority=x->priority;
    x->priority=y->priority;
    y->priority=temp_priority;
    
    int temp_pNum=x->pNum;
    x->pNum=y->pNum;
    y->pNum=temp_pNum;
}

void sortBurst(struct node *header){
    int control=1;
    struct node*tempHeader=header;
    struct node*tempSort;
    if(tempHeader==NULL)
        exit(0);
    
    while(control){
        control=0;
        tempHeader=header;
        while(tempHeader->next!=NULL) {
            if(tempHeader->burstTime>tempHeader->next->burstTime)
            {
                swap(tempHeader,tempHeader->next);
                control=1;
            }
            tempHeader=tempHeader->next;
        }
        tempSort=tempHeader;
    }
        header=tempSort;
}

void sortArrival(struct node *header){
    
    int control=1;
    struct node *tempHeader=header;
    struct node *tempSort;
    if (tempHeader == NULL)
        exit(0);
    
    while(control){
        control=0;
        tempHeader=header;
        
        while (tempHeader->next!=NULL) {
            if (tempHeader->arrivalTime>tempHeader->next->arrivalTime)
            {
                swap(tempHeader,tempHeader->next);
                control=1;
            }
            tempHeader=tempHeader->next;
        }
        tempSort=tempHeader;
    }
        header=tempSort;    
}

void sortPriority(struct node *header){

    int control=1;
    struct node *tempHeader=header;
    struct node *tempSort;
    if (tempHeader == NULL)
        exit(0);
    
    while(control){
        control=0;
        tempHeader=header;
        
        while (tempHeader->next!=NULL) {
            if (tempHeader->priority>tempHeader->next->priority)
            {
                swap(tempHeader,tempHeader->next);
                control=1;
            }
                
            tempHeader=tempHeader->next;
        }
        tempSort=tempHeader;
    }




        header=tempSort;    
}



