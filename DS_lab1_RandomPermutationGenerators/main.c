#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define N 100
#define REPEAT 1

/**
 * Created by ijaehyeon on 2017. 9. 10..
 **/

int my_rand1(int base, int range);
int my_rand2(int base, int range);
void algo1();
void algo2();
void algo3();
void swap(int *this,int *that);

int main() {
    algo1();    // 1
    //algo2();  // 2
    //algo3();  // 3

    return 0;
}

void algo1(){

    srand((unsigned)time(NULL));
    int i,j,k;
    int array[N] = {-1,};
    for(i = 0 ; i < N ; i++){
        array[i] = my_rand1(0,N);
        for(j = 0 ; j < i ; j++) {
            if (array[i] == array[j]) {
                i--;
                break;
            }
        }
    }

    for(k = 0 ; k < N ; k++){
        printf("%d, ",array[k]);
    }
}
void algo2(){
    srand((unsigned)time(NULL));
    int i,j,k;
    int array[N]={-1,};
    int lookup[N]={0,};
    bool flag;
    for(int i = 0 ; i < N ; i++){ ;
        while(1){
            array[i] = my_rand1(0,N);
            if(lookup[array[i]-1] != 1){
                lookup[array[i]-1] = 1;
                break;
            }
        }
    }
    for(k = 0 ; k < N ; k++){
        printf("%d, ",array[k]);
    }
}

void algo3(){
    srand((unsigned)time(NULL));
    int i,j,k;
    int array[N] = {-1,};
    for(i = 0 ; i < N ; i++){
        array[i] = i + 1;
    }
    for(i = 1 ; i < N ; i ++){
        swap(&array[i],&array[my_rand2(0,i)]);
    }
    for(k = 0 ; k < N ; k++){
        printf("%d, ",array[k]);
    }
}


int my_rand1(int base, int range){ // base + ( 1 ~ N )
    int rand_value = rand() % range + base + 1 ;
    return rand_value;
}
int my_rand2(int base, int range){ //  base + ( 0 ~ N )
    int rand_value = rand() % (range+1) + base  ;
    return rand_value;
}

void swap(int *this, int *that){
    int temp = *this;
    *this = *that;
    *that = temp;
}


/*
 * time_t startTime = clock();
 * time_t endTime = (float)(clock-startTime)/(CLOCKS_PER_SEC);
 *
 * File *fp = fopen("~~.csv","w+");
 * fprintf(fp,"%d,",array[k]);
 * fprintf(fp,"\n");
 * */