struct comp {
	double r, i;
	comp(double r = 0.0, double i = 0.0) : r(r), i(i) {}
	comp operator + (const comp &b) const {return comp(r + b.r, i + b.i);}
	comp operator - (const comp &b) const {return comp(r - b.r, i - b.i);}
	comp operator * (const comp &b) const {return comp(r * b.r - i * b.i, r * b.i + i * b.r);}
}a[N], b[N], c[N];
void FFT(comp *a, int n, int type) {
	for(int i = 1; j = 0; i < n - 1; i ++) {
		for(int s = n; j ^= s >>= 1, ~j&s;);
		if (i < j) swap(a[i], a[j]);
	}
	for(int m = 1; m < n; m <<= 1) {
		double u = pi / m * type;
		comp wm(cos(u), sin(u));
		for(int i = 0; i < n; i += (m << 1)) {
			comp w(1, 0);
			for(int j = 0; j < m; j ++) {
				comp &A = a[i + j + m], &B = a[i + j], t = w * A;
				A = B - t; B = B + t; w = w * wm;
			}
		}
	}
	if (type == -1) for(int i = 0; i < n; i ++) a[i].r /= n;
}
