"""
Calculates sequence global alignment score with weighted gap penalty.

`gap_weight = ρ + i · σ`
"""

def similarity(ch1, ch2):
    """ Returns similarity between to characters."""
    return 1 if ch1 == ch2 else -1

def get_alignment_score(s, t):
    """ Calculates alignment for two strings."""
    upper = [[int(-1e10)] * (len(t) + 1) for _ in range(len(s) + 1)]
    lower = [[int(-1e10)] * (len(t) + 1) for _ in range(len(s) + 1)]
    main  = [[0] * (len(t) + 1) for _ in range(len(s) + 1)]

    for i in range(0, len(s) + 1):
        for j in range(0, len(t) + 1):
            if i > 0:
                upper[i][j] = max(upper[i - 1][j] + sigma, main[i - 1][j] + sigma + rho)
            if j > 0:
                lower[i][j] = max(lower[i][j - 1] + sigma, main[i][j - 1] + sigma + rho)
            if i > 0 or j > 0:
                main[i][j] = max(upper[i][j], lower[i][j])
            if i > 0 and j > 0:
                main[i][j] = max(main[i][j], main[i - 1][j - 1] + similarity(s[i - 1], t[j - 1]))
    return main[-1][-1]

# solution
s = input()
t = input()
rho, sigma = [int(x) for x in input().split(' ')]

print(get_alignment_score(s, t))
