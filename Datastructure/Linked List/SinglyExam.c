#include<stdlib.h>
#include<stdio.h>

typedef struct node{
    int info;
    struct node* next;
};
struct node* createNode(struct node* proot){
    struct node* p = NULL;
    struct node* tmp=NULL;

    int num;
    do{
        printf("Enter num: "); scanf("%d", &num);
            if(num != -99){
            tmp = (struct node*) malloc(sizeof(struct node));
            tmp->info = num;
            tmp->next = NULL;

            if(proot == NULL){
                proot = p = tmp;
            }
            else{
                p->next = tmp;
                p = p->next;
            }
        }
    }while(num != -99);
    return proot;
}
void display(struct node* proot){
    struct node* p = proot;
    if(proot == NULL)
        printf("node list is empty");
    
    while(p != NULL){
        printf("%5d", p->info);
        p = p->next;
    }
  
}
struct node* deleteFirstNode(struct node* proot){
    proot = proot->next;
    printf("delete first node success");
    return proot;
}
void insertPos(struct node* proot){
    int key;
    struct node* p = proot;
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    printf("Enter num : "); scanf("%d", &newNode->info);
    printf("Enter key: "); scanf("%d", &key);

    while(key >1){
        p = p->next;
        key--;
    }
    newNode->next = p->next;
    p->next = newNode;
    
    printf("insert success");
}
void updateAll(struct node* proot){
    struct node* p = proot;
    while(p != NULL){
        p->info = p->info * 1.2;
        p = p->next;
    }
}
int main(){
    int ch;
    struct node* proot=NULL;
    do{
        printf("\n 1. Input node");
        printf("\n 2. output node");
        printf("\n enter option: "); scanf("%d",&ch);
        
        switch (ch)
        {
        case 1:
            proot = createNode(proot);
            break;
        case 2:
            display(proot);
            break;
        case 3:
            proot = deleteFirstNode(proot);
            break;
        case 4:
            insertPos(proot);
            break;
        case 5:
            updateAll(proot);
            break;
        default:
            break;
        }
    }while(ch != 0);
}