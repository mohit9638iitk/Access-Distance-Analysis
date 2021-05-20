#include<iostream>
#include<bits/stdc++.h>
#define ll unsigned long long 
using namespace std;

int main(int argc,char**argv)
{
	if(argc<2)
 	{
		cout<<"Please Enter the Trace File name";
		return 0;
  	}
	
	FILE *fp;
	fp=fopen(argv[1],"rb");	
	
	
	unordered_map<ll,array<bool,8> > m;	
	ll tid,Address;
	while(!feof(fp))
	{
		fread(&tid,sizeof(ll),1,fp);
		fread(&Address,sizeof(ll),1,fp);
		ll Block_Address=(Address)/64;
		
		m[Block_Address][tid]=true;
	}
	
	int count[9]={0};//number of thread varyies from 1 to 8 ,total size will be 9 as index 0 is not used
	
	for(auto j:m)
	{
		//j.first is block address
		int ans=0;
		for(auto k:j.second)
		{
			if(k==true)
			{
				ans++;
			}
		}
		count[ans]++;
	}
	//count[0] will contain the number of private blocks 
	cout<<"the number of private blocks  "<<count[1]<<endl;
	for(int i=2;i<=8;i++)
	{
		cout<<"Number of blocks "<<count[i]<<" shared by "<<i<<"threads"<<endl;
	}
	return 0;
}
		
		
 
