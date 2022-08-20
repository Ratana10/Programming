#ifndef ACADEMIC_H
#define ACADEMIC_H

#include "person.h"
class Academic: public Person{
    private:
        int id;
        float eng,ca,dbs,dsa,dataCom,cpp;
        //English, ComputerAchetecture, databasesystem, datastructAlgorithm, datacomunication, C++ Program

    public:
        Academic();
        Academic(int id,float eng, float ca, float dbs, float dsa, float dataCom, float cpp);
        ~Academic(){}

        void setID(int id);
        void setEnglish(float eng); 
        void setComputerAchitecture(float ca);
        void setDatabase(float dbs);
        void setDatastructureAlgorithm(float dsa);
        void setDataCom(float dataCom);
        void setCpp(float cpp);
        

        int getID();
        float getEng();
        float getCa();
        float getDbs();
        float getDsa();
        float getDataCom();
        float getCpp();

        float getTotal();
        float getAverage();
        char getGrade();

        void input();
        void print();
        void println(){
            print();
            cout<<endl;
        }
        void printScore();
           
        static void printHeadingDetail();
        static void printHeadingScore();


};
Academic::Academic(){
    this->id = 0;
    this->eng = 0.0;
    this->ca = 0.0;
    this->dbs = 0.0;
    this->dsa = 0.0;
    this->dataCom = 0.0;
    this->cpp = 0.0;
}
Academic::Academic(int id,float eng, float ca, float dbs, float dsa, float dataCom, float cpp){
    this->id = id;
    this->eng = eng;
    this->ca = ca;
    this->dbs = dbs;
    this->dsa = dsa;
    this->dataCom = dataCom;
    this->cpp = cpp;
}

/// Setter

void Academic::setID(int id){
    this->id = id;
}
void Academic::setEnglish(float eng){
    this->eng = eng;
}
void Academic::setComputerAchitecture(float ca){
    this->ca = ca;
}
void Academic::setDatabase(float dbs){
    this->dbs = dbs;
}
void Academic::setDatastructureAlgorithm(float dsa){
    this->dsa = dsa;
}
void Academic::setDataCom(float dataCom){
    this->dataCom = dataCom;
}
void Academic::setCpp(float cpp){
    this->cpp = cpp;
}

/// getter

int Academic::getID(){
    return id;
}
float Academic::getEng(){
    return eng;
}
float Academic::getCa(){
    return ca;
}
float Academic::getDbs(){
    return dbs;
}
float Academic::getDsa(){
    return dsa;
}
float Academic::getDataCom(){
    return dataCom;
}
float Academic::getCpp(){
    return cpp;
}

float Academic:: getTotal(){
    return eng+ca+dbs+dsa+dataCom+cpp;
}
float Academic::getAverage(){
    return getTotal()/6;
}
char Academic::getGrade(){
    float avg = getAverage();
    if(avg >= 90)
        return 'A';
    else if(avg >=80)
        return 'B';
    else if(avg >= 70)
        return 'C';
    else if(avg >= 60)
        return 'D';
    else if(avg >= 50)
        return 'E';
    else
        return 'F';
    
}
 
void Academic::input(){
    cout<<"\n\n\n";
    cout<<endl<<tab<<"English                : "; cin>>eng;
    cout<<endl<<tab<<"ComputerAchitecture    : "; cin>>ca;
    cout<<endl<<tab<<"DatabaseSystem         : "; cin>>dbs;
    cout<<endl<<tab<<"DataStructureAlgorithm : "; cin>>dsa;
    cout<<endl<<tab<<"Datacommunication      : "; cin>>dataCom;
    cout<<endl<<tab<<"Cpp Program            : "; cin>>cpp;
}
void Academic::printHeadingScore(){
    cout<<"\t\t\t"<<left<<setw(10)<<"English"<<setw(10)<<"Computer"<<setw(10)<<"Database"<<setw(10)<<"DataStructure"<<setw(10)<<"Datacom"<<setw(10)<<"CPP"<<endl;
    cout<<"\t\t\t";
    for(int i=0; i<49+7; i++){
        cout<<"-";
    }
    cout<<endl;
}
void Academic::printHeadingDetail(){
    cout<<"\t\t\t\t\t"<<left<<setw(10)<<"ID"<<setw(10)<<"Total"<<setw(10)<<"Average"<<setw(10)<<"Grade"<<endl;
    cout<<"\t\t\t\t\t";
    for(int i=0; i<35; i++){
        cout<<"-";
    }
    cout<<endl;    

}
void Academic::print(){
    cout<<"\t\t\t\t\t"<<left<<setw(10)<<id;
    cout<<setprecision(3);
    cout<<setw(10)<<getTotal()<<setw(10)<<getAverage()<<setw(10)<<getGrade();
}
void Academic::printScore(){
    cout<<"\t\t\t"<<left<<setw(5)<<id<<setw(5)<<eng<<setw(5)<<ca<<setw(5)<<dbs<<setw(5)<<dsa<<setw(5)<<dataCom<<setw(5)<<cpp;
}
#endif