
// #include "stdafx.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"

#define FIELD_HEIGHT 4
#define FIELD_WIDTH 4
#define MINES 1

int mines_place[MINES][2];
int bombs_around[FIELD_HEIGHT+1][FIELD_WIDTH+1];
int FIELD[FIELD_HEIGHT+1][FIELD_WIDTH+1];

int bombsCount = 0;

char h_axis[FIELD_WIDTH+1] = {};

void defaultFieldSet(){
	for (int i = 1;i <= FIELD_HEIGHT;i++) {
		for (int j = 1;j <= FIELD_WIDTH;j++) {
			FIELD[i][j]=0;
		}
	}

	for(int i=1;i<=FIELD_WIDTH;i++){
		char tmp = (char)i+96;
		h_axis[i]=tmp;
	}
}

void BombsCount(){
	bombsCount=0;
	for(int i=1;i<=FIELD_HEIGHT;i++){
		for(int j=1;j<=FIELD_WIDTH;j++){
			if(FIELD[i][j]==-11){
				bombsCount++;
			}
		}
	}
	printf("\nMINES %d / %d\n",bombsCount,MINES);
}

void disp() {
	BombsCount();
	for (int i = 0;i <= FIELD_HEIGHT;i++) {
		for (int j = 0;j <= FIELD_WIDTH;j++) {
			if (i == 0 && j == 0) {
				printf("%5c", 0);
			}
			else if (i == 0 && j>0) {
				printf("%4c", j + 96);
				// if(j==FIELD_WIDTH){
				// 	printf("\n");
				// 	for(int k=0;k<=FIELD_WIDTH;k++){
				// 		if(k==0){
				// 			printf("    ");
				// 		}
				// 		printf("____");
				// 	}
				// }
			}
			else if (j == 0 && i>0) {
				// printf("%2d |", i);
				printf("%4d",i);
			}
			else {
				printf("%4c",FIELD[i][j]+46);
				// printf("%4c", 46);
			}

			if (j == FIELD_WIDTH) {
				// printf("\n   |\n");
				printf("\n\n");
			}
		}
	}
	printf("\n\n\n\n");
}

void mineDisp() {
	for (int i = 1;i <= FIELD_WIDTH;i++) {
		for (int j = 1;j <= FIELD_HEIGHT;j++) {
			for (int k = 0;k < MINES;k++) {
				printf("%d %d\n", mines_place[k][0], mines_place[k][1]);
				if (i == mines_place[k][0] && j == mines_place[k][1]) {
					printf("%4d", 1);
				}
			}
		}
	}
}

void mineMapDisp() {
	int flag;
	for (int j = 1;j <= FIELD_HEIGHT;j++) {
		for (int i = 1;i <= FIELD_WIDTH;i++) {
			flag = 0;
			for (int k = 0;k < MINES;k++) {
				if (i == mines_place[k][0] && j == mines_place[k][1]) {
					printf("%4d", 1);
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				printf("%4c",0);
			}
			if (i == FIELD_WIDTH) {
				printf("\n\n");
			}
			if (flag == 1) {
				continue;
			}		
		}
	}
}

void mineMapDash() {
	for (int i = 1;i <= FIELD_WIDTH;i++) {
		for (int j = 1;j <= FIELD_HEIGHT;j++) {
			printf("HHHHHHHHHHHHHHHHHHHH %4d %4d\n", i, j);
			for (int k = 0;k < MINES;k++) {
				printf("MINE %4d %4d\n", mines_place[k][0], mines_place[k][1]);
				if (i == mines_place[k][0] && j == mines_place[k][1]) {
					printf("%4d\n", 1);
					break;
				}
			}


			if (j == FIELD_HEIGHT) {
				printf("\n\n");
			}
		}
	}
}

int SearchBomb(int x,int y){
	int num =0; 
	for (int i=0;i<MINES;i++){
		if(x>1){
			if(y>1){
				if(x-1==mines_place[i][0] && y-1==mines_place[i][1]){
					num++;
				}
			}
			if(x-1==mines_place[i][0] && y==mines_place[i][1]){
				num++;
			}
			if(y<FIELD_HEIGHT){
				if(x-1==mines_place[i][0] && y+1==mines_place[i][1]){
					num++;
				}
			}
		}
		if(y>1){
			if(x==mines_place[i][0] && y-1==mines_place[i][1]){
				num++;
			}
		}
		if(y<FIELD_HEIGHT){
			if(x==mines_place[i][0] && y+1==mines_place[i][1]){
				num++;
			}
		}
		if(x<FIELD_WIDTH){
			if(y>1){
				if(x+1==mines_place[i][0] && y-1==mines_place[i][1]){
					num++;
				}
			}
			if(x+1==mines_place[i][0] && y==mines_place[i][1]){
				num++;
			}
			if(y<FIELD_HEIGHT){
				if(x+1==mines_place[i][0] && y+1==mines_place[i][1]){
					num++;
				}
			}
		}
	}
	return num;
}

void dfs(int x,int y){
	FIELD[y][x]=bombs_around[y][x]+2;

	for(int dx=-1;dx<=1;dx++){
		for(int dy=-1;dy<=1;dy++){
			int nx = x+dx,ny=y+dy;

			if(dx==0&&dy==0){
				continue;
			}
			
			if(1<=nx && nx<=FIELD_WIDTH && 1<=ny && ny<=FIELD_HEIGHT){
				if(bombs_around[ny][nx]==0 && FIELD[ny][nx]==0){
					dfs(nx,ny);
				}else{
					FIELD[ny][nx]=bombs_around[ny][nx]+2;
				}
			}
		}
	}
	return;
}

void dispAns(){
	for (int i = 0;i <= FIELD_HEIGHT;i++) {
		for (int j = 0;j <= FIELD_WIDTH;j++) {
			if (i == 0 && j == 0) {
				printf("%4c", 0);
			}
			else if (i == 0 && j>0) {
				printf("%4c", j + 96);
			}
			else if (j == 0 && i>0) {
				printf("%4d",i);
			}
			else {
				printf("%4d",bombs_around[i][j]);
			}

			if (j == FIELD_WIDTH) {
				printf("\n\n");
			}
		}
	}
}

bool CompareBombsAns(){
	int count=0;
	for (int i=1;i<=FIELD_HEIGHT;i++){
		for(int j=1;j<=FIELD_WIDTH;j++){
			if(FIELD[i][j]==-11){
				for(int k=0;k<MINES;k++){
					if(i==mines_place[k][0] && j==mines_place[k][1]){
						break;
					}
				}
				count++;
			}
		}
	}

	if(count!=MINES){
		return false;
	}
	return true;
}

bool IsFull(){
	for(int i=1;i<=FIELD_HEIGHT;i++){
		for(int j=1;j<=FIELD_WIDTH;j++){
			if(FIELD[i][j]==0){
				return false;
			}
		}
	}

	return true;
}

int main()
{

	defaultFieldSet();
	disp();

	srand((unsigned)time(NULL));
	int temp = 1;
	for (int i = 0;i < MINES;i++) {
		
		//mines_place[i][0]= rand() % FIELD_WIDTH + 1;
		//mines_place[i][1]=rand() % FIELD_HEIGHT + 1;
		//printf("%d %d\n",mines_place[i][0],mines_place[i][1]);
		int x = rand() % FIELD_WIDTH + 1;
		int y = rand() % FIELD_HEIGHT + 1;

		for (int j = 0;j < temp;j++) {
			if (mines_place[j][0] != x && mines_place[j][1] != y) {
				mines_place[i][0] = x;
				mines_place[i][1] = y;
			}
		}
		
		//bool tmtm = isOK(temp);
		//printf("%d", tmtm);
		temp++;

		
	}

	//真真真真
	//bombs set to bombs_around from mines_place
	int temp_flag=0;
	for (int i = 1;i <= FIELD_HEIGHT;i++) {
		for (int j = 1;j <= FIELD_WIDTH;j++) {
			int bombs=0;
			for(int k=0;k<MINES;k++){
				if(j==mines_place[k][0]&&i==mines_place[k][1]){
					bombs=10;
					goto A;
				}
			}
			bombs=SearchBomb(j,i);
A:
			bombs_around[i][j]=bombs;
		}
	}

	
	printf("answer\n");
	for(int i=1;i<=FIELD_HEIGHT;i++){
		for(int j=1;j<=FIELD_WIDTH;j++){
			printf("%4d",bombs_around[i][j]);
			if(j==FIELD_WIDTH){
				printf("\n\n");
			}
		}
	}

	// mineMapDisp();

	while(1) {
		int v_num,h_num;
		char str;
		scanf("%d %c", &v_num,&str);

		if(int(str)>=97 && int(str)<=97+FIELD_WIDTH){
			h_num=int(str)-96;

			switch(bombs_around[v_num][h_num]){
				case 10:{
					printf("\n\nGAME OVER!!\n\n");
					printf("THE ANSWER IS\n");
					dispAns();
					return 0;
				}
				case 0:{
					dfs(h_num,v_num);
				}
				default:{
					FIELD[v_num][h_num]=bombs_around[v_num][h_num]+2;
				}
			}
		}

		if(int(str)>=65 && int(str)<=73+FIELD_WIDTH){
			h_num=int(str)-64;

			if(FIELD[v_num][h_num]==-11){
				FIELD[v_num][h_num]=0;
			}else{
				FIELD[v_num][h_num]=-11;
			}
		}

		if(IsFull()){
			if(CompareBombsAns()){
				printf("YOU ARE WIN!!\n");
				dispAns();
				return 0;
			}
			printf("YOU ARE WRONG!\nYOUR ANSWER IS\n");
			disp();

			printf("THE ANSWER IS \n");
			dispAns();
			return 0;
		};

		disp();
	}
}
