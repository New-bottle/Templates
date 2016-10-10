struct LCT {
	int c[N][2], fa[N], v[N], mx[N];
	bool rev[N];
	int st[N], top;
#define L c[x][0]
#define R c[x][1]
	void Push_up(int x) {
		mx[x] = x;
		if (v[mx[L]] > v[mx[x]]) mx[x] = mx[L];
		if (v[mx[R]] > v[mx[x]]) mx[x] = mx[R];
	}
	void Push_down(int x) {
		if (rev[x]) rev[x] = 0, rev[L] ^= 1, rev[R] ^= 1, swap(L, R);
	}
	bool not_root(int x) {
		return c[fa[x]][0] == x || c[fa[x]][1] == x;
	}
	void Rotate(int x) {
		int y = fa[x], z = fa[y], l = (c[y][1] == x), r = l ^ 1;
		if (not_root(y)) c[z][c[z][1] == y] = x;
		fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
		c[y][l] = c[x][r]; c[x][r] = y;
		Push_up(y);
	}
	void preview(int x) {
		top = 0; st[++top] = x;
		for(;not_root(x); x = fa[x]) st[++top] = fa[x];
		for(int i = top; i; i --) Push_down(st[i]);
	}
	void splay(int x, int y = 0) {
		for(preview(x); not_root(x); Rotate(x))
			if (not_root(y = fa[x]))
				Rotate(c[y][1] == x ^ c[fa[y][1]] == y ? x : y);
		Push_up(x);
	}
	void access(int x, int y = 0) {
		for(;x;splay(x), c[x][1] = y, y = x, x = fa[x]);
	}
	void makeroot(int x) {
		access(x); splay(x); rev[x] ^= 1;
	}
	void link(int x, int y) {
		makeroot(x); fa[x] = y;
	}
	void cut(int x, int y) {
		makeroot(x); access(y); splay(y);
		if (c[y][0] == x) c[y][0] = fa[x] = 0;
	}
	int query(int x, int y) {
		makeroot(x); access(y); splay(y);
		return mx[y];
	}
};
