#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print(void *p)
{
	int i ; 
	int num = *(int*)(p);
	int sum  = 0;
	for(i=1;i<=num;i++)
	sum += i;
	printf("sum : %d\n",sum);
	pthread_exit(0);
}


int main(int argc , char *argv[])
{
   pthread_t thread;
   if(argc!=2) 
   {
       printf("\nWRONG NUM OF ARG GIVEN\n");
       return -1;
   }   

   if(atoi(argv[1])< 0) 
   {
       printf("\nARG SHOULD BE GREATER THAN 0\n");
       return -1;
   }
   
   int a = atoi(argv[1]);
   
   pthread_create(&thread , NULL , print , &a);
   pthread_join(thread , NULL);
   
   return 0;
}