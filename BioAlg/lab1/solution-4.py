"""
Calculates sequence alignment with weighted gap penalty.

`gap_weight = ρ + i · σ`
"""

def similarity(ch1, ch2):
    """ Returns similarity between to characters."""
    return 1 if ch1 == ch2 else -1

def get_alignment(s, t):
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
    return restore_chain(s, t, upper, lower, main)

def restore_chain(s, t, upper, lower, main):
    """ Answer restoration."""
    s1, t1 = "", ""
    i, j = len(s), len(t)

    while i > 0 or j > 0:
        score = main[i][j]
        score_main = main[i - 1][j - 1]
        score_upper = upper[i][j]
        score_lower = lower[i][j]

        if score == score_main + similarity(s[i - 1], t[j - 1]):
            # match / mismatch
            s1 += s[i - 1]
            t1 += t[j - 1]
            i -= 1
            j -= 1
        elif score == score_upper:
            # found end of insertion
            while i > 0 and upper[i][j] == upper[i - 1][j] + sigma:
                # move through insertions
                s1 += s[i - 1]
                t1 += "-"
                i -= 1
            if i > 0 and upper[i][j] == main[i - 1][j] + sigma + rho:
                # found start of insertion
                s1 += s[i - 1]
                t1 += "-"
                i -= 1
        elif score == score_lower:
            # found end of deletion
            while j > 0 and lower[i][j] == lower[i][j - 1] + sigma:
                # move through deletions
                s1 += "-"
                t1 += t[j - 1]
                j -= 1
            if j > 0 and lower[i][j] == main[i][j - 1] + sigma + rho:
                # found start of deletion
                s1 += "-"
                t1 += t[j - 1]
                j -= 1
    while i > 0:
        s1 += s[i - 1]
        t1 += "-"
        i -= 1
    while j > 0:
        s1 += "-"
        t1 += t[j - 1]
        j -= 1
    return (s1[::-1], t1[::-1])

# solution
s = input()
t = input()
rho, sigma = [int(x) for x in input().split(' ')]

s1, t1 = get_alignment(s, t)
print(s1)
print(t1)
