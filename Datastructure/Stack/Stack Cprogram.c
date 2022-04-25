#include<stdio.h>
#define MAXSIZE 10
typedef struct{
    int top;
    int s[MAXSIZE];
}Stack;

void initalize(Stack *ps){
    ps->top =-1;
}
void push(Stack *ps, int value){
    if(ps->top == MAXSIZE-1){
        printf("Stack over flow\n");
    }
    else{
        ps->top++;
        ps->s[ps->top]=value;
    }
}
int pop(Stack *ps){
    int value;
    if(ps->top == -1){
        printf("Stack under flow\n");
    }
    else{
        value = ps->s[ps->top];
        ps->top--;
        
    }
    
    return value;

}
void display(Stack *ps){
    for(int i=ps->top; i>=0; i--){
        printf("%d\t",ps->s[i]);
    }
}
int main(){
    Stack ps[MAXSIZE];
    initalize(ps);
    int ch;
    do{
        printf("\n1, Push\n2.Pop\n3.Display\n0.Exit\n");
        printf("Enter option : "); scanf("%d",&ch);
        switch(ch){
            case 1: 
                printf("Enter number to insert into stack : ");
                int number;
                scanf("%d",&number);
                push(ps,number);
                break;
            case 2: 
                number = pop(ps);
                printf("Pop number is : %d",number);
                break;
            case 3: 
                display(ps);
                break;
            
        }
    }while(ch != 0);

 
    return 0;
}