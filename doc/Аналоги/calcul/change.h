#define  PI				3.1415926
#define  LENGTH			1024
#define  FUNC		100//Кол-во функций 
#define  PER		100// кол-во переменных
#define  FUNC_ST    50//Кол-во стандартных функций
#define  CON      100//Кол-во констант

struct String
{
	char string[LENGTH];

	void Delete(int begin,int length)
	{
		int i,j;

		for (j=0; j<length; j++)
		{
			for (i=begin; (unsigned int)i<=strlen(string); i++)
			{
				string[i-1]=string[i];
			}
		}

		if ((unsigned int)begin+length>strlen(string))
			string[begin+length]=0;
	}

	void Insert(const char *b,unsigned int c )
	{
		unsigned int i,k,s=strlen(string);
	
		for (k=1; k<=strlen(b);k++)   //Смещаем буквы на strlen(B) с позиции C
		{
			for (i=strlen(string)+1;i>c;i--)
			{
				string[i]=string[i-1];
			}
		}

		for (i=c;i<strlen(b)+c;i++)
			string[i]=b[i-c];

		if (c==s)
			string[c+strlen(b)]=0;
	}		

	void Copy(char *b,int c,int d)
	{
		int i;

		for (i=c;i<=c+d-1;i++)
			b[i-c] = string[i];
		b[d]=0;
	}

	char* operator=(char *buf)
	{
		strcpy(string,buf);
		return buf;
	}
	
	char* operator+(char *buf)
	{
		char *b=string;
		strcat(b,buf);
		return b;
	}

	char* operator+=(char *buf)
	{
		char *b=string;
		strcat(b,buf);
		strcpy(string,b);
		return b;
	}

	String(char *buf)
	{
		strcpy(string,buf);
	};

	String()
	{
	};
};

struct Const
{
	String name;
	double def;
};

struct Pr
{
	String def;
	String name;
};

Pr per[PER];
String vid[FUNC-FUNC_ST];
String error;
Const con[CON];

int Round(double a)
{
	if (a>=0) return(int)(a+0.5);
	return (int)(a-0.5);
}

long int Factorial(int n)
{
	if (n==0) return 1;
		else return Factorial(n-1)*n;
}

long int Factorial2(int n)
{
	if (n==0 || n==1) return 1;
	   else return n*Factorial2(n-2);
}

long int Fibon(int n)
{
	if (n==0 || n==1) return 1;
	else
		return Fibon(n-1)+Fibon(n-2);
}

struct Action
{
	String znak;
	int prioretet,type;
};


double Change(String a,int num,String *MessageError,bool *def_error,Action* action,int FUNC_KOL,Pr* per,int PER_KOL,String* con,int CON_KOL);

Action action[FUNC];

void AddOperation(int num,char* buf,int prioretet,int type)
{
	action[num].znak=buf; action[num].type=type; action[num].prioretet=prioretet;
}

void Init()
{
	con[0].name="Pi"; con[0].def=PI;
	con[1].name="e";  con[1].def=2.718281828459045;
	con[2].name="g";  con[2].def=9.81;
	con[3].name="Ф";  con[3].def=(sqrt(5)+1)/2;
	con[4].name="ф";  con[4].def=1/con[3].def;//const

	AddOperation( 0,"+",1,1);
	AddOperation( 1,"-",1,1);
	AddOperation( 2,"*",2,1);
	AddOperation( 3,"/",2,1);
	AddOperation( 4,"^",3,1);
	AddOperation( 5,"div",2,1);
	AddOperation( 6,"mod",2,1);
	AddOperation( 7,"cos",3,2);
	AddOperation( 8,"sin",3,2);
	AddOperation( 9,"arccos",3,2);
	AddOperation(10,"arcsin",3,2);
	AddOperation(11,"round",3,2);
	AddOperation(12,"abs",3,2);
	AddOperation(13,"tg",3,2);
	AddOperation(14,"ctg",3,2);
	AddOperation(15,"arctg",3,2);
	AddOperation(16,"arcctg",3,2);
	AddOperation(17,"not",3,2);
	AddOperation(18,"==",1,1);
	AddOperation(19,"and",1,1);
	AddOperation(20,"or",1,1);
	AddOperation(21,"!=",1,1);
	AddOperation(22,"exp",3,2);
	AddOperation(23,"ln",3,2);
	AddOperation(24,"!",3,0);
	AddOperation(25,"rad",3,2);
	AddOperation(26,"deg",3,2);
	AddOperation(27,"cosh",3,2);
	AddOperation(28,"sinh",3,2);
	AddOperation(29,"->",1,1);
	AddOperation(30,"<-",1,1);
	AddOperation(31,"<->",1,1);
	AddOperation(32,"|",1,1);
	AddOperation(33,"#",1,1);
	AddOperation(34,"<<",1,1);
	AddOperation(35,">>",1,1);
	AddOperation(36,"sec",3,2);
	AddOperation(37,"cosec",3,2);
	AddOperation(38,"!!",3,0);
	AddOperation(39,"fibon",3,2);
	AddOperation(40,"c",3,3);
	AddOperation(41,"random",3,2);
	AddOperation(42,"sqr",3,2);
	AddOperation(43,"sqrt",3,2);
	AddOperation(44,">=",1,1);
	AddOperation(45,"<=",1,1);
	AddOperation(46,">",1,1);
	AddOperation(47,"<",1,1);
}

int strcmp(const char* a,const char* b)
{
	int value=1;
	if (strlen(a)==strlen(b))
	{
		for (int i=0;(unsigned)i<strlen(a);i++)
		{
			if (a[i]!=b[i])
			{
				value=0;
				break;
			}
		}
	}
	else 
		value=0;
	return value;
}

void Delete( char *a, int b,int n )
{
	unsigned int i;
	for (i=b+n;i<=strlen(a); i++)
	{
		a[i-n]=a[i];
	}
}

void DeleteProbel(String *vir)
{
	for (unsigned int i=0; i<strlen(vir->string); i++)//Удаление пробелов
		{
			if (vir->string[i]==' ') 
			{
				Delete(vir->string,i,1);
				i-=1;
			}
		}	
}

int Begin(String a,unsigned int pos,Action* action,int FUNC_KOL)
{
	String b;
	unsigned int MaxLength=0;
	int k=0,l=0;
	for (int i=0; i<FUNC_KOL; i++)
	{
		if (strlen(action[i].znak.string)>0)
		{
			a.Copy(b.string,pos,strlen(action[i].znak.string));
			if ( strcmp(b.string,action[i].znak.string)==1 && strlen(action[i].znak.string)>MaxLength && ( ( (a.string[pos+strlen(action[i].znak.string)]>=0 && a.string[pos+strlen(action[i].znak.string)]<=256) ) || a.string[pos+strlen(action[i].znak.string)]=='?'  || a.string[pos+strlen(action[i].znak.string)]=='('  ))
			{
				MaxLength=strlen(action[i].znak.string);
				l=i;
			}
		}
	}
	if (MaxLength>0) k=l;
		else k=-1;
	return k;
}

int End(String a,unsigned int pos,Action* action,int FUNC_KOL)
{
	String b;
	unsigned int MaxLength=0;
	int k=0,l=0;
	for (int i=0; i<FUNC_KOL; i++)
	{
		if (strlen(action[i].znak.string)>0)
		{
			a.Copy(b.string,pos-strlen(action[i].znak.string)+1,strlen(action[i].znak.string));
			if ( strcmp(b.string,action[i].znak.string)==1 && strlen(action[i].znak.string)>MaxLength && ( (a.string[pos-strlen(action[i].znak.string)]>=0 && a.string[pos-strlen(action[i].znak.string)]<=256) || (pos-strlen(action[i].znak.string+1)==0) || a.string[ pos-strlen(action[i].znak.string) ]=='(' ) )//48 57
			{
				MaxLength=strlen(action[i].znak.string);
				l=i;
			}
		}
	}
	if (MaxLength>0) k=l;
	else k=-1;
	return k;
}

double Convert(String *a,String *MessageError,bool *def_error,Action* action,int FUNC_KOL,Pr* per,int PER_KOL,Const *con,int CON_KOL)
{
	int k=Begin(*a,0,action,FUNC_KOL);
	if (k!=-1 && action[k].type<2) 
		a->Insert("0",0);
	if (a->string[0]=='?') a->Insert("0+",0);
		
	bool error=false;
	String l,r;
	int n;
	for (int p=3; p>0; p--)//Приоретет
	{
		for (unsigned int i=0; i<strlen( a->string ); i++)//Длина A
		{
			if ( (n=Begin(*a,i,action,FUNC_KOL))>-1) //Если встретил знак
			{
				if ( action[n].prioretet==p )//и приоретет знака==p
				{
					if ( action[n].type==1 || action[n].type==0)
					{
						double left=0,right=0;
						int l1=0,r1=0;
						unsigned int k=i-1;
						while ( k>0 && End(*a,k,action,FUNC_KOL)==-1 )
						{
							if (k==0) break;
							k--;
						}
						if (k==0) k--;
						l1=k;
						a->Copy(l.string,l1+1,i-l1-1);
						k=i+strlen(action[n].znak.string);
		
						while ( Begin(*a,k,action,FUNC_KOL)==-1)
						{
							if (k==strlen(a->string)) break;
							k++;
						}
						r1=k;
						a->Copy(r.string,i+strlen(action[n].znak.string),k-i-strlen(action[n].znak.string));
						if (l.string[0]=='?') l.string[0]='-';
						if (r.string[0]=='?') r.string[0]='-';
						left=atof(l.string); right=atof(r.string);

						double total=0;
						switch(n)
						{
						case 0:total=left+right;
							   break;
						case 1:total=left-right;
							   break;
						case 2:total=right*left;
							   break;
						case 3:if (right==0) 
							   {
								 if (def_error!=0) 
								 {
									 *def_error=true;
									 *MessageError+="Деление на ноль\n";
								 }
							   }
							   else
								total=left/right;
							   break;
						case 4:if (left<0 && right!=(int)right) 
							   {
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно возвести в степень\n";
								   }
							   }
							   else
								total=pow(left,right);
							   break;
						case 5:if (right==0)
							   {
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Деление на ноль\n";
								   }
							   }
							   else
								total=(int)(left/right);//div
							   break;
						case 6:if (right==0) 
							   {
								   *def_error=true;
								   *MessageError+="Деление на ноль\n";
							   }
							   else
								total=(int)left % (int)right;//mod;
							   break;
						case 18:total=(left==right);//==
							   break;
						case 19:total=(left && right);//&
							  break;
						case 20:total=(left || right);
							  break;
						case 21:total=(left!=right);
							  break;
						case 24:if (left<0 || (int)left!=left) 
									{
										if (def_error!=0) 
										{
											*def_error=true;
											*MessageError+="Невозможно вычислить факториал\n";
										}
									}
							    else
								  total=Factorial(abs(Round(left)));
							  break;
						case 29:total=!left || right;
							  break;
						case 30:total=left || !right;
							  break;
						case 31:total=!( ( (int)left+(int)right ) %2 );
							  break;
						case 32:total=!(left && right);
							  break;
						case 33:total=!left && !right;
							  break;
						case 34:total=(int)left << (int)right;
							  break;
						case 35:total=(int)left >> (int)right;
							  break;
						case 38:if (left<0 || (int)left!=left) 
								{
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить факториал2\n";
								   }
								}
							    else
								  total=Factorial2(abs(Round(left)));
							  break;
						case 44:total=left>=right;
							  break;
						case 45:total=left<=right;
							  break;
						case 46:total=left>right;
							  break;
						case 47:total=left<right;
							  break;
						}
		
						String total_s;
						sprintf(total_s.string,"%f",total);
						if (total_s.string[0]=='-') total_s.string[0]='?';
						if (action[n].type==1)
							a->Delete(l1+2,r1-l1-1);
						if (action[n].type==0)
							a->Delete(l1+2,i-l1-1+strlen(action[n].znak.string));
						a->Insert(total_s.string,l1+1);
						i=0;
					}
					if (action[n].type>=2)//cos(...)
					{
						int kol=action[n].type-1,j;
						String bet;
						double x[100];
						int s,e;
						int sc=0;

						s=i+strlen(action[n].znak.string);
						for (j=s;(unsigned)j<strlen(a->string);j++)//Начало и конец скобок
						{
							if (a->string[j]=='(') sc--;
							if (a->string[j]==')' && sc==-1) break;

							if (a->string[j]==')' ) sc++;
						}
	
						a->Copy(bet.string,i+strlen(action[n].znak.string),j-i-strlen(action[n].znak.string)+1);//Между скобками
						
						e=j;
	
						int u=s+1;
						String zap;
						int h=0;
						for (j=s+1;j<e;j++)//Берём значения x
						{
							if (a->string[j]==',')
							{
								a->Copy(zap.string,u,j-u);
								u=j+1;
								x[h]=Convert(&zap,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL);
								h++;
							}
						}
						a->Copy(zap.string,u,e-u);
						
						x[h]=Convert(&zap,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL);
						if (a->string[i+strlen(action[n].znak.string)+1]==')') 
						{
							error=true;
							*MessageError+="Отсутсвие аргумента в ";
							*MessageError+=action[n].znak.string;
							*MessageError+="\n";
							*def_error=true;
							a->Delete(0,strlen(a->string));
						};

						if (!error && h+2!=action[n].type)
						{
							error=true;
							strcat(MessageError->string,"Неправильное кол-во аргументов в функции ");
							strcat(MessageError->string,action[n].znak.string);
							strcat(MessageError->string,"\n");
							*def_error=true;
						}

						double total=0;
						if (!error)
						{
						switch(n)
						{
						case 7:total=cos(x[0]);
							   break;
						case 8:total=sin(x[0]);
							   break;
						case 9:if (x[0]>1 || x[0]<-1) 
							   {
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить arccos\n";
								   }
							   }
							   else
								 total=acos(x[0]);
							   break;
						case 10:if (x[0]>1 || x[0]<-1) 
								{
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить arcsin\n";
								   }
								}
							    else
									total=asin(x[0]);
							   break;
						case 11:total=Round(x[0]);
							   break;
						case 12:if (x[0]>0) total=x[0];
									else total=-x[0];
								break;
						case 13:if (cos(x[0])==0) 
								{
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить tg\n";
								   }
								}
								else
									total=sin(x[0])/cos(x[0]);
							    break;
						case 14:if (sin(x[0])==0) 
								{
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить ctg\n";
								   }
								}
								else
									total=cos(x[0])/sin(x[0]);
							    break;
						case 15:total=atan(x[0]);
							    break;
						case 16:if (x[0]<0)
									total=atan(1/x[0])+PI/2;
								if (x[0]==0)
									total=0;
								if (x[0]>0)
									total=atan(1/x[0])-PI/2;
							    break;
						case 17:total=(int)(x[0]+1)%2;//~
							    break;
						case 22:total=exp(x[0]);
							    break;
						case 23:if (x[0]<=0) 
								{
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить ln\n";
								   }
								}
								else total=log(x[0]);
								break;
						case 25:total=x[0]*PI/180;
								break;
						case 26:total=x[0]*180/PI;
								break;
						case 27:total=cosh(x[0]);
							    break;
						case 28:total=sinh(x[0]);
							    break;
						case 36:if (sin(x[0])==0) 
								{
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить sec\n";
								   }
								}
								else
								   total=1/sin(x[0]);
							    break;
						case 37:if (cos(x[0])==0) 
								{
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить cosec\n";
								   }
								}
								else
								   total=1/cos(x[0]);
							    break;
						case 39:if (x[0]<0 || (int)x[0]!=x[0]) 
								{
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить последовательность Фибонначи\n";
								   }
								}
							    else
								  total=Fibon(abs(Round(x[0])));
							  break;
						case 40:if (x[0]<0 || (int)x[0]!=x[0] || x[1]>x[0] || x[1]<0 || (int)x[1]!=x[1]) 
								{
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить бином Ньютона\n";
								   }
								}
							    else
								  total=Factorial((int)x[0])/(Factorial((int)x[1])*Factorial((int)x[0]-(int)x[1]));
							  break;
						case 41:if (x[0]<1 || (int)x[0]!=x[0]) 
								{
									*def_error=true;
									*MessageError+="Невозможно найти число\n";
								}
							    else
									total=rand()%(int)x[0];
							  break;
						case 42:total=x[0]*x[0];
							  break;
						case 43:if (x[0]<0) 
								{
								   if (def_error!=0) 
								   {
									   *def_error=true;
									   *MessageError+="Невозможно вычислить квадратный корень\n";
								   }
								}
							  else
							    total=sqrt(x[0]);
							  break;
						}
							if (n>=FUNC_KOL)
							{
							//	String b,c;
							//	strcpy(c.string,vid[n-KOL_FUNC_ST].string);
							//	int s,e,k;
							//	for (int i=0; (unsigned)i<strlen(c.string); i++)
							//	{
							//		if (c.string[i]=='[') s=i;
							//		if (c.string[i]==']') 
							//		{
							//			e=i;
							//			c.Copy(b.string,s+1,e-s-1);
							//			k=atoi(b.string)-1;
							//			sprintf(b.string,"%f",x[k]);
							//			c.Delete(s,e-s+2);
							//			c.Insert(b.string,s-1);
							//			i=-1;
							//		}
							//	}
							//	if (!Change(c,1,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL))
							//		total=Change(c,0,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL);
							//	else
							//		total=0;
							}

						String total_s;
						sprintf(total_s.string,"%f",total);
						a->Delete(i+1,e-i+1);
						if (total_s.string[0]=='-') total_s.string[0]='?';
						a->Insert(total_s.string,i);
						}
						if (a->string[0]=='-') a->string[0]='?';
						i=0;
					}
				}
			}
		}
	}
	if (a->string[0]=='?') a->string[0]='-';
	return atof(a->string);
}

double Scobki(String *a,String *MessageError,bool *def_error,Action* action,int FUNC_KOL,Pr* per,int PER_KOL,Const* con,int CON_KOL)
{
	int s=0,e=0;
	String bet,in;
	bool error=false;

	for (unsigned int i=0;i<strlen(a->string);i++)
	{
		if (a->string[i]=='(') s++;
		if (a->string[i]==')') s--;
		if (s<0) break;
	}
	if (s!=0) 
	{
		error=true;
		strcat(::error.string,"Не соответсвие скобок\n");
	}

	if (e==false)
	{
	for (i=0;(unsigned)i<strlen(a->string);i++)
	{
		if (a->string[i]=='(') s=i;
		if (a->string[i]==')') 
		{
			e=i;
			int end=End(*a,s-1,action,FUNC_KOL);
			if ( end==-1 || action[end].type==1 || action[end].type==0 )
			{
				a->Copy(bet.string,s+1,e-s-1);	
				double f=Convert(&bet,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL);
				sprintf(in.string,"%f",f);
				if (in.string[0]=='-') in.string[0]='?';
				a->Delete(s+1,e-s+1);
				a->Insert(in.string,s);
				Scobki(a,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL);
				int i=-1;
			}
			else
			{
				int length=strlen(action[end].znak.string);
				a->Copy(bet.string,s-length,e-s+length+1 );
				double f=Convert(&bet,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL);
				String f_s;
				sprintf(f_s.string,"%f",f);
				if (f_s.string[0]=='-') f_s.string[0]='?';
				a->Delete(s-length+1,e-s+length+1);
				a->Insert(f_s.string,s-length);
				Scobki(a,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL);
				int i=-1;
			}
		}
	}
	}
	return Convert(a,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL);
}

void Con( String *vir,Const* con,int CON_KOL,Action* action,int FUNC_KOL)
{
for (unsigned int i=0; i<strlen(vir->string); i++)
	{
		String bet;
		for (int j=CON_KOL-1;j>=0;j--)
		{
			if (strlen(con[j].name.string)>0)
			{
				vir->Copy(bet.string,i,strlen(con[j].name.string));
				int b=Begin(*vir,i+strlen(con[j].name.string),action,FUNC_KOL),e=End(*vir,i-1,action,FUNC_KOL);
				if ( strcmp(bet.string,con[j].name.string)==1  && 
					(i==0 || (e>-1 && action[e].type==1) || vir->string[i-1]=='(' || vir->string[i-1]==','  || vir->string[i-1]=='?') && 
					(i+strlen(con[j].name.string)==strlen(vir->string) || (b>-1 && action[b].type==0) || b>-1 && (action[b].type==1) || vir->string[i+strlen(con[j].name.string)]==')' || vir->string[i+strlen(con[j].name.string)]==',' ) )
				{
					char buf[128];
					vir->Delete(i+1,strlen(con[j].name.string));
					sprintf(buf,"%f",con[j].def);
					if (buf[0]=='-') buf[0]='?';
					vir->Insert(buf,i);
					i=0;
				}
			}
		}
	}
}

void Per( String *vir,Const *con,int CON_KOL,Pr* per,int PER_KOL,Action* action,int FUNC_KOL )
{
	for (unsigned int i=0; i<strlen(vir->string); i++)
	{
		String bet;
		for (int j=PER_KOL-1;j>=0;j--)
		{
			if (strlen(per[j].name.string)>0 && Begin(*vir,i,action,FUNC_KOL)==-1)
			{
				vir->Copy(bet.string,i,strlen(per[j].name.string));
				int b=Begin(*vir,i+strlen(per[j].name.string),action,FUNC_KOL),e=End(*vir,i-1,action,FUNC_KOL);
				if ( strcmp(bet.string,per[j].name.string)==1  && 
					(i==0 || (e>-1 && action[e].type==1) || vir->string[i-1]=='(' || vir->string[i-1]==',' || vir->string[i-1]=='?') && 
					(i+strlen(per[j].name.string)==strlen(vir->string) || (b>-1 && action[b].type==0) || (b>-1 && action[b].type==1) || vir->string[i+strlen(per[j].name.string)]==')' || vir->string[i+strlen(per[j].name.string)]==',' ) )
				{
					vir->Delete(i+1,strlen(per[j].name.string));
					vir->Insert("(",i);
					vir->Insert(per[j].def.string,i+1);
					vir->Insert(")",i+1+strlen(per[j].def.string) );
					Con(vir,con,CON_KOL,action,FUNC_KOL);
					Per(vir,con,CON_KOL,per,PER_KOL,action,FUNC_KOL);
				}
			}
		}
	}
}

double Change(String a,int num,String *MessageError,bool *def_error,Action* action,int FUNC_KOL,Pr* per,int PER_KOL,Const* con,int CON_KOL)
{
	String vir=a;

	if ( (num==1 || num==3) && MessageError!=0)
	{
		static int from;
		if (num==1)
			from=0;
		*MessageError="";
		bool error=false;
		int s=0;
		DeleteProbel(&a);
		Con(&a,con,CON_KOL,action,FUNC_KOL);
		Per(&a,con,CON_KOL,per,PER_KOL,action,FUNC_KOL);

		for (unsigned int i=0;i<strlen(a.string);i++)
		{
			if (a.string[i]=='(') s++;
			if (a.string[i]==')') s--;
			if (s<0) break;
		}

		if (s!=0) 
		{
			*MessageError+="Не соответсвие скобок\n";
			error=true;
			return true;
		}
		else
		{
			for (i=0;i<strlen(a.string);i++)
			{
				int n=Begin(a,i,action,FUNC_KOL);
				
				if (n>-1 && action[n].type==1)
				{
					i+=strlen(action[n].znak.string)-1;
					int k=0;
					if (i+1<strlen(a.string))
						k=Begin(a,i+1,action,FUNC_KOL);
	
					if ( !( (k>-1 && action[k].type>=2) || (a.string[i+1]>='0' && a.string[i+1]<='9') || a.string[i+1]=='(' || a.string[i+1]=='?') || a.string[i+1]==',' )
					{
						error=true;
						*MessageError+="Неверный вид\n";
						return true;
					}
					continue;
				}

				if (n>-1 && action[n].type==0)
				{
					i+=strlen(action[n].znak.string)-1;
					int k=0;
					if (i+1<strlen(a.string))
						k=Begin(a,i+1,action,FUNC_KOL);
					if ( !( (k>-1 && action[k].type<2) || a.string[i+1]==',' || a.string[i+1]==')' || i+1==strlen(a.string))  )
					{
						error=true;
						*MessageError+="Неверный вид\n";
						return true;
					}
					continue;
				}

				if ( n>-1 && action[n].type>=2)
				{
					if ( a.string[i+strlen(action[n].znak.string)]!='(' )
					{
						*MessageError+="Отсутсвие скобки после ";
						*MessageError+=action[n].znak.string;
						*MessageError+="\n";
						error=true;
						i+=strlen(action[n].znak.string)-1;
						continue;
					}
					else
						{
							unsigned int j=i+strlen(action[n].znak.string)-1;
							int zap=0,s=0; bool e=false;
							while (1)
							{
								j++;

								if (a.string[j]=='(')
								{
									e=true;
									s++;
								}

								if (a.string[j]==')')
								{
									e=true;
									s--;
								}
	
								if (s==0 && a.string[j]==',')
								{
									zap++;
								}

								if (j>=strlen(a.string) || (s==0))
								{
									break;
								}

								if (!error && zap>action[n].type-2)
								{
									error=true;
									*MessageError+="Неправильное кол-во аргументов в функции ";
									*MessageError+=action[n].znak.string;
									*MessageError+="\n";
								}
							}
							String bet;
							a.Copy(bet.string,i+strlen(action[n].znak.string)+1,j-i-strlen(action[n].znak.string)-1);
							from=from+strlen(action[n].znak.string)+1;
							if (Change(bet,3,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL))
								error=true;
							i=j;
							int n=0;
							if (j+1<strlen(a.string))
								n=Begin(a,i+1,action,FUNC_KOL);
							if ( !( (n>-1 && action[n].type<2) || a.string[i+1]==',' || a.string[i+1]==')' || j+1==strlen(a.string))  )
							{
								error=true;
								*MessageError+="Неверный вид\n";
								return true;
							}
						}
					continue;
				}

				if ( n==-1 && !( (a.string[i]>='0' && a.string[i]<='9') || a.string[i]=='?' || a.string[i]=='.' || a.string[i]=='(' || a.string[i]==')' || a.string[i]==',') )
				{
					*MessageError+="Неверный символ: ";
					char buf[128];
					itoa(i+1+from,buf,10);
					*MessageError+=buf;
					*MessageError+="\n";
					error=true;
				}
			}
		}
		if (error)
			return 1;
		else 
			return 0;
	}

	if (num==2)
	{
		Per(&vir,con,CON_KOL,per,PER_KOL,action,FUNC_KOL);

		return Scobki(&vir,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL);
	}

	if (num==0)
	{
		DeleteProbel(&vir);	
		
		Con(&vir,con,CON_KOL,action,FUNC_KOL);//Замена контстант
		Per(&vir,con,CON_KOL,per,PER_KOL,action,FUNC_KOL);//Замена переменных
	
		return Scobki(&vir,MessageError,def_error,action,FUNC_KOL,per,PER_KOL,con,CON_KOL);
	}
	return 0;
}