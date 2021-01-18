#include<stdio.h>
#include<conio.h>
#include <stdlib.h>

//Movement Functions
int CheckMovement(int movej, int movei,int movefj, int movefi, char piece,char pro);
void movement (int movej, int movei,int movefj, int movefi) ;

int undoRedo(char unRedo, char *p, int *ifchecked);

char board[8][8] ;

// Structure for the current pieces in board
struct pieces{
    int k[2] ;  // king place
    int places[16][2] ;
    int NOp ;  // number of pieces
}whitePieces , BlackPieces ;

int checkby[3] = {0,0,0} ;  // {Number of pieces making check, i of the piece, j of the piece}




void storepieces(){
    // put the places in the structure
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
    // check function
    storepieces() ;

    struct pieces *current ;
    int i,j ;
    char o ;  // the opposite player
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

    int r = 0 ; // the return variable for if checked or not
    checkby[0] = 0 ;
    for(int x=0 ; x<current->NOp ; x++){  // loop on the the opposite pieces
        int a = current->places[x][0] ;
        int b = current->places[x][1] ;
        if (CheckMovement(a, b,i, j,o, '\0')){  // can go to the king will be check
            r = 1 ;
            checkby[0] ++ ;
            checkby[1] = a ;
            checkby[2] = b ;
        }
    }
    return r ;

}


int tempMoveCheck(char p, int movej, int movei,int movefj, int movefi, char pro){
    // do a move temporary if valid , and see if check after doing the move or not then return to origin
    // returned 1 is not valid or will be checked, return 0 if valid and will not be checked
    if(movei<0 || movei >7 || movej<0 || movej >7 || movefi<0 || movefi >7 || movefj<0 || movefj >7){
        return 1 ;
    }
    int storeCheckBy[3] ;  // storing check by piece details
    for(int n=0 ; n<3 ; n++){
        storeCheckBy[n] = checkby[n] ;
    }

    if(CheckMovement(movej, movei, movefj, movefi, p,pro)){  // if valid move
        movement(movej,movei,movefj,movefi) ;
        int r ;
        r = checked(p) ;  // the return variable
        int ifchecked ;
        undoRedo('c', &p, &ifchecked);  // restore the current board and variables without changes

        for(int n=0 ; n<3 ; n++){  // restore the check by details
            checkby[n] = storeCheckBy[n] ;
        }
        return r ;

    }else{
        return 1 ;
    }

}

void minMax (int arr[]){
    // sort arr of 2
    if (arr[0]>arr[1]){
        int temp = arr[0] ;
        arr[0] = arr[1] ;
        arr[1] = temp ;
    }
}


int checkmate(char p){
    struct pieces *current ;
    int i,j,a,b ;
    if(p == 'b'){  // get the king place and the pieces places
        current = &BlackPieces ;
        i = BlackPieces.k[0] ;
        j = BlackPieces.k[1] ;
    }else{
        current = &whitePieces ;
        i = whitePieces.k[0] ;
        j = whitePieces.k[1] ;
    }

    // king moves to get out of the check
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
    // more than one piece making check and king can't move then will be checkmate
    if(checkby[0]>1){
        return 1 ;
    }
    // if the check is by piece can be eaten
    int ich = checkby[1] ;  // the place of the check by piece
    int jch= checkby[2] ;
    for(int x=0 ; x<current->NOp ; x++){
        a = current->places[x][0] ;  // the place of the piece of the current piece in loop
        b = current->places[x][1] ;
        char piece = board[a][b] ;
        if(piece=='p' && a==1){  // white pawn and will be promoted while eating
            if (tempMoveCheck(p, a, b,ich, jch,'q')-1){
                return 0 ;
            }
        }else if(piece=='P' && a==6){  // black pawn and will be promoted while eating
            if (tempMoveCheck(p, a, b,ich, jch,'Q')-1){
                return 0 ;
            }
        }else if (tempMoveCheck(p, a, b,ich, jch,'\0')-1){  //other piece can eat the piece which making the check
            return 0 ;
        }
    }

    // if the check is by knight the path can't be interrupted
    if(board[ich][jch]=='n' || board[ich][jch]=='N'){
        return 1 ;
    }

    // see if the path between the king and the check by piece can be interrupted
    int mMi[2] = {i,ich} ;     // sort the indexes of the path
    int mMj[2] = {j,jch} ;
    minMax(mMi) ;
    minMax(mMj) ;
    if(i==ich){  // the king and piece are at the same horizontal line
        for(int y= mMj[0]+1 ; y<mMj[1] ; y++){
            for(int x=0 ; x<current->NOp ; x++){
                a = current->places[x][0] ;     // the place of the piece of the current piece in loop
                b = current->places[x][1] ;
                char piece = board[a][b] ;

                if(piece=='p' && a==1){     // white pawn and will be promoted while interrupting the path
                    if (tempMoveCheck(p, a, b,i, y,'q')-1){
                        return 0 ;
                    }
                }else if(piece=='P' && a==6){       // black pawn and will be promoted while interrupting the path
                    if (tempMoveCheck(p, a, b,i, y,'Q')-1){
                        return 0 ;
                    }
                }
                if (tempMoveCheck(p, a, b,i, y,'\0')-1){  // other piece will interrupt the path
                    return 0 ;
                }
            }
        }
    }else if (j==jch){  // the king and piece are at the same vertical line
        for(int y= mMi[0]+1 ; y<mMi[1] ; y++){
            for(int x=0 ; x<current->NOp ; x++){
                a = current->places[x][0] ;
                b = current->places[x][1] ;

                if (tempMoveCheck(p, a, b, y, j,'\0')-1){
                    return 0 ;
                }
            }
        }
    }else if((i-ich)*(j-jch)>0){  // the king and piece are at the diagonal in "\"
        for(int y= 1 ; y<mMi[1]-mMi[0] ; y++){
            for(int x=0 ; x<current->NOp ; x++){
                a = current->places[x][0] ;
                b = current->places[x][1] ;
                if (tempMoveCheck(p, a, b,mMi[0]+y ,mMj[0]+y ,'\0')-1){
                    return 0 ;
                }
            }
        }
    }else if((i-ich)*(j-jch)<0){  // the king and piece are at the diagonal in /
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

    // else then its checkmate
    return 1 ;

}


int lackofCheckmate(char p){
    // this function see if there lack if checkmate material for the player p
    // if the pieces with the king was b of n or n,n
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
    if (lackofCheckmate('w')==1 && lackofCheckmate('b')==1){  // check if there lack of checkmate material first, that will be draw
        return 1 ;
    }

    struct pieces *current ;    // get the data for the current player
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

    // if the king has moves
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

    // see if the pieces can move
    for(int z=0 ; z<current->NOp ; z++){
        i= current->places[z][0] ;
        j= current->places[z][1] ;
        if(board[i][j]=='k' ||board[i][j]=='K'){
            continue ;
        }
        if (board[i][j]=='b' || board[i][j]=='q' || board[i][j]=='B' || board[i][j]=='Q' ){  // if b or q will the the diagonal moves
            if(tempMoveCheck(p, i, j, i+1, j+1,'\0')==0 || tempMoveCheck(p, i, j, i-1, j+1,'\0')==0 || tempMoveCheck(p, i, j, i+1, j-1,'\0')==0 ||tempMoveCheck(p, i, j, i-1, j-1,'\0')==0 ){
                return 0 ;
            }
        }
        if (board[i][j]=='r' || board[i][j]=='q' || board[i][j]=='R' || board[i][j]=='Q' ){  // if r or q will the the vertical and horizontal moves
            if(tempMoveCheck(p, i, j, i+1, j,'\0')==0 || tempMoveCheck(p, i, j, i-1, j,'\0')==0 || tempMoveCheck(p, i, j, i, j+1,'\0')==0 ||tempMoveCheck(p, i, j, i, j-1,'\0')==0 ){
                return 0 ;
            }
        }else if (board[i][j]=='n' || board[i][j]=='N'){   // if n will see its moves
            for(int x=-2 ; x<3 ; x++){
                for(int y=-3 ; y<3 ; y++){
                    if (x*y == 2 || x*y == -2){
                        if(tempMoveCheck(p, i, j, i+x, j+y,'\0')==0){
                            return 0 ;
                    }}
                }
            }
        }else if (board[i][j]=='p'){  // the white pawn moves
            char pro ='\0';
            if (j==1){       // if will be promoted
                pro = 'q' ;
            }
            if(tempMoveCheck(p, i, j, i-1, j,pro)==0 || tempMoveCheck(p, i, j, i-1, j-1,pro)==0 || tempMoveCheck(p, i, j, i-1, j+1,pro)==0 ){
                return 0 ;
            }
        }else if (board[i][j]=='P'){  // the black pawn moves
            char pro ='\0';
            if (j==6){      // if will be promoted
                pro = 'Q' ;
            }
            if(tempMoveCheck(p, i, j, i+1, j,pro)==0 || tempMoveCheck(p, i, j, i+1, j-1,pro)==0 || tempMoveCheck(p, i, j, i+1, j+1,pro)==0 ){
                return 0 ;
            }
        }
    }


    // if no piece can move then it is stalemate
    return 1 ;

}



















