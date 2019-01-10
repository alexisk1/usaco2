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

int main() {

    std::ifstream ifs;
    std::ofstream ofs;

    ofs.open("subset.out");
    ifs.open("subset.in");

    int N;
    ifs>>N;
    long long max_sum = ((N+1)*N)/2;

    if (max_sum % 2 == 1){
       ofs<<"0\n";
       return 0;
    }

    long long total_sol = 0;
    long long partial_sums[820]= {0};

    partial_sums[0] = 1;

    for(long long sum=1; sum<=N; sum++){
        for(long long n=max_sum -sum;n>=0; n--){ 
           partial_sums[sum+n] += partial_sums[n];
        }
    }

    ofs<<partial_sums[max_sum/2]/2<<"\n";  

    return 0;
}

