#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mmsystem.h>
#include <conio.h>
#include "change.h" 
#include <iostream.h>     

void main()
{
	int KOL_PER=0,KOL_CON=5,KOL_FUNC=48;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	char name[128];
	CharToOem("Калькулятор",name);
	Init();
	SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	char start[512]="Для вывода списка функции наберите: список или spisok.\nДля создания новой переменной нужно ввести: per\nЕсли хотите выйти наберите: exit.\n";
	CharToOem(start,start);
	cout<<start<<endl;
	
	SetConsoleTitle(name);
	PCONSOLE_SCREEN_BUFFER_INFO bu=(PCONSOLE_SCREEN_BUFFER_INFO)malloc(sizeof(PCONSOLE_SCREEN_BUFFER_INFO));
	
	bool DefError=false;
	String vir="",
	MessageError="";
	COORD coord;
	double def;
	while (1)
	{
		char enter[128];
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		CharToOem("Введите выражение:",enter);
		cout<<enter<<endl;
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cin.getline(vir.string,1024,'\n');
		if (strcmp(vir.string,"exit"))
		   break;
		
		char buf[128];
		CharToOem("список",buf);
		if (strcmp(vir.string,buf) || strcmp(vir.string,"spisok"))
		{
			CharToOem("Функции:\t\t\tПеременные:\nИмя:\tПриоретет:\tТип:\tИмя:\tЗначение:",buf);
			cout<<buf<<endl;
			int counter=KOL_FUNC;
			if (KOL_FUNC<KOL_PER) counter=KOL_PER;
			for (int i=0; i<counter; i++)
			{
				if (i<KOL_FUNC)
					cout<<action[i].znak.string<<"\t"<<action[i].prioretet<<"\t\t"<<action[i].type<<"\t";
				if (i<KOL_PER)
					cout<<per[i].name.string<<"\t"<<per[i].def.string;
				cout<<endl;
			}
			continue;
		}

		vir.Copy(buf,0,6);

		if (strcmp(buf,"per"))
		{
			int num=0;
			SetConsoleTextAttribute(hOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			CharToOem("Создать новую переменную(0-создать или № переменной-изменить):",enter);
			cout<<enter<<endl;
			SetConsoleTextAttribute(hOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cin.getline(buf,4,'\n');
			num=atoi(buf)%100;
			int k=KOL_PER;

			if ( (num==0 || num>KOL_PER+1) && KOL_PER<100)
			{
				num=KOL_PER;
				k++;
			}
			else
				num=atoi(buf)-1;
		
			bool match=false;
			do
			{
				match=false;
				SetConsoleTextAttribute(hOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				CharToOem("Имя переменной:",enter);
				cout<<enter<<endl;
				SetConsoleTextAttribute(hOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cin.getline(::per[num].name.string,33,'\n');
				for (int i=0; i<KOL_PER; i++)
				{
					if (i==num)
						continue;

					if (strcmp(per[i].name.string,per[num].name.string))
					{
						match=true;
						break;
					}
				}
			}while(match);
			
			do
			{
				SetConsoleTextAttribute(hOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				CharToOem("Значение:",enter);
				cout<<enter<<endl;
				SetConsoleTextAttribute(hOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cin.getline(per[num].def.string,33,'\n');
			}while( Change(per[num].def.string,1,&MessageError,&DefError,action,KOL_FUNC,per,KOL_PER,con,KOL_CON) );//|| strlen(MessageError.string)>0);

			KOL_PER=k;
			continue;
		}

		GetConsoleScreenBufferInfo(hOut,bu);
		coord.Y=bu->dwCursorPosition.Y-1; coord.X=strlen(vir.string);
		::SetConsoleCursorPosition(hOut,coord);
		if (!Change(vir,1,&MessageError,&DefError,action,KOL_FUNC,per,KOL_PER,con,KOL_CON))
			def=Change(vir,0,&MessageError,&DefError,action,KOL_FUNC,per,KOL_PER,con,KOL_CON);
		
		if (DefError || strlen(MessageError.string)>0)
		{
			SetConsoleTextAttribute(hOut,FOREGROUND_RED | FOREGROUND_INTENSITY );
			CharToOem("...Ошибка...",buf);
			cout<<endl<<buf<<endl;
			if (strlen(MessageError.string)>0)
			{
				CharToOem(MessageError.string,MessageError.string);
				cout<<MessageError.string<<endl;
				::GetConsoleScreenBufferInfo(hOut,bu);
				coord.Y=bu->dwCursorPosition.Y-2;
				coord.X=0;
				SetConsoleCursorPosition(hOut,coord);
			}
		}

		if (!DefError && strlen(MessageError.string)==0)
			printf("=%lf",def);
		cout<<endl;
		DefError=false;
	}
}
