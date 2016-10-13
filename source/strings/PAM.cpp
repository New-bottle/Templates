int ch[N][26], fail[N], len[N], tot, cnt[N];
void ready() {
	len[0] = 0; len[1] = -1;
	fail[0] = 1; fail[1] = -1;
}
void Insert(char *s, int *cnt) {
	int now = 1, l = strlen(s), x, y, tmp;
	for(int i = 0; i < l; ++ i) {
		x = s[i] - 'a';
		while(s[i] != s[i - len[now] - 1]) now = fail[now];
		if (!ch[now][x]) {
			ch[now][x] = ++ tot;
			len[tot] = len[now] + 2;
		}
		y = ch[now][x];
		tmp = fail[now];
		if (tmp == -1) fail[y] = 0;
		else {
			while(s[i] != s[i - len[tmp] - 1]) tmp = fail[tmp];
			fail[y] = ch[tmp][x];
		}
		now = y;
		cnt[now] ++;
	}
}
