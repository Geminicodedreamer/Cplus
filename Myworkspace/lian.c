
// #include<stdio.h>
// #include<stdlib.h>
// typedef struct Node{
// 	int data;
// 	struct Node *next;
// }node;
// int main()
// {
// 	node *head = NULL;
// 	int n,m;
// 	int i;
// 	scanf("%d%d",&n,&m);
// 	if(m == 1) printf("%d",n);
// 	else 
// 	{
// 		node *New=(node *)malloc(1*sizeof(node));
// 		head = New;
// 		for(int i = 1 ; i < n ; i ++)
// 		{
// 			New->data = i;
// 			New = New->next = (node *)malloc(1*sizeof(node));	
// 		}
// 		New->next = head ;
// 		int cnt = 0 , de = 0;
// 		node *p;
// 		for(p = head ; de != n - 1 ; p = p->next){
// 			cnt ++;
// 			if(cnt % (m - 1) == 0) p->next = p->next->next , de ++ ;
// 		}
// 		printf("%d",p->data);
// 	}
	
// 	return 0;
// }

