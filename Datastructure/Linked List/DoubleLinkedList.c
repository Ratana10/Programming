#include <stdio.h>
#include <stdlib.h>
struct node{
    int num;
    struct node *prevptr;
    struct node *nextptr;
}*stnode,*ennode;

void createListNode(int n){
    struct node *newnode;
    int num;
    
    stnode = (struct node *)malloc(sizeof(struct node));
    if(stnode == NULL){
        printf("Memory cann't allocated");
        return ;
    }
    else{
        printf("Input number for node [1] : "); scanf("%d",&num);
        stnode->num = num;
        stnode->prevptr = NULL;
        stnode->nextptr = NULL;
        ennode = stnode;
        
        for(int i=2; i<=n; i++){
            newnode = (struct node *)malloc(sizeof(struct node));
            if(newnode == NULL){
                printf("Memory cann't allocated");
                break;
            }
            else{
                printf("Input number for node [%d] : ",i); scanf("%d",&num);
                newnode->num = num;
                newnode->prevptr = ennode;
                newnode->nextptr = NULL;
                
                ennode->nextptr = newnode;
                ennode = newnode;
            }
        }
    }
    
}

void displayNodeList(){
    struct node *tmp;
    if(stnode == NULL){
        printf("Node list is empty");
        return ;
    }
    else{
        tmp = stnode;
        int i=1;
        while(tmp != NULL){
            printf("node [%d] : %d\n",i++,tmp->num);
            tmp = tmp->nextptr;
        }
    }
}
void reverseNodeList(){
    struct node *tmp;
    if(stnode == NULL){
        printf("Node list is empty");
        return ;
    }
    else{
        tmp = ennode;
        int i=1;
        while(tmp != NULL){
            printf("node [%d] : %d\n",i++,tmp->num);
            tmp = tmp->prevptr;
        }
    }
}
void insertNodetoBeg(int num){
    struct node *newnode;
    
    newnode = (struct node *)malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("Memory cann't allocated");
        return ;
    }
    newnode->num = num;
    newnode->prevptr = NULL;
    newnode->nextptr = stnode;
    stnode->prevptr = newnode;
    stnode = newnode;
    
}
void insertNodetoEnd(int num){
    struct node *newnode;
    
    newnode = (struct node *)malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("Memory cann't allocated");
        return ;
    }
    newnode->num = num;
    newnode->prevptr = ennode;
    newnode->nextptr = NULL;
    
    ennode->nextptr = newnode;
    ennode = newnode;
    
}
int insertNodetoAnyPosition(int num,int n){
    struct node *newnode,*tmp;
    int isFound = 0;
    newnode = (struct node *)malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("Memory cann't allocated");
        return 0;
    }
    
    tmp = stnode;
    
    for(int i=1; i<n-1; i++){
        isFound = 1;
        tmp = tmp->nextptr ;
        if(tmp == NULL){
            isFound = 0;
            break;
        }
    }
    if(n == 1){
        isFound = 1;
        insertNodetoBeg(num);
    }
    if(isFound == 1 && n!= 1){
        
        newnode->num = num;
        newnode->prevptr = tmp;
        newnode->nextptr = tmp->nextptr;
        tmp->nextptr = newnode;
    }
    
    return isFound;
    
}
void deleteNodeatBeg(){
    struct node *tmp;
    if(stnode == NULL){
        printf("Node list is empty");
        return ;
    }
    else{
        tmp = stnode;
        stnode = stnode->nextptr;
        stnode->prevptr = NULL;
        printf("The number : %d  at the first node deleted successfully",tmp->num);
        free(tmp);
    }
    
}
void deleteNodeatEnd(){
    struct node *tmp;
    if(stnode == NULL){
        printf("Node list is empty");
        return ;
    }
    else{
        tmp = ennode;
        ennode = ennode->prevptr;
        ennode->nextptr = NULL;
        printf("The number : %d  at the end node deleted successfully",tmp->num);
        free(tmp);
    }
}
int deleteNodeatAnyPosition(int n){
    struct node *tmp;
    if(stnode == NULL){
        printf("Node list is empty");
        return 0;
    }
    int isFound = 0;
    tmp = stnode;
    int i;
    for(i=1; i<n; i++){
        isFound = 1;
        tmp = tmp->nextptr;
        if(tmp == NULL){
            isFound = 0;
            break;
        }
    }
    
    if(n==1){
        isFound = 1;
        deleteNodeatBeg();
    }
    if(isFound == 1 && n!= 1){
        tmp->prevptr->nextptr = tmp->nextptr;
        tmp->nextptr->prevptr = tmp->prevptr;
        printf("The number : %d  at the %d node deleted successfully",tmp->num,n);
        free(tmp);
        
    }
    
    return isFound;
}
int findElement(int num){
    struct node *tmp;
    int pos=1;
    if(stnode == NULL){
        printf("Node List is empty");
        return 0;
    }
    else{
        tmp = stnode;
        while(tmp->nextptr != stnode){
            if(tmp->num == num){
                break;
            }
            else{
                pos++;
            }
            tmp = tmp->nextptr;
        }
    }
    
    return pos;
    
}
int main()
{
    int ch,isFound=0;
    int number,pos,n;
    do{
        printf("\n\n Double Linked List Exercise \n");
        printf("1.Input Node List\n");
        printf("2.Display Node List\n");
        printf("3.Reverse Node List\n");
        printf("4.Insert Node to beginning\n");
        printf("5.Insert Node to end\n");
        printf("6.Insert Node to anyposition\n");
        printf("7.Delete Node at beginning\n");
        printf("8.Delete Node at end\n");
        printf("9.Delete Node at anyposition\n");
        printf("10.Find element\n");
        printf("0.Exit\n");
        printf("----------------------\n");
        printf("Enter option : "); scanf("%d",&ch);
        switch(ch){
            case 1: 
                   printf("Input number of node : "); scanf("%d",&n);
                   createListNode(n);
                   
            break;
            case 2: 
                    printf("The number you entered in the node are \n\n");
                    displayNodeList();
            break;
            case 3: 
                    printf("The reverse Node list are \n\n");
                    reverseNodeList();
            break;
            case 4: 
                    printf("Input number to insert into beginning : "); scanf("%d",&number);
                    insertNodetoBeg(number);
                    printf("Insert Successfully");
            break;
            case 5: 
                    printf("Input number to insert into end : "); scanf("%d",&number);
                    insertNodetoEnd(number);
                    printf("Insert Successfully");
            break;
            case 6: 
                    printf("Input number to insert into any position : "); scanf("%d",&number);
                    printf("Input position you want to insert : "); scanf("%d",&n);
                    isFound = insertNodetoAnyPosition(number,n);                // cannot delete the last node in this case
                    if(isFound == 1) printf("Insert Successfully");
                    else printf("Input not possible to the given position");   
            break;
            case 7: 
                    deleteNodeatBeg();
            break;
            case 8: 
                    deleteNodeatEnd();
            break;
            case 9: 
                    printf("Input position to be delete : "); scanf("%d",&n);
                    isFound = deleteNodeatAnyPosition(n);
                    if(isFound == 0) printf("Input not possible to the given position");
                    
            break;
            case 10: 
                    printf("Input number you want to find : "); scanf("%d",&number);
                    isFound = findElement(number);
                    printf("The number %d found at node : %d",number,isFound);
            break;
        }
    }while(ch != 0);

    return 0;
}
