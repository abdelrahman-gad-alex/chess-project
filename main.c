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

// movement functions
void CheckCastling();
int CheckMovement(int movej, int movei,int movefj, int movefi, char piece,char pro) ;
void movement (int movej, int movei,int movefj, int movefi) ;
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
    printf("     ") ;
    for (int i=0;i<8;i++){
        printf(" %c ",'A'+i) ;
    }printf("\n\n") ;

    for (int i=0;i<8;i++){
        for (int j=-1;j<9;j++){
            if(j==-1 || j==8){
                printf("  %d  ",8-i) ;
            }else{
                printf(" %c " ,board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n     ") ;
    for (int i=0;i<8;i++){
        printf(" %c ",'A'+i) ;
    }printf("\n\n") ;

    if(wdied.counter){
        printf ("White died pieces :-");

        for (int i=0;i<wdied.counter;i++){
            printf (" %c ",wdied.die[i]);
        }
    }
    if(bdied.counter){
        printf ("\nBlack died pieces :-");

        for (int i=0;i<bdied.counter;i++){
            printf (" %c ",bdied.die[i]);

        }
        printf("\n\n") ;
    }


}


int main(){
    char sl[5];
    int exit=0;
    int z=0;
    int ifchecked ;
    int movei=0,movej=0, movefi=0,movefj=0,x=0;
    char piece = 'w';
    wdied.counter = 0;
    bdied.counter = 0;

    char o = 'b';
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
    storemove(piece, ifchecked, 's') ;
    printBoard();


    while (!exit){
        CheckCastling();
    /////////////////input check///////////
        if(piece=='w'){
            printf("White:");
        }else{
            printf("black:");
        }
        printf(" Enter Move \n");
        while (1){
        char move[100];
            gets(move);
            movei=(tolower(move[0])-'a');
            movej=('8'-move[1]);
            movefi=(tolower(move[2])-'a');
            movefj=('8'-move[3]);


        // if entered move
         if (((tolower(move[0])<='h'&& tolower(move[0])>='a')&&(move[1]-'0')<9&& (move[1]-'0')>0&&(tolower(move[2])<='h'&& tolower(move[2])>='a')&&(move[3]-'0')<9&& (move[3]-'0')>0)&&(move[0]!=move[2]||(move[1]-'0')!=(move[3]-'0'))&&(tolower(move[4])=='n'||tolower(move[4])=='r'||tolower(move[4])=='b'||tolower(move[4])=='q'||move[4]=='\0')){
                if (!tempMoveCheck(piece, movej,movei,movefj, movefi,move[4])){

                    if (CheckMovement( movej,  movei, movefj,  movefi ,piece ,move[4])){

                        x=1;
                        break;
                    }
                }
                printf("Enter Move Correctly\n");

            }else if(move[0]=='s'&&move[1]=='a'&&move[2]=='v'&&move[3]=='e'&&move[4]=='\0'){  // if entered save
                save(piece);
                char t[1];
                while(1){
                    printf("Continue(Y/N):");
                    gets(t);
                    if (tolower(t[0])=='y'){
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
                x=0;
                if (undoRedo('u', &piece,  &ifchecked)){
                    if (piece=='w'){
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
                x=0;
                if (undoRedo('r', &piece,  &ifchecked)){
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

        if(x){
            movement ( movej, movei, movefj, movefi );
            printBoard();
            if(checked(o)){
                if(checkmate(o)){
                    printf("Check Mate!%c%c%c%c\n",7,7,7,7);
                    if (o=='w'){
                        printf ("Black Wins!\n");
                    }else{
                        printf ("White Wins!\n");
                    }
                    exit=1;
                }else{
                printf("Checked!!%c%c\n",7,7);
                ifchecked=1;
                }
            }else if (stalemate(o)){
                        printf("Draw%c%c%c%c\n",7,7,7,7);
                        exit=1;
            }else{
                ifchecked=0;

            }

            if (piece=='w'){
                piece='b';
                o = 'w';
            }else{
                piece='w';
                o = 'b';
            }
            storemove(piece, ifchecked, 'p') ;

        }

    }
    return 0;
}



