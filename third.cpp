#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

#define l2_set 2048
#define l2_associativity 16
#define l2_block_size 64


#define ull unsigned long long 
class cache{
	public:
		bool valid;
		unsigned long long tag;
		unsigned long long counter;
		cache()
		{
			valid=false;
			tag=-1;
			counter	=-1;
		}
};	



void space_free(cache** &C,int num_of_set,int associativity,int block_size)
{
	for(int i=0;i<associativity;i++)
	{
	      delete C[i];
	}
	delete C;
       return ;
}

void  space_acquire(cache**&C,int num_of_set,int associativity,int block_size)
{

	C=new cache*[num_of_set*sizeof(cache*)];
	for(int i=0;i<num_of_set;i++)
	{

		C[i]=new cache[associativity*sizeof(cache)];
	}
	return ;
}

int count_bits(int x)
{
	int ans=0;
	while(x>0)
	{ 
   	   x>>=1;
	   ans++;
        }
    return ans-1;
}
bool back_inv(cache**&C,int num_of_set,int associativity,int block_size,ull address)
{
	int add_64[64]={0};
	int count=0;
	ull value=address;
	while(address>0)
	{
		add_64[count]=(address&1);
		count++;
		address>>=1;
	}
	int block_offset_bits=count_bits(block_size);
	int index_bits=count_bits(num_of_set);
	int index=0;
	long long  ans=1;
	for(int i=block_offset_bits;i<(index_bits+block_offset_bits);i++)
	{
		index+=(add_64[i]*ans);
		ans<<=1;
	}
        
	ull tag=0;
	ans=1;
	for(int i=index_bits+block_offset_bits;i<64;i++)
	{
	    tag+=(add_64[i]*ans);
	    ans<<=1;
	}
        //now we have index and tag . Tag contain block address.index contain the set number
	for(int i=0;i<associativity;i++)
	{
		if((C[index][i].valid==true)&&(C[index][i].tag==tag))
		{
			C[index][i].valid=false;
			return true;	
		}
	}
	return false;


}
int lru_replacement(cache * &set_index,int associativity)
{
	for(int i=0;i<associativity;i++)
	{
		if(!set_index[i].valid)
		{
			return i;
		}
	}
	int index=0;
        for(int i=0;i<associativity;i++)
	{
		if(set_index[i].counter<set_index[index].counter)
		{
			index=i;
		}
	}
	return index;
}
bool cache_present(cache ** &C,int num_of_set, int associativity, int block_size, ull address, ull current_counter)
{
	int add_64[64]={0};
	int count=0;
	ull value=address;
	while(address>0)
	{
		add_64[count]=(address&1);
		count++;
		address>>=1;
	}
	int block_offset_bits=count_bits(block_size);
	int index_bits=count_bits(num_of_set);
	int index=0;
	long long  ans=1;
	for(int i=block_offset_bits;i<(index_bits+block_offset_bits);i++)
	{
		index+=(add_64[i]*ans);
		ans<<=1;
	}
        
	ull tag=0;
	ans=1;
	for(int i=index_bits+block_offset_bits;i<64;i++)
	{
	    tag+=(add_64[i]*ans);
	    ans<<=1;
	}
	
	for(int i=0;i<associativity;i++)
	{
		if((C[index][i].valid==true)&&(C[index][i].tag==tag))
		{
			C[index][i].counter=current_counter;
			return true;
		}
	}
	return false;
	
}

ull cache_handler_miss(cache ** &C,int num_of_set,int associativity,int block_size,ull address, ull current_counter)
{
	int add_64[64]={0};
	int count=0;
	ull value=address;
	while(address>0)
	{
		add_64[count]=(address&1);
		count++;
		address>>=1;
	}
	int block_offset_bits=count_bits(block_size);
	int index_bits=count_bits(num_of_set);
	int index=0;
	long long  ans=1;
	for(int i=block_offset_bits;i<(index_bits+block_offset_bits);i++)
	{
		index+=(add_64[i]*ans);
		ans<<=1;
	}
        
	ull tag=0;
	ans=1;
	for(int i=index_bits+block_offset_bits;i<64;i++)
	{
	    tag+=(add_64[i]*ans);
	    ans<<=1;
	}
	
	ull evicted_address,evicted_tag;
	
	int replace_line=lru_replacement(C[index],associativity);
	if(!C[index][replace_line].valid)
	{
		evicted_address=-1;
	}
	else
	{
		evicted_tag=C[index][replace_line].tag;
		evicted_address=(evicted_tag*num_of_set+index)*(block_size);
	}
	C[index][replace_line].tag=tag;
	C[index][replace_line].valid=true;
	C[index][replace_line].counter=current_counter;

	return evicted_address;
	
}


void inclusive(int argc,char ** argv)
{


        cache **l2;
	space_acquire(l2,l2_set,l2_associativity,l2_block_size);
	unsigned long long Addr, tid;

	ull access_counter = 0;
	ull l2_miss_counter = 0;
	ull l2_hit_counter = 0;

    	FILE* fp;
	fp = fopen(argv[1], "rb");
    
    	char output_name[100];
    	sprintf(output_name, "filter_%s", argv[1]);
    	FILE* fp1;
    	fp1 = fopen(output_name,"wb");
	assert(fp1 != NULL);
    	while (!feof(fp))
    	{
    	     fread(&tid, sizeof(unsigned long long), 1, fp);
	     fread(&Addr, sizeof(unsigned long long), 1, fp);
    	        access_counter++;
    	        if(cache_present(l2,l2_set,l2_associativity,l2_block_size,Addr,access_counter))
    	        {
    	            	l2_hit_counter++;
    	        }
    	        else
    	        {
    	            	l2_miss_counter++;
			fwrite(&tid, sizeof(unsigned long long), 1, fp1);
            		fwrite(&Addr, sizeof(unsigned long long), 1, fp1);
           	        cache_handler_miss(l2,l2_set,l2_associativity,l2_block_size,Addr,access_counter);
    	                
    	        }
    	    
    	}
    	fclose(fp);
	fclose(fp1);
	

	space_free(l2,l2_set,l2_associativity,l2_block_size);
    	cout<<"Total Access  "<<access_counter<<endl;
    	cout<<"Total Hit     "<<l2_hit_counter<<endl;
	cout<<"Total Miss    "<<l2_miss_counter<<endl;
	
	return ;
}



int main(int argc,char**argv)
{
    inclusive(argc,argv);
    return 0;
}
