//Kunal Ojha,IT 2nd Year, Enroll-510817016
//This programs inputs a NFA an constructs an equivalent DFA
//The inputs and next states are of the form q0.....qn
//The next state(s) must be given in without space. 
//E.g.: If next states are q0 qnd q1, the input must be given as q0q1
//Also It accepts null next state as character '-'
//The program always assumes the first state to be the initial state. however it can have more than one
//final state.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Line
{//this structure stores one line form the description table.
	char cur_state[10];
	int state_type[2];
	char ns_zero[10];
	char ns_one[10];
	//can have max of 10 states q0-q9
}line;
void convert(line **t,int n);
void remove_duplicates(char *s);
void sort(char *s);
void print_table(line **t,int n);
void simplify(line **t,int n);
int main(void)
{
	label1:
	printf("\n");
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
		char num[1];
		num[0]=(char)(i+48);
		strcpy(temp->cur_state,num);
		temp->cur_state[1]='\0';
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
		int k;
		int ns_pos=0;
		if(strlen(state_inp)==1)
		{
			temp->ns_zero[0]='-';
			temp->ns_zero[1]='\0';
		}
		else
		{
			for(k=1;k<strlen(state_inp);k+=2)
			{
				temp->ns_zero[ns_pos]=state_inp[k];
				ns_pos++;
			}
			temp->ns_zero[ns_pos]='\0';
		}
		printf("Enter the states for Input=1 seperated by no space and prefixed with 'q':- ");
		scanf("%s",&state_inp);
		ns_pos=0;
		if(strlen(state_inp)==1)
		{
			temp->ns_one[0]='-';
			temp->ns_one[1]='\0';
		}
		else
		{
			for(k=1;k<strlen(state_inp);k+=2)
			{
				temp->ns_one[ns_pos]=state_inp[k];
				ns_pos++;
			}
			temp->ns_one[ns_pos]='\0';
		}
		table[i] = temp;
	}
	//till here all user friendly input and "program-friendly" storage operations are performed
	convert(table,n);// method call
	printf("\n");
	printf("What you wish to do?\n");
	printf("1.Convert another NFA\n");
	printf("2.Exit\n");
	printf("Enter your choice:");
	int choice;
	scanf("%d",&choice);
	if(choice==1)
		goto label1;
	else
		;
}
void convert(line **t,int n)
{
	char array[1<<n][10];//create a stack size of 2^n
	int array_top=-1;
	line *new_table[1<<n];//Array of pointers to structures 
	int top=-1;
	array_top++;
	strcpy(array[array_top],t[0]->cur_state);//pushing the first element in the stack
	while(array_top!=-1)
	{//run the loop while the stack is not empty or while no new combinations are found
		char temp_string[10];
		strcpy(temp_string,array[array_top]);
		array_top--;
		int flag=0;
		int k;
		for(k=0;k<=top;k++)
		{//checking if the combination has occured earlier
			if(strcmp(temp_string,new_table[k]->cur_state)==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{//if a new combination is found
			line *temp = (line *)malloc(sizeof(line));
			temp->state_type[0]=0;
			temp->state_type[1]=0;
			strcpy(temp->cur_state,temp_string);
			char ns0[10],ns1[10];
			ns0[0]='\0';
			ns1[0]='\0';
			if(strcmp(temp_string,"-")==0)
				goto label3;//checking for empty string
			int pos;
			for(pos=0;pos<strlen(temp_string);pos++)
			{
				int c=temp_string[pos]-'0';
				if(strcmp(t[c]->ns_zero,"-")!=0)
					strcat(ns0,t[c]->ns_zero);
				if(strcmp(t[c]->ns_one,"-")!=0)
					strcat(ns1,t[c]->ns_one);
			}
			sort(&ns0[0]);
			sort(&ns1[0]);
			if(strlen(ns0)!=0)
				remove_duplicates(&ns0[0]);  
			if(strlen(ns1)!=0)
				remove_duplicates(&ns1[0]);
			label3:;
			if(strlen(ns0)==0)
			{
				ns0[0]='-';
				ns0[1]='\0';
			}
			if(strlen(ns1)==0)
			{
				ns1[0]='-';
				ns1[1]='\0';
			}
			strcpy(temp->ns_zero,ns0);
			strcpy(temp->ns_one,ns1);
			++array_top; // pushing the next states for two inputs in the stack
			strcpy(array[array_top],ns1);
			++array_top;
			strcpy(array[array_top],ns0);
			++top;
			new_table[top]=temp;//adding the new structure to the new table
		}
	}
	int i;
	new_table[0]->state_type[0]=1;
	for(i=0;i<n;i++)
	{//loop to mark the final state
		if(t[i]->state_type[1]==1)
		{
			int j;
			for(j=0;j<=top;j++)
			{
				int k;
				for(k=0;k<strlen(new_table[j]->cur_state);k++)
				{
					if(new_table[j]->cur_state[k]==t[i]->cur_state[0])
					{
						new_table[j]->state_type[1]=1;
						break;
					}
				}
			}
		}
	}
	simplify(new_table,top+1);
}
void sort(char *s)
{//sorts a given string, making it easier to check for new combination
	int i,j;
	for(i=0;i<strlen(s);i++)
	{
		for(j=0;j<strlen(s)-i-1;j++)
		{
			if((*(s+j))>(*(s+j+1)))
			{
				int ch = *(s+j);
				*(s+j)=*(s+j+1);
				*(s+j+1)=ch;
			}
		}
	}
}
void remove_duplicates(char *s)
{//remove duplicate characters from string if any
	int i;
	for(i=0;i<strlen(s)-1;)
	{
		if(s[i]==s[i+1])
		{
			int k;
			for(k=i;k<strlen(s)-1;k++)
				s[k]=s[k+1];
			s[strlen(s)-1]='\0';
			continue;
		}
		i++;
	}
}
void print_table(line **t,int n)
{
	printf("Present State\t|\t Next State\n");
	printf("-----------------------------------------------------------------------\n");
	printf("             \t|\tInp=0\tInp=1\n");
	printf("-----------------------------------------------------------------------\n");
	int i;
	for(i=0;i<n;i++)
	{
		printf("\t%s ",t[i]->cur_state);
		printf("\t|\t");
		printf("  %s ",t[i]->ns_zero);
		printf("\t");
		printf("  %s ",t[i]->ns_one);
		if(t[i]->state_type[0]==1)
			printf("  (Start State) ");
		if(t[i]->state_type[1]==1)
			printf("  (Final State) ");
		printf("\n");
	}
}
void simplify(line **t,int n)
{//method to simplify the newly constructed DFA 
	int i;
	printf("\nThe equivalent DFA is given by:-\n");
	for(i=0;i<n;i++)
	{
		printf("%c=> ",('A'+i));
		int k;
		for(k=0;k<strlen(t[i]->cur_state);k++)
			printf("q%c ",t[i]->cur_state[k]);
		printf("\n");
	}
	for(i=0;i<n;i++)
	{
		int k;
		for(k=0;k<n;k++)
		{
			if(strcmp(t[i]->ns_zero,t[k]->cur_state)==0)
				break;
		}
		t[i]->ns_zero[0]='A'+k;
		t[i]->ns_zero[1]='\0';
	}
	for(i=0;i<n;i++)
	{
		int k;
		for(k=0;k<n;k++)
		{
			if(strcmp(t[i]->ns_one,t[k]->cur_state)==0)
				break;
		}
		t[i]->ns_one[0]='A'+k;
		t[i]->ns_one[1]='\0';
	}
	for(i=0;i<n;i++)
	{
		t[i]->cur_state[0]='A'+i;
		t[i]->cur_state[1]='\0';
	}
	print_table(t,n);
}