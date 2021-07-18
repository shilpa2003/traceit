#include<stdio.h>
//in main
//opening file to write data in output file
FILE *fptr;
//assume: stack:stack1,size:MAXSIZE1,top:top1
int MAXSIZE1 = 5;
int top1 = -1;
int stack1[5];

void push1(int data) {

   if(top1!=MAXSIZE1) {
	   top1=top1+1;
fprintf(fptr,"top1:%d;\n",top1);

	   stack1[top1]=data;
fprintf(fptr,"stack1:%d:%d;\n",top1,stack1[top1]);

   }
   else {
	   printf("Could not insert data, Stack is full.\n");
   }
}

int pop1() {
   int data;

   if(top1!=(-1)) {
      data=stack1[top1];
fprintf(fptr,"stack1:%d:%d;\n",top1,stack1[top1]);

      printf("\ndata : %d\n",data);
      top1=top1 - 1;
fprintf(fptr,"top1:%d;\n",top1);

      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

int main()
{
fptr=fopen("./output.txt","w+");
fputs("stack:stack1,size:MAXSIZE1,top:top1;\n",fptr);
fputs("initial:MAXSIZE1:5,top1:-1;\n",fptr);
int var1;
 int choice;

    while (1)

    {

        printf("1.Push Element On Stack\n");

        printf("2.Pop Element From Stack\n");

        printf("3.Quit \n");

        printf("Enter your choice : ");

        scanf("%d", &choice);

        switch (choice)

        {

            case 1:
			printf("Enter Element : ");
			scanf("%d",&var1);
			push1(var1);
            break;

            case 2:

            pop1();

            break;

            case 3:

            return 0;

            default:

            printf("Wrong choice \n");

        }
        }
return 0;
}

