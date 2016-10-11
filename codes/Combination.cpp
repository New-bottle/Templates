//Lucas
int C(int n, int m) {
	if (n < m) return 0;
	if (n < P && m < P) return fac[n] * inv[m] % P * inv[n - m] % P;
	return C(n % P, m % P) * C(n / P, m / P);
}
//inv
for(int i = 1; i <= n; i ++)
	inv[i] = (LL)inv[P % i] * (P - P / i) % P;

