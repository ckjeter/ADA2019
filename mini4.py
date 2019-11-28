import numpy as np

w = np.array([0, 1, 3, 4, 5, 8, 10, 11])
v = np.array([0, 3, 7, 10, 12, 17, 19, 21])
dp = np.zeros((8, 16))

for i in range(1,8):
	for y in range(1,16):
		if w[i] > y:
			dp[i][y] = dp[i-1][y]
		else:
			dp[i][y] = max(dp[i-1][y], v[i] + dp[i-1][y-w[i]])

print(dp)