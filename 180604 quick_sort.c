//
//  quick_sort.c
//  Mentoring
//
//  Created by Gam on 2018. 6. 4..
//  Copyright © 2018년 Gam. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a,const void *b);
int main(void) {
    int arr[20],i;
    srand(time(0));
    for (i=0;i<20;i++){
        arr[i]=rand()%999+1;
    }
    qsort(arr,20,sizeof(int),compare);
    for (i=0;i<20;i++){
        printf("%d\n",arr[i]);
    }
    return 0;
}
int compare(const void *a,const void *b){
    return *(int*)a-*(int*)b;
}
