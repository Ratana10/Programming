#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct date{
    int month,day,year;
};
struct customer{
    char name[60];
    char acc_no[60];
    char address[20];
    int age;
    char citizenship[20];
    char phone[20];
    char acc_type[20];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
    char password[13];
    char dates[10];
}add,upd,check,rem,transaction;

char *getdate(){
    char *today=(char *)malloc(15);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(today,"%02d/%02d/%02d",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
    return today;
}
void maskPassword(char pass[]){
    char ch; int i=0;
    while((ch = getch()) != 13){
        pass[i]=ch;
        printf("*");
        i++;
    }
    pass[i] ='\0';
}
void loading(int n){
    printf("\n\n\t\t\t\tLoading");
    for(int i=0; i<n; i++){
       printf(".");
       Sleep(500);
    }
    printf("\n\n\n");

}
void encrypt(char password[], int key){
    for(int i=0; i<strlen(password); i++){
        password[i] = password[i] - key;
    }
}
void decrypt(char password[], int key){
    for(int i=0; i<strlen(password); i++){
        password[i] = password[i] + key;
    }
}
int checkdate(int day,int month){
    if(day>=1 && day <=31 && month>=1 && month <=12){
        return 1;
    }
    else return 0;
}
void newaccount(){
    FILE *fp ;

    char *mydate = getdate();

    acc :;
    fp = fopen("customer.txt","a+");
    system("cls");

    printf("\n\t\t\t==============================");
    printf("\n\t\t\t    Create New Account      ");
    printf("\n\t\t\t==============================");

    printf("\n\t\t\t     Today : %s\n\n",mydate);

    printf("\n\t\t\tAccount ID    : "); fflush(stdin); scanf("%[^\n]s",check.acc_no);
    while(fscanf(fp,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address,add.citizenship,add.phone,&add.amt,add.acc_type) != EOF)
    {
        if(strcmp(check.acc_no,add.acc_no) == 0){
            printf("\n\n\t\tAccount Id already in used !!");
             printf("\n\n\t\tTry other Account ID\n\n");
            system("pause");

            goto acc;
        }

    }
    strcpy(add.dates,mydate);
    strcpy(add.acc_no,check.acc_no);
    printf("\n\t\t\tAccount Name  : "); fflush(stdin); scanf("%[^\n]s",add.name);
    printf("\n\t\t\tPassword      : "); maskPassword(add.password); //encrypt(add.password,0xAED);

    again :

    printf("\n\n\t\t\tDate of Birth(dd/mm/yyyy) : ");  scanf("%d/%d/%d",&add.dob.day,&add.dob.month,&add.dob.year);

    if(checkdate(add.dob.day,add.dob.month) == 0 ){
        printf("Invalid Date");
        goto again;
    }
    printf("\n\t\t\tAge           : "); scanf("%d",&add.age);
    printf("\n\t\t\tAddress       : "); fflush(stdin); scanf("%[^\n]s",add.address);
    printf("\n\t\t\tCitizenship number  : "); fflush(stdin); scanf("%[^\n]s",add.citizenship);
    printf("\n\t\t\tPhone Number  : "); fflush(stdin); scanf("%[^\n]s",add.phone);
    printf("\n\t\t\tAmount Deposit: $ "); scanf("%f",&add.amt);
    int ch;
    printf("\n\t\t\tType of account :\n\t\t\t1.Saving\n\t\t\t2.Current"); printf("\n\t\t\tChoose Account Type :"); scanf("%d",&ch);
    if(ch == 1) strcpy(add.acc_type,"Saving");
    else if(ch == 2) strcpy(add.acc_type,"Current");
    strupr(add.name);
    fprintf(fp,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,add.dob.day,add.dob.month,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.amt,add.acc_type);
    fclose(fp);
    printf("\n\n\n\t\t\t=====>CREATE NEW ACCOUNT SUCCESSFULLY<=====\n\n");
    system("pause");
}

void updateaccount(){
    int f=0, ch,k;
    FILE *fp,*newrec;
    fp = fopen("customer.txt","r");
    newrec = fopen("temp.txt","w");


    system("cls");
    printf("\n\t\t\t============================");
    printf("\n\t\t\t      UPDATE ACCOUNT        ");
    printf("\n\t\t\t============================\n");
    printf("\n\t\t\tEnter Account ID : "); fflush(stdin); gets(check.acc_no);
    loading(2);
    while(fscanf(fp,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address,add.citizenship,add.phone,&add.amt,add.acc_type) != EOF)
    {
        if(strcmp(check.acc_no,add.acc_no) == 0){
            f=1;
            do{
                system("cls");
                printf("\n\t\t\t============================");
                printf("\n\t\t\t      UPDATE ACCOUNT        ");
                printf("\n\t\t\t============================\n");
                printf("\n\t\t\tCurrent Account ID : %s",add.acc_no);
                printf("\n\t\t\tWhich information you want to change ");
                printf("\n\t\t\t1.Account ID");
                printf("\n\t\t\t2.Account Name");
                printf("\n\t\t\t3.Account Password");
                printf("\n\t\t\t0.Back");
                printf("\n\t\t\t============================\n");
                printf("\n\t\t\tEnter Option : "); scanf("%d",&ch);
                switch(ch){
                    case 1:
                        acc : ;
                        k = 0;
                        system("cls");
                        printf("Enter New Account ID : "); fflush(stdin); gets(add.acc_no);
                        printf("\n\t\t\t=====>UPDATE ACCOUNT ID SUCCESFULLY<=====\n\n");
                        system("pause");
                    break;
                    case 2:
                        printf("Enter New Account Name : "); fflush(stdin); gets(add.name);
                        printf("\n\t\t\t=====>UPDATE ACCOUNT NAME SUCCESFULLY<=====\n\n");
                        system("pause");
                    break;
                    case 3:
                         printf("Enter New Account Password : "); fflush(stdin); gets(add.password);
                         printf("\n\t\t\t=====>UPDATE ACCOUNT PASSWORD SUCCESFULLY<=====\n\n");
                         system("pause");
                    break;
                    case 0:
                        fprintf(newrec,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,add.dob.day,add.dob.month,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.amt,add.acc_type);
                    break;

                }
            } while(ch != 0);
        }else
        {
          fprintf(newrec,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,add.dob.day,add.dob.month,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.amt,add.acc_type);

        }
    }

    fclose(fp);
    fclose(newrec);
    remove("customer.txt");
    rename("temp.txt","customer.txt");
    if(f == 0){
        printf("\n\t\t\t=====>ACCOUNT CANNOT FOUND<=====\n\n");
        system("pause");
    }

}
void deleteaccount(){
    int f=0;
    FILE *fp,*newrec;
    fp = fopen("customer.txt","r");
    newrec = fopen("temp.txt","w");
    system("cls");
    printf("\n\t\t\t============================");
    printf("\n\t\t\t      DELETE ACCOUNT        ");
    printf("\n\t\t\t============================\n");
    printf("\n\t\t\tEnter Account ID : "); fflush(stdin); gets(check.acc_no);
    loading(4);
    while(fscanf(fp,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address,add.citizenship,add.phone,&add.amt,add.acc_type) != EOF)
    {
        if(strcmp(check.acc_no,add.acc_no)==0){
            f=1;
        }
        else{
         fprintf(newrec,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,add.dob.day,add.dob.month,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.amt,add.acc_type);

        }
    }
    fclose(fp);
    fclose(newrec);

     remove ("customer.txt");
     rename ("temp.txt","customer.txt");

     if(f ==1) printf("\n\n\t\t\t=====>DELETE ACCOUNT SUCCESFULLY<=====\n\n");
     else if(f==0) printf("\n\n\t\t\t=====>ACCOUNT NOT FOUND<=====\n\n");
     system("pause");


}
void viewallaccount(){
    int f=0;
    FILE *fp = fopen("customer.txt","r");

    system("cls");
    printf("\n\t\t\t============================");
    printf("\n\t\t\t    VIEW LIST CUSTOMER      ");
    printf("\n\t\t\t============================\n");
    loading(2);
    system("cls");
    printf("\n%-10s%-10s%-10s%-20s%-10s%-10s%-15s%-15s%-10s","Account","Name","PS","Dateofbirth","Age","Address","Account type","PhoneNumber","Cityzenship");
    printf("\n===================================================================================================\n");
    while(fscanf(fp,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address,add.citizenship,add.phone,&add.amt,add.acc_type) != EOF)
    {
        f=1;
        printf("%-10s%-12s%-12s%d/%d/%-10d%-12d%-10s%-12s%-15s%-10s\n",add.acc_no,add.name,add.password,add.dob.day,add.dob.month,add.dob.year,add.age,add.address,add.acc_type,add.phone,add.citizenship);
    }
    if(f == 0) printf("\n\n\t\t\t=====>NO ACCOUNT RECORD<=====\n\n");
    printf("\n===================================================================================================\n");
    fclose(fp);


    system("pause");
}
float interest(float t,float amount,int rate){
    float si;
    si = (rate*t*amount)/100.0;
    return si;
}
void viewaccount(){
    int rate,f=0;
    float times;
    float intrst;
    FILE *fp = fopen("customer.txt","r");

    system("cls");
    printf("\n\t\t\t============================");
    printf("\n\t\t\t      SEARCH ACCOUNT        ");
    printf("\n\t\t\t============================\n");

    printf("\n\n\t\t\tEnter Account ID : "); scanf("%s",check.acc_no);
    loading(4);


    while(fscanf(fp,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address,add.citizenship,add.phone,&add.amt,add.acc_type) != EOF)
    {
        //decrypt(add.password,0xAED);
        if(strcmp(add.acc_no,check.acc_no) == 0){
            system("cls");
            f=1;
            printf("\n\t\t\t============================");
            printf("\n\t\t\t      SEARCH ACCOUNT        ");
            printf("\n\t\t\t============================\n");
            printf("\n\n\n\t\t\tnAccount ID    : %s",add.acc_no);
            printf("\n\t\t\tAccount Name  : %s",add.name);
            printf("\n\t\t\tPassword      : %s",add.password);
            printf("\n\t\t\tDate of Birth : %d/%d/%d",add.dob.day,add.dob.month,add.dob.year);
            printf("\n\t\t\tAge           : %d",add.age);
            printf("\n\t\t\tAddress       : %s",add.address);
            printf("\n\t\t\tCitizenship number  : %s",add.citizenship);
            printf("\n\t\t\tPhone Number    : %s",add.phone);
            printf("\n\t\t\tType of account : %s",add.acc_type);
            printf("\n\t\t\tCurrent Balance : $ %.2f",add.amt);
            printf("\n\t\t\tDate Deposit    : %s",add.dates);
            if(strcmp(add.acc_type,"Saving") ==0){

                    times = (1.0/12.0);
                    rate = 8;
                    intrst = interest(times,add.amt,rate);
                printf("\nYou will get $%.2f as interest every month",intrst);
            }
           else if(strcmp(add.acc_type,"Current") ==0){
                printf("\nYou will get no interest");
            }
        }
    }
    fclose(fp);
    if(f == 0)  printf("\n\n\n\t\t\t=====>ACCOUNT NOT FOUND<=====\n\n");
    else        printf("\n\n\n\t\t\t=====>ACCOUNT FOUND<=====\n\n");
    system("pause");

}
void transactionmoney(){
    char *mydate = getdate();
    int ch,f=0;



    FILE *fp,*newrec;
    fp = fopen("customer.txt","r");
    newrec = fopen("temp.txt","w");

    system("cls");
    printf("\n\t\t\t============================");
    printf("\n\t\t\t        TRANSACTION         ");
    printf("\n\t\t\t============================\n");
    printf("\n\t\t\tEnter Account ID : "); fflush(stdin); scanf("%[^\n]s",check.acc_no);
    printf("\n\t\t\tEnter Password   : "); fflush(stdin); maskPassword(check.password);

    loading(2);
    while(fscanf(fp,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address,add.citizenship,add.phone,&add.amt,add.acc_type) != EOF)
    {
        //decrypt(add.password,0xAED);
        if(strcmp(check.acc_no,add.acc_no)==0 && strcmp(check.password,add.password)==0){
                f=1;
            do{
                system("cls");

                printf("\n\t\t\t============================");
                printf("\n\t\t\t        TRANSACTION         ");
                printf("\n\t\t\t============================\n");
                printf("\n\t\t\t       Today : %s",mydate);
                printf("\n\n\t\t\t   BALANCE : %.2f\n\n",add.amt);
                printf("\n\t\t\t1.Deposit");
                printf("\n\t\t\t2.Withdraw");
                printf("\n\t\t\t0.Back");
                printf("\n\t\t\t============================\n");
                printf("\n\t\t\t            Enter option : "); scanf("%d",&ch);
                switch(ch){
                case 1:
                    system("cls");
                    printf("\n\t\t\t============================");
                    printf("\n\t\t\t           DEPOSIT          ");
                    printf("\n\t\t\t============================\n");
                    printf("\n\t\t\tCurrent Date : %s",mydate);
                    strcpy(transaction.dates,mydate);
                    printf("\n\n\t\t\t   BALANCE : %.2f\n\n",add.amt);
                    printf("\n\n\n\tInput amount to deposit : "); scanf("%f",&transaction.amt);
                    add.amt += transaction.amt;


                    printf("\n\n\t\t\t=====>DEPOSIT SUCESSFULLY<=====\n\n");
                    system("pause");
                    break;
                case 2:
                    again :

                    system("cls");
                    printf("\n\t\t\t============================");
                    printf("\n\t\t\t          WITHDARW          ");
                    printf("\n\t\t\t============================\n");
                    printf("\n\t\t\tCurrent Date : %s",mydate);
                    strcpy(transaction.dates,mydate);
                    printf("\n\n\t\t\t    BALANCE : %.2f",add.amt);
                    printf("\n\n\tInput amount to withdraw : "); scanf("%f",&transaction.amt);
                    if(transaction.amt > add.amt){
                        printf("\n\n\t\t\t=====>NOT ENOUGH MONEY<=====\n\n");
                        printf("\t\t\t=====>WITHDRAW UNSUCESSFUL<=====\n\n");
                        system("pause");
                        goto again;
                    }
                    add.amt -= transaction.amt;


                    printf("\n\n\t\t\t=====>WITHDRAW SUCESSFULLY<=====\n\n");
                    system("pause");
                    break;
                case 0:
                        fprintf(newrec,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,transaction.dates,add.dob.day,add.dob.month,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.amt,add.acc_type);

                    break;
                }

            }while(ch !=0);


        }
        else{
            fprintf(newrec,"%s %s %s %s %d/%d/%d %d %s %s %s %f %s\n",add.acc_no,add.name,add.password,add.dates,add.dob.day,add.dob.month,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.amt,add.acc_type);

        }

    }
    fclose(fp);
    fclose(newrec);

     remove ("customer.txt");
     rename ("temp.txt","customer.txt");

    if(f==0) printf("\n\n\t\t\t=====>WRONG OR INCORRECT PASSWORD<=====\n\n");
    system("pause");

}
void welcome(){
    printf("\n\t\t\t=================================");
    printf("\n\t\t\t|                               |");
    printf("\n\t\t\t|    WELCOME TO C BANK SYSTEM   |");
    printf("\n\t\t\t|                               |");
    printf("\n\t\t\t|===============================|");
    printf("\n\t\t\t|        Build By Ratana        |");
    printf("\n\t\t\t|*******************************|");
    printf("\n\t\t\t");
    for(int i=0; i<33; i++)
        printf("\xB4");
}
void main(){
    int ch,ch1;
    welcome();
    loading(7);
     do{
        system("cls");
        printf("\n\t\t\t============================");
        printf("\n\t\t\t         MAIN MENU           ");
        printf("\n\t\t\t============================\n");
        printf("\n\t\t\t1. Admin");
        printf("\n\t\t\t2. Transaction");
        printf("\n\t\t\t3. Create New account");
        printf("\n\t\t\t0. Exit");
        printf("\n\t\t\t============================");
        printf("\n\t\t\t            Enter option : "); scanf("%d",&ch);
        switch(ch){
        case 1:
                if(1){
                    do{
                        system("cls");
                        printf("\n\t\t\t============================");
                        printf("\n\t\t\t           ADMIN            ");
                        printf("\n\t\t\t============================\n");
                        printf("\n\t\t\t1.Update Account");
                        printf("\n\t\t\t2.Delete Account");
                        printf("\n\t\t\t3.Search Account");
                        printf("\n\t\t\t4.View All Customer list");
                        printf("\n\t\t\t0.Back");
                        printf("\n\t\t\t============================");
                        printf("\n\t\t\tEnter option : "); scanf("%d",&ch1);
                        switch(ch1){
                            case 1: updateaccount(); break;
                            case 2: deleteaccount(); break;
                            case 3: viewaccount(); break;
                            case 4:viewallaccount(); break;

                        }

                    }while(ch1 != 0);
                }
                else{
                    loading(2);
                    printf("\n\t\t\tWrong Username or Password !!");
                    printf("\n\t\t\tTry again\n\n");
                    system("pause");
                }
            break;
        case 2: transactionmoney(); break;
        case 3: newaccount(); break;

        }

     }while(ch!=0);
     printf("\n\n\t\t\t=====>THANK YOU<=====\n\n");
    getch();
}

