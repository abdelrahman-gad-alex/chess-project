#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int Rl=0;
int Rr=0;
int rl=0;
int rr=0;

char board[8][8] ;


void movement (int movej, int movei,int movefj, int movefi)
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


int CheckRook(int movej, int movei,int movefj, int movefi, char pro)
{
int i,j;
int x=1;
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
if(pro !='\0'){
    x=0;
}

return x;
}




int Checkknight(int movej, int movei,int movefj, int movefi, char pro)
{
int x=1;
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
if(pro !='\0'){
    x=0;
}


return x;
}

int CheckBishop(int movej, int movei,int movefj, int movefi, char pro)
{
int i;
int x=1;
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
if(pro !='\0'){
    x=0;
}

return x;
}

int CheckKing(int movej, int movei,int movefj, int movefi, char pro)
{
int x=1;
    if (abs(movefi-movei)<=1&&abs(movefj-movej)<=1){
        x=1;
    }
    else if(((~rl)||(~Rl))&&(movej==movefj&&movefi==2)){
            x=1;
            for (int i=3;i>0;i-- ){
                if ((board[movej][i]>'a'&&board[movej][i]<'z')||(board[movej][i]>'A'&&board[movej][i]<'Z')){
                        x=0;
    }}
    if (x==1){
    movement(movej,0,movefj,3);
    }
    }
    else if(((~rr)||(~Rr))&&(movej==movefj&&movefi==6)){
            x=1;

            for (int i=6;i>4;i-- ){
                if ((board[movej][i]>'a'&&board[movej][i]<'z')||(board[movej][i]>'A'&&board[movej][i]<'Z')){
                        x=0;
    }}
    if (x==1){
    movement(movej,7,movefj,5);
    }
    }

    else{
        x=0;
    }

if(pro !='\0'){
    x=0;
}

return x;

}


int CheckQueen(int movej, int movei,int movefj, int movefi, char pro)
{
int i,j;
int x=1;
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

if(pro !='\0'){
    x=0;
}


return x;
}


int CheckPawnW(int movej, int movei,int movefj, int movefi,char pro)
{

int x=1;
    if (movei==movefi&&(movej-movefj)==1&&movefj!=0&&pro=='\0'){
        x=1;
    }
    else if ((movej-movefj)==1&&abs(movei-movefi)==1&&board[movefj][movefi]>'A'&&board[movefj][movefi]<'Z'){
            if (movefj==0&&pro !='\0'){
        x=1;
        board[movej][movei]=tolower(pro);
    }
     else if (movefj==0&&pro =='\0'){
        x=0;
    }
    else{
        x=1;
    }}
    else if (movej == 6 && movefj== 4){
        x=1;
    }
    else if (movefj==0&&pro !='\0'){
        x=1;
        board[movej][movei]=tolower(pro);
    }
    else{
    x=0;
}


  return x ;
}

int CheckPawnB(int movej, int movei,int movefj, int movefi,char pro)
{
int x=1;
    if (movei==movefi&&(movefj-movej)==1&&movefj!=7&&pro=='\0'){
        x=1;
    }
    else if ((movefj-movej)==1&&abs(movei-movefi)==1&&board[movefj][movefi]>'a'&&board[movefj][movefi]<'z'){
            if (movefj==7&&pro !='\0'){
        x=1;
        board[movej][movei]=toupper(pro);
    }
     else if (movefj==7&&pro =='\0'){
        x=0;
    }
    else{
        x=1;
    }}
    else if (movej == 1 && movefj== 3){
        x=1;
    }
    else if (movefj==7&&pro !='\0'){
    x=1;
        board[movej][movei]=toupper(pro);
    }

    else{
    x=0;
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
                x=CheckPawnW(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'r':
                x=CheckRook(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'n':
                x=Checkknight(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'b':
                x=CheckBishop(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'k':
                x=CheckKing(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'q':
                x=CheckQueen(movej,  movei, movefj,  movefi, pro);
                break ;
                default:
                x=0;
            }
        }
        return x;

    }else if (piece == 'b'){

        if(((board[movefj][movefi]>'a'&&board[movefj][movefi]<'z')||board[movefj][movefi]=='.'||board[movefj][movefi]=='-')&&(board[movej][movei]>'A'&&board[movej][movei]<'Z')){
        switch(board[movej][movei])
        {
            case 'P':
            x=CheckPawnB(movej,  movei, movefj,  movefi, pro);
            break ;
            case 'R':
            x=CheckRook(movej,  movei, movefj,  movefi, pro);
            break ;
            case 'N':
            x=Checkknight(movej,  movei, movefj,  movefi, pro);
            break ;
            case 'B':
            x=CheckBishop(movej,  movei, movefj,  movefi, pro);
            break ;
            case 'K':
            x=CheckKing(movej,  movei, movefj,  movefi, pro);
            break ;
            case 'Q':
            x=CheckQueen(movej,  movei, movefj,  movefi, pro);
            break ;
            default:
            x=0;
        }
        }
        return x;

    }else{
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






