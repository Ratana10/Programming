#include<stdio.h>
#include<stdlib.h>

struct node{
    int num;
    struct node *nextptr;
}*stnode;

void createNodelist(int n){
    int num;
    struct node *tmp,*newnode;
    
    stnode = (struct node *)malloc(sizeof(struct node));
    if(stnode == NULL){
        printf("Memory can not allocated");
        return ;
    }
    
    printf("Input number for node [1] : "); scanf("%d",&num);
    stnode->num = num;
    stnode->nextptr =NULL;
    tmp = stnode;
    
    for(int i=2; i<=n; i++){
        newnode = (struct node *)malloc(sizeof(struct node));
        if(newnode == NULL){
            printf("Memory can not allocated");
            break ;
        }
        
        printf("Input number for node [%d] : ",i); scanf("%d",&num);
        newnode->num = num;
        newnode->nextptr =NULL;
        tmp->nextptr = newnode;
        tmp = newnode;
    }
    tmp->nextptr = stnode;      //Make last node point to the first node
    
}
void displayNodeList(){
    struct node *tmp;
    if(stnode != NULL){
        tmp = stnode;
        int i=1;
        
        do{
            printf("node [%d] : %d\n",i++,tmp->num);
            tmp = tmp->nextptr;
        }while(tmp != stnode);
    }
    else{
        printf("Node List is Empty");
    }
}
void  insertNodetoBeg(int num){

    struct node *tmp,*newnode;

    newnode = (struct node *)malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("Memory can not allocated");
        return ;
    }
    
    newnode->num = num;
    newnode->nextptr = stnode;
    tmp = stnode;

    while(tmp->nextptr != stnode){
        tmp = tmp->nextptr;
        
    }
    tmp->nextptr = newnode;
    stnode = newnode;
    
}
void insertNodetoEnd(int num){
    struct node *tmp,*newnode;
    
    newnode = (struct node *)malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("Memory can not allocated");
        return ;
    }
    
    newnode->num = num;
    newnode->nextptr = stnode;
    tmp = stnode;
    
    while(tmp->nextptr != stnode){
        tmp = tmp->nextptr;
    }
    tmp->nextptr = newnode;
    
}
int insertNodetoAnyPosition(int num, int pos){
    struct node *tmp,*newnode,*prevnode;
    int isFound = 0;
    newnode = (struct node *)malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("Memory can not allocated");
        return 0;
    }
    newnode->num = num;
    tmp = stnode;
    if(pos == 1){
        insertNodetoBeg(num);
        isFound = 1;
    }
    else{
        for(int i=1; i<pos; i++){
        prevnode = tmp;
         tmp = tmp->nextptr;
        isFound = 1;
        
        //Cannot start the circle linked list again
            if(tmp == stnode){
                 isFound = 0;
                break;
            }
         }
        
    }

    if(isFound == 1 && pos != 1){
        prevnode->nextptr = newnode;
        newnode->nextptr = tmp;
    }
    
    return isFound;
}
void deleteNodeatBeg(){
    struct node *tmp;
    if(stnode == NULL){
        printf("Node List is Empty");
        return ;
    }
    tmp = stnode;
    
    while(tmp->nextptr != stnode){
        tmp = tmp->nextptr ;
    }
    tmp->nextptr = stnode->nextptr;
    //Assing again
    tmp = stnode;
    stnode = stnode->nextptr;
    printf("The number : %d  at the first node deleted successfully",tmp->num);
    free(tmp);
}
void deleteNodeatEnd(){
    struct node *tmp,*prevnode;
    tmp = stnode;
    if(stnode == NULL){
        printf("Node List is Empty");
        return ;
    }
    while(tmp->nextptr != stnode){
        prevnode = tmp;
        tmp = tmp->nextptr;
    }
    prevnode->nextptr = stnode;
    printf("The number : %d  at the first node deleted successfully",tmp->num);
    free(tmp);
    
}
int deleteNodeatAnyPosition(int pos){
    struct node *tmp,*prevnode;
    int isFound = 0;
    if(stnode == NULL){
        printf("Node List is Empty");
        return 0;
    }
    
    tmp = stnode;
    if(pos == 1){
        deleteNodeatBeg();
        isFound = 1;
    }
    else{
        
        for(int i=1; i<pos; i++){
            isFound = 1;
            prevnode = tmp;
            tmp = tmp->nextptr;
            
            if(tmp == stnode){
                isFound = 0;
                break;
            }
        }
        
    }
    
    
    if(isFound == 1 && pos!=1){
        prevnode->nextptr = tmp->nextptr;
        printf("The number : %d  at the %d node deleted successfully",tmp->num,pos);
        free(tmp);
    }
    
    return isFound;
}

int main()
{
    int ch,isFound=0;
    int number,pos,n;
    do{
        printf("\n\nCircle Linked List Exercise \n");
        printf("1.Input Node List\n");
        printf("2.Display Node List\n");
        printf("3.Reverse Node List\n");
        printf("4.Insert Node to beginning\n");
        printf("5.Insert Node to end\n");
        printf("6.Insert Node to anyposition\n");
        printf("7.Delete Node at beginning\n");
        printf("8.Delete Node at end\n");
        printf("9.Delete Node at anyposition\n");
        
        printf("0.Exit\n");
        printf("----------------------\n");
        printf("Enter option : "); scanf("%d",&ch);
        switch(ch){
             case 1: 
                    printf("Input number of node : "); scanf("%d",&n);
                    createNodelist(n);
            break;
            case 2: 
                    printf("The number you entered in the node are \n\n");
                    displayNodeList();
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
                    isFound = insertNodetoAnyPosition(number,n);
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
            
        }
    }while(ch != 0);
    

    return 0;
}
