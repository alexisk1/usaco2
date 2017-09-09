/*
ID: alexisk2
PROG: castle
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
struct coord{
  int x,y;
};

struct point{
  bool N;
  bool S;
  bool W;
  bool E;
};

void searchRoom(point*** castle, 
                bool** visited,
                       vector<coord*> *room, 
                      int x,int y,int xlim,int ylim){

    if(visited[x][y]==false){
       visited[x][y]=true;
       coord* a= new coord();
       a->x=x;
       a->y=y;
       room->push_back(a);
       if(castle[x][y]->N==false && y>0){
 				searchRoom(castle,
                           visited,
                           room,
                           x,y-1,xlim,ylim);        
       }
       if(castle[x][y]->S==false && y<ylim-1){
 				searchRoom(castle,
                           visited,
                           room,
                           x,y+1,xlim,ylim);  
       }
       if(castle[x][y]->W==false && x>0){
 				searchRoom(castle,
                           visited,
                           room,
                           x-1,y,xlim,ylim);  
       }
       if(castle[x][y]->E==false  && x<xlim-1){
 				searchRoom(castle,
                           visited,
                           room,
                           x+1,y,xlim,ylim);
       }
    }
 
};


bool check_adjacent(vector<coord*> a, vector<coord*> b){
  for(int i=0; i<a.size();i++){
     for(int t=0; t<b.size();t++){
         if(a[i]->x==b[t]->x-1 || a[i]->x==b[t]->x+1){
            if(a[i]->y==b[t]->y){
               return true;
            }
         }
         if(a[i]->y==b[t]->y-1 || a[i]->y==b[t]->y+1){
            if(a[i]->x==b[t]->x){
               return true;
            }
         }
     }
  }
  return false;
}
//N 0
//S 1
//W 2
//E 3
bool find_wall(vector<coord*> a, vector<coord*> b){
 cout<<"EDO";
  vector<coord*> adj;
  vector< int> adj_dir;
  for(int i=0; i<a.size();i++){
     for(int t=0; t<b.size();t++){
        if(a[i]->y==b[t]->y){
           if(a[i]->x==b[t]->x-1){
                coord *c= new coord();
                c->x=a[i]->x;
                c->y=a[i]->y;
                adj.push_back(c);
                adj_dir.push_back(3);
           }else if(a[i]->x==b[t]->x+1) {
                coord *c= new coord();
                c->x=b[t]->x;
                c->y=b[t]->y;
                adj.push_back(c);
                adj_dir.push_back(3);
           }
        }else if(a[i]->x==b[t]->x){
              if(a[i]->y==b[t]->y-1 ){
                coord *c= new coord();
                c->x=b[t]->x;
                c->y=b[t]->y;
                 adj.push_back(c);
                 adj_dir.push_back(0);
              }else if(a[i]->y==b[t]->y+1){
                coord *c= new coord();
                c->x=a[i]->x;
                c->y=a[i]->y;
                 adj.push_back(c);
                 adj_dir.push_back(0);
              }
        }
     }
  }

  int pos =0;
  int west=adj[0]->x;
  int south=adj[0]->y;
  for(int i=1; i<adj.size();i++){
     if(adj[i]->x<west){
        pos =i;
        west=adj[i]->x;
        south=adj[i]->y;
     }else if(adj[i]->x==west){
         if(adj[i]->y>south){
                pos =i;
                west=adj[i]->x;
                south=adj[i]->y;
         }
     }
  }
  ofs<<south+1 <<" "<<west+1<<" ";
  if(adj_dir[pos]==0){
      ofs<<"N\n";
  }else{
      ofs<<"E\n";
  }
}

int main() {

   ofs.open ("castle.out");
   ifs.open ("castle.in");

   
   int M,N;
   ifs>>M>>N;
   point*** castle;
   castle = new point** [M];
   for (int i=0; i < M; i++)
         castle[i] = new  point* [N];
   bool** visited;
   visited = new bool* [M];
   for (int i=0; i < M; i++)
         visited[i] = new bool[N];

   for(int y=0; y<N;y++){
		for(int x=0; x<M;x++){
            visited[x][y]=0;
		}
	}
   int p;

   for(int y=0; y<N;y++){
		for(int x=0; x<M;x++){
            ifs>>p;

            bool N=false,S=false,W=false,E=false;
            if(p>=8){
                S=true;
                p=p-8;
            }
            if(p>=4){
                E=true;
                p=p-4;
            }
            if(p>=2){
                N=true;
                p=p-2;
            }
            if(p>=1){
                W=true;
                p=p-1;
            }
            point* a=new point();
            a->N=N;
            a->S=S;
            a->W=W;
            a->E=E;
            castle[x][y]=a;
        }
   }
   ifs.close();

  vector< vector<coord*> > rooms;

  for(int y=0; y<N;y++){
		for(int x=0; x<M;x++){
           	if(visited[x][y]!=true){
                vector<coord*> room;   
				searchRoom(castle,
                           visited,
                           &room,
                           x,y,M,N);

                rooms.push_back(room);
           	}
        }
   }

   delete visited;
   delete castle;
   int max_adj=0;
   int maxi=0;
   int maxj=0;
   for (int i=0; i < rooms.size(); i++){
            for (int j=0; j < rooms.size(); j++){
                if (i!=j){
                    if( check_adjacent(rooms[i],rooms[j]) ){
                      if (max_adj<rooms[i].size()+rooms[j].size()) {
                           max_adj=rooms[i].size()+rooms[j].size();
                           maxi=i;
                           maxj=j;
                       }else if(max_adj==rooms[i].size()+rooms[j].size()){
                          if(rooms[i][0]->x<rooms[maxi][0]->x){
                               maxi=i;
                               maxj=j;
                          }else  if(rooms[i][0]->x==rooms[maxi][0]->x 
                                     && rooms[i][0]->y>rooms[maxi][0]->y){
                               maxi=i;
                               maxj=j;
                          }
                       }
                    }
                }
            }
   }
  int  max=0;
   for(int i=0;i<rooms.size();i++){
       if(rooms[i].size()>max){
          max = rooms[i].size(); 
       }
   }

   ofs<<rooms.size()<<"\n";
   ofs<<max<<"\n";
   ofs << max_adj<<"\n";
   find_wall(rooms[maxi],rooms[maxj]);
   return 0;
}

