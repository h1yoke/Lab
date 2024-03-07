"""
Calculates sequence global alignment (Needleman-Wunsch).

https://en.wikipedia.org/wiki/Needleman–Wunsch_algorithm#Advanced_presentation_of_algorithm
"""

def similarity(ch1, ch2):
    """ Returns similarity between to characters."""
    return 1 if ch1 == ch2 else -1

def get_alignment(s, t):
    """ Calculates alignment for two strings."""
    dp = [[0] * (len(t) + 1) for _ in range(len(s) + 1)]

    for i in range(len(s) + 1):
        dp[i][0] = i * (-2)
    for j in range(len(t) + 1):
        dp[0][j] = j * (-2)

    for i in range(1, len(s) + 1):
        for j in range(1, len(t) + 1):
            match_replace = dp[i - 1][j - 1] + similarity(s[i - 1], t[j - 1])
            delete = dp[i - 1][j] - 2
            insert = dp[i][j - 1] - 2
            dp[i][j] = max(match_replace, insert, delete)
    return restore_chain(s, t, dp)

def restore_chain(s, t, scores):
    """ Answer restoration."""
    s1, t1 = "", ""
    i, j = len(s), len(t)

    while i > 0 or j > 0:
        score = scores[i][j]
        score_diag = scores[i - 1][j - 1]
        score_up = scores[i][j - 1]
        score_left = scores[i - 1][j]

        if score == score_diag + similarity(s[i - 1], t[j - 1]):
            s1 += s[i - 1]
            t1 += t[j - 1]
            i -= 1
            j -= 1
        elif score == score_left - 2:
            s1 += s[i - 1]
            t1 += "-"
            i -= 1
        elif score == score_up - 2:
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

s1, t1 = get_alignment(s, t)
print(s1)
print(t1)
