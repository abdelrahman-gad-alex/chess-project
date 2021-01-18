#include<stdio.h>
#include<conio.h>
#include <stdlib.h>


int CheckMovement(int movej, int movei,int movefj, int movefi, char piece,char pro);
void movement (int movej, int movei,int movefj, int movefi) ;

int undoRedo(char unRedo, char *p, int *ifchecked);

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


int tempMoveCheck(char p, int movej, int movei,int movefj, int movefi, char pro){
    if(movei<0 || movei >7 || movej<0 || movej >7 || movefi<0 || movefi >7 || movefj<0 || movefj >7){
        return 1 ;
    }
    int storeCheckBy[3] ;
    for(int n=0 ; n<3 ; n++){
        storeCheckBy[n] = checkby[n] ;
    }

    if(CheckMovement(movej, movei, movefj, movefi, p,pro)){
        movement(movej,movei,movefj,movefi) ;
        int r ;
        r = checked(p) ;
        int ifchecked ;
        undoRedo('c', &p, &ifchecked);

        for(int n=0 ; n<3 ; n++){
            checkby[n] = storeCheckBy[n] ;
        }
        return r ;

    }else{
        return 1 ;
    }

}

void minMax (int arr[]){
    if (arr[0]>arr[1]){
        int temp = arr[0] ;
        arr[0] = arr[1] ;
        arr[1] = temp ;
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
            if(tempMoveCheck(p, i, j, i+x, j+y,'\0')-1){
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
        char piece = board[a][b] ;
        if(piece=='p' && a==1){
            if (tempMoveCheck(p, a, b,ich, jch,'q')-1){
                return 0 ;
            }
        }else if(piece=='P' && a==6){
            if (tempMoveCheck(p, a, b,ich, jch,'Q')-1){
                return 0 ;
            }
        }else if (tempMoveCheck(p, a, b,ich, jch,'\0')-1){
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
                char piece = board[a][b] ;

                if(piece=='p' && a==1){
                    if (tempMoveCheck(p, a, b,i, y,'q')-1){
                        return 0 ;
                    }
                }else if(piece=='P' && a==6){
                    if (tempMoveCheck(p, a, b,i, y,'Q')-1){
                        return 0 ;
                    }
                }
                if (tempMoveCheck(p, a, b,i, y,'\0')-1){
                    return 0 ;
                }
            }
        }
    }else if (j==jch){  // same vertical
        for(int y= mMi[0]+1 ; y<mMi[1] ; y++){
            for(int x=0 ; x<current->NOp ; x++){
                a = current->places[x][0] ;
                b = current->places[x][1] ;

                if (tempMoveCheck(p, a, b, y, j,'\0')-1){
                    return 0 ;
                }
            }
        }
    }else if((i-ich)*(j-jch)>0){  // diagonal in "\"
        for(int y= 1 ; y<mMi[1]-mMi[0] ; y++){
            for(int x=0 ; x<current->NOp ; x++){
                a = current->places[x][0] ;
                b = current->places[x][1] ;
                if (tempMoveCheck(p, a, b,mMi[0]+y ,mMj[0]+y ,'\0')-1){
                    return 0 ;
                }
            }
        }
    }else if((i-ich)*(j-jch)<0){  // diagonal in /
        for(int y= 1 ; y<mMi[1]-mMi[0] ; y++){
            for(int x=0 ; x<current->NOp ; x++){
                a = current->places[x][0] ;
                b = current->places[x][1] ;
                if (tempMoveCheck(p, a, b,mMi[0]+y ,mMj[1]-y ,'\0')-1){
                    return 0 ;
                }
            }
        }
    }


    return 1 ;

}


int lackofCheckmate(char p){
    int NOp ;
    struct pieces *current ;
    if(p=='b'){
        current = &BlackPieces ;
        NOp = BlackPieces.NOp ;
    }else{
        current = &whitePieces ;
        NOp = whitePieces.NOp ;
    }

    if( NOp > 3){
        return 0 ;
    }
    int b = 0 ;
    int n = 0 ;
    for(int i=0 ; i< NOp ; i++){
        char piece = board[current ->places[i][0]][current ->places[i][1]] ;

        if(piece!='k' && piece !='K' && piece!='b' && piece!='B' && piece!='n' && piece!='N' ){
            return 0 ;
        }
        if (piece == 'b'|| piece == 'B' ){
            b++ ;
        }else if (piece == 'n'||piece == 'N' ){
            n++ ;
        }
    }

    if (b==0 ||(n==0 && b==1)){
        return 1 ;
    }else{
        return 0 ;
    }
}


int stalemate(char p){
    if (lackofCheckmate('w')==1 && lackofCheckmate('b')==1){
        return 1 ;
    }

    struct pieces *current ;
    int i,j ;
    if(p == 'b'){
        current = &BlackPieces ;
        i = BlackPieces.k[0] ;
        j = BlackPieces.k[1] ;
    }else{
        current = &whitePieces ;
        i = whitePieces.k[0] ;
        j = whitePieces.k[1] ;
    }

    // For the king's moves
    for(int x=-1 ; x<2 ; x++){
        for(int y=-1 ; y<2 ; y++){
            if(x==0 && y==0){
                continue ;
            }
            if(tempMoveCheck(p, i, j, i+x, j+y,'\0')==0){
                return 0 ;
            }
        }
    }

    for(int z=0 ; z<current->NOp ; z++){
        i= current->places[z][0] ;
        j= current->places[z][1] ;
        if(board[i][j]=='k' ||board[i][j]=='K'){
            continue ;
        }
        if (board[i][j]=='b' || board[i][j]=='q' || board[i][j]=='B' || board[i][j]=='Q' ){
            if(tempMoveCheck(p, i, j, i+1, j+1,'\0')==0 || tempMoveCheck(p, i, j, i-1, j+1,'\0')==0 || tempMoveCheck(p, i, j, i+1, j-1,'\0')==0 ||tempMoveCheck(p, i, j, i-1, j-1,'\0')==0 ){
                return 0 ;
            }
        }
        if (board[i][j]=='r' || board[i][j]=='q' || board[i][j]=='R' || board[i][j]=='Q' ){
            if(tempMoveCheck(p, i, j, i+1, j,'\0')==0 || tempMoveCheck(p, i, j, i-1, j,'\0')==0 || tempMoveCheck(p, i, j, i, j+1,'\0')==0 ||tempMoveCheck(p, i, j, i, j-1,'\0')==0 ){
                return 0 ;
            }
        }else if (board[i][j]=='n' || board[i][j]=='N'){
            for(int x=-2 ; x<3 ; x++){
                for(int y=-3 ; y<3 ; y++){
                    if (x*y == 2 || x*y == -2){
                        if(tempMoveCheck(p, i, j, i+x, j+y,'\0')==0){
                            return 0 ;
                    }}
                }
            }
        }else if (board[i][j]=='p'){
            char pro ='\0';
            if (j==1){
                pro = 'q' ;
            }
            if(tempMoveCheck(p, i, j, i-1, j,pro)==0 || tempMoveCheck(p, i, j, i-1, j-1,pro)==0 || tempMoveCheck(p, i, j, i-1, j+1,pro)==0 ){
                return 0 ;
            }
        }else if (board[i][j]=='P'){
            char pro ='\0';
            if (j==6){
                pro = 'Q' ;
            }
            if(tempMoveCheck(p, i, j, i+1, j,pro)==0 || tempMoveCheck(p, i, j, i+1, j-1,pro)==0 || tempMoveCheck(p, i, j, i+1, j+1,pro)==0 ){
                return 0 ;
            }
        }
    }

    return 1 ;

}



















