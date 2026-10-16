/**
 * Author: Arman Ferdous (inspiration: tourist, atcoder library)
 * Date:
 * License: 
 * Source:
 * Description: Zero-indexed lazy segment tree with inclusive range updates and queries.
 * The sample node supports range addition and range-sum queries.
 * Time: $\mathcal{O}(\log N)$
 * Status: Tested
 */

#pragma once

template <class T> struct lazy_segtree {
	int n; V<T> t;
	void init(int _) {
		assert(_ >= 0);
		n = _; t.assign(n ? n + n - 1 : 0, T());
	}
	void init(const V<T>& v) {
		n = sz(v); t.assign(n ? n + n - 1 : 0, T());
		if (n) build(0,0,n-1,v);
	}
	template <typename... V>
	void upd(int l, int r, const V&... v) {
	  assert(0 <= l && l <= r && r < n);
	  upd(0, 0, n-1, l, r, v...);
	}
	T get(int l, int r) {
    assert(0 <= l && l <= r && r < n);
    return get(0, 0, n-1, l, r);
  }
private:
	inline void push(int u, int b, int e) {
		if (t[u].lazy == 0) return;
		int mid = (b+e)>>1, rc = u+((mid-b+1)<<1);
		t[u+1].upd(b, mid, t[u].lazy);
		t[rc].upd(mid+1, e, t[u].lazy);
		t[u].lazy = 0;
	}
	void build(int u,int b,int e,const V<T>&v) {
		if (b == e) return void(t[u] = v[b]);
		int mid = (b+e)>>1, rc = u+((mid-b+1)<<1);
		build(u+1, b,mid,v); build(rc, mid+1,e,v);
		t[u] = t[u+1] + t[rc];
	}
	template <typename... V>
	void upd(int u, int b, int e, int l, int r, const V&... v) {
		if (l <= b && e <= r) return t[u].upd(b, e, v...);
		push(u, b, e);
		int mid = (b+e)>>1, rc = u+((mid-b+1)<<1);
		if (l<=mid) upd(u+1, b, mid, l, r, v...);
		if (mid<r) upd(rc, mid+1, e, l, r, v...);
		t[u] = t[u+1] + t[rc];
	}
	T get(int u, int b, int e, int l, int r) {
		if (l <= b && e <= r) return t[u];
		push(u, b, e); 
		T res; int mid = (b+e)>>1, rc = u+((mid-b+1)<<1);
		if (r<=mid) res = get(u+1, b, mid, l, r);
		else if (mid<l) res = get(rc,mid+1,e,l,r);
		else res = get(u+1, b, mid, l, r) + get(rc, mid+1, e, l, r);
		t[u] = t[u+1] + t[rc]; return res;
	}
}; // Hash upto here = f76c77
/* (1) lazy_segtree<node> T; T.init(10) creates everything as node().Consider using V<node> leaves to build
(2) upd(l, r, ...v): Order in ...v must be same as node.upd() fn */
struct node {
	ll sum = 0, lazy = 0;
	node(ll _sum = 0, ll _lazy = 0) : sum(_sum), lazy(_lazy) {}
	friend node operator+(const node &a, const node &b) {
		return node(a.sum + b.sum);
	}
	void upd(int b, int e, ll x) {
		sum += (e - b + 1) * x, lazy += x;
	}
};