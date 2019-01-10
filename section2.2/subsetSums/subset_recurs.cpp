/*
ID: alexisk2
PROG: subset
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


void recurs_sets2(int sum, int max_used, int& max_sum, int &total_sol, int& N)
{
     if(sum == max_sum){
        total_sol++;
        return;
     }if (max_sum - sum < max_used ){
        return;
     }else{
        for(int i=max_used+1; i<=N;i++)
           recurs_sets2(sum+i, i, max_sum, total_sol, N);
     }
}


int main() {

    std::ifstream ifs;
    std::ofstream ofs;

    ofs.open ("subset.out");
    ifs.open ("subset.in");

    int N;
    ifs>>N;
    
    int max_sum = ((N+1)*N)/2;
    if (max_sum%2==1){
       ofs<<"0\n";
       return 0;
    }
    int sum=1;
    int total_sol = 0;
    recurs_sets2(sum, 1, max_sum, total_sol, N);
    ofs<<std::to_string(total_sol)+"\n";

    return 0;
}

