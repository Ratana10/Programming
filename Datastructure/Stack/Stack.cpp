#include<iostream>
using namespace std;
#define MAX 10
typedef struct{
    int top;
    int s[MAX];
}Stack;
void initalize(Stack *ps){
    ps->top = -1;
}
bool isFull(Stack *ps){
    if(ps->top == MAX-1)
        return true;
    else
        return false;
}
bool isEmpty(Stack *ps){
    if(ps->top == -1)
        return true;
    else 
        return false;
}
void push(Stack *ps, int value){
    if(isFull(ps)){
        cout<<"Cannot insert the value, stack is overflow"<<endl;
        return ;
    }
    else{
        ps->top++;
        ps->s[ps->top]=value;
    }
}
void pop(Stack *ps){
    if(isEmpty(ps)){
        cout<<"Cannot delete , stack is underflow"<<endl;
        return ;
    }
    else{
        int value = ps->s[ps->top];
        ps->top --;
        cout<<"The value "<<value<<" deleted from the stack"<<endl;
    }
}
int peek(Stack *ps){
   
    return ps->s[ps->top];
}
void display(Stack *ps){
    if(isEmpty(ps)){
        cout<<"Stack is empty"<<endl;
        return ;
    }

    for(int i=ps->top; i>=0; i--){
        cout<<ps->s[i]<<'\t';
    }
}

int main(){
    Stack *ps = new Stack[MAX];
    initalize(ps);
    int ch,number;

    do{
        cout<<"\n--- Stack operation ---"<<endl;
        cout<<"1.Push"<<endl;
        cout<<"2.Pop"<<endl;
        cout<<"3.Peek"<<endl;
        cout<<"4.Display"<<endl;
        cout<<"0.Exit"<<endl;
        cout<<"Enter option : "; cin>>ch;
        switch(ch){
            case 1:
                cout<<"Enter number to insert : "; cin>>number;
                push(ps,number);
                break;
            case 2:
                pop(ps);
                break;
            case 3:
                if(isEmpty(ps)){
                    cout<<"Stack is empty"<<endl;
                }
                else{
                    number = peek(ps);
                    cout<<"The last value is : "<<number<<endl;
                }
                
                break;
            case 4:
                display(ps);
                break;
        }
    }while(ch != 0);

    return 0;
}