//求串S中最长的回文子串的长度
char s[N];
int a[N];
int manacher(char *s) {
	memset(p, 0, sizeof p);
	int n = strlen(s);
	for(int i = 1; i <= n; i ++) a[i << 1] = b[i - 1];
	n = n << 1 | 1;
	int id = 0, mx = 0, ans = 0;
	for(int i = 1; i <= n; i ++) {
		if (mx > i) p[i] = min(p[2 * id - i], mx - i);
		while(i - p[i] - 1 > 0 && i + p[i] + 1 <= n 
				&& a[i - p[i] - 1] == a[i + p[i] + 1]) p[i] ++;
		if (p[i] + i > mx) mx = p[i] + i, id = i;
		if (p[i] > ans) ans = p[i];
	}
	return ans;
}
