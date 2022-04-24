#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
struct Date
{
	int dd,mm,yy;
}date;
struct Remainder{
	int dd,mm;
	char note[50];
}R;

COORD xy={0, 0};

void gotoxy(int x, int y){
	xy.X = x; xy.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);

}
void foreColor(int color)
{
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle,color|FOREGROUND_INTENSITY);     
}
int check_leapYear(int year){
	if(year % 400 == 0 || year %4 ==0 && year %100 !=0){
		return 1;
	}
	else return 0;
}
void increase_month(int *mm, int *yy){
	++*mm;
	if(*mm >12){
		++*yy;
		*mm -=12;
	}
}
void decrease_month(int *mm, int *yy){
	--*mm;
	if(*mm <1){
		--*yy;
		if(*yy <1600){
			printf("No record available");
		}
		*mm+=12;
	}
}
int getNumberOfDays(int month, int year){
	switch(month){
		case 1: return 31;
		case 2:
				if(check_leapYear(year) == 1){
					return 29;
				}
				else return 28;
		case 3: return 31;
		case 4: return 30;
		case 5: return 31;
		case 6: return 30;
		case 7: return 31;
		case 8: return 31;
		case 9: return 30;
		case 10: return 31;
		case 11: return 30;
		case 12: return 31;

	}
}
char *getName(int day){
	switch(day){
		case 0: return "Sunday";
		case 1: return "Monday";
		case 2: return "Tuesday";
		case 3: return "Wednesday";
		case 4: return "Thurday";
		case 5: return "Friday";
		case 6: return "Saturday";
	}
}
char *getMonth(int mm){
	switch(mm){
		case 1: return "January";
		case 2: return "February";
		case 3: return "March";
		case 4: return "April";
		case 5: return "May";
		case 6: return "June";
		case 7: return "July";
		case 8: return "August";
		case 9: return "September";
		case 10: return "October";
		case 11: return "November";
		case 12: return "December";
	}
}
void print_date(int mm, int yy){
	printf("-----------------------\n");
	gotoxy(25,6);
	printf("%s ,%d\n",getMonth(mm),yy);
	gotoxy(20,7);
	printf("-----------------------\n");

}
int getDayNumber(int day, int mon, int year){
	int k=0, t1,t2,y=year;
	year -= 1600;
	while(year >=100){
		k+=5;
		year -= 100;
	}
	k %= 7;
	t1 = (year-1) /4;
	t2 = (year-1) -t1;
	t1 = (t1*2)+t2;
	t1 %= 7;
	k +=t1;
	k %=7;
	t2=0;
	for(t1=1; t1<mon; t1++){
		t2 += getNumberOfDays(t1,y);
		
	}
	t2 += day;
	t2 %= 7;
	k += t2;
	k %= 7;
	if(y>2000){
		k += 1;
	}

	k %= 7;
	return k;
	
}
char *getDay(int dd, int mm, int yy){
	int day;
	if(!(mm>=1 && mm<=12)) return "Invalid month value";
	if(!(dd>=1 && dd<=31)) return "Invalid day value";

	if(yy>=1600){
		day = getDayNumber(dd,mm,yy);
		day %=7;
		return getName(day);
	}else{
		return "Please give year more than 1600";
	}	
}
int checkNote(int dd, int mm){
	FILE *fp;
	fp= fopen("note.dat","rb");
/*
	if(fp == NULL){
		printf("Error in opeing file ");
	}
	*/
	while(fread(&R,sizeof(R),1,fp)== 1){
		if(R.mm == mm && R.dd == dd){
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;


}
void printMonth(int mon , int year, int x, int y){
	int nod, day, cnt, d=1, x1=x, y1=y, isNote =0;
	if(!(mon>=1 && mon<=12)){
		printf("Invalid Month");
		getch();
	}
	if(!(year>1600)){
		printf("Invalid Year");
		getch();
	}
	gotoxy(20,y); print_date(mon,year);
	y += 3;
	
	gotoxy(x,y);  
	foreColor(12); printf("S");
	foreColor(7);
	printf("   M   T   W   TH   F   S  ");
	y++;
	nod = getNumberOfDays(mon,year);
	day = getDayNumber(d,mon,year);
	switch(day){
		case 0: x=x;  cnt=1;   break;
		case 1: x+=4;  cnt=2;   break;
		case 2: x+=8;  cnt=3;   break;
		case 3: x+=12;  cnt=4;   break;
		case 4: x+=16;  cnt=5;   break;
		case 5: x+=20;  cnt=6;   break;
		case 6: x+=24;  cnt=7;   break;
	}
	if(cnt ==1) foreColor(12);
	if(checkNote(d,mon)==1) foreColor(12);
	gotoxy(x,y); printf("%2d",d);


	for(d=2; d<=nod; d++){
		foreColor(7);
		if(cnt %7==0){
			y+=1;
			cnt =0;
			x=x1-4;
		}
		x+=4;
		cnt++;
		
		if(cnt==1) foreColor(12);
		else foreColor(7);

		if(checkNote(d,mon) == 1){
			foreColor(12);
		}

		gotoxy(x,y); printf("%2d",d);

		
	}
	
	foreColor(2);
	gotoxy(8,y+2); printf("Press 'n'<NEXT> , 'p'<PREVIOUS>, 'q'<QUIT> ");
	gotoxy(8,y+3); printf("to see HOLIDAY Note,Press 's'<See note> ");
	foreColor(7);

}
void AddNote(){
	FILE *fp;
	fp=fopen("note.dat","ab+");
	system("cls");
	gotoxy(25,2); printf("Enter DATE ");
	gotoxy(20,5); printf("Day: ");
	gotoxy(30,5); printf("Month: ");
	gotoxy(25,5); scanf("%d",&R.dd);
	gotoxy(37,5); scanf("%d",&R.mm);
	
	gotoxy(5,7); printf("Enter the Note(50): "); fflush(stdin); gets(R.note);

	if(fwrite(&R,sizeof(R),1,fp)==1){
		gotoxy(5,12); foreColor(2); puts("Note is saved successfully");
		

	}
	else{
		gotoxy(5,12); foreColor(12); puts("Fail to save");
	}
	foreColor(7);
	gotoxy(5,15);
	printf("Press any key...........");
	getch();
	fclose(fp);

}
void deleteNote(){
	system("cls");
	int isFound=0;
	FILE *fp,*temp;
	fp= fopen("note.dat","rb");
	temp = fopen("temp.dat","ab");

	gotoxy(25,2); printf("Enter DATE TO DELETE");
	gotoxy(20,5); printf("Day: ");
	gotoxy(30,5); printf("Month: ");
	gotoxy(25,5); scanf("%d",&date.dd);
	gotoxy(37,5); scanf("%d",&date.mm);

	while(fread(&R,sizeof(R),1,fp)==1){
		if(R.mm == date.mm & R.dd == date.dd){
			isFound =1;
		}
		else{
			fwrite(&R,sizeof(R),1,temp);
		}
	}
	gotoxy(5,12);
	if(isFound == 0) printf("No Note");
	else printf("Delete Note successfully");
	
	fclose(fp);
	fclose(temp);
	remove("note.dat");
	rename("temp.dat","note.dat");

	
	getch();

}
void showNote(int mm){
	FILE *fp;
	fp=fopen("note.dat","rb");
	system("cls");

	int i=0, isFound=0;

	
	while(fread(&R,sizeof(R),1,fp)==1){
		if(R.mm == mm){
			gotoxy(10,5+i);
			printf("Note %d day = %d : %s",i+1,R.dd,R.note);
			isFound=1;
			i++;
		}
	}
	if(isFound == 0){
		gotoxy(10,5); printf("This Month contains no note");
	}
	gotoxy(10,7+i); printf("Press any key to back.....");
	getch();

}
void main(){
	int ch1;
	char ch='a';

	do{
		system("cls");
		printf("\n\t\t==========================");
		printf("\n\t\t       C Calender           ");
		printf("\n\t\t==========================");
		printf("\n\t\t1. Find Out the date");
		printf("\n\t\t2. Print all the Month");
		printf("\n\t\t3. Add Note");
		printf("\n\t\t4. Delete note");
		printf("\n\t\t0. Exit");
		printf("\n\t\t==========================");
		printf("\n\t\t     Enter option : "); scanf("%d",&ch1);
		switch(ch1){
			case 1: 
					system("cls");
					gotoxy(25,2); printf("==> Find Out the date <=="); 
					gotoxy(20,5); printf("Day: ");
					gotoxy(30,5); printf("Month: ");
					gotoxy(42,5); printf("Year: ");
					gotoxy(25,5); scanf("%d",&date.dd);
					gotoxy(37,5); scanf("%d",&date.mm);
					gotoxy(48,5); scanf("%d",&date.yy);
			
					gotoxy(23,8); printf("Day :");
					gotoxy(30,8); foreColor(2); printf("%s",getDay(date.dd,date.mm,date.yy));
					foreColor(7);
					getch();
			break;
			
			case 2:
					system("cls");
					gotoxy(25,1); printf("==> Input DATE <=="); 
					gotoxy(20,3); printf("Month: ");
					gotoxy(35,3); printf("Year: ");
					gotoxy(27,3); scanf("%d",&date.mm);
					gotoxy(41,3); scanf("%d",&date.yy);
					do{
						system("cls");
						printMonth(date.mm,date.yy,20,5);
						ch = getch();
						switch(ch){
							case 'n':
									increase_month(&date.mm,&date.yy);
									system("cls");
									printMonth(date.mm,date.yy,20,5);
							break;
							case 'p':
									decrease_month(&date.mm,&date.yy);
									system("cls");
									printMonth(date.mm,date.yy,20,5);
							break;
							case 's':
									showNote(date.mm);
									system("cls");
							break;
						}
					}while(ch != 'q');


			break;
			case 3:AddNote(); break;
			case 4: deleteNote(); break;
					 
			
		}
	}while(ch1 != 0);

}