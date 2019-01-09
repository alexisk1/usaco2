/*
ID: alexisk2
PROG: preface
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

void update_counting(std::vector<int> &letters, int num)
{

  // Update I and V for decimals
  int dec = num%10;
  int deca = ((num-dec)%100) / 10;
  int eka = ((num-dec-deca)%1000) / 100;


  if(dec<4){
     letters[0] = letters[0] + dec;
  }else if(dec<9){
     letters[0] = letters[0] + abs(dec-5);
     letters[1] = letters[1] + 1;
  }else{ //if(dec==9)
     letters[0] = dec == 0 ? letters[0] : letters[0] + 1;
     letters[2] = letters[2] + 1;
  }

  if(deca<4){
     letters[2] = letters[2] + deca;
  }else if(deca<9){
     letters[2] = letters[2] + abs(deca-5);
     letters[3] = letters[3] + 1;
  }else{
     letters[2] = deca ==0 ? letters[2] : letters[2] + 1;
     letters[4] = letters[4] + 1;
  }

  if(eka<4){
     letters[4] = letters[4] + eka;
  }else if(eka<9){
     letters[4] = letters[4] + abs(eka-5);
     letters[5] = letters[5] + 1;
  }else{
     letters[4] = eka == 0 ? letters[4] : letters[4] + 1;
     letters[6] = letters[6] + 1;
  }
   
 int th = num/1000;
 letters[6] = letters[6]+ th;
}
 
int main() {

    std::ifstream ifs;
    std::ofstream ofs;

    ofs.open ("preface.out");
    ifs.open ("preface.in");

    int N;
    ifs>>N;
    std::vector<int> letters(7);
    // I V  X  L   C   D    M
    // 1 5 10 50 100 500 1000
    for(int i=1; i<=N; i++)
    {
       update_counting(letters, i);

    }
    if(letters[0]!=0)
       ofs<<"I "<< std::to_string(letters[0])<<"\n";
    
    if(letters[1]!=0)
       ofs<<"V "<< std::to_string(letters[1])<<"\n";

    if(letters[2]!=0)
       ofs<<"X "<< std::to_string(letters[2])<<"\n";

    if(letters[3]!=0)
       ofs<<"L "<< std::to_string(letters[3])<<"\n";

    if(letters[4]!=0)
       ofs<<"C "<< std::to_string(letters[4])<<"\n";

    if(letters[5]!=0)
       ofs<<"D "<< std::to_string(letters[5])<<"\n";

    if(letters[6]!=0)
       ofs<<"M "<< std::to_string(letters[6])<<"\n";

    return 0;
}

