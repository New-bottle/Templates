struct node {
  int cnt, l, r;
}t[N * 30];

void update(int &o, int l, int r, int pos) {
  t[++ cnt] = t[o], o = cnt, ++ t[o].cnt;
  if (l == r) return;
  if (pos <= mid) update(t[o].l, l, mid, pos);
  else update(t[o].r, mid + 1, r, pos);
}

int query(int i, int j, int rank) {
  i = root[i], j = root[j];
  int l = 1, r = n;
  while(l != r) {
    if (t[t[j].l].cnt - t[t[i].l].cnt >= rank)
      r = mid, i = t[i].l, j = t[j].l;
    else{
      rank -= t[t[j].l].cnt - t[t[i].l].cnt;
      l = mid + 1, i = t[i].r, j = t[j].r;
    }
  }
  return l;
}
