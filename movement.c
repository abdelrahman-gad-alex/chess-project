#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int R[4];   //castling indicators
int pw[8];  //white enpassent indicators
int pb[8];  //black enpassent indicators
char board[8][8] ;  //the chess board

struct died     //struct to store the dead pieces
{
	char die[15];
    int counter ;
}wdied,bdied;



void movement (int movej, int movei,int movefj, int movefi)  //The movement function which is responsible for the pieces from the initial place to the final place.
{
    char temp=board[movej][movei];  //here we store the piece we want to move which is on the initial place.

    if (isupper(board[movefj][movefi])){  //here we check if there is black piece in the final place & if we find one we add it to the died black pieces array.
        bdied.die[bdied.counter]=board[movefj][movefi];
        bdied.counter++;
    }else if(islower(board[movefj][movefi])){ //here we do the same with the white pieces.
        wdied.die[wdied.counter]=board[movefj][movefi];
        wdied.counter++;
    }

    else if ((movei+movej)%2==0){ //here we replace the initial place with a - if the initial place is an even square.
        board[movej][movei]='-';
    }else{
        board[movej][movei]='.';//else we replace it with a . .
    }

    board[movefj][movefi]=temp; //here we put the stored piece in the final place.
}


int CheckRook(int movej, int movei,int movefj, int movefi, char pro) //this function is responsible for checking the movement of rooks white or black.
{
    int i,j;
    int x=1; //here we initialize the x as 1 to allow the move except for the following cses which change the variable value to 0.
    if(movefi==movei||movefj==movej){ //here we check if the rook is moving horizontally or vertically .
         //here we check  if there is any piece between the initial piece and the final piece in the movement direction. If there is we make x = 0.
        if (movei < movefi&&movej==movefj){ //Here the movement is to the right .
            for (i=movei+1;i<movefi;i++){
                if((board[movej][i]>='a'&&board[movej][i]<='z')||(board[movej][i]>='A'&&board[movej][i]<='Z')){
                    x=0 ;

                }
            }
        }else if (movei > movefi&&movej==movefj){  //Here the movement is to the left .
            for (i=movei-1;i>movefi;i--){
                if((board[movej][i]>='a'&&board[movej][i]<='z')||(board[movej][i]>='A'&&board[movej][i]<='Z')){
                    x=0 ;
                }
            }
        }else if (movei == movefi&&movej>movefj){  //Here the movement is upward .
            for (j=movej-1;j>movefj;j--){
                if((board[j][movei]>='a'&&board[j][movei]<='z')||(board[j][movei]>='A'&&board[j][movei]<='Z')){
                    x=0 ;
                }
            }
        }else if (movei == movefi&&movej<movefj){  //Here the movement is downward .
            for (j=movej+1;j<movefj;j++){
                if((board[j][movei]>='a'&&board[j][movei]<='z')||(board[j][movei]>='A'&&board[j][movei]<='Z')){
                    x=0 ;
                }
            }
        }

    }else { //if the movement is niether horizontally nor vertically then we make x = 0.
        x=0;

    }
    if(pro !='\0'){ //here we check if the user enter a fifth character . If so we make x = 0.
        x=0;

    }

    return x;  //we return the x value in the end.
}




int Checkknight(int movej, int movei,int movefj, int movefi, char pro)  //this function is responsible for checking the movement of knights white or black.
{
    int x;
    if ((movefi == movei + 2 &&movefj == movej+1)||(movefi == movei + 2 &&movefj == movej-1)||(movefi == movei - 2 &&movefj == movej+1)||(movefi == movei - 2 &&movefj == movej-1))
    {   //here we check the movement of the knight if it is two squares in the horizontal direction and one in the vertical direction. If so we make x = 1.
        x=1;

    }else if ((movefj == movej + 2 &&movefi == movei+1)||(movefj == movej + 2 &&movefi == movei-1)||(movefj == movej - 2 &&movefi == movei+1)||(movefj == movej - 2 &&movefi == movei-1))
    {   //here we check the movement of the knight if it is two squares in the vertical direction and one in the horizontal direction. If so we make x = 1.
        x=1;

    }else{   //if the movement the user entered for the knight is not what we checked earlier then we make x=0.
        x=0;

    }
    if(pro !='\0'){  //here we check if the user enter a fifth character . If so we make x = 0.
    x=0;

    }

    return x;  //we return the x value in the end.
}

int CheckBishop(int movej, int movei,int movefj, int movefi, char pro) //this function is responsible for checking the movement of bishops white or black.
{
    int i;
    int x=1;  //here we initialize the x as 1 to allow the move except for the following cases which change the variable value to 0.
    if (abs(movefi-movei)==abs(movefj-movej)){  //here we check if the bishop will move diagonally
         //here we check  if there is any piece between the initial place and the final place in the movement direction. If there is we make x = 0.
        if (movefi > movei && movefj > movej){ //the movement is to the down right
            for (i=1;i<(movefi-movei);i++){
                if ((board[movej+i][movei+i]>'a'&&board[movej+i][movei+i]<'z')||(board[movej+i][movei+i]>'a'&&board[movej+i][movei+i]<'z')){
                x=0;
                }
            }
        }else if (movefi < movei && movefj > movej){//the movement is to the down left
            for (i=1;i<(movei-movefi);i++){
                if ((board[movej+i][movei-i]>'a'&&board[movej+i][movei-i]<'z')||(board[movej-i][movei+i]>'A'&&board[movej-i][movei+i]<'Z')){
                x=0;
                }
            }
        }else if (movefi > movei && movefj < movej){  //the movement is to the upper right
            for (i=1;i<(movefi-movei);i++){
                if ((board[movej-i][movei+i]>'a'&&board[movej-i][movei+i]<'z')||(board[movej-i][movei+i]>'A'&&board[movej-i][movei+i]<'Z')){
                x=0;
                }
            }
        }else if (movefi < movei && movefj < movej){//the movement is to the upper left
            for (i=1;i<(movei-movefi);i++){
                if ((board[movej-i][movei-i]>'a'&&board[movej-i][movei-i]<'z')||(board[movej-i][movei-i]>'A'&&board[movej-i][movei-i]<'Z')){
                x=0;
                }
            }
        }
    }else{  //here we check if the move is not diagonally
        x=0;

    }
    if(pro !='\0'){  //here we check if the user enter a fifth character . If so we make x = 0.
    x=0;

    }

    return x;  //we return the x value in the end.
}

int CheckKing(int movej, int movei,int movefj, int movefi, char pro  )//this function is responsible for checking the movement of Kings white or black.
{
    int x;
    if (abs(movefi-movei)<=1&&abs(movefj-movej)<=1){ // here we check if the king is moving to one from the 8 adjacent places
        x=1;
    }else if(((!R[2])&&movefj==movej&&movej==7&&movefi==2&&movei==4)||((!R[0])&&movefj==movej&&movej==0&&movefi==2&&movei==4)){// here we check for the castling special case with the left rooks white or black and we check that the chosen rooks and the king never move before
        x=1;
        for (int i=3;i>0;i-- ){ // here we check if there is any piece in the path between the king and the chosen Rook
            if ((board[movej][i]>'a'&&board[movej][i]<'z')||(board[movej][i]>'A'&&board[movej][i]<'Z')){
                x=0;
            }
        }
        if (x==1){  // if the castling is allowed we move the rook to its new place here
            movement(movej,0,movefj,3);
        }
    }else if(((!(R[3]))&&movefj==movej&&movej==7&&movefi==6&&movei==4)||((!(R[1]))&&movefj==movej&&movej==0&&movefi==6&&movei==4)){// here we check for the castling special case with the right rooks white or black and we check that the chosen rooks and the king never move before
        x=1;
        for (int i=6;i>4;i-- ){// here we check if there is any piece in the path between the king and the chosen Rook
            if ((board[movej][i]>'a'&&board[movej][i]<'z')||(board[movej][i]>'A'&&board[movej][i]<'Z')){
                x=0;
            }
        }
        if (x==1){// if the castling is allowed we move the rook to its new place here
            movement(movej,7,movefj,5);
        }
    }else{ //here we disallow the move if it is not one of the above
    x=0;

    }
    if(pro !='\0'){  //here we check if the user enter a fifth character . If so we make x = 0.
    x=0;

    }

    return x;  //we return the x value in the end.
}



int CheckQueen(int movej, int movei,int movefj, int movefi, char pro)//this function is responsible for checking the movement of queens white or black.
{
    int i,j;
    int x=1;  //here we initialize the x as 1 to allow the move except for the following cses which change the variable value to 0.
    if (abs(movefi-movei)==abs(movefj-movej)){//here we check if the queen will move  diagonally
    //here we check  if there is any piece between the initial place and the final place in the movement direction. If there is we make x = 0.
        if (movefi > movei && movefj > movej){//the movement is to the down right
            for (i=1;i<(movefi-movei);i++){
                if ((board[movej+i][movei+i]>'a'&&board[movej+i][movei+i]<'z')||(board[movej+i][movei+i]>'A'&&board[movej+i][movei+i]<'Z')){
                x=0;
                }
            }
        }else if (movefi < movei && movefj>movej){//the movement is to the down left
            for (i=1;i<(movei-movefi);i++){
                if ((board[movej+i][movei-i]>'a'&&board[movej+i][movei-i]<'z')||(board[movej+i][movei-i]>'A'&&board[movej+i][movei-i]<'Z')){
                x=0;
                }
            }
        }else if (movefi > movei && movefj < movej){//the movement is to the upper right
            for (i=1;i<(movefi-movei);i++){
                if ((board[movej-i][movei+i]>'a'&&board[movej-i][movei+i]<'z')||(board[movej-i][movei+i]>'A'&&board[movej-i][movei+i]<'Z')){
                x=0;
                }
            }
        }else if (movefi < movei && movefj < movej){//the movement is to the upper left
            for (i=1;i<(movei-movefi);i++){
                if ((board[movej-i][movei-i]>'a'&&board[movej-i][movei-i]<'z')||(board[movej-i][movei-i]>'A'&&board[movej-i][movei-i]<'Z')){
                x=0;
                }
            }
        }
    }else if(movefi==movei||movefj==movej){//here we check if the queen is moving horizontally or vertically .
    //here we check  if there is any piece between the initial piece and the final piece in the movement direction. If there is we make x = 0.
        if (movei < movefi&&movej==movefj){ //Here the movement is to the right .
            for (i=movei+1;i<movefi;i++){
                if((board[movej][i]>='a'&&board[movej][i]<='z')||(board[movej][i]>='A'&&board[movej][i]<='Z')){
                    x=0 ;
                }
            }
        }else if (movei > movefi&&movej==movefj){//Here the movement is to the left .
            for (i=movei-1;i>movefi;i--){
                if((board[movej][i]>='a'&&board[movej][i]<='z')||(board[movej][i]>='A'&&board[movej][i]<='Z')){
                    x=0 ;
                }
            }
        }else if (movei == movefi&&movej>movefj){//Here the movement is upward .
            for (j=movej-1;j>movefj;j--){
                if((board[j][movei]>='a'&&board[j][movei]<='z')||(board[j][movei]>='A'&&board[j][movei]<='Z')){
                    x=0 ;
                }
            }
        }else if (movei == movefi&&movej<movefj){//Here the movement is downward .
            for (j=movej+1;j<movefj;j++){
                if((board[j][movei]>='a'&&board[j][movei]<='z')||(board[j][movei]>='A'&&board[j][movei]<='Z')){
                    x=0 ;
                }
            }
        }

    }else{ //if the move is not diagonally , horizontally or vertically then the move is disallowed( x=0)
        x=0;

    }
    if(pro !='\0'){  //here we check if the user enter a fifth character . If so we make x = 0.
        x=0;

    }

    return x;  //we return the x value in the end.
}


int CheckPawnW(int movej, int movei,int movefj, int movefi,char pro)//this function is responsible for checking the movement of the white pawns only
{
    int x;
    if (movei==movefi&&(movej-movefj)==1&&movefj!=0&&pro=='\0'&&(board[movefj][movefi]=='.'||board[movefj][movefi]=='-')){ //here we check that the pawn moves only one square to the forward only and the final square is empty and there are no fifth character in the user input and the final square is not the last square.
        x=1;
    }else if (movei==movefi&&(movej-movefj)==1&&movefj==0&&pro !='\0'&&(board[movefj][movefi]=='.'||board[movefj][movefi]=='-')){//here we check that the pawn moves only one square to the forward only and the final square is empty and there are a fifth character in the user input and the final square is the last square.
        x=1;
        board[movej][movei]=tolower(pro); //here we promote the pawn to the chosen piece.
    }else if ((movej-movefj)==1&&abs(movei-movefi)==1&&board[movefj][movefi]>'A'&&board[movefj][movefi]<'Z'){ //here we check for the diagonal move for the pawn in case of the black piece
        if (movefj==0&&pro !='\0'){//here we see if there are a fifth character in the user input and the final square is the last square.
            x=1;
            board[movej][movei]=tolower(pro);//here we promote the pawn to the chosen piece.
        }else if (movefj==0&&pro =='\0'){//here we see if there are no fifth character in the user input and the final square is the last square.
            x=0;
        }else if (movefj!=0&&pro !='\0'){//here we see if there are a fifth character in the user input and the final square is not the last square.
            x=0;
        }else{ //here we see if there are no fifth character in the user input and the final square is not the last square.
            x=1;
        }
    }else if (movej == 6 && movefj== 4&&movei==movefi&&(board[movefj][movefi]=='.'||board[movefj][movefi]=='-')&&pro =='\0'){//here we check for the douple square move for the pawn in the first move
        x=1;
        if(board[4][movei+1]=='P'||board[4][movei-1]=='P'){// here we check for the ability of an en passant case
            pw[movei]=1;
        }
    }else if ((movej) == 3 && movefj == 2 && abs(movei-movefi)==1&&board[3][movefi]=='P'&&pb[movefi]&&pro =='\0'){// here we check for the en passant case
        x=1;
        //here we remove the black pawn from the board
        bdied.die[bdied.counter]=board[3][movefi];
        bdied.counter++;
        if ((movefi+3)%2==0){
            board[3][movefi]='-';
        }
        else{
            board[3][movefi]='.';
        }

    }else{ //if the pawn move is not one from the above then the move is disallowed( x=0)
    x=0;
    }
    return x ; //we return the x value in the end.
}

int CheckPawnB(int movej, int movei,int movefj, int movefi,char pro)//this function is responsible for checking the movement of the Black pawns only
{
    int x=1;
    if (movei==movefi&&(movefj-movej)==1&&movefj!=7&&pro=='\0'&&(board[movefj][movefi]=='.'||board[movefj][movefi]=='-')){//here we check that the pawn moves only one square to the forward only and the final square is empty and there are no fifth character in the user input and the final square is not the last square.
        x=1;
    }else if (movei==movefi&&(movefj-movej)==1&&movefj==7&&pro!='\0'&&(board[movefj][movefi]=='.'||board[movefj][movefi]=='-')){//here we check that the pawn moves only one square to the forward only and the final square is empty and there are a fifth character in the user input and the final square is the last square.
        x=1;
        board[movej][movei]=toupper(pro);//here we promote the pawn to the chosen piece.
    }else if ((movefj-movej)==1&&abs(movei-movefi)==1&&board[movefj][movefi]>'a'&&board[movefj][movefi]<'z'){ //here we check for the diagonal move for the pawn in case of a white piece
        if (movefj==7&&pro !='\0'){//here we see if there are a fifth character in the user input and the final square is the last square.
            x=1;
            board[movej][movei]=toupper(pro);//here we promote the pawn to the chosen piece.
        }else if (movefj==7&&pro =='\0'){//here we see if there are no fifth character in the user input and the final square is the last square.
            x=0;
        }else if (movefj!=7&&pro !='\0'){//here we see if there are a fifth character in the user input and the final square is not the last square.
            x=0;
        }else{//here we see if there are no fifth character in the user input and the final square is not the last square.
            x=1;
        }
    }else if (movej == 1 && movefj== 3 && movei==movefi&&(board[movefj][movefi]=='.'||board[movefj][movefi]=='-')&&pro =='\0'){//here we check for the douple square move for the pawn in the first move
        x=1;
        if(board[3][movei+1]=='p'||board[3][movei-1]=='p'){// here we check for the ability of an en passant case
            pb[movei]=1;
        }
    }else if ((movej) == 4 && movefj == 5 && abs(movei-movefi)==1&&board[4][movefi]=='p'&&pw[movefi]&&pro =='\0'){// here we check for the en passant case
        x=1;
        //here we remove the white pawn from the board
        wdied.die[wdied.counter]=board[4][movefi];
        wdied.counter++;
        if ((movefi+4)%2==0){
            board[4][movefi]='-';
        }else{
            board[4][movefi]='.';
        }
    }else{//if the pawn move is not one from the above then the move is disallowed( x=0)
    x=0;
    }
    return x ;//we return the x value in the end.
}





int CheckMovement(int movej, int movei,int movefj, int movefi, char piece,char pro)  //This is the function that checks the movement by checking the piece and then check its available moves
{

    int x=0;
    if (piece == 'w'){//if its white turn then we check for the movement of white pieces
        if(((board[movefj][movefi]>'A'&&board[movefj][movefi]<'Z')||board[movefj][movefi]=='.'||board[movefj][movefi]=='-')&&(board[movej][movei]>'a'&&board[movej][movei]<'z')){ //here we check that the piece we want to move is white and the place we want to move it into is empty or contain black piece.
            switch(board[movej][movei]) //here we check to know the kind of the white piece.
            {
                case 'p'://if it is pawn we check for the movement of the white pawn.
                x=CheckPawnW(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'r'://if it is rook we check for its movement.
                x=CheckRook(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'n'://if it is knight we check for its movement.
                x=Checkknight(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'b'://if it is bishop we check for its movement.
                x=CheckBishop(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'k'://if it is king we check for its movement.
                x=CheckKing(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'q'://if it is queen we check for its movement.
                x=CheckQueen(movej,  movei, movefj,  movefi, pro);
                break ;
                default:
                x=0;
            }
        }
        return x;

    }else if (piece == 'b'){//if its black turn then we check for the movement of black pieces
        if(((board[movefj][movefi]>'a'&&board[movefj][movefi]<'z')||board[movefj][movefi]=='.'||board[movefj][movefi]=='-')&&(board[movej][movei]>'A'&&board[movej][movei]<'Z')){//here we check that the piece we want to move is black and the place we want to move it into is empty or contain white piece.
            switch(board[movej][movei])//here we check to know the kind of the black piece.
            {
                case 'P'://if it is pawn we check for the movement of the black pawn.
                x=CheckPawnB(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'R'://if it is rook we check for its movement.
                x=CheckRook(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'N'://if it is knight we check for its movement.
                x=Checkknight(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'B'://if it is bishop we check for its movement.
                x=CheckBishop(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'K'://if it is king we check for its movement.
                x=CheckKing(movej,  movei, movefj,  movefi, pro);
                break ;
                case 'Q'://if it is queen we check for its movement.
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

void CheckCastling()//This function is used to indicate if any rook or any king had moved before.
{

    if (board[0][0]!='R'){
        R[0]=1;
    }
    if (board[0][7]!='R'){
        R[1]=1;
    }
    if (board[7][0]!='r'){
        R[2]=1;
    }
    if (board[7][7]!='r'){
        R[3]=1;
    }
    if (board[0][4]!='K'){
        R[0]=1;
        R[1]=1;
    }
    if (board[7][4]!='k'){
        R[2]=1;
        R[3]=1;
    }
}





