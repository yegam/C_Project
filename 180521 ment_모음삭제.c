#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
int main(){
	int i, j;
	char word[20],temp[20];
	j = 0;
	printf("영어단어를 입력하세요.\n");
	scanf("%s",word);
	for (i=0;i<21;i++){
		if (word[i] != 'a' && word[i] != 'e' && word[i] != 'i' && word[i] != 'o' && word[i] != 'u'){
			temp[j++] = word[i];
		}
	}
	printf("%s",temp);


	system("pause");
	return 0;
}