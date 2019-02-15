//Kunal Ojha, 4th Semeter, Hx-15,510817016
//The program inputs a number n and creates a moore machine for mod-n counter
//Input is an Integer.
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
void createMachine(int n);
char* deciTobin(int n)
{//return the binary equivalent of a decimal number in reverse order
	if(n==0)
		return "0";
	char *ret;
	ret = malloc(log(n)/log(2)+2);
	ret[0]='\0';
	while(n>0)
	{
		int t=n%2;
		if(t==1)
			strcat(ret,"1");
		else
			strcat(ret,"0");
		n/=2;
	}
	return ret;
}
void main()
{ //Input Code
	printf("--Welcome to Mod-N counter creator.--\n");
	label:;
	printf("Enter the value of N : ");
	int n;
	scanf("%d",&n);
	createMachine(n);//machine creation function
	printf("\nDo you wish to create another machine?\n1.Yes\n2.No\nEnter your choice:");
	int ch;
	scanf("%d",&ch);
	if(ch==1)
		goto label;
	else ;
}
void createMachine(int n)
{ //method to create the machine
	int state_table[n][2];
	int i;
	for(i=0;i<(n<<1);i++)
	{ //in 2n steps all possible combinations are covered . rest are repetitions
		char *temp;
		temp = malloc(n+1);
		strcpy(temp,deciTobin(i));
		int j;
		int cur_state=0;
		for(j=strlen(temp)-1;j>=0;j--)
		{//traversing each binary string to find where it ends
			if(j==0)
			{
				if(temp[0]=='1')
					state_table[cur_state][1]=i%n;
				else
					state_table[cur_state][0]=i%n;
			}
			else
				cur_state=state_table[cur_state][temp[j]-'0'];
		} 
	}
	//output code
	printf("\nThe Moore Machine for Mod-%d counter is:-\n\n",n);
	printf("Present State |\tNext State\n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("              |");
	for(i=0;i<2;i++)
		printf(" Inp=%d ",i);
	printf("\n");
	printf("------------------------------------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("       q%d     |",i);
		int j;
		for(int j=0;j<2;j++)
		{
			printf("  q%d    ",state_table[i][j]);
		}
		printf("Output=%d",i);
		printf("\n");
	}
	printf("\n");
}