
LL a[N], r[N], n;
void exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
	if (!b) {d = a; x = 1; y = 0;}
	else {exgcd(b, a%b, d, y, x); y -= (a / b) * x;}
}

LL ex_CRT(LL *m, LL *r, int n) {
	LL M = m[1], R = r[1], x, y, d;
	for(int i = 2; i <= n; i ++) {
		exgcd(M, m[i], d, x, y);
		if ((r[i] - R) % d) return -1;
		x = (r[i] - R) / d * x % (m[i] / d);
		R += x * M;
		M = M / d * m[i];
		R %= M;
	}
	return R > 0 ? R : R + M;
}
