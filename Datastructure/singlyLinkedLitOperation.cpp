#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define newNode (Node *)malloc(sizeof(Node))


typedef struct node{
    int item;
    struct node *next;
}Node;

Node* create(Node* s);
void display(Node* s);
Node* insert(Node* s);
int count(Node* s);
void search(Node* s);
Node* insert(Node* s);
Node* deleteNode(Node* s);

int main(){
	printf("Hello world");
	Node *ptr=NULL, *start = NULL;
	
	int ch, cnt;
	start = create(start);
	display(start);
	
	do{
		printf("\n Single Linked List operation"); 
		printf("\n1-> Count");
		printf("\n2-> Display");
		printf("\n3-> Insert");
		printf("\n4-> Delete");
		printf("\n5-> Search");
		printf("\nNeter w.choice : "); scanf("%d", &ch);
		
		switch(ch){
			case 1:
				printf("\nNo of Nodes = %d", count(start));
				break;
			case 2:
				display(start);
				break;
			case 3:
				start = insert(start);
				break;
			case 4:
				start = deleteNode(start);
				break;
			case 5:
				search(start);
				break;
				
			default:
				printf("\nInvalid Selection\n");
				break;
		}
	}while(ch != 0);
	
	return 0;
}

Node* create(Node* s){
	Node* tmp = NULL;
	Node* t1  = NULL;
	
	int num;
	t1 = s;
	
	do{
		printf("\n Enter the element : "); scanf("%d", &num);
		if(num != -99){
			tmp = newNode;
			tmp->item = num;
			tmp->next = NULL;
			
			if(s == NULL){
				s = t1 = tmp;
			}
			else{
				t1->next = tmp;
				t1 = t1->next;
			}
		}
		else{
			printf("\nLinked List create successfully");
		}
	}while( num != -99);
	
	return s;
} 
void display(Node* s){
	if(s == NULL){
		printf("\nMT Linked List");
	}
	else{
		while( s != NULL){
			printf("%5d", s->item);
			s=s->next;
		}
		printf("\n");
	}
}
int count(Node* s){
	int total=0;
	
	while(s != NULL){
		total++;
		s = s->next;
	}
	return total;
}
Node* insert(Node* s){
	Node* t1 = NULL, *tmp=newNode;
	int pos;
	
	printf("Enter the position to be insert : "); scanf("%d", &pos);
	
	if(pos >0 && pos<= count(s)+1){
		printf("\nEnter the element to be inserted : "); scanf("%d", tmp->item);
		
		if(pos == 1){
			tmp->next = s;
			s = tmp;
		}
		else{
			t1 = s;
			while( pos >2){
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
	
	return s;
}

Node* deleteNode(Node* s){
	Node* t1= s;
	Node* tmp=NULL;
	
	int pos;
	
	printf("\nEnter the position to be deleted : "); scanf("%d",&pos);
	if( pos >0 && pos <= count(s)){
		if(pos == 1){
			s= s->next;
			free(t1);
		}
		else{
			while(pos >2){
			t1 = t1->next;
			pos--;
		}
		tmp=t1->next;
		t1->next = tmp->next;
		free(tmp);
		}
		
	}
	
	else{
		printf("\nInvalide Position");
	}
	return s;
}
void search(Node* s){
	int element;
	int flag=0;
	printf("\nEnter the element to be search : "); scanf("%d",&element);
	
	if( s != NULL){
		while(s != NULL){
			if( s->item == element){
				printf("\n %d is present",element);
				flag = 1;
				return ;
			}
		}
		if(flag == 0){
			printf("\nElement Not Found");
		}
	}
	else{
		printf("\nList is MT, Key element can't be searched\n");
	}
}
