//Made By:- Kunal Ojha, IT 2nd Year , 2017-21 , Enroll-510817016
//The program accepts a binary string and creates a state machine
//for detecting the sequence in any binary stream.
//It also prints the state table.
#include <stdio.h>
#include <string.h>
int over_lap(char s[])
{
	//method to find the maximum overlap of any given string
	int shift=0; //the shift given to the string to calculate the overlap
	int i=0;
	int len=strlen(s);
	char t[len];
	strcpy(t,s); //creating an identacal copy of string; one will be shifted and matched with other
	while(shift!=len)
	{
		shift++; //we start with a minimum of one shift as 0 shift would be trivially true
		int flag=0;
		for(i=shift;i<len;i++)
		{
			//instead of actually shifting the string we manipulate the indexing variables
		 	//to achieve this functionality
			if(t[i-shift] != s[i])
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			//in case overlap is successful, we need not go further
			break;
		}
	}
	return (len-shift);//overlap
}
int main()
{
	label1:
	//Input Section
	printf("Enter the length of string:");
	int len;
	scanf("%d",&len);
	char inp[len];
	printf("Enter the sequence of 1 and 0 to be detected: ");
	scanf("%s",&inp);
	//End of input section
	int state_array[len][2];//state table
	int out_array[len][2];//output table
	int i,j;
	for(i=0;i<len;i++)
	{
		for(j=0;j<2;j++)
		{
			//initializing the array elements
			state_array[i][j]=-1;
			out_array[i][j]=-1;
		}
	}
	for(i=0;i<len-1;i++)
	{
		//This part is trivial. Scan the input. From an inital starting state change the state
		//from ith state to (i+1)th state for ith digit in the input sequence(where i>=0).
		//Continue this till second last position.
		//for eg. if the input in 1011; then S0 changes to S1 for input 1; S1 changes to S2 for 0;
		//S2 changes S3 for input 1. Update in state table.
		state_array[i][(int)inp[i]-48]=i+1;
	}
	//for the last digit the arrow turns back to either of the previous or current state
	//like if the max overlap of input string is 2; then the next state for the last state
	//for input equal to last digit would be S2
	//Note that the State numbering starts with 0
	state_array[len-1][(int)inp[len-1]-48]=over_lap(inp);
	for(i=0;i<len;i++)
	{
		for(j=0;j<2;j++)
		{
			//for the remaining empty slots, we scan and extract the string upto i-1 position 
			//from the orignal input and then we add the required empty input to the extracted
			//string. Then we find the overlap of this string to get the next state
			//For example our input is "1010" then we next state for S2 for input 0 empty. So
			//we extract the string upto 1st position i.e "10" and add zero to it to get "100"
			//We then find the max overlap of "100" to be 0. So the next state of S2 for input
			//0 would be S0
			if(state_array[i][j]==-1)
			{
				char temp_String[i+1];
				strcpy(temp_String,"\0");
				strncpy(temp_String,inp,i);
				temp_String[i]='\0';
				if(j==0)
					strncat(temp_String,"00",1);
				else 
					strncat(temp_String,"10",1);
				state_array[i][j]=over_lap(temp_String);
			}
		}
	}
	//output is trivially 1 at just one position
	for(i=0;i<len;i++)
	{
		for(j=0;j<2;j++)
		{
			if(i==len-1 && j==(inp[len-1]-'0'))
				out_array[i][j]=1;
			else
				out_array[i][j]=0;
		}
	}
	//Decorating and aligning the output
	printf("\nThe state table for the sequence detector of given sequence is:\n\n");
	printf("Present State\t|\tNext State/Output\t\t\n");
	printf("-------------------------------------------------------------\n");
	printf("             \t|\t  Inp=0   Inp=1\n");
	printf("--------------------------------------------------------------\n");
	for(i=0;i<len;i++)
	{
	printf("       S%d       |\t   S%d/%d    S%d/%d\n",i,state_array[i][0],out_array[i][0],state_array[i][1],out_array[i][1]);
	}
    label2:
    printf("\nDo you want to test against a random sequence? [1.yes/2.no]: ");
    int ch;
    scanf("%d",&ch);
    if(ch==1)
    {
    	//checking our designed machine against a random bit sequnce
    	int local_len;
   		printf("Enter the size of your bit stream: ");
   		scanf("%d",&local_len);
   		char local_inp[local_len];
   		char local_out[local_len];
   		printf("Enter the bit sequence: ");
   		scanf("%s",&local_inp);
   		int cur_state=0;
   		int cur_out=-1;
   		for(i=0;i<local_len;i++)
   		{
   			local_out[i]=out_array[cur_state][local_inp[i]-'0'];
   			cur_state=state_array[cur_state][local_inp[i]-'0'];
   		}
   		printf("\n");
   		printf("Input Sequence:");
   		for(i=0;i<local_len;i++)
   		{
   			printf(" %d ",local_inp[i]-'0');
   		}	
   		printf("\n");
   		printf("Output        :");
   		for(i=0;i<local_len;i++)
   		{
   			printf(" %d ",local_out[i]);
   		}  	
   	}	
   	label3:
   	printf("\n\n");
   	//options for users
   	printf("What do you wish to do?\n1.Create another detector\n2.Test another sequence\n3.Exit");
   	printf("\nEnter your choice: ");
   	scanf("%d",&ch);
   	if(ch==1)
   		goto label1;
   	else if(ch==2)
   		goto label2;
	return 0;
}