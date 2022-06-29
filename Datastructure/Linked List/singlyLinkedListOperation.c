#include<stdlib.h>
#include<stdio.h>
#define newNode (Node*)malloc(sizeof(Node))
typedef struct node{
    int item;
    struct node* next;
}Node;


Node* createNode(Node* s){

    int num;
    Node* tmp=NULL;
    Node* t1=NULL;
    printf("* Note : Enter number -99 to exit\n\n");
    do{
        printf("Enter number : "); scanf("%d",&num);
        if(num != -99){
                tmp = newNode;
            tmp->item = num;
            tmp->next = NULL;

            if(s == NULL){
                s = t1 = tmp;
            }
            else{
                t1->next = tmp;
                t1= t1->next;    
            }
            
        }
    }while( num != -99);
    return s;

}
void display(Node* s){
    if(s == NULL){
        printf("Node List is Empty");
    }
    while( s != NULL){
        printf("%5d", s->item);
        s = s->next;
    }
}
int countNode(Node* s){
    int count=0;
    while( s != NULL){
        s = s->next;
        count++;
    }
    return count;
}
Node* insertNode(Node* s){
    int pos;
    int flag=0;
    Node* tmp =NULL;
    Node* t1 = s;

    tmp = newNode;
    printf("Enter position you want to insert : "); scanf("%d",&pos);
    if( pos >0 && pos <=countNode(s)+1){
        flag = 1;
        printf("Enter number : "); scanf("%d", &tmp->item);
        if(pos == 1){
            tmp->next = s;
            s= tmp;
        }
        else{
            
            while(pos >2 ){
                t1 = t1->next;
                pos--;
            }
            tmp->next = t1->next;
            t1->next = tmp;
        }

    }
    else{
        printf("\nInvalid position");
    }
    if(flag == 1){
        printf("\nInsert successfully");
    }
    return s;
}
Node* deleteNode(Node* s){
    int pos;
    int flag=0;
    Node* t1= s;
    Node* tmp=NULL;
    printf("Enter position you want to delete : "); scanf("%d",&pos);

    if(pos > 0 && pos<= countNode(s)){
        flag = 1;
        if(pos == 1){
            s = s->next;
            free(t1);
        }
        else{
            while( pos > 2){
                t1= t1->next;
                pos--;
            }
            tmp = t1->next;
            t1->next = tmp->next;
            free(tmp);
        }
    }
    if(flag == 1){
        printf("Delete successfully");
    }
    return s;
}
void searchNode(Node* s){
    int num;
    int flag = 0;
    printf("Enter number to search : "); scanf("%d", &num);

    while(s != NULL){
        if( num == s->item){
            flag = 1;
            printf("%d is present ",num);
            break;
        }
        s = s->next;
    }
    if(flag == 0){
        printf("Element Not found");
    }
}
void sortAscending(Node* s){
    int item;
    for(Node* i = s; i->next != NULL; i=i->next){
        for(Node* j= i->next; j!= NULL; j=j->next){
            if(i->item > j->item){
                item = i->item;
                i->item = j->item;
                j->item = item;
            }
        }
    }
    printf("Sorted Ascending successfully");

}
void sortDescending(Node* s){
    int item;
    for(Node* i = s; i->next != NULL; i=i->next){
        for(Node* j= i->next; j!= NULL; j=j->next){
            if(i->item < j->item){
                item = i->item;
                i->item = j->item;
                j->item = item;
            }
        }
    }
    printf("Sorted Descending successfully");

}
Node* clearList(Node* s){
    Node* current= s;
    Node* next = NULL;

    int i=0;
    while( current != NULL){
        next = current->next;
        free(current);
        current = next;
        printf("\nDelete Node %d",++i);
    }
    s = NULL;
    printf("\nClear List successfully");
    return s;
}
void showMenu(){
    printf("\n\nSingly Linked List Operation using Pointer");
    printf("\n1. Display");
    printf("\n2. Count");
    printf("\n3. Insert");
    printf("\n4. Delete");
    printf("\n5. Search");
    printf("\n6. Sort");
    printf("\n7. ClearList");
    printf("\n0. Exit");
}
int main(){
    int ch;
    int ch1;
    Node* start=NULL;
    start = createNode(start);
    do{
        showMenu();
        printf("\nEnter option : "); scanf("%d",&ch);

        switch(ch){
            case 1:
                display(start);
                break;
            case 2:
                printf("Total of node : %d",countNode(start));
                break;
            case 3:
                start = insertNode(start);
                break;
            case 4:
                start = deleteNode(start);
                break;
            case 5:
                searchNode(start);
                break;
            case 6:
                printf("\n1. Ascending Order");
                printf("\n2. Descending Order");
                printf("\nEnter option : "); scanf("%d", &ch1);
                if( ch1 == 1){
                    sortAscending(start);
                }
                else if(ch1 == 2){
                    sortDescending(start);
                }
                break;
            case 7:
                start = clearList(start);
                break;
        }
    }while(ch != 0);
    return 0;
}