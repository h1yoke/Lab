"""
Calculates sequence global alignment (Hirschberg).

https://en.wikipedia.org/wiki/Hirschberg%27s_algorithm#Algorithm_description
"""

def similarity(ch1, ch2):
    """ Returns similarity between to characters."""
    return 2 if ch1 == ch2 else -1

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

def needleman_wunsch(s, t):
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

def align_weight(s, t):
    """ Helper hirschberg function with 2-row dp."""
    score = [[0] * (len(t) + 1) for _ in range(2)]

    for j in range(1, len(t) + 1):
        score[0][j] = score[0][j - 1] - 2
    for i in range(1, len(s) + 1):
        score[1][0] = score[0][0] - 2
        for j in range(1, len(t) + 1):
            score_sub = score[0][j - 1] + similarity(s[i - 1], t[j - 1])
            score_del = score[0][j] - 2
            score_ins = score[1][j - 1] - 2
            score[1][j] = max(score_sub, score_del, score_ins)
        for i, x in enumerate(score[1]):
            score[0][i] = x
    result = [0] * (len(t) + 1)
    for j in range(len(t) + 1):
        result[j] = score[1][j]
    return result

def hirschberg(s, t):
    """ Calculates alignment for two strings."""
    s1, t1 = "", ""
    if len(s) == 0:
        for g in t:
            s1 += "-"
            t1 += g
    elif len(t) == 0:
        for g in s:
            s1 += g
            t1 += "-"
    elif len(s) == 1 or len(t) == 1:
        s1, t1 = needleman_wunsch(s, t)
    else:
        xmid = len(s) // 2

        left = align_weight(s[:xmid], t)
        right = align_weight(s[xmid:][::-1], t[::-1])[::-1]

        ymid = 0
        for i in range(1, min(len(left), len(right))):
            if left[ymid] + right[ymid] < left[i] + right[i]:
                ymid = i

        opt1 = hirschberg(s[:xmid], t[:ymid])
        opt2 = hirschberg(s[xmid:], t[ymid:])
        s1 = opt1[0] + opt2[0]
        t1 = opt1[1] + opt2[1]
    return (s1, t1)

# solution
s = input()
t = input()

s1, t1 = hirschberg(s, t)
print(s1)
print(t1)
