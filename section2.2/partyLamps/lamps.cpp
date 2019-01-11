/*
ID: alexisk2
PROG: lamps
LANG: C++11
*/

#include <fstream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath> 
#include <stdlib.h>     /* abs */
#include <algorithm>    // std::sort

using namespace std;

int find_next(const std::vector<bool> a, int pos){
    
    for(int i=pos; i<a.size(); i++){
        if(a[i]==true)
          return i;
    }
    return -1;
}

bool compare (std::vector<bool> a,std::vector<bool> b){ 
   // return a < b
   int pos_a = find_next(a,0);
   int pos_b = find_next(b,0);
   if(pos_a == -1 && pos_b>=0)
      return true;

   if( pos_a== -1 && pos_b==-1)
      return false;

   if( pos_a>=0 && pos_b== -1 )
      return false;

     if(pos_a<pos_b)
      return false;
     if(pos_a>pos_b)
      return true;


   while(pos_a == pos_b){
    if(pos_a ==-1)
       return false;
    pos_a = find_next(a,pos_a+1);
    pos_b = find_next(b,pos_b+1);

     if(pos_a<pos_b)
      return false;
     if(pos_a>pos_b)
      return true;
    }   
      
}



int main() {

    std::ifstream ifs;
    std::ofstream ofs;

    ofs.open("lamps.out");
    ifs.open("lamps.in");

    int N,C;
    ifs>>N;
    ifs>>C;
    std::vector<int> mask_off; 
    std::vector<int> mask_on;

    // read ON

    auto l = C;
    while(l!=-1){
        ifs>>l; 
        if(l !=-1){
           mask_on.push_back(l);
        }
    }

    // read OFF
    l = C;
    bool off_required=false;
    while(l!=-1){
        ifs>>l;
        if(l !=-1){
           mask_off.push_back(l);
            off_required=true;
         }
    }


    if(C==0){
       if(off_required){
          ofs<<"IMPOSSIBLE\n";
       }else{
          for(int i=0;i<N; i++)
             ofs<<"1";
         ofs<<"\n";
       }
       return 0;
    }

    std::vector<std::vector<bool>> results;
    for(int a=0; a<=1; a++){  
       for(int b=0; b<=1; b++){
          for(int c=0; c<=1; c++){
             for(int d=0; d<=1; d++){

                if(a+c+b+d>C || a+c+d+b==0)
                   continue;
                bool state[N];
                for(int i=0; i<N; i++)
                     state[i] = true; 
                // button 1
                if(a==1)
                    for(int x=0;x<N;x++)
                        state[x] = not state[x];
             
                // button 2
                if(b==1)
                    for(int x=0;x<N;x+=2)
                        state[x] = not state[x];

                // button 3
                if(c==1)
                    for(int x=1;x<N;x+=2)
                        state[x] = not state[x];

                // button 4
                if(d==1)
                    for(int x=0;x<N;x+=3)
                        state[x] = not state[x];
                
                bool break_f = false;
                for(auto off: mask_off){
                    if(state[off-1])
                      break_f =true;
                }
                for(auto on: mask_on)
		    if(state[on-1]==false)
		      break_f=true;
                if(break_f)
                     continue;
                std::vector<bool> sol_state(state, state+N);
                results.push_back(sol_state); 
                for(int i=0; i<N; i++){
                    std::cout<< (sol_state[i] ? 1 : 0) << " ";
                }
             }
          }
       }
    }

    if (results.size()==0){
       ofs<<"IMPOSSIBLE\n";
    }
        
    std::sort (results.begin(), results.end(), compare); 
    results.erase( unique( results.begin(), results.end() ), results.end() );

    for(auto res: results){
       for(int i=0; i<N; i++)
          ofs<<res[i];
       ofs<<"\n";
    }  
    return 0;
}

