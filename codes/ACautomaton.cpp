int cnt = 1;
struct Trie {
	int ch[26], cnt, fail;
	bool sign;
}T[N];
inline int id(char c) {return c - 'A';}
void Ins(char *s) {
	int x = 1, y, l = strlen(s);
	for(int i = 0; i < l; i ++) {
		y = id(s[i]);
		if (!T[x].ch[y]) T[x].ch[y] = ++cnt;
		x = T[x].ch[y];
	}
	T[x].sign = 1;
}
int Q[N];
void make_fail() {
	int l = 0, r = -1;
	Q[++r] = 1;
	while(l <= r) {
		int x = Q[l++], y, j;
		for(int i = 0; i < 26; i ++) {
			j = T[x].fail;
			T[x].sign |= T[j].sign;
			while(j && !T[x].ch[i]) j = T[j].fail;
			if (T[x].ch[i]) {
				y = T[x].ch[i];
				T[y].fail = j ? T[j].ch[i] : 1;
				Q[++r] = y;
			} else T[x].ch[i] = j ? T[j].ch[i] : 1;
		}
	}
}
