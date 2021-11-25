#include<stdio.h>
#define N 20

int data[N], priority[N];
int rear = -1,front = -1; //Initiation

void enqueue(int Data,int dataprior) //Enqueue function to insert data and its priority in queue
{
	int i;
	if((front==0)&&(rear==N-1)) //Check if Queue is full
		printf("Queue is full");
	else
	{
		if(front==-1)//if Queue is empty
		{
			front = rear = 0;
			data[rear] = Data;
			priority[rear] = dataprior;
		}
		else // If there are some elements in queue
		{
			for(i = rear;i>=front;i--)
			{
				if(dataprior>priority[i]) // Jika masukan prioritas data lebih besar, lakukan pergeseran data dan prioritasnya
				{
					data[i+1] = data[i];
					priority[i+1] = priority[i];
				}
				else
					break;
			}
			//Memasukkan data dan prioritasnya
			data[i+1] = Data;
			priority[i+1] = dataprior;
			rear++;
		}
	}
}

void print() //print the data of Queue
{
    int i;
	for(i=front;i<=rear;i++)
	{
		printf("\nElement = %d\tPriority = %d",data[i],priority[i]);
	}
}

int dequeue() //remove the data from front
{
	if(front == -1)
	{
		printf("Queue is Empty");
	}
	else
	{
		printf("deleted Element = %d\t Its Priority = %d",data[front],priority[front]);
		if(front==rear)
			front = rear = -1;
		else
			front++;
	}
}

int main()
{
	int option,n,i,data,p;
	printf("Enter Your Choice:-");
	do{
		printf("\n\n1 for Insert the Data in Queue\n2 for show the Data in Queue \n3 for Delete the data from the Queue\n0 for Exit\n");
		scanf("%d",&option);
		switch(option){
			case 1:
				printf("\nEnter the number of data: ");
				scanf("%d",&n);
				printf("\nEnter your data and Priority of data : ");
				i=0;
				while(i<n)
                {
					scanf("%d %d",&data,&p);
					enqueue(data,p);
					i++;
				}
				break;
			case 2:
				print();
				break;
			case 3:
				 dequeue();
				break;
			case 0:
				break;
			default:
				printf("\nIncorrect Choice");
		}
	}
	while(option!=0);
        return 0;
}
