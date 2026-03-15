#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int N,H,W;
int aware_box=2e9;

void break_near(int i,int j,int cpy[15][12]){
    queue<pair<int,int>> q;
    if(cpy[i][j]==0) return;
    q.push({i,j});
    while(!q.empty()){
        int a = q.front().first;
        int b = q.front().second;
        q.pop();
        int num=cpy[a][b];
        cpy[a][b] = 0;
        int dx[4]={0,0,-1,1};
        int dy[4]={-1,1,0,0};
        if(num<=1)
            continue;
        for(int t=1;t<num;t++){       //방향
            for(int k=0;k<4;k++){
                int nx=a+dx[k]*t;
                int ny=b+dy[k]*t;
                if(nx>=H||nx<0||ny>=W||ny<0)
                    continue;
                if(cpy[nx][ny]==0)
                    continue;
                q.push({nx,ny});
            }
        }
    }
}

void break_box(int n,int arr[15][12]){        // k는 열 위치
    if(aware_box==0)
        return;
    if(n==N){
            int sum=0;
            for(int i=0;i<H;i++){
                for(int j=0;j<W;j++){
                    if(arr[i][j]!=0)
                        sum++;
                }
            }
            aware_box=min(aware_box,sum);
            return;
    }
    for(int k=0;k<W;k++){
    int cpy[15][12];
    memcpy(cpy,arr,sizeof(cpy));        // arr 는 포인터로 넘어오기에 배열크기 x
    // 부수는 함수
    for(int i=0;i<H;i++){
        if(cpy[i][k]!=0){
            break_near(i,k,cpy);
            break;
        }
    }

    // 빈칸이 나오면 위에 올라가서 숫자랑 바꾼다
    for(int i = 0; i < W; i++){
        vector<int> temp;
        for(int j = H - 1; j >= 0; j--){
            if(cpy[j][i] != 0) temp.push_back(cpy[j][i]);
            cpy[j][i] = 0; // 일단 다 비움
        }
        for(int j = 0; j < temp.size(); j++){
            cpy[H - 1 - j][i] = temp[j]; // 아래부터 채움
        }
    }
    // 중력함수
    break_box(n + 1, cpy);
    }
}



int main(){
    int T;
    cin>>T;
    int num=1;
    // arr[H][W];
    while(T--){
        cin>>N>>W>>H;
        int arr[15][12];
        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++){
                cin>>arr[i][j];
            }
        }
        break_box(0,arr);
        cout<<"#"<<num<<" "<<aware_box<<endl;
        num++;
        aware_box=2e9;
    }
}