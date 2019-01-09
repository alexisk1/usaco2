

/*
ID: alexisk2
PROG: sort3
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
//   cout <<num[pos]<<"  "<<pos<<"  \n";
   if (num[pos]==1){
      int min_pos3=pos;
      for(int i=pos-1; i>=0; i--){
         if(num[i]==3){
            min_pos3=i;
         }
      }
  //    cout<<"min3  "<<min_pos3<<"\n";
      int min_pos2=pos;
      if(min_pos3==pos){
        for(int i=pos-1; i>=0; i--){
          if(num[i]==2){
            min_pos2=i;
          }
         }
    //   cout<<"min2 "<<min_pos2<<"\n";
      }else {
      // cout<<"AA"<<" \n"; 
       return min_pos3;
      }
      return min_pos2;
   }
  if (num[pos]==2){
      int min_pos3=pos;
      for(int i=pos-1; i>=0; i--){
         if(num[i]==3){
            min_pos3=i;
         }
      }
     // cout<<"min2 "<<min_pos3<<"\n";
      return min_pos3;
   }

   return pos;
} 

void sort_next(vector<int> num, int pos , int *changes ){
    if(pos>0){
       // cout<<pos<<" pppp "<<*changes<<"\n";
        if(num[pos]==3){
           sort_next(num, pos-1 ,changes);
        }else{
	   int sm=find_smallest(num,pos);
           if (sm !=pos){
         //      cout<<"Q!! SM "<<sm<<"\n";
		    (*changes)++;
	           cout<<"CHANGES  "<<*changes<<"\n "<<sm<< "  "<<pos<<"\n";
		   int  c= num[sm];
		   num[sm]=num[pos];
		   num[pos]=c; 
           }

     //for(int i=0; i<num.size();i++) cout<<"\n"<<num[i]<<"\n";
       // cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
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

   for(int i=0; i<num.size();i++) cout<<"\n"<<num[i]<<"\n";
   int changes = 0;
   sort_next(num,num.size()-1, &changes);
   cout<<"after\n"; 
  
   for(int i=0; i<num.size();i++) cout<<"\n"<<num[i]<<"\n";
   ofs<<changes<<"\n";
}

