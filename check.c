#include<stdio.h>
#include<conio.h>
#include <stdlib.h>


int CheckMovement(int movej, int movei,int movefj, int movefi, char piece,char pro);
void movement (int movej, int movei,int movefj, int movefi,char board[8][8]) ;

char board[8][8] ;


struct pieces{
    int k[2] ;
    int places[16][2] ;
    int NOp ;
}whitePieces , BlackPieces ;

int checkby[3] = {0,0,0} ;


void storepieces(){
    // put the places in the struct
    whitePieces.NOp = 0 ;
    BlackPieces.NOp = 0 ;

    for (int j=0 ; j<8 ; j++){
        for (int i=0 ; i<8 ; i++){
            if (board[i][j]>= 'a' && board[i][j]<= 'z'){
                if (board[i][j] == 'k'){
                    whitePieces.k[0] = i ;
                    whitePieces.k[1] = j ;
                }
                whitePieces.places[whitePieces.NOp][0] = i ;
                whitePieces.places[whitePieces.NOp][1] = j ;
                whitePieces.NOp ++ ;

            }else if(board[i][j]>= 'A' && board[i][j]<= 'Z'){
                if (board[i][j] == 'K'){
                    BlackPieces.k[0] = i ;
                    BlackPieces.k[1] = j ;
                }
                BlackPieces.places[BlackPieces.NOp][0] = i ;
                BlackPieces.places[BlackPieces.NOp][1] = j ;
                BlackPieces.NOp ++ ;
            }
        }
    }
}


int checked(char p){
    storepieces() ;

    struct pieces *current ;
    int i,j ;
    char o ;
    if(p == 'b'){
        current = &whitePieces ;
        i = BlackPieces.k[0] ;
        j = BlackPieces.k[1] ;
        o = 'w' ;
    }else{
        current = &BlackPieces ;
        i = whitePieces.k[0] ;
        j = whitePieces.k[1] ;
        o = 'b' ;
    }

    int r = 0 ;
    checkby[0] = 0 ;
    for(int x=0 ; x<current->NOp ; x++){
        int a = current->places[x][0] ;
        int b = current->places[x][1] ;
        if (CheckMovement(a, b,i, j,o, '\0')){
            r = 1 ;
            checkby[0] ++ ;
            checkby[1] = a ;
            checkby[2] = b ;
        }
    }
    return r ;

}

void minMax (int arr[]){
    if (arr[0]>arr[1]){
        int temp = arr[0] ;
        arr[0] = arr[1] ;
        arr[1] = temp ;
    }
}

int tempMoveCheck(char p, int movej, int movei,int movefj, int movefi){
    if(movei<0 || movei >7 || movej<0 || movej >7 || movefi<0 || movefi >7 || movefj<0 || movefj >7){
        return 1 ;
    }
    char start = board[movej][movei] ;
    char finish =board[movefj][movefi] ;
    int storeCheckBy[3] ;
    for(int n=0 ; n<3 ; n++){
        storeCheckBy[n] = checkby[n] ;
    }
    if(CheckMovement(movej, movei, movefj, movefi, p,'\0')){
        movement(movej,movei,movefj,movefi,board) ;
        int r ;
        r = checked(p) ;
        board[movej][movei] = start ;
        board[movefj][movefi] = finish;
        for(int n=0 ; n<3 ; n++){
            checkby[n] = storeCheckBy[n] ;
        }
        return r ;

    }else{
        return 1 ;
    }

}


int checkmate(char p){
    struct pieces *current ;
    int i,j,a,b ;
    if(p == 'b'){
        current = &BlackPieces ;
        i = BlackPieces.k[0] ;
        j = BlackPieces.k[1] ;
    }else{
        current = &whitePieces ;
        i = whitePieces.k[0] ;
        j = whitePieces.k[1] ;
    }

    // king moves
    for(int x=-1 ; x<2 ; x++){
        for(int y=-1 ; y<2 ; y++){
            if(x==0 && y==0){
                continue ;
            }
            if(tempMoveCheck(p, i, j, i+x, j+y)-1){
                return 0 ;
            }
        }
    }
    // more than one piece making check
    if(checkby[0]>1){
        return 1 ;
    }
    // if the checkby piece can be eaten
    int ich = checkby[1] ;
    int jch= checkby[2] ;
    for(int x=0 ; x<current->NOp ; x++){
        a = current->places[x][0] ;
        b = current->places[x][1] ;
        if (tempMoveCheck(p, a, b,ich, jch)-1){
            return 0 ;
        }
    }

    // if the check is by knight the path can't be interrupted
    if(board[ich][jch]=='n' || board[ich][jch]=='N'){
        return 1 ;
    }

    int mMi[2] = {i,ich} ;
    int mMj[2] = {j,jch} ;
    minMax(mMi) ;
    minMax(mMj) ;
    if(i==ich){  // same horizontal
        for(int y= mMj[0]+1 ; y<mMj[1] ; y++){
            for(int x=0 ; x<current->NOp ; x++){
                a = current->places[x][0] ;
                b = current->places[x][1] ;
                if (tempMoveCheck(p, a, b,i, y)-1){
                    return 0 ;
                }
            }
        }
    }else if (j==jch){  // same vertical
        for(int y= mMi[0]+1 ; y<mMi[1] ; y++){
            for(int x=0 ; x<current->NOp ; x++){
                a = current->places[x][0] ;
                b = current->places[x][1] ;
                if (tempMoveCheck(p, a, b, y, j)-1){
                    return 0 ;
                }
            }
        }
    }else if((i-ich)*(j-jch)>0){  // diagonal in "\"
        for(int y= 1 ; y<mMi[1]-mMi[0] ; y++){
            for(int x=0 ; x<current->NOp ; x++){
                a = current->places[x][0] ;
                b = current->places[x][1] ;
                if (tempMoveCheck(p, a, b,mMi[0]+y ,mMj[0]+y )-1){
                    return 0 ;
                }
            }
        }
    }else if((i-ich)*(j-jch)<0){  // diagonal in /
        for(int y= 1 ; y<mMi[1]-mMi[0] ; y++){
            for(int x=0 ; x<current->NOp ; x++){
                a = current->places[x][0] ;
                b = current->places[x][1] ;
                if (tempMoveCheck(p, a, b,mMi[0]+y ,mMj[1]-y )-1){
                    return 0 ;
                }
            }
        }
    }


    return 1 ;

}




