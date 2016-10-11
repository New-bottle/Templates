
int tot, prime[N], mu[N], sum[N];
bool check[N];
void getmu() {
	mu[1] = 1;
	for(int i = 2; i < n; i ++) {
		if (!check[i]) {
			prime[++ tot] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= tot; j ++) {
			if (i * prime[j] > n) break;
			check[i * prime[j]] = 1;
			if (i % prime[j]) mu[i * prime[j]] = -mu[i];
			else {
				mu[i * prime[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1; i < n; i ++) sum[i] = sum[i - 1] + mu[i];
}
