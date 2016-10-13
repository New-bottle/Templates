//SCC
int dfn[N], low[N], dfs_clock, belong[N], SCC, size[N];
int st[N], top;
bool in[N];
void tarjan(int x) {
	dfn[x] = low[x] = ++dfs_clock;
	st[top++] = x;
	in[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (!dfn[to[i]]) {
			tarjan(to[i]);
			low[x] = min(low[x], low[to[i]]);
		} else if (in[to[i]]) low[x] = min(low[x], dfn[to[i]]);
	if (low[x] == dfn[x]) {
		SCC ++; size[SCC] = 0;
		for(int y = 0; y != x;) {
			y = st[--top];
			in[y] = 0;
			belong[y] = num;
			size[num] ++;
		}
	}
}

//BCC
int dfn[N], low[N], dfs_clock, bccno[N], have[N], size[N], bcc, top;
bool iscut[N];
void tarjan(int x, int fa) {
	low[x] = dfn[x] = ++dfs_clock;
	int child = 0;
	for(int i = head[x]; i; i = nxt[i]) {
		if (!dfn[to[i]]) {
			child ++;
			tarjan(to[i], x);
			low[x] = min(low[to[i]], low[x]);
			if (low[to[i]] >= dfn[x]) iscut[x] = 1;
		} else low[x] = min(low[x], dfn[to[i]]);
	}
	if (fa < 0 && child == 1) iscut[x] = 0;
}

bool vis[N];
void dfs(int x) {
	vis[x] = 1; size[bcc] ++;
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]) {
			if (!iscut[to[i]]) dfs(to[i]);
			else if (bccnoo[to[i]] != bcc)
				bccno[to[i]] = bcc, have[bcc] ++;
		}
}
