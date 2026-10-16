/**
 * Author: MTB Ishmam (inspiration: KACTL)
 * Date: 2026-07-17
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed iterative segment tree with point updates and inclusive range queries.
 * Customize the node identity and its associative operator+.
 * Time: $\mathcal{O}(\log N)$
 * Status: stress-tested
 */
#pragma once

struct node { // only change here
	ll x;
	node(ll _ = LLONG_MIN) : x(_) {} // identity elem
	friend node operator+(const node &a, const node &b) {
		return node(max(a.x, b.x));
	}
};
template <class T> struct segtree {
	int n; V<T> t;
	segtree(int _ = 0) { init(_); }
	void init(int _) {// init-> HLD, Euler tours
		n = 1; while (n < _) n <<= 1;
		t.assign(2 * n, T());
	}
	void update(int i, T v) { // 0 <= i < n
		for (t[i += n] = v; i >>= 1;)
			t[i] = t[i << 1] + t[i << 1 | 1];
	}
	T query(int l, int r) { // [l, r] && l <= r
		T lc, rc;
		for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) lc = lc + t[l++];
			if (!(r & 1)) rc = t[r--] + rc;
		}
		return lc + rc;
	}
};