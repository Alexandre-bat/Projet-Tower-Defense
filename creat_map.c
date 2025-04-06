#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void creat_map(){
    int SIZE, START, END, count=0, n=0,k=0,d=0,l,tmp;
    char SIDE;
    int* path;
    printf("What size do you want for your map ?\n 11-99\n");
    scanf("%d",&SIZE);
    if (SIZE<11 || SIZE>99) {
        printf("erreur 1");
        exit(1);
    }
    printf("In which side is the start on the map ?\n u/d/r/l\n");
    scanf(" %c",&SIDE);
    if ((SIDE!= 'u') && (SIDE!= 'd') && (SIDE!= 'r') && (SIDE!= 'l')){
        printf("erreur 2");
        exit(2);
    }


    // get the size and the side for build the map


    srand(time(NULL));
    START=(SIZE/4)+rand()%(SIZE/2);
    END=(SIZE/4)+rand()%(SIZE/2);
    printf("\n%d %d\n",START, END);
    path=malloc(sizeof(int) * SIZE );
    if (path==NULL){
        printf("erreur 3");
       exit(3);
    }
    if (SIDE=='d'){
        tmp=END;
        END=START;
        START=tmp;
    }
    if (SIDE=='u' || SIDE=='d'){
        while (n<SIZE+1){
           *(path+count)= rand()%3;
           if (*(path+count)==1) {
               n++;
           }
           printf("  %d\n",*(path+count));
           count++;
        }    
    

    
    //generate a random path 
    
    
    printf("O  ");
    for (int i = 1; i < 10; i++){
        printf("%d   ",i);
    }
    for (int i = 10; i < SIZE+1; i++){
        printf("%d  ",i);
    }
    for (int i = 0; i < SIZE-floor(SIZE/3); i++){
    k=0;
     printf("\n%d",i+1);
     for (int j = 1; j < SIZE+1; j++){
        if (i<9 && j==1) {
            printf(" ");
         }
        if (j==START && i==0){
            printf("\033[48;2;153;87;1m    \033[0m"); 
            *(path+i)=0;   
            l=j;
            k=1;
        }
        else if (*(path+i)==1 && k==0 && j==l-2 && *(path+i-1)!=2 && l-(SIZE/10)>2){
            printf("\033[48;2;153;87;1m            \033[0m");
            l = j;
            k = 1;
            j+=2;
        }        
        else if (*(path+i)==2 && j==l && *(path+i-1)!=1 && k==0 && l+(SIZE/10)<SIZE){
            printf("\033[48;2;153;87;1m            \033[0m");
            l=j+2;
            k=1;
            j+=2;
        }
        else if (j==l && k==0){
            printf("\033[48;2;153;87;1m    \033[0m");
            *(path+i)=0;
            k=1;
        }
        else{
            printf("\033[48;2;11;102;11m    \033[0m");
        }
     } 
     printf("  %d  ",*(path+i));
    }
    for (int i = SIZE-floor(SIZE/3); i < SIZE-1; i++){
       k=0;
       printf("\n%d",i+1);
        for (int j = 1; j < SIZE+1; j++){
            if((START%2)!=(END%2) && d==0){
                if (l>END && *(path+i-1)!=2 && j==l-2){
                    printf("\033[48;2;11;102;11m    \033[0m");
                    printf("\033[48;2;153;87;1m        \033[0m");
                    l=j+1;
                    k=1;
                    j+=3;
                    *(path+i)=3; 
                    d=1;
                }
                else if (l<END && *(path+i-1)!=1 && j==l){
                    printf("\033[48;2;153;87;1m        \033[0m");
                    l=j+1;
                    k=1;
                    j+=2; 
                    *(path+i)=4;
                    d=1;
                }    
            }
            if (l>END && *(path+i-1)!=2 && *(path+i-1)!=4 && j==l-2 && k==0){
                printf("\033[48;2;153;87;1m            \033[0m");
                l=j;
                k=1;
                j+=2;
                *(path+i)=1;
            }
            else if (l<END && *(path+i-1)!=1 && *(path+i-1)!=3 && j==l && k==0){
                printf("\033[48;2;153;87;1m            \033[0m");
                l=j+2;
                k=1;
                j+=2;
                *(path+i)=2;
            }
            else if (j==l && k==0){
                printf("\033[48;2;153;87;1m    \033[0m");
                *(path+i)=0;
                k=1;
            }
            else{
                printf("\033[48;2;11;102;11m    \033[0m");
            }
        }
    printf("  %d  ",*(path+i));
    }
    if (l!=END){
        printf("erreur 4");
        exit(4);
    }
    printf ("\n%d", SIZE);
    for (int j = 1; j < SIZE+1; j++){
        if (j==l){
            printf("\033[48;2;153;87;1m    \033[0m");
        }
        else {
            printf("\033[48;2;11;102;11m    \033[0m");
        }
    }
    }
}

//build the first map with the data