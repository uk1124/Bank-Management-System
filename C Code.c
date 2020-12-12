#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Admin
{
char name[100];
char userid[100];
char password[100];
struct Admin *Next;
};
struct CrdtCard {
 int act;
 long int ccNum;
 int ccScore;
 int ccLimit;
 int intrstRate;
 int creditUsed;
 int availBalance;
 int flag;
};
struct Customers
{
char userid[100];
char password[100];
char name[100];
char aadhaar[12];
char pan[10];
struct Accounts* Achead;
struct Customers *Next;
int kyc;
struct CrdtCard Crdt;
};
struct Accounts
{
 int accno;
 int balance;
 struct Transactions* top;
 struct Accounts *Next;
};
struct date
{
 int dd,mm,yyyy;
};
struct Transactions
{
 struct date d;
 int amount;
 int balance;
 char type[100];
 struct Transactions *Next;
};
typedef struct Admin AdminNode;
typedef struct Customers CustomerNode;
typedef struct Accounts AcNode;
typedef struct Transactions Tnode;
AdminNode *Ahead=NULL;
CustomerNode *Uhead=NULL;
void creditCard(CustomerNode *cptr)
{
 int h;
 if(cptr->Crdt.act!=78780730923&&cptr->Crdt.flag!=1)
 {
 printf("\n \n YOU DON'T HAVE A CREDIT CARD! WOULD YOU LIKE
TO HAVE ONE?\n\n");
 printf("\n 1. Yes");
 printf("\n 2. No \n");
 scanf("%d",&h);
 getchar();
 switch(h){
 case 1:
 {
 printf("\nCongratulations!\n Credit Card will be delivered in next
7 Working Days ");
 cptr->Crdt.availBalance=150000;
 printf("\nAvailable balance is: %d \n",cptr->Crdt.availBalance);
 cptr->Crdt.ccNum=78780730923;
 printf("\n Your Credit Card number is: %d \n",cptr-
>Crdt.ccNum);
 cptr->Crdt.intrstRate=8;
 printf("\n The intrest rate is: %d \% \n",cptr->Crdt.intrstRate);
 printf("\n PRESS ENTER TO RETURN TO MAIN MENU \n");
 cptr->Crdt.flag=1;
 getchar();
 MainMenu_Customer(cptr);
 }
 case 2:
 {
 MainMenu_Customer(cptr);
 }
 }
 }
 else {
 printf("\n 1. View Credit Card Status\n");
 printf("\n 2. Pay Using Card \n");
 int j;
 scanf("%d",&j);
 switch(j){
 case 1:
 {
 cptr->Crdt.creditUsed=0;
 printf("\nAvailable balance is: %d \n",cptr->Crdt.availBalance);
 printf("\n Your Credit Card number is: %d \n",cptr-
>Crdt.ccNum);
 printf("\n The intrest rate is: %d \% \n",cptr->Crdt.intrstRate);
 getchar();
 printf("\n PRESS ENTER TO RETURN TO MAIN MENU \n");
 getchar();
 MainMenu_Customer(cptr);
 break;
 }
 case 2:
 {
 int payingAmnt;
 printf("Enter the amount you want to pay: ");
 scanf("%d",&payingAmnt);
 printf("Payment of %d Successful!",payingAmnt);
 cptr->Crdt.creditUsed=cptr->Crdt.creditUsed+payingAmnt;
 cptr->Crdt.availBalance-=payingAmnt;
 printf("Your available balance is: %d",cptr->Crdt.availBalance);
 getchar();
 printf("\n PRESS ENTER TO RETURN TO MAIN MENU \n");
 getchar();
 MainMenu_Customer(cptr);
 break;
 }
 }
 }
}
void start()
{
 Welcome();
 Login();
}
void Header()
{
 system("cls||clear");
 for(int i=0;i<56;i++)
 printf("*");
 printf("\n* BANK MANAGEMENT SYSTEM *\n");
 for(int i=0;i<56;i++)
 printf("*");
 return;
}
void Welcome()
{
 system("cls||clear");
 printf("\n\n\n\n\n\n\n\n\n\n");
 printf(" ");
 printf("WELCOME!");
 printf("\n\n ");
 printf("Press Enter to Continue...");
 getchar();
 return;
}
AdminNode* CreateAdminNode()
{
 Header();
 AdminNode *n=(AdminNode*)malloc(sizeof(AdminNode));
 printf("\n Enter new Admin Name: ");
 scanf("%s",&n->name);
 printf("\n Enter new Admin UserID: ");
 scanf("%s",&n->userid);
 printf("\n Enter Password: ");
 scanf("%s",&n->password);
 n->Next=NULL;
 return n;
}
void CreateAdminUser()
{
 system("cls||clear");
 Header();
 if(Ahead==NULL)
 Ahead=CreateAdminNode();
 else
 {
 AdminNode *p=Ahead;
 while(p->Next!=NULL)
 {
 p=p->Next;
 }
 p->Next=CreateAdminNode();
 }
 Login();
 return;
}
Tnode* CreateTnode(Tnode* T,AcNode* A)
{
 Header();
 Tnode *n=(Tnode*)malloc(sizeof(Tnode));
 printf("\n Enter Date: ");
 scanf("%d%d%d",&n->d.dd,&n->d.mm,&n->d.yyyy);
 printf("\n Enter Amount: ");
 scanf("%s",&n->amount);
 printf("\n Enter Type: ");
 scanf("%s",&n->type);
 if(T==NULL)
 {
 n->Next=NULL;
 n->balance=n->amount;
 }
 else
 {
 n->Next=T;
 T->Next=NULL;
 n->balance=n->Next->balance+n->amount;
 }
 A=n->balance;
 return n;
}
Tnode* CreateTransaction(struct date d,long int a,Tnode *T,AcNode *A)
{
 Tnode *t=(Tnode*)malloc(sizeof(Tnode));
 t->d.dd=d.dd;
 t->d.mm=d.mm;
 t->d.yyyy=d.yyyy;
 t->amount=a;
 t->balance=A->balance+a;
 if(a<0)
 strcpy(t->type,"Withdrawal");
 else
 strcpy(t->type,"Deposit");
 if(T==NULL)
 {
 t->Next=NULL;
 T=t;
 }
 else
 {
 t->Next=T;
 T->Next=NULL;
 }
 A->balance+=a;
 return t;
}
Tnode* DisplayTrasnsactions(Tnode *T)
{
 Tnode *p=T;
 Header();
 printf("\nYour Tansactions Are: ");
 printf("\n S.no Date Amount Balance Tyoe");
 int i=1;
 while(p!=NULL)
 {
 printf("\n %d %d/%d/%d %d %d %s",i++,p->d.dd,p-
>d.mm,p->d.yyyy,p->amount,p->balance,p->type);
 p=p->Next;
 }
 getchar();
}
AcNode* CreateAcNode()
{
 Header();
 AcNode *n=(AcNode*)malloc(sizeof(AcNode));
 n->accno=2000000000+rand()%10000;
 printf("\n\nEnter the Amount you wish to Open Account with: ");
 scanf("%d",&n->balance);
 printf("\n\nCONGRATULATIONS ACCOUNT SUCCESSFULLY
OPENED!");
 printf("\n Your Account Number is: %d",n->accno);
 n->top=NULL;
 n->Next=NULL;
 getchar();
 return n;
}
void DisplayAccounts(AcNode *p)
{
 AcNode *q=p;
 Header();
 printf("\n\n S.no. Account No.");
 int i=1;
 while(q!=NULL)
 {
 printf("\n %d %d",i++,q->accno);
 q=q->Next;
 }
 getchar();
 return;
}
CustomerNode* CreateCustomerNode()
{
 Header();
 CustomerNode *n=(CustomerNode*)malloc(sizeof(CustomerNode));
 printf("\n Enter new Customer Name: ");
 scanf("%s",&n->name);
 printf("\n Enter new Customer UserID: ");
 scanf("%s",&n->userid);
 printf("\n Enter Password: ");
 scanf("%s",&n->password);
 n->Next=NULL;
 n->kyc=0;
 n->Achead=NULL;
 return n;
}
void CreateCustomerUser()
{
 Header();
 if(Uhead==NULL)
 {
 Uhead=CreateCustomerNode();
 }
 else
 {
 CustomerNode *p=Uhead;
 while(p!=NULL)
 {
 p=p->Next;
 }
 p=CreateCustomerNode();
 }
 return;
}
void Login()
{
 Header();
 if(Ahead==NULL)
 {
 printf("\n This is your first Login.\n\n");
 printf(" Please create Admin User \n\n");
 printf(" Press Enter to Continue...");
 getchar();
 CreateAdminUser();
 }
 else
 {
 int ch=0;
 printf("\n Choose an Option:");
 printf("\n 1. Customer Login");
 printf("\n 2. Admin Login\n");
 scanf("%d",&ch);
 getchar();
 switch(ch)
 {
 case 1:
 {
 if(Uhead==NULL)
 {
 printf("\n\nNo Costumer Accounts found!!");
 printf("\n Please sign up first");
 getchar();
 Login();
 break;
 }
 CustomerLogin();
 break;
 }
 case 2:
 {
 AdminLogin();
 break;
 }
 default:
 {
 printf("\n\nInvalid choice!!!");
 getchar();
 Login();
 }
 }
 }
}
void AdminLogin()
{
 Header();
 AdminNode *p=Ahead;
 char userid[100],password[100];
 printf("\n Enter Admin User id: ");
 scanf("%s",userid);
 printf("\n Enter Password: ");
 scanf("%s",password);
 do
 {
 if(strcmpi(p->userid,userid)==0&&strcmp(password,p->password)==0)
 {
 MainMenu_Admin();
 }
 else
 p=p->Next;
 }while(p!=NULL);
 printf("\n\nInvalid Userid/Password!!");
 printf("\n\n Please try Again");
 getchar();
 Login();
 return;
}
void CustomerLogin()
{
 Header();
 CustomerNode *p=Uhead;
 char userid[100],password[100];
 printf("\n Enter Customer User id: ");
 scanf("%s",userid);
 printf("\n Enter Password: ");
 scanf("%s",password);
 do
 {
 if(strcmpi(p->userid,userid)==0&&strcmp(password,p->password)==0)
 MainMenu_Customer(p);
 else
 p=p->Next;
 }while(p!=NULL);
 getchar();
 printf("\n\nInvalid Userid/Password!!");
 printf("\n\n Please try Again");
 printf("\n\nPress Enter to Continue...");
 getchar();
 return;
}
void SelectAccount(CustomerNode *ptr)
{
 int ch=0;
 DisplayAccounts(ptr->Achead);
 printf("\n\n Please select your account: ");
 scanf("%d",&ch);
 AcNode* p=ptr->Achead;
 int i=1;
 while(i!=ch)
 {
 p=p->Next;
 i++;
 }
 AccountMenu(p);
 return;
}
void AccountMenu(AcNode *ptr)
{
 int op=0;
 do
 {
 Header();
 printf("\n\n Welcome to Accounts Page!");
 printf("\nViewing Details for Account: %d",ptr->accno);
 printf("\n Balance: %d",ptr->balance);
 printf("\n\n Please Choose an Option: ");
 printf("\n 1. DEPOSIT ");
 printf("\n 2. WITHDRAW ");
 printf("\n 3. CREATE NEW TRANSACTION ");
 printf("\n 4. VIEW ALL TRANSACTIONS ");
 printf("\n 5. GO BACK");
 printf("\n\n Your Choice: ");
 scanf("%d",&op);
 getchar();
 switch(op)
 {
 case 1:
 {
 int amount;
 struct date d;
 printf("\nEnter date as dd mm yyyy: ");
 scanf("%d%d%d",&d.dd,&d.mm,&d.yyyy);
 printf("\n Enter Deposit Amount: ");
 scanf("%d",&amount);
 ptr->top=CreateTransaction(d,amount,ptr->top,ptr);
 break;
 }
 case 2:
 {
 int amount;
 struct date d;
 printf("\nEnter date as dd mm yyyy: ");
 scanf("%d%d%d",&d.dd,&d.mm,&d.yyyy);
 printf("\n Enter Withdrawal Amount: ");
 scanf("%d",&amount);
 ptr->top=CreateTransaction(d,-amount,ptr->top,ptr);
 break;
 }
 case 3:
 {
 CreateTnode(ptr->top,ptr);
 break;
 }
 case 4:
 {
 DisplayTrasnsactions(ptr->top);
 break;
 }
 case 5:
 {
 return;
 }
 }
 }
 while(op!=5);
 getchar();
 return;
}
void MainMenu_Customer(CustomerNode *ptr)
{
 int op=0;
 do
 {
 Header();
 printf("\n\n Welcome %s to Customer Page!",ptr->name);
 printf("\n\n Please Choose an Option: ");
 printf("\n 1. OPEN NEW ACCOUNT ");
 printf("\n 2. CLOSE AN ACCOUNT ");
 printf("\n 3. VIEW ALL ACCOUNTS ");
 printf("\n 4. GO TO ACCOUNT ");
 printf("\n 5. CHANGE MY PASSWORD ");
 printf("\n 6. VIEW KYC INFO ");
 printf("\n 7. CHANGE KYC INFO ");
 printf("\n 8. CREDIT CARD INFO");
 printf("\n 9. SIGN OUT ");
 printf("\n 10. EXIT");
 printf("\n\n Your Choice: ");
 scanf("%d",&op);
 getchar();
 switch(op)
 {
 case 1:
 {
 AcNode *n=ptr->Achead;
 while(n!=NULL)
 {
 n=n->Next;
 }
 n=CreateAcNode();
 if(ptr->Achead==NULL)
 ptr->Achead=n;
 break;
}
 case 2:
 {
 CloseCustomerAccount();
 break;
 }
 case 3:
 {
 DisplayAccounts(ptr->Achead);
 break;
 }
 case 4:
 {
 SelectAccount(ptr);
 break;
 }
 case 5:
 {
 changeCustomerPassword(ptr);
 break;
 }
 case 6:
 {
 if(ptr->kyc==0)
 {
 printf("\n\n KYC INFO NOT PRESENT");
 break;
 }
 else
 {
 printf("\n\n AADHAAR: %s ",ptr->aadhaar);
 printf("\n\n PAN CARD: %s ",ptr->pan);
 break;
 }
 }
 case 7:
 {
 printf("Enter Aadhaar No. : ");
 scanf("%s",ptr->aadhaar);
 printf("Enter Pan No. : ");
 scanf("%s",ptr->pan);
 ptr->kyc=1;
 printf("\n\n KYC Updated Successfully.");
 printf("Press Enter to Continue...");
 break;
 }
 case 8:
 {
 creditCard(ptr);
 break;
 }
 case 9:
 {
 Login();
 op=9;
 break;
 }
 case 10:
 {
 exit(0);
 }
 default:
 {
 printf("\n\nInvalid Choice, Please try again");
 getchar();
 }
}
 }while(op!=9);
 getchar();
 return;
}
void MainMenu_Admin(AdminNode *ptr)
{
 int op=0;
 do
 {
 Header();
 printf("\n\n Welcome %s to Admin Page!",ptr->name);
 printf("\n\n Please Choose an Option: ");
 printf("\n 1. CREATE NEW CUSTOMER ACCOUNT ");
 printf("\n 3. CLOSE CUSTOMER ACCOUNT ");
 printf("\n 3. CHANGE CUSTOMER PASSWORD ");
 printf("\n 4. VIEW ALL ADMIN ACCOUNTS ");
 printf("\n 5. LIST ALL CUSTOMERS ");
 printf("\n 6. CHANGE ADMIN PASSWORD ");
 printf("\n 7. CHANGE MY PASSWORD ");
 printf("\n 9. SIGN OUT ");
 printf("\n 10. EXIT");
 printf("\n\n Your Choice: ");
 scanf("%d",&op);
 switch(op)
 {
 case 1:
 {
 CreateCustomerUser();
 break;
 }
 case 2:
 {
 RemoveCustomer();
 break;
 }
 case 3:
 {
 changeCustomerPasswordAdmin();
 break;
 }
 case 4:
 {
 listAdminAccounts();
 break;
 }
 case 5:
 {
 listCustomerAccount();
 break;
 }
 case 6:
 {
 changeAdminPassword();
 break;
 }
 case 7:
 {
 changeCurrentAdminPassword(ptr);
 break;
 }
 case 8:
 {
 CreateAdminUser();
 break;
 }
 case 9:
 {
 Login();
 op=10;
 break;
 }
 case 10:
 {
 exit(0);
 break;
 }
 default:
 {
 printf("\n\nInvalid Choice, Please try again");
 getchar();
 }
 }
 }while(op!=10);
 getchar();
 return;
}
void CloseCustomerAccount(CustomerNode *c)
{
 Header();
 long int accno;
 AcNode *a=c->Achead;
 printf("\n Please Enter Account Number you which to Remove: ");
 scanf("%d",&accno);
 if(accno==a->accno)
 {
 c->Achead=a->Next;
 }
 else
 {
 while(accno==a->Next->accno) {
 a=a->Next;
 }
 AcNode *clrp=a->Next;
 a->Next=a->Next->Next;
 free(clrp);
 }
 printf("\n\nPress ENTER to return to the Main Menu... ");
 getchar();
}
void changeCurrentAdminPassword(AdminNode *currentUserPointer)
{
 Header();
 AdminNode *p;
 p=Ahead;
 printf("\nEnter the new password: ");
 scanf("%s",currentUserPointer->password);
 printf("\n\nPASSWORD SUCCESSFULLY CHANGED!\n\n");
 printf("Press ENTER to return to main menu...");
 getchar();
 return;
}
void changeAdminPassword()
{
 Header();
 char uid[100];
 char newPassword[100];
 AdminNode *p;
 p=Ahead;
 printf("\n\n Enter the Admin UserID : ");
 scanf("%s",&uid);
 printf("\n Enter the new password: ");
 scanf("%s",&newPassword);
 while(strcmp(p->userid,uid)!=0) {
 p=p->Next;
 }
 strcpy(p->password,newPassword);
 printf("\n\nPASSWORD SUCCESSFULLY CHANGED!\n\n");
 printf("Press ENTER to return to main menu...");
 getchar();
 return;
}
void listCustomerAccount()
{
 Header();
 CustomerNode *p;
 p=Uhead;
 int cntr=1;
 if(p==NULL)
 printf("\n\n NO CUSTOMER ACCOUNTS FOUND\n\n");
 else
 printf("\n\n List of All Customer Accounts: ");
 while(p!=NULL)
 {
 printf("\nUser %d: \n",cntr++);
 printf("Name: %s \n",p->name);
 printf("UserID: %s \n",p->userid);
 p=p->Next;
 }
 getchar();
 printf("\n\n Press ENTER to return to main menu...");
 getchar();
}
void listAdminAccounts()
{
 Header();
 AdminNode *p;
 p=Ahead;
 int cntr=1;
 printf("\n List of all Admin Accounts. \n\n");
 while(p!=NULL) {
 printf("\nAdmin %d: \n",cntr);
 printf("Name: %s \n",p->name);
 printf("UserID: %s \n",p->userid);
 p=p->Next;
 }
 getchar();
 printf("\n\n Press ENTER to return to main menu...");
 getchar();
}
void changeCustomerPasswordAdmin()
{
 Header();
 char uid[100];
 char newPassword[100];
 CustomerNode *p;
 p=Uhead;
 printf("\n\nEnter the UserID of the Customer: ");
 scanf("%s",&uid);
 printf("\nEnter the new password: ");
 scanf("%s",&newPassword);
 while(strcmpi(p->userid,uid)!=0)
 {
 p=p->Next;
 }
 strcpy(p->password,newPassword);
 printf("\n\nPASSWORD SUCCESSFULLY CHANGED!\n\n");
 printf("Press ENTER to return to main menu...");
 getchar();
 return;
}
void changeCustomerPassword(CustomerNode *p)
{
 Header();
 char newPassword[100];
 printf("\nEnter the new password: ");
 scanf("%s",&newPassword);
 strcpy(p->password,newPassword);
 printf("\n\nPASSWORD SUCCESSFULLY CHANGED!\n\n");
 printf("Press ENTER to return to main menu...");
 getchar();
 return;
}
void RemoveCustomer()
{
 Header();
 char uid;
 CustomerNode *p,*clrp;
 p=Uhead;
 printf("\nEnter the UserID of the Customer: ");
 scanf("%s",uid);
 if(strcmp(p->userid,uid)==0)
 {
 Uhead=p->Next;
 }
 else
 {
 while(strcmp(p->Next->userid,uid)!=0)
 {
 p=p->Next;
 }
 clrp=p->Next;
 p->Next=p->Next->Next;
 free(clrp);
 }
 printf("\n\nPress ENTER to return to the Main Menu...");
 getchar();
}
int main()
{
start();
getchar();
return 0;
}
