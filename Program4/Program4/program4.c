//Kevin Beltran, 04/23/17, Program 4 - structs

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MIDICHLORIANS 40

typedef struct {
	char clonename[MIDICHLORIANS];
	char rank[MIDICHLORIANS];
	int productid;
	int ptscore;
	double accuracy;
	double dnaintegrity;
} clone;

//Greets the user
void HelloThere();

//hardcodes five entries
void CloneArmy(clone* ar);

//runs the menu and gets the user choice
char OrdersSir();

//prints the contents of the list onto the screen
void SitRep(clone squad[], int count);

//prints a report to a file 
/*declare the file pointer, connect to the file and close the file pointer all inside this function*/
void SaveIntel(clone squad[], int count);

//adds an item to the list
void FreshBoot(clone* ClonePtr, int count);

//displays the ids in the list, gets the id from the user and returns it
int SoundOff(clone squad[], int count);

//searches the list by id and returns the index, if there is a match or returns -1 
//three arguments: list, number of items, id
int Accountability(clone squad[], int count, int id1);

//removes an item from the list 
//takes three arguments, the list, the number of items and the location
void Article15(clone* ClonePtr, int count, int loc);

//updates PT Score
//takes three arguments, the list, the number of items and the location
void AlterTheDeal(clone* ClonePtr, int count, int loc);

int main()
{
	char orders;
	clone squad[MIDICHLORIANS];
	int headcount = 0;
	int rosterNumber;
	int position;
	CloneArmy(&squad);
	headcount = 5;
	HelloThere();
	do {
		//Get User choice
		orders = OrdersSir();

		//change choice to upper case
		orders = toupper(orders);
		printf("You chose %c\n", orders);

		//test the choices
		switch (orders) {
		case 'P':	SitRep(squad, headcount);
					break;
		case 'A':	FreshBoot(&squad, headcount);
			headcount = headcount + 1;
					break;
		case 'C':	*squad = *squad;
					headcount = 0;
					break;
		case 'S':	SaveIntel(squad, headcount);
					break;
		case 'D':	rosterNumber = SoundOff(squad, headcount);
					position = Accountability(squad, headcount, rosterNumber);
					//call delete
					Article15(&squad, headcount, position);
					headcount = headcount - 1;
					break;
		case 'U':	rosterNumber = SoundOff(squad, headcount);
					position = Accountability(squad, headcount, rosterNumber);
					AlterTheDeal(&squad, headcount, position);
					break;
		case 'R':	CloneArmy(&squad);
					headcount = 5;
					printf("\nYou crazy.\n");
					break;
		case 'Q':	printf("\nGoodbye, and may the Force be with you.");
		default:	printf("\n\nSo uncivilized.");
		}
	} while (orders != 'Q');
	return 0;
}

//Greets the user
void HelloThere()
{
	printf("\nHello There! This is General Kenobi of the Galactic Federation.\n\nWe are granting you a spot on the Jedi Council, Jedi Master Security Clearance and full access \nto this experimental program which manages your Clone Army. You are on this council, but we do not \ngrant you the rank of Master.\n\nEach clone has a unique ID\n\nUse the Force and follow the prompts on the menu:\n\n\n---------------------------------------\n");
}

//Creates 5 clones
void CloneArmy(clone* ar)
{
	strcpy(ar[0].clonename, "Rex");
	strcpy(ar[0].rank, "Captain");
	ar[0].ptscore = 300;
	ar[0].productid = 7567;
	ar[0].accuracy = 35.00;
	ar[0].dnaintegrity = 99.00;
	strcpy(ar[1].clonename, "Cody");
	strcpy(ar[1].rank, "Commander");
	ar[1].ptscore = 298;
	ar[1].productid = 2224;
	ar[1].accuracy = 33.00;
	ar[1].dnaintegrity = 99.80;
	strcpy(ar[2].clonename, "Fives");
	strcpy(ar[2].rank, "Trooper");
	ar[2].ptscore = 272;
	ar[2].productid = 5555;
	ar[2].accuracy = 29.00;
	ar[2].dnaintegrity = 96.00;
	strcpy(ar[3].clonename, "Echo");
	strcpy(ar[3].rank, "Trooper");
	ar[3].ptscore = 282;
	ar[3].productid = 1409;
	ar[3].accuracy = 31.00;
	ar[3].dnaintegrity = 97.00;
	strcpy(ar[4].clonename, "Heavy");
	strcpy(ar[4].rank, "Trooper");
	ar[4].ptscore = 286;
	ar[4].productid = 782;
	ar[4].accuracy = 26.00;
	ar[4].dnaintegrity = 95.00;
}

//runs the menu and gets the user choice
char OrdersSir()
{
	char choice;
	printf("\nAwaiting Orders: \n\nP....Print the roster on to the screen\n\nA....Add a new trooper\n\nC....Clear all records\n\nS....Save Intel Report(save it to a file)\n\nD....Remove a trooper from the roster\n\nU....Update PT score\n\nR...Reinitialize Squad\n\nQ....Quit  \n\n");
	scanf(" %c", &choice);
	return choice;
}

//prints the contents of the list onto the screen
void SitRep(clone squad[], int count)
{
	int i;
	for (i = 0; i < count; i++)
	{
		printf("\nName: %s", squad[i].clonename);
		printf("\nRank: %s", squad[i].rank);
		printf("\nID: %d", squad[i].productid);
		printf("\nPT Score: %d", squad[i].ptscore);
		printf("\nAccuracy: %.2f", squad[i].accuracy);
		printf("\nDNA Integrity: %.2f\n", squad[i].dnaintegrity);
	}
}

//prints a report to a file 
/*declare the file pointer, connect to the file and close the file pointer all inside this function*/
void SaveIntel(clone squad[], int count)
{
	//file pointer
	FILE* ptr;
	int i;
	//connect to file
	ptr = fopen("Intel Report.txt", "w");
	for (i = 0; i < count; i++)
	{
		fprintf(ptr, "\nName: %s", squad[i].clonename);		
		fprintf(ptr, "\nRank: %s", squad[i].rank);
		fprintf(ptr, "\nID: %d", squad[i].productid);
		fprintf(ptr, "\nPT Score: %d", squad[i].ptscore);
		fprintf(ptr, "\nAccuracy: %.2f", squad[i].accuracy);
		fprintf(ptr, "\nDNA Integrity: %.2f\n", squad[i].dnaintegrity);
	}
	fclose(ptr);
}

//adds an item to the list
void FreshBoot(clone* ClonePtr, int count)
{
	printf("\nEnter Clone name: ");
	scanf(" %s", ClonePtr[count].clonename);
	printf("\nEnter Clone rank: ");
	scanf(" %s", ClonePtr[count].rank);
	printf("\nEnter Clone ID: ");
	scanf(" %d", &ClonePtr[count].productid);
	printf("\nEnter Clone PT Score: ");
	scanf(" %d", &ClonePtr[count].ptscore);
	printf("\nEnter Clone Accuracy: ");
	scanf(" %lf", &ClonePtr[count].accuracy);
	printf("\nEnter Clone DNA Integrity: ");
	scanf(" %lf", &ClonePtr[count].dnaintegrity);
}

//displays the ids in the list, gets the id from the user and returns it
int SoundOff(clone squad[], int count)
{
	int i;
	int id;
	for (i = 0; i < count; i++)
	{
		printf("\n%s: %d", squad[i].clonename, squad[i].productid);
	}
	printf("\nEnter ID: ");
	scanf("%d", &id);
	return id;
}

//searches the list by id and returns the index, if there is a match or returns -1 
//three arguments: list, number of items, id
int Accountability(clone squad[], int count, int id1)
{
	int i;
	for (i = 0; i < count; i++)
	{
		if (id1 == squad[i].productid)
		{
			return i;
		}
	}
	return -1;
}

//removes an item from the list 
//takes three arguments, the list, the number of items and the location
void Article15(clone* ClonePtr, int count, int loc)
{
	if (loc == -1)
	{
		//do nothing
	}
	else
	{
		ClonePtr[loc] = ClonePtr[count - 1];
	}
}

//updates PT Score 
//takes three arguments, the list, the number of items and the location
void AlterTheDeal(clone squad[],int count, int loc)
{
	if (loc == -1)
	{
		//do nothing
	}
	else
	{
		printf("\nEnter new PT score: ");
		scanf(" %d", &squad[loc].ptscore);
	}
}
