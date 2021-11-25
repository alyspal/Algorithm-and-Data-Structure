#include <stdio.h>

#define MAX 10

/*Returns parent index*/
int parent(int i){
	return i/2;
}

/*Returns left child index*/
int left(int i){
	return 2*i;
}

/*Returns right child index*/
int right(int i){
	return 2*i+1;
}

/*This function is used to swap two elements*/
void swap(int *p, int *q){
	int temp;
	temp=*p;
	*p=*q;
	*q=temp;
}

void insert(int a[],int heapsize,int data){
	int i,p;
	if(heapsize==MAX){
		printf("Queue Is Full!!\n");
		return;
	}
	i=1+heapsize;
	a[i]=data;
	p=parent(i);
	while(i>1 && a[p]<a[i]){
		swap(&a[p],&a[i]);
		i=p;
		p=parent(i);
	}
}

/*This function deletes an element from the queue*/
int delete(int a[],int heapsize){
	int data,i,l,r,max_child,t;
	if(heapsize==0)	{
		printf("Queue Is Empty!!\n");
		return 0;
	}
	t=a[1];
	swap(&a[1],&a[heapsize]);
	i=1;
	heapsize--;
    while(1){
		if((l=left(i))>=heapsize) //leaf
            break;

		if((r=right(i))>=heapsize) //leaf
            max_child=l;
		else
            max_child=(a[l]>a[r])?l:r; //which one is larger, left or right

		if(a[i]>=a[max_child])
            break;

		swap(&a[i],&a[max_child]);
		i=max_child;
	}
	return t;
}

/*This function displays the queue*/
void display(int a[],int n){
	int i;
	if(n==0){
		printf("Queue Is Empty!!\n");
		return;
	}
	for(i=1;i<=n;i++) printf("%d ",a[i]);
	printf("\n");
}

void main(){
	int choice,num,n,a[MAX],data,s;
	n=0;/*Represents number of nodes in the queue*/
	while(1){
		printf(".....MAIN MENU.....\n");
		printf("\n1.Insert.\n");
		printf("2.Delete.\n");
		printf("3.Display.\n");
		printf("4.Quit.\n");
		printf("\nEnter your choice : ");
		scanf("%d",&choice);

        switch(choice){
			case 1:/*choice to accept an element and insert it in the queue*/
				printf("Enter data to be inserted : ");
				scanf("%d",&data);
				insert(a,n,data);
				n++;
				break;
			case 2:
				s=delete(a,n);
				if(s!=0) printf("\nThe deleted value is : %d \n",s);
				if(n>0) n--;
				break;
            case 3: //display
				printf("\n");
				display(a,n);
				break;
			case 4: return;
			default: printf("Invalid choice.\n");
		}
		printf("\n\n");
	}
}
