//Kunal Ojha,IT 2nd Year, Enroll-510817016
//This program accepts an NFA as input and checks whether a given string is accepted or not.
//The program can also accept DFA as a special case of NFA
//The program can have multiple start and multiple final states.
//The program does accept the character '-' for empty next state.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Line
{
	int cur_state;
	int state_type[2]; //whether it is final or statrt or both or nothing.
	char *ns_zero;
	char *ns_one;
}line;
//This structure stores the single description line from the table.
int check(line **t,char s[],int state);
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
int main(void)
{
	label1:
	printf("Please enter the state table of your machine---\n");
	printf("How many states does it have? :");
	int n;
	scanf("%d",&n);
	line *table[n];
	int i;
	for(i=0;i<n;i++)
	{
		printf("\n");
		line *temp = (line *)malloc(sizeof(line));
		temp->cur_state=i;
		temp->state_type[0]=0;
		temp->state_type[1]=0;
		printf("--Details for state q%d--\n",i);
		printf("What kind of state is this? [1:Initial State,(-1):Final State,2:Both final & start,0:Otherwise]:- ");
		int ch;
		scanf("%d",&ch);
		if(ch==1)
			temp->state_type[0]++;
		else if(ch==-1)
			temp->state_type[1]++;
		else if(ch==2)
		{
			temp->state_type[0]++;
			temp->state_type[1]++;
		}
		else
			;
		printf("Enter the states for Input=0 seperated by no space and prefixed with 'q':- ");
		char state_inp[20];
		scanf("%s",&state_inp);
		temp->ns_zero=malloc(strlen(state_inp)+1);
		strcpy(temp->ns_zero,state_inp);
		printf("Enter the states for Input=1 seperated by no space and prefixed with 'q':- ");
		temp->ns_one=malloc(strlen(state_inp)+1);
		scanf("%s",&state_inp);
		strcpy(temp->ns_one,state_inp);
		table[i] = temp;
	}
	label2:
	printf("\nEnter the size of bit string to be tested?: ");
	int m;
	scanf("%d",&m);
	char inp_string[m];
	printf("Enter your bit string: ");
	scanf("%s",inp_string);
	int is = 0;
	for(i=0;i<n;i++)
	{//This loop checks for multiple initial states
		if(table[i]->state_type[0]==1)
			is = (check(table,inp_string,i) || is);
	}
	if(is==0)
		printf("\nThe given string is not accepted by this FA\n");
	else
		printf("\nThe given string is accepted by this FA.\n");
	printf("\nWhat you wish to do?\n");
	printf("1.Create a new FA\n");
	printf("2.Test another String\n");
	printf("3.Exit\nEnter your choice: ");
	int c;
	scanf("%d",&c);
	if(c==1)
		goto label1;
	else if(c==2)
		goto label2;
	else
		;
	return 0;
}
int check(line **t,char s[],int state)
{
	if(strlen(s)==0)
	{//our base case when the string is fully traversed
		if(t[state]->state_type[1]==1)
			return 1;
		else
			return 0;
	}
	int yes=0; //to store the final result;
	char *new_s=substring(s,1,strlen(s)-1);
	char temp_string[20];
	if(s[0]=='0')
		strcpy(temp_string,t[state]->ns_zero);
	else
		strcpy(temp_string,t[state]->ns_one);
	if(strcmp(temp_string,"-")==0)
	{//if an empty next state is found and the string still remains to be scanned
		//then simply return false
		return 0;
	}
	int k;
	for(k=1;k<strlen(temp_string);k+=2)
		yes=(check(t,new_s,temp_string[k]-'0') || yes);  //this loop checks all the possible paths 
	return yes;
}