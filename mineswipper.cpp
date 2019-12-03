
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

int bombsCount = 0;

char h_axis[FIELD_WIDTH+1] = {};

char win_str[13][152]={"###N########NN#N#NNN#N##N#####NNN#######N##########H###NNNNNNNN#NN####################NN###NNN##N###NNNNNNN######################N#NNNNNNNN###########",
					   "#NNN#N######NNN#N#####NNN#N###NNN####N##NN#####N########NN#NNNNNNN#####################NN####N########NNNNN####NNNNN####NN###H####NNNNNNN###N########N",
					   "#NNNNNNNNNNN#Na   dMNNNN#N; .kNNN#= .gNNNMa, 7MNN##Nm.  .M###NNNa, .gMNNNNNNNNa.  dM#N##NF .MNNNNMN, .dNNNa   +MNNMN,   /MNNN#NNa, .gM#NNN#NNNNNNNNNNN",
					   "NNNNNNNNNNNNNNNN.  WNNNNNF.dNNNND  JNNNNNNNN[  UNNNNN]  MNNNNNNNNb MNNNNNNNNNNNb  JNNNNNM`  (NNNNNN!.NNNNNN~  NNNNNNN]..  WNN#NN#N dNNNNNNNNNNNNNNNNNN",
					   "NNNNNNNNNNNNNNNNN,  WNNNF.MNNNNF  .NNNMNNNNNM,  WN#NN]  MN#NNNNNN# MNNNNNNNNNNNN,  MNNNM$.[  WNNNNF MNNNNNN~  NNMNNNNF.N,  ?MNNNNM d#NNNNNNNNNNNNNNNNN",
					   "NNNNNNNNNNNNNNNNNN,  WMt.MNNNMM   MNNNNMNNNNN]  ,N#NN[  MNNNNNNNN#`MNNNNNNNNNNNNb  ,NNN@.MN. .MNNM!.NNNNNNN~  NNNMNNNF.NNm. .WNNNM dNNNNNNNNNNNNNNNNNN",
					   "NNNNNNNNNNNMNMNNNNN,  '.NNNNNN#   MNNNNNNNNMNF  .NNNN]  MNNNNNN#N# MNNNNNNNNNNNNN;  HNM!JNNb  ?NNF.NNNNMNNN~  NNNNNNNF.NNNN,  7NNM`dNNNNNNNNNNNNNNNNNN",
					   "NNNNMNNNNNNNNMMNNMNN  .NNNMNNNM.  MMNMNNMNNNNF  .NNNN]  MNNNNNNNN# MNNNNNNNNNMNNMN  ,NF.NNMN;  HM`dNMNMNNMM~  NNNNMNN].NNNNNL  ,MM dNNNNNNNNNNMNNNNNNN",
					   "NNNNNNNMNNMNNNMNNNNM  .NMNNMNNNb  JNNNNNNNNNM!  dNNNN]  MMNNNNNNN# MNNNNNNNNNNNNNN[  T.MNNNMN  ,F.NNNMNNNNN~  NNNNNNNF.NN#NNNN,  T dNNNNNNNNNNNNNNNNNN",
					   "NNNNNNNNNMNMNNNNNNMN  .MNNNNNMNMp  TNNNNNNNM% .dMNNNMb  (NNNNNMNM^.NNNNNMNNNNNNNNMN.  JNNNNNMb   MNNNNMNNNN~  NNNMNNN].MNNNNNNNp   dNNNMNNMNMNNNNMNNNN",
					   "NNNNNNNNMNNNMNNMNMY'   TWMNNMNNNMNJ..TMMM#'`.(NNNMNNNNh, .T'HH'''..NMNMMNNNNNMNMNNN] .NNNMNNNN, .MNNNNNMMH9   TWMNM'''  -TWMNNNNNN, dNMNNNNNMNMNMNMNNM",
					   "NNNNMMMNMMNNNMNMMNNNNNNNNMNMMNMNNNNMNmgJJggNNNNNMNNMNNNMNNg+J+gMNNMNMNMNNMNNMNNNMNMNgMNMNMMNMNNgNNMMMMNNNNNNNNNNMNNNNNNNNNMNNMMNNMgMNNNMNMNNNMMNMMNMNN",
					   "NNMNNNNMNMMMMNMNNNNNNNMMNNMNNNNNMNNNNNMMNNMNMNNMNNMMMMMNMNNMNNNNMMMNNMNNMNNMNNMNNMMNMNMNMNNMMNMMMMNNNMNNNNNNNNNNMMNNMNMNNNNMMNMMMMNMMNMNMNMMMNNMNNNNMN"
};

char loose_str[15][183]={
	"#H#####################HH####NNN####NNN#########################H################################H###N#N##N###NNN########################H#H############NN#####H##H##H##############",
	"###################N########N####N#############N###################H###N########N########H#####H#H###N#####N#########N#NN#######################N###N#N#######################H#####",
	"##################NNN########NN########NN#####NNNN################H#####NNNNNNNN######H################NNNNNN#########NN########NN#####N###H#H###NN##NN#N###########################",
	"############NNM'=-....M'DMM###N####NM`/#####N#Nb<MMMMMNN#####N##MlMM<j##D<MMMM<<<<<MMMz###N########MY'!...._7WN##ND???M?<jN###$<??M?<#<??M?<<<<<????##NR<??M?<<<M?'B###N#NN#########",
	"NNN#NNNNNNNN#^ .MN##NNN,  M###NNNNNM^  UNNNNNNNNNN.(  ?NNNNNN#N/.  (######N  ,NNNN##p ,#NNNNNNNNNMD .+#NN#NNa. TNNNNN. .MNNNNNNNN .NN#NN|  MNN###N, ##NN#b  -NNNNm  .HNNNNN#NNNN#N##",
	"N#NNNNNN##NF  .NN#NNNNN#[ MNNNNNNNNF.,  MNNNNNNNNN{JL  WNNNNNNF.@  JN#NNNNM  ,NNNNNNNm(##N##NNN#M^ .MNNNNNNNNN  (NNN#b  (NNNNNNN$.##NNN#]  MNN#NNNN.#NNNN#  -NN#NN[  ,N#NNN##NN#NNNN",
	"NNNNNNNNN##  .NN#NNN#N#NN.MNNNNNNNF.MN. .MNNNNNNNN{JM, .MNNNN@.M@  J##NNNNM` ,N#NNF.#NNN#NNNNNNNt  (NNNNNNNNNN[  dNNNN[  4NNNNNF.MNNNNN#]  MNNNM`W#####NN#  -NNNNM! .dNNNN##NN#NNN##",
	"##NNN#NNNN]  ,NNN#NNN###NNNNNNNNN# dN#b  (NNNNNNNN{JNN. ,NNNM_d#@  J#NN##NN  .'''^ .NN#NNNNNNN#N~  dNNNNNNNNNNF  ,NNNNM,  MNNN#-dNNNNNNN]  ''''  MNNNNNNN@  -MMW' ..MNNNNNNNNN##NN##",
	"NNNNNN#NNN]  ,NN#NNNF7777777dNNNM',MMMMt  ZNNNNNNM{JN#b  ?NM^JNN@  JNNNNNNN` ,NNNN,.NNNNN#NNNNNN_  dNNMNNNNNNNF  .NNNNNN. ,NNM'JNNNNNNNN] `M#NMp MNNNNNNN#  .ga  ,MNNNNNN#NN##NNNNNN",
	"####NNNNNNN   MN#N###NN[  dNNMMNt.gggggg,  WNNNNNN{JNNN[  W$.###@  JNNNNMNM  ,NN#NN.N#NMNNNNNNNNL  JNNMNNNNNNN%  JNNNNNNb  JN%.NNNNNN##N]  MNNNNJMNNMMNN##  -N#N,  TNNNNNNNNNNN####N",
	"NNNNNN#N#NNb  ,MN#NNNNN]  MNNNNF.MNNNNNNN. .MNNNNN:(NN#M,  .#NNN@  JNNNNNNM` ,NNNNNNNND.NNNNNNNNN,  WNNNNNMNNF  .NNNNNNNN[  =.#NNNNNNNNN]  MNNNNNNN# dNNN#  -NNNNp  (MNNNNNNNNNNNNNN",
	"NNNNNNNNNNNNN, .TMNNNNMt  MNMMD -NMNNMNNMb  ,MNMM@ .HNNNN..MNNNNF  (NMNNMN#  .MNNNMNM= .NNNNNNNNNMm, TMNMNMM' .dNNNMNMNNMM, .MNNNNN#NNNM/  UMNMNNMD  MNNNF  -NMNNNN.  TMNNMNNNNNNNNN",
	"NNNNNNNNMNNNNNMm-......(gMNNa......MNNMh.......(.......NNNdN#N........NNa...............NNNNNMNMNNNNNg......JMMNNMNNMNNMNNN.dNNNNNNNNN...............MNa.......MMNNN-....MNNNNN#NNNN",
	"NNMNNMNNNNNMNNNMNNNNNNNNMMNMNNMMNNNNNMNNNNNMNNNNNNNNNMMMNMNNNNNNNMMNMNMNNMNMNMNNNMNNNMNNNNMNNNNNMMNNNNMNMNNNNNMNMNNNMNNNNNNNNMMMMNMNNNNNNNMNNMNMNMNNNNNNNMMNNNNMNNMNNNNMMMNNMNNNNNNN",
	"NNNMNNMNNMNNNNNNNNNNNNNNNMMNMNMMMNMNNMNMMNNNNMNNMNNMMNNNNNMNNNNNNNNMNMNNMNNNNNNNMNMNNNMNNNNNMNNNNNMMNMNMMNNMNNMNMMNNNNMNNMNNMNNNNNNNMNNNNNNNMNMNNMNMNNMNNNNMNNNNMNNMNMNMNNMNNMNNMNNN"
};



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
			}
			else if (j == 0 && i>0) {
				printf("%4d",i);
			}
			else {
				printf("%4c",FIELD[i][j]+46);
			}

			if (j == FIELD_WIDTH) {
				printf("\n\n");
			}
		}
	}
	printf("\n\n\n\n");
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

void dispWin(){
	for(int i=0;i<13;i++){
		printf("%s\n",win_str[i]);
	}
}

void dispLoose(){
	for(int i=0;i<15;i++){
		printf("%s\n",loose_str[i]);
	}
}

int main()
{

	defaultFieldSet();
	disp();

	srand((unsigned)time(NULL));
	int tempBombs = 1;
	for (int i = 0;i<MINES;i++) {
	// for (int i = 0;;i++) {
		
RAND:
		int x = rand() % FIELD_WIDTH + 1;
		int y = rand() % FIELD_HEIGHT + 1;

		for (int j = 0;j < tempBombs;j++) {
			if (mines_place[j][0] == x && mines_place [j][1] == y){
				goto RAND;
			}
			if (mines_place[j][0] != x && mines_place[j][1] != y && j == tempBombs-1) {
				mines_place[i][0] = x;
				mines_place[i][1] = y;
			}
		}

		if(tempBombs==MINES){
			break;
		}
		tempBombs++;
	}
	printf("bombs : %d\n",tempBombs);

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


	while(1) {
		int v_num,h_num;
		char str;
		scanf("%d %c", &v_num,&str);

		if(int(str)>=97 && int(str)<=97+FIELD_WIDTH){
			h_num=int(str)-96;

			switch(bombs_around[v_num][h_num]){
				case 10:{
					dispLoose();
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
				dispWin();
				dispAns();
				return 0;
			}
			dispLoose();
			disp();

			printf("THE ANSWER IS \n");
			dispAns();
			return 0;
		};
	printf("answer\n");
	for(int i=1;i<=FIELD_HEIGHT;i++){
		for(int j=1;j<=FIELD_WIDTH;j++){
			printf("%4d",bombs_around[i][j]);
			if(j==FIELD_WIDTH){
				printf("\n\n");
			}
		}
	}
		disp();
	}
}
