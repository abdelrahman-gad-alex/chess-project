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
                    { '-' , 'K' , 'N' , '.' , '-' , '.' , '-' , 'B' },
                    { '.' , '-' , 'P' , '-' , '.' , '-' , '.' , '-' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , 'P' , '.' , '-' , '.' , '-' , 'R' , '-' },
                    { '-' , '.' , '-' , 'k' , '-' , '.' , 'n' , '.' },
                    { '.' , '-' , '.' , '-' , '.' , 'Q' , '.' , '-' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , 'q' , '.' , '-' , '.' , '-' , '.' , '-' }};


void CheckCastling();
int CheckMovement(int movej, int movei,int movefj, int movefi, char piece,char pro) ;

int checked(char p) ;
int tempMoveCheck(char p, int movej, int movei,int movefj, int movefi) ;
int checkmate(char p) ;





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
        *x=1;
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
    char piece = 'w';
    printBoard();
    CheckCastling();

    printf("Enter Move \n");
    inputCheck(&x,&movei,&movej,&movefi,&movefj,piece);

    if (x==0){
        movement ( movej,  movei, movefj,  movefi );
        printBoard();

}
}


/*
int main()
{

    int r ;
    if (checked('w')){
        r= checkmate('w') ;
    }
    printf("%d",r) ;

    return 0;
}
*/
