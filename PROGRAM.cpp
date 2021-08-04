// GROUP MEMBERS
// RITIK = K180130
// TAHA MIR = K180147
// SABIR = K181158
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<sstream>
#include<cstdio>
using namespace std;

class administrator;
class user;
class province;
class punjab;
class sindh;
class balochistan;
class kpk;
class gilgit_baltistan;
class kashmir;
class city;
class town;
class house;

province *SINDH=NULL;
province *PUNJAB=NULL;
province *KPK=NULL;
province *GILGITBALTI=NULL;
province *BALOCH=NULL;
province *KASHMIR=NULL;

class province{
	public:
		char name[50];
		int no_of_cities;
		city *left_city, *middle_city, *right_city;
		
	province()
	{
		for(int i=0;i<50;i++)
		name[i]=0;
		no_of_cities=0;
	}	
	province(const char *n,int m)
	{
		for(int i=0;i<strlen(n);i++)
		name[i]=n[i];
		name[strlen(n)]='\0';
		no_of_cities=m;
	}
	void display(void)
	{
		cout<<"Province Name: "<<name<<endl;
		cout<<"No of cities: "<<no_of_cities<<endl<<endl;
	}
};
class gilgit_baltistan:public province
{
	public:
		kashmir *gokashmir;
		kpk *gokpk;
		
	gilgit_baltistan()
		{}
		gilgit_baltistan(const char *n,int m):province(n,m)
		{}
};
class kashmir:public province
{
	public:
		punjab *gopunjab;
		kpk *gokpk;
		gilgit_baltistan *gogilgit_baltistan;
		
		kashmir()
		{}
		kashmir(const char *n,int m):province(n,m)
		{}
};

class kpk:public province
{
	public:
		punjab *gopunjab;
		balochistan *gobalochistan;
		kashmir *gokashmir;
		gilgit_baltistan *gogilgit_baltistan;
		
		kpk()
		{}
		kpk(const char *n,int m):province(n,m)
		{}
};

class balochistan:public province
{
	public:
		punjab *gopunjab;
		sindh *gosindh;
		kpk *gokpk;
		balochistan()
		{}
		balochistan(const char *n,int m):province(n,m)
		{}
};

class punjab:public province
{
	public:
		sindh *gosindh;
		balochistan *gobalochistan;
		kpk *gokpk;
		kashmir *gokashmir;
		
		punjab()
		{}
		punjab(const char *n,int m):province(n,m)
		{}
};

class sindh:public province
{
	public:
		punjab *gopunjab;
		balochistan *gobalochistan;
		
		sindh()
		{}
		sindh(const char *n,int m):province(n,m)
		{}
};

class city
{
	public:
	string city_name;
	int no_of_towns;
	town *t1, *t2, *t3, *t4;
	city()
	{
		city_name= '\0';
		no_of_towns= 0;
	}
	city(string name,int t)
	{
		city_name= name;
		no_of_towns= t;
	}
	void display()
	{
		cout<<"City name: "<<city_name<<endl;
		cout<<"No of towns: "<<no_of_towns<<endl;
	}
};
class house;
house *head=NULL;
class house
{
	public:
	string house_adr;
	char salary;
	int count_prev_ration;
	int total_persons;
	int infected_persons;
	float priority;
	house *next;
	void display()
	{
		house *p= head;
		while(p)
		{
			cout<<p->count_prev_ration<<endl;
			cout<<p->infected_persons<<endl;
			cout<<p->salary<<endl;
			cout<<p->total_persons<<endl<<endl;
			cout<<p->house_adr<<endl;
			p=p->next;
		}
	}
};
class town 
{
	string town_name;
	int no_of_houses;
	public:
	house *h;
	town()
	{
		town_name= '\0';
		no_of_houses= 0;
	}
	town(string name,int h)
	{
		town_name= name;
		no_of_houses= h;
	}
	void display()
	{
		cout<<"Town name: "<<town_name<<endl;
		cout<<"No of houses: "<<no_of_houses<<endl;
	}
};

house* create_houses(int size)
{
	head= new house;
	head->house_adr= '\0';
	head->priority= 0;
	head->salary= '\0';
	head->count_prev_ration= 0;
	head->total_persons= 0;
	head->infected_persons= 0;
	head->next= NULL;
	house *tail;
	static house *temp;
	tail= head;
	for(int i=1;i<size;i++)
	{
		temp= new house;
		temp->house_adr= '\0';
		temp->priority= 0;
		temp->salary= '\0';
		temp->count_prev_ration= 0;
		temp->total_persons= 0;
		temp->infected_persons= 0;
		temp->next= NULL;
		tail->next= temp;
		tail= temp;
	}
	return head;
}

void store_houses_data(house *p,ifstream &fin)
{
	string house_adr;
	char salary;
	int total_persons;
	int infected_persons;
	int count_prev_ration;
	float priority;
	while(p)
	{
		getline(fin,house_adr);
		if(fin)
		{
			p->house_adr= house_adr;
			
			fin>>priority;
			p->priority= priority;
			
			fin>>salary;
			p->salary= salary;
			
			fin>>total_persons;
			p->total_persons= total_persons;
			
			fin>>infected_persons;
			p->infected_persons= infected_persons;
			
			fin>>count_prev_ration;
			p->count_prev_ration= count_prev_ration;
			
			fin.ignore();
		}
		p=p->next;
	}
}

class QUEUE{
	public:
		int front,rear;
		town **Q;
		int size;
	QUEUE()
	{
		front=rear=-1;
		size=20;
		
		Q=new town*[size];
	}
	~QUEUE()
	{
		delete []Q;
	}
	void enqueue(town *x)
	{
		if(rear==size-1)
		{
			cout<<"queue is full...";
		}
		else
		{
			rear++;
			Q[rear]=x;
		}
	}
	
	town* dequeue(void)
	{
		town *x=NULL;
		if(front==rear)
		{
			cout<<"queue is empty...";
		}
		else
		{
			front++;
			x=Q[front];
		}
		return x;
	}
};

void town_ptr(province *P,ifstream &fin)
{
	//QUEUE//
	town *ptr;
	town *to1=P->left_city->t1;	// town pointers 
	town *to2=P->left_city->t2;
	town *to3=P->left_city->t3;
	town *to4=P->left_city->t4;
	
	town *to5=P->middle_city->t1;
	town *to6=P->middle_city->t2;
	town *to7=P->middle_city->t3;
	town *to8=P->middle_city->t4;
	
	town *to9=P->right_city->t1;
	town *to10=P->right_city->t2;
	town *to11=P->right_city->t3;
	town *to12=P->right_city->t4;
	
	QUEUE Q;
	Q.enqueue(to1);
	Q.enqueue(to2);
	Q.enqueue(to3);
	Q.enqueue(to4);
	Q.enqueue(to5);
	Q.enqueue(to6);
	Q.enqueue(to7);
	Q.enqueue(to8);
	Q.enqueue(to9);
	Q.enqueue(to10);
	Q.enqueue(to11);
	Q.enqueue(to12);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t1_houses= ptr->h;
	store_houses_data(t1_houses,fin);
		
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t2_houses= ptr->h;
	store_houses_data(t2_houses,fin);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t3_houses= ptr->h;
	store_houses_data(t3_houses,fin);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t4_houses= ptr->h;
	store_houses_data(t4_houses,fin);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t5_houses= ptr->h;
	store_houses_data(t5_houses,fin);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t6_houses= ptr->h;
	store_houses_data(t6_houses,fin);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t7_houses= ptr->h;
	store_houses_data(t7_houses,fin);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t8_houses= ptr->h;
	store_houses_data(t8_houses,fin);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t9_houses= ptr->h;
	store_houses_data(t9_houses,fin);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t10_houses= ptr->h;
	store_houses_data(t10_houses,fin);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t11_houses= ptr->h;
	store_houses_data(t11_houses,fin);
	
	ptr=Q.dequeue();			
	ptr->h=create_houses(350);
	house *t12_houses= ptr->h;
	store_houses_data(t12_houses,fin);
}

void make_data_structure()
{
	static sindh S("Sindh",3);
	static punjab P("Punjab",3);
	static balochistan B("Balochistan",3);
	static kpk KP("Kpk",3);
	static gilgit_baltistan GB("Gilgit baltistan",3);
	static kashmir KASH("Kashmir",3);
	
	//FOR GLOBAL POINTERS//
	SINDH=&S;
	PUNJAB=&P;
	BALOCH=&B;
	KPK=&KP;
	GILGITBALTI=&GB;
	KASHMIR=&KASH;
	
	S.gopunjab=&P;      //CONNECTING LINKS OF GRAPH
	S.gobalochistan=&B;
	
	P.gobalochistan=&B;
	P.gokashmir=&KASH;
	P.gokpk=&KP;
	P.gosindh=&S;
	
	B.gokpk=&KP;
	B.gopunjab=&P;
	B.gosindh=&S;
	
	KP.gobalochistan=&B;
	KP.gogilgit_baltistan=&GB;
	KP.gokashmir=&KASH;
	KP.gopunjab=&P;
	
	GB.gokashmir=&KASH;
	GB.gokpk=&KP;
	
	static city karachi("Karachi",4), hyderabad("Hyderabad",4), larkana("Larkana",4);  // sindh
	S.left_city= &karachi;
	S.middle_city= &hyderabad;
	S.right_city= &larkana;
	
	static city lahore("Lahore",4), faisalabad("Faisalabad",4), multan("Multan",4);	// punjab
	P.left_city= &lahore;
	P.middle_city= &faisalabad;
	P.right_city= &multan;
	
	static city quetta("Quetta",4), sibi("Sibi",4), hub("Hub",4);	// balochistan
	B.left_city= &quetta;
	B.middle_city= &sibi;
	B.right_city= &hub;
	
	static city peshawar("Peshawar",4), mardan("Mardan",4), kohat("Kohat",4);	// KPK
	KP.left_city= &peshawar;
	KP.middle_city= &mardan;
	KP.right_city= &kohat;
	
	static city kotli("Kotli",4), muzzafarabad("Muzzafarabad",4), bhimber("Bhimber",4);	// kashmir
	KASH.left_city= &kotli;
	KASH.middle_city= &muzzafarabad;
	KASH.right_city= &bhimber;
	
	static city gilgit("Gilgit",4), skardu("Skardu",4), chilas("Chilas",4);	// gilgit baltistan
	GB.left_city= &gilgit;
	GB.middle_city= &skardu;
	GB.right_city= &chilas;
	// sindh
	static town k_town1("Karachi town 1",0), k_town2("Karachi town 2",0), k_town3("Karachi town 3",0), k_town4("Karachi town 4",0);	// karachi towns
	karachi.t1= &k_town1;
	karachi.t2= &k_town2;
	karachi.t3= &k_town3;
	karachi.t4= &k_town4;
	
	static town h_town1("Hyderabad town 1",0), h_town2("Hyderabad town 2",0), h_town3("Hyderabad town 3",0), h_town4("Hyderabad town 4",0);	// hyderabad towns
	hyderabad.t1= &h_town1;
	hyderabad.t2= &h_town2;
	hyderabad.t3= &h_town3;
	hyderabad.t4= &h_town4;
	
	static town l_town1("Larkana town 1",0), l_town2("Larkana town 2",0), l_town3("Larkana town 3",0), l_town4("Larkana town 4",0);	// larkana towns
	larkana.t1= &l_town1;
	larkana.t2= &l_town2;
	larkana.t3= &l_town3;
	larkana.t4= &l_town4;
	// punjab
	static town la_town1("Lahore town 1",0), la_town2("Lahore town 2",0), la_town3("Lahore town 3",0), la_town4("Lahore town 4",0);	// lahore towns
	lahore.t1= &la_town1;
	lahore.t2= &la_town2;
	lahore.t3= &la_town3;
	lahore.t4= &la_town4;
	
	static town f_town1("Faisalabad town 1",0), f_town2("Faisalabad town 2",0), f_town3("Faisalabad town 3",0), f_town4("Faisalabad town 4",0);	// faisalabad towns
	faisalabad.t1= &f_town1;
	faisalabad.t2= &f_town2;
	faisalabad.t3= &f_town3;
	faisalabad.t4= &f_town4;
	
	static town m_town1("Multan town 1",0), m_town2("Multan town 2",0), m_town3("Multan town 3",0), 	m_town4("Multan town 4",0);	// multan towns
	multan.t1= &m_town1;
	multan.t2= &m_town2;
	multan.t3= &m_town3;
	multan.t4= &m_town4;
	// kashmir
	static town ko_town1("Kotli town 1",0), ko_town2("Kotli town 2",0), ko_town3("Kotli town 3",0), ko_town4("Kotli town 4",0);	// kotli towns
	kotli.t1= &ko_town1;
	kotli.t2= &ko_town2;
	kotli.t3= &ko_town3;
	kotli.t4= &ko_town4;
	
	static town mu_town1("Muzzafarabad town 1",0), mu_town2("Muzzafarabad town 2",0), mu_town3("Muzzafarabad town 3",0), mu_town4("Muzzafarabad town 4",0);	// muzzafarabad towns
	muzzafarabad.t1= &mu_town1;
	muzzafarabad.t2= &mu_town2;
	muzzafarabad.t3= &mu_town3;
	muzzafarabad.t4= &mu_town4;
	
	static town B_town1("Bhimber town 1",0), B_town2("Bhimber town 2",0), B_town3("Bhimber town 3",0), B_town4("Bhimber town 4",0);	// bhimber towns
	bhimber.t1= &B_town1;
	bhimber.t2= &B_town2;
	bhimber.t3= &B_town3;
	bhimber.t4= &B_town4;
	//kpk
	static town P_town1("Peshawar town 1",0), P_town2("Peshawar town 2",0), P_town3("Peshawar town 3",0), P_town4("Peshawar town 4",0);	// peshawar towns
	peshawar.t1= &P_town1;
	peshawar.t2= &P_town2;
	peshawar.t3= &P_town3;
	peshawar.t4= &P_town4;
	
	static town M_town1("Mardan town 1",0), M_town2("Mardan town 2",0), M_town3("Mardan town 3",0), M_town4("Mardan town 4",0);	// mardan towns
	mardan.t1= &M_town1;
	mardan.t2= &M_town2;
	mardan.t3= &M_town3;
	mardan.t4= &M_town4;
	
	static town K_town1("Kohat town 1",0), K_town2("Kohat town 2",0), K_town3("Kohat town 3",0), K_town4("Kohat town 4",0);	// kohat towns
	kohat.t1= &K_town1;
	kohat.t2= &K_town2;
	kohat.t3= &K_town3;
	kohat.t4= &K_town4;
	//gilgit baltistan
	static town G_town1("Gilgit town 1",0), G_town2("Gilgit town 2",0), G_town3("Gilgit town 3",0), G_town4("Gilgit town 4",0);	// gilgit towns
	gilgit.t1= &G_town1;
	gilgit.t2= &G_town2;
	gilgit.t3= &G_town3;
	gilgit.t4= &G_town4;
	
	static town S_town1("Skardu town 1",0), S_town2("Skardu town 2",0), S_town3("Skardu town 3",0), S_town4("Skardu town 4",0);	// skardu towns
	skardu.t1= &S_town1;
	skardu.t2= &S_town2;
	skardu.t3= &S_town3;
	skardu.t4= &S_town4;
	
	static town C_town1("Chilas town 1",0), C_town2("Chilas town 2",0), C_town3("Chilas town 3",0), C_town4("Chilas town 4",0);	// chilas towns
	chilas.t1= &C_town1;
	chilas.t2= &C_town2;
	chilas.t3= &C_town3;
	chilas.t4= &C_town4;
	//balochistan
	static town Q_town1("Quetta town 1",0), Q_town2("Quetta town 2",0), Q_town3("Quetta town 3",0), Q_town4("Quetta town 4",0);	// quetta towns
	quetta.t1= &Q_town1;
	quetta.t2= &Q_town2;
	quetta.t3= &Q_town3;
	quetta.t4= &Q_town4;
	
	static town SIBI_town1("Sibi town 1",0), SIBI_town2("Sibi town 2",0), SIBI_town3("Sibi town 3",0), SIBI_town4("Sibi town 4",0);	// sibbi towns
	sibi.t1= &SIBI_town1;
	sibi.t2= &SIBI_town2;
	sibi.t3= &SIBI_town3;
	sibi.t4= &SIBI_town4;
	
	static town H_town1("Hub town 1",0), H_town2("Hub town 2",0), H_town3("Hub town 3",0), H_town4("Hub town 4",0);	// hub towns
	hub.t1= &H_town1;
	hub.t2= &H_town2;
	hub.t3= &H_town3;
	hub.t4= &H_town4;
	
	ifstream fin("Pakistan.txt");
	if(fin)
	{
		town_ptr(&S,fin);
		town_ptr(&P,fin);
		town_ptr(&B,fin);
		town_ptr(&KP,fin);
		town_ptr(&KASH,fin);
		town_ptr(&GB,fin);	
	}
	fin.close();
}

struct Hnode
{
	string addr;
	float priority;	
};  

void heapify(Hnode arr[], int n, int i) 
{ 
    int largest = i; 
    int l = 2 * i + 1; // left = 2*i + 1 
    int r = 2 * i + 2; // right = 2*i + 2 
  
    if (l < n && arr[l].priority > arr[largest].priority) 
        largest = l; 

    if (r < n && arr[r].priority > arr[largest].priority) 
        largest = r; 
 
    if (largest != i) { 
        swap(arr[i], arr[largest]); 
  
        heapify(arr, n, largest); 
    } 
} 
 
void heapSort(Hnode arr[], int n) 
{ 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
		 
    for (int i = n - 1; i >= 0; i--) 
	{ 
        swap(arr[0], arr[i]); 
        heapify(arr, i, 0); 
    } 
} 

void swap(Hnode v1,Hnode v2)
{
	Hnode temp;
	temp.addr= v1.addr;
	temp.priority= v1.priority;
	
	v1.addr= v2.addr;
	v1.priority= v2.priority;
	
	v2.addr= temp.addr;
	v2.priority= temp.priority;
	
}
int get_count(char choice)
{
	int count=0;
	string data;
	ifstream fin;
	if(choice=='R')
	fin.open("request.txt");
	else
	fin.open("survey.txt");
	float p;
	while(fin)
	{
		fin>>data;
		if(fin)
		{
			fin>>data;
			count++;
		}
	}
	fin.close();
	return count;
}
void heap_sort(char choice) 
{ 
	ifstream fin;
	int n;
	if(choice=='R')
	{
		fin.open("request.txt");
		if(fin)
		n= get_count('R');
	}
	else
	{
		fin.open("survey.txt");
		n= get_count('S');
	}
	
	Hnode *A= new Hnode[n];
	string data;
	int i=0;
	float p;
	while(fin)
	{
		fin>>data;
		if(fin)
		{
			A[i].addr= data;
			fin>>p;
			A[i].priority= p;
			i++;
		}
	}
	fin.close();
    heapSort(A, n); 
	ofstream fout;
    if(choice=='R')
    fout.open("request.txt");
    else
    fout.open("survey.txt");
    for(int j=n-1;j>=0;j--)
	{
		fout<<A[j].addr<<endl;
		fout<<A[j].priority<<endl;
	}
	fout.close();
	return;
}
void Goto_house(string ADDR,char choice,char char_data,int int_data)
{
	char PRO;
	char CITY[10];
	int TOWN;
	char HOUSE[10];
	
	province *pp=NULL;
	city *cp=NULL;
	town *tp=NULL;
	house *hp=NULL;
	
	PRO=ADDR[0];
	
	for(int i=1,j=0;i<=3;i++,j++)
	CITY[j]=ADDR[i];
	CITY[3]='\0';
	
	TOWN=ADDR[5];
	TOWN=TOWN-48;
	
	for(int i=7,j=0;i<=9;i++,j++)
	HOUSE[j]=ADDR[i];
	HOUSE[3]='\0';

	if(PRO=='S')
	pp=SINDH;
	else if(PRO=='P')
	pp=PUNJAB;
	else if(PRO=='K')
	pp=KPK;
	else if(PRO=='G')
	pp=GILGITBALTI;
	else if(PRO=='A')
	pp=KASHMIR;
	else if(PRO=='B')
	pp=BALOCH;
	else
	{
		cout<<"Incorrect Address...\n";
		return;	
	}
	
	if(!strcmp(CITY,"KAR")||!strcmp(CITY,"LAH")||!strcmp(CITY,"QUE")||!strcmp(CITY,"PES")||!strcmp(CITY,"KOT")||!strcmp(CITY,"GIL"))
	cp=pp->left_city;
	else if(!strcmp(CITY,"HYD")||!strcmp(CITY,"FAI")||!strcmp(CITY,"SIB")||!strcmp(CITY,"MAR")||!strcmp(CITY,"MUZ")||!strcmp(CITY,"SKA"))
	cp=pp->middle_city;
	else if(!strcmp(CITY,"LAR")||!strcmp(CITY,"MUL")||!strcmp(CITY,"HUB")||!strcmp(CITY,"KOH")||!strcmp(CITY,"BHI")||!strcmp(CITY,"CHI"))
	cp=pp->right_city;
	else
	{
		cout<<"Incorrect Address...\n";
		return;	
	}
	
	if(TOWN==1)
	tp=cp->t1;
	else if(TOWN==2)
	tp=cp->t2;
	else if(TOWN==3)
	tp=cp->t3;
	else if(TOWN==4)
	tp=cp->t4;
	else
	{
		cout<<"Incorrect Address...\n";
		return;
	}
	
	hp=tp->h;
	while(hp)
	{
		if(hp->house_adr==ADDR)
		break;
		else
		hp=hp->next;
	}
	if(hp)
	{
		if(hp->house_adr==ADDR)
		{
			if(choice=='D')
			hp->count_prev_ration= int_data;
			
			else if(choice=='S')
			hp->salary= char_data;
			
			else if(choice=='T')
			hp->total_persons= int_data;
			
			else
			hp->infected_persons= int_data;
		}
	}
}
void edit_data(string addr , char choice)
{
	ifstream fin("Pakistan.txt");
	ofstream fout("temp.txt");
	string data;
	if(choice=='I' || choice=='R')
	cout<<"\n\nPress -1 to go Back.. ";
	else if(choice!='D')
	cout<<"\n\nPress 0 to go Back.. ";
	while(fin)
	{
	fin>>data;
	if(fin)
	{
		if(addr!=data)
		{
			fout<<data<<endl;
			for(int i=1;i<=5;i++)
			{
				fin>>data;
				fout<<data<<endl;
			}
		}
		else
		{
			if(choice=='D')
			{
				fout<<data<<endl;
				for(int i=1;i<=5;i++)
				{
					if(i==5)
					{
						int count_ration;
						fin>>count_ration;
						count_ration++;
						fout<<count_ration<<endl;
						cout<<"\n\n\n\t\t"<<"Ration Distributed Successfully to House : "<<addr<<endl<<endl;
						Goto_house(addr,choice,'\0',count_ration);
					}
					else
					{
						fin>>data;
						fout<<data<<endl;
					}
				}
			}
			else if(choice=='S')
			{
				fout<<data<<endl;
				for(int i=1;i<=5;i++)
				{
					if(i==2)
					{
						fin>>data;
						string new_data;
						cout<<"\n\n\n\t\t\t\t"<<"Enter Salary (A-E): ";
						getline(cin,new_data);
						if(new_data=="0")
						{
							fin.close();
							fout.close();
							remove("temp.txt");
							return;
						}
						while(new_data!="A" && new_data!="B" && new_data!="C" && new_data!="D" && new_data!="E")
						{
							cout<<"\n\n\n\t\t\t\t"<<"Please enter b/w A and E ... ";
							getline(cin,new_data);
						}
						fout<<new_data<<endl;
						cout<<"\n\n\n\t\t\t\t"<<"New Salary Updated Successfully!"<<endl<<endl;
						char new_salary= new_data[0];
						Goto_house(addr,choice,new_salary,0);
						system("pause");
						system("cls");
					}
					else
					{
						fin>>data;
						fout<<data<<endl;
					}
				}
			}
			else if(choice=='T')
			{
				fout<<data<<endl;
				for(int i=1;i<=5;i++)
				{
					if(i==3)
					{
						fin>>data;
						string new_data;
						cout<<"\n\n\n\t\t\t\t"<<"Enter No of Total Persons (2-7): ";
						getline(cin,new_data);
						if(new_data=="0")
						{
							fin.close();
							fout.close();
							remove("temp.txt");
							system("cls");
							return;
						}
						while(new_data!="2" && new_data!="3" && new_data!="4" && new_data!="5" && new_data!="6" && new_data!="7")
						{
							cout<<"\n\n\n\t\t\t\t"<<"Please enter b/w 2 and 7 ... ";
							getline(cin,new_data);
						}
						fout<<new_data<<endl;
						cout<<"\n\n\n\t\t\t\t"<<"Number of Total Persons Updated Successfully!"<<endl<<endl;
						int val= new_data[0]-48;
						Goto_house(addr,choice,'\0',val);
						system("pause");
						system("cls");
					}
					else
					{
						fin>>data;
						fout<<data<<endl;
					}
				}
			}
			else
			{
				fout<<data<<endl;
				for(int i=1;i<=5;i++)
				{
					if(i==4)
					{
						fin>>data;
						string new_data;
						cout<<"\n\n\n\t\t\t\t"<<"Enter No of Infected Persons (0-7): ";
						getline(cin,new_data);
						if(new_data=="-1")
						{
							fin.close();
							fout.close();
							remove("temp.txt");
							system("cls");
							return;
						}
						while(new_data!="0" && new_data!="1" && new_data!="2" && new_data!="3" && new_data!="4" && new_data!="5" && new_data!="6" && new_data!="7")
						{
							cout<<"\n\n\n\t\t\t\t"<<"Please enter b/w 0 and 7 ... ";
							getline(cin,new_data);
						}
						fout<<new_data<<endl;
						cout<<"\n\n\n\t\t\t\t"<<"Number of Total Infected Persons Updated Successfully!"<<endl<<endl;
						int val= new_data[0]-48;
						Goto_house(addr,choice,'\0',val);
						system("pause");
						system("cls");
					}
					else
					{
						fin>>data;
						fout<<data<<endl;
					}
				}	
			}
		}
	}
	}
	fin.close();
	fout.close();
	remove("Pakistan.txt");
	rename("temp.txt","Pakistan.txt");
	return;
}
void login_system();
void Goto_house(string,char);
class user
{
	string username;
	float priority;
	public:
	void start()
	{
		cout<<"Press 0 To Go Back"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t1. Sign Up"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t2. Sign In"<<endl<<endl;
		string choice;
		cout<<endl<<endl<<endl<<"\t\t\t";
		cin>>choice;
		if(choice=="0")
		{
			system("cls");
			login_system();
		}
		else if(choice=="1")
		{
			system("cls");
			sign_up();
		}
		else if(choice=="2")
		{
			system("cls");
			sign_in();
		}
		else
		{
			cout<<endl<<endl<<endl<<"\t\t\tInvalid choice ... Try Again";
			system("pause");
			system("cls");
			start();
		}
	}
	void sign_up()
	{
		cout<<"\n\n\t\t\t\tS I G N   U P   P A G E"<<endl<<endl;
		cout<<"Press 0 To Go Back"<<endl<<endl;
		cout<<"\n\n\n\t\tUsername(House Address): ";
		fflush(stdin);
		getline(cin,username);
		if(username=="0")
		{
			system("cls");
			start();
			return;
		}
		ifstream fin("user ids.txt");
		string data;
		while(fin)
		{
			fin>>data;
			if(fin)
			{
				if(username==data)
				{
					cout<<"\n\n\n\t\tUsername already exist"<<endl;
					system("pause");
					system("cls");
					fin.close();
					sign_up();
				}
			}	
		}
		fin.close();		
		ifstream fin1("Pakistan.txt");
		while(fin1)
		{
			fin1>>data;
			if(fin1)
			{
				if(username==data)
				{
					char pass[20];
					cout<<"\n\n\n\t\tPassword: ";
					enter_password(pass);
					ofstream fout("user ids.txt",ios::app);
					fout<<username<<endl<<pass<<endl;
					fout.close();
					fin1.close();
					cout<<"\n\n\n\t\tAccount Created Successfully!"<<endl<<endl;
					cout<<"\n\n\n\t\tSign In Now ..."<<endl<<endl;
					system("pause");
					system("cls");
					sign_in();
				}
			}
		}
		fin1.close();
		cout<<"\n\n\n\t\tUsername(House Address) not found in the record."<<endl;
		system("pause");
		system("cls");
		sign_up();
	}
	void enter_password(char pass[])
	{
		char remove;
		int i=0;
		while(1)
		{
			pass[i]=getch();
			if(pass[i]==13)
			{
				pass[i]='\0';
				break;
			}
			else if(pass[i]==8)
			{
				remove=8;
				cout<<remove;
				remove=32;
				cout<<remove;
				remove=8;
				cout<<remove;
				i--;
				pass[i]='\0';
			}
			else if(pass[i]!=13)
			{
				cout<<"*";
				i++;
			}
		}
	}
	float set_priority()
	{
		ifstream fin("Pakistan.txt");
		string data;
		while(fin)
		{
			getline(fin,data);
			if(fin)
			{
				if(data==username)
				{
					fin>>priority;
					fin.close();
				}
			}
		}
	}
	void sign_in()
	{
		cout<<"\n\n\t\t\t\tS I G N   I N   P A G E"<<endl<<endl;
		cout<<"Press 0 To Go Back"<<endl<<endl;
		cout<<"\n\n\n\t\tUsername(House Address): ";
		fflush(stdin);
		getline(cin,username);
		if(username=="0")
		{
			system("cls");
			start();
			return;
		}
		char pass[50];
		cout<<"\n\n\n\t\tPassword: ";
		enter_password(pass);
		ifstream fin("user ids.txt");
		string data;
		while(fin)
		{
			getline(fin,data);
			if(fin)
			{
				if(data==username)
				{
					getline(fin,data);
					if(strcmp(pass,data.c_str())==0)
					{
						fin.close();
						set_priority();
						system("cls");
						display_functions();
					}
					else
					{
						cout<<"\n\n\n\t\tIncorrect Password ... Try Again"<<endl;
						system("pause");
						system("cls");
						fin.close();
						sign_in();
					}
				}
			}
		}
		fin.close();
		cout<<"\n\n\n\t\tUsername Not Found"<<endl;
		system("pause");
		system("cls");
		sign_in();
	}
	void display_functions()
	{
		cout<<endl<<endl<<endl<<"\t\t\t1. Request for Ration"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t2. View My House Info"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t3. Edit House Info"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t4. Logout"<<endl<<endl;
		string choice;
		cout<<endl<<endl<<"\t\t\tChoice: ";
		cin>>choice;
		if( strcmp(choice.c_str() , "1")==0)
		{
			system("cls");
			request_ration();
		}
		else if( strcmp(choice.c_str() , "2")==0)
		{
			system("cls");
			view_house_info();
		}
		else if( strcmp(choice.c_str() , "3")==0)
		{
			system("cls");
			edit_house_info();
		}
		else if( strcmp(choice.c_str() , "4")==0)
		{
			system("cls");
			start();
		}
		else
		{
			cout<<endl<<choice<<" is not Mentioned."<<endl;
			cout<<"Try Again.."<<endl;
			system("pause");
			system("cls");
			display_functions();
		}
	}
	void request_ration()
	{
		ifstream fin("request.txt");
		string data;
		while(fin)
		{
			getline(fin,data);
			if(fin)
			{
				if(username==data)
				{
					fin.close();
					cout<<"\n\n\t\tYou have already requested for Ration!"<<endl;
					cout<<"\n\n\t\tWe will respond to your request soon"<<endl;
					system("pause");
					system("cls");
					display_functions();
				}
			}
		}
	    ofstream fo;
        fo.open("request.txt", ios::app);
		fo<<username<<endl;
		fo<<priority<<endl;	
		fo.close();	
		cout<<"\n\n\t\tRation Request Sent Successfully!"<<endl;
		heap_sort('R');
		system("pause");
		system("cls");
		display_functions();
	}
	void view_house_info()
	{
		ifstream fin("Pakistan.txt");
		cout<<endl<<endl<<endl<<endl;
		string data;
		while(fin)
		{
			fin>>data;
			if(fin)
			{
				if(data==username)
				{
					cout<<"\t\tHouse Address. "<<data<<endl<<endl;
					fin>>data;
					cout<<"\t\tPriority. "<<data<<endl<<endl;
					fin>>data;
					cout<<"\t\tSalary. "<<data<<endl<<endl;
					fin>>data;
					cout<<"\t\tTotal Persons. "<<data<<endl<<endl;
					fin>>data;
					cout<<"\t\tInfected Persons. "<<data<<endl<<endl;
					fin>>data;
					cout<<"\t\tPrev Ration Count. "<<data<<endl<<endl;
					break;
				}
			}
		}
		fin.close();
		system("pause");
		system("cls");
		display_functions();
	}
	void edit_house_info()
	{
		cout<<"\n\nPress 0 to go Back.. ";
		cout<<endl<<endl<<endl<<"\t\t\t1. Edit Salary"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t2. Edit No of Total Persons"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t3. Edit No of Infected Persons"<<endl<<endl;
		string choice;
		cout<<endl<<endl<<"\t\t\t: ";
		cin>>choice;
		if( strcmp(choice.c_str() , "0")==0)
		{
			system("cls");
			display_functions();
		}
		else if( strcmp(choice.c_str() , "1")==0)
		{
			system("cls");
			edit_data(username,'S');
			system("cls");
			display_functions();
		}
		else if( strcmp(choice.c_str() , "2")==0)
		{
			system("cls");
			edit_data(username,'T');
			system("cls");
			display_functions();
		}
		else if( strcmp(choice.c_str() , "3")==0)
		{
			system("cls");
			edit_data(username,'I');
			system("cls");
			display_functions();
		}
		else
		{
			cout<<endl<<choice<<" is not Mentioned."<<endl;
			cout<<"Try Again.."<<endl;
			system("pause");
			system("cls");
			edit_house_info();
		}
	}
};
class administrator
{
	int ration_qu;
	public:
	administrator()
	{
		ration_qu= 0;
	}
	
	void login()
	{
		cout<<"\n\n\n\t\tW E L C O M E\tT O\tA D M I N I S T R A T O R"<<endl;
		cout<<"_______________________________________________________________________________"<<endl<<endl<<endl;
		cout<<"Press 0 To Go Back"<<endl<<endl;
		cout<<"\n\n\n\t\tUsername: ";
		string username;
		fflush(stdin);
		getline(cin,username);
		if(username=="0")
		{
			system("cls");
			login_system();
			return;
		}
		char pass[20];
		cout<<"\n\n\n\t\tPassword: ";
		enter_password(pass);
		if(username=="fastnukhi" && strcmp(pass,"dsproject")==0)
		{
			system("cls");
			display_functions();
		}
		else if(username=="fastnukhi" && strcmp(pass,"dsproject")!=0)
		{
			cout<<endl<<"Invalid Password"<<endl;
			system("pause");
			system("cls");
			login();
		}
		else if(username!="fastnukhi" && strcmp(pass,"dsproject")==0)
		{
			cout<<endl<<"Invalid Username"<<endl;
			system("pause");
			system("cls");
			login();
		}
		else
		{
			cout<<endl<<"Invalid Password and Usrname"<<endl;
			system("pause");
			system("cls");
			login();
		}
	}
	
	void enter_password(char pass[])
	{
		char remove;
		int i=0;
		while(1)
		{
			pass[i]=getch();
			if(pass[i]==13)
			{
				pass[i]='\0';
				break;
			}
			else if(pass[i]==8)
			{
				remove=8;
				cout<<remove;
				remove=32;
				cout<<remove;
				remove=8;
				cout<<remove;
				i--;
				pass[i]='\0';
			}
			else if(pass[i]!=13)
			{
				cout<<"*";
				i++;
			}
		}
	}
	
	void display_functions()
	{
		cout<<endl<<endl<<endl<<"\t\t\t1. Set Ration Quantity"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t2. View Requests for Ration"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t3. Distribute Ration to House (Request)"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t4. View Delivered Ration Houses (Request)"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t5. Take Survey"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t6. View Survey Results"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t7. Distribute Ration to House (Survey)"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t8. View Delivered Ration Houses (Survey)"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t9. Provinces Info"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t10. View All Houses Data"<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\t11. Logout"<<endl<<endl;
		string choice;
		cout<<endl<<endl<<"\t\t\tChoice: ";
		cin>>choice;
		if( strcmp(choice.c_str() , "1")==0)
		{
			system("cls");
			set_ration_qu();
		}
		else if( strcmp(choice.c_str() , "2")==0)
		{
			system("cls");
			view_file('R');
		}
		else if( strcmp(choice.c_str() , "3")==0)
		{
			system("cls");
			distribute_ration('R');
		}
		else if( strcmp(choice.c_str() , "4")==0)
		{
			system("cls");
			view_file('D');
		}
		else if( strcmp(choice.c_str() , "5")==0)
		{
			system("cls");
			take_survey();
		}
		else if( strcmp(choice.c_str() , "6")==0)
		{
			system("cls");
			view_file('S');
		}
		else if( strcmp(choice.c_str() , "7")==0)
		{
			system("cls");
			distribute_ration('S');
		}
		else if( strcmp(choice.c_str() , "8")==0)
		{
			system("cls");
			view_file('d');
		}
		else if( strcmp(choice.c_str() , "9")==0)
		{
			system("cls");
			provinces_info();
		}
		else if( strcmp(choice.c_str() , "10")==0)
		{
			system("cls");
			view_data();
		}
		else if( strcmp(choice.c_str() , "11")==0)
		{
			system("cls");
			login();
		}
		else
		{
			cout<<endl<<choice<<" is not Mentioned."<<endl;
			cout<<"Try Again.."<<endl;
			system("pause");
			system("cls");
			display_functions();
		}
	}
	
	void set_ration_qu()
	{
		cout<<endl<<endl<<endl<<"\n\n\t\t\tRation Quantity is set to "<<ration_qu<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\tDo you want to edit Ration Quantity? (y/n) ... ";
		string choice;
		cin>>choice;
		if(choice=="y")
		{
			cout<<endl<<endl<<endl<<"\t\t\tEnter quantity no: ";
			cin>>ration_qu;
			while(ration_qu<0)
			{
				cout<<"\n\n\t\t\tIt should be Positive Integer .. ";
				cin>>ration_qu;
			}
			cout<<endl<<endl<<endl<<"\t\t\tRation Quantity updated Successfully!"<<endl<<endl;
			system("pause");
			system("cls");
			set_ration_qu();
		}
		else if(choice=="n")
		{
			system("cls");
			display_functions();
		}
		else
		{
			cout<<endl<<endl<<endl<<"\t\t\tInvalid Choice ... Try Again";
			system("pause");
			system("cls");
			set_ration_qu();
		}	
	}
	
	void view_file(char choice)
	{
		ifstream fin;
		if(choice=='S')
		fin.open("survey.txt");
		else if(choice=='D')
		fin.open("delivered request.txt");
		else if(choice=='d')
		fin.open("delivered survey.txt");
		else
		fin.open("request.txt");
		int num=1;
		string data;
		while(fin)
		{
			fin>>data;
			if(fin)
			{
				cout<<num<<".\tHouse Address. "<<data<<endl;
				fin>>data;
				cout<<" \tPriority. "<<data<<endl<<endl;
				if(num%96==0)
				system("pause");
			}
			num++;
		}
		cout<<"\tEND"<<endl;
		fin.close();
		system("pause");
		system("cls");
		display_functions();
	}
	
	void take_survey()
	{
		ifstream fin("Pakistan.txt");
		string data;
		float av_priority=0;
		float priority=0;
		int break_cond= 0;
		fin>>data;
		fin>>priority;
		while(fin)
		{
			av_priority= av_priority+priority;
			for(int i=1;i<=5;i++)
			{
				if(fin)
				fin>>data;
				else 
				{
					break_cond=1;
					break;
				}
			}
			if(break_cond==1)
			break;
			fin>>priority;
		}
		av_priority= av_priority/25200;
		fin.close();
		
		break_cond= 0;
		ofstream fout("survey.txt");
		ifstream fin1("Pakistan.txt");
		fin1>>data;
		fin1>>priority;
		while(fin1)
		{
			if(priority>av_priority)
			fout<<data<<endl<<priority<<endl;
			for(int i=1;i<=5;i++)
			{
				if(fin1)
				fin1>>data;
				else 
				{
					break_cond=1;
					break;
				}
			}
			if(break_cond==1)
			break;
			fin1>>priority;
		}
		fout.close();
		fin1.close();
		cout<<endl<<endl<<endl<<"\t\t\tAverage Priority= "<<av_priority<<endl<<endl;
		cout<<endl<<endl<<endl<<"\t\t\tSuvery taken Successfully!"<<endl<<endl;
		heap_sort('S');
		system("pause");
		system("cls");
		display_functions();
	}
	
	void provinces_info()
	{
		int x[100];
		float y[100],b;
		int t=0;
		ifstream infile;
		infile.open("Pakistan.txt");
		if(infile.fail())
		{
			cout<<"file didn't work"<<endl;
			
		}
		else
		{
			string s;
			int i=1;
			float s1=0,s2=0,s3=0,s4=0,s5=0,s6=0;
			int a,sum=0,sum1=0,sum2=0,sum3=0,sum4=0,sum5=0;
			while(getline(infile, s))
			{
				
				if(i<=25200)
				{
				if(i%6==2)
				{
					istringstream(s)>>b;
					s1+=b;
					y[0]=s1;
				}
				if(i%6==5)
				{
					istringstream(s)>>a;
					sum+=a;
					x[0]=sum;	
			}}
			else if(i<=50400)
				{
				if(i%6==2)
				{
					istringstream(s)>>b;
					s2+=b;
					y[1]=s2;
				}
				
				if(i%6==5)
				{
					istringstream(s)>>a;
					sum1+=a;
					x[1]=sum1;	
			}}
			else if(i<=75600)
				{
				if(i%6==2)
				{
					istringstream(s)>>b;
					s3+=b;
					y[2]=s3;
				}
				
				if(i%6==5)
				{
					istringstream(s)>>a;
					sum2+=a;
					x[2]=sum2;	
			}}
			else if(i<=100800)
				{
				if(i%6==2)
				{
					istringstream(s)>>b;
					s4+=b;
					y[3]=s4;
				}
				
				if(i%6==5)
				{
					istringstream(s)>>a;
					sum3+=a;
					x[3]=sum3;	
			}}
			else if(i<=126000)
				{
				if(i%6==2)
				{
					istringstream(s)>>b;
					s5+=b;
					y[4]=s5;
				}
				
				if(i%6==5)
				{
					istringstream(s)>>a;
					sum4+=a;
					x[4]=sum4;	
			}}
			else if(i<=151200)
				{
				if(i%6==2)
				{
					istringstream(s)>>b;
					s6+=b;
					y[5]=s6;
				}
				
				if(i%6==5)
				{
					istringstream(s)>>a;
					sum5+=a;
					x[5]=sum5;	
			}}
			i++;
			}
			int k=sum,l=sum1,m=sum2,n=sum3,o=sum4,p=sum5;
			float k1=s1,l1=s2,m1=s3,n1=s4,o1=s5,p1=s6;
			int j,temp;
			cout<<endl<<endl;
			for(i=0;i<6;i++)
			{
				for(j=0;j<6-i-1;j++)
				{
					if(x[j]<x[j+1])
					{
						temp=x[j];
						x[j]=x[j+1];
						x[j+1]=temp;
					}
				}
			}
			cout<<endl<<"\tA.\tNO\tOF\tCASES"<<endl;
			cout<<"\t\t_____________________"<<endl<<endl;
			for(i=0;i<6;i++)
			{
				if(k==x[i])
				{
					cout<<"\t\t"<<i+1<<".\tSindh. "<<x[i]<<endl<<endl;
				}
				else if(l==x[i])
				{
					cout<<"\t\t"<<i+1<<".\tPunjab. "<<x[i]<<endl<<endl;
				}
				else if(m==x[i])
				{
					cout<<"\t\t"<<i+1<<".\tBalochistan. "<<x[i]<<endl<<endl;
				}
				else if(n==x[i])
				{
					cout<<"\t\t"<<i+1<<".\tKPK. "<<x[i]<<endl;
				}
				else if(o==x[i])
				{
					cout<<"\t\t"<<i+1<<".\tGilgit Baltistan. "<<x[i]<<endl<<endl;
				}
				else if(p==x[i])
				{
					cout<<"\t\t"<<i+1<<".\tKashmir. "<<x[i]<<endl<<endl;
				}
			}
			float temp1;
			cout<<endl<<endl<<endl;
			cout<<endl<<"\tB.\tRation\tPriority"<<endl;
			cout<<"\t\t________________"<<endl<<endl;
			for(i=0;i<6;i++)
			{
				for(j=0;j<6-i-1;j++)
				{
					if(y[j]<y[j+1])
					{
						temp1=y[j];
						y[j]=y[j+1];
						y[j+1]=temp1;
					}
				}
			}
			
			for(i=0;i<6;i++)
			{
				if(k1==y[i])
				{
					cout<<"\t\t"<<i+1<<".\tSindh. "<<y[i]/4200<<endl<<endl;
				}
				else if(l1==y[i])
				{
					cout<<"\t\t"<<i+1<<".\tPunjab. "<<y[i]/4200<<endl<<endl;
				}
				else if(m1==y[i])
				{
					cout<<"\t\t"<<i+1<<".\tBalochistan. "<<y[i]/4200<<endl<<endl;
				}
				else if(n1==y[i])
				{
					cout<<"\t\t"<<i+1<<".\tKPK. "<<y[i]/4200<<endl<<endl;
				}
				else if(o1==y[i])
				{
					cout<<"\t\t"<<i+1<<".\tGilgit Baltistan. "<<y[i]/4200<<endl<<endl;
				}
				else if(p1==y[i])
				{
					cout<<"\t\t"<<i+1<<".\tKashmir. "<<y[i]/4200<<endl<<endl;
				}
			}
			infile.close();
			infile.clear();
		}
		system("pause");
		system("cls");
		display_functions();
	}
	bool check(string addr)
	{
		ifstream fin("distribute.txt");
		string data;
		while(fin)
		{
			getline(fin,data);
			if(fin)
			{
				if(data==addr)
				return true;
			}
		}
		fin.close();
		return false;
	}
	void sort_distance_wise()
	{
		ifstream fin("Pakistan.txt");
		ofstream fout("distribute1.txt");
		string data;
		while(fin)
		{
			getline(fin,data);
			if(fin)
			{
				if(check(data))
				{
					fout<<data<<endl;
					getline(fin,data);
					fout<<data<<endl;
					getline(fin,data);
					getline(fin,data);
					getline(fin,data);
					getline(fin,data);
				}
				else
				{
					for(int i=0;i<5;i++)
					getline(fin,data);
				}
			}
		}
		fin.close();
		fout.close();
		remove("distribute.txt");
		rename("distribute1.txt","distribute.txt");
	}
	void distribute_ration(char choice)
	{
		int no_of_houses= get_count(choice);
		if(ration_qu==0)
		{
			cout<<"\n\n\t\t\tYou have Ration Quantity = 0\n\n\t\t\tYou have not Ration to Distribute"<<endl<<endl;
			system("pause");
			system("cls");
			display_functions();
		}
		if(no_of_houses==0)
		{
			cout<<"\n\n\t\t\tYou have Ration Quantity = "<<ration_qu<<endl<<endl;
			cout<<"\n\n\t\t\tYou have no any House to Distribute Ration"<<endl<<endl;
			system("pause");
			system("cls");
			display_functions();
		}
		cout<<"Press 0 to go  Back";
		cout<<"\n\t\t\tYou have Ration Quantity = "<<ration_qu<<endl<<endl;
		cout<<"\n\t\t\tYou have Houses for Distribute Ration = "<<no_of_houses<<endl<<endl;
		cout<<"\n\n\t\t\tHow much Quantity you want to Distribute? ";
		int qu;
		cin>>qu;
		if(qu==0)
		{
			system("cls");
			display_functions();
		}
		while(qu>ration_qu || qu<1 || qu>no_of_houses)
		{
			cout<<"\n\n\t\t\tTry Again ... ";
			cin>>qu;
		}
		ration_qu= ration_qu-qu;
		
		// store Houses for distribute
		ofstream fout("distribute.txt"), fout1;
		ifstream fin;
		if(choice=='R')
		{
			fin.open("request.txt");
			fout1.open("temp del.txt");
		}
		else 
		{
			fin.open("survey.txt");
		}
		string data;
		while(qu!=0)
		{
			getline(fin,data);
			if(fin)
			{
				fout<<data<<endl;
				getline(fin,data);
				fout<<data<<endl;
				qu--;
			}
		}
		fout.close();
		if(choice=='R')
		{
			while(fin)
			{
				getline(fin,data);
				if(fin)
				{
					fout1<<data<<endl;
					getline(fin,data);
					fout1<<data<<endl;
				}
			}
			fin.close();
			fout1.close();
			ofstream fr("request.txt");
			ifstream ft("temp del.txt");
			string data;
			while(ft)
			{
				getline(ft,data);
				if(ft)
				{
					fr<<data<<endl;
				}
			}
			ft.close();
			fr.close();
			remove("temp del.txt");
		}
		else fin.close();
		
		// sort and Deliver to Houses 
		sort_distance_wise();
		ifstream fin1("distribute.txt");
		int count=0;
		if(!fin1)
		cout<<"file not found";
		else
		{
			ofstream fstore;
			if(choice=='R')
			fstore.open("delivered request.txt",ios::app);
			else
			fstore.open("delivered survey.txt",ios::app);
			string data;
			while(fin1)
			{
				getline(fin1,data);
				if(fin1)
				{
					edit_data(data,'D');
					fstore<<data<<endl;
					getline(fin1,data);
					fstore<<data<<endl;
					count++;	
				}
			}
			fin1.close();
			fstore.close();
		}
		remove("distribute.txt");
		
		cout<<"\n\n\n\t\tRation Distributed Successfully to All "<<count<<" Houses!"<<endl;
		string ch;
		if(choice=='R')
		{
			cout<<"\n\n\t\tDo you want to clear All Requests (y/n)? ";
			cin>>ch;
			while(ch!="y" && ch!="n")
			{
				cout<<"\n\n\t\tInvalid ... Press 'y' or 'n' ... ";
				cin>>ch;
			}
			if(ch=="y")
			{
				ofstream fout("request.txt");
				fout.close();
				cout<<"\n\n\t\t\tRequests Cleared Successfully!"<<endl<<endl;
			}
			else
			{
				cout<<"\n\n\t\t\tRequests not Cleared"<<endl<<endl;
			}
		}
		else
		{
			cout<<"\n\n\t\tDo you want to clear Survey Data (y/n)? ";
			cin>>ch;
			while(ch!="y" && ch!="n")
			{
				cout<<"\n\n\t\tInvalid ... Press 'y' or 'n'"<<endl<<endl;
				cin>>ch;
			}
			if(ch=="y")
			{
				ofstream fout("survey.txt");
				fout.close();
				cout<<"\n\n\t\t\tSurvey Data Cleared Successfully!"<<endl<<endl;
			}
			else
			{
				cout<<"\n\n\t\t\tSurvey Data not Cleared"<<endl<<endl;
			}
		}
		system("pause");
		system("cls");
		display_functions();
	}
	
	void view_data()
	{
		ifstream fin("Pakistan.txt");
		int num=1;
		string data;
		while(fin)
		{
			fin>>data;
			if(fin)
			{
				cout<<num<<".\tHouse Address. "<<data<<endl;
				fin>>data;
				cout<<" \tPriority. "<<data<<endl;
				fin>>data;
				cout<<" \tSalary. "<<data<<endl;
				fin>>data;
				cout<<" \tTotal Persons. "<<data<<endl;
				fin>>data;
				cout<<" \tInfected Persons. "<<data<<endl;
				fin>>data;
				cout<<" \tPrev Ration Count. "<<data<<endl<<endl;
				if(num%42==0)
				system("pause");
			}
			num++;
		}
		cout<<"\tEND"<<endl;
		fin.close();
		system("pause");
		system("cls");
		display_functions();
	}
};
void login_system()
{
	string choice;
	system("color 2F");
	cout<<"\n\n\n_______________________________________________________________________________"<<endl;
	cout<<"\t\t\tR A T I O N\tD I S T R I B U T I O N"<<endl;
	cout<<"_______________________________________________________________________________"<<endl<<endl;
	cout<<endl<<endl<<endl<<"\t\t\t1.\tA D M I N I S T R A T O R"<<endl<<endl;
	cout<<endl<<endl<<endl<<"\t\t\t2.\tU S E R"<<endl<<endl;
	cout<<endl<<endl<<endl<<"\t\t\t3.\tE X I T"<<endl<<endl;
	cout<<endl<<endl<<endl<<"\t\t\tEnter Choice: ";
	cin>>choice;
	if(choice=="1")
	{
		system("cls");
		administrator admin;
		admin.login();
	}
	else if(choice=="2")
	{
		system("cls");
		user u;
		u.start();
	}
	else if(choice=="3")
	{
		system("cls");
		cout<<"\n\n\n\t\t\t   GROUP MEMBERS\n\n\t\t\t1. RITIK -\tK180130\n\n\t\t\t2. TAHA MIR -\tK180147\n\n\t\t\t3. SABIR -\tK181158"<<endl;	
		exit(1);
	}
	else
	{
		cout<<endl<<endl<<"\t\t\tInvalid Choice\n\t\t\tTry Again";
		system("pause");
		system("cls");
		login_system();
	}
}

int main()
{
	make_data_structure();
	login_system();
	return 0;
}
