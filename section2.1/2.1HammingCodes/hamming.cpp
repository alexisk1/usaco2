
/*
ID: alexisk2
PROG: hamming
LANG: C++11
*/

#include <fstream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath> 
using namespace std;

uint8_t check_distance(uint8_t a, uint8_t b, uint8_t bit_length)
{
  auto xored = a^b;
  uint8_t sum = 0;
  for(int i=0; i<bit_length; i++)
  {
     if(xored & 1 == 1)
        sum++;
     xored = xored >>1;
  }
  return sum;
}
 
int main() {

    std::ifstream ifs;
    std::ofstream ofs;
    ofs.open ("hamming.out");
    ifs.open ("hamming.in");
    int N,B,D;

    ifs>>N>>B>>D;
//    std::cout<< N<< " " << B<<" "<<D <<" "<<pow(2,B);
    unsigned int limit = std::pow(2, B);
    for(uint8_t i=0; i<limit; i++)
    {
        std::vector<uint8_t> visited;
        uint8_t start = i;
  //      std::cout<<"START:"<<std::to_string(start)<< " with limit "<<limit<<"\n";
        visited.push_back(i);
        uint8_t tot = 1;
        uint8_t previous = start;
        uint8_t pos = start + 1;
        while(tot<N && pos!=start)
        {
    //       std::cout<< " C:"<<to_string(pos)<<",";
           bool all_good = true;;
           for(uint8_t x=0; x<visited.size(); x++){
              auto dist = check_distance(visited[x], pos, B);
              if(dist<D)
                all_good = false;
           }
           if(all_good){
              visited.push_back(pos); 
              tot++;
           }
           pos++;
           if(pos == limit)
              pos = 0;
        }
        if(tot == N){
           for(uint8_t x=0; x<N; x++)
           {
              if(x%10==0 && x!=0){
                 ofs<<"\n";
              }else{
                 if(x!=0)
                 ofs<<" ";
              }
              ofs<<std::to_string(visited[x]);
           }
           ofs<<"\n";
           return 0;
        }
       
    }
    return 0;
}

