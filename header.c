// header.c


#include"header.h"

product *Add(product *head){

	product *temp=NULL,*nu;
	nu=calloc(1,sizeof(product));
	if(nu==NULL){
		printf("Memory is Allocated.\n");
		return head;
	}

	__fpurge(stdin);
	printf("Enter Product Name : ");
	scanf("%s",nu->name);
	printf("Enter Product Id : ");
	scanf("%d",&nu->id);
	printf("Enter Cost : ");
	scanf("%f",&nu->cost);
	printf("Enter Quantity : ");
	scanf("%d",&nu->quantity);


	if(head==NULL){
		head=nu;
	}
	else{

		temp=head;
		while(temp->link){
			temp=temp->link;
		}
		temp->link=nu;
	}
	return head;
}

void View(product *head)
{
	__fpurge(stdin);
	if(head==NULL)
	{
		printf("No Item Available in List.......\n");
		sleep(2);
	}
	else
	{

		printf("--------------------------------- < Item List > -------------------------------\n");
		printf("\tId\tName\tCost\tQuantity\n");
		while(head)
		{
			printf("\t%d\t%s\t%0.2f\t%d\n",head->id,head->name,head->cost,head->quantity);
			head=head->link;
		}

	}
}


product *Delete(product *head)
{

	product *temp=NULL,*pptr=NULL;
	int id;
	if(head==NULL){
		printf("No Item Available in List.......\n");
		sleep(1);
	}
	else{
		printf("Enter Id : ");
		scanf("%d",&id);
		if(id==head->id){

			temp=head;
			head=head->link;
			free(temp);
		}
		else{


			pptr=head;
			temp=head->link;
			while( temp &&temp->id!= id ){
				pptr=temp;
				temp=temp->link;
			}

			if(temp==NULL)
			{

				printf("> %d Card ID Not Available to Delete.......\n",id);
				sleep(2);
			}
			else{

				pptr->link=temp->link;
				free(temp);
			}

		}
	}
	return head;

}

product * Menu(product *head)
{
	system("clear");
		char ch;
	while(1)
	{
		printf("---------------------Maneger Cart-----------------------\n");
		printf("A : Add   V : View    D : Delete   U : Update   R : Return\n");
		printf("Enter Your Choice : ");
		__fpurge(stdin);
		//fflush(stdin);
		scanf("%c",&ch);

		switch(ch){
			case 'a':
			case 'A':head=Add(head);
				 break;
			case 'v':
			case 'V':View(head);
				 break;
			case 'd':
			case 'D':head=Delete(head);
				 break;
			case 'u':
			case 'U':head=Update(head);
				 break;
			case 'r':
			case 'R':system("clear");
				 return head;

			default:printf("Invalid Choice \n");

		}
		sleep(1);
		//getchar();
		system("clear");
	}
	return head;
}

void Saveitem(product *head) {
	int size_struct=(sizeof(product)-8);
	FILE *fp;
	fp = fopen("itemlist", "w");
	if (fp == NULL) {
		printf("Error opening file for writing\n");
		return;
	}

	while (head) {
		fwrite(head, size_struct, 1, fp);
		head = head->link;
	}

	fclose(fp);
}

product *Syncitem(product *head)
{
	int size_struct=(sizeof(product)-8);
	FILE *fp = fopen("itemlist", "r");
	if (fp == NULL) {
		printf("Error opening file for reading\n");
		return head;
	}

	product temp;
	while (fread(&temp, size_struct, 1, fp) == 1) {
		product *nu = (product *)malloc(sizeof(product));
		if (nu == NULL) {
			printf("Memory allocation failed\n");
			return head;
		}
		memcpy(nu, &temp, size_struct);

		if(head==NULL)
			head=nu;
		else
		{
			product *temp=head;
			while(temp->link)
				temp=temp->link;
			temp->link=nu;
		}
	}

	fclose(fp);
	return head;
}

product *Update(product *head)
{

	product *temp=NULL;
	int id;
	if(head==NULL)
	{
		printf("No Item Available in List.......\n");
		sleep(2);
	}
	else
	{
		int quantity;
		float cost;
		char ch;

		printf("Enter Id : ");
		scanf("%d",&id);
		__fpurge(stdin);

		printf("A.Update Quantity\nB.Update Cost\nC.Both\n");
		printf("Enter Choice : ");
		scanf("%c",&ch);
		__fpurge(stdin);


		if(ch=='A'||ch=='C'||ch=='a'||ch=='c')
		{
			printf("Enter New Quantity : ");
			scanf("%d",&quantity);
		}
		if(ch=='B'||ch=='C'||ch=='b'||ch=='c')
		{
			printf("Enter New Cost : ");
			scanf("%f",&cost);
		}

		if(id==head->id){

			if(ch=='A'||ch=='C'||ch=='a'||ch=='c')
				head->quantity=quantity;
			if(ch=='B'||ch=='C'||ch=='b'||ch=='c')
				head->cost=cost;
		}
		else{

			int i=1;
			temp=head;
			while( temp && temp->id != id ){
				temp=temp->link;
			}

			if(temp==NULL){
				printf(">%d Card ID not found in list.\n",id);
				sleep(2);
			}
			else{
				if(ch=='A'||ch=='C'||ch=='a'||ch=='c')
					temp->quantity=quantity;
				if(ch=='B'||ch=='C'||ch=='b'||ch=='c')
					temp->cost=cost;
			}

		}
	}
	return head;

}

