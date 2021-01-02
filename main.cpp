#include <iostream>
#include <cstdio>
//#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <cstring>
#include <wincon.h>
#include <string>
#include <cstdlib>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
bool high=0;
/*char* itoa(int num,char* str,int radix)
{
    char index[]="0123456789ABCDEF";
    int i=0,j,k;
    if(radix==10&&num<0)
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num;
    do{
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
       }while(unum);
    str[i]='\0';
    if(str[0]=='-')
        k=1;
    else
        k=0;
     
    for(j=k;j<=(i-1)/2;j++)
    {       char temp;
        temp=str[j];
        str[j]=str[i-1+k-j];
        str[i-1+k-j]=temp;
    }
    return str;
}*/

string help[100]= {"Cot Chargame","Help:","",
                   "Player is displayed as character \"+\"",
                   "Press \"W,A,S,D\" to move",
                   "The wall is \"X\" which you can't go through it'",
                   "Don't touch '\"K\" or you loses",
                   "Level passes while touch \"Y\""
                   "\"<\" \"^\" \">\" \"v\" are direction-limiting blocks",
                   "You can only enter from the big ending and exit from the small ending",
                   "Set color mode with button \"C\"",
                   "You can load a map code if you press \"T\" repeatly when startup"," ",
                   "Produced by COT",
                   "Press any key to return game.",
                  };
string map[100];
string name;
void runMap();
void pause()
{
	system("pause>nul");
}
int xL=0,yL=0;
int level=1,x,y,startpoint[2];
void share();
void mapCode()
{
	system("cls");
	system("color fc");
	system("mode con cols=25 lines=8");
	cout<<"Load code"<<endl<<endl<<"Press backspace for 2s, and drag the share.cgmsr to here."<<endl;
	char final[10001];
	cin.getline(final,10001);
	cout<<"Loading...";
	Sleep(500);
	freopen(final,"r",stdin);
	Sleep(1000);
	cin>>xL>>yL>>name;
	string frt;
	getline(cin,frt);
	for(int i=0; i<yL; i++) {
		getline(cin,map[i]);
	}
	fclose(stdin);
	level=0;
	runMap();
}
void set() {
	system("color fc"); 
	HWND hWnd = GetConsoleWindow(); //获得cmd窗口句柄
	RECT rc;
	GetWindowRect(hWnd, &rc); //获得cmd窗口对应矩形

	//改变cmd窗口风格
	SetWindowLongPtr(hWnd,
	                 GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	//因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果
	SetWindowPos(hWnd,
	             NULL,
	             rc.left,
	             rc.top,
	             rc.right - rc.left, rc.bottom - rc.top,
	             NULL);
}
void highlight() {
	if(KEY_DOWN('C')) {
		if(high) {
			system("color fc");
			high=false;
		} else {
			system("color 07");
			high=true;
		}
	}
}
void runMap() {
	int x=100,y=80,count=0,cd=200000,flag=0;
	cout<<"Loading map..."<<endl;
	for(int i=0; i<yL; i++) {
		for(int j=0; j<xL; j++) {
			if(map[i][j]=='S') {
				x=j;
				y=i;
				x++;
				y++;
				cout<<"Found the spawning point!"<<endl;
				break;
			}
			count++;
		}
	}
	x--;
	y--;
	swap(x,y);
	int fX=x;
	int fY=y;
	system("title Chargame Custom");
	char cols[1000];
	char lines[1000];
	/*itoa(xL,cols,10);
	itoa(yL,lines,10);*/
	while(level==0) {
		/*system(strcat("mode con cols=",strcat(cols,strcat(" lines=",lines))));*/
		system("mode con cols=60 lines=60");
		cout<<"Chargame Custom:"<<name;
		/*for(int i=0; i<yL; i++) {
			for(int j=0; j<xL; j++) {
				if(j==y) {
					cout<<"+";
				} else {
					printf("%c",map[i][j]);
				}
			}
		}*/
		for(int i=0; i<yL; i++) {
			cout<<endl;
			for(int j=0; j<xL; j++) {
				if(j==y&&i==x) {
					cout<<"+";
				} else {
					cout<<map[i][j];
				}
			}
		}
		cout<<endl;
		 pause();
		if(KEY_DOWN('A')&&map[x][y-1]!='X'&&map[x][y-1]!='>') {
			y--;
		} else if(KEY_DOWN('W')&&map[x-1][y]!='X'&&map[x-1][y]!='v') {
			x--;
		} else if(KEY_DOWN('D')&&map[x][y+1]!='X'&&map[x][y+1]!='<') {
			y++;
		} else if(KEY_DOWN('S')&&map[x+1][y]!='X'&&map[x+1][y]!='^') {
			x++;
		}
		if(KEY_DOWN('H')) {
			system("mode con cols=50 lines=17");
			system("cls");
			for(int i=0; i<13; i++) {
				cout<<help[i]<<endl;
			}
			system("pause>nul");
		}
		if(KEY_DOWN('C')) {
			if(high) {
				system("color fc");
				high=false;
			} else {
				system("color 0f");
				high=true;
			}
		}
		if(map[x][y]=='Y') {
			cout<<"Great! You have won!"<<endl<<"Press any key to get the sharing file for this map, or exit the game by CTRL+C."<<endl;
			system("pause>nul");
			cout<<"Loading...";
			share();
			return;
		} else if(map[x][y]=='K') {
			cout<<"You failed."<<endl<<"Press any key to retry.";
			system("pause>nul");
			x=fX;
			y=fY;
		}
		Sleep(5);
	}
}
void createMap() {
	system("cls");
	cout<<"Map-making"<<endl<<"First,"<<endl<<"Enter the length of the map ( character count ): ";
	cin>>xL;
	if(xL>90) {
		MessageBox(NULL,"The longest length is 60.","Notice",MB_OK);
		createMap();
		return;
	}
	if(xL<2) {
		MessageBox(NULL,"The shortest length is 2.","Notice",MB_OK);
		createMap();
		return;
	}
	system("cls");
	cout<<"Map-making"<<endl<<"Second,"<<endl<<"Enter the height of the map ( character count ): ";
	cin>>yL;
	if(yL>20) {
		MessageBox(NULL,"The longest height is 20.","Notice",MB_OK);
		createMap();
		return;
	}
	if(yL<2) {
		MessageBox(NULL,"The shortest height is 2.","Notice",MB_OK);
		createMap();
		return;
	}
	system("cls");
	cout<<"Map-making"<<endl<<"Third,"<<endl<<"Enter the name of the map:";
	cin>>name;
	if(name.length()<5) {
		MessageBox(NULL,"The name has to be more than 5 characters.","Notice",MB_OK);
		createMap();
		return;
	}
	if(name.length()>15) {
		MessageBox(NULL,"The name has to be less than 15 characters.","Notice",MB_OK);
		createMap();
		return;
	}
	system("cls");
	system("mode con cols=91 lines=24");
	system("mode con cols=91 lines=24");
	system("mode con cols=91 lines=24");
	cout<<"Please enter the cols of the map one by one.\nPlese round the map with block X and K.\nThe map has to be "<<xL<<" chars wide and heights "<<yL<<" .\n The name of this map is "<<name<<" .\n\n";
	string frt;
	getline(cin,frt);
	for(int i=0; i<yL; i++) {
		getline(cin,map[i]);
	}
	level=0;
	runMap();
}
void share()
{
	freopen("share.cgmsr","w",stdout);
	cout<<xL<<" "<<yL<<" "<<name<<endl;
	for(int i=0;i<yL;i++)
	{
		cout<<map[i]<<endl;
	}
	fclose(stdout);
	cout<<"The share.cgmsr has been saved to the main directory of the Chargame root directory. You can share it with your friends.";
	Sleep(2000);
}
int main() {
	set();

	string map1[100]= {"XXXXXXXXXXXXXXXXXXX",
	                   "XS XXXXXXXXXXXXXXXX",
	                   "XX XXX            X",
	                   "XX     XXXXXXXXXX X",
	                   "XXXXXXXXX         X",
	                   "XXXXXXXXXYXXXXXXXXX"
	                  };
	string map2[100]= {"XXXXXXXXXXXXXXXXXXXXXXXXXX",
	                   "XSXXXXXXXX XXXXXXXXXXXXXXX",
	                   "X                        X",
	                   "XXXX XXX XXXXXXXX XXXXXXXX",
	                   "X      X           XXXXXXX",
	                   "XXXYXXXXXXXXXXXXXXXXXXXXXX"
	                  };
	string map3[100]= {"XXXXXXXXXXXXXXXXXXXXXXXXXX",
	                   "XS                XXXXYXXX",
	                   "XXXX XX XXXXXXXXXXXXXX XXX",
	                   "XXXXK      K           XXX",
	                   "XXXXXXXXXX   XXXXXXXXXXXXX",
	                   "XXXXXXXXXXXXXXXXXXXXXXXXXX"
	                  };
	string map4[100]= {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	                   "XS            X       >           KX",
	                   "XXXXXXXXXXXXX X XXXXXXXXXXXXXXXXXXXX",
	                   "X                                  X",
	                   "X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	                   "X         K           K       K    K",
	                   "X   K           K           K   K  K",
	                   "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXYKX"
	                  };
	string map5[100]= {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	                   "XS        >   XXXXXXXXXXXXXX     YXXXXXXX",
	                   "XXXX XXXXXXX XXXXXXXXXXXXXXX^XXXXXXXXXXXX",
	                   "XXXX   >   X                            X",
	                   "XXXXXXXXXX XXXXXXXXXXXXXXXXXXXXXXXXXXXX X",
	                   "XXXXXXXXXXKXXXXXXXXXXXXXXXXXXXXXXXXXXXXKX"
	                  };
	string map6[100]= {"KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK",
	                   "KS         K         YX                           K",
	                   "XKKKKKKKKK X^KXXKKKKKKX^XXXXXXXXXXXXXXXXXXXXXXXXX^X",
	                   "K          X              K      KK          <    X",
	                   "X KKXXXXXXXXXXXXXXXXXXXXX  vXXXXv   KXXXXX XXXXXX X",
	                   "X                        XX    K XXXXXXXXXXXXXXXX X",
	                   "XXXXXXXXXXXXXXXXXXXXXXXX XX      KXXXXXXXXXXXXXXX X",
	                   "XXXXXXXXXXXXXXXXXXXXXXXX XXXX^XXXXXXXXXXXXXXXXXXX^X",
	                   "XXXXXXXXXXXXXXXXXXXXXXXX                          X",
	                   "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
	                  };
	string map7[100]= {"KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK",
	                   "KSKYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYK",
	                   "X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKKKK^KKKKKKKKKKKKKKKK",
	                   "X > > > > > > > K                 X                        X",
	                   "XvKvXvKvXvKvKvXvKXKXvXXXXXXXXXXXXXXXXKXXvXXXXXXX^XXXXXXXXXXX",
	                   "X X K K K X K K X              X           X               X",
	                   "X X X X   < K > XXXXXXXXXXX^XXXXXXXXX^XXXXXXXXXXXXXXX^XXXXXX",
	                   "X X K XKKXXXK KKX               X             X            X",
	                   "K X K    X     KXXXKXXvXKKKKKK^KKKKKKXXXXXX^XXXKKKKKKKKXKX^K",
	                   "K K XKK^XXXXX  KXXKK    K   K   K   K   K   K   K   K   K  K",
	                   "X <                   K   K   K   K   K   K   K   K   K    X",
	                   "XXXXXXXXKKKKKKKKKKKKKKKKKKKKKKKKKKKXXXXXXKXKXKXKKKKKKKKXXXXK"
	                  };
	x=y=1;
	system("mode con cols=20 lines=4");
	system("title Chargame 2");
	system("color f7");
	cout<<endl<<"  COT GAME STUDIOS            By COT";

	Sleep(100);
	system("color f7");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f8");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f0");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f1");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f9");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color fd");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f5");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color fc");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f5");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color fd");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f9");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f1");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f0");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f8");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	system("color f7");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	Sleep(100);
	if(KEY_DOWN('T')) {
		mapCode();
	}
	system("cls");
	Sleep(1000);
	if(KEY_DOWN('T')) {
		mapCode();
	}
	system("color fc");
	if(KEY_DOWN('T')) {
		mapCode();
	}
	//Dev-mode start
/*
	system("mode con cols=23 lines=4");
	system("title Chargame developing");
	cout<<"Chargame dev\n( jump to ): "<<endl<<"";
	cin>>level;
*/	//Dev-mode end
	system("title Chargame Level 1");
	while(level==1) {
		system("mode con cols=20 lines=8");
		cout<<"Chargame Level 1"<<endl;
		for(int i=0; i<6; i++) {
			if(i!=x) cout<<map1[i];
			else {
				for(int j=0; j<19; j++) {
					if(j==y) {
						cout<<"+";
					} else {
						printf("%c",map1[i][j]);
					}
				}
			}
			cout<<endl;
		}
		system("pause>nul");
		if(KEY_DOWN('A')&&map1[x][y-1]!='X') {
			y--;
		} else if(KEY_DOWN('W')&&map1[x-1][y]!='X') {
			x--;
		} else if(KEY_DOWN('D')&&map1[x][y+1]!='X') {
			y++;
		} else if(KEY_DOWN('S')&&map1[x+1][y]!='X') {
			x++;
		} 
		if(KEY_DOWN('H')) {
			system("mode con cols=50 lines=17");
			system("cls");
			for(int i=0; i<13; i++) {
				cout<<help[i]<<endl;
			}
			system("pause>nul");
		}
		if(KEY_DOWN('C')) {
			if(high) {
				system("color fc");
				high=false;
			} else {
				system("color 0f");
				high=true;
			}
		}	if(KEY_DOWN('T')) {
		mapCode();
	}
		if(map1[x][y]=='Y') {
			cout<<"Congratulations!\nPress any key to go next.";
			system("pause>nul");
			level++;
		}
		Sleep(5);
	}
	x=y=1;

	system("title Chargame Level 2");
	while(level==2) {
		system("mode con cols=27 lines=8");
		cout<<"Chargame Level 2"<<endl;
		for(int i=0; i<6; i++) {
			if(i!=x) cout<<map2[i];
			else {
				for(int j=0; j<26; j++) {
					if(j==y) {
						cout<<"+";
					} else {
						printf("%c",map2[i][j]);
					}
				}
			}
			cout<<endl;
		}
		system("pause>nul");
		if(KEY_DOWN('A')&&map2[x][y-1]!='X') {
			y--;
		} else if(KEY_DOWN('W')&&map2[x-1][y]!='X') {
			x--;
		} else if(KEY_DOWN('D')&&map2[x][y+1]!='X') {
			y++;
		} else if(KEY_DOWN('S')&&map2[x+1][y]!='X') {
			x++;
		}
		if(KEY_DOWN('H')) {
			system("mode con cols=50 lines=17");
			system("cls");
			for(int i=0; i<13; i++) {
				cout<<help[i]<<endl;
			}
			system("pause>nul");
		}	if(KEY_DOWN('T')) {
		mapCode();
	}
		if(KEY_DOWN('C')) {
			if(high) {
				system("color fc");
				high=false;
			} else {
				system("color 0f");
				high=true;
			}
		}
		if(map2[x][y]=='Y') {
			cout<<"Congratulations!\nPress any key to go next.";
			system("pause>nul");
			level++;
		}
		Sleep(5);
	}
	x=y=1;

	system("title Chargame Level 3");
	while(level==3) {
		system("mode con cols=27 lines=8");
		cout<<"Chargame Level 3"<<endl;
		for(int i=0; i<6; i++) {
			if(i!=x) cout<<map3[i];
			else {
				for(int j=0; j<26; j++) {
					if(j==y) {
						cout<<"+";
					} else {
						printf("%c",map3[i][j]);
					}
				}
			}
			cout<<endl;
		}
		system("pause>nul");
		if(KEY_DOWN('A')&&map3[x][y-1]!='X') {
			y--;
		} else if(KEY_DOWN('W')&&map3[x-1][y]!='X') {
			x--;
		} else if(KEY_DOWN('D')&&map3[x][y+1]!='X') {
			y++;
		} else if(KEY_DOWN('S')&&map3[x+1][y]!='X') {
			x++;
		}
		if(KEY_DOWN('H')) {
			system("mode con cols=50 lines=17");
			system("cls");
			for(int i=0; i<13; i++) {
				cout<<help[i]<<endl;
			}
			system("pause>nul");
		}	if(KEY_DOWN('T')) {
		mapCode();
	}
		if(KEY_DOWN('C')) {
			if(high) {
				system("color fc");
				high=false;
			} else {
				system("color 0f");
				high=true;
			}
		}
		if(map3[x][y]=='Y') {
			cout<<"Congratulations!\nPress any key to go next.";
			system("pause>nul");
			level++;
		} else if(map3[x][y]=='K') {
			cout<<"Sorry. Try again.";
			system("pause>nul");
			x=y=1;
		}
		Sleep(5);
	}
	x=y=1;

	system("title Chargame Level 4");
	while(level==4) {
		system("mode con cols=37 lines=10");
		cout<<"Chargame Level 4"<<endl;
		for(int i=0; i<8; i++) {
			if(i!=x) cout<<map4[i];
			else {
				for(int j=0; j<36; j++) {
					if(j==y) {
						cout<<"+";
					} else {
						printf("%c",map4[i][j]);
					}
				}
			}
			cout<<endl;
		}
		system("pause>nul");
		if(KEY_DOWN('A')&&map4[x][y-1]!='X'&&map4[x][y-1]!='>') {
			y--;
		} else if(KEY_DOWN('W')&&map4[x-1][y]!='X'&&map4[x-1][y]!='v') {
			x--;
		} else if(KEY_DOWN('D')&&map4[x][y+1]!='X'&&map4[x][y+1]!='<') {
			y++;
		} else if(KEY_DOWN('S')&&map4[x+1][y]!='X'&&map4[x+1][y]!='^') {
			x++;
		}
		if(KEY_DOWN('H')) {
			system("mode con cols=50 lines=17");
			system("cls");
			for(int i=0; i<13; i++) {
				cout<<help[i]<<endl;
			}
			system("pause>nul");
		}
		if(KEY_DOWN('C')) {
			if(high) {
				system("color fc");
				high=false;
			} else {
				system("color 0f");
				high=true;
			}
		}	if(KEY_DOWN('T')) {
		mapCode();
	}
		if(map4[x][y]=='Y') {
			cout<<"Congratulations!\nPress any key to go next.";
			system("pause>nul");
			level++;
		} else if(map4[x][y]=='K') {
			cout<<"Sorry. Try again.";
			system("pause>nul");
			x=y=1;
		}
		Sleep(5);
	}
	x=y=1;

	system("title Chargame Level 5");
	while(level==5) {
		system("mode con cols=42 lines=8");
		cout<<"Chargame Level 5"<<endl;
		for(int i=0; i<6; i++) {
			if(i!=x) cout<<map5[i];
			else {
				for(int j=0; j<41; j++) {
					if(j==y) {
						cout<<"+";
					} else {
						printf("%c",map5[i][j]);
					}
				}
			}
			cout<<endl;
		}
		system("pause>nul");
		if(KEY_DOWN('A')&&map5[x][y-1]!='X'&&map5[x][y-1]!='>') {
			y--;
		} else if(KEY_DOWN('W')&&map5[x-1][y]!='X') {
			x--;
		} else if(KEY_DOWN('D')&&map5[x][y+1]!='X'&&map5[x][y+1]!='<') {
			y++;
		} else if(KEY_DOWN('S')&&map5[x+1][y]!='X'&&map5[x+1][y]!='^') {
			x++;
		}
		if(KEY_DOWN('H')) {
			system("mode con cols=50 lines=17");
			system("cls");
			for(int i=0; i<13; i++) {
				cout<<help[i]<<endl;
			}
			system("pause>nul");
		}
		if(KEY_DOWN('C')) {
			if(high) {
				system("color fc");
				high=false;
			} else {
				system("color 0f");
				high=true;
			}
		}
		if(map5[x][y]=='Y') {
			cout<<"Congratulations!\nPress any key to go next.";
			system("pause>nul");
			level++;
		} else if(map5[x][y]=='K') {
			cout<<"Sorry. Try again.";
			system("pause>nul");
			x=y=1;
		}
		Sleep(5);
	}
	x=y=1;

	system("title Chargame Level 6");
	while(level==6) {
		system("mode con cols=52 lines=12");
		cout<<"Chargame Level 6"<<endl;
		for(int i=0; i<10; i++) {
			if(i!=x) cout<<map6[i];
			else {
				for(int j=0; j<51; j++) {
					if(j==y) {
						cout<<"+";
					} else {
						printf("%c",map6[i][j]);
					}
				}
			}
			cout<<endl;
		}
		system("pause>nul");
		if(KEY_DOWN('A')&&map6[x][y-1]!='X'&&map6[x][y-1]!='>') {
			y--;
		} else if(KEY_DOWN('W')&&map6[x-1][y]!='X'&&map6[x-1][y]!='v') {
			x--;
		} else if(KEY_DOWN('D')&&map6[x][y+1]!='X'&&map6[x][y+1]!='<') {
			y++;
		} else if(KEY_DOWN('S')&&map6[x+1][y]!='X'&&map6[x+1][y]!='^') {
			x++;
		}
		if(KEY_DOWN('H')) {
			system("mode con cols=50 lines=17");
			system("cls");
			for(int i=0; i<13; i++) {
				cout<<help[i]<<endl;
			}
			system("pause>nul");
		}
		if(KEY_DOWN('C')) {
			if(high) {
				system("color fc");
				high=false;
			} else {
				system("color 0f");
				high=true;
			}
		}
		if(map6[x][y]=='Y') {
			cout<<"Congratulations!\nPress any key to go next.";
			system("pause>nul");
			level++;
		} else if(map6[x][y]=='K') {
			cout<<"Sorry. Try again.";
			system("pause>nul");
			x=y=1;
		}
		Sleep(5);
	}
	x=y=1;

	system("title Chargame Level 7");
	while(level==7) {
		system("mode con cols=61 lines=14");
		cout<<"Chargame Level 7"<<endl;
		for(int i=0; i<12; i++) {
			if(i!=x) cout<<map7[i];
			else {
				for(int j=0; j<60; j++) {
					if(j==y) {
						cout<<"+";
					} else {
						printf("%c",map7[i][j]);
					}
				}
			}
			cout<<endl;
		}
		system("pause>nul");
		if(KEY_DOWN('A')&&map7[x][y-1]!='X'&&map7[x][y-1]!='>') {
			y--;
		} else if(KEY_DOWN('W')&&map7[x-1][y]!='X'&&map7[x-1][y]!='v') {
			x--;
		} else if(KEY_DOWN('D')&&map7[x][y+1]!='X'&&map7[x][y+1]!='<') {
			y++;
		} else if(KEY_DOWN('S')&&map7[x+1][y]!='X'&&map7[x+1][y]!='^') {
			x++;
		}
		if(KEY_DOWN('H')) {
			system("mode con cols=50 lines=17");
			system("cls");
			for(int i=0; i<13; i++) {
				cout<<help[i]<<endl;
			}
			system("pause>nul");
		}
		if(KEY_DOWN('C')) {
			if(high) {
				system("color fc");
				high=false;
			} else {
				system("color 0f");
				high=true;
			}
		}
		if(map7[x][y]=='Y') {
			cout<<"Congratulations!\nPress any key to go next.";
			system("pause>nul");
			level++;
		} else if(map7[x][y]=='K') {
			cout<<"Sorry. Try again.";
			system("pause>nul");
			x=y=1;
		}
		Sleep(5);
	}
	//win!
	system("title Chargame 2");
	system("mode con lines=5 cols=3");
	Sleep(300);
	system("mode con lines=5 cols=33");
	Sleep(300);
	system("cls");
	cout<<"                         "<<endl<<"                         "<<endl<<"                         "<<endl<<"             U           ";
	Sleep(500);
	system("cls");
	cout<<"                         "<<endl<<"                         "<<endl<<"             |           "<<endl<<"             U           ";
	Sleep(500);
	system("cls");
	cout<<"                         "<<endl<<"             O           "<<endl<<"             |           "<<endl<<"             U           ";
	Sleep(500);
	system("cls");
	cout<<"             A           "<<endl<<"            -O-          "<<endl<<"             |           "<<endl<<"             U           ";
	Sleep(500);
	system("cls");
	cout<<"           +-A-+         "<<endl<<"           -=O=-         "<<endl<<"            -|-          "<<endl<<"             U           ";
	Sleep(500);
	system("cls");
	cout<<"           0=A=0         "<<endl<<"           /=O=\\         "<<endl<<"           =-|-=         "<<endl<<"             UL          ";
	Sleep(500);
	system("cls");
	cout<<"           0   0         "<<endl<<"           /   \\         "<<endl<<"           =   =         "<<endl<<"              L          ";
	Sleep(500);
	system("cls");
	cout<<"                         "<<endl<<"           I   I         "<<endl<<"                         "<<endl<<"                         ";
	Sleep(500);
	system("cls");
	cout<<"CONGRATULATIONS!"<<endl<<"You've passed all the levels"<<endl<<"Please look forward to Chargame 3"<<endl<<"Thanks for playing!";
	system("pause>nul");
	system("cls");
	//createMap();
	return 0;
}
