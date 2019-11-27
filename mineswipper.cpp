
// #include "stdafx.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"

#define FIELD_HEIGHT 9
#define FIELD_WIDTH 9
#define MINES 10

int mines_place[MINES][2];
int bombs_around[FIELD_HEIGHT+1][FIELD_WIDTH+1];
int FIELD[FIELD_HEIGHT+1][FIELD_WIDTH+1];

char h_axis[FIELD_WIDTH+1] = {
	' ','a','b','c','d','e','f','g','h','i'
};

void defaultFieldSet(){
	for (int i = 1;i <= FIELD_HEIGHT;i++) {
		for (int j = 1;j <= FIELD_WIDTH;j++) {
			FIELD[i][j]=0;
		}
	}
}

void disp() {
	for (int i = 0;i <= FIELD_HEIGHT;i++) {
		for (int j = 0;j <= FIELD_WIDTH;j++) {
			if (i == 0 && j == 0) {
				printf("%4c", 0);
			}
			else if (i == 0 && j>0) {
				printf("%4c", j + 96);
			}
			else if (j == 0 && i>0) {
				printf("%4d", i);
			}
			else {
				printf("%4c",FIELD[i][j]+46);
				// printf("%4c", 46);
			}

			if (j == FIELD_WIDTH) {
				printf("\n\n");
			}
		}
	}
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
		// CountBombs(&num,x-1,y-1);
		//
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

// void CountBombs(*int num,int x,int y){
// 	for(int i=0;i<MINES;i++){
// 		if(x==mines_place[i][0]&&y==mines_place[k][1]){
// 			*num++;
// 		}
// 	}
// }


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
	printf("bombs around\n");
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
			printf("%4d",bombs);
			bombs_around[i][j]=bombs;

			if(j==FIELD_WIDTH){
				printf("\n\n");
			}
		}
	}

	
	printf("hogei\n");
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

		h_num=int(str)-96;

		printf("h_num : %d\n",h_num);
		// for(int i=0;i<MINES;i++){
		// 	if(v_num==mines_place[i][1] && h_num==mines_place[i][0]){
		// 		printf("GAME OVER!!\n");
		// 		return 0;
		// 	}
		// }
		// 
		printf("%d\n",bombs_around[v_num][h_num]);

		switch(bombs_around[v_num][h_num]){
			case 10:{
				printf("\n\nGAME OVER!!\n\n");
				return 0;
			}
			case 0:{
			}
			default:{
				// FIELD[v_num][h_num]=bombs_around[v_num][h_num];
				FIELD[v_num][h_num]=bombs_around[v_num][h_num]+2;
			}
		}

		
		printf("%d %c\n", v_num, str);
		printf("%d %d\n",bombs_around[v_num][h_num],FIELD[v_num][h_num]);
		disp();
	}
}

//bool IsOK(int mines_place[MINES][2], int temp[2]) {
//bool isOK(int temp[2]){
//	printf("%d %d\n", temp[0], temp[1]);
//	return true;
//}

