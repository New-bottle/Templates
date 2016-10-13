const int N = 100010;
int D, p[N], tot, root;
struct node {
	int d[2], mn[2], mx[2], l, r, D, size, sum, v;
	int& operator [] (int x) {return d[x];}
}t[N], now;

inline bool cmp(int x, int y) {return t[x][D] < t[y][D];}
#define L t[o].l
#define R t[o].r
#define mid ((l + r) >> 1)
inline void Push_up(int o) {
	for(int i = 0; i < 2; i ++) {
		t[o].mn[i] = min(t[o].mn[i], min(t[L].mn[i], t[R].mn[i]));
		t[o].mx[i] = max(t[o].mx[i], max(t[L].mx[i], t[R].mx[i]));
	}
	t[o].sum = t[L].sum + t[R].sum + t[o].v;
	t[o].size = t[L].size + t[R].size + 1;
}
inline int build(int l, int r, int dir) {
	D = dir;
	nth_element(p + 1, p + mid, p + r + 1, cmp);
	int o = p[mid];
	for(int i = 0; i < 2; i ++) t[o].mn[i] = t[o].mx[i] = t[o][i];
	t[o].sum = t[o].v;
	L = l < mid ? build(l, mid - 1, dir ^ 1) : 0;
	R = mid < r ? build(mid + 1, r, dir ^ 1) : 0;
	Push_up(o);
	return o;
}
inline void dfs(int o){
	if (!o) return;
	dfs(L);
	p[++cnt] = o;
	dfs(R);
}
inline void rebuild(int &o) {
	cnt = 0;
	dfs(o);
	o = bulid(1, cnt, t[o].D);
}
inline void Insert(int &o, int dir) {
	if (!o) {
		o = ++tot; t[o] = now;
		for(int i = 0; i < 2; i ++) t[o].mn[i] = t[o].mx[i] = t[o][i];
		t[o].D = dir;
		t[o].size = 1;
		t[o].sum = t[o].v;
		return;
	}
	if (now[dir] < t[o][dir]) {
		Insert(L, dir ^ 1);
		Push_up(o);
		if ((double)t[L].size > (double)t[o].size * 0.7) rebuild(o);
	} else {
		Insert(R, dir ^ 1);
		Push_up(o);
		if ((double)t[R].size > (double)t[o].size * 0.7) rebuild(o);
	}
}
inline double getans(int o, int k) {
	if (!o) return INF;
}
inline double calc(int o, double k) {
	if (!o) return INF;
	double ans = ....;
}
inline void query(int o, double k) {
	if (!o) return 0;
	double dl = calc(L, k), dr = calc(R, k), d0 = getans(o, k);
	ans = max(ans, d0);
	if (dl < dr) {
		if (dr > ans && R) query(R, k);
		if (dl > ans && L) query(L, k);
	} else {
		if (dl > ans && L) query(L, k);
		if (dr > ans && R) query(R, k);
	}
}
