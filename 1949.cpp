#include <iostream>
#include <vector>
#include <queue>
#include <cstring>  // memset 사용시에 필요
using namespace std;


// 가장 높은 봉우리 시작이니 최대값 따로 저장

// 높이가 같아도 안됨

// 최대값이 여러개 존재할수있기에 따로 최대값이 저장된 자리를 저장해둘필요있음

// 등산로의 딱 한곳을 최대 k만큼 뺄수있기에 모든 맵을 일단 뺄 필요 있어보임

int arr[8][8];
bool visit[8][8];
int long_road=-1;
int m=0;
int N,k;

// 맵을 넘겨받아서 최대값을 기준으로 차레차례 bfs 하는 함수

// 맵을 1번부터 N*N번까지 1~k를 뺀 맵을 정하기

// 가장높은 봉우리는 5개가 최대

// 결국 하나의 값을 변경하지만 어떤 연쇄반응이 일어날지모르기에 전체를 다 해야함

// 일단 깎고 보는게 아니라 진행하다가 깎을기회가 있고 깎으면 더 나갈수있는 상황일경우

// dfs 백트래킹으로 깎아서 데이터 변경,길이 측정후 백트래킹,이렇게 하면 됨

// 가장 긴 길, 전체를 모두 다녀봐야하는경우 - dfs

// 최단거리,최소횟수,가까운곳 부터 확산 될경우 - bfs

// 하나의 루트를 돌고 변동한거는 백트래킹으로 원상복구 하면 되기에 

// 새로이 맵을 복사해나갈필요 x

void length_route(int i,int j,int len,bool cut,bool visit[8][8]){    // dfs로 여행다님
    long_road=max(long_road,len);
    visit[i][j]=true;
    int now_num=arr[i][j];
    int dx[4]={0,0,-1,1};
    int dy[4]={-1,1,0,0};
    for(int a=0;a<4;a++){
        int nx=i+dx[a];
        int ny=j+dy[a];
        if(nx<0||nx>=N||ny<0||ny>=N)
            continue;
        if(now_num>arr[nx][ny]&&visit[nx][ny]==false)
            length_route(nx,ny,len+1,cut,visit);
        else{
            if(arr[nx][ny]-k<now_num && cut==false&&visit[nx][ny]==false){   // 결국 지금있는곳보다 1작은게 베스트기에
                int backup=arr[nx][ny];
                arr[nx][ny]=now_num-1;
                length_route(nx,ny,len+1,true,visit);
                arr[nx][ny]=backup;
            }
        }
    }
    visit[i][j]=false;
    return;
}

// dfs를 돌때 저장해야하는것 

// 방문표시는 결국 할필요없다 
// 큰값에서 작은값으로 가기에 단순히 깎이 여부만 기록할 필요있음

int main(){
    int T;
    cin>>T;
    int num=1;
    while(T--){
        cin>>N>>k;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                cin>>arr[i][j];
                m=max(m,arr[i][j]);
            }
        }
    // 최대값 저장되어있음
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
               if(m==arr[i][j]){
                   memset(visit,false,sizeof(visit));
                   length_route(i,j,1,false,visit);
               }
            }   
        }
        cout<<"#"<<num<<" "<<long_road<<"\n";
        num++;
        long_road=-1;
        m=0;
    }
    return 0;
}