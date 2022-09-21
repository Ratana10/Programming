#include<stdio.h>
#include<stdlib.h>

struct node{
    int info;
    struct node* left;
    struct node* right;
};
struct node* getNode(){
    struct node* p;
    p = (struct node* )malloc(sizeof(struct node));
    return p;
}
struct node* makeNode(int item){
    struct node* p = getNode();
    p->info = item;
    p->left = NULL;
    p->right = NULL;
    return p;
}
void clearTree(struct node* proot){
    if(proot == NULL)
        return ;
    
        clearTree(proot->left);
        clearTree(proot->right);
        printf("\nDeleted : %d",proot->info);
        free(proot);
    
}
struct node* insert(struct node* proot, int item){
    if(proot == NULL)
        proot = makeNode(item);
    else{
        if(proot->info == item)
            printf("p node has in binary search tree");

        else if(proot->info > item)
            proot->left = insert(proot->left, item);

        else if(proot->info < item)
            proot->right = insert(proot->right, item);
    }
    return proot;

}
struct node* inputNNode(struct node* proot, int n){
    if(n == 0)
        return NULL;
    int num;
    for(int i=0; i<n; i++){
        printf("Enter info of node : "); scanf("%d",&num);
        proot = insert(proot, num);
    }

    return proot;
}

void preOrder(struct node* proot){
    if(proot != NULL){
        printf("%d   ",proot->info);
        preOrder(proot->left);
        preOrder(proot->right);
    }
}
void inOrder(struct node* proot){
    if(proot != NULL){
        inOrder(proot->left);
        printf("%d   ",proot->info);
        inOrder(proot->right);
    }
}
void postOrder(struct node* proot){
    if(proot != NULL){
        postOrder(proot->left);
        postOrder(proot->right);
        printf("%d   ",proot->info);
    }
}
void printBinaryTree(struct node* proot, int level ){
    if(proot != NULL){
        printBinaryTree(proot->right, level+1);
        printf("\n");
        for(int i=0; i<level; i++)
            printf("\t");
        printf("%d",proot->info);
        printBinaryTree(proot->left, level+1);
    }
}
struct node* findMinNode(struct node* proot){
    while(proot->left != NULL)
        proot = proot->left;
    
    return proot;
}
struct node* findMaxNode(struct node* proot){
    while(proot->right != NULL)
        proot = proot->right;
    
    return proot;
}
struct node* searchNode(struct node* proot, int item){
    struct node* p = NULL;
    if(proot != NULL){
        if(proot->info > item)
            p = searchNode(proot->left, item);
        else if(proot->info < item)
            p = searchNode(proot->right, item);
        else
            return proot;
        
    }
    return p;
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
struct node* deleteNode(struct node *proot, int item)
{
    //searching for the item to be deleted
    if(proot==NULL)
        return NULL;
    if(item < proot->info)
        proot->left = deleteNode(proot->left, item);
    else if (item >  proot->info)
        proot->right = deleteNode(proot->right, item);
    

    else   //found that item
    {
      
        //No Children
        if(proot->left==NULL && proot->right==NULL)
        {
            printf("deleted %d", proot->info);
            free(proot);
            return NULL;
        }

        //One Child
        else if(proot->left==NULL || proot->right==NULL)
        {
            struct node *temp;
            if(proot->left ==NULL)
                temp = proot->right;
            else
                temp = proot->left;

            printf("deleted %d", proot->info);
            free(proot);
            return temp;
        }

        //Two Children
        else
        {
            char ch;
            int num;
            struct node *temp;
            printf("Do you want to delete \n right(r) ,left(l) : "); fflush(stdin); scanf("%c",&ch);
            if(ch == 'r'){
                temp = findMinNode(proot->right);
                swap(&proot->info, &temp->info);
                // num = proot->info;
                // proot->info = temp->info;
                // temp->info = num;
                proot->right = deleteNode(proot->right, temp->info);
            }
            else{
                temp = findMaxNode(proot->left);
                swap(&proot->info, &temp->info);
                // num = proot->info;
                // proot->info = temp->info;
                // temp->info = num;
                proot->left= deleteNode(proot->left, temp->info);
            }
            
            
        }
    }
    
    return proot;
}

void showMenu(){
    printf("\n\n");
    printf("\n [1]. Input n node");
    printf("\n [2]. Insert node");
    printf("\n [3]. Print ");
    printf("\n [4]. Print In Binary Tree");
    printf("\n [5]. Search");
    printf("\n [6]. Delete");
    printf("\n [7]. Clear Tree");
    printf("\n [0]. Exit");
    printf("\n Enter option : ");
}
int main(){
    struct node* root = NULL;

    int ch,ch1,n;
    do{
        showMenu();
        scanf("%d",&ch);
        switch (ch)
        {
        case 1 :
            printf("Enter n node :"); scanf("%d",&n);
            root = inputNNode(root, n);
            break;
        case 2 :
            printf("");
            int arrNum[20] ={ 50,30,70,45,60,85,35,48,55,65,
                              75,90,33,40,47,52,58,63,73,80 };
            int arr1[15]= {
                14,15,4,9,7,18,3,5,16,4,20,17,9,14,5
            };

            for(int i=0; i<15; i++){
                root = insert(root, arr1[i]);
                printf("\n Inserted %d",arrNum[i]);
            }
            printf("\n Insert Completed");
            break;
        case 3 :
            if(root == NULL)
                printf("binary tree is empty ");
            else{
                printf("\n [1]. PreOrder");
                printf("\n [2]. InOrder");
                printf("\n [3]. PostOrder");
                printf("\n Enter option: "); scanf("%d",&ch1);
                
                if( ch1 == 1){
                    printf("PreOrder  : ");
                    preOrder(root);
                }else if( ch1 == 2){
                    printf("InOrder   : ");
                    inOrder(root);
                }else if( ch1 == 3){
                    printf("PostOrder : ");
                    postOrder(root);
                }
            }
            break;
        case 4 :
            if(root == NULL)
                printf("binary tree is empty ");
            else{
                printf("\t\t\tBinary Search Tree\n\n\n");
                printBinaryTree(root,1);
            }
            break;
        case 5 :
            printf("Enter number to search : "); scanf("%d",&n);
            struct node* temp = searchNode(root, n);
            if(temp == NULL)
                printf("search not found !!");
            else
                printf("found [%d] in binary tree", temp->info);
            break;
        case 6 :
            printf("Enter number to delete : "); scanf("%d",&n);
            root = deleteNode(root, n);
            break;
        case 7:
            clearTree(root);
            root = NULL;
            break;
        
        default:
            break;
        }
    }while(ch != 0);
    getch();
    return 0;
}