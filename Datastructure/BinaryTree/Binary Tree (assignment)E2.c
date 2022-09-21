#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

typedef struct Tree Tree;
struct Tree{
    int info;
    Tree* left;
    Tree* right;
};

//=============================================================
//printing tree in ascii
typedef struct asciinode_struct asciinode;

struct asciinode_struct {
    asciinode *left, *right;

    //length of the edge from this node to its children
    int edge_length;

    int height;

    int lablen;

    //-1=I am left, 0=I am root, 1=right
    int parent_dir;

    //max supported unit32 in dec, 10 digits max
    char label[11];
};



#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

//adjust gap between left and right nodes
int gap = 3;

//used for printing next node in the same level,
//this is the x coordinate of the next char printed
int print_next;

int MIN(int X, int Y) {
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX(int X, int Y) {
    return ((X) > (Y)) ? (X) : (Y);
}

asciinode *build_ascii_tree_recursive(Tree *t) {
    asciinode *node;

    if (t == NULL) return NULL;

    node = (asciinode*)malloc(sizeof(asciinode));
    node->left = build_ascii_tree_recursive(t->left);
    node->right = build_ascii_tree_recursive(t->right);

    if (node->left != NULL) {
        node->left->parent_dir = -1;
    }

    if (node->right != NULL) {
        node->right->parent_dir = 1;
    }

    sprintf(node->label, "%d", t->info);
    node->lablen = (int) strlen(node->label);

    return node;
}


//Copy the tree into the ascii node structre
asciinode *build_ascii_tree(Tree *t) {
    asciinode *node;
    if (t == NULL) return NULL;
    node = build_ascii_tree_recursive(t);
    node->parent_dir = 0;
    return node;
}


//Free all the nodes of the given tree
void free_ascii_tree(asciinode *node) {
    if (node == NULL) return;
    free_ascii_tree(node->left);
    free_ascii_tree(node->right);
    free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode *node, int x, int y) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
    if (node->left != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(asciinode *node, int x, int y) {
    int i, notleft;
    if (node == NULL) return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
    if (node->right != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(asciinode *node) {
    int h, hmin, i, delta;
    if (node == NULL) return;
    compute_edge_lengths(node->left);
    compute_edge_lengths(node->right);

    /* first fill in the edge_length of node */
    if (node->right == NULL && node->left == NULL) {
        node->edge_length = 0;
    } else {
        if (node->left != NULL) {
            for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->left, 0, 0);
            hmin = node->left->height;
        } else {
            hmin = 0;
        }
        if (node->right != NULL) {
            for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->right, 0, 0);
            hmin = MIN(node->right->height, hmin);
        } else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        //If the node has two children of height 1, then we allow the
        //two leaves to be within 1, instead of 2
        if (((node->left != NULL && node->left->height == 1) ||
             (node->right != NULL && node->right->height == 1)) && delta > 4) {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    //now fill in the height of node
    h = 1;
    if (node->left != NULL) {
        h = MAX(node->left->height + node->edge_length + 1, h);
    }
    if (node->right != NULL) {
        h = MAX(node->right->height + node->edge_length + 1, h);
    }
    node->height = h;
}
//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode *node, int x, int level) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->lablen;
    } else if (node->edge_length >= level) {
        if (node->left != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->right != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    } else {
//    	printf("\n");
        print_level(node->left,
                    x - node->edge_length - 1,
                    level - node->edge_length - 1);
        print_level(node->right,
                    x + node->edge_length + 1,
                    level - node->edge_length - 1);
    }
}

//prints ascii tree for given Tree structure
void print_ascii_tree(Tree *t) {
	printf("%88s"," ");
    asciinode *proot;
    int xmin, i;
    if (t == NULL) return;
    proot = build_ascii_tree(t);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
        printf("%88s"," ");
    }
    if (proot->height >= MAX_HEIGHT) {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
}

//======================================================================


Tree* insertNode(Tree* t, int item){
    Tree* newNode;
    
    if(t == NULL){
        t = (Tree*)malloc(sizeof(Tree));
        t->info = item;
        t->left = NULL;
        t->right = NULL;
    }
        
    else{
        if(t->info == item)
            printf("item have in binary search tree");
        else if(item < t->info )
            t->left = insertNode(t->left, item);
        else {
            t->right = insertNode(t->right, item);
        }
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
Tree* deleteNode(Tree* t, int item){
    if(t == NULL)
        return NULL;
    if(item < t->info)
        t->left = deleteNode(t->left, item);
    else if(item > t->info)
        t->right = deleteNode(t->right, item);
    else{
            // search found 
        Tree* temp;
        if(t->left == NULL && t->right == NULL){
            printf("deleted %d", t->info);
            free(t);
            return NULL;
        }
        else if(t->left== NULL){
            temp = t->right;
            printf("deleted %d", t->info);
            free(t);
            return temp;
        }
        else if(t->right == NULL){
            temp=t->left;
            printf("deleted %d", t->info);
            free(t);
            return temp;
        }
        else{
            char ch;
            printf("left(l) or Right(r): "); fflush(stdin); scanf("%c",&ch);
            if(ch == 'l'){
                temp = findMaxNode(t->left);
                swap(&t->info, &temp->info);
                t->left = deleteNode(t->left, temp->info);
            }
            else{
                temp = findMinNode(t->right);
                swap(&t->info, &temp->info);
                t->right = deleteNode(t->right, temp->info);
            }
        }
    }

    return t;

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
}
void showMenu(){
    printf("\n\n");
    printf("%40c%c%c%s%c%c%c\n\n",176,176,176,"[1]. Input n node [2]. Insert exist node [3]. Print In Binary Tree[4]. Delete [5]. Search [6]. Clear Tree [0]. Exit",176,176,176);
    printf("\n %94cEnter option : ",16);
}


int main(){
	system("COLOR F0");
	blue();
    Tree* root=NULL;
    Tree* temp=NULL;
    int ch;
    int num;
    do{
    	blue();
        showMenu();
        scanf("%d",&ch);
        switch (ch)
        {
        case 1:
            /* code */
            break;
        case 2:
        	system("cls");
            printf("\n\n");
            int nums[20]= { 50,30,70,45,60,85,35,48,55,65, 75,90,33,40,47,52,58,63,73,80 };
            for(int i=0; i<20; i++){
                root = insertNode(root, nums[i]);
                printf("\n%100s  [%d] ","Inserted",nums[i]);
            }    
            red();
            printf("\n %90cInsert completed%c",19,19);
            
            break;
        case 3:
        	printf("\n%85s"," ");
        	black_yellow();
            printf("%s  \n\n\n","=======> Binary Search Tree <=======");
            red();
            print_ascii_tree(root);
            break;
        case 4:
        	printf("\n%95s"," ");
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
        default:
            break;
        }
    }while(ch != 0);

    
}
void blue(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),241);
}
void red(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),244);
}
void green(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),242);
}
void white(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),255);
}
void black_yellow(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
}
void red_white(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),75);
}







































































































































































































































































































































//Rattanak Oudom