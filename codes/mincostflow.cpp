
int cost, flow;
struct edge {
	int from, to, v, c;
}E[M];
void ins(int x, int y, int z, int c) {
	E[++ cnt] = (edge){x, y, z, c};
	nxt[cnt] = heda[x]; head[x] = cnt;
}
void add(int x, int y, int z, int c) {
	ins(x, y, z, c); ins(y, x, 0, -c);
}
int S, T, d[N], from[N], Q[M];
bool inq[N];
bool spfa() {
	int l = 0, r = -1;
	for(int i = 0; i <= T; i ++)
		if (d[E[i].to] > d[x] + E[i].c && E[i].v) {
			d[E[i].to] = d[x] + E[i].c;
			from[E[i].to] = i;
			if (!inq[E[i].to]) {
				Q[++ r] = E[i].to;
				inq[E[i].to] = 1;
			}
		}
	return d[T] != INF;
}
void mcf() {
	int x = INF;
	for(int i = from[T]; i; i = from[E[i].from])
		x = min(x, E[i].v);
	for(int i = from[T]; i; i = from[E[i].from]) {
		E[i].v -= x;
		E[i ^ 1].v += x;
	}
	cost += x * d[T];
	flow += x;
}
