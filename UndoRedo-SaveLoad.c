#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <ctype.h>

char board[8][8] ;

int R[4]={0,0,0,0};  // Mentooooo !!!!!
int pw[8]={0,0,0,0,0,0,0,0};
int pb[8]={0,0,0,0,0,0,0,0};
struct died
{
	char die[15];
    int counter ;
}wdied,bdied;


// Undo and Redo part
struct node
{
	char chess[8][8];  // the chess board
	char player ;
    int R[4];
    int pw[8];
    int pb[8];
    int ifchecked ;  // refer if in this play there are check on the king
    int wdie , bdie ;  // counter of the died pieces
	struct node *next;  // pointer on the next node for redo
	struct node *prev;  // pointer on the previous node for undo
};
struct node *head = NULL;
struct node *current = NULL;
/*
we are using linked lest for that
every node refer to a play
*/



void storemove(char p, int ifchecked, char startorPlay){

    struct node *t;
    t = (struct node*)malloc(sizeof(struct node));  // create the node

    // storing the current data in node
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
        head = t ;  // making it the head(the start of the game) and the current
        current = head ;

    }else if(startorPlay=='p'){ // play in game
        current->next = t ;
        t ->prev = current ;  // making the previous current points to this node
        t ->next = NULL ;
        current = t ;  // making this node is the current
    }
}

int undoRedo(char unRedo, char *p, int *ifchecked){
    // the return value = 1 if can happen and done
    // the return value = 0 if can't happen and did not do it

    if(unRedo=='u'){  // refer to undo
        if(current->prev != NULL){  // check if there a previous for the current first
            current = current->prev ; // make the previous is the current
        }else{
            return 0;  // can't done
        }
    }else if(unRedo=='r'){  // refer to redo
        if(current->next != NULL){  // check if there a next for the current first
            current = current->next ;  // make the next is the current
        }else{
            return 0;   // can't done
        }
    }
    // else if the unRedo = 'c' then it mean that restore the data in current

    // restoring data
    for(int i=0 ; i<8 ; i++){
        for(int j=0 ; j<8 ; j++){
            board[i][j] = current->chess[i][j] ;
    }}

    *p = current->player ;
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


    return 1 ; // it means that the restore is done
}



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

