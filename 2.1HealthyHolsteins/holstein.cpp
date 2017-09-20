
/*
ID: alexisk2
PROG: holstein
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>    // std::sort
#include <string>


std::ifstream ifs;
std::ofstream ofs;
using namespace std;


bool dfs(int *scoops,int *sums,vector<int> *list,int **feeds,int V,int F,int min_V[], int lvl){
    bool right =true;
    for(int x=0;x<V;x++){
		if(sums[x]<min_V[x]){ right=false; break;
		}
	}
	if(right)return true;
    bool ret=true;

    for (int i=0;i<V;i++){
        if(sums[i]<min_V[i] ){
			ret=false;
			break;
		}
		
    }
    if(ret ) return true;
    int min_scoops=*scoops;
    vector<int> min_list_a;
    int min_sums[V];
    for(int x=0;x<V;x++) min_sums[x]=sums[x];
    for(int x=0;x<list->size();x++)min_list_a.push_back((*list)[x]);
   

    int DD=0;
    if(list->size()>0) DD=(*list)[list->size()-1];
    for (int i=DD; i<F;i++){
          int  scoops_a=*scoops;
          scoops_a++;
          int sums_a[V];
          for(int x=0;x<V;x++) {sums_a[x]=sums[x]+feeds[i][x]; }
          vector<int> list_a;
          for(int x=0;x<list->size();x++)list_a.push_back((*list)[x]);
          bool exists=false;
          for(int x=0;x<list->size();x++) if((*list)[i]==i) exists=true;
          if(exists==false) list_a.push_back(i);
          bool above=true;
          for(int x=0;x<V;x++) if(sums[x]<min_V[x] && feeds[i][x]!=0) above=false;
          bool zeros=false; 
          if(above==true){
            for(int x=0; x<V;x++)if(sums[x]<min_V[x] && feeds[i][x]==0)zeros=true;
          }
          bool res=false;
         if(zeros==false){ res=dfs(&scoops_a,sums_a,&list_a,feeds,V,F,min_V,lvl+1);
		 
         if(res){
          if(min_scoops==*scoops){
                  min_scoops=scoops_a;
               //   min_list_a.clear();

			      min_list_a=list_a;
                  for(int x=0;x<V;x++) min_sums[x]=sums_a[x];
          }else if(min_scoops>scoops_a){
                min_scoops=scoops_a;
             //   min_list_a.clear();
                min_list_a=list_a;
                for(int x=0;x<V;x++) min_sums[x]=sums_a[x];
          }else if(min_scoops==scoops_a){
               int sum1=0;
			   //cout<<"CCC!!\n";
               bool right =true;
            /*   for(int x=0;x<V;x++) if(sums_a[x]<min_V[x]) right=false;
               for(int y=0;y<V;y++)sum1+=feeds[min_list_a[min_list_a.size()-1]][y];
               int sum2=0;
               for(int y=0;y<V;y++)sum2+=feeds[list_a[list_a.size()-1]][y];*/
			   for(int x=0;x<V;x++) if(sums_a[x]>min_sums[x] ) right=false;
            if( right){
                 min_scoops=scoops_a;
                 min_list_a.clear();
		         min_list_a=list_a;     
             for(int x=0;x<V;x++) min_sums[x]=sums_a[x];
            }
			}        
         }}
    }
    for(int x=0;x<V;x++) if(min_sums[x]<min_V[x])return false;
/*				     cout<<"Min_V\n";
    for(int x=0;x<V;x++)cout<<min_V[x]<<" ";
	cout<<"\n";
    cout<<"sums\n";
    for(int x=0;x<V;x++)cout<<sums[x]<<" ";
	cout<<"\n";
    cout<<"min_sums\n";
    for(int x=0;x<V;x++)cout<<min_sums[x]<<" ";
	cout<<"\n";*/
    for(int x=0;x<V;x++) sums[x]=min_sums[x];
		/*cout<<"\n kusta\n";

	    for(int x=0;x<list->size();x++) cout<<(*list)[x]<<" ";
		cout<<"\n";*/

    *scoops=min_scoops;
    list->clear();   
    *list=min_list_a;

 return true;
};

int main(){
   ofs.open("holstein.out");
   ifs.open("holstein.in");
   int V;
   ifs>>V;
 // cout<<V<<"\n";
   int min_V[V];
   for(int i=0;i<V;i++){
     ifs>>min_V[i];
   //  cout<<min_V[i]<<" ";
   }
   cout<<"\n";
   int F;
   ifs>>F;
  // cout<<F<<"\n";
   int **feeds;//[F][V];
   feeds= new int*[F];
   for(int i=0; i<F;i++){
      feeds[i]=new int[V];   
   }
   int max_f[V];

   for(int i=0;i<V;i++){
     max_f[0];
   }
   
   for(int x=0;x<F;x++){
      for (int i=0;i<V;i++){
          ifs>>feeds[x][i];
      }
   }
 // cout<<"!!\n";
  int scoops=0;
  vector<int> list;
  int *sums=new int[V];
 // cout<<"asda\n";
  for(int i=0;i<V; i++)
      sums[i]=0;
 //  cout<<V<< "V"<< F<<" F\n";
  dfs(&scoops,sums,&list,feeds,V,F,min_V,0);
   cout<<scoops<<"  VGEEE\n"<<list.size()<<"\n";
  ofs<<scoops<<" "; for(int i=0;i<list.size()-1;i++) ofs<<list[i]+1<<" ";
  ofs<<list[list.size()-1]+1<<"\n";
 //cout<<"\n";
}

