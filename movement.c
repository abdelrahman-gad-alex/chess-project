#include <stdio.h>
#include <stdlib.h>
int Rl=0;
int Rr=0;
int rl=0;
int rr=0;

char board[8][8];


void movement (int movej, int movei,int movefj, int movefi,char board[8][8])
{
char temp=board[movej][movei];
if ((movei+movej)%2==0){
    board[movej][movei]='-';
}
else{
    board[movej][movei]='.';
}
board[movefj][movefi]=temp;

}


int CheckRook(int movej, int movei,int movefj, int movefi,char board[8][8],char r )
{
int i,j;
int x=1;
if (r=='r'||r=='R'){
    if(movefi==movei||movefj==movej){
            if (movei < movefi&&movej==movefj){
                for (i=movei+1;i<movefi;i++){
                        if((board[movej][i]>='a'&&board[movej][i]<='z')||(board[movej][i]>='A'&&board[movej][i]<='Z')){
                            x=0 ;

                        }
                    }
                }
            else if (movei > movefi&&movej==movefj){
                for (i=movei-1;i>movefi;i--){
                        if((board[movej][i]>='a'&&board[movej][i]<='z')||(board[movej][i]>='A'&&board[movej][i]<='Z')){
                            x=0 ;


                        }
                    }
                }

            else if (movei == movefi&&movej>movefj){
                    for (j=movej-1;j>movefj;j--){
                        if((board[j][movei]>='a'&&board[j][movei]<='z')||(board[j][movei]>='A'&&board[j][movei]<='Z')){
                            x=0 ;

                        }
                    }
                }
            else if (movei == movefi&&movej<movefj){
                    for (j=movej+1;j<movefj;j++){
                        if((board[j][movei]>='a'&&board[j][movei]<='z')||(board[j][movei]>='A'&&board[j][movei]<='Z')){
                            x=0 ;

                        }
                    }
                }

}
else {
    x=0;
}
}

return x;
}




int Checkknight(int movej, int movei,int movefj, int movefi,char board[8][8],char n )
{
int x=1;
if (n=='n'||n=='N'){
    if ((movefi == movei + 2 &&movefj == movej+1)||(movefi == movei + 2 &&movefj == movej-1)||(movefi == movei - 2 &&movefj == movej+1)||(movefi == movei - 2 &&movefj == movej-1))
    {
        x=1;
    }
    else if ((movefj == movej + 2 &&movefi == movei+1)||(movefj == movej + 2 &&movefi == movei-1)||(movefj == movej - 2 &&movefi == movei+1)||(movefj == movej - 2 &&movefi == movei-1))
    {
        x=1;
    }
    else{
        x=0;
    }


}
return x;
}

int CheckBishop(int movej, int movei,int movefj, int movefi,char board[8][8],char b )
{
int i;
int x=1;
if (b=='b'||b=='B'){
    if (abs(movefi-movei)==abs(movefj-movej)){
        if (movefi > movei && movefj > movej){
            for (i=1;i<(movefi-movei);i++){
                if ((board[movej+i][movei+i]>'a'&&board[movej+i][movei+i]<'z')||(board[movej+i][movei+i]>'a'&&board[movej+i][movei+i]<'z')){
                x=0;
                }
            }
        }
        else if (movefi < movei && movefj>movej){
            for (i=1;i<(movei-movefi);i++){
                if ((board[movej+i][movei-i]>'a'&&board[movej+i][movei-i]<'z')||(board[movej-i][movei+i]>'A'&&board[movej-i][movei+i]<'Z')){
                x=0;
                }
            }
        }
        else if (movefi > movei && movefj < movej){
            for (i=1;i<(movefi-movei);i++){
                if ((board[movej-i][movei+i]>'a'&&board[movej-i][movei+i]<'z')||(board[movej-i][movei+i]>'A'&&board[movej-i][movei+i]<'Z')){
                x=0;
                }
            }
        }
        else if (movefi < movei && movefj < movej){
            for (i=1;i<(movei-movefi);i++){
                if ((board[movej-i][movei-i]>'a'&&board[movej-i][movei-i]<'z')||(board[movej-i][movei-i]>'A'&&board[movej-i][movei-i]<'Z')){
                x=0;
                }
            }
        }
    }
    else{
        x=0;
    }
}

return x;
}

int CheckKing(int movej, int movei,int movefj, int movefi,char board[8][8],char k )
{
int x=1;
if (k=='k'||k=='K'){
    if (abs(movefi-movei)<=1&&abs(movefj-movej)<=1){
        x=1;
    }
    else if((((k=='k')&&(~rl))||((k=='K')&&(~Rl)))&&(movej==movefj&&movefi==2)){
            x=1;
            for (int i=3;i>0;i-- ){
                if ((board[movej][i]>'a'&&board[movej][i]<'z')||(board[movej][i]>'A'&&board[movej][i]<'Z')){
                        x=0;
    }}
    if (x==1){
    movement(movej,0,movefj,3,board);
    }
    }
    else if((((k=='k')&&(~rr))||((k=='K')&&(~Rr)))&&(movej==movefj&&movefi==6)){
            x=1;

            for (int i=6;i>4;i-- ){
                if ((board[movej][i]>'a'&&board[movej][i]<'z')||(board[movej][i]>'A'&&board[movej][i]<'Z')){
                        x=0;
    }}
    if (x==1){
    movement(movej,7,movefj,5,board);
    }
    }

    else{
        x=0;
    }
}

return x;

}


int CheckQueen(int movej, int movei,int movefj, int movefi,char board[8][8],char q)
{
int i,j;
int x=1;
if (q=='q'||q=='Q'){
    if (abs(movefi-movei)<=1&&abs(movefj-movej)<=1){
        x=1;
    }
    else if (abs(movefi-movei)==abs(movefj-movej)){
        if (movefi > movei && movefj > movej){
            for (i=1;i<(movefi-movei);i++){
                if ((board[movej+i][movei+i]>'a'&&board[movej+i][movei+i]<'z')||(board[movej+i][movei+i]>'A'&&board[movej+i][movei+i]<'Z')){
                x=0;
                }
            }
        }
        else if (movefi < movei && movefj>movej){
            for (i=1;i<(movei-movefi);i++){
                if ((board[movej+i][movei-i]>'a'&&board[movej+i][movei-i]<'z')||(board[movej+i][movei-i]>'A'&&board[movej+i][movei-i]<'Z')){
                x=0;
                }
            }
        }
        else if (movefi > movei && movefj < movej){
            for (i=1;i<(movefi-movei);i++){
                if ((board[movej-i][movei+i]>'a'&&board[movej-i][movei+i]<'z')||(board[movej-i][movei+i]>'A'&&board[movej-i][movei+i]<'Z')){
                x=0;
                }
            }
        }
        else if (movefi < movei && movefj < movej){
            for (i=1;i<(movei-movefi);i++){
                if ((board[movej-i][movei-i]>'a'&&board[movej-i][movei-i]<'z')||(board[movej-i][movei-i]>'A'&&board[movej-i][movei-i]<'Z')){
                x=0;
                }
            }
        }
    }
    else if(movefi==movei||movefj==movej){
        if (movei < movefi&&movej==movefj){
                for (i=movei+1;i<movefi;i++){
                        if((board[movej][i]>='a'&&board[movej][i]<='z')||(board[movej][i]>='A'&&board[movej][i]<='Z')){
                            x=0 ;

                        }
                    }
                }
        else if (movei > movefi&&movej==movefj){
                for (i=movei-1;i>movefi;i--){
                        if((board[movej][i]>='a'&&board[movej][i]<='z')||(board[movej][i]>='A'&&board[movej][i]<='Z')){
                            x=0 ;


                        }
                    }
                }

        else if (movei == movefi&&movej>movefj){
                    for (j=movej-1;j>movefj;j--){
                        if((board[j][movei]>='a'&&board[j][movei]<='z')||(board[j][movei]>='A'&&board[j][movei]<='Z')){
                            x=0 ;

                        }
                    }
                }
        else if (movei == movefi&&movej<movefj){
                    for (j=movej+1;j<movefj;j++){
                        if((board[j][movei]>='a'&&board[j][movei]<='z')||(board[j][movei]>='A'&&board[j][movei]<='Z')){
                            x=0 ;

                        }
                    }
                }

        }
    else{
        x=0;
    }




}

return x;
}


int CheckPawnW(int movej, int movei,int movefj, int movefi,char board[8][8],char p,char pro)
{

int x=1;
if (p=='p'){
    if (movei==movefi&&(movej-movefj)==1&&movefj!=0){
        x=1;
    }
    else if ((movej-movefj)==1&&abs(movei-movefi)==1&&board[movefj][movefi]>'A'&&board[movefj][movefi]<'Z'){
        x=1;
    }
    else if (movej == 6 && movefj== 4){
        x=1;
    }
    else if (movefj==0&&pro !='\0'){
        x=1;
        if (pro>'A'&&pro<'Z'){
        board[movej][movei]=pro+32;
    }
    else{
        board[movej][movei]=pro;

    }
    }
    else{
    x=0;
}

}
  return x ;
}

int CheckPawnB(int movej, int movei,int movefj, int movefi,char board[8][8],char p,char pro)
{
int x=1;
if (p=='P'){
    if (movei==movefi&&(movefj-movej)==1&&movefj!=7){
        x=1;
    }
    else if ((movefj-movej)==1&&abs(movei-movefi)==1&&board[movefj][movefi]>'a'&&board[movefj][movefi]<'z'){
        x=1;
    }
    else if (movej == 1 && movefj== 3){
        x=1;
    }
    else if (movefj==7&&pro !='\0'){
    x=1;
        if (pro>'a'&&pro<'z'){
        board[movej][movei]=pro-32;
    }
    else{
        board[movej][movei]=pro;

    }
    }

    else{
    x=0;
}

}
  return x ;
}





int CheckMovement(int movej, int movei,int movefj, int movefi, char piece,char pro)
{

    int x;
    x=0;
if (piece == 'w'){

if(((board[movefj][movefi]>'A'&&board[movefj][movefi]<'Z')||board[movefj][movefi]=='.'||board[movefj][movefi]=='-')&&(board[movej][movei]>'a'&&board[movej][movei]<'z')){
switch(board[movej][movei])
{
    case 'p':
    x=CheckPawnW(movej,  movei, movefj,  movefi, board, board[movej][movei],pro);
    break ;
    case 'r':
    x=CheckRook(movej,  movei, movefj,  movefi, board, board[movej][movei]);
    break ;
    case 'n':
    x=Checkknight(movej,  movei, movefj,  movefi, board, board[movej][movei]);
    break ;
    case 'b':
    x=CheckBishop(movej,  movei, movefj,  movefi, board, board[movej][movei]);
    break ;
    case 'k':
    x=CheckKing(movej,  movei, movefj,  movefi, board, board[movej][movei]);
    break ;
    case 'q':
    x=CheckQueen(movej,  movei, movefj,  movefi, board, board[movej][movei]);
    break ;
    default:
    x=0;
}
}
return x;

}
else if (piece == 'b'){

if(((board[movefj][movefi]>'a'&&board[movefj][movefi]<'z')||board[movefj][movefi]=='.'||board[movefj][movefi]=='-')&&(board[movej][movei]>'A'&&board[movej][movei]<'Z')){
switch(board[movej][movei])
{
    case 'P':
    x=CheckPawnB(movej,  movei, movefj,  movefi, board, board[movej][movei],pro);
    break ;
    case 'R':
    x=CheckRook(movej,  movei, movefj,  movefi, board, board[movej][movei]);
    break ;
    case 'N':
    x=Checkknight(movej,  movei, movefj,  movefi, board, board[movej][movei]);
    break ;
    case 'B':
    x=CheckBishop(movej,  movei, movefj,  movefi, board, board[movej][movei]);
    break ;
    case 'K':
    x=CheckKing(movej,  movei, movefj,  movefi, board, board[movej][movei]);
    break ;
    case 'Q':
    x=CheckQueen(movej,  movei, movefj,  movefi, board, board[movej][movei]);
    break ;
    default:
    x=0;
}
}
return x;

}
    else{
    return 0;
    }
}

void CheckCastling()
{

if (board[0][0]!='R'){
    Rl=1;
}
if (board[0][7]!='R'){
    Rr=1;
}
if (board[7][0]!='r'){
    rl=1;
}
if (board[7][7]!='r'){
    rr=1;
}
if (board[0][4]!='K'){
    Rr=1;
    Rl=1;
}
if (board[7][4]!='k'){
    rr=1;
    rl=1;
}
}













/*

int main()
{
int i,j,movei,movej, movefi,movefj;
char move[5];
char piece = 'w';

for (i=0;i<8;i++){
    for (j=0;j<8;j++){
        printf(" %c ," ,board[i][j]);
        if (j==7){
            printf("\n");
        }
    }
}
CheckCastling();

printf("Enter Move \n");

while (1){
    gets(move);

switch(move[0])
{
    case 'a':
        movei=0;
        break;
    case 'b':
        movei=1;
        break;
    case 'c':
        movei=2;
        break;
    case 'd':
        movei=3;
        break;
    case 'e':
        movei=4;
        break;
    case 'f':
        movei=5;
        break;
    case 'g':
        movei=6;
        break;
    case 'h':
        movei=7;
        break;
    case 'A':
        movei=0;
        break;
    case 'B':
        movei=1;
        break;
    case 'C':
        movei=2;
        break;
    case 'D':
        movei=3;
        break;
    case 'E':
        movei=4;
        break;
    case 'F':
        movei=5;
        break;
    case 'G':
        movei=6;
        break;
    case 'H':
        movei=7;
        break;
}

movej=(move[1]-'0')-1;

switch(move[2])
{
    case 'a':
        movefi=0;
        break;
    case 'b':
        movefi=1;
        break;
    case 'c':
        movefi=2;
        break;
    case 'd':
        movefi=3;
        break;
    case 'e':
        movefi=4;
        break;
    case 'f':
        movefi=5;
        break;
    case 'g':
        movefi=6;
        break;
    case 'h':
        movefi=7;
        break;
    case 'A':
        movefi=0;
        break;
    case 'B':
        movefi=1;
        break;
    case 'C':
        movefi=2;
        break;
    case 'D':
        movefi=3;
        break;
    case 'E':
        movefi=4;
        break;
    case 'F':
        movefi=5;
        break;
    case 'G':
        movefi=6;
        break;
    case 'H':
        movefi=7;
        break;
}
movefj=(move[3]-'0')-1;




    if ((((move[0]<='h'&& move[0]>='a')||(move[0]<='H'&& move[0]>='A'))&&(move[1]-'0')<9&& (move[1]-'0')>0&&((move[2]<='h'&& move[2]>='a')||(move[2]<='H'&& move[2]>='A'))&&(move[3]-'0')<9&& (move[3]-'0')>0)&&(move[0]!=move[2]||(move[1]-'0')!=(move[3]-'0'))&&(move[4]=='N'||move[4]=='R'||move[4]=='B'||move[4]=='Q'||move[4]=='n'||move[4]=='r'||move[4]=='b'||move[4]=='q'||move[4]=='\0')){
        if (CheckMovement( movej,  movei, movefj,  movefi ,piece ,move[4])){
            break;
        }
    printf("Enter Move Correctly\n");
        }
    else{
    printf("Enter Move Correctly\n");
    }
}


movement ( movej,  movei, movefj,  movefi, board);

for (i=0;i<8;i++){
    for (j=0;j<8;j++){
        printf(" %c ," ,board[i][j]);
        if (j==7){
            printf("\n");
        }
    }
}
}
*/


