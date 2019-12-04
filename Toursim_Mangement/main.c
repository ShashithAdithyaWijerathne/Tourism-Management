//Developed by Hbs_Adithya

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum state{menu,loggedin};
enum state currentstate=menu;

typedef struct user
{
    char username[100];
    char password[100];
    char place[100];
    float price;
    int numtick;
    struct user *next;
}user;

void ShowLocations();
user* InitializeList(user*);
user* AddUser(user*);
void LoginUser(user*);
void BookTicket(user*);
void PrintTicket(user*);
void CancelTicket(user*);
void ChangePassword(user*);
void LogoutUser();
void CheckTicket(user*);
void DisplayAll(user*);
void WriteToFile(user*);
void ExitProgram();

char currentuser[100];

int main()
{
    printf("\t\t\t_________________________________________\n");
    printf("\t\t\t==== || TOURISM MANAGEMENT SYSTEM || ====\n");
    printf("\t\t\t_________________________________________\n");
    user *h=NULL;
    int ch1,ch2;
    h=InitializeList(h);
    while (1)
    {

        if(currentstate==menu)
        {

            printf("\n\t\t\t\tAdd User    -[1]\n\t\t\t\tLogin User  -[2]\n\t\t\t\tLocations   -[3]\n\t\t\t\tExit        -[4]\n\n\t\t\t\tEnter:");
            scanf("%d",&ch1);
            switch(ch1)
            {
                case 1:
                    h=AddUser(h);
                    break;
                case 2:
                    LoginUser(h);
                    break;
                case 3:
                    ShowLocations();
                    break;
                case 4:
                    ExitProgram();


                    exit(0);
                    break;
                default:
                    printf("Not a valid input at this stage\n");
            }
        }
        else if(currentstate==loggedin)
        {
        system("CLS");
        printf("\n\t\t\t\t_____________________________");
		printf("\n\t\t\t\t||TOURISM MANAGEMENT SYSTEM||");
		printf("\n\t\t\t\t_____________________________\n");
            printf("\n\t\t\t\tBook Package    - [1]\n\t\t\t\tCheck Ticket    - [2]\n\t\t\t\tPrint Ticket    - [3]\n\t\t\t\tCancel Ticket   - [4]\n\t\t\t\tChange Password - [5]"
                   "\n\t\t\t\tLogout User     - [6]\n\t\t\t\tLocations       - [7]\n\t\t\t\tExit            - [8]\n");
            scanf("%d",&ch2);
            switch(ch2)
            {
                case 1:
                    BookTicket(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 2:
                    CheckTicket(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 3:
                    PrintTicket(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 4:
                    CancelTicket(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 5:
                    ChangePassword(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 6:
                    LogoutUser(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 7:
                    ShowLocations();
                    system("PAUSE");
                    system("CLS");
                    break;
                case 8:
                    ExitProgram();
                    exit(0);
                    break;
                default:
                    printf("Not a valid input at this stage\n");
            }
        }
    }
    return 0;
}

user* InitializeList(user *h)
{
    user* t,*ptr,temp;
    FILE *fp;
    int cc=0,x;
    float ff;
    fp=fopen("users.txt","r");

    if(fp==NULL)
        return NULL;

    if(fgetc(fp)==EOF)
        return NULL;

    rewind(fp);
	while(fscanf(fp,"%s %s %s %f %d",temp.username,temp.password,temp.place,&temp.price,&temp.numtick)!=EOF)
	{
		ptr=(user*)malloc(sizeof(user));
		strcpy(ptr->username,temp.username);
		strcpy(ptr->password,temp.password);
		strcpy(ptr->place,temp.place);
		ptr->price=temp.price;
		ptr->numtick=temp.numtick;
		ptr->next=NULL;

		if(h==NULL)
            h=t=ptr;
		else
		{
			h->next=ptr;
			h=ptr;
		}
	}
	fclose(fp);
    return t;
}

void WriteToFile(user *h)
{
    FILE *fp;
    fp=fopen("users.txt","w");//Create a user file
    while(h!=NULL)
    {
        fprintf(fp,"%s %s %s %f %d\n",h->username,h->password,h->place,h->price,h->numtick);
        h=h->next;
    }
    fclose(fp);
}
//Show the Locations
void ShowLocations()
{
	system("CLS");
    printf("__________________________________\n\tPRICE LIST\n__________________________________\n01. [A] - Anuradhapura - Rs 2000/= \n02. [B] - Badulla      - Rs 6000/= \n03. [G] - Galle        - Rs 2500/=\n04. [K] - Kithulgala   - Rs 3800/=\n"
           "05. [E] - Ella         - Rs 2000/=\n06. [D] - Dabulla      - Rs 1000/=\n07. [J] - Jaffna       - Rs 3000/=\n08. [N] - NuwaraEliya  - Rs 2000/=\n09. [R] - Ritigala     - Rs 4500/=\n10. [H] - Haputhale    - Rs 2500/=\n__________________________________\n\n");
}
//Check the Ticket
void CheckTicket(user *h)
{
    while(h!=NULL)
    {
        if(!strcmp(h->username,currentuser))
            break;
        h=h->next;
    }
    if(!strcmp(h->place,"\0") || h->price==0.0 || h->numtick==0)
    {
        printf("You do not have a ticket booked yet\n");
        return;
    }
    float total=0.0;
    total=(h->price)*(h->numtick);
    printf("You have booked %d tickets for a sum total of Rs %f for tour code %s\n",h->numtick,total,h->place);
}
//Create a new account
user* AddUser(user* h)
{
    user *t;
    t=h;
    user *nw;
    nw=(user*)malloc(sizeof(user));
    fflush(stdin);
    printf("Enter username or email\n");//Add email
    scanf("%s",nw->username);
    while(h!=NULL)
    {
        if(!strcmp(h->username,nw->username))//Check the email already use or not
        {
            printf("That email already exists\n");
            return t;
        }
        h=h->next;
    }
    h=t;
    fflush(stdin);
    printf("Enter password\n");//Add password
    scanf(" %[^\n]s",&nw->password);
    nw->next=NULL;
    strcpy(nw->place,"N/A");
    nw->price=0.0;
    nw->numtick=0;

    if(h==NULL)
    {
        h=t=nw;
    }
    else
    {
        while(h->next!=NULL)
        {
            h=h->next;
        }
        h->next=nw;
    }
    WriteToFile(t);
    return t;
}
//Log in to the system (Developed by Hbs_ Adithya)
void LoginUser(user* h)
{
    char username[100];
    char password[100];
    fflush(stdin);
    printf("\n\n");
    printf("\t\tEnter Email/Username:\n\t\t");
    scanf("%s",username);
    fflush(stdin);
    printf("\n\t\tEnter Password:\n\t\t");
    scanf(" %[^\n]s",password);
    while(h!=NULL)//Check whether email and password correct or not
    {
        if((!strcmp(h->username,username)) && (!strcmp(h->password,password)))
        {
            currentstate=loggedin;
            strcpy(currentuser,username);

            printf("\n\t\tLogin successful!\n");
            system("PAUSE");
            return;
        }
        else if((!strcmp(h->username,username)) && (strcmp(h->password,password)))
        {
            printf("Password mismatch\n");
            return;
        }
        h=h->next;
    }
    printf("Sorry, no such user record was found\n");
}
//Booking the Ticket(Developed by Hbs_Adithya)
void BookTicket(user *h)
{
    user *t=h;
    char place[100];
    while(h!=NULL)
    {
        if(!strcmp(h->username,currentuser))
            break;
        h=h->next;
    }
    if(h==NULL)
        return;
    if(h->price!=0.0)
    {
        printf("You must cancel your previous ticket before buying a new one\n");
        return;
    }
    ShowLocations();
    float pricelist[]={2000.0,6000.0,2500.0,3800.0,2000.0,1000.0,3000.0,2000.0,4500.0,2500.0};
    fflush(stdin);
    printf("\nEnter place code (eg: A,B)\n");
    scanf(" %[^\n]s",place);
    char choice;
    fflush(stdin);
    printf("\nWould You Like to Confirm Booking?\n[1] - Yes\n[2] - No\n");
    scanf("%c",&choice);
    float price;
    if(choice!='1')
        return;
    if(strcmp(place,"A")==0)
        price=pricelist[0];
    else if(strcmp(place,"B")==0)
        price=pricelist[1];
    else if(strcmp(place,"G")==0)
        price=pricelist[2];
    else if(strcmp(place,"K")==0)
        price=pricelist[3];
    else if(strcmp(place,"E")==0)
        price=pricelist[4];
    else if(strcmp(place,"D")==0)
        price=pricelist[5];
    else if(strcmp(place,"J")==0)
        price=pricelist[6];
    else if(strcmp(place,"N")==0)
        price=pricelist[7];
    else if(strcmp(place,"R")==0)
        price=pricelist[8];
    else if(strcmp(place,"H")==0)
        price=pricelist[9];
    else
    {
        printf("That tour code doesn't exist\n");
        return;
    }
    printf("Enter the number of tickets you want to book?\n");
    scanf("%d",&h->numtick);
    if(h->numtick==0)
        return;
    strcpy(h->place,place);
    h->price=price;
    WriteToFile(t);
    printf("Bookings Done!!\n");
    system("PAUSE");

}
//Print the Tickets(Developed by Hbs_Adithya)
void PrintTicket(user *h)
{
    while(h!=NULL)
    {
        if(!strcmp(h->username,currentuser))
            break;
        h=h->next;
    }
    if(!strcmp(h->place,"\0") || h->price==0.0 || h->numtick==0)
    {
        printf("You do not have a ticket booked yet\n");
        return;
    }
    float total=0.0;
    total=(h->price)*(h->numtick);
    FILE *fp;
    char filename[50];
    strcpy(filename,h->username);
    strcat(filename,"_ticket.txt");//Create a document
    fp=fopen(filename,"w");
    if(fp==NULL)
    {
        printf("Problem opening the file\n");
        return;
    }
    if(fgetc(fp)==EOF)
    {
        fprintf(fp,"||TOURISM TICKET||\n________________________\n\n");
    }
    fprintf(fp,"Email ID: %s\nTour Code: %s\nTicket Cost: Rs %f\nNumber of tickets: %d\nTotal Cost: Rs %f\n",h->username,h->place,h->price,h->numtick,total);
    fclose(fp);
}
//Cancel the ticket (Developed by Hbs_Adithya)
void CancelTicket(user *h)
{
    user *t=h;
    while(h!=NULL)
    {
        if(!strcmp(h->username,currentuser))
            break;
        h=h->next;
    }

    int flag=-1;

    if(h==NULL)
        printf("No such user\n");

    if(strcmp(h->place,"A")==0)
        flag++;
    else if(strcmp(h->place,"B")==0)
        flag++;
    else if(strcmp(h->place,"G")==0)
        flag++;
    else if(strcmp(h->place,"K")==0)
        flag++;
    else if(strcmp(h->place,"E")==0)
        flag++;
    else if(strcmp(h->place,"D")==0)
        flag++;
    else if(strcmp(h->place,"J")==0)
        flag++;
    else if(strcmp(h->place,"N")==0)
        flag++;
    else if(strcmp(h->place,"R")==0)
        flag++;
    else if(strcmp(h->place,"H")==0)
        flag++;
    else
    {
        printf("You haven't booked a tour yet\n");
        return;
    }
    if(flag==0)
    {
        printf("Your ticket has been successfully cancelled\nA refund of Rs %f for Tour Code %s for %d tickets will soon be made to your original source of purchase\n",h->price,h->place,h->numtick);
        strcpy(h->place,"N/A");
        h->price=0.0;
        h->numtick=0;
        WriteToFile(t);
    }
}
//Change password (Developed by Hbs_Adithya)
void ChangePassword(user *h)
{
    user *t=h;
    char passcurr[100];
    fflush(stdin);
    printf("Enter your current password to continue:\n");
    scanf(" %[^\n]s",passcurr);
    while(h!=NULL)
    {
        if(!strcmp(h->username,currentuser))
            break;
        h=h->next;
    }
    if(h==NULL)
        return;
    if(!strcmp(passcurr,h->password))
    {
        printf("Enter new password:\n");
        scanf(" %[^\n]s",h->password);
    }
    WriteToFile(t);
}
//Logout in the System(Developed by Hbs_Adithya)
void LogoutUser()
{
    if(currentstate==menu || strcmp(currentuser,"\0")==0)
    {
        printf("You must be logged in to logout\n");
        return;
    }
    strcpy(currentuser,"\0");
    currentstate=menu;
    printf("You have been successfully logged out\n");
}

void ExitProgram()
{
    printf("Exiting...\nDeveloped By Hbs_Adithya,SLIIT\n\nPress \"Enter/Return\" to exit");
    char exitprog;
    fflush(stdin);
    scanf("%c",&exitprog);
}
