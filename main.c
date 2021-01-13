#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
int R[4]={0,0,0,0};
int pw[8]={0,0,0,0,0,0,0,0};
int pb[8]={0,0,0,0,0,0,0,0};
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
                    { '-' , 'K' , '.' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , '-' , '-' , '-' , '.' , '-' , '.' , '-' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , '-' , 'Q' , 'B' , 'B' , '.' , '.' , '-' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '.' , '.' },
                    { '.' , '-' , 'p' , '.' , '.' , '-' , '.' , '-' },
                    { '-' , 'k' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { 'b' , '-' , '.' , 'Q' , '.' , '-' , '.' , '.' }};


void CheckCastling();
int CheckMovement(int movej, int movei,int movefj, int movefi, char piece,char pro) ;

int checked(char p) ;
int tempMoveCheck(char p, int movej, int movei,int movefj, int movefi) ;
int checkmate(char p) ;
int stalemate(char p);

void storemove(char p, int ifchecked , char startorPlay);
void save();
void load();


void printstored();


void inputCheck(int *x,int *movei,int *movej,int *movefi,int *movefj,char piece){
    char move[5];
    while (1){

    gets(move);
    *movei=(tolower(move[0])-'a');
    *movej=(move[1]-'0')-1;
    *movefi=(tolower(move[2])-'a');
    *movefj=(move[3]-'0')-1;
    if (((tolower(move[0])<='h'&& tolower(move[0])>='a')&&(move[1]-'0')<9&& (move[1]-'0')>0&&(tolower(move[2])<='h'&& tolower(move[2])>='a')&&(move[3]-'0')<9&& (move[3]-'0')>0)&&(move[0]!=move[2]||(move[1]-'0')!=(move[3]-'0'))&&(tolower(move[4])=='n'||tolower(move[4])=='r'||tolower(move[4])=='b'||tolower(move[4])=='q'||move[4]=='\0')){
        if (CheckMovement( *movej,  *movei, *movefj,  *movefi ,piece ,move[4])){

            break;
        }
    printf("Enter Move Correctly\n");
        }
    else if(move[0]=='s'&&move[1]=='a'&&move[2]=='v'&&move[3]=='e'&&move[4]=='\0'){
        save();
        char t[1];
        while(1){
            printf("Continue(Y/N):");
            gets(t);
            if (tolower(t[0])=='y'){
                *x=0;
                break;
                }
            if (tolower(t[0])=='n'){
                *x=1;
                break;
                }
            }
        break;
    }
    else if(move[0]=='l'&&move[1]=='o'&&move[2]=='a'&&move[3]=='d'&&move[4]=='\0'){
        load();
        *x=0;
        break;
    }
    else{
    printf("Enter Move Correctly\n");
    }
}
}

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
    int movei,movej, movefi,movefj,x=0;
    char piece = 'b';
    printBoard();
    CheckCastling();
    int ifchecked ;

    printf("Enter Move \n");
    inputCheck(&x,&movei,&movej,&movefi,&movefj,piece);

    if (x==0){
        printf("before move\n") ;
        storemove(piece, ifchecked, 's') ;
        printf("after store\n") ;
        printstored() ;
        movement ( movej,  movei, movefj,  movefi );

        storemove(piece, ifchecked, 'p') ;
        printstored() ;
        //printBoard();

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
