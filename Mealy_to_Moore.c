//Kunal Ojha, 4th Semester,Hx-15,510817016
//The program accepts a mealy machine and creates an equivalent moore machine
//All the states must q0,q1,... in this order only.
//However while giving the output only an integer has to be entered.
//Suppose if next state 'q1' then only '1' need to be typed.
//The program can only handle q0-q9
//The output is either 0 or 1.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void convert(int *a,int n);
void main(void)
{
	//Input Code
	label1:;
	printf("\nEnter the details for the Mealy Machine:-\n");
	printf("Enter the number of states:-");
	int n;
	scanf("%d",&n);
	int i;
	int mealy_table[n][5];
	printf("Enter the details of next state:-\n");
	for(i=0;i<n;i++)
	{
		mealy_table[i][0]=i;
		int j;
		printf("--Details for state %d--\n",i);
		for(j=0;j<2;j++)
		{
			printf("Enter the next state number for Input=%d: ",j);
			scanf("%d",&mealy_table[i][2*j+1]);
			printf("Enter the output for Input=%d: ",j);
			scanf("%d",&mealy_table[i][2*j+2]);
		}
	}
	convert(&mealy_table[0][0],n);
	printf("\nDo you wish to convert another machine?\n1.Yes\n2.No\nEnter your choice:");
	int ch;
	scanf("%d",&ch);
	if(ch==1)
		goto label1;
	else ;
}
void convert(int *a,int n)
{//method to convert to equivalent moore machine
	int ns[n][2];
	int i;
	for(i=0;i<n;i++)
	{
		int j;
		for(j=0;j<2;j++)
			ns[i][j]=0;
	}
	for(i=0;i<n;i++)
	{//finding which states have contardicting outputs 
		ns[*(a+i*5+(1))][*(a+i*5+(2))]++;
		ns[*(a+i*5+(3))][*(a+i*5+(4))]++;
	}
	int count=0;
	for(i=0;i<n;i++)
		if(ns[i][0]>0 && ns[i][1]>0)
			count++; //finding the number of states in "expanded" moore table
	count+=n;
	char moore_table[count][4][3];
	int k=0;
	for(i=0;i<n;i++)
	{
		if(ns[i][0]>0 && ns[i][1]>0)
		{//partitioning the states
			moore_table[k][0][0]='0'+i;
			moore_table[k][0][1]='0';
			moore_table[k][0][2]='\0';
			k++;
			moore_table[k][0][0]='0'+i;
			moore_table[k][0][1]='1';
			moore_table[k][0][2]='\0';
			k++;
		}
		else
		{
			moore_table[k][0][0]='0'+i;
			moore_table[k][0][1]='\0';	
			k++;
		}
	}
	for(i=0;i<count;i++)
	{//filiing in the next states
		int j;
		for(j=0;j<2;j++)
		{
			int next=(*(a+(moore_table[i][0][0]-'0')*5+(2*j+1)));
			if(ns[next][0]>0 && ns[next][1]>0)
			{
				if((*(a+(moore_table[i][0][0]-'0')*5+(2*j+2)))==0)
				{
					moore_table[i][j+1][0]='0'+next;
					moore_table[i][j+1][1]='0';
					moore_table[i][j+1][2]='\0';
				}
				else
				{
					moore_table[i][j+1][0]='0'+next;
					moore_table[i][j+1][1]='1';
					moore_table[i][j+1][2]='\0';
				}
			}	
			else
			{
				moore_table[i][j+1][0]='0'+next;
				moore_table[i][j+1][1]='\0';
			}
		}
	}
	for(i=0;i<count;i++)
	{//filing in the output
		int p=moore_table[i][0][0]-'0';
		if(ns[p][0]>0 && ns[p][1]>0)
			moore_table[i][3][0]=moore_table[i][0][1];
		else if(ns[p][0]>0)
			moore_table[i][3][0]='0';
		else
			moore_table[i][3][0]='1';
	}
	//printing part
	printf("\nThe equivalent Moore Machine for the given Mealy Machine is:-\n\n");
	printf("Present State |\tNext State\n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("              |");
	for(i=0;i<2;i++)
		printf(" Inp=%d ",i);
	printf("\n");
	printf("------------------------------------------------------------------------------------------\n");
	int flag=0;
	if(moore_table[0][3][0]=='1')
	{//if the output for first state is 1 then add one extra line
		if(strlen(moore_table[0][0])==1)
			printf("      >qa     |");
		else
			printf("      >q%s    |",moore_table[0][0]);
		if(strlen(moore_table[0][1])==1)
			printf("  q%s    ",moore_table[0][1]);
		else
			printf("  q%s   ",moore_table[0][1]);
		if(strlen(moore_table[0][2])==1)
			printf("  q%s    ",moore_table[0][2]);
		else
			printf("  q%s   ",moore_table[0][2]);
		printf("Output=0\n");
		flag=1;
	}
	for(i=0;i<count;i++)
	{
		if(i==0 && flag!=1)
			printf("      >");
		else
			printf("       ");
		if(strlen(moore_table[i][0])==1)
			printf("q%s     |",moore_table[i][0]);
		else
			printf("q%s    |",moore_table[i][0]);
		int j;
		for(int j=0;j<2;j++)
		{
			if(strlen(moore_table[i][j+1])==1)
				printf("  q%s    ",moore_table[i][j+1]);
			else
				printf("  q%s   ",moore_table[i][j+1]);
		}
		printf("Output=%c",moore_table[i][3][0]);
		printf("\n");
	}
	printf("\n");
}