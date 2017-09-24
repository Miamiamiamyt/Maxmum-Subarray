//
//  main.c
//  最大子数组
//
//  Created by miamiamia on 17/9/22.
//  Copyright © 2017年 miamiamia. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
#include <math.h>

void FIND_MAX_CROSSING_SUBARRAY(int a[],int low,int mid,int high,int *x,int *y,int *z) {
    int left_sum = INT_MIN;
    int right_sum = INT_MIN;
    int sum = 0;
    int max_left = 0;
    int max_right = 0;
    int i;
    for(i = mid; i >= low; i--) {
        sum = sum + a[i];
        if(sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    sum = 0;
    for(i = mid+1; i <= high; i++) {
        sum = sum + a[i];
        if(sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }
    *x = max_left;
    *y = max_right;
    *z = left_sum+right_sum;
    
}

void FIND_MAXMUM_SUBARRAY(int a[],int low,int high,int *x,int *y,int *z) {
    int mid = 0;
    int left_low,left_high,left_sum;
    int right_low,right_high,right_sum;
    int cross_low,cross_high,cross_sum;
    if(low == high) {
        *x = low;
        *y = high;
        *z = a[low];
        return;
    }
    mid = floor((low+high)/2);
    FIND_MAXMUM_SUBARRAY(a,low,mid,&left_low,&left_high,&left_sum);
    FIND_MAXMUM_SUBARRAY(a,mid+1,high,&right_low,&right_high,&right_sum);
    FIND_MAX_CROSSING_SUBARRAY(a,low,mid,high,&cross_low,&cross_high,&cross_sum);
    if(left_sum >= right_sum && left_sum >= cross_sum){
        *x = left_low;
        *y = left_high;
        *z = left_sum;
        return;
    }
    else if(right_sum >= left_sum && right_sum >= cross_sum) {
        *x = right_low;
        *y = right_high;
        *z = right_sum;
        return;
    }
    else {
        *x = cross_low;
        *y = cross_high;
        *z = cross_sum;
        return;
    }
}
int main(int argc, const char * argv[]) {
    int low = 0,high = 0, sum = 0;
    int a[5000];
    int count = 0;
    FILE *fp;
    if((fp = fopen("task1.txt","r")) == NULL) {//判断文件是否存在及可读
           printf("error!");
           return -1;
    }
   
    while (fscanf(fp,"%d",a+count++)==1) {
        //printf("%d\n",a[count-1]);
    }
    fclose(fp);
    FIND_MAXMUM_SUBARRAY(a,0,count-2,&low,&high,&sum);
    printf("%d %d %d",low,high,sum);
    return 0;
}
