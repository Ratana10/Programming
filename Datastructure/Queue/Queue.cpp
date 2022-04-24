#include<iostream>
using namespace std;
#define MAX 10
struct queue{
    int front;
    int rear;
    int que[MAX];
};
void initalize(struct queue *q){
    q->front = 0;
    q->rear = -1;
}
bool isFull(struct queue *q){
    if(q->rear == MAX -1){
        return true;
    }
    else    
        return false;
}
bool isEmpty(struct queue *q){
    if(q->front <0 || q->front > q->rear)
        return true;
    else   
        return false;
}
void enqueue(struct queue *q, int value){
    if(isFull(q)){
        cout<<"queue is overflow"<<endl;
        return ;
    }
    else{
        q->rear++;
        q->que[q->rear] = value;
        cout<<"Insert to queue successfully"<<endl;
    }
}
void dequeue(struct queue *q){
    int value;
    if(isEmpty(q)){
        cout<<"queue is underflow"<<endl;
        return ;
    }
    else{
        value =q->que[q->front];
        q->rear --;
        q->front++;
        cout<<"The number "<<value<<" deleted from queue"<<endl;
    
    }
}
void display(struct queue *q){
    for(int i=0; i<=q->rear; i++){
        cout<<q->que[i]<<'\t';
    }
}
int main(){
   
    struct queue *q = new queue[MAX];
    initalize(q);
    int ch;
    int number;
    do{
        cout<<"1.Enqueue"<<endl;
        cout<<"2.Dequeue"<<endl;
        cout<<"3.Display"<<endl;
        cout<<"0.Exit"<<endl;
        cout<<"Enter option : "; cin>>ch;
        switch (ch)
        {
        case 1:
            cout<<"Enter number to queue : "; cin>>number;
            enqueue(q,number);
            
            break;
        case 2:
            dequeue(q);
            break;
        case 3:
            display(q);
            break;
        default:
            break;
        }
    }while(ch != 0);
    return 0;
}