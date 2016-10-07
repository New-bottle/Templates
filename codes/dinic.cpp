const int N = 1010, M = 100010;
const int INF = 1e9;
struct edge{
	int to, v;
}E[M << 1];
int head[N], nxt[M << 1], cnt = 1;

void add(int x, int y, int z) {
	E[++ cnt] = (edge){y, z}; nxt[cnt] = head[x]; head[x] = cnt;
	E[++ cnt] = (edge){x, 0}; nxt[cnt] = head[y]; head[y] = cnt;
}

int S, T, d[N], cur[N];
bool mklevel() {
	memset(d, -1, sizeof d);
	Q.push(S);
	d[S] = 0;
	while(!Q.empty()) {
		int x = Q.front(); Q.pop();
		for(int i = head[x]; i; i = nxt[i])
			if (d[E[i].to] == -1 && E[i].v) {
				d[E[i].to] = d[x] + 1;
				Q.push(E[i].to);
			}
	}
	return d[T] != -1;
}

int dfs(int x, int a) {
	if (x == T || a == 0) return a;
	int flow = 0;
	for(int &i = cur[x]; i; i = nxt[i])
		if (d[E[i].to] == d[x] + 1 && E[i].v) {
			int f = dfs(E[i].to, min(E[i].v, a - flow));
			E[i].v -= f;
			E[i ^ 1].v += f;
			flow += f;
			if (f == a) break;
		}
	if (!flow) d[x] = -1;
	return flow;
}

int Dinic() {
	int ans = 0;
	while(mklevel()) {
		for(int i = 0; i <= T; i ++) cur[i] = head[i];
		ans += dfs(S, INF);
	}
	return ans;
}
