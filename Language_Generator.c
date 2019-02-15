//Made By:- Kunal Ojha, IT 2nd Year , 2017-21 , Enroll-510817016
//The program creates a laguage from a given grammar upto a certain level.
//The grammar is accepted from the user in form of productions.
//The program can only process context free grammar.
//Firstly the user needs to enter the number of production rules
//Then the user shall to asked to enter a terminal. Note that the non-terminal should a capital letter.
//All capital letters are treated as non-terminals and their number must be equal to number of productions
//After entering the non terminals prompt the user to enter the no. of productions for the terminal
//Then enter the productions, one in a line.
//The produtions may be any combination of Terminals and any other symbol except "#"" which denotes empty string
//The enter the level upto which you wish to print the strings in a language. Wait for the result.
//Limitations: The program can take a maximum of 10 Non Terminals
//           : For each non-terminal, there can be at most 20 produtions
//			 : Each production for a non terminal can be 6 characters at max
//           : The program can handle a max string size of 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void createLanguage(char[],int);
int find(char,char[]);
char *substring(char *string, int position, int length);
char rules[10][21][6];
char NT[10];
int globe;
void main()
{
	int i;
	label1:;
	//Input portion
	printf("Enter number of production rules: ");
	int n;
	scanf("%d",&n);
	for(i=0;i<10;i++)
	{
		int j;
		for(j=0;j<11;j++)
		{
			strcpy(rules[i][j],"\0");
		}
	}
	for(i=0;i<n;i++)
	{
		printf("Enter the non-terminal:");
		scanf("%s",&rules[i][0]);
		NT[i]=rules[i][0][0];
		printf("How many productions you wish to enter for this terminal?: ");
		int m;
		scanf("%d",&m);
		int j;
		printf("Enter the rules:\n");
		for(j=1;j<=m;j++)
		{
			scanf("%s",&rules[i][j]);
		}
	}
	label2:;
	printf("Upto what level you wish to print the string?: ");
	scanf("%d",&globe);
	//End of Input section
	//Printing the grammar in standard format
	printf("\nThe grammar is:\n");
	for(i=0;i<n;i++)
	{
		printf("%s->",rules[i][0]);
		int j;
		for(j=1;j<21;j++)
		{
			if(strcmp(rules[i][j],"\0")==0)
				break;
			printf("%s/",rules[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("The language upto level %d is:\n",globe);
	createLanguage(rules[0][0],0);
	printf("\nWhat you wish to do?\n1.Create new Grammar\n2.Create new Level\n3.Exit\nEnter your choice:");
	int choice; //end choices
	scanf("%d",&choice);
	if(choice==1)
		goto label1;
	else if(choice==2)
		goto label2;
	else;
}
void createLanguage(char start[],int l)
{
	//recursive function to print language
	if(l>globe) //if the highest level is reached
		return;
	char temp_String[100];
	strcpy(temp_String,start);
	int pos_cap=-1; //store the position of first capital letter from the left
	int j;
	char ch;
	for(j=0;j<strlen(temp_String);j++)
	{//finding the postion of first non-terminal from the left
		if(temp_String[j]>='A' && temp_String[j]<='Z')
		{
			ch=temp_String[j];
			pos_cap=j;
			break;
		}
	}
	if(pos_cap==-1)
	{
		//no non terminal exists
		int k;
		printf(">>Level %d: ",l);
		if(strcmp(temp_String,"#")==0) //special case to handle #(epsilon)
			printf("<Empty String>");
		for(k=0;k<strlen(temp_String);k++)
		{
			if(temp_String[k]=='#')
				continue;
			printf("%c",temp_String[k]);
		}
		printf("\n");
		goto W;
	}
	int pos = find(ch,NT);
	int i;
	for(i=1;i<20;i++)
	{//Here we replace the non terminal by all possible functions and perform recursion on the replaced string
		char new[100];
		strcpy(new,"\0");
		if(pos_cap!=0)//string before non-terminal
			strcat(new,substring(temp_String,0,pos_cap));
		if(strcmp(rules[pos][i],"\0")==0)
		{
			//if null is encountered do nothing
			goto W;
		}
		char local_rule[6];
		strcpy(local_rule,rules[pos][i]);
		strcat(new,local_rule);
		char super_local[100];
		strcpy(super_local,new);
		if(pos_cap!=(strlen(temp_String)-1)) //string after non terminal
			strcat(super_local,substring(temp_String,pos_cap+1,strlen(temp_String)-pos_cap-1));
		createLanguage(super_local,l+1);
	}
	W:;
}
int find(char ch,char nt[])
{
	//finding the position of given non terminal
	int i;
	for(i=0;i<strlen(nt);i++)
	{
		if(ch==nt[i])
			return i;
	}
	return -9999;
}
char *substring(char *string, int position, int length)
{
	//function to find substring
   char *pointer;
   int c;
   pointer = malloc(length+1);
   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *(string+position);      
      string++;  
   }
   *(pointer+c) = '\0';
   return pointer;
}