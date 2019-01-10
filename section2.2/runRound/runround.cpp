/*
ID: alexisk2
PROG: runround
LANG: C++11
*/

#include <fstream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath> 
#include <stdlib.h>     /* abs */

using namespace std;

bool check_if_runround(unsigned long x)
{
   unsigned long modulo = x;
   unsigned long sum_mods = 0;
   std::vector<unsigned char> numbers;
   bool unique[10]= {0};
   while(modulo>0){
        unsigned long n_mod = modulo % 10;
        
        if(n_mod == 0)
           return false;
        if(unique[n_mod])
           return false;
        unique[n_mod]=true;
        sum_mods += n_mod;
        numbers.insert(numbers.begin(), n_mod);
        modulo = modulo / 10;
   }

   auto nums = numbers.size();
   unsigned long pos = 0;
   bool map[nums] = {0};
   for(int i=0; i < nums; i++){
      auto new_pos = (pos + numbers[pos])%nums;
      if( map[new_pos])
          return false;
      map[new_pos] = true;
      pos = new_pos; 
   }
   
   return true;
}
int main() {

    std::ifstream ifs;
    std::ofstream ofs;

    ofs.open("runround.out");
    ifs.open("runround.in");

    unsigned long M;
    ifs>>M;
    bool res=false;
    while(res!=true){
         M++;
         res = check_if_runround(M);
    }
    ofs<<M<<"\n";
    return 0;
}

