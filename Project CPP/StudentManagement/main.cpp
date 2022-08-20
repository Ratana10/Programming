#include"person.h"
#include"academic.h"

#include<fstream>
#include<conio.h>

void writeStudentInformation();
void printAllStudentInformation(Person p[], int n);
void readStudentInformation();

void searchStudentInformationOption(Person p[], int n);
void searchStudentInformation();

void updateStudentInformationOption(Person p[], int n);
void updateStudentOption(Person& p);
void updateStudentInformation();

void deleteStudent(Person p[], int n);
void deleteStudentInformation();



void writeStudentScore();
void printAllStudentDetail(Academic s[], int n);
void readStudentScore();

void searchStudentScoreOption(Academic s[], int n);
void searchStudentScore();

void updateStudentScoreOption(Academic s[], int n);
void updateScoreOption(Academic& s);
void updateStudentScore();

void deleteScore(Academic s[], int n);
void deleteStudentScore();

void studentInformationMenu(){
    cout<<"\n\n\n\n";
    cout<<tab<<"******Student Information******\n\n";
    cout<<tab<<"1. Register new Student\n"<<endl;
    cout<<tab<<"2. View All Student\n"<<endl;
    cout<<tab<<"3. Search Student\n"<<endl;
    cout<<tab<<"4. Modify Student\n"<<endl;
    cout<<tab<<"5. Delete Student\n"<<endl;
    cout<<tab<<"0. Back\n"<<endl;
}
void studentScoreMenu(){
    cout<<"\n\n\n\n";
    cout<<tab<<"******Student Score******\n\n";
    cout<<tab<<"1. Input student Score\n"<<endl;
    cout<<tab<<"2. View student Score\n"<<endl;
    cout<<tab<<"3. Search Student\n"<<endl;
    cout<<tab<<"4. Modify Student\n"<<endl;
    cout<<tab<<"5. Delete Student\n"<<endl;
    cout<<tab<<"0. Back\n"<<endl;
}
int main(){
    char ch,ch1,ch2;
    //rename("tmp.bin", "StudentInformation.bin");
    do{
        system("cls");
        cout<<"\n\n\n\n\n";
        cout<<tab<<"\tStudent Management System \n\n";
        cout<<tab<<"1. Student Information\n\n";
        cout<<tab<<"2. Student Score\n\n";
        cout<<tab<<"0. Exit\n\n";
        cout<<tab<<"Enter option : "; ch = getch();
        switch(ch){
            case '1':
                do{
                    system("cls");
                    studentInformationMenu();
                    cout<<tab<<"Enter option: "; ch1=getch();
                    system("cls");
                    switch(ch1){
                        case '1':
                            writeStudentInformation();
                            break;
                        case '2':
                            readStudentInformation();
                            break;
                        case '3':
                            searchStudentInformation();
                            break;
                        case '4':
                            updateStudentInformation();
                            break;
                        case '5':
                            deleteStudentInformation();
                            break;
                        
                    }
                }while(ch1 != '0');
                break;
            case '2':
                do{
                    system("cls");
                    studentScoreMenu();
                    cout<<tab<<"Enter option: "; ch2=getch();
                    system("cls");
                    switch(ch2){
                        case '1':
                            writeStudentScore();
                            break;
                        case '2':
                            readStudentScore();
                            break;
                        case '3':
                            searchStudentScore();
                            break;
                        case '4':   
                            updateStudentScore();
                            break;
                        case '5':
                            deleteStudentScore();

                            break;
                        
                    }
                }while(ch2 != '0');
                break;
            
        }
    }while(ch != '0');
    return 0;
}

void writeStudentInformation(){
    fstream fout;
    fout.open("StudentInformation.bin", ios::app | ios::binary);
    if(fout.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;
    }

    Person p;
    char op;
    while(1){
        system("cls");
        p.input();
        fout.write((char*)&p, sizeof(Person));

        Again:
        cout<<"\n\n\n\n"<<tab<<"Do you want to continue(y/n) : "; 
        op = getch();
        if(op == 'Y' || op == 'y')
            continue;
        else if(op == 'N' || op == 'n')
            break;
        else
            goto Again;
    }

    fout.close();

}
void readStudentInformation(){
    fstream fin;
    fin.open("StudentInformation.bin", ios::in | ios::binary);
    if(fin.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;
    }
    
    Person* p;
    fin.seekg(0, ios::end);
    int n = fin.tellg()/sizeof(Person);
    fin.seekg(0, ios::beg);

    if(n == 0){
        cout<<"\n\n\n\n"<<tab<<"No Record";
        getch();
        return ;
    }  
    else{
        p = new Person[n];
        fin.read((char*)p, n*sizeof(Person));
        fin.close();
    
    }
    cout<<"\n\n\n\n\n";
    cout<<tab<<"ALL STUDENTS INFORMATION\n\n\n";
    Person::printHeading();
    printAllStudentInformation(p,n);

    getch();
    delete[] p;

}
void printAllStudentInformation(Person p[], int n){
    for(int i=0; i<n; i++){
        p[i].println();
    }
}
void searchStudentInformation(){
    fstream fin;
    fin.open("StudentInformation.bin", ios::in | ios::binary);
    if(fin.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;
    }

    fin.seekg(0, ios::end);
    int n = fin.tellg()/sizeof(Person);
    fin.seekg(0, ios::beg);

    if(n == 0){
        cout<<"\n\n\n\n"<<tab<<"No Record";
        getch();
        return ;
    }

    Person* p = new Person[n];
    fin.read((char*)p, n*sizeof(Person));
    fin.close();

    searchStudentInformationOption(p,n);
    delete[] p;

}
void searchStudentInformationOption(Person p[], int n){
    char op;
    int isFound=0;
    int searchID;

    while(1){
        system("cls");
        isFound =0;
        cout<<"\n\n\n\n"<<tab<<"Enter studentID to search: "; cin>>searchID;

        for(int i=0; i<n; i++){
            if(p[i].getID() == searchID){
                isFound=1;
                cout<<"\n\n\n\n";
                Person::printHeading();
                p[i].println();
                getch();
                break;
            }
        }

        if(isFound==0){
            cout<<"\n\n\n\n"<<tab<<"Search Not found";
            getch();
        }
        Again:
        cout<<"\n\n\n\n"<<tab<<"Do you want to continue(y/n) : "; 
        op = getch();
        if(op == 'Y' || op == 'y')
            continue;
        else if(op == 'N' || op == 'n')
            break;
        else{
            system("cls");
            goto Again;
        }
            
    }
    
        
}

void updateStudentInformation(){
    fstream fin;
    fin.open("StudentInformation.bin", ios::in | ios::binary);
    if(fin.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;
    }
    fin.seekg(0, ios::end);
    int n= fin.tellg()/sizeof(Person);
    fin.seekg(0, ios::beg);

    if(n==0){
        cout<<"\n\n\n\n"<<tab<<"No Record";
        getch();
        return ;       
    }

    Person* p = new Person[n];
    fin.read((char*)p, n*sizeof(Person));
    fin.close();
   
    
    updateStudentInformationOption(p,n);

    delete[] p;
}
void updateStudentInformationOption(Person p[], int n){
    char op;
    int isFound=0;
    int searchID;

    while(1){
        system("cls");
        isFound =0;
        cout<<"\n\n\n\n"<<tab<<"Enter studentID to update : "; cin>>searchID;

        for(int i=0; i<n; i++){
            if(p[i].getID() == searchID){
                isFound=1;
                updateStudentOption(p[i]);     
            }
        }
        if(isFound == 0){
            cout<<"\n\n\n\n"<<tab<<"Student ID not found";
            getch();
        }
        Again:
        cout<<"\n\n\n\n"<<tab<<"Do you want to continue(y/n) : "; 
        op = getch();
        if(op == 'Y' || op == 'y')
            continue;
        else if(op == 'N' || op == 'n')
            break;
        else{
            system("cls");
            goto Again;
        }
    }
    

    if(isFound != 0){
        fstream fout;
        fout.open("tmp.bin", ios::out | ios::binary); 
        if(fout.fail()){
            cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
            getch();
            return ;
        }
        fout.write((char*)p, n*sizeof(Person));
        fout.close();

        remove("StudentInformation.bin");
        rename("tmp.bin","StudentInformation.bin");

    }
    
    getch();
    
}
void updateStudentOption(Person& p){
    char ch;
    do{
        system("cls");
        cout<<"\n\n\n\n";
        cout<<tab<<"   What do you want to update    \n\n";
        cout<<tab<<"1. Student ID\n"<<endl;
        cout<<tab<<"2. Student Name\n"<<endl;
        cout<<tab<<"3. Student Gender\n"<<endl;
        cout<<tab<<"4. Student Age\n"<<endl;
        cout<<tab<<"0. Back\n"<<endl;
        cout<<tab<<"Enter option : "; ch = getch();
        
        system("cls");
        if(ch == '1'){
            int id;
            cout<<endl<<tab<<"Current ID   : "<<p.getID()<<endl;
            cout<<endl<<tab<<"Enter new ID : "; cin>>id;
            p.setID(id);
            cout<<endl<<tab<<"Update ID Successfully";
            getch();
        }
        else if(ch == '2'){
            char name[20];
            cout<<endl<<tab<<"Current Name   : "<<p. getName()<<endl;
            cout<<endl<<tab<<"Enter new Name : "; cin.seekg(0,ios::end); cin.clear(); cin.get(name,20);
            p.setName(name);
            cout<<endl<<tab<<"Update Name Successfully";
            getch();
        }
        else if(ch == '3'){
            char gender;
            cout<<endl<<tab<<"Current Gender   : "<<p.getGender()<<endl;
            cout<<endl<<tab<<"Enter new Gender : "; cin>>gender;
            p.setGender(gender);
            cout<<endl<<tab<<"Update Gender Successfully";
            getch();
        }
        
    }while(ch != '0');
}
void deleteStudentInformation(){
    fstream fin;
    fin.open("StudentInformation.bin", ios::in | ios::binary);
    if(fin.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;
    }

    fin.seekg(0, ios::end);
    int n = fin.tellg()/sizeof(Person);
    fin.seekg(0, ios::beg);

    if(n == 0){
        cout<<"\n\n\n\n"<<tab<<"No Record";
        getch(); 
        return ; 
    }
    
    Person* p = new Person[n];
    fin.read((char*)p, n*sizeof(Person));
    fin.close();

    deleteStudent(p,n);

    delete[] p;
}
void deleteStudent(Person p[], int n){
    fstream fout;
    fout.open("tmp.bin", ios::out | ios::binary);
    if(fout.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;
    }

    int searchID,isFound=0;

    while(1){
        system("cls");
        isFound =0; 
        cout<<endl<<tab<<"Enter StudentID to delete : "; cin>>searchID;

        for(int i=0; i<n; i++){
            if(searchID == p[i].getID()){
                isFound =1;
                continue;
            }
            else{
                fout.write((char*)&p[i], sizeof(Person));        
            }
        }

        if(isFound == 0){
            cout<<"\n\n\n\n"<<tab<<"Student ID not found";
            getch();
        }
        else{
            cout<<endl<<tab<<"Delete  Successfully";
            getch();
        }

        Again:
        cout<<"\n\n\n\n"<<tab<<"Do you want to continue(y/n) : "; 
        char op = getch();
        if(op == 'Y' || op == 'y')
            continue;
        else if(op == 'N' || op == 'n')
            break;
        else{
            system("cls");
            goto Again;
        }

    }

    fout.close(); 
    if(isFound == 1){
        remove("StudentInformation.bin");
        rename("tmp.bin","StudentInformation.bin");
    }


}

void writeStudentScore(){
    fstream  fout;
    fout.open("StudentScore.bin", ios::app | ios::binary);

    fstream fin;
   // fin.open("StudentInformation.bin", ios::in | ios::binary);

    if(fout.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;  
    }


    Person p;
    Academic s;
        
    
      
    while(1){
        fin.open("StudentInformation.bin", ios::in | ios::binary);
        if(fin.fail()){
            cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
            getch();
            return ;  
        }
        system("cls");
        
        int searchID;
        int isFound=0;
        
        cout<<endl<<tab<<"Enter student ID : "; cin>>searchID;
        
        
        while(fin.read((char*)&p, sizeof(Person))){
            
            if(p.getID() == searchID){
                isFound = 1;
                s.setID(searchID);
                //cout<<"Testing : "<<s.getID(); getch();
                s.input(); 
                fout.write((char*)&s,sizeof(Academic));
            }

        }

        if(isFound == 0){
            cout<<"\n\n\n\n"<<tab<<"Student ID not found";
            getch();
        }
        else{
            cout<<endl<<tab<<"Successfully";
            getch();
        }

        fin.close();
        Again:
        cout<<"\n\n\n\n"<<tab<<"Do you want to continue(y/n) : "; 
        char op = getch();
        if(op == 'Y' || op == 'y')
            continue;
        else if(op == 'N' || op == 'n')
            break;
        else{
            system("cls");
            goto Again;
        }

        
    }

    fin.close();
    fout.close();
       
}

void readStudentScore(){
    fstream fin;
    fin.open("StudentScore.bin", ios::in | ios::binary);
    if(fin.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;  
    }

    Academic* s;
    fin.seekg(0, ios::end);
    int n = fin.tellg()/sizeof(Academic);
    fin.seekg(0, ios:: beg);

    if(n == 0){
        cout<<"\n\n\n\n"<<tab<<"No Record";
        getch();
        return ;
    }

    s = new Academic[n];
    fin.read((char*)s, n*sizeof(Academic));
    fin.close();

    cout<<"\n\n\n\n\n";
    cout<<tab<<"ALL STUDENTS INFORMATION\n\n\n";
    Academic::printHeadingDetail();
    printAllStudentDetail(s,n);
    getch();

    delete[] s;

}
void printAllStudentDetail(Academic s[], int n){
    for(int i=0; i<n; i++){
        s[i].println();
    }
}

void searchStudentScore(){
    fstream fin;
    fin.open("StudentScore.bin", ios::in | ios::binary);
    if(fin.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;  
    }

    Academic* s;
    fin.seekg(0, ios::end);
    int n = fin.tellg()/sizeof(Academic);
    fin.seekg(0, ios:: beg);

    if(n == 0){
        cout<<"\n\n\n\n"<<tab<<"No Record";
        getch();
        return ;
    }

    s = new Academic[n];
    fin.read((char*)s, n*sizeof(Academic));
    fin.close();
 
    searchStudentScoreOption(s,n);
    delete[] s;

}
void searchStudentScoreOption(Academic s[], int n){
    char op;
    int isFound=0;
    int searchID;

    while(1){
        system("cls");
        isFound =0;
        cin.seekg(0,ios::end); cin.clear();
        cout<<"\n\n\n\n"<<tab<<"Enter studentID to search: "; cin>>searchID;

        for(int i=0; i<n; i++){
            cout<<"Testing sID = "<<s[i].getID()<<endl;
            cout<<"Testing searchID = "<<searchID<<endl;
            if(s[i].getID() == searchID){
                isFound=1;
                cout<<"\n\n\n\n";
                Academic::printHeadingDetail();
                s[i].println();
                getch();
                break;
            }
        }

        if(isFound==0){
            cout<<"\n\n\n\n"<<tab<<"Search Not found";
            getch();
        }
        Again:
        cout<<"\n\n\n\n"<<tab<<"Do you want to continue(y/n) : "; 
        op = getch();
        if(op == 'Y' || op == 'y')
            continue;
        else if(op == 'N' || op == 'n')
            break;
        else{
            system("cls");
            goto Again;
        }
            
    }
}
void updateStudentScore(){
    fstream fin;
    fin.open("StudentScore.bin", ios::in | ios::binary);
    if(fin.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;
    }
    fin.seekg(0, ios::end);
    int n= fin.tellg()/sizeof(Person);
    fin.seekg(0, ios::beg);

    if(n==0){
        cout<<"\n\n\n\n"<<tab<<"No Record";
        getch();
        return ;       
    }

    Academic* s = new Academic[n];
    fin.read((char*)s, n*sizeof(Academic));
    fin.close();
  
    
    updateStudentScoreOption(s,n);

    delete[] s;
}
void updateStudentScoreOption(Academic s[],int n){
    char op;
    int isFound=0;
    int searchID;

    while(1){
        system("cls");
        isFound =0;
        cout<<"\n\n\n\n"<<tab<<"Enter studentID to update : "; cin>>searchID;

        for(int i=0; i<n; i++){
            if(s[i].getID() == searchID){
                isFound=1;
                updateScoreOption(s[i]);     
            }
        }
        if(isFound == 0){
            cout<<"\n\n\n\n"<<tab<<"Student ID not found";
            getch();
        }
        Again:
        cout<<"\n\n\n\n"<<tab<<"Do you want to continue(y/n) : "; 
        op = getch();
        if(op == 'Y' || op == 'y')
            continue;
        else if(op == 'N' || op == 'n')
            break;
        else{
            system("cls");
            goto Again;
        }
    }
    

    if(isFound != 0){
        fstream fout;
        fout.open("tmp.bin", ios::out | ios::binary); 
        if(fout.fail()){
            cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
            getch();
            return ;
        }
        fout.write((char*)s, n*sizeof(Person));
        fout.close();

        remove("StudentScore.bin");
        rename("tmp.bin","StudentScore.bin");

    }
    
    getch();
    
}
void updateScoreOption(Academic& s){
    char ch;
    do{
        system("cls");
        cout<<"\n\n\n\n";
        cout<<tab<<"   What do you want to update    \n\n";
        cout<<tab<<"1. English\n"<<endl;
        cout<<tab<<"2. ComputerAchitecture\n"<<endl;
        cout<<tab<<"3. Database system\n"<<endl;
        cout<<tab<<"4. DataStructure Algorithm\n"<<endl;
        cout<<tab<<"5. DataCommunication\n"<<endl;
        cout<<tab<<"6. Cpp Programming\n"<<endl;
        cout<<tab<<"0. Back\n"<<endl;
        cout<<tab<<"Enter option : "; ch = getch();


        system("cls");
        if(ch == '1'){
            float num;
            cout<<endl<<tab<<"Current English   : "<<s.getEng()<<endl;
            cout<<endl<<tab<<"Enter new Score   : "; cin>>num;
            s.setEnglish(num);
            cout<<endl<<tab<<"Update Successfully";
            getch();
        }
        else if(ch == '2'){
            float num;
            cout<<endl<<tab<<"Current ComputerAchitecture   : "<<s.getCa()<<endl;
            cout<<endl<<tab<<"Enter new Score   : "; cin>>num;
            s.setComputerAchitecture(num);
            cout<<endl<<tab<<"Update Successfully";
            getch();
        }
        else if(ch == '3'){
            float num;
            cout<<endl<<tab<<"Current Database system   : "<<s.getDbs()<<endl;
            cout<<endl<<tab<<"Enter new Score   : "; cin>>num;
            s.setDatabase(num);
            cout<<endl<<tab<<"Update Successfully";
            getch();
        }
        else if(ch == '4'){
            float num;
            cout<<endl<<tab<<"Current DataStructure Algorithm   : "<<s.getDsa()<<endl;
            cout<<endl<<tab<<"Enter new Score   : "; cin>>num;
            s.setDatastructureAlgorithm(num);
            cout<<endl<<tab<<"Update Successfully";
            getch();
        }
        else if(ch == '5'){
            float num;
            cout<<endl<<tab<<"Current DataCommunication   : "<<s.getDataCom()<<endl;
            cout<<endl<<tab<<"Enter new Score   : "; cin>>num;
            s.setDataCom(num);
            cout<<endl<<tab<<"Update Successfully";
            getch();
        }
        else if(ch == '6'){
            float num;;
            cout<<endl<<tab<<"Current Cpp Programming   : "<<s.getCpp()<<endl;
            cout<<endl<<tab<<"Enter new Score   : "; cin>>num;
            s.setCpp(num);
            cout<<endl<<tab<<"Update Successfully";
            getch();
        }

    }while(ch != '0');
}
void deleteStudentScore(){
    fstream fin;
    fin.open("StudentScore.bin", ios::in | ios::binary);
    if(fin.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;
    }

    fin.seekg(0, ios::end);
    int n = fin.tellg()/sizeof(Academic);
    fin.seekg(0,ios::beg);

    if(n == 0){
        cout<<"\n\n\n\n"<<tab<<"No Record";
        getch(); 
        return ; 
    }
    
    Academic* s = new Academic[n];
    fin.read((char*)s, n*sizeof(Academic));
    fin.close();

    deleteScore(s,n);

    delete[] s;
    
}
void deleteScore(Academic s[], int n){
    fstream fout;
    fout.open("tmp.bin", ios::out | ios::binary);
    if(fout.fail()){
        cout<<"\n\n\n\n"<<tab<<"ERROR, Cannot openning the file";
        getch();
        return ;
    }
    
    int searchID, isFound=0;
    while(1){
        system("cls");
        isFound =0;
        cout<<endl<<tab<<"Enter StudentID to delete : "; cin>>searchID;

        for(int i=0; i<n; i++){
            if(searchID == s[i].getID()){
                isFound = 1;
                continue;
            }
            else{
                fout.write((char*)&s[i], sizeof(Academic));
            }
        }

        if(isFound == 0){
            cout<<"\n\n\n\n"<<tab<<"Student ID not found";
            getch();
        }
        else{
            cout<<endl<<tab<<"Delete  Successfully";
            getch();
        }

        Again:
        cout<<"\n\n\n\n"<<tab<<"Do you want to continue(y/n) : "; 
        char op = getch();
        if(op == 'Y' || op == 'y')
            continue;
        else if(op == 'N' || op == 'n')
            break;
        else{
            system("cls");
            goto Again;
        }
    } 

    fout.close();
    if(isFound == 1){
        remove("StudentScore.bin");
        rename("tmp.bin", "StudentScore.bin");
    }

}