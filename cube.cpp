#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>
#include <time.h>
using namespace std;

#define red "\x1b[41m  \x1b[0m"
#define green "\x1b[42m  \x1b[0m"
#define yellow "\x1b[43m  \x1b[0m"
#define blue "\x1b[44m  \x1b[0m"
#define orange "\x1b[45m  \x1b[0m"
#define white "\x1b[47m  \x1b[0m"

class stacks
{
	public:
	struct node
	{
		string str;
		struct node *next;
		}*top;
		
	stacks()
	{
		top=NULL;
		}
	
	void add(string ch)
	{
		struct node *temp;
		temp=new node;
		
		temp->str=ch;
		temp->next=top;
		top=temp;
		}
		
	string pop()
	{
		if(top==NULL)
		return "z";
		struct node *temp=top;
		top=top->next;
		
		string ch=temp->str;
		delete temp;
		return ch;
		}
	};

class cube
{
	public:
	class stacks s;
	
	struct face
	{
		string colour[3][3];
		} f[6];
		
	cube()
	{
		for(int i=0;i<6;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					switch(i)
					{
						case 0: f[0].colour[j][k]=white; break;
						
						case 1: f[1].colour[j][k]=blue; break;
						
						case 2: f[2].colour[j][k]=orange; break;
						
						case 3: f[3].colour[j][k]=green; break;
						
						case 4: f[4].colour[j][k]=yellow; break;
						
						case 5: f[5].colour[j][k]=red; break;
						
						}
						
		}//end of constructor
		
	void top(int m, int n=1)//m is row no. n is direction
	{
		string temp[3];
		
		for(int i=0;i<3;i++)
		temp[i]=f[0].colour[i][m];
		
		for(int i=0;i<3;i++)
			f[0].colour[i][m]=f[5].colour[i][m];
		for(int i=0;i<3;i++)
			f[5].colour[i][m]=f[4].colour[abs(i-2)][abs(m-2)];
		for(int i=0;i<3;i++)
			f[4].colour[abs(i-2)][abs(m-2)]=f[2].colour[i][m];
		for(int i=0;i<3;i++)
			f[2].colour[i][m]=temp[i];
			
		if(!n)
		for(int i=0;i<2;i++)
			top(m);
		
		}//end of top move
		
	void side(int m, int n=1)//m is row no. n is direction
	{
		string temp[3];
		
		for(int i=0;i<3;i++)
		temp[i]=f[0].colour[m][i];
		
		for(int i=0;i<3;i++)
		{
			f[0].colour[m][i]=f[1].colour[m][i];
			f[1].colour[m][i]=f[4].colour[m][i];
			f[4].colour[m][i]=f[3].colour[m][i];
			f[3].colour[m][i]=temp[i];
			}
			
		if(!n)
		for(int i=0;i<2;i++)
			side(m);
		
		}//end of top move
		
	void transpose(int m, int n=1)
	{//m is face no. n is dir
		string temp[3];
		
		for(int i=0;i<3;i++)
			temp[i]=f[m].colour[0][i];
		
		for(int i=0;i<3;i++)
			f[m].colour[0][i]=f[m].colour[abs(i-2)][0];
		for(int i=0;i<3;i++)
			f[m].colour[i][0]=f[m].colour[2][i];
		for(int i=0;i<3;i++)
			f[m].colour[2][i]=f[m].colour[abs(i-2)][2];
		for(int i=0;i<3;i++)
			f[m].colour[i][2]=temp[i];
		
		if(!n)
		for(int i=0;i<2;i++)
		transpose(m);
		
		}//end of transpose
		
	void move(string ch)
	{
		if(ch=="ma")
		{
			side(1,1);
			s.add("md");
			}
		
		if(ch=="md")
		{
			side(1,0);
			s.add("ma");
			}
		
		if(ch=="mw")
		{
			top(1,1);
			s.add("ms");
			}
		
		if(ch=="ms")
		{
			top(1,0);
			s.add("mw");
			}
			
		if(ch=="aw")
		{
			top(0,1);
			transpose(3,0);
			s.add("as");
			}
		
		if(ch=="dw")
		{
			top(2,1);
			transpose(1,1);
			s.add("ds");
			}
		
		if(ch=="as")
		{
			top(0,0);
			transpose(3,1);
			s.add("aw");
			}
		
		if(ch=="ds")
		{
			top(2,0);
			transpose(1,0);
			s.add("dw");
			}
		
		if(ch=="wa")
		{
			side(0,1);
			transpose(2,1);
			s.add("wd");
			}
		
		if(ch=="sa")
		{
			side(2,1);
			transpose(5,0);
			s.add("sd");
			}
		
		if(ch=="wd")
		{
			side(0,0);
			transpose(2,0);
			s.add("wa");
			}
		
		if(ch=="sd")
		{
			side(2,0);
			transpose(5,1);
			s.add("sa");
			}
			
		if(ch=="A")
		{
			side(0,1);
			transpose(2,1);
			side(2,1);
			transpose(5,0);
			side(1,1);
			s.add("D");
			
			}
			
		if(ch=="D")
		{
			side(0,0);
			transpose(2,0);
			side(2,0);
			transpose(5,1);
			side(1,0);
			s.add("A");
			
			}
			
		if(ch=="W")
		{
			top(0,1);
			transpose(3,0);
			top(2,1);
			transpose(1,1);
			top(1,1);
			s.add("S");
			
			}
			
		if(ch=="S")
		{
			top(0,0);
			transpose(3,1);
			top(2,0);
			transpose(1,0);
			top(1,0);
			s.add("W");
			
			}

		if(ch=="z")
		cout<<"";
		
			
		if(ch=="aa"||ch=="dd")
		{
			int j=(ch=="aa")? 1:3;
			for(int i=0;i<j;i++)
			{
				side(0,1);
				transpose(2,1);
				side(2,1);
				transpose(5,0);
				side(1,1);//for turning
			
				top(0,1);
				transpose(3,0);//for face turning
			
				side(0,0);
				transpose(2,0);
				side(2,0);
				transpose(5,1);
				side(1,0);//back to original side
				}
			if(j==1)
				s.add("dd");
				
			else
			s.add("aa");
			}
			
		if(ch=="ra" || ch=="rd")
		{
			
			int j=(ch=="ra")? 1:3;
			for(int i=0;i<j;i++)
			{
				side(0,1);
				transpose(2,1);
				side(2,1);
				transpose(5,0);
				side(1,1);
			
				top(0,1);
				transpose(3,0);
				top(2,1);
				transpose(1,1);
				top(1,1);
			
				side(0,0);
				transpose(2,0);
				side(2,0);
				transpose(5,1);
				side(1,0);
				
				}
			if(j==1)
				s.add("rd");
				
			else
			s.add("ra");
			}
		
		}//end of move function
		
	void display()
	{
		for(int j=0;j<3;j++)
		{ 
			cout<<"       ";
				for(int k=0;k<3;k++)
				cout<<f[2].colour[j][k];
			
			if(j==1)
			cout<<"\t\t  back side";
				cout<<"\n";
				}//top part
		cout<<endl;
				
		for(int k=0;k<3;k++)
		{
			for(int j=0;j<3;j++)
				cout<<f[3].colour[k][j];
			cout<<" ";
			
			for(int j=0;j<3;j++)
				cout<<f[0].colour[k][j];
			cout<<" ";
			
			for(int j=0;j<3;j++)
				cout<<f[1].colour[k][j];
			cout<<"        ";
			
			for(int j=0;j<3;j++)
				cout<<f[4].colour[k][j];
				
			cout<<"\n";
			}	//middle part
		cout<<endl;
			
		for(int j=0;j<3;j++)
		{ 
			cout<<"       ";
				for(int k=0;k<3;k++)
				cout<<f[5].colour[j][k];
				cout<<"\n";
				}//bottom part
			
		}//end of display
		
	void savegame()
	{
		fstream file("save_cube.dat",ios::out|ios::trunc|ios::binary);
		
		for(int i=0;i<6;i++)
		for(int j=0;j<3;j++)
		for(int k=0;k<3;k++)
		file.write((char*)&f[i].colour[j][k],12);
		
		file.close();

		}
		
	void load()
	{
		fstream file("save_cube.dat",ios::in|ios::binary);
		
		for(int i=0;i<6;i++)
		for(int j=0;j<3;j++)
		for(int k=0;k<3;k++)
		file.read((char*)&f[i].colour[j][k],12);

		file.close();
		}
	
	};

int main()
{	
	srand(time(0));
	int l,m,n;
	
	class cube c;
	string ch;
		
	for(int i=0;i<50;i++)
		{
			l=rand()%70+1;
			m=rand()%50+1;
			n=(l+m)%10+1;
			
			switch(n)
			{
				case 1:
					c.move("aw");
				break;
				
				case 2:
					c.move("as");
				break;
				
				case 3:
					c.move("dw");
				break;
				
				case 4:
					c.move("ds");
				break;
				
				case 5:
					c.move("wa");
				break;
				
				case 6:
					c.move("wd");
				break;
				
				case 7:
					c.move("sa");
				break;
				
				case 8:
					c.move("sd");
				break;
				
				case 9:
					c.move("aa");
				break;
				
				case 10:
					c.move("dd");
				break;
				
				}
			ch=c.s.pop();
		}
		
	cout<<"want to load the previous save? 1/0 ";
	cin>>l;
	system("cls");

	if(l==0)
	{
		cout<<"welcome to the game\nThe controls are simple\n\nYou will be using WASD keys to control\nWant to select left side? use \"a\" and to move up put \"w\" after that\nI.e aw (other examples sd for moving bottom row to right and wd for moving top row to right)\nIf you want to move the middle row or column just start with letter \"m\" and follow it with the direction you want to move. \neg. ma will ove middle row to left while mw will move middle column on top \nTo change the face put capital keys like A for Moving face to left\nTo rotate the face to left or right press\"aa\" or \"dd\"\nand to rotate the top colour while keeping the face same use \"ra\" or \"rd\"\n\ntry to enjoy the game >:)\npress enter to continue";
		cin.ignore();
		cin.ignore();
	}
		system("cls");

	if(l)
	c.load();
			
	while(1)
	{
		c.display();
		cin>>ch;
		
		if(ch!="b" && ch!="e")
		c.move(ch);
		
		if(ch=="b")
		{
		c.move(c.s.pop());
		ch=c.s.pop();
			}
			
		if(ch=="e")
			break;
		
		system("cls");
	}
	
	c.savegame();
	}