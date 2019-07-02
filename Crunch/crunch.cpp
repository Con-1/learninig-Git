#include<iostream>
#include<conio.h>
#include<string>
#include<stdio.h>
#include<sstream>
#include<fstream>

using namespace std;

ofstream fout;
int count=0;
string cmd="";
int flag=1;

class DataSets
{
	public:
		const string numeric="0123456789";
		const string lower="qwertyuiopasdfghjklzxcvbnm";
		const string upper="QWERTYUIOPASDFGHJKLZXCVBNM";
		const string lowup=lower+upper;
		const string lownum=lower+numeric;
		const string upnum=upper+numeric;
		const string all=numeric+lower+upper;
		string special;
}ds;


class inputs
{
	public:
		int flagDataset=0;
		int flagReplace=0;
		int min=0;
		int max=0;
		int setSize;
		string insString;
		string Dataset;
}in;		

void ini()
{
	cmd="";
	count=0;
	in.min=0;
	in.max=0;
	in.flagDataset=0;
	in.flagReplace=0;
	flag=1;
}

class generate
{
	public:
		void makeword(string dataset, string str,int sizeofset, int sizeofword) 
		{	 
			if (sizeofword == 0) 
			{		 
				fout<<str<< endl; 
				return; 
			}	 
			for (int i=0;i<sizeofset;i++) 
			{ 
				string finstr; 
				finstr = str + dataset[i]; 
				makeword(dataset, finstr, sizeofset, sizeofword - 1); 
			} 
		}	
		
		void makewordreplace(int relist[],string dataset, string str,int sizeofset, int sizeofword) 
		{	 
			if (sizeofword == 0) 
			{	
				for(int i=0;i<in.min;i++)
				{
					in.insString[relist[i]]=str[i];	
				} 
				fout<<in.insString<< endl; 
				return; 
			}	 
			for (int i=0;i<sizeofset;i++) 
			{ 
				string finstr; 
				finstr = str + dataset[i]; 
				makewordreplace(relist,dataset, finstr, sizeofset, sizeofword - 1); 
			} 
		}	 
}wd;

class GetCommand
{
	public:
		void getcmd()
		{
			cout<<"C:/>";
			fflush(stdout);
			getline(cin,cmd);
		}
}cmnd;

class GetPhrase
{
	public:
		string temp;
		int del;		
		void parse()
		{
			stringstream wd(cmd);
			while(wd>>temp)
			{
				count++;
				if(count==1&&temp!="crunch")
				{
					cout<<"\n'"<<temp<<"' is not recognized as an internal or external command,operable program or batch file."<<endl;
					flag=0;		
					break;
				}
				else if(count==2)
				{
					for(int i=0;i<temp.length();i++)
					{
						if(!isdigit(temp[i]))
						{
							cout<<"Please enter the corect parameters :: The Min and Max lenght should be of Int type";
							cout<<endl<<"For help you can use command \"crunch --help\"\n";
							flag=0;
							break;
						}
						else
						{
							in.min=in.min*10+(int(temp[i])-48);
						}
					}
				}
				else if(count==3)
				{
					for(int i=0;i<temp.length();i++)
					{
						if(!isdigit(temp[i]))
						{
							cout<<"Please enter the corect parameters :: The Min and Max lenght should be of Int type";
							cout<<endl<<"For help you can use command \"crunch --help\"\n";
							flag=0;
							return;
						}
						else
						{
							in.max=in.max*10+(int(temp[i])-48);
						}
					}
					if(in.min>in.max)
					{
						cout<<"ERROR::Min length can not be greater than the Max length";
						cout<<endl<<"For help you can use command \"crunch --help\"\n";
						flag=0;
						break;
					}
				}
				else if(count>3)
				{
					if(temp=="-d")
					{
						if(in.flagDataset==1)
						{
							cout<<"ERROR::INVALID PARAMETERS YOU CAN ONLY USE ALN ARGUMENT ONCE";
							cout<<endl<<"For help you can use command \"crunch --help\"\n";
							flag=0;
							break;	
						}
						wd>>temp;
						in.flagDataset=1;
						if(temp=="num")
							in.Dataset=ds.numeric;
						else if(temp=="lower")
							in.Dataset=ds.lower;
						else if(temp=="upper")
							in.Dataset=ds.upper;
						else if(temp=="lownum")
							in.Dataset=ds.lownum;
						else if(temp=="upnum")
							in.Dataset=ds.upnum;
						else if(temp=="all")
							in.Dataset=ds.all;
						else
						{
							cout<<"ERROR::INVALID PARAMETERS";
							flag=0;
							cout<<endl<<"For help you can use command \"crunch --help\""<<endl;
							in.flagDataset=0;
							break;
						}
					}
					else if(temp=="-ds")
					{
						if(in.flagDataset==1)
						{
							cout<<"ERROR::INVALID PARAMETERS YOU CAN ONLY USE ALN ARGUMENT ONCE";
							cout<<endl<<"For help you can use command \"crunch --help\"\n";
							flag=0;
							break;
						}
						wd>>temp;
						in.flagDataset=1;
						if(temp=="")
						{
							cout<<"ERROR::INVALID ARGUMENTS";
							cout<<endl<<"For help you can use command \"crunch --help\"\n";
							flag=0;
							in.flagDataset=0;
							break;
						}
						else
						{
							ds.special=temp;
							in.Dataset=ds.special;
						}	
					}
					else if(temp=="-r")
					{
						if(in.flagReplace==1)
						{
							cout<<"ERROR::INVALID PARAMETERS YOU CAN ONLY USE ARGUMENT ONCE";
							flag=0;
							cout<<endl<<"For help you can use command \"crunch --help\"\n";
							break;
						}
						wd>>temp;
						in.flagReplace=1;
						if(temp=="")
						{
							cout<<"ERROR::INVALID ARGUMENTS";
							cout<<endl<<"For help you can use command \"crunch --help\"\n";
							flag=0;					
							in.flagReplace=0;
							break;
						}
						else
						{
							in.insString=temp;
						}
					}
					else
					{
						cout<<"ERROR::INVALID ARGUMENTS";
						flag=0;				
						cout<<endl<<"For help you can use command \"crunch --help\""<<endl;	
					}
				}
			}
			if(in.flagDataset==0)
				in.Dataset=ds.all;
		}	
		
		void phrase()
		{
			ifstream fin;
			string s;
			cmnd.getcmd();
			if(cmd=="crunch")
			{
				fin.open("ins.txt");
				flag=0;	
				while(getline(fin,s))
					cout<<s<<endl;
				fin.close();
				return;
			}
			else if(cmd=="crunch --help")
			{
				fin.open("help.txt");
				flag=0;
				while(getline(fin,s))
					cout<<s<<endl;
				fin.close();
				return;
			}
			parse();
		}
}gp;


class writeFile
{
	public:
		void writeIn()
		{
			if(flag==0)
			{
				
			}
			else
			{
				fout.open("WordList.txt");
				if(in.flagReplace==0)
				{
					for(int i = in.min;i<=in.max;i++)
					{
						wd.makeword(in.Dataset,"",in.Dataset.length(),i);
					}	
				}			
				else
				{
					int cnt=0;
					int relist[in.min];
					for(int i=0,j=0;i<in.insString.length();i++)
					{
						if(in.insString[i]=='@')
						{
							cnt++;
						relist[j++]=i;
						}	
					}
					if(cnt!=in.min||in.min!=in.max)
					{
						cout<<"ERROR :: WHILE USING REPLACE ARGUMENT \"-r\" MIN, MAX AND NO. OF @ IN STRING SHOULD BE SAME"<<endl;
						cout<<"For help you can use command \"crunch --help\"\n";
						return;
					}
					wd.makewordreplace(relist,in.Dataset,"",in.Dataset.length(),cnt);
				}
				fout.close();	
				cout<<"WORDLIST CREATED"<<endl;
			}				
		}
}fi;


main()
{
	while(1)
	{
		ini();
		gp.phrase();
		fi.writeIn();
	}
}
