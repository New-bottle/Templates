struct node{
	int l, r, pnt, v, dist;
}a[N * 17 + (N << 1)];
struct Heap{
	int root;
	int size;
	int merge(int x, int y){
		if(!(x && y)) return x ^ y;
		if(a[x].v < a[y].v) swap(x, y);
		a[x].r = merge(a[x].r, y);
		if(a[x].r) a[a[x].r].pnt = x;
		if(a[a[x].l].dist < a[a[x].r].dist) swap(a[x].l, a[x].r);
		a[x].dist = a[a[x].r].dist + 1;
		return x;
	}
	inline int newnode(int x, int p){
		int res = id(x, p);
		a[res].pnt = a[res].l = a[res].r = 0;
		a[res].dist = 1;
		a[res].v = d[x][p];
		return res;
	}
	inline void push(int x, int p){
		size ++;
		int t = newnode(x, p);
		root = merge(root, t);
	}
	inline void pop(int x, int p){
		size--;
		int res = id(x, p);
		int fa = a[res].pnt;
		int t = merge(a[res].l, a[res].r);
		a[t].pnt = fa;
		if(!fa) root = t;
		if(a[fa].l == res) a[fa].l = t;
		if(a[fa].r == res) {a[fa].r = t; a[fa].dist = a[t].dist + 1;}
	}
	inline int top(){return a[root].v;};
	inline int newnode2(int x, int v){
		int res = h(x);
		a[res].dist = 1;
		a[res].l = a[res].r = a[res].pnt = 0;
		a[res].v = v;
		return res;
 	}
	inline void push(int x){
		size ++;
		root = merge(root, x);
	}
	inline void pop(int x){
		size--;
		int fa = a[x].pnt;
		int t = merge(a[x].l, a[x].r);
		a[t].pnt = fa;
		if(!fa) root = t;
		if(a[fa].l == x) a[fa].l = t;
		else if(a[fa].r == x) a[fa].r = t;
	}
	inline void change(int x, int v){
		pop(h(x));
		push(newnode2(x, v));
	}
}q[N << 1],  Q;
