#include<stdio.h>
#include<conio.h>
#include <stdlib.h>

struct node
{
	char data[8][8];
	struct node *pNext;
	struct node *pPrev;
};
struct node *pHead;
struct node *pTail;




/*
struct node* createnode(int data);
int search(int data);
void printall(void);
int addnode(int);
int addnodetoend(int data);
int addnodetobeg(int data);
int insert(int data,int loc);
int delete (int loc);

int deletebydata(int);

//3 5 5 2 1 7 1

int main()
{
	clrscr();
	printf("Add 1 to end: %d",addnodetoend(1));
	//printall();
	printf("\nAdd 5 to start: %d",addnodetobeg(5));
	//printall();
	printf("\nAdd 7 to end: %d",addnodetoend(7));
	//printall();
	printf("\nInsert 1 at 6: %d",insert(1,6));
	//printall();
	printf("\nInsert 2 at 1: %d",insert(2,1));
	//printall();
	printf("\nInsert 3 at 0: %d",insert(3,0));
	//printall();
	printf("\nInsert 5 at 1: %d",insert(5,1));
	//printall();
	printf("\nDeleted at 1: %d", delete(1));
	//printall();
	printf("\nDeleted at 7: %d", delete(7));
	//printall();
	printf("\nDeleted at 0: %d", delete(0));
	//printall();

	printf("\nFound 0 at %d",search(0));
	printf("\nFound 7 at %d", search(7));
	printall();
	printf("\nDeleted data 7: %d", deletebydata(7));
	printf("\nDeleted data -9: %d", deletebydata(-9));
	printf("\nFound 7 at %d", search(7));
    printall();
	getch();
	return 0;
}
*/
