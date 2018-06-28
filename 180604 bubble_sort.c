#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void) {
    int arr[20],i,j,k,temp,max;
    srand(time(0));
    for (i=0;i<20;i++){
        arr[i]=rand()%999+1;
        printf("%d,",arr[i]);
    }
    printf("\n=========================\n");
    for (i=1;i<20;i++){// 기준 인덱스
        for(j=0;j<i;j++){// 기준 인덱스와 이전 인덱스를 비교
            if (arr[j]/arr[i]>=1){ // 기준 인덱스보다 이전 인덱스가 크거나 같을 경우
                if (i-j>1){
                    temp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = temp;
                    for (k=j+1;k<i;k++){
                        temp = arr[k];
                        arr[k] = arr[i];
                        arr[i] = temp;
                    }
                }
                else if (i-j==1){
                    temp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = temp;
                }
            }
        }
    }
    for(i=0;i<20;i++){
        printf("%d\n",arr[i]);
    }
    return 0;
}
