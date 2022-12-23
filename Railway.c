//this the main file everything meets here
#include<stdio.h>//ye toh sabse important hai
#include<stdlib.h>//for malloc() and exit()
#include<stdbool.h>//for type bool
#include<string.h>//string functions
#include<time.h>//for clock() function
struct person{
	char user_name[10];//it contains the name of the person
	char train_name[10];//it contains the name of train the person is travelling in
	int train_no;//it contains the train number of the train
	int password;//it contains the login password for the user
	char ph_no[11];//it contains the phone number of the user
	short int coach_type;//seat type 0-GN 1-Sl 2-1A 3-2a 4-3a 
	bool seat_status;//this checks if the seat has been allocated or not
	short int seat_type;//lower(1) or middle(2) or upper(3) or side lower(4) or side upper(5)
	short int seat_no;//the seat no allocated to the person
	float cost;//the cost of the ticked
	struct person*next;//doubly linked list to traverse along the persons travelling in the train
	struct person*prev;
};
struct train{
	char date[11];//Date of train travel, the each train is distinct with its own date
	//for example if a user wants to travel at a new date,a new train structure will be created
	//and all the seats will be set to vacant
	int n;//this int value is to identify the train ex:- 1.rajdhani 2.mumbai 3.Shatabdi 4.Humsafar
	bool vacancy[5][80];//vacancy of 80 seats and the 5 array index means that there are five coaches with 80 seats
	int waiting_list[5];//waiting list of each of the five coaches
	struct train *next;//singly liked list to traverse available train at different dates
};
void starting_display(void);//the starting display funciton 
typedef struct train* TRAIN_NODE;
typedef struct person* USER_NODE;
const char*TRAINS[4]={"Rajdhani Exp","Mumbai Exp","Shatabdi Exp","Humsafar Exp"};//train names
const long int TRAIN_NOS[4]={22691,16332,12028,15705};//train numbers
USER_NODE modify_person(USER_NODE,int,int,TRAIN_NODE);//this function adds the train name,train no,cost of seat etc to a person
TRAIN_NODE train_function(TRAIN_NODE,USER_NODE,int); //train function handles all the train operations 
USER_NODE new_account(USER_NODE); //creates new account for the user
USER_NODE existing_account(USER_NODE);//traverses DLL to find the existing user account if not found reports null
USER_NODE relocator(USER_NODE);//relocates the person pointer to the first node
USER_NODE makenew(USER_NODE,int,int,TRAIN_NODE);//makes a new user
void ticket_display(USER_NODE);//displays a users ticket
void payment(USER_NODE);//handles payment
USER_NODE cancel_ticket(TRAIN_NODE,USER_NODE);//ticket cancellations
int main(void)
{
	starting_display();//display the starting page
	TRAIN_NODE train=NULL;
	USER_NODE person_curr=NULL;
	printf("\n\n1.New User(sign in)\t2.Existing User(login)\t3.Cancel Ticket to quit\n");
	int user_opt;
	while(scanf("%d",&user_opt)==1)//run the loop untill a character(q) is pressed
	{
		switch(user_opt)
		{
			case 1: person_curr=new_account(person_curr);break;
			case 2: person_curr=existing_account(person_curr);
					if(person_curr==NULL)//if an existing account was not found with the username
					{
						printf("\n\n\t\t\tPlease try again\n");
						continue;
					}
					break;
			case 3:	person_curr=cancel_ticket(train,person_curr);
					if(person_curr==NULL)//if train with specified date was not found and user also was not found
					{
						printf("\n\n\t\t\tPlease try again\n");
						continue;
					}
					break;
			default:printf("\nPlease choose the right option\n");continue;
		}
		printf("\n\n\t\t\t\t\t\t****TRAIN CHART****\n\n\n");
		printf("Train Name\t\tTrain Number\tSource\t\t\tDestination\t\tDeparture\t\tJouney Time\n\n");
		printf("1.Rajdhani Exp\t\t22691\t\tBangalore\t\tHyderabad\t\t8:00PM\t\t\t11h35m\n\n");
		printf("2.Mumbai Exp  \t\t16332\t\tBangalore\t\tMumbai   \t\t9:30PM\t\t\t23h20m\n\n");
		printf("3.Shatabdi Exp\t\t12028\t\tBangalore\t\tChennai  \t\t6:00AM\t\t\t5hours\n\n");
		printf("4.Humsafar Exp\t\t15705\t\tBangalore\t\tDelhi    \t\t1:55PM\t\t\t48h55m\n\n");
		printf("\nSelect a train(q to quit):\t");
		short int op;//this is to select a train from any of the above trains
		while(scanf("%d",&op)==1)//run loop untill a character is pressed
		{
			if(op>4||op<1)
			{
				printf("\n\nPlease type a valid train option('q'to quit):\t");
				continue;
			}
			train=train_function(train,person_curr,op);//train function takes train node,person node,and the train_choice
			break;
		}
		person_curr=relocator(person_curr);//this takes back the person pointer to first person
		printf("\n\n1.New User(sign in)\t2.Existing User(login)\t3.Cancel Ticket to quit\n");
	}
	return 0;
}
//----------------------------------------------------------------------------------------------
USER_NODE new_account(USER_NODE first)//takes a user node as arguement and creates a new node
{
	USER_NODE curr=first;//helpful for the else condition
	if(first==NULL)//check if no user is present in the train
	{
		first=(USER_NODE)malloc(sizeof (struct person));//create the first user
		printf("\n\n\tPlease type your username:\t");
		scanf("%s",first->user_name);
		printf("\n\n\tPlease type your Phone number:\t");
		scanf("%s",first->ph_no);
		printf("\n\n\tPlease set a (4 digit)password for you account:\t");
		scanf("%d",&first->password);
		first->prev=NULL;//user node is a doubly linked list hence the first user has both its pointers set to null
		first->next=NULL;
		return first;
	}
	else
	{
		while(curr->next!=NULL)//if earlier a user was present,add the new user to last of linked list
			curr=curr->next;
		USER_NODE new=(USER_NODE)malloc(sizeof (struct person));//create a new node
		printf("\n\n\tPlease type your username:\t");
		scanf("%s",new->user_name);
		printf("\n\n\tPlease type your Phone number:\t");
		scanf("%s",new->ph_no);
		printf("\n\n\tPlease set a (4 digit)password for you account:\t");
		scanf("%d",&new->password);
		new->prev=curr;//last node is set
		new->next=NULL;
		curr=curr->next;
	}
	return curr;//returns the current user info
}
//-----------------------------------------------------------------------------------------
USER_NODE existing_account(USER_NODE first)//if account with given username exists returns that else returns NULL
{
	if(first==NULL)
	{
		printf("\n\nThere is no existing user present\n");
		return first;
	}
	USER_NODE curr=first;
	printf("\n\nPlease type your username:\t");
	char username[20];
	scanf("%s",username);//user inputs the username
	while(curr!=NULL&&strcmp(curr->user_name,username))//checks if the username was correct if yes exits
		curr=curr->next;
	if(curr==NULL)//if the username was not found in the whole list,displays error and returns NULL
	{
		printf("\nThere is no account with this username\n");
		return curr;
	}
	printf("\n\n\t\tType the account password:\t");//validates the user by checking his password
	int pass;
	while(scanf("%d",&pass)==1)//checks the password untill the password is correct
	{
		if(pass==curr->password)
			break;
		printf("\n\n\t\tWrong password try again:\t");
	}
	return curr;// return the existing account
}
//----------------------------------------------------------------------------------------------------------------
TRAIN_NODE train_function(TRAIN_NODE first,USER_NODE person,int t)
{
	strcpy(person->train_name,TRAINS[t-1]);
	person->train_no=TRAIN_NOS[t-1];
	int i=0;
	while(i++<80)
		putchar('-');
	printf("\n\t\t\t%s\n",TRAINS[t-1]);//displays the selected train name according to arguement 't'
	i=0;
	while(i++<80)
		putchar('-');
	printf("\n\nPlease type the date of travel(dd/mm/yyyy):\t");
	char date[11];
	scanf("%s",date);//here the user has to type the valid date format (dd/mm/yy) else program becomes faulty
	TRAIN_NODE curr =first;
	if(first==NULL)//if there is no current train registered create a new train according and set that date
	{
		first=(TRAIN_NODE)malloc(sizeof(struct train));
		strcpy(first->date,date);
		first->n=t;//gives the train the train number
		first->next=NULL;
		int i,j;
		for(i=0;i<5;i++)
			for(j=0;j<80;j++)
				first->vacancy[i][j]=true;//for new train all seats are set to vacant
		for(i=0;i<5;i++)
					first->waiting_list[i]=0;//waiting list is 0 for a new train
		curr=first;
	}
	else
	{//if earlier a train was present check the train date,if the date matches,then jump to that train
		while(strcmp(date,curr->date)!=0&&curr->next!=NULL)
			curr=curr->next;
		if(strcmp(date,curr->date)==0)
		{//if the train with given date is found but the train number match
			//for example for a single date there can be 4 trains 
			if(curr->n!=t)//create a train with same date but different train no
			{
				TRAIN_NODE new=(TRAIN_NODE)malloc(sizeof(struct train));
				strcpy(new->date,date);
				new->n=t;
				new->next=NULL;
				int i,j;
				for(i=0;i<5;i++)
					for(j=0;j<80;j++)
						new->vacancy[i][j]=true;
				for(i=0;i<5;i++)
						new->waiting_list[i]=0;
				curr->next=new;
				curr=curr->next;
			}
		}
		if(curr->next==NULL&&strcmp(date,curr->date)!=0)//if train with given date is not fount create a new train
		{
			TRAIN_NODE new=(TRAIN_NODE)malloc(sizeof(struct train));
			strcpy(new->date,date);
			new->n=t;
			new->next=NULL;
			int i,j;
			for(i=0;i<5;i++)
				for(j=0;j<80;j++)
					new->vacancy[i][j]=true;
			for(i=0;i<5;i++)
					new->waiting_list[i]=0;
			curr->next=new;
			curr=curr->next;
		}
	}
	printf("\n\n\t\t%s \t%s\n",TRAINS[t-1],date);
	printf("\n\nFare:\tGN:210\tSL:350\t1A:2355\t2A:1355\t3A:760");
	float fare[5]={210,350,2335,1355,760};
	printf("\n\nVacancy:\tGN\tSL\t1A\t2A\t3A");
	printf("\n\t\t");
	for( i=0;i<5;i++)
	{
		int count=0;
		int j;
		for(j=0;j<80;j++)
			if((curr->vacancy[i][j])==true)
				count++;
		printf("%d\t",count);//print the vacancies of each coach
	}
	printf("\n\nSelect the coach type:\t");
	printf("\n\n\t\t1. GEN\t2. SL\t3. 1A\t4. 2A\t5. 3A ('q' to quit)");
	int coach_type;
	while(scanf("%d",&coach_type)==1)
	{
		if(coach_type<1||coach_type>5)
		{
			printf("\n\nPlease type the right option\n\n");
			printf("\n\n\t\t1. GEN\t2. SL\t3. 1A\t4. 2A\t5. 3A ('q' to quit)");
			continue;
		}
		break;
	}
	printf("\n\nType the number of tickets you want:\t");//a person can book n tickets for his family
	int no_tickets;scanf("%d",&no_tickets);
	printf("\n\nPlease type the preferred seat type for first ticket:\n");
	printf("\n\t\t1.UPPER(U)\t2.MIDDLE(M)\t3.LOWER(L)\t4.SIDE LOWER(SL)\t5.SIDE UPPER(SU)(Q to quit):");
	int k;//takes the first user preference of seat type
	while(scanf("%d",&k)==1)
	{
		if(k<1||k>5)//here we have to consider the two scanf for k values
			{
				printf("\n\nPlease type the right option\n\n");
				printf("\n\t\t1.UPPER(U)\t2.MIDDLE(M)\t3.LOWER(L)");
				continue;
			}
		break;
	}
	person=modify_person(person,k,coach_type,curr);//modifies the person 
	for(i=0;i<no_tickets-1;i++)//now tries to modifies his family if present
	{
		printf("\n\n--*TICKET*--%d\n",i+2);
		printf("\n\t\t1.UPPER(U)\t2.MIDDLE(M)\t3.LOWER(L)\t4.SIDE LOWER(SL)\t5.SIDE UPPER(SU)(Q to quit);");
		while(scanf("%d",&k)==1){
			if(k<1||k>5)//here we have to consider the two scanf for k values
			{
				printf("\n\nPlease type the right option\n\n");
				printf("\n\t\t1.UPPER(U)\t2.MIDDLE(M)\t3.LOWER(L)t4.SIDE LOWER(SL)\t5.SIDE UPPER(SU)(Q to quit)");
				continue;
			}
			switch(k)
			{
				case 1:person=makenew(person,1,coach_type,curr);break;//these are the preferred seat types for family members
				case 2:person=makenew(person,2,coach_type,curr);break;//here the person structure should be the owner
				case 3:person=makenew(person,3,coach_type,curr);break;
				case 4:person=makenew(person,4,coach_type,curr);break;
				case 5:person=makenew(person,5,coach_type,curr);break;
				default:printf("\nright option was not chosen Please choose again\n");continue;
			}
			break;
		}
	}
	printf("\n\n\t\t\t(0)----Proceeding for payment----(0)\n\t\tBHIM>>\n\t\tUPI>>");
	clock_t start=clock();
			while(clock()<start+2000);
	payment(person);
	person->cost=no_tickets*fare[coach_type-1];
	ticket_display(person);
	return first;
}
//-------------------------------------------------------------------------------------------------------
void payment(USER_NODE curr)
{
	while(1){
	printf("\n\n\t\tPlease type the otp received on your mobile number:(wait 5 seconds)\t");
	int k=(rand()%9999)+1000;//rand() function with ranges to generate random otp
	clock_t start=clock();
			while(clock()<start+5000);//will receive otp in five seconds
	printf("\t\t\t\t\t\t|OTP--%d|\n",k);
	int y;scanf("%d",&y);
	if(y==k)
		break;
	printf("\nType again");
	continue;
	}
}
//-------------------------------------------------------------------------------------------------------
USER_NODE relocator(USER_NODE curr)
{
	USER_NODE first=curr;
	while(first->prev!=NULL)
		first=first->prev;
	return first;
}
//--------------------------------------------------------------------------------------------------------
void ticket_display(USER_NODE person)
{
	printf("\nPrinting your ticket\n");
	clock_t start=clock();
			while(clock()<start+1000);
	int i;
	printf("\t\t\t");
	for(i=0;i<100;i++)
		putchar('-');
	printf("\n\t\t\t|");
	for(i=0;i<99;i++)
		printf(" ");putchar('|');
	printf("\n\t\t\t|");
	for(i=0;i<43;i++)
		printf(" ");printf("HAPPY JOURNEY");
	for(i=0;i<43;i++)
		printf(" ");putchar('|');
	printf("\n\t\t\t");
	for(i=0;i<100;i++)
		putchar('-');
	printf("\n\t\t\t|");
		for(i=0;i<42;i++)
		printf(" ");printf("INDIAN RAILWAYS");
	for(i=0;i<42;i++)
		printf(" ");putchar('|');
	printf("\n\t\t\t|");
	for(i=0;i<34;i++)
		printf(" ");printf("Train name          Train number");
	 start=clock();
			while(clock()<start+1000);
	for(i=0;i<33;i++)
		printf(" ");putchar('|');
	printf("\n\t\t\t|");
	for(i=0;i<34;i++)
		printf(" ");
	printf("%s            %d",person->train_name,person->train_no);
	for(i=0;i<42;i++)
		printf(" ");putchar('|');
	printf("\n\t\t\t|");
	for(i=0;i<11;i++)
		printf(" ");printf("USERNAME         SEAT           COST           COACH      STATUS       TYPE   ");
	for(i=0;i<10;i++)
		printf(" ");putchar('|');
	printf("\n\t\t\t|");
	for(i=0;i<11;i++)
		printf(" ");
	printf("%s         %d           %.3f           ",person->user_name,person->seat_no,person->cost);
	switch(person->coach_type)
	{
		case 1:printf("GN      ");break;
		case 2:printf("SL      ");break;
		case 3:printf("1A      ");break;
		case 4:printf("2A      ");break;
		case 5:printf("3A      ");break;
		default:break;
	}
	(person->seat_status)==false?printf("WL       "):printf("CNF          ");
	switch(person->seat_type)
		{
			case 1:printf("U");break;
			case 2:printf("M ");break;
			case 3:printf("L ");break;
			case 4:printf("SL ");break;
			case 5:printf("SU ");break;
			default:break;
		}
	for(i=0;i<10;i++)
		printf(" ");putchar('|');
	printf("\n\t\t\t");
		for(i=0;i<100;i++)
		putchar('-');
	printf("\n\t\t\t|");
	for(i=0;i<34;i++)
		printf(" ");printf("AN INITIATIVE OF INDIAN RAILWAYS");
	for(i=0;i<34;i++)
		printf(" ");putchar('|');
	printf("\n\t\t\t");
	for(i=0;i<100;i++)
		putchar('-');
	start=clock();
			while(clock()<start+1000);
	return;
}
//-----------------------------------------------------------------------------------------------
USER_NODE makenew(USER_NODE person,int seat_type,int coach,TRAIN_NODE currt)
{
	USER_NODE curr=person;
	while(curr->next!=NULL)curr=curr->next;//goes to the end of linked list person
	USER_NODE new=(USER_NODE)malloc(sizeof(struct person));//allocates space
	printf("\n\n\t\tPlease type the name:\t");
	scanf("%s",new->user_name);
	strcpy(new->train_name,person->train_name);
	new->train_no=person->train_no;
	new->prev=curr;
	new->next=NULL;
	int lower[20];
	int middle[20];
	int upper[20];
	int side_lower[10];
	int side_upper[10];
	int i,k=1,j=4;
	for(i=0;i<9;i++)
	{
		lower[i]=k;
		lower[i+1]=j;
		k=k+8;
		j=j+8;
	}
	k=2,j=5;
	for(i=0;i<9;i++)
	{
		middle[i]=k;
		lower[i+1]=j;
		k=k+8;
		j=j+8;
	}
	k=3,j=6;
	for(i=0;i<9;i++)
	{
		upper[i]=k;
		upper[i+1]=j;
		k=k+8;
		j=j+8;
	}
	k=7,j=8;
	for(i=0;i<10;i++)
	{
		side_lower[i]=k;
		side_upper[i]=j;
		k=k+8;j=j+8;
	}
	i=0;
	switch(seat_type)
	{
		case 1:while(i<10&&(currt->vacancy[coach][lower[i]])!=true)i++;break;
		case 2:while(i<10&&(currt->vacancy[coach][middle[i]])!=true)i++;break;
		case 3:while(i<10&&(currt->vacancy[coach][upper[i]])!=true)i++;break;
		case 4:while(i<10&&(currt->vacancy[coach][side_lower[i]])!=true)i++;break;
		case 5:while(i<10&&(currt->vacancy[coach][side_upper[i]])!=true)i++;break;
	}
	if(i>=10)
	{
		printf("\n\n\t\t******Your ticket will be kept on waiting list*******\n");
		person->seat_status=false;
		currt->waiting_list[coach-1]++;
		return person;
	}
	switch(seat_type)
	{
		case 1:currt->vacancy[coach][lower[i]]=false;break;
		case 2:currt->vacancy[coach][middle[i]]=false;break;
		case 3:currt->vacancy[coach][upper[i]]=false;break;
		case 4:currt->vacancy[coach][side_lower[i]]=false;break;
		case 5:currt->vacancy[coach][side_upper[i]]=false;break;
	}
	switch(seat_type)
	{
		case 1:new->seat_no=lower[i];
		case 2:new->seat_no=middle[i];
		case 3:new->seat_no=upper[i];
		case 4:new->seat_no=side_lower[i];
		case 5:new->seat_no=side_upper[i];
	}
	new->coach_type=coach;
	new->seat_type=seat_type;
	new->cost=0;//the cost for this user is zero because this is not the main user this is just the family member
	ticket_display(new);//displays the users ticket
	return person;//returns the person structure of the main member who will make the payment
}
//-------------------------------------------------------------------------------------------------------
USER_NODE modify_person(USER_NODE person,int seat_type,int coach,TRAIN_NODE currt)
{
	int lower[20];//these are all the seat numbers of lower type
	int middle[20];//these are all the seat numbers of middle type
	int upper[20];//these are all the seat numbers of upper type
	int side_lower[10];//these are all the seat numbers of Sl type
	int side_upper[10];//these are all the seat numbers of SU type
	int i,k=1,j=4;
	for(i=0;i<9;i++)
	{
		lower[i]=k;//assigning the seat numbers,for lower it will be 1,4,9,13.....
		lower[i+1]=j;
		k=k+8;
		j=j+8;
	}
	k=2,j=5;
	for(i=0;i<9;i++)
	{
		middle[i]=k;//assigning the seat numbers,for middle it will be 2,5,10,13.....
		lower[i+1]=j;
		k=k+8;
		j=j+8;
	}
	k=3,j=6;
	for(i=0;i<9;i++)
	{
		upper[i]=k;//assigning the seat numbers,for upper it will be 3,6,11,14.....
		upper[i+1]=j;
		k=k+8;
		j=j+8;
	}
	k=7,j=8;
	for(i=0;i<9;i++)
	{
		side_lower[i]=k;//assigning the seat numbers,for side lower it will be 7,15,22.....
		side_upper[i]=j;//assigning the seat numbers,for side upper it will be 8,16,24.....
		k=k+8;j=j+8;
	}
	i=0;
	switch(seat_type)
	{//see which seat number is vacant in the train according to the seat_type
		case 1:while(i<10&&(currt->vacancy[coach][lower[i]])!=true)i++;break;
		case 2:while(i<10&&(currt->vacancy[coach][middle[i]])!=true)i++;break;
		case 3:while(i<10&&(currt->vacancy[coach][upper[i]])!=true)i++;break;
		case 4:while(i<10&&(currt->vacancy[coach][side_lower[i]])!=true)i++;break;
		case 5:while(i<10&&(currt->vacancy[coach][side_upper[i]])!=true)i++;break;
	}
	if(i>=10)
	{//if all the seats of the perffered seat type is full,give the user waiting list seat
		printf("\n\n\t\t******Your ticket will be kept on waiting list*******\n");
		person->seat_status=false;//in person structure set that the user was not allocated seat
		currt->waiting_list[coach-1]++;//increment the waiting list of the coach
		return person;
	}
	person->seat_status=true;//user has got a seat
	switch(seat_type)
	{
		case 1:currt->vacancy[coach][lower[i]]=false;break;//set the current opted seat in train to not vancant
		case 2:currt->vacancy[coach][middle[i]]=false;break;
		case 3:currt->vacancy[coach][upper[i]]=false;break;
		case 4:currt->vacancy[coach][side_lower[i]]=false;break;
		case 5:currt->vacancy[coach][side_upper[i]]=false;break;
	}
	switch(seat_type)
	{
		case 1:person->seat_no=lower[i];//give person his seat number
		case 2:person->seat_no=middle[i];
		case 3:person->seat_no=upper[i];
		case 4:person->seat_no=side_lower[i];
		case 5:person->seat_no=side_upper[i];
	}
	person->coach_type=coach;//give person his coach type 
	person->seat_type=seat_type;//give person his seat type
return person;//return the current person structure
}
//------------------------------------------------------------------------------------------------------
void starting_display(void)
{
	printf("\n\n\n\n\n\n\t\t\t\t\t");
	int i=0;
	while(i++<70)
		putchar('-');
	printf("\n\t\t\t\t\t|");
	i=0;while(i++<68)printf(" ");
	putchar('|');
	printf("\n\t\t\t\t\t|");
	printf("\tWELCOME TO IRCTC RAILWAY RESERVATION SYSTEM SIMULATION");
	clock_t start1=clock();
			while(clock()<start1+2000);//this is a clock() function which halts program for 1000ms
	i=0;
	while(i++<6)printf(" ");printf(" |");
	printf("\n\t\t\t\t\t|");
	i=0;while(i++<68)printf(" ");
	printf("|");
	printf("\n\t\t\t\t\t|\t\t----------MADE BY-----------");
	i=0;while(i++<25)printf(" ");printf("|");
	const char* array[]={
		"MUSTHAFFA","SOHAN","RAJA SAGAR","SATYAM","RUMAN","SUDHANSHU","HARSH","SHASHANK"
	};
	i=0;
	while(i<8)
	{
			clock_t start=clock();
			while(clock()<start+700);
				printf("\n\t\t\t\t\t|");
				printf("\t\t\t%s",array[i]);
				int a=0;while(a++<(45-strlen(array[i])))printf(" ");putchar('|');
			i++;
	}
	printf("\n\t\t\t\t\t");
	 i=0;
	while(i++<70)
		putchar('-');
	printf("\n\n\t\t\t\tPlease type the project password(Q to Quit):\t");
	int k;
	while(scanf("%d",&k)==1)
	{
		if(k==786)
			break;
		printf("\n\t\t\t\tWrong password!! Type again:\t");
	}
	system("cls");//clears the display screen
}
//----------------------------------------------------------------------------------------------
USER_NODE cancel_ticket(TRAIN_NODE first,USER_NODE person)
{
	if(person==NULL)
	{
		printf("\n\tNo Ticket was created\n");
		return NULL;
	}
	printf("\n\nPlease type the date of travel(dd/mm/yyyy):\t");
	char date[10];
	scanf("%s",date);
	TRAIN_NODE currt=first;
	while(currt!=NULL&&strcmp(currt->date,date)!=0)
		currt=currt->next;
	if(currt==NULL)
	{
		printf("\n\tA train with this date was not registered\n");
		return NULL;
	}
	if(person=NULL)
	{
		printf("\nThere is no current user of the train to delete the ticket\n");
		return NULL;
	}
	USER_NODE curr=person;
	printf("\nType the username of the person to delete the ticket");
	char username[20];
	scanf("%s",username);
	while(curr!=NULL&&strcmp(curr->user_name,username)!=0)
				curr=curr->next;
	if(curr==NULL)
	{
		printf("\n\tThe person with specified username was not found\n");
		return NULL;
	}
	if(curr->seat_status=false)
		currt->waiting_list[curr->coach_type-1]--;
	currt->vacancy[curr->coach_type-1][curr->seat_no]=true;
	USER_NODE new=curr->prev;
	new->next=curr->next;
	free(curr);
	printf("****Your Ticket was deleted****");
	return person;
}
