#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void play(int bet)
{
    char c[3] = {'j', 'k', 'q'};
    printf("Shuffling ...\n");
    srand(time(NULL));
    int i;
    for (i = 0; i < 5; i++)
    {

        int x = rand() % 3;
        int y = rand() % 3;
        int temp = c[x];
        c[x] = c[y];
        c[y] = temp; // swap character at position x and y
    }
    int playersGuess;
    printf("What's the position of queen -1, 2 or 3?");
    scanf("%d", &playersGuess);
    if(c[playersGuess - 1]=='q') {
        cash += 3*bet;
        printf("You Win !!! result = %c%c%c Total Cash= %d", c[0],c[1],c[2]);
    }
    else{
        cash -= bet;
    }
}

int cash =100;
int main(){
    int bet;
    while (cash > 0) {
        printf("What's your bet? $");
        scanf("%d", bet);
    }
}