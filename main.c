#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
/*
                    { 'R' , 'N' , 'B' , 'Q' , 'K' , 'B' , 'N' , 'R' },
                    { 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
                    { 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' },
                    { 'r' , 'n' , 'b' , 'q' , 'k' , 'b' , 'n' , 'r' }};
*/



char board[8][8] = {
                    { '-' , 'N' , 'B' , '.' , 'K' , 'B' , 'N' , 'R' },
                    { 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
                    { '-' , '.' , '-' , 'R' , '-' , '.' , '-' , '.' },
                    { '.' , '-' , '.' , '-' , '.' , 'Q' , '.' , '-' },
                    { 'p' , 'p' , 'p' , 'p' , '-' , '.' , 'p' , 'p' },
                    { 'r' , 'n' , 'b' , '-' , 'k' , '-' , '.' , 'r' }};


void CheckCastling();
int CheckMovement(int movej, int movei,int movefj, int movefi, char piece,char pro) ;

int checked(char p) ;
int tempMoveCheck(char p, int movej, int movei,int movefj, int movefi,char pro) ;
int checkmate(char p) ;
int stalemate(char p);

void storemove(char p, int ifchecked , char startorPlay);
int undoRedo(char unRedo, char *p, int *ifchecked);

void save(char piece);
void load(char *piece);


void printstored();

void printBoard()
{

for (int i=0;i<8;i++){
    for (int j=0;j<8;j++){
        printf(" %c ," ,board[i][j]);
        if (j==7){
            printf("\n");
        }
    }
}
}


int main(){
    char sl[5];
    int exit=0;
    int ifchecked ;
    int movei=0,movej=0, movefi=0,movefj=0,x=0;
    char piece = 'w';
    char o = 'b';
    printf("(start/load)\nMake Your Choice\n");
    while(1){
    gets(sl);
    if(sl[0]=='l'&&sl[1]=='o'&&sl[2]=='a'&&sl[3]=='d'&&sl[4]=='\0'){
        load(&piece);
    if (piece=='b'){
        o = 'w';
    }
        break;
    }
    else if(sl[0]=='s'&&sl[1]=='t'&&sl[2]=='a'&&sl[3]=='r'&&sl[4]=='t'&&sl[5]=='\0'){
        break;
    }
    printf("(start/load)\nMake Your Choice correctly %c\n",7);

    }


    ifchecked = checked(piece);
    storemove(piece, ifchecked, 's') ;






while (!exit){
    printBoard();
    CheckCastling();
    if (ifchecked){
        printf("check!!\n");
    }
/////////////////input check///////////

    printf("\nEnter Move \n");
        char move[5];
    while (1){

    gets(move);
    movei=(tolower(move[0])-'a');
    movej=('8'-move[1]);
    movefi=(tolower(move[2])-'a');
    movefj=('8'-move[3]);

    if (((tolower(move[0])<='h'&& tolower(move[0])>='a')&&(move[1]-'0')<9&& (move[1]-'0')>0&&(tolower(move[2])<='h'&& tolower(move[2])>='a')&&(move[3]-'0')<9&& (move[3]-'0')>0)&&(move[0]!=move[2]||(move[1]-'0')!=(move[3]-'0'))&&(tolower(move[4])=='n'||tolower(move[4])=='r'||tolower(move[4])=='b'||tolower(move[4])=='q'||move[4]=='\0')){

        if (!tempMoveCheck(piece, movej,movei,movefj, movefi,move[4])){

            if (CheckMovement( movej,  movei, movefj,  movefi ,piece ,move[4])){
            x=1;
            break;
        }

        }
    printf("Enter Move Correctly\n");
        }
    else if(move[0]=='s'&&move[1]=='a'&&move[2]=='v'&&move[3]=='e'&&move[4]=='\0'){
        save(piece);
        char t[1];
        while(1){
            printf("Continue(Y/N):");
            gets(t);
            if (tolower(t[0])=='y'){
                exit=0;
                x=0;
                break;
                }
            if (tolower(t[0])=='n'){
                exit=1;
                x=0;
                break;
                }
            }
        break;
    }
    else if(move[0]=='u'&&move[1]=='n'&&move[2]=='d'&&move[3]=='o'&&move[4]=='\0'){
    ////////////////////////////////////

    x=0;
    }
    else if(move[0]=='r'&&move[1]=='e'&&move[2]=='d'&&move[3]=='o'&&move[4]=='\0'){
//////////////////////////////////////////


    x=0;
    }
    else{
    printf("Enter Move Correctly\n");
    }
}
////////////end of input check////////////////

if (x){

movement ( movej, movei, movefj, movefi );



if(checked(o)){
    if(checkmate(o)){
        printf("Check Mate!\n");
        if (o=='w'){
            printf ("Black Wins!\n");
            }
        else{
            printf ("White Wins!\n");
            }
        exit=1;
    }else{
    ifchecked=1;
    }
}
else if (stalemate(o)){
            printf("Draw\n");
            exit=1;
}
else{
    ifchecked=0;

}


        storemove(piece, ifchecked, 'p') ;
    if (piece=='w'){
        piece='b';
        o = 'w';
    }
    else{
        piece='w';
        o = 'b';
    }

}

}
}


/*
int main()
{
    int r ;
    if(checked('w')){
        printf("check\n") ;
        if(checkmate('w')){
            printf("checkmate\n");
        }
    }else if (stalemate('w')){
        printf("stalemate\n");
    }

    return 0;
}
*/
