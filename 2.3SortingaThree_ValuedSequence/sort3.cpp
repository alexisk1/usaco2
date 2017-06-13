

/*
ID: alexisk2
PROG: frac1
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

int find_smallest(vector<int> num, int pos){
   int i=pos-1;
   if (num[i]<num[pos]){
      i--;
   }else{ 
      return i+1;
   }
   return pos;
} 

void sort_next(vector<int> num, int pos , int *changes ){
    if(pos>0){
        cout<<pos<<"\n";
        if(num[pos]==3){
           sort_next(num, pos-1 ,changes);
        }else{
	   int sm=find_smallest(num,pos);
           if (sm !=pos){
               cout<<"Q!! SM "<<sm<<"\n";
		   changes++;
		   int  c= num[sm];
		   num[sm]=num[pos];
		   num[pos]=c; 
           }
           sort_next(num,pos-1,changes);
        }
         
    }
}

int main() {

   ofs.open ("sort3.out");
   ifs.open ("sort3.in");
   int n;
   ifs>>n;
   int k;
   vector <int> num;
   for ( int i = 0; i < n ; i++ ){
         ifs>>k;
         num.push_back(k);      
   }
   int changes = 0;
   sort_next(num,num.size()-1, &changes);
   ofs<<changes;
}

