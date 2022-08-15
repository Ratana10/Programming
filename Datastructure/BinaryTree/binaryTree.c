#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include"binarysearchtree.h"

/*
typedef struct Tree Tree;
struct Tree{
    int info;
    Tree* left;
    Tree* right;
};
*/
void clearTree(Tree* t){
    if(t == NULL)
        return ;
    
        clearTree(t->left);
        clearTree(t->right);
        printf("\nDeleted : %d",t->info);
        free(t);
    
}
Tree* insertNode(Tree* t, int item){
    if(t == NULL){
        t = (Tree*)malloc(sizeof(Tree));
        t->info = item;
        t->left = NULL;
        t->right = NULL;
    }
        
    else{
        if(t->info == item)
            printf("item already have in binary search tree");
        else if(item < t->info )
            t->left = insertNode(t->left, item);
        else {
            t->right = insertNode(t->right, item);
        }
    }
    return t;
}
Tree* insertNNode(Tree* t, int n){
    int num;
    for(int i=0; i<n; i++){
        printf("Enter number: "); scanf("%d",&num);
        t = insertNode(t, num);
    }
    return t;
}

Tree* findMinNode(Tree* t){
    while(t->left != NULL)
        t = t->left;
    return t;
}
Tree* findMaxNode(Tree* t){
    while(t->right != NULL)
        t = t->right;
    return t;
}
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
Tree* searchNode(Tree* t, int item){
    if(t == NULL)
        return NULL;
    
    if(item == t->info)
        return t;
    else if(item < t->info)
        t->left = searchNode(t->left, item);
    else
        t->right = searchNode(t->right, item);
    
    return t;
}

Tree* deleteNode(Tree* t, int item){
    if(t == NULL)
        return NULL;
    if(item < t->info)
        t->left = deleteNode(t->left, item);
    else if(item > t->info)
        t->right = deleteNode(t->right, item);
    else{  // search found 
            
        Tree* temp;
        // zero degree
        if(t->left == NULL && t->right == NULL){
            printf("deleted %d", t->info);
            free(t);
            return NULL;
        }
        // one degree
        else if(t->left== NULL || t->right == NULL){
            if(t->left == NULL)
                temp = t->right;
            else    
                temp = t->left;

            printf("deleted %d", t->info);
            free(t);
            return temp;
        }
        // two degreee
        else{
            char ch;
            printf("left(l) or Right(r): "); fflush(stdin); scanf("%c",&ch);
            if(ch == 'l'){
                temp = findMaxNode(t->left);
                swap(&t->info, &temp->info);
               // t->left = deleteNode(t->left, temp->info);
            }
            else{
                temp = findMinNode(t->right);
                swap(&t->info, &temp->info);
                //t->right = deleteNode(t->right, temp->info);
            }
        }
    }

    return t;

}

void showMenu(){
    printf("\n\n");
    printf("\n ** Binary Search Tree Operation **\n");
    printf("\n   [1]. Input n node");
    printf("\n   [2]. Insert exist node");
    printf("\n   [3]. Print In Binary Tree");
    printf("\n   [4]. Delete");
    printf("\n   [5]. Search");
    printf("\n   [6]. Clear Tree");
    printf("\n   [0]. Exit");
    printf("\n   Enter option : ");
}


int main(){
    Tree* root=NULL;
    Tree* temp=NULL;
    int ch,n;
    int num;
    do{
        showMenu();
        scanf("%d",&ch);
        switch (ch)
        {
        case 1:
            printf("Etner n : "); scanf("%d",&n);
            root = insertNNode(root, n);
            printf("\n Insert [%d] node completed",n);
            break;
        case 2:
            n=20;
            int nums[20]= { 50,30,70,45,60,85,35,48,55,65, 75,90,33,40,47,52,58,63,73,80 };
            for(int i=0; i<n; i++){
                root = insertNode(root, nums[i]);
                printf("\n Inserted [%d] ", nums[i]);
            }    
            printf("\n Insert completed");
            
            break;
        case 3:
            printf("\n  =======> Binary Search Tree <=======\n\n\n");
            print_ascii_tree(root);
            break;
        case 4:
            printf("Enter number to delete : "); 
            scanf("%d",&num);
            root = deleteNode(root, num);
            break;
        case 5:
            printf("Enter number to search "); scanf("%d", &num);
            temp = searchNode(root, num);
            if(temp == NULL){
                printf("Search not found in bianry Tree");
            }else{
                printf("Search found %d",temp->info);
            }
            break;
        case 6:
                clearTree(root);
                root = NULL;
                system("cls");
            break;
        case 0:
            system("cls");
            printf("\n\n\n\n\t\t\t\t\t\tThank you !!\n\n\n\n\n\n\n\n");
            exit(0);
            break;
        default:
            break;
        }
    }while(ch != 0);

    return 0;
}