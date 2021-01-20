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
                    { 'R' , 'N' , 'B' , 'Q' , 'K' , 'B' , 'N' , 'R' },
                    { 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
                    { 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' },
                    { 'r' , 'n' , 'b' , 'q' , 'k' , 'b' , 'n' , 'r' }};

// movement functions and global
void CheckCastling();
int CheckMovement(int movej, int movei,int movefj, int movefi, char piece,char pro) ;
void movement (int movej, int movei,int movefj, int movefi) ;
int pw[8];
int pb[8];
struct died
{
	char die[15];
    int counter ;
}wdied,bdied;

// check,checkmate and stalemate functions
int checked(char p) ;
int tempMoveCheck(char p, int movej, int movei,int movefj, int movefi,char pro) ;
int checkmate(char p) ;
int stalemate(char p);

// undo and redo functions
void storemove(char p, int ifchecked , char startorPlay);
int undoRedo(char unRedo, char *p, int *ifchecked);

// save and load functions
void save(char piece);
void load(char *piece);



void printBoard(){
    // this function prints the chess board with the letters and numbers of the places and the died pieces for both white and black

    printf("     ") ;
    for (int i=0;i<8;i++){  // printing from A to H
        printf(" %c ",'A'+i) ;
    }printf("\n\n") ;

    for (int i=0;i<8;i++){  // printing the board
        for (int j=-1;j<9;j++){
            if(j==-1 || j==8){
                printf("  %d  ",8-i) ;  // before and after the board: prints the row number
            }else{
                printf(" %c " ,board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n     ") ;

    for (int i=0;i<8;i++){  // printing from A to H
        printf(" %c ",'A'+i) ;
    }
    printf("\n\n") ;

    if(wdied.counter){  // if there white pieces died
        printf ("White died pieces :-");

        for (int i=0;i<wdied.counter;i++){
            printf (" %c ",wdied.die[i]);
        }
        printf("\n") ;
    }
    if(bdied.counter){  // if there black pieces died
        printf ("Black died pieces :-");

        for (int i=0;i<bdied.counter;i++){
            printf (" %c ",bdied.die[i]);

        }
        printf("\n") ;
    }
    printf("\n");

}


int main(){
    char sl[5];
    int exit=0;
    int z=0;
    int ifchecked ;  // refer to if there a check or not
    int movei=0,movej=0, movefi=0,movefj=0;
    int x=0;    // refer if move will happen or not
    char piece = 'w';  // the current player
    char o = 'b';  // the opposite player
    wdied.counter = 0;
    bdied.counter = 0;


    printf("(start/load)\nMake Your Choice\n");
    while(1){
        gets(sl);
        if(sl[0]=='l'&&sl[1]=='o'&&sl[2]=='a'&&sl[3]=='d'&&sl[4]=='\0'){
            load(&piece);
            if(piece=='b'){
                o = 'w';
            }
            break;
        }else if(sl[0]=='s'&&sl[1]=='t'&&sl[2]=='a'&&sl[3]=='r'&&sl[4]=='t'&&sl[5]=='\0'){
            break;
        }
        printf("(start/load)\nMake Your Choice correctly \n");
    }


    ifchecked = checked(piece);
    storemove(piece, ifchecked, 's') ;  // store the start board in the linked list
    printBoard();


    while (!exit){
        CheckCastling();
        ///input check
        if(piece=='w'){
            printf("White:");
        }else{
            printf("Black:");
        }

        printf(" Enter Move \n");
        while (1){  // loop until the move entered correctly
            char move[10];
                gets(move);
                movei=(tolower(move[0])-'a');
                movej=('8'-move[1]);
                movefi=(tolower(move[2])-'a');
                movefj=('8'-move[3]);


            // if entered move
            if (((tolower(move[0])<='h'&& tolower(move[0])>='a')&&(move[1]-'0')<9&& (move[1]-'0')>0&&(tolower(move[2])<='h'&& tolower(move[2])>='a')&&(move[3]-'0')<9&& (move[3]-'0')>0)&&(move[0]!=move[2]||(move[1]-'0')!=(move[3]-'0'))&&(tolower(move[4])=='n'||tolower(move[4])=='r'||tolower(move[4])=='b'||tolower(move[4])=='q'||move[4]=='\0')){
                if (!tempMoveCheck(piece, movej,movei,movefj, movefi,move[4])){  // see if the move happened, will be check on the player or not

                    if (CheckMovement( movej,  movei, movefj,  movefi ,piece ,move[4])){  // check if it valid move or not
                            x=1;  // to make the move happen
                            break;
                        }
                    }
                    printf("Enter Move Correctly\n");

            }else if(move[0]=='s'&&move[1]=='a'&&move[2]=='v'&&move[3]=='e'&&move[4]=='\0'){  // if entered save
                save(piece);
                char t[4];
                while(1){
                    printf("Continue(Y/N):");
                    gets(t);
                    if(tolower(t[0])=='y'){
                        exit=0;
                        x=0;
                        printBoard();
                        break;
                    }else if (tolower(t[0])=='n'){
                        exit=1;
                        x=0;
                        break;
                    }
                }
                    break;

            }else if(move[0]=='u'&&move[1]=='n'&&move[2]=='d'&&move[3]=='o'&&move[4]=='\0'){  // if entered undo
                x=0;   // there no move will happen
                if (undoRedo('u', &piece,  &ifchecked)){  // if undo is valid and done
                    if (piece=='w'){  // restore the opposite player
                        o = 'b';
                    }else{
                        o = 'w';
                    }
                    printBoard();
                    break ;
                }else{
                    printf("Can't do undo\n");
                }

            }else if(move[0]=='r'&&move[1]=='e'&&move[2]=='d'&&move[3]=='o'&&move[4]=='\0'){  // if entered redo
                x=0;  // there no move will happen
                if (undoRedo('r', &piece,  &ifchecked)){  // if redo is valid and done
                    if (piece=='w'){
                        o = 'b';
                    }else{
                        o = 'w';
                    }
                    printBoard();
                    break ;
                }else{
                    printf("Can't do redo\n");
                }

            }else{  // entered something wrong
                printf("Enter Move Correctly\n");
            }
        }
    ////////////end of input check////////////////

        if(x){  // if move will happen
            movement ( movej, movei, movefj, movefi );  // do the move
            printBoard();

            if (piece=='w'){  // switch players
                piece='b';
                o = 'w';
                for(int i=0; i<8 ; i++){
                    pb[i]=0;  // Mentoooo !! bsafer el emboasont shof 7tktbha ezay XD XD
                }
            }else{
                piece='w';
                o = 'b';
                for(int i=0; i<8 ; i++){
                    pw[i]=0;
                }
            }

            ifchecked= checked(piece) ;  // see if the player is in check
            storemove(piece, ifchecked, 'p') ;  // store this play in the linked list

            if(ifchecked){
                if(checkmate(piece)){  // see if there a checkmate
                    printf("Checkmate!%c%c%c%c\n",7,7,7,7);
                    if (piece=='w'){
                        printf ("Black Wins!\n");
                    }else{
                        printf ("White Wins!\n");
                    }
                    exit=1;  // game over
                }else{
                    printf("Checked!!%c%c\n",7,7);

                }
            }else if (stalemate(piece)){  // if there a draw
                printf("Draw%c%c%c%c\n",7,7,7,7);
                exit=1;
            }

        }

    }
    return 0;
}



