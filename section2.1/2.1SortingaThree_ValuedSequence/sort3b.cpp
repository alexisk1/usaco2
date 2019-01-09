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


int main() {

   ofs.open ("sort3.out");
   ifs.open ("sort3.in");
   int n;
   ifs>>n;
   int k;
   vector <int> num;
   int no_1=0;
   int no_2=0;
   int no_3=0;
   for ( int i = 0; i < n ; i++ ){
         ifs>>k;
         num.push_back(k);
         if(k==1) no_1++;  
         if(k==2) no_2++; 
         if(k==3) no_3++;                   
   }
  
   int changes = 0;
//   sort_next(num,num.size()-1, &changes);

   int a2=0;
   int a3=0;
   for(int i=0; i<no_1;i++){
       if(num[i]==2){
           a2++;
       }else if (num[i]==3){
           a3++;
       }
   }
   int b1=0;
   int b3=0;
   for(int i=no_1; i<no_1+no_2;i++){
       if(num[i]==1){
           b1++;
       }else if (num[i]==3){
           b3++;
       }
   }
   int c1=0;
   int c2=0;
   for(int i=no_1+no_2; i<no_1+no_2+no_3;i++){
       if(num[i]==1){
           c1++;
       }else if (num[i]==2){
           c2++;
       }
   }  
     
  cout<< "AA  a2:"<<a2<<"  a3:" <<a3<<"\n";
  cout<< "BB  b1:"<<b1<<"  b3:" <<b3<<"\n";
  cout<< "CC  c1:"<<c1<<"  c2:" <<c2<<"\n";

   if(b3!=0 && c2!=0){
        changes+=b3;
        c2=c2-b3;
        b3=0;
   }
   cout<< "\n1)AA  a2:"<<a2<<"  a3:" <<a3<<"\n";
  cout<< "BB  b1:"<<b1<<"  b3:" <<b3<<"\n";
  cout<< "CC  c1:"<<c1<<"  c2:" <<c2<<"\n";


   if(b3!=0 && c1!=0){
        changes+=b3;
        c1=c1-b3;
        b1=b1+b3;
        b3=0;
   }

  cout<< "\n2)AA  a2:"<<a2<<"  a3:" <<a3<<"\n";
  cout<< "BB  b1:"<<b1<<"  b3:" <<b3<<"\n";
  cout<< "CC  c1:"<<c1<<"  c2:" <<c2<<"\n";


   if(a3!=0 && c1!=0){
        changes+=a3;
        if(c1>a3){
           c1=c1-a3;
            a3=0;
        } else{
           a3=a3-c1;
           c1=0;
        }
        
      
   }
   cout<< "\n3)AA  a2:"<<a2<<"  a3:" <<a3<<"\n";
  cout<< "BB  b1:"<<b1<<"  b3:" <<b3<<"\n";
  cout<< "CC  c1:"<<c1<<"  c2:" <<c2<<"\n";

   if(c2!=0 && a3!=0){
     changes+=a3;
     c2=c2-a3;
     a3=0;
   }    
   if(b1!=0 && a2!=0){
        changes+=a2;
        b1=b1-a2;
        a2=0;
   }
  cout<< "\n4)AA  a2:"<<a2<<"  a3:" <<a3<<"\n";
  cout<< "BB  b1:"<<b1<<"  b3:" <<b3<<"\n";
  cout<< "CC  c1:"<<c1<<"  c2:" <<c2<<"\n";

   ofs<<changes<<"\n";
}

