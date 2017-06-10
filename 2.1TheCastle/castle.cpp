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
  unsigned char x,y;
  coord( unsigned char x,  unsigned char y):x(x),y(y){
  }
};

struct point{
  bool N;
  bool S;
  bool W;
  bool E;
  point(bool N,bool S,bool W,bool E):N(N),S(S),W(W),E(E){
  }
};

void searchRoom(point*** castle, 
                bool** visited,
                       vector<coord*> *room, 
                      int x,int y,int xlim,int ylim){

    if(visited[x][y]==false){
    //cout<<"\n"<<x<<" " << y<<"\n";
       visited[x][y]=true;
       room->push_back(new coord(x,y));
       if(castle[x][y]->N==false && y>0){
       //     cout<<"N";
 				searchRoom(castle,
                           visited,
                           room,
                           x,y-1,xlim,ylim);        
       }
       if(castle[x][y]->S==false && y<ylim-1){
    //        cout<<"S";
 				searchRoom(castle,
                           visited,
                           room,
                           x,y+1,xlim,ylim);  
       }
       if(castle[x][y]->W==false && x>0){
     //       cout<<"W";
 				searchRoom(castle,
                           visited,
                           room,
                           x-1,y,xlim,ylim);  
       }
       if(castle[x][y]->E==false  && x<xlim-1){
    //        cout<<"E";
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
  vector<coord*> adj;
  vector< unsigned char> adj_dir;
/*cout<<"\n a ";
        for (int r=0; r< a.size(); r++){
            cout<<"  "<< a[r]->x<<" "<< a[r]->y<<" "<<"\n";
        }

cout<<"\n  b";

        for (int r=0; r< b.size(); r++){
            cout<<"  "<< b[r]->x<<" "<< b[r]->y<<" "<<"\n";
        }
cout<<"\n  ";*/
  for(int i=0; i<a.size();i++){
     for(int t=0; t<b.size();t++){
        if(a[i]->y==b[t]->y){
           if(a[i]->x==b[t]->x-1){
                adj.push_back(new coord(a[i]->x,a[i]->y));
                adj_dir.push_back(3);
           }else if(a[i]->x==b[t]->x+1) {
                adj.push_back(new coord(b[t]->x,b[t]->y));
                adj_dir.push_back(3);
           }
        }else if(a[i]->x==b[t]->x){
              if(a[i]->y==b[t]->y-1 ){
                 adj.push_back(new coord(b[t]->x,b[t]->y));
                 adj_dir.push_back(0);
              }else if(a[i]->y==b[t]->y+1){
                 adj.push_back(new coord(a[i]->x,a[i]->y));
                 adj_dir.push_back(0);
              }
        }
     }
  }
/*cout<<"\n  ";

        for (int r=0; r<adj.size(); r++){
            cout<<"  "<<adj[r]->x<<" "<<adj[r]->y<<" "<<adj_dir[r]<<"\n";
        }
cout<<"\n  ";*/
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
    cout<<"AAA\n";
   for(int y=0; y<N;y++){
		for(int x=0; x<M;x++){
            ifs>>p;
        //    cout <<p;
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
            castle[x][y]=new point(N,S,W,E);
        }
   }
    cout<<"BBB\n";
  vector< vector<coord*> > rooms;
    cout<<"CCC\n";
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
    cout<<"DDD\n";
   delete visited;
   delete castle;

    int** adjacent;
   adjacent = new  int* [rooms.size()];
   for (int i=0; i < rooms.size(); i++)
         adjacent[i] = new  int[rooms.size()];
    cout<<"EEE\n";
//  cout<<"DONE!!!\n";
/*cout<<"\n  ";
   for(int i=0; i<rooms.size(); i++){
        for (int r=0; r<rooms[i].size(); r++){
            cout<<"  "<<rooms[i][r]->x<<" "<<rooms[i][r]->y;
        }
cout<<"\n  ";
   }*/
   
   int max=0;
   int maxi=0;
   int maxj=0;
   for (int i=0; i < rooms.size(); i++){
            for (int j=0; j < rooms.size(); j++){
                if (i!=j){
                    if( check_adjacent(rooms[i],rooms[j]) ){
                      adjacent[i][j]=rooms[i].size()+rooms[j].size();
                      adjacent[j][i]=rooms[i].size()+rooms[j].size();
                      if (max<adjacent[i][j]) {
                           max=adjacent[i][j];
                           maxi=i;
                           maxj=j;
                       }
               //        cout<<" "<<i <<" "<<j<< "  == "<< adjacent[i][j] << "\n";
                    }
                }
            }
   }
    max=0;
   for(int i=0;i<rooms.size();i++){
       if(rooms[i].size()>max){
          max = rooms[i].size(); 
       }
   }

   ofs<<rooms.size()<<"\n";
   ofs<<max<<"\n";
   ofs <<adjacent[maxi][maxj]<<"\n";
   find_wall(rooms[maxi],rooms[maxj]);
   return 0;
}

