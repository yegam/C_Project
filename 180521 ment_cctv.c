#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

int section[6][6]={ {0,0,0,0,0,0},
					{0,4,0,3,0,0},
					{0,1,0,0,0,0},
					{0,0,0,0,0,0},
					{4,0,0,0,2,0},
					{0,0,0,0,0,0}};

void f1(int,int,int);//오른쪽
void f2(int,int,int);//왼쪽
void f3(int,int,int);//위
void f4(int,int,int);//아래
//1=위아래,2==오른쪽왼쪽, 3==오른쪽왼쪽위아래

int main(){
	int y,x,all;
	while (1){
	y=x=0;
		for(y=0;y<6;y++){
			for(x=0;x<6;x++){
				if(section[y][x]=1){
					section[6][6]=f3(y,x,section[6][6]);
					section[6][6]=f4(y,x,section[6][6]);
				}
			}
		}
			else if(section[y][x]=2){
				section[y][x]=f1(y,x,section[6][6]);
				section[y][x]=f2(y,x,section[6][6]);
			}
	}
	system("pause");
	return 0;
}

int f1(int y, int x, int section[6][6]){
	while(x<6 && section[y][x]!=4){
		section[y][x]= -1;
		x=x+1;
	}
}