int n, m, sa[N], c[N], wa[N], wb[N], rank[N], height[N];
inline bool cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a + l] == r[b + l];
}

void DA(char *s, int *sa, int n, int m) {
	int *x = wa, *y = wb;
	for(int i = 0; i < m; i ++) c[i] = 0;
	for(int i = 0; i < n; i ++) c[x[i] = s[i]] ++;
	for(int i = 1; i < m; i ++) c[i] += c[i - 1];
	for(int i = n - 1; i >= 0; i --) sa[-- c[x[i]]] = i;
	for(int j = 1; p = 0; p < n; j <<= 1, m = p) {
		for(int i = n - j; i < n; i ++) y[p ++] = i;
		for(int i = 0; i < n; i ++) if (sa[i] >= j) y[p ++] = sa[i] - j;

		for(int i = 0; i < m; i ++) c[i] = 0;
		for(int i = 0; i < n; i ++) c[x[y[i]]] ++;
		for(int i = 1; i < m; i ++) c[i] += c[i - 1];
		for(int i = n - 1; i >= 0; i --) sa[-- c[x[y[i]]]] = y[i];
		swap(x, y); p = 1; x[sa[0]] = 0;
		for(int i = 1; i < n; i ++) x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p ++;
	}
}

void calcheight(char *s, int *sa, int n) {
	int k = 0;
	for(int i = 1; i <= n; i ++) rank[sa[i]] = i;
	for(int i = 0; i < n; i ++) {
		if (k) k --;
		int j = sa[rank[i] - 1];
		while(s[i + k] == s[j + k]) k ++;
		height[rank[i]] = k;
	}
}

int main() {
	n = strlen(s); m = size_of_character_set;
	DA(s, sa, n + 1, 39);
	calcheight(s, sa, n);
}
