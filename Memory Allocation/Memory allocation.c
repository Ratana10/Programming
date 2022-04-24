#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student{
    char id[10],name[20],sex[6];
    int age;
};
void input(struct student *st, int n){
        for(int i=0;i<n; i++)
    {
        printf("Enter Id : "); scanf("%s",(st+i)->id);
        printf("Enter name : "); scanf("%s",(st+i)->name);
        printf("Enter Sex : "); scanf("%s",(st+i)->sex);
        printf("Enter age : "); scanf("%d",&(st+i)->age);
        }
}
void output(struct student *st, int n){
    printf("%-10s%-10s%-10s%-10s\n","ID","Name","Sex","Age");
    printf("=================================\n");
    for(int i=0; i<n; i++){
        printf("%-10s%-10s%-10s%-10d\n",(st+i)->id,(st+i)->name,(st+i)->sex,(st+i)->age);
    }
}
int finding(struct student *st, int n){
    int ch,index=-1;
    char find_id[10],find_name[20];

    printf("What you want to enter : \n\t1.ID\n\t2.Name\n\tEnter option : "); scanf("%d",&ch);
    char str[2][10]={"ID","Name"};
    printf("Enter %s :",str[ch-1]);

    if(ch ==1) scanf("%s",find_id);
    else if(ch ==2) scanf("%s",find_name);

    for(int i=0; i<n; i++){
        if(strcmp(find_id,(st+i)->id )==0 || strcmp(find_name,(st+i)->name) == 0){
            index=i;
            break;
        }
    }
    return index;
}

void search(struct student *st, int i){
    printf("%-10s%-10s%-10s%-10s\n","ID","Name","Sex","Age");
    printf("==================================\n");
    printf("%-10s%-10s%-10s%-10d\n",(st+i)->id,(st+i)->name,(st+i)->sex,(st+i)->age);
}
void update(struct student *st, int i){
    int ch;
    do{
        printf("What you want update ?\n\t1.ID\n\t2.Name\n\t3.Sex\n\t4.Age\n\t0.Exit\n\tEnter option");
        scanf("%d",&ch);
        if(ch == 1){
            printf("Enter new ID : "); scanf("%s",(st+i)->id);
            printf("Update Id successful\n");
        }
        else if(ch == 2){
            printf("Enter new Name : "); scanf("%s",(st+i)->name);
            printf("Update name successful\n");
        }
        else if(ch == 3){
            printf("Enter new Sex : "); scanf("%s",(st+i)->sex);
            printf("Update sex successful\n");
        }
        else if(ch == 4){
            printf("Enter new age : "); scanf("%d",&(st+i)->age);
            printf("Update age successful\n");
        }
    }while(ch != 0);
}
void delete(struct student *st, int n,int index){
    for(int i=index; i<n; i++){
        for(int j=i+1; j<n; j++){
            *(st+i) = *(st+j);
        }
    }
}
void sort(struct student *st, int n){
    struct student *temp;

    temp = (struct student*)malloc(sizeof(struct student));
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(strcmp((st+i)->name,(st+j)->name) >0){

                *temp = *(st+i);
                *(st+i) = *(st+j);
                *(st+j) = *temp;
            }
        }
    }
}
void add_more(struct student *st, int n, int n1){
    for(int i=n; i<n+n1; i++){
        printf("Enter Id : "); scanf("%s",(st+i)->id);
        printf("Enter name : "); scanf("%s",(st+i)->name);
        printf("Enter Sex : "); scanf("%s",(st+i)->sex);
        printf("Enter age : "); scanf("%d",&(st+i)->age);
    }
}
void main(){
    int ch,n,n1,index;
    struct student *st;
    do{
    printf("1.Input\n");
    printf("2.Output\n");
    printf("3.Search\n");
    printf("4.Update\n");
    printf("5.Delete\n");
    printf("6.Sort (Name)\n");
    printf("7.Add more \n");
    printf("0.Exit\n");
    printf("Enter option : "); scanf("%d",&ch);
    switch(ch){
        case 1:
            printf("How many student : "); scanf("%d",&n);
            st = (struct student *)calloc(n,sizeof(struct student));
            //calling fuction
            input(st,n);
        break;
        case 2: output(st,n); break;
        case 3:
                index =finding(st,n);
                if(index == -1) printf("Not found !!\n");
                else search(st,index);

        break;
        case 4:
                index = finding(st,n);
                if(index == -1) printf("Not found !!\n");else update(st,index);
        break;
        case 5:
                index = finding(st,n);
                if(index == -1) printf("Not found !!\n");
                else{
                    delete(st,n,index);
                    printf("Delete successful\n");
                     n=n-1;
                }

        break;
        case 6:
                sort(st,n);
                output(st,n);
        break;
        case 7:
                printf("How many student to add more : "); scanf("%d",&n1);

                st = realloc(st,(n1+n)*sizeof(struct student));
                add_more(st,n,n1);
                n=n+n1;

        break;

    }
  }while(ch!=0);
}
