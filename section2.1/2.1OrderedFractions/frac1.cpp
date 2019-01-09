
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

int main() {

   ofs.open ("frac1.out");
   ifs.open ("frac1.in");
   int n;
   ifs >> n;
   vector<int> a;
   vector<int> b;
   vector<float> c;
   for(int i=1; i<=n; i++){
       for(int j=1; j<=n; j++){
          if(i<j){
            a.push_back(i);
            b.push_back(j);
            c.push_back((float)i/(float)j);
           }
      }
   }
   for(int i=0; i<c.size(); i++){
      for(int j=0; j<c.size(); j++){
         if(c[i]<c[j]){
             int d,e;
             float f;
             d=a[i];
             a[i]=a[j];
             a[j]=d;
             d=b[i];
             b[i]=b[j];
             b[j]=d;
             f=c[i];
             c[i]=c[j];
             c[j]=f;
         }else    if(c[i]==c[j] && i!=j){
         if(a[i]<a[j]){
              a[j]=0;
              b[j]=0;
              c[j]=0;
           }else{
              a[i]=0;
              b[i]=0;
              c[i]=0;
           }
 }
      }
   } 

  /* for(int i=0; i<c.size(); i++){
      cout<<c[i]<<"\n";
   }  */ 
  ofs<<"0/1\n";
  for(int i =0; i<b.size();i++){
      if(a[i]!=0) ofs<<a[i]<<"/"<<b[i]<<"\n";
  }
  ofs<<"1/1\n";
}
