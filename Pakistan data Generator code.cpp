#include<iostream>
#include <ctime> 
#include <cstdlib>
#include<fstream>
#include<math.h>
using namespace std;

char salary()
{
	int lowesti=65, highesti=69; 
    int rangei=(highesti-lowesti)+1;
	char random_char =0;
	random_char = lowesti+int(rangei*rand()/(RAND_MAX + 1.0));
	return random_char;
}
int prev_ration()
{
	int lowestr=0, highestr=3; 
    int ranger=(highestr-lowestr)+1; 	
	int random_r =0;
	random_r = lowestr+int(ranger*rand()/(RAND_MAX + 1.0));
	return random_r;
}
int total_persons()
{
	int lowestp=2, highestp=7; 
    int rangep=(highestp-lowestp)+1; 		
	int random_p =0;
	random_p = lowestp+int(rangep*rand()/(RAND_MAX + 1.0));
	return random_p;
}
int infected_persons()
{
	int lowestv=0, highestv=7; 
    int rangev=(highestv-lowestv)+1; 		
	int random_v =0;
	random_v = lowestv+int(rangev*rand()/(RAND_MAX + 1.0));
	return random_v;
}
int main()
{
	int x=0,y=3;////////Sindh punjab balochistan kpk gilgit kashmir
	string province[6]={"S","P","B","K","A","G"};
	string city[18]={"KAR","HYD","LAR","LAH","FAI","MUL","QUE","SIB","HUB","PES","MAR","KOH","KOT","MUZ","BHI","GIL","SKA","CHI"};
	char town= 'T';
	char house= 'H';
	int i,j,k,l;
	int count_town=1, count_house=1;
	ofstream fout("Pakistan.txt");
	for(i=0;i<6;i++)	// province
	{
		if(i==0)x=0;
		if(i==0)y=3;
		
		if(i==1)x=3;
		if(i==1)y=6;
		
		if(i==2)x=6;
		if(i==2)y=9;
		
		if(i==3)x=9;
		if(i==3)y=12;
		
		if(i==4)x=12;
		if(i==4)y=15;
		
		if(i==5)x=15;
		if(i==5)y=18;
		
		for(j=x;j<y;j++)	// city
		{
			for(k=0;k<4;k++)	// town
			{
				for(l=0;l<350;l++)	// house
				{
					
					if(count_house<10)
					fout<<province[i]<<city[j]<<town<<count_town<<house<<"00"<<count_house<<endl;
					else if(count_house>9 && count_house<100)
					fout<<province[i]<<city[j]<<town<<count_town<<house<<"0"<<count_house<<endl;
					else
					fout<<province[i]<<city[j]<<town<<count_town<<house<<count_house<<endl;
					
					char sal= salary();
					int tp= total_persons();
					int ip= infected_persons();
					while(ip>tp)
					{
						ip= infected_persons();
					}
					int prev_ration_count= prev_ration();
					float priority;
					int income;
					if(sal=='E')
					income= 1;
					else if(sal=='D')
					income= 2;
					else if(sal=='C')
					income= 3;
					else if(sal=='B')
					income= 4;
					else if(sal=='A')
					income= 5;
					priority= tp * (ip+1);
					float denominator= (prev_ration_count+1) * income;
					priority= priority/denominator;
					fout<<priority<<endl;
					fout<<sal<<endl;
					fout<<tp<<endl;
					fout<<ip<<endl;
					fout<<prev_ration_count<<endl;
					count_house++;
				}
				count_house=1;
				count_town++;
			}
			count_town= 1;
		}
	}
	fout.close();
	return 0;
}
