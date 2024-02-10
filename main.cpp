//https://patorjk.com/software/taag/#p=display&f=Banner3&t=GAME%20MENU +
//zombie moving algorithm +
//spawn camp problem +
//vaccines dissaparing +
//game lore at begginig -
//zombies eating things IMPORTANT +
//zombie eating eachother ?
//please enter right char at end not beggining +
//add color and design +
//zombie attacks is not instant
//player eating zombies -
//save and load +
//pdf file with explanation +

#include <iostream>
#include <windows.h>
//#include <stdio.h> 
#include <conio.h>
#include <ctime>
#include <fstream>
using namespace std;

string RESET = "\033[0m";
string RED ="\e[31m";
string GRN ="\e[32m";
string YEL ="\e[33m";
string BLU ="\e[34m";
string MAG ="\e[35m";
string CYN ="\e[36m";
string BYEL= "\e[33;1m";

int sound=0;
int level, vaccine, credit, rounds, health, inAmmo, outAmmo, kill;
int V;
int range, capacity, CapacityCredit, RangeCredit, HealthCredit;
char space[15][15];
int Px, Py;
bool killed;
bool Input=true;
int Zx[10]={15}, Zy[10]={15};
int Vx[10]={15}, Vy[10]={15};
int Ax[5]={15}, Ay[5]={15};

void ClearScr();
void sleep_sec(float seconds);
void MainMenu();
void GameMenu();
void Round();
void Movement();
void NewGame();
void NewLevel();
void Stats();
void Board();
void Settings();
void Settings1();
void Credits();
void Credits1();
void Help();
void Help1();
void Exit();
void Exit1();
void StartNew();
void Lose();
void Restart();
void UpgradeMenu();
void KillMsg();
void Zombie();
//void Lore();
void Save();
void Load();
void Death();

int main(){
	PlaySound(TEXT("music.wav"),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);
	MainMenu();
}       

void ClearScr(){
	#if defined _WIN32
	system("cls");
	#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	#elif defined (__APPLE__)
	system("clear");
	#endif
}

void sleep_sec(float seconds){
	clock_t startClock = clock();
	float secondsAhead = seconds * CLOCKS_PER_SEC;
	while (clock() < startClock + secondsAhead);
	return;
}

void MainMenu(){
	ClearScr();
	cout<<RED;
	cout<<" ######   #######  ##     ## #### ########       #######    #####    #######    #####  "<<endl;
	cout<<"##    ## ##     ## ##     ##  ##  ##     ##     ##     ##  ##   ##  ##     ##  ##   ## "<<endl;
	cout<<"##       ##     ## ##     ##  ##  ##     ##            ## ##     ##        ## ##     ##"<<endl;
	cout<<"##       ##     ## ##     ##  ##  ##     ##      #######  ##     ##  #######  ##     ##"<<endl;
	cout<<"##       ##     ##  ##   ##   ##  ##     ##     ##        ##     ##        ## ##     ##"<<endl;
	cout<<"##    ## ##     ##   ## ##    ##  ##     ##     ##         ##   ##  ##     ##  ##   ## "<<endl;
	cout<<" ######   #######      #     #### ########       #######    #####    #######    #####  "<<RESET<<endl;
	cout<<"Welcome to Covid 2030 game!"<<endl<<endl;
	cout<<GRN<<"Dare to begin?"<<RESET<<endl;
	cout<<"1-New Game"<<endl;
	cout<<"2-Load last save"<<endl;
	cout<<"3-Settings"<<endl;
	cout<<"4-Credits"<<endl;
	cout<<"5-Help"<<endl;
	cout<<"6-Exit"<<endl;
	if (Input==false){
		cout<<endl<<YEL<<"Please just enter the numbers in the menu:"<<RESET<<endl;
		Input=true;
	}
	char Input1 = getch();
	if (Input1=='1'){
		NewGame();
	}
	else if (Input1=='2'){
		Load();
	}
	else if (Input1=='3'){
		Settings();
	}
	else if (Input1=='4'){
		Credits();
	}
	else if (Input1=='5'){
		Help();
	}
	else if (Input1=='6'){
		Exit();
	}
	else {
		ClearScr();
		Input=false;
		MainMenu();
	}
}

void Round(){
	ClearScr();
	Stats();
	Board();
	rounds++;
	Movement();
	if (rounds%2==0){
		Zombie();
	}
	Death();
	Round();
}

void Movement(){
	space[Py][Px]=' ';
	if(space[14][14]==' '){
		space[14][14]='D';
	}
	
	char move = getch();
	if (move=='w'||move=='W'){
		if (Py>0){
			Py--;
		}
	}
	else if (move=='s'||move=='S'){
		if (Py<14){
			Py++;	
		}
	}
	else if (move=='a'||move=='A'){
		if (Px>0){
			Px--;
		}
	}
	else if (move=='d'||move=='D'){
		if (Px<14){
			Px++;
		}
	}
	else if (move=='t'||move=='T'){
		if (inAmmo==0){
			cout<<RED<<"No charged ammo!"<<RESET;
		}
		else {
			for (int i=1; i<=range; i++){
				if (space[Py-i][Px]=='Z'){
					space[Py-i][Px]=' ';
					kill++;
					killed=true;
					for (int j=0; j<level; j++){
						if (Zx[j]==Px && Zy[j]==Py-i){
							Zx[j]=15;
							Zy[j]=15;
						}
					}
					KillMsg();
					cout<<GRN<<level+1<<" credit gained!"<<RESET<<endl;
					credit+=level+1;
					break;
				}
			}
			if (killed==false){
				cout<<BLU<<"Zombie is not in range! come closer."<<RESET<<endl;
			}
			inAmmo--;
			killed=false;
			sleep_sec(2);
		}
	}
	else if (move=='f'||move=='F'){
		if (inAmmo==0){
			cout<<RED<<"No charged ammo!"<<RESET;
		}
		else {
			for (int i=1; i<=range; i++){
				if (space[Py][Px-i]=='Z'){
					space[Py][Px-i]=' ';
					kill++;
					killed=true;
					for (int j=0; j<level; j++){
						if (Zx[j]==Px-i && Zy[j]==Py){
							Zx[j]=15;
							Zy[j]=15;
						}
					}
					KillMsg();
					cout<<GRN<<level+1<<" credit gained!"<<RESET<<endl;
					credit+=level+1;
					break;
				}
			}
			if (killed==false){
				cout<<BLU<<"Zombie is not in range! come closer."<<RESET<<endl;
			}
			inAmmo--;
			killed=false;
			sleep_sec(2);
		}
	}
	else if (move=='g'||move=='G'){
		if (inAmmo==0){
			cout<<RED<<"No charged ammo!"<<RESET;
		}
		else {
			for (int i=1; i<=range; i++){
				if (space[Py+i][Px]=='Z'){
					space[Py+i][Px]=' ';
					kill++;
					killed=true;
					for (int j=0; j<level; j++){
						if (Zx[j]==Px && Zy[j]==Py+i){
							Zx[j]=15;
							Zy[j]=15;
						}
					}
					KillMsg();
					cout<<GRN<<level+1<<" credit gained!"<<RESET<<endl;
					credit+=level+1;
					break;
				}
			}
			if (killed==false){
				cout<<BLU<<"Zombie is not in range! come closer."<<RESET<<endl;
			}
			inAmmo--;
			killed=false;
			sleep_sec(2);
		}
	}
	else if (move=='h'||move=='H'){
		if (inAmmo==0){
			cout<<RED<<"No charged ammo!"<<RESET;
		}
		else {
			for (int i=1; i<=range; i++){
				if (space[Py][Px+i]=='Z'){
					space[Py][Px+i]=' ';
					kill++;
					killed=true;
					for (int j=0; j<level; j++){
						if (Zx[j]==Px+i && Zy[j]==Py){
							Zx[j]=15;
							Zy[j]=15;
						}
					}
					KillMsg();
					cout<<GRN<<level+1<<" credit gained!"<<RESET<<endl;
					credit+=level+1;
					break;
				}
			}
			if (killed==false){
				cout<<BLU<<"Zombie is not in range! come closer."<<RESET<<endl;
			}
			inAmmo--;
			killed=false;
			sleep_sec(2);
		}
	}
	else if (move=='r'||move=='R'){
		if (outAmmo==0){
			cout<<RED<<"No Ammo!"<<RESET;
		}
		else if (capacity==inAmmo){
			cout<<BLU<<"The gun is already Charged."<<RESET;
		}
		else {
			while (capacity>inAmmo&&outAmmo>0){
				outAmmo--;
				inAmmo++;
			}
			cout<<GRN<<"Reloaded!"<<RESET;
		}
		sleep_sec(2);
	}
	else if (move=='e'||move=='E'){
		space[Py][Px]='P';
		Exit1();
	}
	else if (move=='u'||move=='U'){
		space[Py][Px]='P';
		ClearScr();
		UpgradeMenu();
	}
	else if (move=='m'||move=='M'){
		space[Py][Px]='P';
		ClearScr();
		GameMenu();
	}
	else if (move=='c'||move=='C'){
		space[Py][Px]='P';
		Save();
		cout<<YEL<<"Your game has been saved."<<RESET<<endl;
		sleep_sec(2);
	}
	else {
		cout<<YEL<<"Please enter the right character:"<<RESET;
		sleep_sec(2);
	}
	
	if (space[Py][Px]=='D'){
		if(V==0){
		cout<<GRN<<"You Won! You have reached level "<<level+1<<"."<<RESET;
		sleep_sec(2);
		NewLevel();
		}
		else{
		cout<<MAG<<"First get all the vaccines."<<RESET;
		sleep_sec(2);
		}
	}
	if (space[Py][Px]=='V'){
		cout<<GRN<<"Vaccine collected!"<<endl;
		cout<<level+1<<" credit gained!"<<RESET;
		V--;
		vaccine++;
		credit+=level+1;
		for (int i=0; i<level; i++){
			if (Vy[i]==Py && Vx[i]==Px){
				Vy[i]=15;
				Vx[i]=15;
			}
		}
		sleep_sec(2);
	}
	if (space[Py][Px]=='A'){
		cout<<GRN<<"Ammo collected!"<<RESET<<endl;
		outAmmo++;
		for (int i=0; i<level/2; i++){
			if (Ay[i]==Py && Ax[i]==Px){
				Ay[i]=15;
				Ax[i]=15;
			}
		}
		sleep_sec(2);
	}
	space[Py][Px]='P';
}

void NewGame(){
	level=0;
	vaccine=0;
	credit=0;
	rounds=0; 
	health=3; 
	inAmmo=3; 
	outAmmo=0; 
	kill=0;
	Px=0;
	Py=0;
	V=0;
	range=5;
	capacity=3;
	Input=true;
	Zx[10]={15};
	Zy[10]={15};
	Vx[10]={15};
	Vy[10]={15};
	Ax[5]={15};
	Ay[5]={15};
	for(int Row=0; Row<15; Row++){
		for (int Column=0; Column<15; Column++){
			space[Row][Column]=' ';
		}
	}
	NewLevel();
}

void NewLevel(){
	if (level<10){
		level++;
		V=level;
		rounds=0;
		Px=0;
		Py=0;
		for(int Row=0; Row<15; Row++){
			for (int Column=0; Column<15; Column++){
				space[Row][Column]=' ';
			}
		}
		srand(time(0));
		for(int i=0 ; i<level/2 ; i++){
			int tempy = rand() % 14;
			int tempx = rand() % 14;
			if (space[tempy][tempx]==' '){
				space[tempy][tempx]='A';
				Ay[i]=tempy;
				Ax[i]=tempx;
			}
			else {
				i--;
			}
		}
		for(int i=0 ; i<level; i++){
			int tempy = rand() % 14;
			int tempx = rand() % 14;
			if (space[tempy][tempx]==' '){
				space[tempy][tempx]='V';
				Vy[i]=tempy;
				Vx[i]=tempx;
			}
			else {
				i--;
			}
		}
		for (int i=0 ; i<level; i++){
			int tempy = rand() % 14;
			int tempx = rand() % 14;
			if (tempy==0&&tempx==1){
				i--;
			}
			else if (tempy==1&&tempx==0){
				i--;
			}
			else if (tempy==1&&tempx==1){
				i--;
			}
			else if (space[tempy][tempx]==' '){
				space[tempy][tempx]='Z';
				Zy[i]=tempy;
				Zx[i]=tempx;
			}
			else {
				i--;
			}
		}
		
		space[14][14]='D';
		space[0][0]='P';
		Round();
	}
	else{
		ClearScr();
		Credits1();
	}
}

void Board(){
	cout<<"-----------------"<<endl;
	for(int Row=0; Row<15; Row++){
		cout<<'|';
		for (int Column=0; Column<15; Column++){
			for (int i=0; i<level; i++){
				if (Vy[i]==Row && Vx[i]==Column && space[Row][Column]==' '){
					space[Row][Column]='V';
				}
			}
			for (int i=0; i<level/2; i++){
				if (Ay[i]==Row && Ax[i]==Column && space[Row][Column]==' '){
					space[Row][Column]='A';
				}
			}
			if (space[Row][Column]=='P'){
				cout<<GRN;
			}
			else if (space[Row][Column]=='A'){
				cout<<BLU;
			}
			else if (space[Row][Column]=='Z'){
				cout<<RED;
			}
			else if (space[Row][Column]=='V'){
				cout<<YEL;
			}
			else if (space[Row][Column]=='D'){
				cout<<MAG;
			}
			cout<<space[Row][Column]<<RESET;
		}
		cout<<'|'<<endl;
	}
	cout<<"-----------------"<<endl;
}

void Stats(){
	cout<<"Level: "<<level<<"  Round: "<<rounds<<"  Vaccine: "<<vaccine;
	cout<<"  Health: [";
	int j=health;
	for (; j>0; j--){
		cout<<'|';
	}
	cout<<']'<<endl;
	cout<<"Credit: "<<credit<<"  Ammo: "<<capacity<<'/'<<inAmmo<<'/'<<outAmmo<<"  Shotgun range: "<<range<<"  Kill: "<<kill<<endl;
}

void Settings(){
	ClearScr();
	cout<<YEL;
	cout<<"   ##     ######  ######## ######## ######## #### ##    ##  ######    ######     ##    "<<endl;
	cout<<"  ##     ##    ## ##          ##       ##     ##  ###   ## ##    ##  ##    ##     ##   "<<endl;
	cout<<" ##      ##       ##          ##       ##     ##  ####  ## ##        ##            ##  "<<endl;
	cout<<"##        ######  ######      ##       ##     ##  ## ## ## ##   ####  ######        ## "<<endl;
	cout<<" ##            ## ##          ##       ##     ##  ##  #### ##    ##        ##      ##  "<<endl;
	cout<<"  ##     ##    ## ##          ##       ##     ##  ##   ### ##    ##  ##    ##     ##   "<<endl;
	cout<<"   ##     ######  ########    ##       ##    #### ##    ##  ######    ######     ##    "<<RESET<<endl<<endl;
	cout << "Final level is: 10"<<endl<<endl;
	if (sound%2==0){
		cout << "Sound is not mute!"<<endl;
		cout << "Do you want to mute the sound? (y,n)"<<endl;
		if (Input==false){
			cout<<endl<<YEL<<"Please enter the right character:"<<RESET<<endl;
			Input=true;
		}
		char a = getch();
		if (a=='y'||a=='Y'){
			sound++;
			PlaySound(0,0,0);
			MainMenu();	
		}
		else if (a=='n'||a=='N'){
			MainMenu();
		}
		else {
			Input=false;
			Settings();
		}
	}
	else {
		cout <<YEL<< "Sound is mute!"<<endl;
		cout << "Do you want to unmute the sound? (y,n)"<<RESET<<endl;
		if (Input==false){
			cout<<endl<<YEL<<"Please enter the right character:"<<RESET<<endl;
			Input=true;
		}
		char a = getch();
		if (a=='y'||a=='Y'){
			sound++;
			PlaySound(TEXT("music.wav"),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);
			MainMenu();
		}
		else if (a=='n'||a=='N'){
			MainMenu();
		}
		else {
			Input=false;
			Settings();
		}
	}	
}

void Settings1(){
	ClearScr();
	cout<<YEL;
	cout<<"   ##     ######  ######## ######## ######## #### ##    ##  ######    ######     ##    "<<endl;
	cout<<"  ##     ##    ## ##          ##       ##     ##  ###   ## ##    ##  ##    ##     ##   "<<endl;
	cout<<" ##      ##       ##          ##       ##     ##  ####  ## ##        ##            ##  "<<endl;
	cout<<"##        ######  ######      ##       ##     ##  ## ## ## ##   ####  ######        ## "<<endl;
	cout<<" ##            ## ##          ##       ##     ##  ##  #### ##    ##        ##      ##  "<<endl;
	cout<<"  ##     ##    ## ##          ##       ##     ##  ##   ### ##    ##  ##    ##     ##   "<<endl;
	cout<<"   ##     ######  ########    ##       ##    #### ##    ##  ######    ######     ##    "<<RESET<<endl<<endl;
	cout << "Final level is: 10"<<endl<<endl;
	if (sound%2==0){
		cout << "Sound is not mute!"<<endl;
		cout << "Do you want to mute the sound? (y,n)"<<endl;
		if (Input==false){
			cout<<endl<<YEL<<"Please enter the right character:"<<RESET<<endl;
			Input=true;
		}
		char a = getch();
		if (a=='y'||a=='Y'){
			sound++;
			PlaySound(0,0,0);
			Round();	
		}
		else if (a=='n'||a=='N'){
			Round();
		}
		else {
			Input=false;
			Settings1();
		}
	}
	else {
		cout <<YEL<< "Sound is mute!"<<endl;
		cout << "Do you want to unmute the sound? (y,n)"<<RESET<<endl;
		if (Input==false){
			cout<<endl<<YEL<<"Please enter the right character:"<<RESET<<endl;
			Input=true;
		}
		char a = getch();
		if (a=='y'||a=='Y'){
			sound++;
			PlaySound(TEXT("music.wav"),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);
			Round();
		}
		else if (a=='n'||a=='N'){
			Round();
		}
		else {
			Input=false;
			Settings1();
		}
	}	
}

void Credits(){
	int i;
	for (i=7; i>0; i--){
	ClearScr();	
	cout<<MAG;
	cout<<"   ##     ######  ########  ######## ########  #### ########  ######     ##    "<<endl;
	cout<<"  ##     ##    ## ##     ## ##       ##     ##  ##     ##    ##    ##     ##   "<<endl;
	cout<<" ##      ##       ##     ## ##       ##     ##  ##     ##    ##            ##  "<<endl;
	cout<<"##       ##       ########  ######   ##     ##  ##     ##     ######        ## "<<endl;
	cout<<" ##      ##       ##   ##   ##       ##     ##  ##     ##          ##      ##  "<<endl;
	cout<<"  ##     ##    ## ##    ##  ##       ##     ##  ##     ##    ##    ##     ##   "<<endl;
	cout<<"   ##     ######  ##     ## ######## ########  ####    ##     ######     ##    "<<RESET<<endl<<endl;
	cout <<CYN<<"Created by: Arian SaeedKondori and Erfan Ghasemian"<<endl<<endl;
	cout << "Class: Programming Basics"<<endl<<endl;
	cout << "Teacher: Ms.Davoodabadi"<<endl<<endl;
	cout << "Iran University of Science and Technology"<<endl<<endl;
	cout << "*Winter of 1402*"<<RESET<<endl<<endl<<endl;
	cout << "Returning to Main Menu in "<< i;
	if(i==1){
		cout<<" Second.";
	}
	else {
		cout<<" Seconds.";
	}
	/*
	cout<<endl<<endl<<"Press any key to quick return.";
	char j = getch();
	if (j != '\0'){
		MainMenu();
	}
	*/
	sleep_sec(1);
	}
	MainMenu();
}

void Credits1(){
	int i;
	for (i=10; i>0; i--){
	ClearScr();
	cout<<GRN;
	cout<<"##    ##  #######  ##     ##       ##      ## #### ##    ##    #### "<<endl;
	cout<<" ##  ##  ##     ## ##     ##       ##  ##  ##  ##  ###   ##    #### "<<endl;
	cout<<"  ####   ##     ## ##     ##       ##  ##  ##  ##  ####  ##    #### "<<endl;
	cout<<"   ##    ##     ## ##     ##       ##  ##  ##  ##  ## ## ##     ##  "<<endl;
	cout<<"   ##    ##     ## ##     ##       ##  ##  ##  ##  ##  ####         "<<endl;
	cout<<"   ##    ##     ## ##     ##       ##  ##  ##  ##  ##   ###    #### "<<endl;
	cout<<"   ##     #######   #######         ###  ###  #### ##    ##    #### "<<RESET<<endl;
	cout<<"Congratulations! You have successfully collected all the vaccines!"<<endl;
	cout<<"Now it is time to return to the Earth."<<endl;
	cout<<"Good Bye!"<<endl<<endl<<endl;
	cout <<CYN<<"Created by: Arian SaeedKondori and Erfan Ghasemian"<<endl<<endl;
	cout << "Class: Programming Basics"<<endl<<endl;
	cout << "Teacher: Ms.Davoodabadi"<<endl<<endl;
	cout << "Iran University of Science and Technology"<<endl<<endl;
	cout << "*Winter of 1402*"<<RESET<<endl<<endl<<endl;
	cout << "Returning to Main Menu in "<< i;
	if(i==1){
		cout<<" Second.";
	}
	else {
		cout<<" Seconds.";
	}
	/*
	cout<<endl<<endl<<"Press any key to quick return.";
	char j = getch();
	if (j != '\0'){
		MainMenu();
	}
	*/
	sleep_sec(1);
	}
	MainMenu();
}

void Help(){
	ClearScr();
	cout<<GRN;
	cout<<"                         ##    ##     ## ######## ##       ########     ##    "<<endl;
	cout<<"                        ##     ##     ## ##       ##       ##     ##     ##   "<<endl;
	cout<<"                       ##      ##     ## ##       ##       ##     ##      ##  "<<endl;
	cout<<"                      ##       ######### ######   ##       ########        ## "<<endl;
	cout<<"                       ##      ##     ## ##       ##       ##             ##  "<<endl;
	cout<<"                        ##     ##     ## ##       ##       ##            ##   "<<endl;
	cout<<"                         ##    ##     ## ######## ######## ##           ##    "<<RESET<<endl;
	cout<<"                                                                               _____Symbols_____"<<endl;
    cout<<"_______________________________Buttons____________________________________     -----------------"<<endl;
	cout<<MAG<<"       movement keys:                      shooting keys:                      "<<RESET<<"|"<<GRN<<"P"<<BYEL<<"(Player)"<<RESET<<"      |"<<endl;
	cout<<"                                                                               |               |"<<endl;
	cout<<YEL<<"             UP          Exit    Reload          UP         Upgrade menu       "<<RESET<<"|               |"<<endl;
	cout<<BLU<<"            ---           ---     ---           ---             ---            "<<RESET<<"|    "<<BYEL<<"(Vaccine)"<<RESET<<YEL<<"V"<<RESET<<" |"<<endl;
	cout<<BLU<<"            |W|           |E|     |R|           |T|             |U|            "<<RESET<<"|               |"<<endl;
	cout<<BLU<<"            ---           ---     ---           ---             ---            "<<RESET<<"|               |"<<endl;
	cout<<BLU<<"      ---   ---   ---      ---            ---   ---   ---       ---            "<<RESET<<"|  "<<BYEL<<"(Ammo)"<<BLU<<"A"<<RESET<<"      |"<<endl;
	cout<<BLU<<"      |A|   |S|   |D|      |C|            |F|   |G|   |H|       |M|            "<<RESET<<"|               |"<<endl;
	cout<<BLU<<"      ---   ---   ---      ---            ---   ---   ---       ---            "<<RESET<<"|               |"<<endl;
    cout<<YEL<<"      LEFT  DOWN  RIGHT    Save           LEFT  DOWN  RIGHT   Game menu        "<<RESET<<"|               |"<<endl;
    cout<<"__________________________________________________________________________     |     "<<RED<<"Z"<<BYEL<<"(Zombie)"<<RESET<<" |"<<endl;
    cout<<"                                                                               |               |"<<endl;
    cout<<CYN<<"Collect all the vaccines and deliver them to the destination.                  "<<RESET<<"|               |"<<endl;
    cout<<CYN<<"Avoid getting hit by zombies;                                                  "<<RESET<<"|               |"<<endl;
    cout<<CYN<<"If they get in your way, just shoot them in the head!                          "<<RESET<<"| "<<BYEL<<"(Destination)"<<MAG<<"D"<<RESET<<"|"<<endl;
    cout<<CYN<<"Your guns are too weak?                                                        "<<RESET<<"-----------------"<<endl;
    cout<<CYN<<"Don't worry you can upgrade them in upgrade menu uisng your credits."<<endl;
    cout<<"Good luck soldier."<<RESET<<endl;
	cout << endl << "Return to Main Menu: (y)"<<endl;
	if (Input==false){
		cout<<endl<<YEL<<"Please enter the right character:"<<RESET<<endl;
		Input=true;
	}
	char c = getch();
	if (c=='y'||c=='Y'){
		MainMenu();
	}
	else {
		Input=false;
		Help();
	}
}

void Help1(){
	ClearScr();
	cout<<GRN;
	cout<<"                         ##    ##     ## ######## ##       ########     ##    "<<endl;
	cout<<"                        ##     ##     ## ##       ##       ##     ##     ##   "<<endl;
	cout<<"                       ##      ##     ## ##       ##       ##     ##      ##  "<<endl;
	cout<<"                      ##       ######### ######   ##       ########        ## "<<endl;
	cout<<"                       ##      ##     ## ##       ##       ##             ##  "<<endl;
	cout<<"                        ##     ##     ## ##       ##       ##            ##   "<<endl;
	cout<<"                         ##    ##     ## ######## ######## ##           ##    "<<RESET<<endl;
	cout<<"                                                                               _____Symbols_____"<<endl;
    cout<<"_______________________________Buttons____________________________________     -----------------"<<endl;
	cout<<MAG<<"       movement keys:                      shooting keys:                      "<<RESET<<"|"<<GRN<<"P"<<BYEL<<"(Player)"<<RESET<<"      |"<<endl;
	cout<<"                                                                               |               |"<<endl;
	cout<<YEL<<"             UP          Exit    Reload          UP         Upgrade menu       "<<RESET<<"|               |"<<endl;
	cout<<BLU<<"            ---           ---     ---           ---             ---            "<<RESET<<"|    "<<BYEL<<"(Vaccine)"<<RESET<<YEL<<"V"<<RESET<<" |"<<endl;
	cout<<BLU<<"            |W|           |E|     |R|           |T|             |U|            "<<RESET<<"|               |"<<endl;
	cout<<BLU<<"            ---           ---     ---           ---             ---            "<<RESET<<"|               |"<<endl;
	cout<<BLU<<"      ---   ---   ---      ---            ---   ---   ---       ---            "<<RESET<<"|  "<<BYEL<<"(Ammo)"<<BLU<<"A"<<RESET<<"      |"<<endl;
	cout<<BLU<<"      |A|   |S|   |D|      |C|            |F|   |G|   |H|       |M|            "<<RESET<<"|               |"<<endl;
	cout<<BLU<<"      ---   ---   ---      ---            ---   ---   ---       ---            "<<RESET<<"|               |"<<endl;
    cout<<YEL<<"      LEFT  DOWN  RIGHT    Save           LEFT  DOWN  RIGHT   Game menu        "<<RESET<<"|               |"<<endl;
    cout<<"__________________________________________________________________________     |     "<<RED<<"Z"<<BYEL<<"(Zombie)"<<RESET<<" |"<<endl;
    cout<<"                                                                               |               |"<<endl;
    cout<<CYN<<"Collect all the vaccines and deliver them to the destination.                  "<<RESET<<"|               |"<<endl;
    cout<<CYN<<"Avoid getting hit by zombies;                                                  "<<RESET<<"|               |"<<endl;
    cout<<CYN<<"If they get in your way, just shoot them in the head!                          "<<RESET<<"| "<<BYEL<<"(Destination)"<<MAG<<"D"<<RESET<<"|"<<endl;
    cout<<CYN<<"Your guns are too weak?                                                        "<<RESET<<"-----------------"<<endl;
    cout<<CYN<<"Don't worry you can upgrade them in upgrade menu uisng your credits."<<endl;
    cout<<"Good luck soldier."<<RESET<<endl;
	cout << endl << "Return to game: (y)"<<endl;
	if (Input==false){
		cout<<endl<<YEL<<"Please enter the right character:"<<RESET<<endl;
		Input=true;
	}
	char c = getch();
	if (c=='y'||c=='Y'){
		Round();
	}
	else{
		Input=false;
		Help1();
	}
}

void Exit(){
	ClearScr();
	cout<<RED;
	cout<<"   ##    ######## ##     ## #### ########    ##    "<<endl;
	cout<<"  ##     ##        ##   ##   ##     ##        ##   "<<endl;
	cout<<" ##      ##         ## ##    ##     ##         ##  "<<endl;
	cout<<"##       ######      ###     ##     ##          ## "<<endl;
	cout<<" ##      ##         ## ##    ##     ##         ##  "<<endl;
	cout<<"  ##     ##        ##   ##   ##     ##        ##   "<<endl;
	cout<<"   ##    ######## ##     ## ####    ##       ##    "<<RESET<<endl<<endl;
	cout<<"Are you sure you want to exit the game? (y,n)"<<endl;
	if (Input==false){
		cout<<endl<<YEL<<"Please enter the right character:"<<RESET<<endl;
		Input=true;
	}
	char Ans = getch();
	if (Ans=='y'||Ans=='Y'){
		ClearScr();
		cout<<"Good Bye!";
	}
	else if (Ans=='n'||Ans=='N'){
		MainMenu();
	}
	else {
		Input=false;
		Exit();
	}
}  

void Exit1(){
	ClearScr();
	cout<<RED;
	cout<<"   ##    ######## ##     ## #### ########    ##    "<<endl;
	cout<<"  ##     ##        ##   ##   ##     ##        ##   "<<endl;
	cout<<" ##      ##         ## ##    ##     ##         ##  "<<endl;
	cout<<"##       ######      ###     ##     ##          ## "<<endl;
	cout<<" ##      ##         ## ##    ##     ##         ##  "<<endl;
	cout<<"  ##     ##        ##   ##   ##     ##        ##   "<<endl;
	cout<<"   ##    ######## ##     ## ####    ##       ##    "<<RESET<<endl<<endl;
	cout<<"Are you sure you want to exit to mainmenu? (y,n)"<<endl;
	cout<<"All of your unsaved progress will be lost!"<<endl;
	if (Input==false){
		cout<<endl<<YEL<<"Please enter the right character:"<<RESET<<endl;
		Input=true;
	}
	char ans = getch();
	if (ans=='y'||ans=='Y'){
		MainMenu();	
	}
	else if (ans=='n'||ans=='N'){
		Round();
	}
	else {
		Input=false;
	Exit1();			
	}
}  

void GameMenu(){
	cout<<YEL;
	cout<<" ######      ###    ##     ## ########     ##     ## ######## ##    ## ##     ##"<<endl;
	cout<<"##    ##    ## ##   ###   ### ##           ###   ### ##       ###   ## ##     ##"<<endl;
	cout<<"##         ##   ##  #### #### ##           #### #### ##       ####  ## ##     ##"<<endl;
	cout<<"##   #### ##     ## ## ### ## ######       ## ### ## ######   ## ## ## ##     ##"<<endl;
	cout<<"##    ##  ######### ##     ## ##           ##     ## ##       ##  #### ##     ##"<<endl;
	cout<<"##    ##  ##     ## ##     ## ##           ##     ## ##       ##   ### ##     ##"<<endl;
	cout<<" ######   ##     ## ##     ## ########     ##     ## ######## ##    ##  ####### "<<RESET<<endl<<endl;
	cout<<"1-Return to Game"<<endl;
	cout<<"2-New Game"<<endl;
	cout<<"3-Settings"<<endl;
	cout<<"4-Help"<<endl;
	cout<<"5-Exit"<<endl<<endl;
	if (Input==false){
		cout<<YEL<<"Please just enter the numbers in the menu:"<<RESET<<endl;
		Input=true;
	}
	char Input1 = getch();
	if (Input1=='1'){
		Round();
	}
	else if (Input1=='2'){
		StartNew();
	}
	else if (Input1=='3'){
		Settings1();
	}
	else if (Input1=='4'){
		Help1();
	}
	else if (Input1=='5'){
		Exit1();
	}
	else {
		ClearScr();
		Input=false;
		GameMenu();
	}
}

void StartNew(){
	ClearScr();
	cout<<CYN;
	cout<<"   ##    ##    ## ######## ##      ##        ######      ###    ##     ## ########    ##    "<<endl;
	cout<<"  ##     ###   ## ##       ##  ##  ##       ##    ##    ## ##   ###   ### ##           ##   "<<endl;
	cout<<" ##      ####  ## ##       ##  ##  ##       ##         ##   ##  #### #### ##            ##  "<<endl;
	cout<<"##       ## ## ## ######   ##  ##  ##       ##   #### ##     ## ## ### ## ######         ## "<<endl;
	cout<<" ##      ##  #### ##       ##  ##  ##       ##    ##  ######### ##     ## ##            ##  "<<endl;
	cout<<"  ##     ##   ### ##       ##  ##  ##       ##    ##  ##     ## ##     ## ##           ##   "<<endl;
	cout<<"   ##    ##    ## ########  ###  ###         ######   ##     ## ##     ## ########    ##    "<<RESET<<endl<<endl;
	cout<<"Are you sure you want to start a new game? (y,n)"<<endl;
	cout<<"you will lose all your progress"<<endl;
	if (Input==false){
		cout<<endl<<YEL<<"Please enter the right character:"<<RESET<<endl;
		Input=true;
	}
	char ans = getch();
	if (ans=='y'||ans=='Y'){
	NewGame();
	}
	else if (ans=='n'||ans=='N'){
	Round();
	}
	else {	
	Input=false;		
	StartNew();	
	}
}

void Lose(){
	ClearScr();
	cout<<RED;
	cout<<" ######      ###    ##     ## ########        #######  ##     ## ######## ########     #### "<<endl;
	cout<<"##    ##    ## ##   ###   ### ##             ##     ## ##     ## ##       ##     ##    #### "<<endl;
	cout<<"##         ##   ##  #### #### ##             ##     ## ##     ## ##       ##     ##    #### "<<endl;
	cout<<"##   #### ##     ## ## ### ## ######         ##     ## ##     ## ######   ########      ##  "<<endl;
	cout<<"##    ##  ######### ##     ## ##             ##     ##  ##   ##  ##       ##   ##           "<<endl;
	cout<<"##    ##  ##     ## ##     ## ##             ##     ##   ## ##   ##       ##    ##     #### "<<endl;
	cout<<" ######   ##     ## ##     ## ########        #######     ###    ######## ##     ##    #### "<<RESET<<endl<<endl;
	cout<<"You Lose! Would you like to try again? (y/n)";
	if (Input==false){
		cout<<endl<<YEL<<"Please enter the right character:"<<RESET<<endl;
		Input=true;
	}
	char ans = getch();
	if (ans=='y'||ans=='Y'){
	Restart();
	}
	else if (ans=='n'||ans=='N'){
	MainMenu();
	}
	else {	
	Input=false;		
	Lose();	
	}
}

void Restart(){
	int i;
	for (i=5; i>0; i--){
	ClearScr();
	cout << "The game will restart in "<< i;
	if(i==1){
		cout<<" Second.";
	}
	else {
		cout<<" Seconds.";
	}
	sleep_sec(1);
	}
	NewGame();
}

void UpgradeMenu(){
	CapacityCredit = capacity*level;
	RangeCredit = range+level;
	HealthCredit = health*(level+1);
	cout<<MAG;
	cout<<"##     ## ########   ######   ########     ###    ########  ########     ##     ## ######## ##    ## ##     ##"<<endl;
	cout<<"##     ## ##     ## ##    ##  ##     ##   ## ##   ##     ## ##           ###   ### ##       ###   ## ##     ##"<<endl;
	cout<<"##     ## ##     ## ##        ##     ##  ##   ##  ##     ## ##           #### #### ##       ####  ## ##     ##"<<endl;
	cout<<"##     ## ########  ##   #### ########  ##     ## ##     ## ######       ## ### ## ######   ## ## ## ##     ##"<<endl;
	cout<<"##     ## ##        ##    ##  ##   ##   ######### ##     ## ##           ##     ## ##       ##  #### ##     ##"<<endl;
	cout<<"##     ## ##        ##    ##  ##    ##  ##     ## ##     ## ##           ##     ## ##       ##   ### ##     ##"<<endl;
	cout<<" #######  ##         ######   ##     ## ##     ## ########  ########     ##     ## ######## ##    ##  ####### "<<RESET<<endl<<endl;
	cout<<"1-Return to game."<<endl<<endl;
	if (capacity<7){
		cout<<"2-Upgrade capacity of magazine: 1 bullet (maximum is 7 bullets, now is "<<capacity<<"), Credit required: "<<CapacityCredit<<endl<<endl;
	}
	else {
		cout<<"2-Magazine Capacity has reached the maximum of 7 bullets!"<<endl<<endl;
	}
	if (range<10){
		cout<<"3-Upgrade range of shotgun: 1 extra range (maximum is 10, now is "<<range<<"), Credit required: "<<RangeCredit<<endl<<endl;
	}
	else {
		cout<<"3-Shotgun has reached the maximum range of 10!"<<endl<<endl;
	}
	if (health<5){
		cout<<"4-get an additional health (maximum is 5 healths, now is "<<health<<"), Credit required: "<<HealthCredit<<endl<<endl;
	}
	else {
		cout<<"4-Health has reached the maximum of 5!"<<endl;
	}
	if (Input==false){
		cout<<YEL<<"Please just enter the numbers in the menu:"<<RESET<<endl<<endl;
		Input=true;
	}
	else {
		cout <<endl;
	}
	
	char Input1 = getch();
	if (Input1=='1'){
		Round();
	}
	else if (Input1=='2'){
		if(credit>=CapacityCredit&&capacity<7){
			credit-=CapacityCredit;
			capacity++;
			cout<<GRN<<"Upgrade done successfully."<<endl;
			cout<<"Your magazine capacity is now "<<capacity<<"."<<RESET<<endl;
		}
		else if(credit<CapacityCredit&&capacity<7){
			cout<<RED<<"Unfortunately, your credit is not enough to get this item."<<endl;
			cout<<"Please gain "<<CapacityCredit-credit<<" more credit by playing."<<RESET<<endl;
		}
		else {
			cout<<BLU<<"The selected item has reached maximum."<<RESET<<endl;
		}
		sleep_sec(2);
		ClearScr();
		UpgradeMenu();
	}
	else if (Input1=='3'){
		if(credit>=RangeCredit&&range<10){
			credit-=RangeCredit;
			range++;
			cout<<GRN<<"Upgrade done successfully."<<endl;
			cout<<"Your shotgun range is now "<<range<<'.'<<RESET<<endl;
		}
		else if(credit<RangeCredit&&range<10){
			cout <<RED<<"Unfortunately, your credit is not enough to get this item."<<endl;
			cout<<"Please gain "<<RangeCredit-credit<<" more credit by playing."<<RESET<<endl;
		}
		else {
			cout<<BLU<<"The selected item has reached maximum."<<RESET<<endl;
		}
		sleep_sec(2);
		ClearScr();
		UpgradeMenu();
	}
	else if (Input1=='4'){
		if(credit>=HealthCredit&&health<5){
			credit-=HealthCredit;
			health++;
			cout<<GRN<<"Upgrade done successfully."<<endl;
			cout<<"Your health is now "<<health<<'.'<<RESET<<endl;
		}
		else if(credit<HealthCredit&&health<5){
			cout <<RED<<"Unfortunately, your credit is not enough to get this item."<<endl;
			cout<<"Please gain "<<HealthCredit-credit<<" more credit by playing."<<RESET<<endl;
		}
		else {
			cout<<BLU<<"The selected item has reached maximum."<<RESET<<endl;
		}
		sleep_sec(2);
		ClearScr();
		UpgradeMenu();
	}
	else {
		Input=false;
		ClearScr();
		UpgradeMenu();
	}
}

void KillMsg(){
	switch (kill%14){
		case 1:
			cout<<"First Blood"<<endl;
			break;
		case 2:
			cout<<"Double Kill"<<endl;
			break;
		case 3:
			if (rounds%2==0){
				cout<<"Triple Kill"<<endl;	
				}
			else {
				cout<<"Hattrick"<<endl;
			}
			break;
		case 4:
			cout<<"Team Killer"<<endl;
			break;
		case 5:
			cout<<"Headshot"<<endl;
			break;
		case 6:
			cout<<"Rampage"<<endl;
			break;
		case 7:
			cout<<"Killing Spree"<<endl;
			break;
		case 8:
			cout<<"Unstoppable"<<endl;
			break;
		case 9:
			cout<<"Monster Kill"<<endl;
			break;
		case 10:
			cout<<"Multi Kill"<<endl;
			break;
		case 11:
			cout<<"Ludicrouskill"<<endl;
			break;
		case 12:
			cout<<"Ultra Kill"<<endl;
			break;
		case 13:
			cout<<"Dominating"<<endl;
			break;
		case 0:
			cout<<"Godlike"<<endl;
			break;
	}
}

void Zombie(){
	/*cout<<"if Z in left of P move to right";
	cout<<"if Z in right of P move to left";
	cout<<"else if Z and P in same collumn move towards P (up or down)";*/
	int i=0;
		for (int y=0; y<15; y++){
			for (int x=0; x<15; x++){
				if (space[y][x]=='Z'){
					for (int j=0; j<level; j++){
						if (Zy[j]==y && Zx[j]==x){
							space[y][x]=' ';
							if (Px==x){
								if (Py>y){
									space[y+1][x]='Z';
									y++;
									Zy[j]++;
								}
								else if (Py<y){
									space[y-1][x]='Z';
									Zy[j]--;
								}
							}
							else {
								if (Px>x){
									space[y][x+1]='Z';
									x++;
									Zx[j]++;
								}
								else if (Px<x){
									space[y][x-1]='Z';
									Zx[j]--;
								}
							}
							i++;
							//if you want to make the game easier remove this 3 lines
							if(i==level){
								Death();
							}
						}
					}
				}
			}
		}
}

/*void Lore(){
	cout<<"In 2030, the corona global disaster reached its peak and pushed the human race to the brink of extinction."<<endl;
	cout<<"In addition to the losses of the disease itself, there were terrible wars over the resources to produce the vaccine,"<<endl;
	cout<<"which brought the population of the planet back to about a hundred years ago."<<endl;
	cout<<"Many countries were destroyed and joined the history."<<endl;
	cout<<"The number of safe places on the planet was estimated to be less than the fingers of the hand."<<endl;
	cout<<"In the meantime, what was left of the United Nations during a secret meeting described"<<endl;
	cout<<"humanity's last hope for survival as follows: <The remaining scientists who still hope to make a definitive vaccine"<<endl;
	cout<<"should take the shuttle to the International Space Station of Mars (ISSM) as soon as possible.>"<<endl;
	cout<<" to try to produce a vaccine there in complete safety."<<endl;
	sleep_sec(10);
}*/

void Save(){
	ofstream F1("save.txt");
	F1<<level<<endl;
	F1<<vaccine<<endl;
	F1<<credit<<endl;
	F1<<rounds<<endl;
	F1<<health<<endl;
	F1<<inAmmo<<endl;
	F1<<outAmmo<<endl;
	F1<<kill<<endl;
	F1<<Px<<endl;
	F1<<Py<<endl;
	F1<<V<<endl;
	F1<<range<<endl;
	F1<<capacity<<endl;
	F1<<Input<<endl;
	for (int i=0; i<10; i++){
		F1<<Zx[i]<<endl;
		F1<<Zy[i]<<endl;
	}
	for (int i=0; i<10; i++){
		F1<<Vx[i]<<endl;
		F1<<Vy[i]<<endl;
	}
	for (int i=0; i<5; i++){
		F1<<Ax[i]<<endl;
		F1<<Ay[i]<<endl;
	}
	F1.close();
}

void Load(){
	level=0;
	vaccine=0;
	credit=0;
	rounds=0; 
	health=3; 
	inAmmo=3; 
	outAmmo=0; 
	kill=0;
	Px=0;
	Py=0;
	V=0;
	range=5;
	capacity=3;
	Input=true;
	Zx[10]={15};
	Zy[10]={15};
	Vx[10]={15};
	Vy[10]={15};
	Ax[5]={15};
	Ay[5]={15};
	for(int Row=0; Row<15; Row++){
		for (int Column=0; Column<15; Column++){
			space[Row][Column]=' ';
		}
	}
	ifstream F2("save.txt");
	F2>>level;
	F2>>vaccine;
	F2>>credit;
	F2>>rounds;
	F2>>health;
	F2>>inAmmo;
	F2>>outAmmo;
	F2>>kill;
	F2>>Px;
	F2>>Py;
	space[Py][Px]='P';
	F2>>V;
	F2>>range;
	F2>>capacity;
	F2>>Input;
	for (int i=0; i<10; i++){
		F2>>Zx[i];
		F2>>Zy[i];
		space[Zy[i]][Zx[i]]='Z';
	}
	for (int i=0; i<10; i++){
		F2>>Vx[i];
		F2>>Vy[i];
		space[Vy[i]][Vx[i]]='V';
	}
	for (int i=0; i<5; i++){
		F2>>Ax[i];
		F2>>Ay[i];
		space[Ay[i]][Ax[i]]='A';
	}
	if (space[0][0]!='P'){
		space[0][0]=' ';
	}
	space[14][14]='D';
	F2.close();
	Round();
}

void Death(){
	if (space[Py-1][Px-1]=='Z'||space[Py-1][Px]=='Z'||space[Py-1][Px+1]=='Z'
	||space[Py][Px-1]=='Z'||space[Py][Px]=='Z'||space[Py][Px+1]=='Z'
	||space[Py+1][Px-1]=='Z'||space[Py+1][Px]=='Z'||space[Py+1][Px+1]=='Z'){
		cout<<RED<<"The zombie is eating you!"<<endl;
		cout<<"You lost one of your healths!"<<RESET<<endl;
		health--;
		sleep_sec(2);
		if(health==0){
			Lose();
		}
		Round();
	}
}