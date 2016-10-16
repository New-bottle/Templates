#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#define M 101
#define N 101010 
#define INF 0x3f3f3f3f
#define LL long long
using namespace std;
int n, m, n1, n2, pos[M][M];
bool map[M][M];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
vector<int> edge[N];
int match[N];
void dfs(int u, bool ans[]){
    ans[u] = true;
    for(int i = 0; i < edge[u].size(); i ++){
        if(match[edge[u][i]] != -1 && !ans[match[edge[u][i]]]){
            dfs(match[edge[u][i]], ans);
        }
    }
}
bool mark[N], vis[N];
bool find(int u){
    for(int i = 0; i < edge[u].size(); i ++){
        int v = edge[u][i];
        if(!vis[v]){
            vis[v] = 1;
            if(match[v] == -1 || find(match[v])){
                match[v] = u; return true;
            }
        }
    }
    return false;
}
int hungary(int cnt){
    int res = 0;
    memset(match, -1, sizeof(match));
    memset(mark, 0, sizeof(mark));
    for(int i = 1; i <= cnt; i ++){
        memset(vis, 0, sizeof(vis));
        if(!find(i)){
            mark[i] = 1;
            res ++;
        }
    }
    return res;
}
bool ans[2][N];
int main(){
    char c;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            scanf(" %c", &c);
            if(c == '.'){
                map[i][j] = 1;
                if((i & 1) ^ (j & 1) == 0){
                    ++ n1;
                    pos[i][j] = n1;
                }
                else{
                    ++ n2;
                    pos[i][j] = n2;
                }
            }
            else map[i][j] = 0;
        }
    }
    for(int i = 1; i <= n; i ++){
        for(int j = (i & 1 ? 1 : 2); j <= m; j += 2){
            if(map[i][j]){
                for(int k = 0; k < 4; k ++){
                    int xx = i + dx[k], yy = j + dy[k];
                    if(0 < xx && xx <= n && 0 < yy && yy <= m && map[xx][yy]){
                        edge[pos[i][j]].push_back(pos[xx][yy]);
                    }
                }
            }
        }
    }
    int tmp = hungary(n1);
    if(tmp == n1 && tmp == n2){
        puts("LOSE");
        return 0;
    }
    for(int i = 1; i <= n1; i ++){
        if(mark[i]) dfs(i, ans[0]);
    }
    for(int i = 1; i <= n1; i ++) edge[i].clear();
    for(int i = 1; i <= n; i ++){
        for(int j = (i & 1 ? 2 : 1); j <= m; j += 2){
            if(map[i][j]){
                for(int k = 0; k < 4; k ++){
                    int xx = i + dx[k], yy = j + dy[k];
                    if(0 < xx && xx <= n && 0 < yy && yy <= m && map[xx][yy]){
                        edge[pos[i][j]].push_back(pos[xx][yy]);
                    }
                }
            }
        }
    }
    hungary(n2);
    for(int i = 1; i <= n2; i ++){
        if(mark[i]) dfs(i, ans[1]);
    }
     
    puts("WIN");
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            if(map[i][j] && ans[(i & 1)^ (j & 1)][pos[i][j]]){
                printf("%d %d\n", i, j);
            }
        }
    }
    return 0;
}
﻿
