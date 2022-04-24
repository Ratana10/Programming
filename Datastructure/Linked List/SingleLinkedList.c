#include <stdio.h>
#include<stdlib.h>
#include<conio.h>

struct node{
    int num;
    struct node *nextptr;
}*stnode;

void createNodelist(int n){
    int num;
    struct node *tmp, *fnnode;
    stnode = (struct node *)malloc(sizeof(struct node));
    if(stnode == NULL){
        printf("Memory cannot allocated");
        return ;
    }
    else{
        printf("Input number for node [1] : "); scanf("%d",&num);
        stnode->num = num;
        stnode->nextptr = NULL;
        tmp = stnode;
        
        for(int i=2; i<=n; i++){
            fnnode = (struct node *)malloc(sizeof(struct node));
            if(fnnode == NULL){
                printf("Memory cannot allocated");
                break;
            }
            else{
                printf("Input number for node [%d] : ",i); scanf("%d",&num);
                fnnode->num = num;
                fnnode->nextptr = NULL;
                tmp->nextptr = fnnode;
                tmp = tmp->nextptr;
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
    struct node *prevnode, *curnode;
    if(stnode == NULL){
        printf("Node list is empty");
        return ;
    }
    else{
        prevnode  = stnode;
        
        curnode = stnode->nextptr;
        stnode = stnode->nextptr;
        prevnode->nextptr = NULL;
        
        while(stnode != NULL){
            stnode = stnode->nextptr;
            curnode->nextptr = prevnode;
            prevnode = curnode;
            curnode = stnode;
        }
        stnode = prevnode;
    }
    
}
void insertNodetoBeg(int num){
    
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->num = num;
    newnode->nextptr = stnode;
    stnode = newnode;
}
void insertNodetoEnd(int num){
    struct node *newnode,*tmp;
    
    newnode = (struct node *)malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("Memory cannot allocated");
        return ;
    }
    newnode->num = num;
    newnode->nextptr = NULL;
    tmp = stnode;
    while(tmp->nextptr != NULL){
        tmp = tmp->nextptr;
    }
    tmp->nextptr = newnode;
}
int insertNodetoAnyPosition(int num, int n){
    struct node *newnode,*tmp;
    
    newnode = (struct node *)malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("Memory cannot allocated");
        return 0;
    }
    newnode->num = num;
    newnode->nextptr = NULL;
    tmp = stnode;
    
    int isFound = 0;
    if(n == 1){
        insertNodetoBeg(num);
        isFound=1;
    }
    else{
        
        for(int i=2; i<n; i++){
            isFound = 1;
            tmp = tmp->nextptr;
            
            if(tmp == NULL){
                isFound = 0;
                break;
            }
        }
        if(isFound == 1){
            newnode->nextptr = tmp->nextptr;
            tmp->nextptr = newnode;
        }
    }
    return isFound;
}
void deleteNodeatBeg(){
    struct node *tmp;
    if(stnode == NULL){
        printf("Node List is empty");
        return ;
    }
    tmp = stnode;
    stnode = stnode->nextptr;
    printf("The number : %d  at the first node deleted successfully",tmp->num);
    free(tmp);
}
void deleteNodeatEnd(){
    struct node *tmp,*prevnode;
    if(stnode == NULL){
        printf("Node List is empty");
        return ;
    }
    tmp = stnode;
    prevnode = stnode;
    
    while(tmp->nextptr != NULL){
        prevnode = tmp;
        tmp = tmp->nextptr;
    }
    prevnode->nextptr = NULL;
    printf("The number : %d  at the first node deleted successfully",tmp->num);
    free(tmp);
    
}
int deleteNodeatAnyPosition(int n){
    struct node *tmp,*prevnode;
    int isFound=0;
    if(stnode == NULL){
        printf("Node List is empty");
        return 0;
    }
    tmp = stnode;
    prevnode = stnode;
    if(n == 1){
        isFound = 1;
        deleteNodeatBeg();
       
    }
    
    for(int i=1; i<n; i++){
        isFound = 1;
        prevnode = tmp;
        tmp = tmp->nextptr;
        if(tmp == NULL){
            isFound = 0;
            break;
        }
           
    }
    if(isFound == 1 && n!= 1){
        prevnode->nextptr = tmp->nextptr;
        printf("The number : %d  at the %d node deleted successfully",tmp->num,n);
        free(tmp);
    }
    return isFound;
   
}
int findElement(int num){
    struct node *tmp;
    int count=1;
    if(stnode == NULL){
        printf("Node List is empty");
        return 0;
    }
    else{
        tmp = stnode;
        while(tmp->nextptr != NULL){
            if(tmp->num == num){
                break;
            }
            else{
                count++;
                tmp = tmp->nextptr;
            }
        }
    }
    return count;
}
void sortNodeListAscending(){
    struct node *tmp,*curnode;
    int x;
    if(stnode == NULL){
        printf("Node List empty");
        return ;
    }
    tmp = stnode;
    curnode = NULL;
 
    while(tmp != NULL){

        curnode = tmp->nextptr;
        
        while(curnode != NULL){
            if(curnode->num < tmp->num  ){
                x = tmp->num;
                tmp->num = curnode->num;
                curnode->num = x;
            }
            
            curnode = curnode->nextptr;
        }
        tmp = tmp->nextptr;
    }
    
}
void sortNodeListDescending(){
    struct node *tmp,*curnode;
    int x;
    if(stnode == NULL){
         printf("Node List empty");
        return ;
    }
    tmp = stnode;
    curnode = NULL;
    while(tmp != NULL){
        curnode = tmp->nextptr;
        while(curnode != NULL){
            if(curnode->num > tmp->num){
                 x = tmp->num;
                tmp->num = curnode->num;
                curnode->num = x;
            }
            
            curnode = curnode->nextptr;
        }
        
        tmp= tmp->nextptr;
    }
}
int main()
{
    int ch,isFound=0;
    int number,pos,n;
    do{
        printf("\n\nSingle Linked List Exercise \n");
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
        printf("11.Sort Node List Ascending order\n");
        printf("12.Sort Node List Ascending order\n");
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
                    printf("Input position to be delete : "); scanf("%d",&pos);
                    isFound = deleteNodeatAnyPosition(pos);
                    if(isFound == 0) printf("Input not possible to the given position");
            break;
            case 10: 
                    printf("Input number you want to find : "); scanf("%d",&number);
                    isFound = findElement(number);
                    printf("The number %d found at node : %d",number,isFound);
            break;
            case 11:
                    printf("Sorting The Node list as Acending Order\n");
                    sortNodeListAscending();
                    displayNodeList();
            break;
            case 12:
                    printf("Sorting The Node list as Descending Order\n");
                    sortNodeListDescending();
                    displayNodeList();
            break;
        }
    }while(ch != 0);

    return 0;
}
