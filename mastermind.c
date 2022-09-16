#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void genPegs(int* mast, int* plater,int* pegs);
void printArr(int arr[], int arrLen);

void printArr(int arr[], int arrLen){
    for (int i = 0; i < arrLen; i++){
       printf("%d ", arr[i]);
    }
    printf("\n");
    
}

void genPegs(int mast[], int player[], int* pegs){
    int black = 0;
    int white = 0;
    int playerCpy[4];
    int mastCpy[4];
    for (int i = 0; i < 4; i++){
        playerCpy[i] = player[i];
        mastCpy[i] = mast[i];
    }
    
    for (int i = 0; i < 4; i++){
        if (playerCpy[i] == mastCpy[i] && playerCpy[i] != 0){
            black ++;
            mastCpy[i] = 0;
            playerCpy[i] = 0;
        }
    }

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (playerCpy[i] == mastCpy[j] && playerCpy[i] != 0){
                white ++;
                playerCpy[i] = 0;
                mastCpy[j] = 0;
            }
        }
    }

    *(pegs) = black;
    *(pegs + 1) = white;
}

void genMaster(int* arr){
    int num;
    for (int i = 0; i < 4; i++){
        num = (rand() % 5) + 1;
        *(arr + i) = num;
    }
}

void genPlayer(int*arr){
    int num = 0;
    printf("Enter your numbers 1 by 1 ");
    for (int i = 0; i < 4; i++){
        scanf("%d", &num);
        if (num >= 1 && num <=6){
             *(arr + i) = num;
        }else{
            printf("Enter num bet 1-6\n");
            i--;
        }  
    }    
}


void incAttempts(int* player, int* pegs, int* attempts){
    for (int i = 0; i < 4; i++){
        *(attempts + i) = *(player + i);
    }
    for (int i = 0; i < 2; i++){
        *(attempts + 4 + i) = *(pegs + i);
    }
}

void printAttempts(int tries, int*attempts){
    for (int i = 0; i < tries; i++){
        for (int i = 0; i < 6; i++){
            if (i == 4){
                printf(" | ");
            }
            printf("%d ",*(attempts + i));
        }
        attempts += 6;
        printf("\n");
    } 
}

//numbers go 1-6
int main(){
    srand(time(0));
    int tries = 0;
    int attempts[6][8];
    int player[4];
    int master[4] = {2,1,1,1};
    int peg[2];
    int* attemptsPtr = &attempts[0][0];
    genMaster(&master[0]);
    while(1){
        printAttempts(tries,&attempts[0][0]);
        genPlayer(&player[0]);
        genPegs(master,player,&peg[0]);
        incAttempts(&player[0], &peg[0],attemptsPtr);
       
        if (peg[0] == 4){
            break;
        }
        
        tries ++;
        attemptsPtr += 6;
    }

    printf("Correct!!, guessed in %d tries",tries);
    
}