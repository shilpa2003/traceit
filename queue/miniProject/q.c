#include<stdio.h>
//assume: queue:Q1,size:MAX,rear:rear,front:front
int MAX=9;
int Q1[9];
int rear = -1;
int front = -1;

void insert()
{
    int add_item;
    if (rear == MAX - 1)
    printf("Queue Overflow \n");
    else
    {
        if (front == - 1)
        front=0;

        printf("Inset the element in queue : ");
        scanf("%d", &add_item);

        rear=rear+1;
        Q1[rear]=add_item;

    }

}

void delete()
{
	int data;
    if (front == - 1 || front > rear)
    {
        printf("Queue Underflow \n");
        return ;
    }
    else
    {
        printf("Element deleted from queue is : %d\n", Q1[front]);
        Q1[front];
        front=front+1;
    }

}

int main()
{
    int choice;

    while (1)

    {

        printf("1.Insert element to queue \n");

        printf("2.Delete element from queue \n");

        printf("3.Quit \n");

        printf("Enter your choice : ");

        scanf("%d", &choice);

        switch (choice)

        {

            case 1:

            insert();

            break;

            case 2:

            delete();

            break;

            case 3:

            return 0;

            default:

            printf("Wrong choice \n");

        }

    }

}
