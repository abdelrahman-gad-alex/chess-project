#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <ctype.h>
struct node
{
	char chess[8][8];
	char player ;
	int Rl;
    int Rr;
    int rl;
    int rr;
    int ifchecked ;
	struct node *next;
	struct node *prev;
};
struct node *head = NULL;
struct node *current = NULL;


char board[8][8] ;
int Rl;
int Rr;
int rl;
int rr;
int R[4];
int pw[8];
int pb[8];

void storemove(char p, int ifchecked, char startorPlay){

    struct node *t;
    t = (struct node*)malloc(sizeof(struct node));
    printf("create node\n") ;

    for(int i=0 ; i<8 ; i++){
        for(int j=0 ; j<8 ; j++){
            t->chess[i][j] = board[i][j] ;
    }}
    t->player = p ;
    t->Rl = Rl ;
    t->rl = rl ;
    t->Rr = Rr ;
    t->rr = rr ;
    t->ifchecked = ifchecked ;
    printf("storing data node\n") ;

    if (startorPlay=='s'){  //Start game
        printf("at if\n") ;
        t->next = NULL ;
        t->prev = NULL ;
        head = t ;
        current = head ;
        printf("after if\n") ;

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
    Rl = current->Rl ;
    rl = current->rl ;
    Rr = current->Rr ;
    rr = current->rr ;
    Rl = current->Rl ;
    *ifchecked = current->ifchecked ;

}


void printstored(){
    printf("%c\n",current->player) ;
    for(int i=0 ; i<8 ; i++){
        for(int j=0 ; j<8 ; j++){
            printf("%c ",current->chess[i][j]) ;
        }
        printf("\n") ;
    }

}




void save(){
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

fclose(fp);

}


void load(){
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
    if(i>=20){
        pb[i-20]= c-'0';
        i++;
        continue;

        }
    }
    fclose(fr);

}

