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
                    { '-' , '.' , '.' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , 'P' , '.' , '-' , '.' , '-' , 'R' , '-' },
                    { '-' , '.' , '-' , 'k' , '-' , '.' , 'n' , '.' },
                    { '.' , '-' , '.' , '-' , '.' , 'Q' , '.' , '-' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' }};


struct pieces{
    int k[2] ;  // Place of king
    int places[16][2] ;  // arr of places of pieces
    int NOp ;
}whitePieces , BlackPieces ;

int checked(char p) ;
int tempMoveCheck(char p, int movej, int movei,int movefj, int movefi) ;
int checkmate(char p) ;

int main()
{

    int r ;
    if (checked('w')){
        r= checkmate('w') ;
    }
    printf("%d",r) ;

    return 0;
}
