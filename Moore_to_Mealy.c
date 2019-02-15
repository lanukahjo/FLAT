//Kunal Ojha , 4th Semester, hx-15 , 510817016
//The program inputs a moore machine in a given format.
//All the states must q0,q1,... in this order only.
//However while giving the output only an integer has to be entered.
//Suppose if next state 'q1' then only '1' need to be typed.
//The output is either 0 or 1.
#include <stdio.h>
#include <stdlib.h>
void print_table(int *a,int n);
void convert(int *a,int n);
void main(void)
{//Input Code
	label:;
	printf("\nEnter the details for the Moore Machine:-\n");
	printf("Enter the number of states:-");
	int n;
	scanf("%d",&n);
	int i;
	int moore_table[n][4];
	printf("Enter the details of next state:-\n");
	for(i=0;i<n;i++)
	{
		moore_table[i][0]=i;
		int j;
		printf("--Details for state %d--\n",i);
		for(j=0;j<2;j++)
		{
			printf("Enter the next state number for Input=%d: ",j);
			scanf("%d",&moore_table[i][j+1]);
		}
		printf("Enter the output for State %d: ",i);
		scanf("%d",&moore_table[i][3]);
	}
	//end of input code
	convert(&moore_table[0][0],n);
	printf("\nDo you wish to convert another machine?\n1.Yes\n2.No\nEnter your choice:");
	int ch;
	scanf("%d",&ch);
	if(ch==1)
		goto label;
	else ;
}
void convert(int *a,int n)
{//method to convert a moore machine to mealy machine
	int mealy_table[n][5];
	int i;
	for(i=0;i<n;i++)
	{
		mealy_table[i][0]=i;
		mealy_table[i][1]=*(a+(i*4)+1);
		mealy_table[i][3]=*(a+(i*4)+2);
		mealy_table[i][2]=*(a+(mealy_table[i][1]*4)+3);
		mealy_table[i][4]=*(a+(mealy_table[i][3]*4)+3);
	}
	//mealy machine created
	print_table(&mealy_table[0][0],n);
}
void print_table(int *a,int n)
{//method to print the mealy table in the format
	printf("\nThe Mealy Machine for the given Moore machine is:-\n\n");
	printf("Present State |\tNext State\\Output\n");
	printf("-----------------------------------------------------\n");
	printf("              |");
	int i;
	for(i=0;i<2;i++)
		printf(" Inp=%d ",i);
	printf("\n");
	printf("-----------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("       q%d     |",i);
		int j;
		for(int j=0;j<2;j++)
		{
			printf("  q%d/%d  ",(*(a+i*(5)+(2*j+1))),(*(a+i*(5)+(2*j+2))));
		}
		printf("\n");
	}
	printf("\n");
}