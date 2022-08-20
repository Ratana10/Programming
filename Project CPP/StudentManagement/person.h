#ifndef PERSON_H
#define PERSON_H
#define tab "\t\t\t\t\t"

#include<iostream>
#include<cstring>
#include<iomanip>

using namespace std;

class Person{
    protected:
        int id;
        char name[20];
        char gender;
        int age;
        int day,month,year;

    public:
        Person();
        Person(int id, char* name, char gender, int age, int day, int month, int year);

        ~Person(){}
        

        int getID();
        char* getName();
        char getGender();
        char getAge();
        

        void setID(int id);
        void setName(char* name);
        void setGender(char gender);
        void setAge(int age);
        void setDate(int day, int month, int year);
        

        void input();
        void print();
        void println(){print(); cout<<endl;}

        static void printHeading();

};
Person::Person(){
    this->id = 0;
    strcpy(this->name,"Unknow");
    this->gender = 'M';
    this->age = 0;
    this->day = 0;
    this->month = 0;
    this->year = 0;
}
Person::Person(int id,char* name, char gender, int age, int day, int month, int year){
    this->id = id;
    strcpy(this->name,name);
    this->gender = gender;
    this->age = age;
    this->day = day;
    this->month = month;
    this->year = year;
}
int Person::getID(){
    return id;
}
char* Person::getName(){
    return name;
}
char Person::getGender(){
    return gender;
}
char Person::getAge(){
    return age;
}
void Person::setID(int id){
    this->id = id;
}
void Person::setName(char* name){
    strcpy(this->name, name);
}
void Person::setGender(char gender){
    this->gender = gender;
}
void Person::setAge(int age){
    this->age = age;
}
void Person::setDate(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}
void Person::input(){
    cout<<"\n\n\n";
    cout<<endl<<tab<<"Enter ID    : "; cin>>id;
    cout<<endl<<tab<<"Enter Name  : "; cin.seekg(0,ios::end); cin.clear(); cin.get(name,20);
    cout<<endl<<tab<<"Gender      : "; cin>>gender;
    cout<<endl<<tab<<"Age         : "; cin>>age;
    cout<<endl<<tab<<"DateOfBirth\n"; 
    cout<<endl<<tab<<"Day   : "; cin>>day;
    cout<<endl<<tab<<"Month : "; cin>>month;
    cout<<endl<<tab<<"Year  : "; cin>>year;
}
void Person::print(){
   cout<<"\t\t\t"<<left<<setw(7)<<id<<setw(18)<<name<<setw(12)<<gender<<setw(8)<<age<<setw(8);
   
   cout.setf(ios::right);
   cout.fill('0');
   cout.width(2); cout<<day<<'/';
   cout.width(2); cout<<month<<'/';
   cout.width(4); cout<<year;
   cout.fill(' ');
}
void Person::printHeading(){

    cout<<"\t\t\t"<<left<<setw(7)<<"ID"<<setw(18)<<"NAME"<<setw(12)<<"GENDER"<<setw(8)<<"AGE"<<setw(8)<<"DATEOFBIRTH"<<endl;
    cout<<"\t\t\t";
    for(int i=0; i<49+7; i++){
        cout<<"-";
    }
    cout<<endl;
}
#endif