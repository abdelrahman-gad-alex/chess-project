#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <ctype.h>
struct node
{
	char data[8][8];
	struct node *pNext;
	struct node *pPrev;
};
struct node *pHead;
struct node *pTail;


char board[8][8] ;
int Rl;
int Rr;
int rl;
int rr;



void save(){
    char file1[100];
    printf("Enter the name of the save file\n");
    gets(file1);
    FILE *fp;
    fp  = fopen (file1, "w");
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            fputc(board[i][j], fp);
            }
        }
    for(int i=0;i<4;i++){
        switch(i){
        case (0):
            fputc((Rl+'0'), fp);
            break;
        case (1):
            fputc((Rr+'0'), fp);
            break;
        case (2):
            fputc((rl+'0'), fp);
            break;
        case (3):
            fputc((rr+'0'), fp);
            break;

    }}
    fclose(fp);

}



void load(){
    char c,name[100];
    int i=0,j=0;
    printf("Enter the name of the load file\n");
    FILE *fr;
    while (1){
        gets(name);
        fr=fopen(name,"r");
        if (fr){
             break;
        }else{
            printf("Not found.\n");
        }

    }
    while ((c = getc(fr)) != EOF) {
        if(i<8&&j<8){
            (board[i][j]= c);
             j++;
             if (j==8){
                i++;
                j=0;
         }}else{
            switch(i){
                case 8 :
                    Rl=c-'0';
                    i++;
                    break;
                case 9 :
                    Rr=c-'0';
                    i++;
                    break;
                case 10 :
                    rl=c-'0';
                    i++;
                    break;
                case 11 :
                    rr=c-'0';
                    i++;
                    break;
         }
         }
    }
    fclose(fr);

}


