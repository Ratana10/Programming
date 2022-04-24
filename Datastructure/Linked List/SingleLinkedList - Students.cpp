#include<iostream>
#include<cstring>
using namespace std;
struct node{
	int id;
	char name[20];
	float avg;
	struct node *nextptr;
}*stnode;
void input(){
	int n;
	
	cout<<"Ente n number : "; cin>>n;
	stnode = new node;
	node *temp = NULL;
	if(stnode == NULL){
		cout<<"Memory cannot allocated";
	}
	else{
		int id;
		char name[20];
		float avg;
		cout<<"Enter id: "; cin>>id;
		cout<<"Enter name : "; cin.seekg(0,ios::end); cin.clear(); cin.get(name,20);
		cout<<"Enter average score :"; cin>>avg;
		
		stnode->id = id;
		strcpy(stnode->name,name);
		stnode->avg = avg;
		stnode->nextptr = NULL;
		temp = stnode;
		
		for(int i=1; i<n; i++){
			
			
			cout<<"Enter id: "; cin>>id;
			cout<<"Enter name : "; cin.seekg(0,ios::end); cin.clear(); cin.get(name,20);
			cout<<"Enter average score :"; cin>>avg;
			node *fnnode = new node;
			if(fnnode == NULL){
				cout<<"Meomry cannot allocated";
			}
			fnnode->id = id;
			strcpy(fnnode->name,name);
			fnnode->avg = avg;
			fnnode->nextptr = NULL;
			
			temp->nextptr = fnnode;
			temp = temp->nextptr;
		}
	}
}
void output(){
	node *temp= new node;
	if(stnode == NULL){
		cout<<"No data";
	}
	else{
		temp = stnode;
		while(temp != NULL){
			cout<<"ID : "<<temp->id<<endl;
			cout<<"Name : "<<temp->name<<endl;
			cout<<"Average : "<<temp->avg<<endl;
			temp = temp->nextptr;
		}
	}
}
int main(){
    cout<<"Hello ";
    input();
    output();
}