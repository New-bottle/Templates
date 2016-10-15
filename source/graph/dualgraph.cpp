//bzoj 2965
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#define N 5010
#define M 500010
#define INF 0x3f3f3f3f
#define LL long long
using namespace std;
int p,n,m;

namespace Max_Flow{
	struct Edge{
		int x,y,v;
		Edge(){}
		Edge(int a,int b,int c){
			x=a;
			y=b;
			v=c;
		}
	}e[M];
	int cnt;
	
	int S,T;
	
	int head[N],next[M],edge[M],f[M],tot=1;
	void connect(int a,int b,int c){
		++tot;next[tot]=head[a];head[a]=tot;edge[tot]=b;f[tot]=c;
		++tot;next[tot]=head[b];head[b]=tot;edge[tot]=a;f[tot]=0;
	}
	
	void init(){
		tot=1;
		memset(head,0,sizeof(head));
	}
	
	void rebuild(){
		for(int i=1;i<=cnt;i++){
			connect(e[i].x,e[i].y,e[i].v);
		}
	}
	
	int l,r,q[N],d[N];
	bool bfs(){
		l=r=0;
		memset(d,0,sizeof(d));
		d[S]=1;
		q[++r]=S;
		while(l!=r){
			int u=q[++l];
			for(int i=head[u];i;i=next[i]){
				int v=edge[i];
				if(f[i] && !d[v]){
					d[v]=d[u]+1;
					if(v==T) return true;
					q[++r]=v;
				}
			}
		}
		return false;
	}
	
	int dinic(int u,int flow){
		if(u==T) return flow;
		
		int tmp=flow,k;
		for(int i=head[u];i;i=next[i]){
			int v=edge[i];
			if(tmp && f[i] && d[v]==d[u]+1){
				k=dinic(v,min(f[i],tmp));
				if(!k) d[v]=0;
				f[i]-=k;
				f[i^1]+=k;
				tmp-=k;
			}
		}
		return flow-tmp;
	}
}

namespace Graph{
	int _index;
	
	struct Point{
		double x,y;
		Point (){}
		Point (double a,double b){
			x=a;
			y=b;
		}
		friend Point operator + (const Point &a,const Point &b){
			return Point (a.x+b.x,a.y+b.y);
		}
		friend Point operator - (const Point &a,const Point &b){
			return Point (a.x-b.x,a.y-b.y);
		}
		friend double operator * (const Point &a,const Point &b){
			return a.x*b.y-a.y*b.x;
		}
		friend double operator ^ (const Point &a,const Point &b){
			return a.x*b.x+a.y*b.y;
		}
		
		inline void read(){
			scanf("%lf%lf",&x,&y);
		}
	}_point[30],point[N];
	
	struct Line{
		Point s,t;
		Line(){}
		Line(const Point &a,const Point &b){
			s=a;
			t=b;
		}
		bool online(const Point &b)const{
			return ((b-s)*(t-s)==0 && (b.x-s.x)*(b.x-t.x)<=0 && (b.y-s.y)*(b.y-t.y)<=0);
		}
	};
	
	struct Link{
		int to,v,belong;
		double alpha;
		Link *another;
		Link(){}
		Link(int a,int b,double c){
			another=0x0;
			to=a;
			v=b;
			belong=0;
			alpha=c;
		}
	};
	
	bool cmp(Link *a,Link *b){
		return a->alpha<b->alpha;
	}
	
	vector<Link*> a[N];
	vector<Point> polygon; 
	
	void add(int x,int y,int z){
		Point p=point[y]-point[x];
		Link *temp1=new Link(y,z,atan2(p.y,p.x));
		Link *temp2=new Link(x,z,atan2(-p.y,-p.x));
		temp1->another=temp2;
		temp2->another=temp1;
		a[x].push_back(temp1);
		a[y].push_back(temp2);
	}
	
	void dfs(Link *p1){
		Link *p2=p1->another;
		int y=p1->to;
		int x=p2->to;
		
		p1->belong=_index;
		polygon.push_back(point[x]);
		
		vector<Link*>::iterator t;
		t=upper_bound(a[y].begin(),a[y].end(),p2,cmp); 
		if(t==a[y].end()) t=a[y].begin();
		
		if((*t)->belong) return;
		dfs(*t);
	}
	
	double Get_Area(){
		int n=polygon.size();
		double s=polygon[0].y*(polygon[n-1].x-polygon[1].x)+polygon[n-1].y*(polygon[n-2].x-polygon[0].x);
		for(int i=1;i<n-1;i++){
			s+=polygon[i].y*(polygon[i-1].x-polygon[i+1].x);
		}
		return s/2;
	}
	
	bool Cross(Line l1,Line l2){
		return(
			(max(l1.s.x,l1.t.x)>=min(l2.s.x,l2.t.x))&&
			(min(l1.s.x,l1.t.x)<=max(l2.s.x,l2.t.x))&&
			(max(l1.s.y,l1.t.y)>=min(l2.s.y,l2.t.y))&&
			(min(l1.s.y,l1.t.y)<=max(l2.s.y,l2.t.y))&&
			(((l1.s-l2.t)*(l2.s-l2.t))*((l1.t-l2.t)*(l2.s-l2.t))<=0)&&
			(((l2.s-l1.t)*(l1.s-l1.t))*((l2.t-l1.t)*(l1.s-l1.t))<=0)&&
			!l1.online(l2.s) && !l1.online(l2.t) && !l2.online(l1.s) && !l2.online(l1.t)
		);
	}
	
	bool In_Polygon(const Point &p){
		Line l1=Line(p,p);
		l1.t.x=1e10;
		
		int intersection=0,n=polygon.size();
		for(int i=0;i<n;i++){
			Line l2=Line(polygon[i],polygon[(i+1)%n]);
			if(l2.online(p)) return false;
			if(Cross(l1,l2)||
			   (l1.online(polygon[(i+1)%n])&&
			    (!l1.online(polygon[(i+2)%n])&&
				 ((polygon[i]-p)*(polygon[(i+1)%n]-p))*((polygon[(i+2)%n]-p)*(polygon[(i+1)%n]-p))<0)||
				(l1.online(polygon[(i+2)%n])&&
				 ((polygon[i]-p)*(polygon[(i+1)%n]-p))*((polygon[(i+3)%n]-p)*(polygon[(i+1)%n]-p))<0)
			   )
			  ) intersection++;
		}
		if(intersection&1) return true;
		return false;
	}
}

int ans[N],pos[30];
int main(){
	using namespace Graph;
	using namespace Max_Flow;
	
	int x,y,z;
	scanf("%d%d%d",&p,&n,&m);
	for(int i=1;i<=p;i++){
		_point[i].read();
	}
	for(int i=1;i<=n;i++){
		point[i].read();
	}
	
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	
	for(int i=1;i<=n;i++){
		sort(a[i].begin(),a[i].end(),cmp);
	}
	
	T=0;
	for(int i=1;i<=n;i++){
		vector<Link*>::iterator t;
		for(t=a[i].begin();t!=a[i].end();t++){
			if(!(*t)->belong){
				polygon.clear();
				
				++_index;
				dfs(*t);
				
				if(Get_Area()>0){
					e[++cnt]=Edge(_index,T,INF);
					continue;
				}
				
				for(int j=1;j<=p;j++){
					if(In_Polygon(_point[j])){
						pos[j]=_index;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		vector<Link*>::iterator t;
		for(t=a[i].begin();t!=a[i].end();t++){
			e[++cnt]=Edge((*t)->belong,(*t)->another->belong,(*t)->v);
		}
	}
	
	S=_index+1;
	
	memset(ans,0x3f,sizeof(ans));
	
	for(int i=1;i<(1<<p);i++){
		int digit=0;
		init();
		rebuild();
		for(int j=0;j<p;j++){
			if(i & (1<<j)){
				digit++;
				connect(S,pos[j+1],INF);
			}
		}
		int maxflow=0;
		while(bfs()) maxflow+=dinic(S,INF);
		ans[digit]=min(ans[digit],maxflow);
	}
	
	for(int i=1;i<=p;i++) printf("%d\n",ans[i]);
	return 0;
}
