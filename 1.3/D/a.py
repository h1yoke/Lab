
""" generate new steps from position """
def get_step(pos):
  if pos == 0:
    return [4, 6]
  if pos == 1:
    return [6, 8]
  if pos == 2:
    return [7, 9]
  if pos == 3:
    return [4, 8]
  if pos == 4:
    return [0, 3, 9]
  if pos == 5:
    return []
  if pos == 6:
    return [0, 1, 7]
  if pos == 7:
    return [2, 6]
  if pos == 8:
    return [1, 3]
  if pos == 9:
    return [2, 4]
  return []

""" main """
n = int(input())
dp = []
for i in range(10):
  dp.append([])
  for j in range(n + 1):
    dp[i].append(0)

for i in range(10):
  dp[i][1] = 1

for j in range(2, n + 1):
  for i in range(10):
    for new_pos in get_step(i):
      dp[i][j] = dp[i][j] + dp[new_pos][j - 1]

# Sum: n length, [0; 9] \ {0; 8} digits
print(dp[1][n] + dp[2][n] + dp[3][n] + dp[4][n] + dp[5][n] + dp[6][n] + dp[7][n] + dp[9][n])
