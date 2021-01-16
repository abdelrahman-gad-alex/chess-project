#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <ctype.h>
struct node
{
	char chess[8][8];
	char player ;
    int R[4];
    int pw[8];
    int pb[8];
    int ifchecked ;
    int wdie , bdie ;
	struct node *next;
	struct node *prev;
};
struct node *head = NULL;
struct node *current = NULL;

struct died
{
	char die[15];
    int counter ;
}wdied,bdied;

char board[8][8] ;

int R[4]={0,0,0,0};
int pw[8]={0,0,0,0,0,0,0,0};
int pb[8]={0,0,0,0,0,0,0,0};

void storemove(char p, int ifchecked, char startorPlay){

    struct node *t;
    t = (struct node*)malloc(sizeof(struct node));

    for(int i=0 ; i<8 ; i++){
        for(int j=0 ; j<8 ; j++){
            t->chess[i][j] = board[i][j] ;
    }}
    for(int i=0 ; i<8 ; i++){
        t->pw[i] = pw[i] ;
        t->pb[i] = pb[i] ;
    }
    for(int i=0 ; i<4 ; i++){
        t->R[i] = R[i] ;
    }
    t->player = p ;
    t->ifchecked = ifchecked ;
    t->wdie = wdied.counter ;
    t->bdie = bdied.counter ;

    if (startorPlay=='s'){  //Start game
        t->next = NULL ;
        t->prev = NULL ;
        head = t ;
        current = head ;

    }else if(startorPlay=='p'){ // play in game
        current->next = t ;
        t ->prev = current ;
        t ->next = NULL ;
        current = t ;
    }
}

int undoRedo(char unRedo, char *p, int *ifchecked){
    if(unRedo=='u'){  // undo
        if(current->prev != NULL){
            current = current->prev ;
        }else{
            return 0;
        }
    }else if(unRedo=='r'){  // redo
        if(current->next != NULL){
            current = current->next ;
        }else{
            return 0;
        }
    }
    for(int i=0 ; i<8 ; i++){
        for(int j=0 ; j<8 ; j++){
            board[i][j] = current->chess[i][j] ;
    }}

    *p = current->player ;
//    printf("%c", current->player) ;
    for(int i=0 ; i<8 ; i++){
        pw[i] = current->pw[i] ;
        pb[i] =current->pb[i] ;
    }
    for(int i=0 ; i<4 ; i++){
        R[i] = current->R[i] ;
    }
    *ifchecked = current->ifchecked ;
    wdied.counter = current->wdie ;
    bdied.counter = current->bdie  ;


    return 1 ;
}

/*
void printstored(){
    printf("%c\n",current->player) ;
    for(int i=0 ; i<8 ; i++){
        for(int j=0 ; j<8 ; j++){
            printf("%c ",current->chess[i][j]) ;
        }
        printf("\n") ;
    }
    for(int i=0 ; i<8 ; i++){
        printf("%d ",current->pw[i]) ;
        printf("%d ",current->pb[i]) ;
    }
    for(int i=0 ; i<4 ; i++){
        printf("%d ",current->R[i]) ;
    }
}
*/



void save(char piece){
char file1[100];
printf("Enter the name of the save file\n");
gets(file1);
FILE *fp;
fp  = fopen (file1, "w");
for (int i=0;i<8;i++){
    for (int j=0;j<8;j++){
        fputc(board[i][j], fp);
        }
    }
for (int i=0;i<4;i++){
    fputc((R[i]+'0'), fp);
}
for (int i=0;i<8;i++){
    fputc((pw[i]+'0'), fp);
}
for (int i=0;i<8;i++){
    fputc((pb[i]+'0'), fp);
}
fputc(piece,fp);
for (int i=0;i<wdied.counter;i++){
    fputc(wdied.die[i],fp);
}
for (int i=0;i<bdied.counter;i++){
    fputc(bdied.die[i],fp);
}

fclose(fp);

}


void load(char *piece){
char c,name[100];
int i=0,j=0;
printf("Enter the name of the load file\n");
FILE *fr;
while (1){
gets(name);
fr=fopen(name,"r");
if (fr){
     break;
}

else{
printf("Not found.\n");
}

}
    while ((c = getc(fr)) != EOF) {
    if(i<8&&j<8){
    (board[i][j]= c);
     j++;
     if (j==8)   {
        i++;
        j=0;
        continue;

     }}
    if(i>=8&&i<12){
        R[i-8]= c-'0';
        i++;
        continue;

        }
    if(i>=12&&i<20){
        pw[i-12]= c-'0';
        i++;
        continue;

        }
    if(i>=20&&i<28){
        pb[i-20]= c-'0';
        i++;
        continue;
        }
    if (i==28){
        *piece=c;
        i++;
        continue;

    }
    if(i==29&&islower(c)){
        wdied.die[wdied.counter]=c;
        wdied.counter++;
        continue;
    }
    if(i==29&&isupper(c)){
        bdied.die[bdied.counter]=c;
        bdied.counter++;
        continue;

    }
}
    fclose(fr);

}

