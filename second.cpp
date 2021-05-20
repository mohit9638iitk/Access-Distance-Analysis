#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<stdio.h>

#define ll unsigned long long 

using namespace std;

unordered_map<ll,ll> m;//to find out most recently time of particular block address
unordered_map<ll,ll> Count;//count the number of occurence of particular access distance 
int main(int argc,char**argv)
{
  
  if(argc<2)
  {
	cout<<"Please Enter the Trace File name";
	return 0;
  }
 	
 	FILE *fp;
	fp=fopen(argv[1],"rb");	
	ll i=0;
	ll Maximum_Distance=0;//longest access distance 
	ll tid,Address;
	ll size=0;//for counting the number of observations as F(d)=d/N
	while(!feof(fp))
	{
		i++;
		fread(&tid,sizeof(ll),1,fp);
		fread(&Address,sizeof(ll),1,fp);
		ll Block_Address=(Address)/64;
		//block is access for first time
		if(m.find(Block_Address) == m.end())
		{
			m[Block_Address]=i;
		}
		else//previous access to this block is accessed 
		{
			ll distance=i-m[Block_Address];
			m[Block_Address]=i;
			Maximum_Distance=max(distance,Maximum_Distance);
			if(Count.find(distance)!=Count.end())
			{
				Count[distance]++;
			}
			else
			{
				Count[distance]=1;
			}
			size++;
		}
	}

	ll N=size;
	ll cumulative_Dist=0;
	double cumulative_Prob=0.0;
	ofstream ofs;
	ofs.open("plotData.csv",ofstream::out);
        double previous =0.0;
	/*there are some prog like prog4 where cumulative probability for each access
	 distance  is required for smooth curve.
	 if big program like prog1 is runned ,please remove this previous variable part of
	 code ,as the generated csv file will become very big around GB of data*/ 
	
	//for writing the data in csv file,stackoverflow is used 	
	for(ll d=1;d<=Maximum_Distance;d++)
	{

		if(Count.find(d)!=Count.end())
		{
			cumulative_Dist=cumulative_Dist+Count[d];
			cumulative_Prob=(double)(cumulative_Dist/N);
			previous=cumulative_Prob;
			ofs<<d<<','<<cumulative_Prob<<endl;
		}
		else
		{
			ofs<<d<<","<<previous<<endl;
		}
	}

	ofs.close();
	fclose(fp);
	return 0;
}
		

