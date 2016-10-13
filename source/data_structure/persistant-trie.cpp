int t[M][2], rt[N], id[M], tot;

inline void Ins(int pre, int x, int k) {
	int now = rt[k] = ++tot; id[tot] = k;
	for(int i = 30; i >= 0; i --) {
		int j = (x >> i) & 1;
		t[now][j ^ 1] = t[pre][j ^ 1];
		t[now][j] = ++tot; id[tot] = k;
		now = tot;
		pre = t[pre][j];
	}
}
inline int query(int l, int r, int x) {
	int ans = 0, now = rt[r];
	for(int i = 30; i >= 0; i --) {
		int j = ((x >> i) & 1) ^ 1;
		if (id[t[now][j]] >= l) ans |= 1 << i; else j ^= 1;
		now = t[now][j];
	}
	return ans;
}

