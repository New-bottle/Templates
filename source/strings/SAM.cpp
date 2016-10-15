struct Suffix_Automation{
	struct node{
		int son[26];
		int pre,cnt,len,right;
	}a[N<<2];
	int tail,tot;
	
	void insert(int key){
		int np,nq,p,q;
		if(a[tail].son[key]){
			if(a[q=a[tail].son[key]].len==a[tail].len+1) tail=q;
			else{
				a[nq=++tot]=a[q];
				a[nq].right=0;
				a[nq].len=a[tail].len+1;
				a[q].pre=nq;
				for(p=tail;a[p].son[key]==q;p=a[p].pre) a[p].son[key]=nq;
				tail=nq;
			}
		}
		else{
			a[np=++tot].len=a[tail].len+1;
			for(p=tail;p && !a[p].son[key];p=a[p].pre) a[p].son[key]=np;
			if(!a[p].son[key]){
				a[p].son[key]=np;
				a[np].pre=p;
			}
			else{
				if(a[q=a[p].son[key]].len==a[p].len+1)  a[np].pre=q;
				else{
					a[nq=++tot]=a[q];
					a[nq].len=a[p].len+1;
					a[nq].right=0;
					a[q].pre=a[np].pre=nq;
					for(;a[p].son[key]==q;p=a[p].pre) a[p].son[key]=nq;
				}
			}
			tail=np;
		}
		a[tail].right++;
	}
	
	void bfs(){
		static int cnt[N],l,r,q[N];
		for(int i=1;i<=tot;i++){
			cnt[a[i].pre]++;
			a[i].cnt=1;
		}
		l=r=0;
		for(int i=1;i<=tot;i++){
			if(!cnt[i]) q[++r]=i;
		}
		
		while(l!=r){
			int u=q[++l];
			int p=a[u].pre;
			a[p].right+=a[u].right;
			a[p].cnt+=a[u].cnt+a[u].right;
			if(!--cnt[p]) q[++r]=p;
		}
	}
}sam;
